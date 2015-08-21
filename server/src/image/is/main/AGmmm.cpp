#include "AGmmm.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

CAGtrainingDataSet::CAGtrainingDataSet():CAGmagicDBOrg()
{
	tAccessedBegin=tAccessedEnd=0;
	m_bIsNorm=agfalse;
}
CAGtrainingDataSet::~CAGtrainingDataSet()
{
	Destroy();
	DBCnnDetach();
}
void CAGtrainingDataSet::Destroy()
{
	m_use.Destroy();
	m_access.Destroy();
	tAccessedBegin=tAccessedEnd=0;
}
agbool CAGtrainingDataSet::IsBegined()
{
	return (tAccessedBegin!=0);
}
agbool CAGtrainingDataSet::IsEnded()
{
	return (tAccessedEnd!=0);
}
void CAGtrainingDataSet::Begin()
{
	if(IsBegined() && !IsEnded())	throw _T("Begined but not end yet");
	Destroy();
	tAccessedBegin=time(NULL);

}
void CAGtrainingDataSet::End()
{
	if(!IsBegined())	throw _T("Not begin yet");
	tAccessedEnd=time(NULL);
}
agbool CAGtrainingDataSet::DBRead(time_t begin, time_t end)
{
	if(begin==0 || end==0)			throw _T("Begin time and end time must not 0");
	if(IsBegined() && !IsEnded())	throw _T("Begined but not end yet");

	Destroy();
	aguint_id*	ImageIDs=NULL;
	agint32		nImageIDs=0;
	time_t		pTimes[2];	pTimes[0]=begin;	pTimes[1]=end;

	CAGuserAccessPatternMatrix::DBGetUserAccessPatternImageIDs(m_pDBCnnI,begin,end,ImageIDs,nImageIDs);
	if(ImageIDs)
	{
		m_use.DBRead(ImageIDs,nImageIDs,pTimes);
		free(ImageIDs);
	}
	m_access.DBRead(0,pTimes);//tham so dau la ImageID: khong su dung
	tAccessedBegin=begin;
	tAccessedEnd=end;

	return agtrue;
}
agbool CAGtrainingDataSet::DBInsert()
{
	if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	
	if(!m_use.DBInsert())		throw _T("Can not Insert");
	if(!m_access.DBInsert())	throw _T("Can not Insert");

	return agtrue;
}
agbool CAGtrainingDataSet::DBUpdate()
{
	if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");

	if(!m_use.DBUpdate())		throw _T("Can not Update");
	if(!m_access.DBUpdate())	throw _T("Can not Update");

	return agtrue;
}
agbool CAGtrainingDataSet::DBDelete()
{
	if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");

	agbool	bResult=agtrue;
	bResult=bResult && m_use.DBDelete();
	bResult=bResult && m_access.DBDelete();

	return bResult;
}
void* CAGtrainingDataSet::DBCnnAttach(void* pDBCnnI)//khong AddRef doi voi ADO
{
	void*	old=CAGmagicDBOrg::DBCnnAttach(pDBCnnI);

	m_use.DBCnnAttach(m_pDBCnnI);
	m_access.DBCnnAttach(m_pDBCnnI);
	return old;
}
void* CAGtrainingDataSet::DBCnnDetach()//khong Release
{
	m_use.DBCnnDetach();
	m_access.DBCnnDetach();
	return CAGmagicDBOrg::DBCnnDetach();
}

