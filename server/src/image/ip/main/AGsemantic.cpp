#include "AGsemantic.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/***********************class CAGimageSemantic, class CAGimageSemanticInfo****************************/
agtchar	CAGimageSemantic::szSemanticTable[32]=				_T("Semantic");
agtchar	CAGimageSemantic::szSemanticInfoTable[32]=			_T("SemanticInfo");
agtchar	CAGimageSemantic::szImagesSemanticTable[32]=		_T("ImagesSemantic");
agtchar	CAGimageSemantic::szImagesSemanticWeightTable[32]=	_T("ImagesSemanticWeight");

CAGimageSemanticInfo::CAGimageSemanticInfo() : CAGmagicDBOrg()
{
	m_SemanticID=0;
	m_Descs=NULL;
}
CAGimageSemanticInfo::~CAGimageSemanticInfo()
{
}
void CAGimageSemanticInfo::Destroy()
{
	m_SemanticID=0;
	if(m_Descs) free(m_Descs); m_Descs=NULL;
}
void CAGimageSemanticInfo::Create(aguint_id SemanticID, agtchar* Descs)
{
	m_SemanticID=SemanticID;
	CAGmagicStrUtil::private_tcscat(m_Descs,Descs,agtrue);
}

agbool CAGimageSemanticInfo::CopyFrom(CAGimageSemanticInfo*	pSrc)
{
	if(pSrc==NULL)	throw _T("Invalid parameter");
	Destroy();

	m_SemanticID=pSrc->m_SemanticID;
	CAGmagicStrUtil::private_tcscat(m_Descs,pSrc->m_Descs,agtrue);

	DBCnnAttach(pSrc->m_pDBCnnI);
	return agtrue;
}
agbool CAGimageSemanticInfo::DBRead(aguint_id SemanticID)
{
	Destroy();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticInfoTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);
		if(SQL) free(SQL); SQL=NULL;
		if(pRs->EndOfFile)
		{
			pRs->Close();
			return agfalse;
		}

		//SemanticID
		_variant_t	varValue = pRs->Fields->GetItem(_T("SemanticID"))->Value;
		m_SemanticID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

		//Name
		varValue = pRs->Fields->GetItem(_T("Descs"))->Value;
		CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_Descs);

		pRs->Close();
	}
	catch(_com_error &e)
	{
		CAGmagicDBUtil::DisplayErrors(m_pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}

agbool CAGimageSemanticInfo::DBInsert()
{
	if(m_SemanticID==0) return agfalse;
	agtchar* SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticInfoTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(SemanticID, Descs) VALUES("),agtrue);
	
	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	if(m_Descs)
	{
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,m_Descs,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	}
	else
		CAGmagicStrUtil::private_tcscat(SQL,_T("NULL)"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

	if(SQL)  free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimageSemanticInfo::DBDelete()
{
	if(m_SemanticID==0) return agfalse;
	agtchar* SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticInfoTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

	if(SQL)  free(SQL); SQL=NULL;
	return agtrue;
}

CAGimageSemantic::CAGimageSemantic() : CAGmagicDBOrg()
{
	m_ID=0;
	m_Name=NULL;
	m_ParentID=0;
	m_ImageType=0;

	m_pInfo=NULL;
}
CAGimageSemantic::~CAGimageSemantic()
{
	Destroy();
}
void CAGimageSemantic::Destroy()
{
	m_ID=0;
	if(m_Name)	free(m_Name);	m_Name=NULL;
	m_ParentID=0;
	m_ImageType=0;
	
	if(m_pInfo) delete m_pInfo; m_pInfo=NULL;
}
void* CAGimageSemantic::DBCnnAttach(void* pDBCnnI)//khong AddRef, tra ve Connection cu doi ADO
{
	if(m_pInfo) m_pInfo->DBCnnAttach(pDBCnnI);
	return CAGmagicDBOrg::DBCnnAttach(pDBCnnI);
}
void* CAGimageSemantic::DBCnnDetach()//khong Release
{
	if(m_pInfo) m_pInfo->DBCnnDetach();
	return CAGmagicDBOrg::DBCnnDetach();
}
agbool CAGimageSemantic::CopyFrom(CAGimageSemantic*	pSrc)
{
	if(pSrc==NULL)	throw _T("Invalid parameter");
	Destroy();

	m_ID=pSrc->m_ID;
	CAGmagicStrUtil::private_tcscat(m_Name,pSrc->m_Name,agtrue);
	m_ParentID=pSrc->m_ParentID;
	m_ImageType=pSrc->m_ImageType;
	DBCnnAttach(pSrc->DBCnnGet());

	if(pSrc->m_pInfo)
	{
		m_pInfo=new CAGimageSemanticInfo();
		m_pInfo->CopyFrom(pSrc->m_pInfo);
	}
	return agtrue;
}
agbool	CAGimageSemantic::DBRead(agtchar SQL[], agbool bIsMoveLast)
{
	Destroy();

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenStatic, adLockReadOnly, adCmdText);
		if(pRs->EndOfFile)
		{
			pRs->Close();
			return agfalse;
		}
		if(bIsMoveLast) pRs->MoveLast();

		//ID
		_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
		m_ID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

		//Name
		varValue = pRs->Fields->GetItem(_T("Name"))->Value;
		CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_Name);

		//ParentID
		varValue = pRs->Fields->GetItem(_T("ParentID"))->Value;
		m_ParentID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
		
		//ImageType
		varValue = pRs->Fields->GetItem(_T("ImageType"))->Value;
		m_ImageType=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

		//SemanticInfo
		m_pInfo=new CAGimageSemanticInfo();
		m_pInfo->DBCnnAttach(m_pDBCnnI);
		m_pInfo->DBRead(m_ID);
		if(m_pInfo->m_SemanticID==0)
		{
			delete m_pInfo; m_pInfo=NULL;
		}
		pRs->Close();
	}
	catch(_com_error &e)
	{
		CAGmagicDBUtil::DisplayErrors(m_pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
	return agtrue;
}
agbool CAGimageSemantic::DBSemanticRead(aguint_id SemanticID)
{
	Destroy();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);

	agbool bResult=DBRead(SQL);

	if(SQL)	free(SQL);	SQL=NULL;
	return bResult;
}
agbool CAGimageSemantic::DBImageTypeTopLevelRead(aguint_id ImageType)
{
	Destroy();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageType="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND ParentID IS NULL"),agtrue);

	agbool bResult=DBRead(SQL);

	if(SQL)	free(SQL);	SQL=NULL;
	return bResult;
}
void CAGimageSemantic::Create(aguint_id ID, agtchar Name[], aguint_id ParentID, aguint_id ImageType, CAGimageSemanticInfo* pInfo)
{
	//khong duoc huy pInfo
	Destroy();
	m_ID=ID;
	CAGmagicStrUtil::private_tcscat(m_Name,Name,agtrue);
	m_ParentID=ParentID;
	m_ImageType=ImageType;

	//m_pInfo duong nhien = NULL
	m_pInfo=pInfo;
	if(m_pInfo)	m_pInfo->DBCnnAttach(m_pDBCnnI);
}
void CAGimageSemantic::Create(aguint_id ID, agtchar Name[], aguint_id ParentID, aguint_id ImageType, agtchar Descs[])
{
	Destroy();
	m_ID=ID;
	CAGmagicStrUtil::private_tcscat(m_Name,Name,agtrue);
	m_ParentID=ParentID;
	m_ImageType=ImageType;

	if(Descs)
	{
		m_pInfo=new CAGimageSemanticInfo();
		m_pInfo->Create(m_ID,Descs);
		m_pInfo->DBCnnAttach(m_pDBCnnI);
	}
}
agbool CAGimageSemantic::DBInsert(agbool bReRead)
{
	if(m_ImageType==0)	return agfalse;
	agtchar* SQL=NULL;
/////////////

	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(Name, ParentID, ImageType) VALUES("),agtrue);

	if(m_Name)
	{
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,m_Name,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}
	else
		CAGmagicStrUtil::private_tcscat(SQL,_T("NULL"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	if(m_ParentID!=0)
		CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentID,agtrue);
	else
		CAGmagicStrUtil::private_tcscat(SQL,_T("NULL"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageType,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL)  free(SQL); SQL=NULL;

/////////////
	if(bReRead)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,szSemanticTable,agtrue);
		if(m_Name)
		{
			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Name="),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,m_Name,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		}
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Name IS NULL"),agtrue);

		if(m_ParentID!=0)
		{
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND ParentID="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentID,agtrue);
		}
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND ParentID IS NULL"),agtrue);

		if(m_ImageType!=0)
		{
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND ImageType="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageType,agtrue);
		}
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND ImageType IS NULL"),agtrue);

		CAGimageSemanticInfo* bkInfo=NULL;
		if(m_pInfo)
		{
			bkInfo=new CAGimageSemanticInfo();
			bkInfo->CopyFrom(m_pInfo);
		}
		agbool bResult=DBRead(SQL,agtrue);
		if(bkInfo)
		{
			if(m_pInfo==NULL) m_pInfo=new CAGimageSemanticInfo();
			m_pInfo->CopyFrom(bkInfo);
			delete bkInfo;
		}

		if(SQL)	free(SQL);	SQL=NULL;
		if(!bResult || m_ID==0)	return agfalse;
	}

/////////////
	if(m_pInfo && m_ID)
	{
		m_pInfo->m_SemanticID=m_ID;
		m_pInfo->DBInsert();
	}
/////////////

	if(SQL)  free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimageSemantic::DBDelete()
{
	if(m_ID==0)	return agfalse;
	if(m_pInfo)	m_pInfo->DBDelete();

	agtchar* SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ID,agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

	if(SQL)  free(SQL); SQL=NULL;
	return agtrue;
}

void CAGimageSemantic::ExportXML(agtchar szFirstAlign[], agtchar*& xml)
{
	if(xml) free(xml); xml=NULL;

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<semantic>\n"),agtrue);

	agtchar* szFirstAlign2=NULL;
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,_T("  "),agtrue);

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign2,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<ID>"),agtrue);
	  CAGmagicStrUtil::private_tcscat_id(xml,m_ID,agtrue);
	CAGmagicStrUtil::private_tcscat(xml, _T("</ID>\n"),agtrue);

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign2,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<Name>"),agtrue);
	     CAGmagicStrUtil::private_tcscat(xml,m_Name,agtrue);
	CAGmagicStrUtil::private_tcscat(xml, _T("</Name>\n"),agtrue);

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign2,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<ParentID>"),agtrue);
	  CAGmagicStrUtil::private_tcscat_id(xml,m_ParentID,agtrue);
	CAGmagicStrUtil::private_tcscat(xml, _T("</ParentID>\n"),agtrue);

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign2,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<ImageType>"),agtrue);
	  CAGmagicStrUtil::private_tcscat_id(xml,m_ImageType,agtrue);
	CAGmagicStrUtil::private_tcscat(xml, _T("</ImageType>\n"),agtrue);

	if(szFirstAlign2)	free(szFirstAlign2);	szFirstAlign2=NULL;

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("</semantic>"),agtrue);
}

void CAGimageSemantic::DBUpdateSemanticOfImage(void* pDBCnnI, aguint_id ImageID, agint32 Threshold)
{
	if(pDBCnnI==NULL) throw _T("Invalid Parameter");

	//Tim tat ca cac Semantic cua ImageID
	CAGidArray SemanticIDs;
	CAGimages_Semantic::DBReadSemanticsFromImageID(pDBCnnI,ImageID,&SemanticIDs);
	agint32    n=SemanticIDs.GetSize();
	if(n==0)   return;

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" x WHERE x.ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND x.Weight="),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T("( SELECT MAX(y.Weight) FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" y WHERE y.ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" )"),agtrue);
	
	//Tim Semantic co trong so lon nhat cua ImageID
	CAGimages_SemanticWeight   max_sw;
	max_sw.DBCnnAttach(pDBCnnI);
	if(!max_sw.DBReadAndTest(SQL)) {free(SQL); return;}
	free(SQL);
	
	//Cap nhat Semantic lon nhat cua Image ID
	CAGimages_Semantic         max_is;
	max_is.DBCnnAttach(pDBCnnI);
	max_is.m_ImageID=ImageID;
	max_is.m_SemanticID=max_sw.m_SemanticID;
	max_is.DBInsertIntel();

	for(agint32 i=0; i<n; i++)
	{
		aguint_id							SemanticID=SemanticIDs.GetAt(i);
		if(SemanticID==max_is.m_SemanticID)	continue;

		//Tim trong so khac trong so max cua ImageID
		CAGimages_SemanticWeight	temp_sw;
		temp_sw.DBCnnAttach(pDBCnnI);
		if(!temp_sw.DBReadAndTest(ImageID,SemanticID))
			continue;
				
		//Neu trong so do nho hon trong so max 1 nguong thi di chuyen semantic do vao semantic max
		if( max_sw.m_Weight - temp_sw.m_Weight> Threshold)
		{
			CAGimages_Semantic         is;
			is.DBCnnAttach(pDBCnnI);
			is.m_ImageID=ImageID;
			is.m_SemanticID=SemanticID;
			is.DBMoveIntel(ImageID,max_sw.m_SemanticID);
		}
	}
}
void CAGimageSemantic::DBUpdateSemanticOfImages(void* pDBCnnI, aguint_id ImageType, agint32 Threshold)
{
	CAGimageIDs	ImageIDs;
	ImageIDs.DBCnnAttach(pDBCnnI);
	ImageIDs.DBRead(ImageType);
	agint32		n=ImageIDs.GetSize();
	for(agint32 i=0; i<n; i++)
		DBUpdateSemanticOfImage(pDBCnnI,ImageIDs.GetAt(i),Threshold);
}

