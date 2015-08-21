#include "AGimageFeat.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif	//#if AGMAGIC_SUPPORT_MFC
/*****************************************class CAGfeatUtil******************************/

IAGflexfVec* CAGfeatUtil::CreateFeaturesVector()
{
	switch(CAGmagicIPConfUtil::AGmagicIP_ClobalFeatures)
	{
	case AGMAGICIP_256CLR_FEATURE :
		return new CAGimage256ClrfVec();
	case AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE :
		return new CAGimage12HSVClr9GridTxtfVec();
	case AGMAGICIP_MULTICLR_FEATURE :
		throw _T("Implement not yet");
	case AGMAGICIP_MULTIATT_FEATURE :
		throw _T("Implement not yet");
	default:
		throw _T("Fatal Error");
	}
}
IAGflexfMatrix* CAGfeatUtil::CreateFeaturesMatrix()
{
	switch(CAGmagicIPConfUtil::AGmagicIP_ClobalFeatures)
	{
	case AGMAGICIP_256CLR_FEATURE :
		return new CAGimage256ClrfMatrix();
	case AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE :
		return new CAGimage12HSVClr9GridTxtfMatrix();
	case AGMAGICIP_MULTICLR_FEATURE :
		throw _T("Implement not yet");
	case AGMAGICIP_MULTIATT_FEATURE :
		throw _T("Implement not yet");
	default:
		throw _T("Fatal Error");
	}
}
agbool CAGfeatUtil::TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers,	CAGbuRectVec* pInRects, 
								 CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								 agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures)
{
	//pInRects va pOutTextures phai co cung phan tu va khoi dau phai co phan tu
	if(centers==NULL || pInRects==NULL || center_pixels == NULL || nTotalPixels==0 || pOutTextures==NULL)	throw _T("Invalid parameter");
	pOutTextures->RemoveAll();

	agint32 nCenters=centers->GetSize();
	agint32 nTextures=pInRects->GetSize();
	if(nCenters!=center_pixels->GetSize())	throw _T("Invalid parameter");
	if(nCenters==0 || nTextures==0)			return agfalse;
	
	pOutTextures->SetSize(nTextures);
	for(agint32 i=0; i<nCenters; i++)
	{
		agreal64		ratio=(agreal64)center_pixels->GetAt(i)/(agreal64)nTotalPixels;
		if(ratio > 1)	throw _T("Fatal error");
		if(  ratio < ExcludePixelsPercent )	continue;

		AGBU_POINT pt=centers->GetAt(i);
		agint32	   j=0;
		for(j=0; j<nTextures; j++)
		{
			AGBU_RECT rc=pInRects->GetAt(j);
			if(rc.left<=pt.x   && pt.x<rc.right &&
			   rc.bottom<=pt.y && pt.y<rc.top
			  )
			  break;
		}
		if(j<nTextures)	pOutTextures->SetAt(j,pOutTextures->GetAt(j)+1);////neu tim thay
	}
	return agtrue;
}
agbool CAGfeatUtil::TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers, AGBU_RECT TotalRect, SIZE block_size, 
								 CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								 agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures)
{
	if(pOutTextures==NULL)	throw _T("Invalid parameter");
	pOutTextures->RemoveAll();

	CAGbuRectVec InRects;
	if(!InRects.CreateByCut(TotalRect,block_size))	return agfalse;
	pOutTextures->SetSize(InRects.GetSize());
	if(!TextureMidPoint(centers,&InRects,center_pixels,nTotalPixels,ExcludePixelsPercent,pOutTextures))
	{
		pOutTextures->RemoveAll();
		return agfalse;
	}
	return agtrue;
}
agbool CAGfeatUtil::TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers,	AGBU_RECT TotalRect, agint32 nRows, agint32 nCols, 
								 CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								 agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures)
{
	if(pOutTextures==NULL)	throw _T("Invalid parameter");
	pOutTextures->RemoveAll();

	CAGbuRectVec InRects;
	if(!InRects.CreateByCut(TotalRect,nRows,nCols))	return agfalse;
	pOutTextures->SetSize(InRects.GetSize());
	if(!TextureMidPoint(centers,&InRects,center_pixels,nTotalPixels,ExcludePixelsPercent,pOutTextures))
	{
		pOutTextures->RemoveAll();
		return agfalse;
	}
	return agtrue;
}

/*****************************************class CAGimageAffMatrix, class CAGaffArray******************************/

