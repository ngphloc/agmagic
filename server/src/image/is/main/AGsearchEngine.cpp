#include "AGsearchEngine.h"

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../ip/main/AGsemantic.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/***********************class COutSim****************************/

COutSim::COutSim()
{
}
COutSim::~COutSim()
{
}
CAGmagicElement* COutSim::CreateMe()
{
	return new COutSim();
}
agbool COutSim::CopyFrom(CAGmagicElement* pAGmagicElement)
{
	COutSim*			pOutSim=(COutSim*)pAGmagicElement;
	if(pOutSim==NULL)	return agfalse;
	id=pOutSim->id;
	sim=pOutSim->sim;
	return agtrue;
}
aguint_id COutSim::GetID()
{
	return id;
}
agfreal	COutSim::GetValue()
{
	return sim;
}

/***********************class CAGoutSimPtrArray****************************/


/***********************interface IAGmmSearchingSystem****************************/

IAGmmSearchingSystem::IAGmmSearchingSystem() : IAGmmSystem()
{
	m_pAGmarkovModel=CreateMarkovModel();
	m_NumberRecordsOfPage=AGMAGICIS_NUMBER_RECORDS_OF_PAGE;//la 10000
	m_InitPageCount=0;
	m_TableCount=AGMAGICIS_TABLE_COUNT;//la 0
}
IAGmmSearchingSystem::~IAGmmSearchingSystem()
{
	if(m_pAGmarkovModel)	delete m_pAGmarkovModel;	m_pAGmarkovModel=NULL;
	DBCnnDetach();
}
IAGmarkovModel* IAGmmSearchingSystem::CreateMarkovModel()
{
	IAGmarkovModel*	 pIAGmarkovModel=new CAGmarkovModel();
	pIAGmarkovModel->Ready(AGMAGICIS_MM_READONLY_MODE,agtrue);
	return pIAGmarkovModel;
}
IAGmarkovModel*	IAGmmSearchingSystem::GetMarkovModel()
{
	return m_pAGmarkovModel;
}
void IAGmmSearchingSystem::IncreaseTablePage(agint32& iTable, agint32& iPage)
{
	iPage ++;
	if(iPage>=m_InitPageCount)
	{
		iTable++;
		if(iTable>=m_TableCount)
		{
			iPage=-1;
			iTable=-1;
		}
	}
}
//iTable=-1: het table, iPage=-1: het page
void IAGmmSearchingSystem::PreFilter(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32 iTable, agint32 iPage)
{
	{
		POST_OUTPUT_NOTICE(AfxGetMainWnd(),_T("Searching System do PreFiltering for searching..."))
	}
	if(pOutputItems==NULL)		throw _T("Parameter invalid");
	pOutputItems->RemoveAll();
	m_InitPageCount=0;
	if(iTable==-1 || iPage==-1)	return;

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);

	//ImageType==0: lay het
	if(ImageType!=0)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Type="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);
	}