/***********************class CAGimages_Semantic****************************/
CAGimages_Semantic::CAGimages_Semantic() : CAGmagicDBOrg()
{
	m_ImageID=0;
	m_SemanticID=0;
}
CAGimages_Semantic::~CAGimages_Semantic()
{
}
void CAGimages_Semantic::Reset()
{
	m_ImageID=0;
	m_SemanticID=0;
}
agbool CAGimages_Semantic::DBReadAndTest(agtchar SQL[])
{
	Reset();

	aguint_id*	data=NULL;
	agint32		fieldsNum=0;
	agbool		bIsSuccess=agtrue;
	bIsSuccess &=AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum);

	if(data)
	{
		if(fieldsNum!=2) throw _T("Fatal Error");
		m_ImageID=data[0];
		m_SemanticID=data[1];

		free(data); data=NULL;
		bIsSuccess &=agtrue;
	}
	else bIsSuccess &=agfalse;

	return bIsSuccess;
}
agbool CAGimages_Semantic::DBReadAndTest(aguint_id ImageID, aguint_id SemanticID)
{
	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);

	agbool  bIsSuccess=DBReadAndTest(SQL);
	if(SQL) free(SQL); SQL=NULL;

	return bIsSuccess;
}
agbool CAGimages_Semantic::DBInsert()
{
	if(m_ImageID==0 || m_SemanticID==0)	return agfalse;
	
	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(ImageID, SemanticID) VALUES("),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimages_Semantic::DBInsertIntel()
{
	if(!DBReadAndTest(m_ImageID,m_SemanticID))
		return DBInsert();
	return agfalse;
}

agbool CAGimages_Semantic::DBDelete()
{
	if(m_ImageID==0 || m_SemanticID==0)	return agfalse;
	
	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);


	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimages_Semantic::DBMove(aguint_id NewImageID, aguint_id NewSemanticID)
{
	DBDelete();
	m_ImageID=NewImageID;
	m_SemanticID=NewSemanticID;
	return DBInsert();
}
agbool CAGimages_Semantic::DBMoveIntel(aguint_id NewImageID, aguint_id NewSemanticID)
{
	if(!DBReadAndTest(m_ImageID,m_SemanticID)) return DBInsert();
	return DBMove(NewImageID,NewSemanticID);
}

void CAGimages_Semantic::DBReadImageIDsFromSemantic(void* pDBCnnI, aguint_id SemanticID, CAGimageIDs* pOutImageIDs)
{
	if(pDBCnnI==NULL || pOutImageIDs==NULL) throw _T("Invalid parameter");
	pOutImageIDs->RemoveAll();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ImageID FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);

	aguint_id*	data=NULL;
	agint32		n=0;
	AGdbReadOneField(pDBCnnI, SQL, 0, agfalse, data, n);
	if(data==NULL) {free(SQL); return;}
	pOutImageIDs->Import(data,n);

	if(SQL) free(SQL); SQL=NULL;
	if(data) free(data); data=NULL;
}
void CAGimages_Semantic::DBReadImageIDsFromSemanticEx(void* pDBCnnI, aguint_id SemanticID, CAGimageIDs* pOutImageIDs)
{
	CAGimageIDs TempOutImageIDs;
	DBReadImageIDsFromSemantic(pDBCnnI, SemanticID, &TempOutImageIDs);
	pOutImageIDs->Append(&TempOutImageIDs);

	CAGobjPtrArray<CAGimageSemantic> Semantics;
	CAGimageSemanticTree::DBReadSemanticsFromParentID(pDBCnnI, SemanticID, &Semantics);
	agint32 n=Semantics.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemantic* pSemantic=Semantics.GetAt(i);
		if(pSemantic==NULL) continue;
		DBReadImageIDsFromSemanticEx(pDBCnnI, pSemantic->m_ID, pOutImageIDs);
	}
}
void CAGimages_Semantic::DBReadSemanticsFromImageID(void* pDBCnnI, aguint_id ImageID, CAGidArray* pOutSemanticIDs)
{
	if(pDBCnnI==NULL || pOutSemanticIDs==NULL) throw _T("Invalid parameter");
	pOutSemanticIDs->RemoveAll();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT SemanticID FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	aguint_id*	data=NULL;
	agint32		n=0;
	AGdbReadOneField(pDBCnnI, SQL, 0, agfalse, data, n);
	if(data==NULL) {free(SQL); return;}
	pOutSemanticIDs->Import(data,n);

	if(SQL)		free(SQL); SQL=NULL;
	if(data)	free(data); data=NULL;
}