CAGimageAffMatrix::CAGimageAffMatrix() : CAGimagefMatrix<agfreal, AGMAGICIP_AFFINITY>()
{
}
CAGimageAffMatrix::~CAGimageAffMatrix()
{
}

agfreal* CAGimageAffMatrix::paff(aguint_id mID, aguint_id nID, agbool throwErr)
{
	agint32 i=LSearchImageID(mID);
	if(i==-1)
	{
		if(throwErr)	throw _T("Can not find ID");
		else			return NULL;
	}

	CAGimageAffVec* pAff=(CAGimageAffVec*)m_vector[i];
	agint32 j=pAff->m_aRelatedImageID.LSearch(nID);
	if(j==-1)
	{
		if(throwErr)	throw _T("Can not find ID");
		else			return NULL;
	}
	return &(pAff->m_vector[i]);
}
agfreal CAGimageAffMatrix::aff(aguint_id mID, aguint_id nID, agbool throwErr)
{
	agfreal* paff_value=paff(mID,nID,throwErr);
	if(paff_value)		return *paff_value;
	else if(throwErr)	throw _T("Error due to return NULL");
	else				return NULL;
}
void CAGimageAffMatrix::SetAff(aguint_id mID, aguint_id nID, agfreal value)
{
	agint32	mIDIdx=LSearchImageID(mID);
	if(mIDIdx!=-1)//neu tim thay
	{
		CAGimageAffVec*	pAff=(CAGimageAffVec*)(m_vector[mIDIdx]);
		agint32					nIDIdx=pAff->m_aRelatedImageID.LSearch(nID);
		if(nIDIdx!=-1)			pAff->SetAt(nIDIdx,value);
		else
		{
			pAff->m_aRelatedImageID.Add(nID);;
			pAff->Add(value);
		}
	}
	else
	{
		CAGimageAffVec*	pAff=new CAGimageAffVec();
		pAff->m_ImageID=mID;
		pAff->m_aRelatedImageID.Add(nID);;
		pAff->DBCnnAttach(m_pDBCnnI);
		pAff->m_bIsNorm=m_bIsNorm;
		pAff->Add(value);

		Add(pAff);
	}
}
void CAGimageAffMatrix::DeleteAllAffInDB(void* pDBCnnI)
{
	if(pDBCnnI==NULL)	throw _T("Invalid parameter");

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesAffinity"),agtrue);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesNormAffinity"),agtrue);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;
}
agbool CAGimageAffMatrix::CreateAffInDB(void* pDBCnnI, aguint_id ImageType)
{
	if(pDBCnnI==NULL)	throw _T("Invalid parameter");

//////////////////////////////
	CAGimageIDs ImageIDs;
	ImageIDs.DBCnnAttach(pDBCnnI);
	ImageIDs.DBRead(ImageType);
	agint32		m=ImageIDs.GetSize();
	if(m==0)	return agfalse;
	for(agint32 i=0; i<m; i++)
	{
		aguint_id ImageID=ImageIDs.GetAt(i);
		CAGimageIDs TempImageIDs;
		TempImageIDs.CopyFrom(&ImageIDs);
		TempImageIDs.RemoveIfValue(ImageID);
		
		agint32		n=TempImageIDs.GetSize();
		if(n==0)	continue;
		if(n!=m-1)	throw _T("Fatal Error");

		CAGimageAffVec affs, norm_affs;
		affs.DBCnnAttach(pDBCnnI);
		norm_affs.DBCnnAttach(pDBCnnI);
		affs.SetIsNorm(agfalse);
		norm_affs.SetIsNorm(agfalse);

		affs.SetSize(n);
		norm_affs.SetSize(n);
		affs.m_aRelatedImageID.SetSize(n);
		norm_affs.m_aRelatedImageID.SetSize(n);
		for(agint32 j=0; j<n; j++)
		{
			if(ImageID==TempImageIDs.GetAt(j)) throw _T("Fatal Error");
			affs.m_aRelatedImageID.SetAt(j,TempImageIDs.GetAt(j));//column RELATEDIMAGEID la cot 1
			affs.m_vector[j]=1;

			norm_affs.m_aRelatedImageID.SetAt(j,TempImageIDs.GetAt(j));//column RELATEDIMAGEID la cot 1
			norm_affs.m_vector[j]=1;
		}
		affs.m_ImageID=norm_affs.m_ImageID=ImageID;
		affs.m_pNoFreeTempAGimageSrc=norm_affs.m_pNoFreeTempAGimageSrc=NULL;
		norm_affs.Normalize();

		affs.DBInsert();
		norm_affs.DBInsert();
	}
	return agtrue;
}
void CAGimageAffMatrix::SetAffToDB(void* pDBCnnI, aguint_id mID, aguint_id nID, agfreal value, agbool bIsNorm)
{
	agtchar*	SQL=NULL;
	//doc thu
	if(!bIsNorm)	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT measure FROM ImagesAffinity WHERE ImageID="),agtrue);
	else				CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT measure FROM ImagesNormAffinity WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,mID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RelatedImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,nID,agtrue);

	agfreal*	data=NULL;
	agint32			fieldsNum;
	AGdbRead(pDBCnnI,SQL,agfalse,data,fieldsNum);
	if(SQL)	free(SQL); SQL=NULL;

	agbool bInsert=(data==NULL);//khong co record nay ?
	
	if(bInsert)
	{
		if(!bIsNorm)
			CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO ImagesAffinity"),agtrue);
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO ImagesNormAffinity"),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T("(IMAGEID,RELATEDIMAGEID,MEASURE) VALUES("),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,mID,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,nID,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);

		AG_private_tcscat_number(SQL,value,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	}
	else
	{
		if(fieldsNum!=1)	throw _T("Fatal Error");
		if(!bIsNorm)
			CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesAffinity SET "),agtrue);
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesNormAffinity SET "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,_T("MEASURE="),agtrue);
		AG_private_tcscat_number(SQL,value+data[0],agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE IMAGEID="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,mID,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RELATEDIMAGEID="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,nID,agtrue);
	}
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;
	if(data!=NULL)		free(data);
}
agbool CAGimageAffMatrix::ReplaceImageID(void* pDBCnnI, aguint_id ImageID, aguint_id ReplaceImageID, agbool bIsNorm)
{
	agtchar*	SQL=NULL;
	if(!bIsNorm)
		CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesAffinity SET IMAGEID="),agtrue);
	else
		CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesNormAffinity SET IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ReplaceImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	agbool bResult=CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;
	return bResult;
}
agbool CAGimageAffMatrix::ReplaceRelatedImageID(void* pDBCnnI, aguint_id RelatedImageID, aguint_id ReplaceRelatedImageID, agbool bIsNorm)
{
	agtchar*	SQL=NULL;
	if(!bIsNorm)
		CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesAffinity SET RELATEDIMAGEID="),agtrue);
	else
		CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesNormAffinity SET RELATEDIMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ReplaceRelatedImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE RELATEDIMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);

	agbool bResult=CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;
	return bResult;
}