void CAGtrainingDataSet::DoWhenReceivedUserAccessMessage(AGUSER_ACCESS_PATTERN_ITEM* use_m_k, AGUSER_ACCESS_FREQUENCY_ITEM* access_k)
{
	if(!IsBegined() || IsEnded())	throw _T("Function only do when begined and not end yet");

	if(access_k!=NULL && access_k->nAccessed > 0)
	{

		agint32 j=m_access.m_aRelatedImageID.LSearch(access_k->kID);
		if(j!=-1)//tim thay
		{
			m_access.SetAt(j, m_access.GetAt(j)+ access_k->nAccessed);
			m_access.m_aTime.SetAt(j,access_k->tAccessed);
		}
		else
		{
			m_access.Add(access_k->nAccessed);

			m_access.m_aRelatedImageID.Add(access_k->kID);
			m_access.m_aTime.Add(access_k->tAccessed);
			if(m_access.GetSize()==1)//lan dau tien
			{
				m_access.m_bIsNorm=m_bIsNorm;
				m_access.m_ImageID=0;//m_access.m_ImageID khong duoc su dung
				m_access.DBCnnAttach(m_pDBCnnI);
				m_access.m_pNoFreeTempAGimageSrc=NULL;
				m_access.m_Reserved=0;
			}
		}
	}

	if(use_m_k!=NULL && use_m_k->isAccess!=0)
	{
		if(use_m_k->mID==use_m_k->kID)	throw _T("m must differ k");
		if(m_access.m_aRelatedImageID.LSearch(use_m_k->kID)==-1)	return;

		agint32 i=m_use.LSearchImageID(use_m_k->mID);
		if(i!=-1)//tim thay
		{
			CAGuserAccessPatternVec*	use_m=(CAGuserAccessPatternVec*)(m_use.GetAt(i));
			agint32					j=use_m->m_aRelatedImageID.LSearch(use_m_k->kID);
			if(j!=-1)//tim thay
			{
				use_m->SetAt(j,use_m_k->isAccess);
				use_m->m_aTime.SetAt(j,use_m_k->tAccessed);
			}
			else
			{
				use_m->Add(use_m_k->isAccess);
				use_m->m_aRelatedImageID.Add(use_m_k->kID);
				use_m->m_aTime.Add(use_m_k->tAccessed);
			}
		}
		else
		{
			CAGuserAccessPatternVec*	use_m=new CAGuserAccessPatternVec();
			use_m->Add(use_m_k->isAccess);

			use_m->m_aRelatedImageID.Add(use_m_k->kID);
			use_m->m_aTime.Add(use_m_k->tAccessed);
			use_m->m_bIsNorm=m_bIsNorm;
			use_m->m_ImageID=use_m_k->mID;
			use_m->DBCnnAttach(m_use.m_pDBCnnI);
			use_m->m_pNoFreeTempAGimageSrc=NULL;
			use_m->m_Reserved=0;

			m_use.Add(use_m);
		}
	}
}
aguint32 CAGtrainingDataSet::use(aguint_id mID, aguint_id kID, agbool throwErr)//thuc hien duoc moi luc
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	agint32 i,					m=m_use.GetSize();
	CAGuserAccessPatternVec*	use_m=NULL;
	for(i=0; i<m; i++)
	{
		use_m=(CAGuserAccessPatternVec*)(m_use.GetAt(i));
		if(use_m->GetImageID()==mID)	break;
	}
	if(i==m)
	{
		if(throwErr)	throw _T("Image ID not exist");
		else			return 0;
	}
	agint32 j, n=use_m->m_aRelatedImageID.GetSize();
	for(j=0; j<n; j++)
		if(use_m->m_aRelatedImageID.GetAt(j)==kID)	break;
	if(j==n)
	{
		if(throwErr)	throw _T("Image ID not exist");
		else			return 0;
	}
	return use_m->GetAt(j);
}
aguint32	CAGtrainingDataSet::access(aguint_id kID, agbool throwErr)//thuc hien duoc moi luc
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	agint32 j, n=m_access.GetSize();
	for(j=0; j<n; j++)
		if(m_access.m_aRelatedImageID.GetAt(j)==kID)	break;
	if(j==n)
	{
		if(throwErr)	throw _T("Image ID not exist");
		else			return 0;
	}
	return m_access.GetAt(j);
}
void CAGtrainingDataSet::GetAllImageIDsNotQuery(CAGidArray* FilterIDs,CAGidArray* aOutImageID)
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	aOutImageID->RemoveAll();

	agint32 n=m_use.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		aguint_id ImageID=m_use.GetAt(i)->GetImageID();

		if(FilterIDs!=NULL)
		{
			if(FilterIDs->LSearch(ImageID)==-1)		continue;//khong co trong filter
		}
		if(aOutImageID->LSearch(ImageID)==-1)	aOutImageID->Add(ImageID);
	}
}
void CAGtrainingDataSet::GetAllQueryImageIDs(CAGidArray* akQueryImageID)
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	akQueryImageID->RemoveAll();

	agint32 m=m_use.GetSize();
	for(agint32 i=0; i<m; i++)
	{
		CAGuserAccessPatternVec*	use_m=(CAGuserAccessPatternVec*)(m_use.GetAt(i));
		agint32					n=use_m->GetSize();
		for(agint32 j=0; j<n; j++)
		{
			aguint_id ImageID=use_m->m_aRelatedImageID.GetAt(j);
			if(akQueryImageID->LSearch(ImageID)==-1)	akQueryImageID->Add(ImageID);
		}
	}

	agint32 n=m_access.GetSize();
	for(agint32 j=0; j<n; j++)
	{
		aguint_id ImageID=m_access.m_aRelatedImageID.GetAt(j);
		if(akQueryImageID->LSearch(ImageID)==-1)	akQueryImageID->Add(ImageID);
	}
}
void CAGtrainingDataSet::GetAllQueryImageIDs(aguint_id ImageID, CAGidArray* akQueryImageID)
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	akQueryImageID->RemoveAll();

	agint32 i,				m=m_use.GetSize();
	CAGuserAccessPatternVec*	use_m=NULL;
	for(i=0; i<m; i++)
	{
		use_m=(CAGuserAccessPatternVec*)(m_use.GetAt(i));
		if(use_m->GetImageID()==ImageID)	break;
	}
	if(i==m)
	{
		agint32				n=use_m->GetSize();
		for(agint32 j=0; j<n; j++)
		{
			aguint_id ID=use_m->m_aRelatedImageID.GetAt(j);
			if(akQueryImageID->LSearch(ID)==-1)	akQueryImageID->Add(ID);
		}
	}
}
//FilterIDs la nhung ID chinh yeu dung de kich hoat
agbool CAGtrainingDataSet::affs(CAGidArray* FilterIDs, agfreal weight, CAGaffArray* aOutAff, CAGaffArray* aOutReversedAff)//chi thuc hien khi: begined && ended
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	if(aOutAff==NULL)				throw _T("Error parameter");

	CAGidArray aImageID, akQueryImageID;
	GetAllImageIDsNotQuery(NULL,&aImageID);
	GetAllQueryImageIDs(&akQueryImageID);
	if(aImageID.GetSize()==0 || akQueryImageID.GetSize()==0)	return agfalse;

	aOutAff->RemoveAll();
	aff_half(FilterIDs,&aImageID,&akQueryImageID,weight,aOutAff);
	agint32 n=aOutAff->GetSize();
	if(n==0)	return agfalse;

	agbool	bDeleteReversedAff=agfalse;
	if(aOutReversedAff!=NULL)	aOutReversedAff->RemoveAll();
	else
	{
		aOutReversedAff=new CAGaffArray();	bDeleteReversedAff=agtrue;
	}
	aOutReversedAff->Append(aOutAff);
	for(agint32 i=0; i<n; i++)
	{
		AGAFFINITY_ITEM&	item=aOutReversedAff->ElementAt(i);
		aguint_id		id=item.mID;
		item.mID=item.nID;
		item.nID=id;
	}
	if(bDeleteReversedAff)
	{
		aOutAff->Append(aOutReversedAff);	delete aOutReversedAff;
	}
	return agtrue;
}
agfreal	CAGtrainingDataSet::aff(aguint_id mID, aguint_id nID, agbool throwErr)//chi thuc hien khi: begined && ended
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	CAGidArray akQueryImageID;
	GetAllQueryImageIDs(&akQueryImageID);
	if(akQueryImageID.GetSize()==0)
	{
		if(throwErr)	throw _T("Not exist Query Image");
		else			return 0;
	}
	return aff(mID,nID,&akQueryImageID);
}
//FilterIDs la nhung ID chinh yeu dung de kich hoat
void CAGtrainingDataSet::aff_half(CAGidArray* FilterIDs, CAGidArray* aImageID, CAGidArray* akQueryImageID, agfreal weight, CAGaffArray* aOutAff)
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	if(FilterIDs==NULL)
	{
		agint32	n=aImageID->GetSize();
		if(n<2)	return;

		AGAFFINITY_ITEM	item;
		item.mID=aImageID->GetAt(0);
		for(agint32 i=1; i<n; i++)
		{
			item.nID=aImageID->GetAt(i);
			if(item.mID==item.nID) throw _T("Fatal error");
			agfreal	aff_value=aff(item.mID,item.nID,akQueryImageID)*weight;
			item.value=aff_value;
			item.bIsNorm=m_bIsNorm;
			aOutAff->Add(item);
		}
		aImageID->RemoveAt(0);
		aff_half(FilterIDs,aImageID,akQueryImageID,weight,aOutAff);//de quy
	}
	else
	{
		if(FilterIDs->GetSize()==0)	return;

		CAGidArray	IDs;
		agint32		m=aImageID->GetSize();
		agint32		i;

		//chi chep nhung ID khong co trong Filter
		for(i=0; i<m; i++)
		{
			aguint_id ImageID=aImageID->GetAt(i);
			if(FilterIDs->LSearch(ImageID)==-1)//khong co trong filter
				IDs.Add(ImageID);
		}

		m=FilterIDs->GetSize();
		for(i=0; i<m; i++)
		{
			aguint_id	mID=FilterIDs->GetAt(i);
			agint32		n=IDs.GetSize();
			for(agint32 j=0; j<n; j++)
			{
				aguint_id		nID=IDs.GetAt(j);
				if(mID==nID)	throw _T("Fatal error");
				agfreal	aff_value=aff(mID,nID,akQueryImageID)*weight;

				AGAFFINITY_ITEM	item;
				item.mID=mID;
				item.nID=nID;
				item.bIsNorm=m_bIsNorm;
				item.value=aff_value;

				aOutAff->Add(item);
			}
		}
		CAGidArray TempIDs;
		TempIDs.Append(FilterIDs);
		if(m>1)	aff_half(NULL,&TempIDs,akQueryImageID,2*weight,aOutAff);//de quy
	}
}
agfreal CAGtrainingDataSet::aff(aguint_id mID, aguint_id nID, CAGidArray* akQueryImageID, agbool throwErr)
{
	//if(!IsBegined() || !IsEnded())	throw _T("Neither begined nor yet");
	agint32		n=akQueryImageID->GetSize();
	if(n==0)
	{
		if(throwErr)	throw _T("Error Paramter");
		else			return 0;
	}
	agfreal	aff=0;
	for(agint32 i=0; i<n; i++)
	{
		aguint_id kID=akQueryImageID->GetAt(i);
		if(!m_bIsNorm)
			aff += (agfreal)use(mID,kID) * use(nID,akQueryImageID->GetAt(i)) * access(kID);
		else	throw _T("Implement not yet");
	}
	return aff;
}
void CAGtrainingDataSet::ResetPatternAndFreq(aguint32 pattern_value, aguint32 freq_value)
{
	agint32		i;
	agint32		m=m_use.GetSize();
	for(i=0; i<m; i++)
	{
		CAGuserAccessPatternVec*	use_m=(CAGuserAccessPatternVec*)(m_use.GetAt(i));
		agint32						n=use_m->GetSize();
		for(agint32 j=0; j<n; j++)
		{
			use_m->SetAt(j,pattern_value);
			use_m->m_aTime.SetAt(j,time(NULL));
		}
	}

	m=m_access.GetSize();
	for(i=0; i<m; i++)
	{
		m_access.SetAt(i, freq_value);
		m_access.m_aTime.SetAt(i,time(NULL));
	}
}