CAGimages_SemanticWeight::CAGimages_SemanticWeight() : CAGmagicDBOrg()
{
	m_ImageID=0;
	m_SemanticID=0;
	m_Weight=0;
}
CAGimages_SemanticWeight::~CAGimages_SemanticWeight()
{
}

void CAGimages_SemanticWeight::Reset()
{
	m_ImageID=0;
	m_SemanticID=0;
	m_Weight=0;
}

agbool CAGimages_SemanticWeight::DBReadAndTest(agtchar SQL[])
{
	Reset();

	agreal64*	data=NULL;
	agint32		fieldsNum=0;
	agbool		bIsSuccess=agtrue;
	bIsSuccess &=AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum);

	if(data)
	{
		if(fieldsNum!=3) throw _T("Fatal Error");
		m_ImageID=(aguint_id)data[0];
		m_SemanticID=(aguint_id)data[1];
		m_Weight=data[2];

		free(data); data=NULL;
		bIsSuccess &=agtrue;
	}
	else bIsSuccess &=agfalse;

	return bIsSuccess;
}
agbool CAGimages_SemanticWeight::DBReadAndTest(aguint_id ImageID, aguint_id SemanticID)
{

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);

	agbool  bIsSuccess=DBReadAndTest(SQL);
	if(SQL) free(SQL); SQL=NULL;

	return bIsSuccess;
}