/*****************************************class CAGaffArray******************************/

CAGaffArray::CAGaffArray()
{
}
CAGaffArray::~CAGaffArray()
{
}
agfreal	CAGaffArray::aff(aguint_id mID, aguint_id nID, agbool throwErr)
{
	agint32 n=GetSize();
	AGAFFINITY_ITEM item={0,0,0,agfalse};
	agint32 i=0;
	for(i=0; i<n; i++)
	{
		item=GetAt(i);
		if(item.mID==mID && item.nID==nID)	break;
	}
	if(i==n)
	{
		if(throwErr)	throw _T("Error paramter");
		else			return 0;
	}
	return item.value;
}
agint32 CAGaffArray::LSearch(aguint_id mID, aguint_id nID, AGAFFINITY_ITEM* pFoundAffItem)
{
	agint32 n=GetSize();
	AGAFFINITY_ITEM item={0,0,0,agfalse};
	agint32 i=0;
	for(i=0; i<n; i++)
	{
		item=GetAt(i);
		if(item.mID==mID && item.nID==nID)	break;
	}
	if(i==n)
	{
		if(pFoundAffItem)	pFoundAffItem=NULL;
		return -1;
	}
	if(pFoundAffItem)		*pFoundAffItem=item;
	return i;
}
void CAGaffArray::DBInsertAt(agint32 idx, void* pDBCnnI)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	agtchar*	SQL=NULL;
	CAGimageAffVec::DBGetAffinityInsertSQL(SQL,m_vector[idx].mID,m_vector[idx].nID,m_vector[idx].value,m_vector[idx].bIsNorm);
	if(!CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse)) throw _T("Error Insert");
	if(SQL)	free(SQL);
}
void CAGaffArray::DBUpdateAt(agint32 idx, void* pDBCnnI)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	agtchar*	SQL=NULL;
	CAGimageAffVec::DBGetAffinityUpdateSQL(SQL,m_vector[idx].mID,m_vector[idx].nID,m_vector[idx].value,m_vector[idx].bIsNorm);
	if(!CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse)) throw _T("Error Insert");
	if(SQL)	free(SQL);
}
void CAGaffArray::DBInsert(void* pDBCnnI)
{
	agint32						n=GetSize();
	for(agint32 i=0; i<n; i++)	DBInsertAt(i,pDBCnnI);
}
void CAGaffArray::DBUpdate(void* pDBCnnI)
{
	agint32						n=GetSize();
	for(agint32 i=0; i<n; i++)	DBUpdateAt(i,pDBCnnI);
}