//phan nay chinh la doan can thay the
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);
		if(SQL)	free(SQL); SQL=NULL;
		m_InitPageCount=pRs->PageCount;
		if(/*m_InitPageCount==0 || */pRs->EndOfFile)
		{
			pRs->Close();
			return;
		}

		agint32 count=0;
		while(!(pRs->EndOfFile))
        {
			CAGimageDBItem*	item=new CAGimageDBItem();
			item->SetIsStoreImage(pOutputItems->IsStoreImage());
			item->DBCnnAttach(pOutputItems->DBCnnGet());
	
			//ID
			_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
			item->m_ImageID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
	
			//Name
			varValue = pRs->Fields->GetItem(_T("Name"))->Value;
			CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,item->m_Name);

			//URL
			varValue = pRs->Fields->GetItem(_T("URL"))->Value;
			CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,item->m_URL);
			
			if(item->IsStoreImage())
			{
				if(item->m_pAGimageSrc)	delete item->m_pAGimageSrc;
				item->m_pAGimageSrc=item->CreateAGimage();
				if(item->m_pAGimageSrc->Load(item->m_URL))
					item->m_pAGimageSrc->m_ID=item->m_ImageID;
				else
				{
					if(item->m_pAGimageSrc)	delete item->m_pAGimageSrc;
					item->m_pAGimageSrc=NULL;
				}
			}
			
			pOutputItems->Add(item);
			pRs->MoveNext();
			count++;
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
	if(SQL)	free(SQL); SQL=NULL;
}
void IAGmmSearchingSystem::PreFilterEx(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32 iTable, agint32 iPage)
{
	if(pOutputItems==NULL)		throw _T("Parameter invalid");
	if(pOutputItems->m_pSemanticTree==NULL || pOutputItems->m_CandidateCount==0)
	{
		PreFilter(ImageID, ImageType, pOutputItems, iTable, iPage);
		return;
	}
	pOutputItems->RemoveAll();
	if(iTable==-1 || iPage==-1)	return;

	CAGimageSemantic::DBUpdateSemanticOfImages(m_pDBCnnI, ImageType);

	CAGimageIDs SemanticImageIDs;
	pOutputItems->m_pSemanticTree->CollectSemanticIDs(agfalse, &SemanticImageIDs);
	pOutputItems->DBRead(SemanticImageIDs.GetData(), SemanticImageIDs.GetSize());

}
/*
Vai tro cua iTable va iPage
	Moi lan tra ket qua tim kiem ve se tra ve tung page thong qua iPage, so iPage chinh la iTable
*/
void IAGmmSearchingSystem::Search(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32& iTable, agint32& iPage, CAGimage* pInputAGimage, agint32 nFeatures/*=0: lay het*/, agfreal Threshold)
{
	//ImageID=0: anh truy van la anh tu do, khong nam trong CSDL, neu ImageID=0 thi pInputAGimage phai khac NULL

	if(pOutputItems==NULL || ImageID==-1)	throw _T("Parameter invalid");
	pOutputItems->RemoveAll();
	m_InitPageCount=0;
	if(iTable==-1 || iPage==-1)	return;

	//Tien loc
	CAGinteractImagesMsg CandidateItems;
	CAGinteractImagesMsg::DefaultInit(&CandidateItems);
	CandidateItems.DBCnnAttach(m_pDBCnnI);
	CandidateItems.SetIsStoreImage(agfalse);
	CandidateItems.SetSemanticTree(pOutputItems->m_pSemanticTree,agtrue);
	CandidateItems.m_CandidateCount=pOutputItems->m_CandidateCount;//=0: se lay het

	PreFilterEx(ImageID,ImageType,&CandidateItems,iTable,iPage);
	IncreaseTablePage(iTable,iPage);
	{
		POST_OUTPUT_NOTICE(AfxGetMainWnd(),_T("Searching System do Searching..."))
	}

	//Lay ID cua cac anh ung cu vien
	if(CandidateItems.GetSize()==0)	return;
	CAGidArray	CandidateIDs;
	CandidateItems.GetAllImageIDs(&CandidateIDs);//lay id cua cac anh ung cu vien

	//loai tru anh tu do(ID=0) ra khoi Markov Model
	m_pAGmarkovModel->GetImageDBItems()->RemoveIfImageID(0);//loai bo ID=0: chinh la ID cua anh tu do
	m_pAGmarkovModel->GetAffinity()->RemoveIfImageID(0);
	m_pAGmarkovModel->GetFeaturesMatrix()->RemoveIfImageID(0);

	//Doc CSDL
	agbool		bRead;
	//Doc CSDL neu nhu MarkoveModel rong, de tai tao MarkoveModel
	if(m_pAGmarkovModel->GetImageDBItems()->IsEmpty() || !m_pAGmarkovModel->GetImageDBItems()->IsContentImageIDs(&CandidateIDs))
	{

		m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		m_pAGmarkovModel->GetAffinity()->SetIsNorm(agfalse);//gia lap Aff khong duoc chuan hoa vi chuong trinh khong xu ly chuan hoa Aff khi luu xuong CSDL
		bRead=m_pAGmarkovModel->DBSimpleRead(CandidateIDs.GetData(), CandidateIDs.GetSize(),agfalse,agfalse);
		if(m_pAGmarkovModel->IsNorm())
			m_pAGmarkovModel->GetAffinity()->Normalize();//chuan hoa lai Aff
	}
	else	bRead=agtrue;
	//Khi doc khong thanh cong nghia la sau khi tai tao Markov Model bang cach doc CSDL, 
	//neu nhu Markov Model rong thi ngung tim kiem
	if(!bRead)
	{
		m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		return;
	}

	//Lay cac thanh phan cua Markov Model
	CAGimageDBItems*	S=m_pAGmarkovModel->GetImageDBItems();
	CAGimageAffMatrix*	A=m_pAGmarkovModel->GetAffinity();
	IAGflexfMatrix*	B=m_pAGmarkovModel->GetFeaturesMatrix();
	if(S->GetSize()==0)
	{
		m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		return;
	}
	//Neu nhu truy tim anh tu do(khong co trong CSDL ) thi phai add anh tu do do vao Markov Model
	if(ImageID ==0)
	{
		if(pInputAGimage==NULL)	throw _T("Fatal Error");
		if(!m_pAGmarkovModel->Add(pInputAGimage,ImageType,CAGmagicConfUtil::IsNegativeImageWhenSegment(ImageType)/*neu la loai flower-spec thi negative*/))
		{
			m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
			return;
		}
	}

	//Lay lai tap anh ung vien
	S->GetAllImageIDs(&CandidateIDs);//lay lai tap anh ung vien
	CAGimageAffVec*		pAGimageAffVec=(CAGimageAffVec*)A->GetAtImageID(ImageID);//Lay matran affinity A
	IAGflexfVec*		pAGflexfVec=B->GetAtImageID(ImageID);//lay ma tran dac trung
	
	//khoi tao cac thong so can thiet cho viec tim kiem
	agint32		C=CandidateIDs.GetSize();//C la ting so cac anh ung cu vien
	agfreal*	aq=(agfreal*)malloc(C*sizeof(agfreal));
	agfreal*	bq=pAGflexfVec->GetData();//vector dac trung cua anh truy van
	agint32*	pIndexForB=(agint32*)malloc(C*sizeof(agint32));

	memset(aq,0,C*sizeof(agfreal));
	memset(pIndexForB,0,C*sizeof(agint32));
	for(agint32 c=0; c<C; c++)
	{
		aguint_id		id=CandidateIDs.GetAt(c);
		agfreal*		aq_c=pAGimageAffVec->GetAtImageID(id);
		if(aq_c==NULL)	CandidateIDs.SetAt(c,-1);// loai tru viec tm kiem lai anh truy van
		else			aq[c]=*aq_c;

		pIndexForB[c]=B->LSearchImageID(id);
		if(pIndexForB[c]==-1)
			throw _T("Fatal Error");
	}

	agint32				default_number_features=B->GetAt(0)->GetSize();
	if(nFeatures==0)	nFeatures=default_number_features;
	else				nFeatures=AGMIN(nFeatures,default_number_features);

	agfreal**	MatrixB=NULL;
	agint32		nVectorsInMatrixB=0, nFeaturesOfVectorInMatrixB=0;
	B->Export(MatrixB,nVectorsInMatrixB,nFeaturesOfVectorInMatrixB);
	if(MatrixB==NULL || nVectorsInMatrixB < C || nFeaturesOfVectorInMatrixB < nFeatures)
		throw _T("Fatal Error");

	OUT_SIM*			OutSim=NULL;
	agint32				nOutSim=0;
	OutSim=SimilarityFromCandidateImagesToQueryImage_q(C, aq, MatrixB, 
						bq, nFeatures, CandidateIDs.GetData(), 
						OutSim, nOutSim, pIndexForB, Threshold);
	{
		POST_OUTPUT_NOTICE(AfxGetMainWnd(),_T("Searching System do Searching Finish"))
	}

    free(aq);
	free(pIndexForB);
	if(MatrixB)
	{
		for(agint32 i=0; i<nVectorsInMatrixB; i++)
			if(MatrixB[i])	free(MatrixB[i]);

		free(MatrixB);	MatrixB=NULL;
	}
	if(OutSim==NULL)
	{
		m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		return;
	}
	//Loc ra cac anh gan dung tu CandidateItems va add vao pOutputItems
	//.......
	for(agint32 i=0; i<nOutSim; i++)
	{
		CAGimageDBItem*	item=new CAGimageDBItem();
		item->SetIsStoreImage(pOutputItems->IsStoreImage());
		item->DBCnnAttach(pOutputItems->DBCnnGet());
		item->m_ImageID=OutSim[i].id;
		CAGimageDBItem*	temp_item=CandidateItems.GetAtID(OutSim[i].id);
		if(temp_item==NULL)	throw _T("Fatal error");

		item->AllocName(temp_item->m_Name);
		item->AllocURL(temp_item->m_URL);
		COutSim* pOutSim=new COutSim();
		pOutSim->id=OutSim[i].id;
		pOutSim->sim=OutSim[i].sim;
		item->m_pReservedAGmagicElement=pOutSim;

		if(item->IsStoreImage())
		{
			item->m_pAGimageSrc=item->CreateAGimage();
			if(item->m_pAGimageSrc->Load(item->m_URL))
				item->m_pAGimageSrc->m_ID=item->m_ImageID;
			else
			{
				delete item->m_pAGimageSrc;
				item->m_pAGimageSrc=NULL;
			}
		}
		
		//Co the chinh sua phan nay lai
		//item->SetSemanticTree(pOutputItems->m_pSemanticTree,agtrue);
		pOutputItems->Add(item);
	}

	if(OutSim)	free(OutSim);
}