/*****************************************interface IAGmarkovModel, class CAGmarkovModel******************************/

CAGmarkovModel::CAGmarkovModel()
{
	m_S=NULL;
	m_A=NULL;
	m_B=NULL;
	m_bIsNorm=agfalse;
	m_mode=AGMAGICIS_MM_UPDATE_MODE;
	m_tLastUpdated=0;
}
CAGmarkovModel::~CAGmarkovModel()
{
	Destroy();
	DBCnnDetach();
}
IAGflexfMatrix* CAGmarkovModel::CreateFeaturesMatrix()
{
	return CAGfeatUtil::CreateFeaturesMatrix();
}
void CAGmarkovModel::Destroy()
{
	if(m_S)	{delete m_S; m_S=NULL;}
	if(m_A)	{delete m_A; m_A=NULL;}
	if(m_B)	{delete m_B; m_B=NULL;}
	//m_bIsNorm=agfalse;
	//m_mode=AGMAGICIS_MM_UPDATE_MODE;
	m_tLastUpdated=0;
}
void CAGmarkovModel::Ready(aguint16 mode, agbool bIsNorm)
{
	void*	pOldDBCnnI=m_pDBCnnI;

	Destroy();
	m_S=new CAGimageDBItems();
	m_A=new CAGimageAffMatrix();		m_A->SetIsNorm(bIsNorm);
	m_B=CreateFeaturesMatrix();				m_B->SetIsNorm(bIsNorm);
	m_mode=mode;
	m_bIsNorm=bIsNorm;
	m_tLastUpdated=0;
	m_pDBCnnI=pOldDBCnnI;
	m_S->DBCnnAttach(m_pDBCnnI);
	m_A->DBCnnAttach(m_pDBCnnI);
	m_B->DBCnnAttach(m_pDBCnnI);
}
agbool CAGmarkovModel::IsReady()
{
	return (m_S!=NULL);
}
void CAGmarkovModel::DoWhenReceivedTrainingDataSet(CAGtrainingDataSet* pDataSet, CAGidArray* FilterIDs, agfreal weight, agbool bIsReReadDBForS, agbool bForceUpdateAffAfter)
{
	if(pDataSet==NULL)						throw _T("Training data set must not null");
	if(!IsReady())							throw _T("Not ready yet");
	if(GetMode()!=AGMAGICIS_MM_UPDATE_MODE)	throw _T("Because of Reading database Only, can not receive DataSet");

	//Cap nhat m_S
	CAGidArray	ImageIDs;
	pDataSet->GetAllImageIDsNotQuery(FilterIDs,&ImageIDs);
	GetImageDBItems()->DBAppendDistinctImageIDs(ImageIDs.GetData(), ImageIDs.GetSize(),bIsReReadDBForS);

	//Cap nhat m_A
	CAGaffArray				aOutAff;
	if(!pDataSet->affs(FilterIDs,weight,&aOutAff))	return;
	agint32	n=aOutAff.GetSize();

	for(agint32 i=0; i<n; i++)
	{
		AGAFFINITY_ITEM	aff_item=aOutAff.GetAt(i);
		if(aff_item.mID==aff_item.nID) continue;
		GetAffinity()->SetAff(aff_item.mID,aff_item.nID,aff_item.value);
	}
	if(bForceUpdateAffAfter)
	{
		UpdateAff();
	}
}
void CAGmarkovModel::UpdateAff(agfreal update_aff_rartio)
{
	if(m_mode==AGMAGICIS_MM_READONLY_MODE)	throw _T("Because of Reading database Only, can not Update");
	if(!IsReady())							throw _T("Not ready yet");

	agint32	i, m;

	//Cap nhay m_A
	CAGaffArray	InsertAffs;
	CAGaffArray	UpdateAffs;
	m=m_A->GetSize();
	for(i=0; i<m; i++)
	{
		CAGimageAffVec*	pAff=(CAGimageAffVec*)(m_A->GetAt(i));
		agint32					n=pAff->m_aRelatedImageID.GetSize();
		for(agint32 j=0; j<n; j++)
		{
			AGAFFINITY_ITEM	affItem;
			affItem.mID=pAff->GetImageID();
			affItem.nID=pAff->m_aRelatedImageID.GetAt(j);
			if(affItem.mID==affItem.nID) throw _T("Fatal Error");
			affItem.value=pAff->GetAt(j);
			affItem.bIsNorm=m_A->IsNorm();
			if(affItem.value==0)	continue;
			//if(InsertAffs.LSearch(affItem.mID,affItem.nID)!=-1 || 
			//   UpdateAffs.LSearch(affItem.mID,affItem.nID)!=-1)
			//   continue;
			affItem.value *=update_aff_rartio;

			//doc thu
			agtchar*	SQL=NULL;
			if(!affItem.bIsNorm)	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT measure FROM ImagesAffinity WHERE ImageID="),agtrue);
			else				CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT measure FROM ImagesNormAffinity WHERE ImageID="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,affItem.mID,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RelatedImageID="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,affItem.nID,agtrue);

			agfreal*	data=NULL;
			agint32		fieldsNum;
			AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum);
			if(data)
			{
				if(fieldsNum!=1)	throw _T("Error read database");
				affItem.value +=data[0];//data[0] chinh la measure hien huu tai database
				UpdateAffs.Add(affItem);
				free(data);
			}
			else
				InsertAffs.Add(affItem);
			pAff->SetAt(j,0);//Set =0 lai tu dau
			if(SQL)	free(SQL);
		}
	}
	if(InsertAffs.GetSize()>0)		InsertAffs.DBInsert(m_pDBCnnI);
	if(UpdateAffs.GetSize()>0)		UpdateAffs.DBUpdate(m_pDBCnnI);
	m_tLastUpdated=time(NULL);
}
void CAGmarkovModel::Refresh()
{
	if(!IsReady())		throw _T("Not ready yet");
	CAGidArray	IDs;
	m_S->GetAllImageIDs(&IDs);
	IDs.RemoveSameValues();
	DBRead(IDs.GetData(),IDs.GetSize());
}
agbool CAGmarkovModel::IsNorm()
{
	return m_bIsNorm;
}
void CAGmarkovModel::SetIsNorm(agbool bIsNorm)
{
	m_bIsNorm=bIsNorm;
	m_A->SetIsNorm(bIsNorm);
	m_B->SetIsNorm(bIsNorm);
}
void CAGmarkovModel::Normalize(CAGmarkovModel* pAGmarkovModel)
{
	if(m_mode==AGMAGICIS_MM_UPDATE_MODE)	throw _T("Because of in update database mode, can not Normalize");
	if(!IsReady())						throw _T("Not Ready");

	if(IsNorm())
	{
		if(pAGmarkovModel)	pAGmarkovModel->CopyFrom(pAGmarkovModel);
		return;
	}
	if(pAGmarkovModel)
	{
		pAGmarkovModel->CopyFrom(pAGmarkovModel);
		if(!pAGmarkovModel->m_A->IsNorm())	pAGmarkovModel->m_A->Normalize();
		if(!pAGmarkovModel->m_B->IsNorm())	pAGmarkovModel->m_B->Normalize();
		pAGmarkovModel->m_bIsNorm=agtrue;
	}
	else
	{
		if(!m_A->IsNorm())	m_A->Normalize();
		if(!m_B->IsNorm())	m_B->Normalize();
		m_bIsNorm=agtrue;
	}
}
void CAGmarkovModel::ChangeMode(aguint16 mode, CAGmarkovModel* pAGMarkovModel)//chi duoc goi khi da Ready
{
	if(!IsReady())			throw _T("Not Ready");
	if(m_mode==mode)
	{
		if(pAGMarkovModel)	pAGMarkovModel->CopyFrom(this);
		return;
	}
	else
	{
		if(pAGMarkovModel)
		{
			pAGMarkovModel->CopyFrom(this);
			pAGMarkovModel->m_mode=mode;
			pAGMarkovModel->Refresh();
		}
		else
		{
			if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
			{
				UpdateAff();
			}
			else if(m_mode==AGMAGICIS_MM_READONLY_MODE)
			{
			}
			else throw _T("Not implement yet");
			m_mode=mode;
			Refresh();
		}
	}
}
aguint16 CAGmarkovModel::GetMode()//goi duoc moi luc
{
	return m_mode;
}
CAGimageDBItems* CAGmarkovModel::GetImageDBItems()//goi duoc moi luc
{
	return m_S;
}
CAGimageAffMatrix* CAGmarkovModel::GetAffinity()//goi duoc moi luc
{
	return m_A;
}
IAGflexfMatrix* CAGmarkovModel::GetFeaturesMatrix()
{
	return m_B;
}
void* CAGmarkovModel::DBCnnAttach(void* pDBCnnI)//khong AddRef, chi duoc goi khi da Ready
{
	if(!IsReady())			throw _T("Not Ready");
	void*	old=CAGmagicDBOrg::DBCnnAttach(pDBCnnI);

	m_S->DBCnnAttach(m_pDBCnnI);
	m_A->DBCnnAttach(m_pDBCnnI);
	m_B->DBCnnAttach(m_pDBCnnI);
	return old;
}
void* CAGmarkovModel::DBCnnDetach()//khong Release, goi duoc bat cu luc nao
{
	if(m_S) m_S->DBCnnDetach();
	if(m_A) m_A->DBCnnDetach();
	if(m_B) m_B->DBCnnDetach();
	return CAGmagicDBOrg::DBCnnDetach();
}
void CAGmarkovModel::CopyFrom(CAGmarkovModel* pAGmarkovModel)
{
	if(pAGmarkovModel==NULL)	throw _T("Error paramter");
	Ready(pAGmarkovModel->m_mode,pAGmarkovModel->m_bIsNorm);

	m_S->CopyFrom(pAGmarkovModel->m_S,agtrue);
	m_A->CopyFrom(pAGmarkovModel->m_A,agtrue);
	m_B->CopyFrom(pAGmarkovModel->m_B,agtrue);
	m_bIsNorm=pAGmarkovModel->m_bIsNorm;
	m_mode=pAGmarkovModel->m_mode;
	m_tLastUpdated=pAGmarkovModel->m_tLastUpdated;
	DBCnnAttach(pAGmarkovModel->m_pDBCnnI);
}
agbool CAGmarkovModel::DBRead(aguint_id ImageIDs[], agint32 nImageIDs, 
							  agbool bIsReReady, agbool bIsReReadImagesInfoFromDB_ReReadS)
{
	if(!IsReady())			throw _T("Not Ready");

	if(m_mode==AGMAGICIS_MM_READONLY_MODE)
	{
		if(bIsReReady)	Ready(m_mode,m_bIsNorm);
		m_A->DBRead(ImageIDs,nImageIDs);
		m_B->DBRead(ImageIDs,nImageIDs);
	}
	else if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
	{
		m_B->DBRead(ImageIDs,nImageIDs);
	}
	else throw _T("Implement not yet");

	CAGidArray	IDs, TotalIDs;
	if(m_mode==AGMAGICIS_MM_READONLY_MODE)
	{
		m_A->GetAllImageIDs(&IDs);	TotalIDs.Append(&IDs);
		m_B->GetAllImageIDs(&IDs);	TotalIDs.Append(&IDs);
	}
	else if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
	{
		m_A->GetAllImageIDs(&IDs);	TotalIDs.Append(&IDs);
		m_B->GetAllImageIDs(&IDs);	TotalIDs.Common(&IDs);
	}

	TotalIDs.RemoveSameValues();
	if(m_mode==AGMAGICIS_MM_READONLY_MODE)
	{
		if(bIsReReadImagesInfoFromDB_ReReadS)
			m_S->DBRead(TotalIDs.GetData(), TotalIDs.GetSize());
		else
			m_S->Import(&TotalIDs);
	}
	else if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
		m_S->DBRead(TotalIDs.GetData(), TotalIDs.GetSize());

	return agtrue;
}
agbool	CAGmarkovModel::DBSimpleRead(aguint_id NoCoincideImageIDs[], agint32 nNoCoincideImageIDs, 
							agbool bIsReReady, agbool bIsReReadImagesInfoFromDB_ReReadS)
{
	if(!IsReady())			throw _T("Not Ready");

	if(m_mode==AGMAGICIS_MM_READONLY_MODE)
	{
		if(bIsReReady)	Ready(m_mode,m_bIsNorm);
		m_A->DBRead(NoCoincideImageIDs,nNoCoincideImageIDs);
		m_B->DBRead(NoCoincideImageIDs,nNoCoincideImageIDs);
	}
	else if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
	{
		m_B->DBRead(NoCoincideImageIDs,nNoCoincideImageIDs);
	}
	else throw _T("Implement not yet");

	if(m_mode==AGMAGICIS_MM_READONLY_MODE)
	{
		if(bIsReReadImagesInfoFromDB_ReReadS)
			m_S->DBRead(NoCoincideImageIDs, nNoCoincideImageIDs);
		else
			m_S->Import(NoCoincideImageIDs,nNoCoincideImageIDs);
	}
	else if(m_mode==AGMAGICIS_MM_UPDATE_MODE)
		m_S->DBRead(NoCoincideImageIDs, nNoCoincideImageIDs);

	return agtrue;
}
agbool CAGmarkovModel::Add(CAGimage* pInputAGimage, aguint_id ImageType, agbool bIsNegativeImageWhenSegment)
{
	if(pInputAGimage==NULL)	throw _T("Fatal Error");

	CAGimageDBItem*	item=new CAGimageDBItem();
	item->SetIsStoreImage(m_S->IsStoreImage());
	item->DBCnnAttach(m_S->DBCnnGet());
	item->m_ImageID=0;
	if(item->IsStoreImage())
	{
		item->m_pAGimageSrc=item->CreateAGimage();
		item->m_pAGimageSrc->Copy(pInputAGimage);
	}
	m_S->Add(item);

	//A
	try
	{
		agint32		i;
		agint32		fieldsNum=0;
		agint32		recordsNum=0;
		agreal64**	data=NULL;
		agtchar*	SQL=NULL;
		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ID FROM "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
		if(ImageType!=0)
		{
			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Type="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);
		}

		if(!AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum,recordsNum))
		{
			m_S->RemoveAt(m_S->GetSize()-1);
			if(SQL)	free(SQL); SQL=NULL;
			return agfalse;
		}
		if(SQL)	free(SQL); SQL=NULL;
		
		CAGimageAffVec* pAGimageAffVec=new CAGimageAffVec();
		pAGimageAffVec->SetIsNorm(IsNorm());
		pAGimageAffVec->SetSize(recordsNum);
		pAGimageAffVec->m_aRelatedImageID.SetSize(recordsNum);
		for(i=0; i<recordsNum; i++)
		{
			pAGimageAffVec->m_aRelatedImageID.SetAt(i,(aguint_id)(data[i][0]));
			if(IsNorm())
				pAGimageAffVec->SetAt(i,(agfreal)1.0/(agfreal)recordsNum);
			else
				pAGimageAffVec->SetAt(i,1);
		}	
		pAGimageAffVec->m_ImageID=0;
		pAGimageAffVec->m_pNoFreeTempAGimageSrc=NULL;
		
		if(data)
		{
			for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
			free(data);
		}
		m_A->Add(pAGimageAffVec);

	}
	catch(_com_error &e)
	{
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
	//m_B
	IAGflexfVec*	pAGflexfVec=(IAGflexfVec*)m_B->newAGOBJ_ARRAY_TYPE(); 
	pAGflexfVec->SetIsNorm(IsNorm());
	pAGflexfVec->CreateFrom(pInputAGimage, bIsNegativeImageWhenSegment,NULL);
	m_B->Add(pAGflexfVec);
	return agtrue;
}