/************************class CAGimageHisto******************************/

int	CAGimageHisto::HISTO_ELEMENTCompareInc(const void* pHISTO_ELEMENT1, const void* pHISTO_ELEMENT2)
{
	HISTO_ELEMENT*	e1=(HISTO_ELEMENT*)pHISTO_ELEMENT1;
	HISTO_ELEMENT*	e2=(HISTO_ELEMENT*)pHISTO_ELEMENT2;
	agreal64 ret=(e1->value - e2->value);
	if(ret==0)			return 0;
	else if(ret < 0)	return -1;
	else 				return 1;
}
int	CAGimageHisto::HISTO_ELEMENTCompareDec(const void* pHISTO_ELEMENT1, const void* pHISTO_ELEMENT2)
{
	HISTO_ELEMENT*	e1=(HISTO_ELEMENT*)pHISTO_ELEMENT1;
	HISTO_ELEMENT*	e2=(HISTO_ELEMENT*)pHISTO_ELEMENT2;
	agreal64 ret=(e2->value - e1->value);
	if(ret==0)			return 0;
	else if(ret < 0)	return -1;
	else 				return 1;
}
CAGimageHisto::CAGimageHisto() : CAGbaseArray<HISTO_ELEMENT>()
{
	m_bIsNorm=agfalse;
}
CAGimageHisto::~CAGimageHisto()
{
}
void CAGimageHisto::SetNorm(agbool bIsNorm)
{
	m_bIsNorm=bIsNorm;
}
agbool CAGimageHisto::IsNorm()
{
	return m_bIsNorm;
}
agbool CAGimageHisto::CopyFrom(const CAGimageHisto* histo)
{
	if(!CAGbaseArray<HISTO_ELEMENT>::CopyFrom(histo)) return agfalse;
	m_bIsNorm=histo->m_bIsNorm;
	return agtrue;
}
void CAGimageHisto::SortInc()
{
	if(IsEmpty()) return;
	qsort((void*)m_vector ,(size_t)m_ne,sizeof(HISTO_ELEMENT),(agcmpfunc)HISTO_ELEMENTCompareInc);
}
void CAGimageHisto::SortDec()
{
	if(IsEmpty()) return;
	qsort((void*)m_vector ,(size_t)m_ne,sizeof(HISTO_ELEMENT),(agcmpfunc)HISTO_ELEMENTCompareDec);
}
agbool CAGimageHisto::Export(AGCLRQUAD*& clrs, agint32& ne)
{
	if(clrs)		free(clrs);
	clrs=NULL;		ne=0;
	if(IsEmpty())	return agfalse;
	ne=m_ne;
	clrs=(AGCLRQUAD*)malloc(sizeof(AGCLRQUAD)*ne);
	for(agint32 i=0; i<ne; i++) clrs[i]=m_vector[i].clr;
	return agtrue;
}
agbool CAGimageHisto::Export(agreal64*& values, agint32& ne)
{
	if(values)		free(values);
	values=NULL;	ne=0;
	if(IsEmpty())	return agfalse;
	ne=m_ne;
	values=(agreal64*)malloc(sizeof(agreal64)*ne);
	for(agint32 i=0; i<ne; i++) values[i]=m_vector[i].value;
	return agtrue;
}
agbool CAGimageHisto::Import(const AGCLRQUAD* clrs, const agreal64* values, const agint32 ne)
{
	if(clrs==NULL || values==NULL || ne<=0)	throw _T("Invalid parameter");
	SetSize(ne);
	for(agint32 i=0; i<ne; i++)
	{
		m_vector[i].clr=clrs[i];
		m_vector[i].value=values[i];
	}
	return agtrue;
}