agfreal IAGmmSearchingSystem::EdgeWeightFromImage_i_ToQueryImage_q_AtFeature_t(agfreal aqi, agfreal bi[], 
														 agfreal bq[], aguint32 t)
{
	if(bi==NULL || bq==NULL)	throw _T("Error parameter");

	agfreal bqi=(bq[0]==0)?AGMAGICIP_MIN_NORM_FEAT_VALUE:bq[0];
	agfreal	Wi=aqi*( 1 - AGABS_OF_SUB(bi[0],bqi)*AGMAGICIP_MIN_NORM_FEAT_VALUE / bqi );
	for(aguint32 o=1; o<=t; o++)
	{
		bqi=(bq[o]==0)?AGMAGICIP_MIN_NORM_FEAT_VALUE:bq[o];
		Wi=Wi*( 1 - AGABS_OF_SUB(bi[o],bqi)*AGMAGICIP_MIN_NORM_FEAT_VALUE / bqi);
	}
	return Wi;
}
agfreal IAGmmSearchingSystem::SimilarityFromImage_i_ToQueryImage_q(agfreal aqi, agfreal bi[], 
											 agfreal bq[], aguint32 T)
{
	if(bi==NULL || bq==NULL || T==0)	throw _T("Error parameter");

	agfreal bqi=(bq[0]==0)?AGMAGICIP_MIN_NORM_FEAT_VALUE:bq[0];
	agfreal	Wi=aqi*( 1 - AGABS_OF_SUB(bi[0],bqi)*AGMAGICIP_MIN_NORM_FEAT_VALUE / bqi );

	agfreal Si=Wi;
	for(aguint32 t=1; t<T; t++)
	{
		bqi=(bq[t]==0)?AGMAGICIP_MIN_NORM_FEAT_VALUE:bq[t];
		Wi=Wi*( 1 - AGABS_OF_SUB(bi[t],bqi)*AGMAGICIP_MIN_NORM_FEAT_VALUE / bqi );

		Si +=Wi;
	}
	return Si;
}