agbool CAGimages_SemanticWeight::DBInsert()
{
	if(m_ImageID==0 || m_SemanticID==0)	return agfalse;
	
	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(ImageID, SemanticID, Weight) VALUES("),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_Weight,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}

agbool CAGimages_SemanticWeight::DBUpdate()
{
	if(m_ImageID==0 || m_SemanticID==0)	return agfalse;
	
	agtchar*	SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" SET Weight="),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,m_Weight,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND SemanticID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_SemanticID,agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimages_SemanticWeight::DBUpdateIntel()
{
	CAGimages_SemanticWeight sw;
	sw.DBCnnAttach(m_pDBCnnI);
	agbool bRead=sw.DBReadAndTest(m_ImageID,m_SemanticID);

	if(!bRead)	DBInsert();
	else
	{
		m_Weight=sw.m_Weight;
		DBUpdate();
	}

	return agtrue;
}
agbool CAGimages_SemanticWeight::DBUpdateIntelAccum(agreal64 accum_weight)
{
	CAGimages_SemanticWeight sw;
	sw.DBCnnAttach(m_pDBCnnI);
	agbool bRead=sw.DBReadAndTest(m_ImageID,m_SemanticID);

	if(!bRead)
	{
		m_Weight=accum_weight;
		DBInsert();
	}
	else
	{
		m_Weight=sw.m_Weight + accum_weight;
		DBUpdate();
	}

	return agtrue;
}

/***********************class CAGimageSemanticNodeData, CAGimageSemanticNode****************************/

CAGimageSemanticNodeData::CAGimageSemanticNodeData()
{
	m_pSemantic=NULL;
	m_pImageIDs=NULL;
	m_weight=0;
}
CAGimageSemanticNodeData::~CAGimageSemanticNodeData()
{
	Destroy();
}
void CAGimageSemanticNodeData::Destroy()
{
	if(m_pSemantic)	delete m_pSemantic;	m_pSemantic=NULL;
	if(m_pImageIDs)	delete m_pImageIDs;	m_pImageIDs=NULL;
	m_weight=0;
}
agbool CAGimageSemanticNodeData::CopyFrom(CAGimageSemanticNodeData*	pSrc)
{
	if(pSrc==NULL)	throw _T("Invalid parameter");
	Destroy();
	
	if(pSrc->m_pSemantic)
	{
		m_pSemantic=new CAGimageSemantic();
		m_pSemantic->CopyFrom(pSrc->m_pSemantic);
	}
	if(pSrc->m_pImageIDs)
	{
		m_pImageIDs=new CAGimageIDs();
		m_pImageIDs->CopyFrom(pSrc->m_pImageIDs);
	}
	m_weight=pSrc->m_weight;
	return agtrue;
}
void CAGimageSemanticNodeData::ExportXML(agtchar szFirstAlign[], agtchar*& xml)
{
	if(xml) free(xml); xml=NULL;

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<nodedata>\n"),agtrue);

	agtchar* szFirstAlign2=NULL;
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,_T("  "),agtrue);
	if(m_pSemantic)
	{
		agtchar* semantic_xml=NULL;

		m_pSemantic->ExportXML(szFirstAlign2,semantic_xml);
		CAGmagicStrUtil::private_tcscat(xml,semantic_xml,agtrue);
		CAGmagicStrUtil::private_tcscat(xml,_T("\n"),agtrue);

		if(semantic_xml)	free(semantic_xml);		semantic_xml=NULL;
	}
	if(m_pImageIDs)
	{
		CAGmagicStrUtil::private_tcscat(xml,szFirstAlign2,agtrue);
		CAGmagicStrUtil::private_tcscat(xml,_T("<ids>"),agtrue);

		CAGreal64Array	IDs;
		agint32			n=m_pImageIDs->GetSize();
		IDs.SetSize(n);
		for(agint32 i=0; i<n; i++) IDs.SetAt(i,(agreal64)(agint64)m_pImageIDs->GetAt(i));

		agtchar*		szIDs=NULL;
		IDs.ToString(szIDs);
		CAGmagicStrUtil::private_tcscat(xml,szIDs,agtrue);
		if(szIDs) free(szIDs); szIDs=NULL;

		CAGmagicStrUtil::private_tcscat(xml,_T("</ids>\n"),agtrue);

	}
	if(szFirstAlign2)	free(szFirstAlign2);	szFirstAlign2=NULL;

	CAGmagicStrUtil::private_tcscat(xml,szFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("</nodedata>"),agtrue);

}

CAGimageSemanticNode::CAGimageSemanticNode()
{
	m_pData=NULL;
	m_pParent=NULL;
	m_pChilds=CreateChilds();//m_pChilds luon luon phai khac NULL
}
CAGimageSemanticNode::~CAGimageSemanticNode()
{
	if(m_pData)		delete m_pData;	m_pData=NULL;

	m_pParent=NULL;
	if(m_pChilds)	delete m_pChilds;	m_pChilds=NULL;
}
CAGobjPtrArray<CAGimageSemanticNode>* CAGimageSemanticNode::CreateChilds()
{
	return new CAGobjPtrArray<CAGimageSemanticNode>();
}
CAGimageSemantic* CAGimageSemanticNode::GetSemantic()
{
	if(m_pData==NULL)	return NULL;
	return	m_pData->m_pSemantic;
}
CAGimageIDs* CAGimageSemanticNode::GetIDs()
{
	if(m_pData==NULL)	return NULL;
	return	m_pData->m_pImageIDs;
}
agbool CAGimageSemanticNode::IsHaveChilds()
{
	return (m_pChilds->GetSize()>0);
}
agbool CAGimageSemanticNode::IsHaveIDs()
{
	CAGimageIDs* pFirstNodeIDs=GetIDs();
	if(pFirstNodeIDs==NULL)			return agfalse;
	if(pFirstNodeIDs->GetSize()==0)	return agfalse;
	return agtrue;
}
agreal64 CAGimageSemanticNode::GetWeight()
{
	if(m_pData==NULL)	return 0;
	return m_pData->m_weight;
}
agbool CAGimageSemanticNode::SetWeight(agreal64 weight)
{
	if(m_pData==NULL)	return agfalse;
	m_pData->m_weight=weight;
	return agtrue;
}

void CAGimageSemanticNode::ExportXML(agtchar* szAutoFreeFirstAlign, agtchar*& xml)
{
	CAGmagicStrUtil::private_tcscat(xml,szAutoFreeFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("<node>\n"),agtrue);

	agtchar* szFirstAlign2=NULL;
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,szAutoFreeFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(szFirstAlign2,_T("  "),agtrue);

	if(m_pData)
	{
		agtchar* data_xml=NULL;
		m_pData->ExportXML(szFirstAlign2,data_xml);
		CAGmagicStrUtil::private_tcscat(xml,data_xml,agtrue);
		CAGmagicStrUtil::private_tcscat(xml,_T("\n"),agtrue);
		if(data_xml) free(data_xml); data_xml=NULL;

		agint32 n=m_pChilds->GetSize();
		for(agint32 i=0; i<n; i++)
		{
			agtchar* szAutoFreeFirstAlign2=NULL;
			CAGmagicStrUtil::private_tcscat(szAutoFreeFirstAlign2,szAutoFreeFirstAlign,agtrue);
			CAGmagicStrUtil::private_tcscat(szAutoFreeFirstAlign2,_T("  "),agtrue);

			m_pChilds->GetAt(i)->ExportXML(szAutoFreeFirstAlign2,xml);
		}
	}

	if(szFirstAlign2)	free(szFirstAlign2);	szFirstAlign2=NULL;

	CAGmagicStrUtil::private_tcscat(xml,szAutoFreeFirstAlign,agtrue);
	CAGmagicStrUtil::private_tcscat(xml,_T("</node>\n"),agtrue);
	if(szAutoFreeFirstAlign)	free(szAutoFreeFirstAlign);	szAutoFreeFirstAlign=NULL;
}
agbool CAGimageSemanticNode::CopyFrom(CAGimageSemanticNode* pSrc)
{
	if(pSrc==NULL) throw _T("Invalid parameter");

	if(m_pData)		delete m_pData;
	if(pSrc->m_pData)
	{
		m_pData=new CAGimageSemanticNodeData();
		m_pData->CopyFrom(pSrc->m_pData);
	}

	if(m_pChilds)	delete m_pChilds;				m_pChilds=CreateChilds();
	agint32			n=pSrc->m_pChilds->GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemanticNode* pSrcChildNode=pSrc->m_pChilds->GetAt(i);
		CAGimageSemanticNode* pChildNode=new CAGimageSemanticNode();
		pChildNode->m_pParent=this;

		pChildNode->CopyFrom(pSrcChildNode);
		m_pChilds->Add(pChildNode);
	}

	return agtrue;
}
void CAGimageSemanticNode::DBUpdateSemanticWeight(void* pDBCnnI, aguint_id ImageID, agbool bIsReset)
{
	CAGimageSemantic*	pSemantic=GetSemantic();
	agreal64			weight=GetWeight();
	if(bIsReset)		SetWeight(0);

	if(pSemantic==NULL || weight==0 || ImageID==0) return;
	CAGimages_SemanticWeight sw;
	sw.DBCnnAttach(pDBCnnI);
	sw.m_ImageID=ImageID;
	sw.m_SemanticID=pSemantic->m_ID;
	sw.DBUpdateIntelAccum(weight);

	agint32 n=m_pChilds->GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemanticNode* pNode=m_pChilds->GetAt(i);
		if(pNode) pNode->DBUpdateSemanticWeight(pDBCnnI,ImageID,bIsReset);
	}
}
void CAGimageSemanticNode::GetTotalWeightAndNode(agreal64& sum_weight, aguint32& sum_node)
{
	sum_weight +=GetWeight();
	sum_node ++;

	agint32 n=m_pChilds->GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemanticNode* pNode=m_pChilds->GetAt(i);
		if(pNode) pNode->GetTotalWeightAndNode(sum_weight, sum_node);
	}
}