/***************************class IAGmmSystem***********************************/
void* IAGmmSystem::DBCnnAttach(void* pDBCnnI)//khong AddRef
{
	void*	old=CAGmagicDBOrg::DBCnnAttach(pDBCnnI);

	IAGmarkovModel*		pIAGmarkovModel=GetMarkovModel();
	if(pIAGmarkovModel) pIAGmarkovModel->DBCnnAttach(m_pDBCnnI);
	
	return old;
}
void* IAGmmSystem::DBCnnDetach()//khong Release
{
	IAGmarkovModel*		pIAGmarkovModel=GetMarkovModel();
	if(pIAGmarkovModel)	pIAGmarkovModel->DBCnnDetach();

	return CAGmagicDBOrg::DBCnnDetach();
}

/***************************class IAGmmTrainingSystem***********************************/

IAGmmTrainingSystem::IAGmmTrainingSystem() : IAGmmSystem()
{
	m_pAGmarkovModel=CreateMarkovModel();

	m_pDataSet=new CAGtrainingDataSet();
	m_pDataSet->Begin();
}
IAGmmTrainingSystem::~IAGmmTrainingSystem()
{
	if(m_pAGmarkovModel)	delete m_pAGmarkovModel;	m_pAGmarkovModel=NULL;
	if(m_pDataSet)			delete m_pDataSet;			m_pDataSet=NULL;

	DBCnnDetach();
}
IAGmarkovModel* IAGmmTrainingSystem::CreateMarkovModel()
{
	IAGmarkovModel*	 pIAGmarkovModel=new CAGmarkovModel();
	pIAGmarkovModel->Ready(AGMAGICIS_MM_UPDATE_MODE,agfalse);
	return pIAGmarkovModel;
}
IAGmarkovModel*	IAGmmTrainingSystem::GetMarkovModel()
{
	return m_pAGmarkovModel;
}
void* IAGmmTrainingSystem::DBCnnAttach(void* pDBCnnI)//khong AddRef
{
	void*	old=IAGmmSystem::DBCnnAttach(pDBCnnI);
	if(m_pDataSet)		m_pDataSet->DBCnnAttach(m_pDBCnnI);
	return	old;
}
void* IAGmmTrainingSystem::DBCnnDetach()//khong Release
{
	if(m_pDataSet)		m_pDataSet->DBCnnDetach();

	return IAGmmSystem::DBCnnDetach();
}