int IAGmmSearchingSystem::CompareTwoSimValueInDecreaseOrder(const void* sim1, const void* sim2)
{
	OUT_SIM* cmpSim1=(OUT_SIM*)sim1;
	OUT_SIM* cmpSim2=(OUT_SIM*)sim2;
	if(cmpSim1->sim > cmpSim2->sim)			return -1;
	else if(cmpSim1->sim == cmpSim2->sim)	return 0;
	else									return 1;
}
int IAGmmSearchingSystem::CompareTwoSimValueInIncreaseOrder(const void* sim1, const void* sim2)
{
	OUT_SIM* cmpSim1=(OUT_SIM*)sim1;
	OUT_SIM* cmpSim2=(OUT_SIM*)sim2;
	if(cmpSim1->sim < cmpSim2->sim)			return -1;
	else if(cmpSim1->sim == cmpSim2->sim)	return 0;
	else 									return 1;
}
OUT_SIM* IAGmmSearchingSystem::SimilarityFromCandidateImagesToQueryImage_q(agint32 C, agfreal aq[], agfreal* B[], agfreal bq[], aguint32 T,  
										aguint_id ids[], OUT_SIM*& OutSim, agint32& nOutSim, agint32 pIndexForB[], agfreal SimThreshold)
{
	if(C==0 || aq==NULL || B==NULL || bq==NULL || T==0)	throw _T("Error parameter");
	if(OutSim)	free(OutSim);	OutSim=NULL;	nOutSim=0;

	OUT_SIM* TempOutSim=(OUT_SIM*)malloc(C*sizeof(OUT_SIM));
	memset(TempOutSim,0,C*sizeof(OUT_SIM));
	for(agint32 c=0; c<C; c++)
	{
		if(ids[c]==-1)	continue;//ID anh =-1:khong co
		agint32 idxB;
		if(pIndexForB==NULL)
			idxB=c;
		else
		{
			idxB=pIndexForB[c];
			if(idxB==-1)		continue;
		}
		agfreal sim=SimilarityFromImage_i_ToQueryImage_q(aq[c],B[idxB],bq,T);
		if(sim > SimThreshold)
		{
			TempOutSim[nOutSim].sim=sim;
			TempOutSim[nOutSim].id=ids[c];
			nOutSim ++;
		}
	}
	if(nOutSim==0)
	{
		free(TempOutSim);
		return NULL;
	}
	OutSim=(OUT_SIM*)malloc(nOutSim*sizeof(OUT_SIM));
	memcpy(OutSim,TempOutSim,nOutSim*sizeof(OUT_SIM));
	free(TempOutSim);

	qsort(OutSim, nOutSim, sizeof(OUT_SIM), CompareTwoSimValueInDecreaseOrder);
	return OutSim;
}
//nhung ham vi du tim kien khong quan trong
void IAGmmSearchingSystem::SampleSearch(aguint_id QueryImageType, CString szImagePath, CStringArray& strOuts)
{
	strOuts.RemoveAll();

	CAGmagicConfUtil::Init();
	CAGmagicIPConfUtil::Init();

	//tao connection den CSDL
	agtchar*	szCnn=NULL;
	void*		pDBCnnI=NULL;
	agtchar*	basedir=CAGmagicConfUtil::AGmagicBaseDirAbsoluteFromBin();
	MessageBox(NULL,basedir,_T("basedir"),MB_OK);


	CAGmagicStrUtil::private_tcscat(szCnn,_T("Provider="),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T("Microsoft.Jet.OLEDB.4.0"),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T(";Persist Security Info=False"),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T(";Data Source="),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,basedir,agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T("data"),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T("db"),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T("access-2000"),agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,AGMAGIC_DIR_SPLASH_STR,agtrue);
	CAGmagicStrUtil::private_tcscat(szCnn,_T("AGmagic.mdb"),agtrue);
	MessageBox(NULL,szCnn,_T("ADO Connection"),MB_OK);
	CAGmagicDBUtil::CnnCreate(pDBCnnI, szCnn, &CAGmagicConfUtil::AGmagic_GlobalDBCnnConfig, agtrue);
	ASSERT(pDBCnnI!=NULL);
	if(szCnn) free(szCnn);
	if(basedir) free(basedir);

	//tao CAGimage tu duong dan szImagePath
	CAGimage QueryImage;
	if(!QueryImage.Load(szImagePath)) return;
	if(QueryImageType==0)
	{
		CAGidTypeArray ImageIDTypes;
		CAGimageDBUtil::FindImageIntel(pDBCnnI, szImagePath.GetBuffer(0), &ImageIDTypes);

		if(ImageIDTypes.GetSize()!=0)
		{
			IMAGE_ID_TYPE	ImageIDType = ImageIDTypes.GetAt(0);
			QueryImageType=ImageIDType.ImageType;
		}
	}

	//Tao doi tuong CAGinteractImagesMsg nhan ket qua tro ve
	CAGinteractImagesMsg SearchResultAGinteractImagesMsg;
	CAGinteractImagesMsg::DefaultInit(&SearchResultAGinteractImagesMsg);
	SearchResultAGinteractImagesMsg.SetDeleteMeInProc(agfalse);// vi khong chuyen doi tuong nay di
	SearchResultAGinteractImagesMsg.DBCnnAttach(pDBCnnI);
	SearchResultAGinteractImagesMsg.SetIsPassID(agfalse);//pass bang CAGimage
	SearchResultAGinteractImagesMsg.SetSemanticTree(NULL,agtrue);//khong su dung Semantic Tree
	SearchResultAGinteractImagesMsg.m_CandidateCount=0;//lay het, khong loc ung cu vien

	//thuc hien viec tim kiem
	agint32					iTable=0, iPage=0;
	IAGmmSearchingSystem	SS;
	IAGmarkovModel*			pAGmarkovModel=SS.GetMarkovModel();
	pAGmarkovModel->Ready(pAGmarkovModel->GetMode(),pAGmarkovModel->IsNorm());
	SS.DBCnnAttach(pDBCnnI);
	SS.Search(0/*khong pass ID*/,QueryImageType,&SearchResultAGinteractImagesMsg,iTable,iPage,&QueryImage);

	agint32 n=SearchResultAGinteractImagesMsg.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageDBItem* item=SearchResultAGinteractImagesMsg.GetAt(i);

		agtchar* oldbasedir=NULL;
		CAGmagicStrUtil::private_tcscat(oldbasedir,_T("."),agtrue);
		CAGmagicStrUtil::private_tcscat(oldbasedir,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(oldbasedir,_T(".."),agtrue);

		agtchar* newbasedir=CAGmagicConfUtil::AGmagicBaseDirAbsoluteFromBin();

		CString URL=item->m_URL;
		URL.Replace(oldbasedir, newbasedir);
		strOuts.Add(URL);

		if(oldbasedir) free(oldbasedir);
		if(newbasedir) free(newbasedir);
	}

	//huy connection toi CSDL
	CAGmagicDBUtil::CnnDestroy(pDBCnnI, agtrue);
	ASSERT(pDBCnnI==NULL);
}
void IAGmmSearchingSystem::SampleSearch(aguint_id QueryImageType, CString szImagePath, CString& strOut, CString token)
{
	CStringArray strOuts;
	SampleSearch(QueryImageType, szImagePath, strOuts);
	strOut=CAGmagicStrUtil::CatString(strOuts, token);
}