/***********************class CAGimageSemanticNodes****************************/

CAGimageSemanticNodes::CAGimageSemanticNodes()
{
}
CAGimageSemanticNodes::~CAGimageSemanticNodes()
{
}

/***********************class CAGimageSemanticTree****************************/

CAGimageSemanticTree::CAGimageSemanticTree() : CAGmagicDBOrg()
{
	m_pRoot=NULL;
}
CAGimageSemanticTree::~CAGimageSemanticTree()
{
	Destroy();
}
void CAGimageSemanticTree::Destroy()
{
	if(m_pRoot)	delete m_pRoot;	m_pRoot=NULL;
}
aguint_id CAGimageSemanticTree::GetImageType()
{
	if(m_pRoot==NULL)	return 0;
	CAGimageSemantic*	pSemantic=m_pRoot->GetSemantic();
	if(pSemantic==NULL)	return 0;

	return pSemantic->m_ImageType;
}
CAGimageSemanticNode* CAGimageSemanticTree::newNode(agbool bIsNewSemantic, void* pDBCnnI, agbool bIsNewImageIDs)
{
	CAGimageSemanticNode* pNode=new CAGimageSemanticNode();
	pNode->m_pData=new CAGimageSemanticNodeData();
	if(bIsNewSemantic)
	{
		pNode->m_pData->m_pSemantic=new CAGimageSemantic();
		pNode->m_pData->m_pSemantic->DBCnnAttach(pDBCnnI);
	}
	if(bIsNewImageIDs)
		pNode->m_pData->m_pImageIDs=new CAGimageIDs();

	return pNode;
}
CAGimageSemanticNode* CAGimageSemanticTree::newNode(CAGimageSemantic* pSemantic)
{
	//pSemantic phai duoc cap phat new tu heap
	//Sau khi su dung ham nay khong duoc huy pSemantic

	CAGimageSemanticNode* pNode=new CAGimageSemanticNode();
	pNode->m_pData=new CAGimageSemanticNodeData();
	pNode->m_pData->m_pSemantic=pSemantic;

	return pNode;
}
agbool CAGimageSemanticTree::InsertNode(CAGimageSemanticNode* pParentNode, CAGimageSemanticNode* pNode)
{
	if(pParentNode==NULL || pNode==NULL)	throw _T("Invalid parameter");
	//pNode phai duoc cap phat new tu heap
	//Sau khi su dung ham nay khong duoc huy pNode

	pParentNode->m_pChilds->Add(pNode);
	pNode->m_pParent=pParentNode;
	return agtrue;
}
CAGimageSemanticNode* CAGimageSemanticTree::InsertSemantic(CAGimageSemanticNode* pParentNode, CAGimageSemantic* pSemantic)
{
	if(pParentNode==NULL || pSemantic==NULL)	throw _T("Invalid parameter");
	//pSemantic phai duoc cap phat new tu heap
	//Sau khi su dung ham nay khong duoc huy pSemantic
	
	CAGimageSemanticNode*	pNode=newNode(pSemantic);
	if(InsertNode(pParentNode,pNode))	return pNode;
	else								return NULL;
}