/***********************************class CAGmmTrainingSystemUIWinThread**********************/

#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNCREATE(CAGmmTrainingSystemUIWinThread, CWinThread)

CAGmmTrainingSystemUIWinThread* pGlobalAGmmTrainingSystemUIWinThread=NULL;

CAGmmTrainingSystemUIWinThread::CAGmmTrainingSystemUIWinThread(CWnd* pWnd, CEvent* pTempEvent) : CWinThread(), IAGmmTrainingSystem()
{
	//m_bAutoDelete=FALSE;
	m_pMainWnd=pWnd;
	CreateThread(CREATE_SUSPENDED);

	m_bIsRunning=agfalse;
	m_bIsInit=agfalse;
	m_pTempNoFreeEvent=pTempEvent;

	m_ResetTSTimerID=0;
}
void CAGmmTrainingSystemUIWinThread::SetTimer()
{
	if(m_ResetTSTimerID==0)
		m_ResetTSTimerID=(aguint_id)::SetTimer(NULL,0,AGMAGICIS_RESET_TRAININGDATASET_ELAPSE_TIME_IN_MILISECS,(TIMERPROC)AGmmTrainingSystemUIWinThreadTimeProc);
}
void CAGmmTrainingSystemUIWinThread::KillTimer()
{
	if(m_ResetTSTimerID!=0)
	{
		::KillTimer(NULL,(UINT_PTR)m_ResetTSTimerID);
		m_ResetTSTimerID=0;

		m_MyEvent.ResetEvent();
		::WaitForSingleObject(m_MyEvent.m_hObject,AGMAGICIS_MYEVENT_WAIT_TIME_IN_MILISECS);
	}
}
CAGmmTrainingSystemUIWinThread::~CAGmmTrainingSystemUIWinThread()
{
	MyCleanup();
}
void CAGmmTrainingSystemUIWinThread::Init()
{
	if(m_bIsInit)	return;
	m_bIsInit=agtrue;
	pGlobalAGmmTrainingSystemUIWinThread=this;
	Start();
}
void CAGmmTrainingSystemUIWinThread::MyCleanup()
{
	if(m_pDataSet->IsBegined())	m_pDataSet->End();
	m_pDataSet->Begin();
	m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());

	KillTimer();
	m_bIsRunning=agfalse;
	m_bIsInit=agfalse;
	m_pTempNoFreeEvent=NULL;

	pGlobalAGmmTrainingSystemUIWinThread=NULL;
}