/***********************class CAGmmSearchingSystemUIWinThread****************************/

#if AGMAGIC_SUPPORT_MFC
IMPLEMENT_DYNCREATE(CAGmmSearchingSystemUIWinThread, CWinThread)

CAGmmSearchingSystemUIWinThread::CAGmmSearchingSystemUIWinThread(CWnd* pWnd, CEvent* pTempEvent) : CWinThread(), IAGmmSearchingSystem()
{
	//m_bAutoDelete=FALSE;
	m_pMainWnd=pWnd;
	CreateThread(CREATE_SUSPENDED);

	m_bIsInit=agfalse;
	m_pTempEvent=pTempEvent;
	m_bIsRunning=agfalse;
}
CAGmmSearchingSystemUIWinThread::~CAGmmSearchingSystemUIWinThread()
{
	MyCleanup();
}
void CAGmmSearchingSystemUIWinThread::Init()
{
	if(m_bIsInit)	return;
	Start();
	m_bIsInit=agtrue;
}
void CAGmmSearchingSystemUIWinThread::MyCleanup()
{
	m_bIsRunning=agfalse;
	m_bIsInit=agfalse;
	m_pTempEvent=NULL;
}
void CAGmmSearchingSystemUIWinThread::Stop()
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();
	if(!m_bIsRunning)					goto end;
	if(SuspendThread()!=0xFFFFFFFF)		m_bIsRunning=agfalse;