CAGimageSemanticNode* CAGimageSemanticTree::InsertImageID(aguint_id ImageID, aguint_id	SemanticID)
{
	if(m_pRoot==NULL)			return NULL;
	CAGimageSemanticNode*		pNode=FindNode(SemanticID);
	if(pNode==NULL)				return NULL;
	if(pNode->m_pData==NULL)	throw _T("Fatal Error");

	if(pNode->m_pData->m_pImageIDs==NULL)
	{
		pNode->m_pData->m_pImageIDs=new CAGimageIDs();
		pNode->m_pData->m_pImageIDs->DBCnnAttach(m_pDBCnnI);
	}
	pNode->m_pData->m_pImageIDs->Add(ImageID);

	return pNode;
}

CAGimageSemanticNode* CAGimageSemanticTree::FindNode(CAGimageSemanticNode* pFirstNode, aguint_id SemanticID)
{
	if(pFirstNode==NULL)	return NULL;
	CAGimageSemantic*		pSemantic=pFirstNode->GetSemantic();
	if(pSemantic==NULL)		return NULL;

	if(pSemantic->m_ID==SemanticID)	return pFirstNode;

	agint32		n=pFirstNode->m_pChilds->GetSize();
	if(n==0)	return NULL;
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemanticNode*	pNode=pFirstNode->m_pChilds->GetAt(i);
		CAGimageSemanticNode*	pFoundNode=FindNode(pNode,SemanticID);
		if(pFoundNode!=NULL)	return pFoundNode;
	}
	return NULL;
}
void CAGimageSemanticTree::DBReadSemantics(void* pDBCnnI, agtchar SQL[], CAGobjPtrArray<CAGimageSemantic>* pSemantics)
{
	if(SQL==NULL || pSemantics==NULL)	throw _T("Invalid Parameter");
	pSemantics->RemoveAll();

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agint32 count=0;
		while(!(pRs->EndOfFile))
        {
			CAGimageSemantic*	pSemantic=new CAGimageSemantic();
			pSemantic->DBCnnAttach(pDBCnnI);

			//ID
			_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
			pSemantic->m_ID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
	
			//Name
			varValue = pRs->Fields->GetItem(_T("Name"))->Value;
			CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,pSemantic->m_Name);

			//ParentID
			varValue = pRs->Fields->GetItem(_T("ParentID"))->Value;
			pSemantic->m_ParentID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
			
			//ImageType
			varValue = pRs->Fields->GetItem(_T("ImageType"))->Value;
			pSemantic->m_ImageType=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

			pSemantics->Add(pSemantic);
			pRs->MoveNext();
			count++;
		}
		pRs->Close();
	}
	catch(_com_error &e)
	{
		CAGmagicDBUtil::DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
}

void CAGimageSemanticTree::DBReadTopLevelSemantics(void* pDBCnnI, CAGobjPtrArray<CAGimageSemantic>* pTopLevelSemantics)
{
	agtchar SQL[1024];
	_tcscpy(SQL,_T("SELECT * FROM "));
	_tcscat(SQL,CAGimageSemantic::szSemanticTable);
	_tcscat(SQL,_T(" WHERE ImageType<>NULL"));

	DBReadSemantics(pDBCnnI, SQL, pTopLevelSemantics);

	agint32	n=pTopLevelSemantics->GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemantic* pSemantic=pTopLevelSemantics->GetAt(i);
		if(pSemantic->m_ParentID!=0)	throw _T("Fatal Database Error");
	}
}
void CAGimageSemanticTree::DBReadSemanticsFromParentID(void* pDBCnnI, aguint_id ParentID, CAGobjPtrArray<CAGimageSemantic>* pSemantics)
{
	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ParentID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ParentID,agtrue);

	DBReadSemantics(pDBCnnI, SQL, pSemantics);
	if(SQL)	free(SQL);	SQL=NULL;

	agint32	n=pSemantics->GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemantic* pSemantic=pSemantics->GetAt(i);
		if(pSemantic->m_ParentID==0)	throw _T("Fatal Database Error");
	}
}

CAGimageSemanticNode* CAGimageSemanticTree::FindNode(aguint_id SemanticID)
{
	return FindNode(m_pRoot,SemanticID);
}

void CAGimageSemanticTree::DBBuild(CAGimageSemanticNode* pFirstNode)
{
	if(pFirstNode==NULL || pFirstNode->GetSemantic()==NULL)	throw _T("Invalid parameter");
	
	CAGobjPtrArray<CAGimageSemantic>	Semantics;
	DBReadSemanticsFromParentID(m_pDBCnnI, pFirstNode->GetSemantic()->m_ID,&Semantics);

	agint32		n=Semantics.GetSize();
	if(n==0)	return;
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemanticNode*	pNode=InsertSemantic(pFirstNode,Semantics.GetAt(i));
		if(pNode)
		{
			DBBuild(pNode);
			Semantics.SetNULLAt(i);//de tranh bi huy
		}
	}
}