void CAGmmTrainingSystemUIWinThread::Stop()
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();
	if(!m_bIsRunning)					goto end;
	if(SuspendThread()!=0xFFFFFFFF)		m_bIsRunning=agfalse;
	KillTimer();
end:
	if(m_pTempNoFreeEvent)	m_pTempNoFreeEvent->SetEvent();
///////////////////////////////////////////////////////////////////
	{
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Training System Stopped"))
	}
}
void CAGmmTrainingSystemUIWinThread::Start()
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();
	if(m_bIsRunning)					goto end;
	if(ResumeThread()!=0xFFFFFFFF)		m_bIsRunning=agtrue;

	//SetTimer();
end:
	if(m_pTempNoFreeEvent)	m_pTempNoFreeEvent->SetEvent();
/////////////////////////////////////
	{
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Training System Started"))
	}
}
agbool CAGmmTrainingSystemUIWinThread::IsRunning()
{
	return m_bIsRunning;
}
BOOL CAGmmTrainingSystemUIWinThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CAGmmTrainingSystemUIWinThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	MyCleanup();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CAGmmTrainingSystemUIWinThread, CWinThread)
	//{{AFX_MSG_MAP(CAGmmTrainingSystemUIWinThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_THREAD_MESSAGE(AGMAGICIP_WM_RECEIVED_USER_ACCESS, OnReceivedUserAccess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmmTrainingSystemUIWinThread message handlers

#include <time.h>
void CAGmmTrainingSystemUIWinThread::OnReceivedUserAccess(WPARAM wParam, LPARAM lParam)
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();
	POST_OUTPUT_NOTICE(m_pMainWnd,_T("Training System has just received Feedback from client"))

	CAGuserAccessMsgs*			pAGuserAccessMsgs=(CAGuserAccessMsgs*)lParam;
	if(pAGuserAccessMsgs==NULL)	return;
	agint32 n=pAGuserAccessMsgs->GetSize();
	if(n==0 || !IsRunning())
	{
		if(pAGuserAccessMsgs->m_bDeleteMeInProc)	delete pAGuserAccessMsgs;
		return;
	}
	
	//CAGmagicDBUtil::BeginTrans(DBCnnGet());
	CAGidArray	mIDs;
	for(agint32 i=0; i<n; i++)
	{
		CAGuserAccessMsg*	pAGuserAccessMsg=pAGuserAccessMsgs->GetAt(i);
		if(pAGuserAccessMsg==NULL)	throw _T("Ftatal Error");
		if(pAGuserAccessMsg->m_usemk)
		{
			pAGuserAccessMsg->m_usemk->tAccessed=time(NULL);
			mIDs.Add(pAGuserAccessMsg->m_usemk->mID);
		}
		if(pAGuserAccessMsg->m_accessk)
		{
			pAGuserAccessMsg->m_accessk->tAccessed=time(NULL);
		}
		m_pDataSet->DoWhenReceivedUserAccessMessage(pAGuserAccessMsg->m_usemk,pAGuserAccessMsg->m_accessk);
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Training System updated Training Data Set from User's Access Pattern and User's Access Frequency"))
	}
	
	if(mIDs.GetSize()>0)
	{
		//mIDs la FilterIDs la nhung ID chinh yeu dung de kich hoat
		m_pAGmarkovModel->DoWhenReceivedTrainingDataSet(m_pDataSet,&mIDs,1,agfalse,agtrue);
//phu them
		agint32 m=m_pDataSet->m_access.m_aRelatedImageID.GetSize();
		for(agint32 i=0; i<m; i++)
		{
			aguint_id	kID=m_pDataSet->m_access.m_aRelatedImageID.GetAt(i);
			aguint32	nAccessed=m_pDataSet->m_access.GetAt(i);
			if(nAccessed==0)	continue;

			agint32 n=mIDs.GetSize();
			for(agint32 j=0; j<n; j++)
			{
				aguint_id		mID=mIDs.GetAt(j);
				if(mID==kID)	continue;
				CAGimageAffMatrix::SetAffToDB(m_pDBCnnI, mID, kID, 
						4*(agfreal)nAccessed*(agfreal)AGMAGICIS_UPDATE_AFF_RATIO, m_pDataSet->IsNorm());
				CAGimageAffMatrix::SetAffToDB(m_pDBCnnI, kID, mID, 
						4*(agfreal)nAccessed*(agfreal)AGMAGICIS_UPDATE_AFF_RATIO, m_pDataSet->IsNorm());
			}
		}
	}
	POST_OUTPUT_NOTICE(m_pMainWnd,_T("Training System Learning (Update Markove Model from Training Data Set) ..."))
	//CAGmagicDBUtil::CommitTrans(DBCnnGet());

	{//Neu nhu khong dinh thoi gian cap nhat lai CSDL
		if(m_ResetTSTimerID==0 && m_pDataSet->m_use.GetSize()>100)
		{
			m_pDataSet->m_use.RemoveAll();
			m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		}
	}

	if(pAGuserAccessMsgs->m_bDeleteMeInProc)	delete pAGuserAccessMsgs;
}