end:
	if(m_pTempEvent)	m_pTempEvent->SetEvent();
////////////////////////////////////////////////////////
	{
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Searching System Stopped"))
	}
}
void CAGmmSearchingSystemUIWinThread::Start()
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();
	if(m_bIsRunning)				goto end;
	if(ResumeThread()!=0xFFFFFFFF)	m_bIsRunning=agtrue;
end:
	if(m_pTempEvent)	m_pTempEvent->SetEvent();
////////////////////////////////////////////////////////
	{
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Searching System Started"))
	}
}
agbool CAGmmSearchingSystemUIWinThread::IsRunning()
{
	return m_bIsRunning;
}
BOOL CAGmmSearchingSystemUIWinThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CAGmmSearchingSystemUIWinThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	MyCleanup();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CAGmmSearchingSystemUIWinThread, CWinThread)
	//{{AFX_MSG_MAP(CAGmmSearchingSystemUIWinThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_THREAD_MESSAGE(AGMAGICIP_WM_SEARCH_REQUIRE, OnReceivedSearchRequire)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAGmmSearchingSystemUIWinThread message handlers
void CAGmmSearchingSystemUIWinThread::OnReceivedSearchRequire(WPARAM wParam, LPARAM lParam)
{
	CSingleLock			singleLock(&m_Mutex);
	singleLock.Lock();

	CAGinteractImagesMsg* pSearchRequireAGinteractImagesMsg=(CAGinteractImagesMsg*)lParam;
	ASSERT(pSearchRequireAGinteractImagesMsg!=NULL);
	{
		POST_OUTPUT_NOTICE(m_pMainWnd,_T("Searching System receive Search require from client"))
	}

	//thong bao loi
	if(pSearchRequireAGinteractImagesMsg->GetSize()!=1 || !IsRunning())
	{
		if(pSearchRequireAGinteractImagesMsg->IsDeleteMeInProc())	delete pSearchRequireAGinteractImagesMsg; pSearchRequireAGinteractImagesMsg=NULL;

		if(m_pMainWnd)	m_pMainWnd->SendMessage(AGMAGICIP_WM_SEARCH_RESULT,-1,(LPARAM)NULL);//wParam=-1: ket thuc ti tim kiem
		return;
	}

	//thuc hien viec tim kiem
	aguint_id	QueryImageID;
	aguint_id	QueryImageType;
	CAGimage*	pQueryImage;
	if(pSearchRequireAGinteractImagesMsg->IsPassID())
	{
		QueryImageID=pSearchRequireAGinteractImagesMsg->GetIDAt(0);
		QueryImageType=pSearchRequireAGinteractImagesMsg->GetAt(0)->m_ImageType;
		pQueryImage=NULL;
	}
	else
	{
		pQueryImage=pSearchRequireAGinteractImagesMsg->GetAt(0)->m_pAGimageSrc;
		if(pQueryImage==NULL)
		{
			if(pSearchRequireAGinteractImagesMsg->IsDeleteMeInProc())	delete pSearchRequireAGinteractImagesMsg; pSearchRequireAGinteractImagesMsg=NULL;

			if(m_pMainWnd)	m_pMainWnd->SendMessage(AGMAGICIP_WM_SEARCH_RESULT,-1,(LPARAM)NULL);//wParam=-1: ket thuc ti tim kiem
			return;
		}
		QueryImageID=pQueryImage->m_ID;
		QueryImageType=pSearchRequireAGinteractImagesMsg->GetAt(0)->m_ImageType;
	}

	agint32		iTable=0, iPage=0;
	agint32		iResult=0;
	while(agtrue)
	{
		CAGinteractImagesMsg* pSearchResultAGinteractImagesMsg=new CAGinteractImagesMsg();
		CAGinteractImagesMsg::DefaultInit(pSearchResultAGinteractImagesMsg);
		pSearchResultAGinteractImagesMsg->SetDeleteMeInProc(agtrue);
		pSearchResultAGinteractImagesMsg->DBCnnAttach(pSearchRequireAGinteractImagesMsg->DBCnnGet());
		pSearchResultAGinteractImagesMsg->SetIsPassID(agtrue/*pSearchRequireAGinteractImagesMsg->IsPassID()*/);

		pSearchResultAGinteractImagesMsg->SetSemanticTree(pSearchRequireAGinteractImagesMsg->m_pSemanticTree,agtrue);
		pSearchResultAGinteractImagesMsg->m_CandidateCount=pSearchRequireAGinteractImagesMsg->m_CandidateCount;

		m_pAGmarkovModel->Ready(m_pAGmarkovModel->GetMode(),m_pAGmarkovModel->IsNorm());
		Search(QueryImageID,QueryImageType,pSearchResultAGinteractImagesMsg,iTable,iPage,pQueryImage);
		if(pSearchResultAGinteractImagesMsg->GetSize()==0)//Neu khong tim thay
		{
			delete pSearchResultAGinteractImagesMsg;
			pSearchResultAGinteractImagesMsg=NULL;
		}
		else if(m_pMainWnd)
		{
			{
				POST_OUTPUT_NOTICE(m_pMainWnd,_T("Searching System send searching Results Image(s) to client"))
			}
			m_pMainWnd->SendMessage(AGMAGICIP_WM_SEARCH_RESULT,(WPARAM)iResult,(LPARAM)pSearchResultAGinteractImagesMsg);//wParam=-1: khong tim thay
			pSearchResultAGinteractImagesMsg=NULL;//xem nhu da huy
			iResult ++;
		}
		else
		{
			delete pSearchResultAGinteractImagesMsg;
			pSearchResultAGinteractImagesMsg=NULL;
		}

		if(iTable==-1 || iPage==-1)//cham dut viec tim kiem
		{
			{
				POST_OUTPUT_NOTICE(m_pMainWnd,_T("Searching System End Searching"))
			}
			if(pSearchResultAGinteractImagesMsg) delete pSearchResultAGinteractImagesMsg; pSearchResultAGinteractImagesMsg=NULL;
			if(m_pMainWnd)	m_pMainWnd->SendMessage(AGMAGICIP_WM_SEARCH_RESULT,-1,(LPARAM)NULL);//wParam=-1: ket thuc ti
			break;
		}
	}
	if(pSearchRequireAGinteractImagesMsg->IsDeleteMeInProc())	delete pSearchRequireAGinteractImagesMsg;
}
/*************Nhung vi du sample cho java*************************/

#include "vn_edu_agu_portal_channels_CTimAnh.h"
JNIEXPORT jstring JNICALL Java_vn_edu_agu_portal_channels_CTimAnh_searchImage
  (JNIEnv * env, jobject obj, jstring strImagePath)
{
	const char *str = env->GetStringUTFChars(strImagePath, false);
	CString szImagePath=str;
	CString results;
	IAGmmSearchingSystem::SampleSearch(0, szImagePath, results);
    return env->NewStringUTF((LPCTSTR)results);
}

#endif	//#if AGMAGIC_SUPPORT_MFC