void CAGimageSemanticTree::DBBuild(aguint_id ImageType, agbool bIsInsertImageIDs)
{
	Destroy();

	//Tao nut goc dau tien
	CAGimageSemanticNode* pNode=newNode(agtrue,m_pDBCnnI,agfalse);
	if(!pNode->m_pData->m_pSemantic->DBImageTypeTopLevelRead(ImageType))
	{
		delete pNode;	pNode=NULL;
		return;
	}
	if(pNode->m_pData->m_pSemantic->m_ID==0 || pNode->m_pData->m_pSemantic->m_ImageType==0)
	{
		delete pNode;	pNode=NULL;
		return;
	}
	m_pRoot=pNode;//tao nut goc dau tien

	//Goi de quy
	DBBuild(m_pRoot);
	if(bIsInsertImageIDs)
	{
		agtchar*		SQL=NULL;
		aguint_id**		data=NULL;
		agint32			fieldsNum=0;
		agint32			recordsNum=0;

		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ImageID, SemanticID FROM "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(".ID="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(".ImageID"),agtrue);
		
		CAGmagicStrUtil::private_tcscat(SQL,_T(" AND Type="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);

		if(!AGdbRead(m_pDBCnnI, SQL, agfalse, data, fieldsNum, recordsNum))
			return;
		if(fieldsNum!=2)	throw _T("Fatal database error");

		for(agint32 i=0; i<recordsNum; i++)
			InsertImageID(data[i][0],data[i][1]);

		if(data)
		{
			for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
			free(data);
			data=NULL;
		}
		if(SQL)	free(SQL);	SQL=NULL;
	}
}
void CAGimageSemanticTree::Traverse(CAGimageSemanticNode* pFirstNode, void (*DoTask)(CAGimageSemanticNode* pNode, void* pReserved1, void* pReserved2), void* pReserved1, void* pReserved2)
{
	if(pFirstNode==NULL) return;
	DoTask(pFirstNode,pReserved1,pReserved2);
	if(pFirstNode->m_pChilds)
	{
		agint32 n=pFirstNode->m_pChilds->GetSize();
		for(agint32 i=0; i<n; i++)
			Traverse(pFirstNode->m_pChilds->GetAt(i),DoTask,pReserved1,pReserved2);
	}
}
void CAGimageSemanticTree::DBDeleteSemanticsRecure(void* pDBCnnI, aguint_id SemanticID)
{
	CAGobjPtrArray<CAGimageSemantic> Semantics;
	DBReadSemanticsFromParentID(pDBCnnI, SemanticID, &Semantics);

	agint32 n=Semantics.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemantic* pSemantic=Semantics.GetAt(i);
		if(pSemantic==NULL) continue;
		DBDeleteSemanticsRecure(pDBCnnI, pSemantic->m_ID);

	}

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGimageSemantic::szSemanticTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,SemanticID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
}
void CAGimageSemanticTree::DBDeleteSemanticsRecure(void* pDBCnnI)
{
	agtchar SQL[1024];
	_tcscpy(SQL,_T("SELECT * FROM "));
	_tcscat(SQL,CAGimageSemantic::szSemanticTable);

	CAGobjPtrArray<CAGimageSemantic> Semantics;
	DBReadSemantics(pDBCnnI, SQL, &Semantics);

	agint32 n=Semantics.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSemantic* pSemantic=Semantics.GetAt(i);
		if(pSemantic==NULL) continue;
		DBDeleteSemanticsRecure(pDBCnnI, pSemantic->m_ID);
	}
}
void CAGimageSemanticTree::DBResetAndInsertSampleTopLevelSemantics(void* pDBCnnI)
{
	agtchar SQL[1024];

	_tcscpy(SQL,_T("DELETE FROM "));
	_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);

	_tcscpy(SQL,_T("DELETE FROM "));
	_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);

	_tcscpy(SQL,_T("DELETE FROM "));
	_tcscat(SQL,CAGimageSemantic::szSemanticInfoTable);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);

	DBDeleteSemanticsRecure(pDBCnnI);

	CAGimageDBItemTypes item_types;
	item_types.DBCnnAttach(pDBCnnI);
	item_types.DBReadAll();

	agint32		n=item_types.GetSize();
	if(n==0)	return;
	for(agint32 i=0; i<n; i++)
	{
		CAGimageDBItemType* item_type=item_types.GetAt(i);

		CAGimageSemantic semantic;
		semantic.DBCnnAttach(pDBCnnI);
		semantic.Create(0,item_type->m_Name,0,item_type->m_ID,item_type->m_Name);
		semantic.DBInsert(agtrue);

		if(item_type->m_ID==1)//animal
		{
			agtchar* szChildSemanticName[] =
				{
					_T("doc"),
					_T("cat"),
					_T("eagle"),
				};
			for(agint32 i=0; i<3; i++)
			{
				CAGimageSemantic child_semantic;
				child_semantic.DBCnnAttach(pDBCnnI);
				child_semantic.Create(0,szChildSemanticName[i],semantic.m_ID,item_type->m_ID,szChildSemanticName[i]);
				child_semantic.DBInsert(agtrue);
			}
		}
		else if(item_type->m_ID==5)//flower-spec
		{
			agtchar* szChildSemanticName[] =
				{
					_T("cacti"),
					_T("orchid"),
					_T("rose"),
					_T("tulip")
				};
			for(agint32 i=0; i<4; i++)
			{
				CAGimageSemantic child_semantic;
				child_semantic.DBCnnAttach(pDBCnnI);
				child_semantic.Create(0,szChildSemanticName[i],semantic.m_ID,item_type->m_ID,szChildSemanticName[i]);
				child_semantic.DBInsert(agtrue);
			}
		}
	}
}
void CAGimageSemanticTree::DBResetAndInsertSampleTopLevelImageIDs(void* pDBCnnI)
{
	agtchar SQL[1024];

	_tcscpy(SQL,_T("DELETE FROM "));
	_tcscat(SQL,CAGimageSemantic::szImagesSemanticTable);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);

	_tcscpy(SQL,_T("DELETE FROM "));
	_tcscat(SQL,CAGimageSemantic::szImagesSemanticWeightTable);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);

	_tcscpy(SQL,_T("SELECT * FROM "));
	_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable);
	CAGimageDBItems	items;
	items.DBCnnAttach(pDBCnnI);
	items.DBRead(SQL,agtrue);

	agint32 n=items.GetSize();
	if(n==0) return;
	for(agint32 i=0; i<n; i++)
	{
		CAGimageDBItem* item=items.GetAt(i);
		if(item->m_ImageID==0 || item->m_ImageType==0) continue;

		CAGimageSemantic semantic;
		semantic.DBCnnAttach(pDBCnnI);
		semantic.DBImageTypeTopLevelRead(item->m_ImageType);
		if(semantic.m_ID==0 || semantic.m_ParentID!=0) continue;

		CAGimages_Semantic images_semantic;
		images_semantic.DBCnnAttach(pDBCnnI);
		images_semantic.m_ImageID=item->m_ImageID;
		images_semantic.m_SemanticID=semantic.m_ID;

		agtchar* idx=_tcsrchr(item->m_URL,AGMAGIC_DIR_SPLASH);//ten file anh
		if(item->m_ImageType==5/*flower-spec*/ &&   idx!=NULL && idx+1!=NULL)
		{
			CAGobjPtrArray<CAGimageSemantic> Spec_Semantics;
			DBReadSemanticsFromParentID(pDBCnnI, semantic.m_ID, &Spec_Semantics);
			agint32 n=Spec_Semantics.GetSize();
			for(agint32 i=0; i<n; i++)
			{
				CAGimageSemantic*	pSemantic=Spec_Semantics.GetAt(i);
				if(pSemantic==NULL)		continue;
				if(pSemantic->m_ID==0)	continue;
				
				agtchar file_name[1024];
				agtchar semantic_name[1024];
				_tcscpy(file_name,idx+1);
				_tcscpy(semantic_name,pSemantic->m_Name);
				if(_tcsstr(file_name,semantic_name))
				{
					images_semantic.m_SemanticID=pSemantic->m_ID;
					break;
				}
			}
		}
		images_semantic.DBInsert();

		CAGimages_SemanticWeight images_semantic_weight;
		images_semantic_weight.DBCnnAttach(pDBCnnI);
		images_semantic_weight.m_ImageID=item->m_ImageID;
		images_semantic_weight.m_SemanticID=semantic.m_ID;
		images_semantic_weight.m_Weight=1;
		images_semantic_weight.DBInsert();
	}
}
void CAGimageSemanticTree::ExportXML(agtchar*& xml)
{
	if(xml) free(xml); xml=NULL;
	if(m_pRoot==NULL)	return;
	m_pRoot->ExportXML(NULL,xml);
}
void CAGimageSemanticTree::OutputXML(CAGoutputConsole* pConsole)
{
	if(pConsole==NULL)	return;

	agtchar* xml=NULL;
	ExportXML(xml);
	if(xml)
	{
		pConsole->Out(xml);
		if(xml)	free(xml);	xml=NULL;
	}
}
void CAGimageSemanticTree::OutputXML(agtchar szFilePath[])
{
	CAGoutputConsole console;
	console.Attach(szFilePath);

	OutputXML(&console);
}
agbool CAGimageSemanticTree::CopyFrom(CAGimageSemanticTree*	pSrcTree)
{
	if(pSrcTree==NULL) throw _T("Invalid parameter");
	Destroy();
	DBCnnAttach(pSrcTree->DBCnnGet());
	if(pSrcTree->m_pRoot==NULL) return agtrue;

	m_pRoot=new CAGimageSemanticNode();
	return m_pRoot->CopyFrom(pSrcTree->m_pRoot);
}
agbool CAGimageSemanticTree::IsEmpty()
{
	return (m_pRoot==NULL);
}