VOID CALLBACK AGmmTrainingSystemUIWinThreadTimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	CAGmmTrainingSystemUIWinThread* pMyThread=pGlobalAGmmTrainingSystemUIWinThread;
	if(pMyThread==NULL)				return;

	CSingleLock						singleLock(&(pMyThread->m_Mutex));
	singleLock.Lock();

	if(!pMyThread->IsRunning())		return;
////////////////////////////////////////////////////////
	{
		POST_OUTPUT_NOTICE(pMyThread->m_pMainWnd,_T("Training System reset Training Data Set and Makov Model. Timer Operating..."))
	}
	if(idEvent==pMyThread->m_ResetTSTimerID)
	{
		if(pMyThread->m_pDataSet->m_use.GetSize()>100)
		{
			pMyThread->m_pDataSet->m_use.RemoveAll();
			pMyThread->m_pAGmarkovModel->Ready(pMyThread->m_pAGmarkovModel->GetMode(),pMyThread->m_pAGmarkovModel->IsNorm());
		}
		else
		{
			pMyThread->m_pDataSet->ResetPatternAndFreq(0, 1);
			//if(pMyThread->m_pMainWnd)
			//	pMyThread->m_pMainWnd->SendMessage(AGMAGICIP_WM_REQUIRE_SEND_ACCESS_FREQ_AGAIN,0,(LPARAM)(&(pMyThread->m_pDataSet->m_access)));
		}
	}
	pMyThread->m_MyEvent.SetEvent();
}
void CAGmmTrainingSystemUIWinThread::Test()
{
	CSingleLock						singleLock(&m_Mutex);
	singleLock.Lock();
	m_pDataSet->End();

	//CAGmagicDBUtil::BeginTrans(pMyThread->DBCnnGet());
	m_pAGmarkovModel->DoWhenReceivedTrainingDataSet(m_pDataSet,NULL,1,agfalse,agtrue);
	//CAGmagicDBUtil::CommitTrans(pMyThread->DBCnnGet());

	m_pDataSet->Begin();
}
#endif	//#if AGMAGIC_SUPPORT_MFC