void CAGimageSemanticTree::CollectSemanticIDs(CAGimageSemanticNode* pFirstNode, void* pDBCnnI, agbool bIsShrinkTree, CAGimageIDs* pOutImageIDs)
{
	if(pFirstNode==NULL || pDBCnnI==NULL || pOutImageIDs==NULL) return;
	if(pFirstNode->GetSemantic()==NULL) return;


	if(!pFirstNode->IsHaveChilds())
	{
		CAGimageIDs FirstNodeIDs;
		CAGimages_Semantic::DBReadImageIDsFromSemanticEx(pDBCnnI,pFirstNode->GetSemantic()->m_ID,&FirstNodeIDs);
		pOutImageIDs->Append(&FirstNodeIDs);
		return;
	}

	CAGimageIDs UnionChildImageIDs;
	agint32		count=0;
	for(agint32 i=0; i<pFirstNode->m_pChilds->GetSize(); i++)
	{
		CAGimageIDs iImageIDs;
		CollectSemanticIDs(pFirstNode->m_pChilds->GetAt(i),pDBCnnI,bIsShrinkTree,&iImageIDs);
		if(iImageIDs.GetSize()==0)
		{
			if(bIsShrinkTree)
			{
				pFirstNode->m_pChilds->RemoveAt(i);
				i--;
			}
		}
		else
		{
			UnionChildImageIDs.Append(&iImageIDs);
			count ++;
		}
	}
	pOutImageIDs->Append(&UnionChildImageIDs);

}
void CAGimageSemanticTree::CollectSemanticIDs(agbool bIsShrinkTree, CAGimageIDs* pOutImageIDs)
{
	if(pOutImageIDs==NULL) throw _T("Invalid parameter");
	pOutImageIDs->RemoveAll();
	if(m_pRoot==NULL) return;

	CollectSemanticIDs(m_pRoot, m_pDBCnnI, bIsShrinkTree, pOutImageIDs);
	if(bIsShrinkTree && pOutImageIDs->GetSize()==0)
	{
		delete m_pRoot;
		m_pRoot=NULL;
	}

	pOutImageIDs->RemoveSameValues();
}
void CAGimageSemanticTree::DBUpdateSemanticWeight(aguint_id ImageID, agbool bIsReset)
{
	if(m_pRoot==NULL) return;
	m_pRoot->DBUpdateSemanticWeight(m_pDBCnnI,ImageID,bIsReset);
}
agreal64 CAGimageSemanticTree::GetNormWeight()
{
	if(m_pRoot==NULL) return 0;

	agreal64 sum_weight=0;
	aguint32 sum_node=0;

	m_pRoot->GetTotalWeightAndNode(sum_weight, sum_node);
	return sum_weight/(agreal64)sum_node;
}


