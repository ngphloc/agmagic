#if !defined(AGMMM_H__055B4D06_393B_498D_B1E1_795DC611B057__INCLUDED_)
#define AGMMM_H__055B4D06_393B_498D_B1E1_795DC611B057__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../ip/main/AGimage.h"
#include "../../ip/main/AGimageFeat.h"
#include "../../ip/main/AGimageUtil.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

#define		AGMAGICIS_UPDATE_AFF_RATIO						(1/*0.000001*/)
#define		AGMAGICIS_TRAINING_FREQ_TIME_INTERVAL_IN_SEC	120

#if AGMAGIC_SUPPORT_MFC
#define	POST_OUTPUT_NOTICE(pWndXXX,szXXX) \
{ \
	if(pWndXXX && szXXX) \
	{ \
		ASSERT(pWndXXX->IsKindOf(RUNTIME_CLASS(CFrameWnd))); \
		agtchar* szNoticeMustFreeAuto=NULL; \
		CAGmagicStrUtil::private_tcscat(szNoticeMustFreeAuto,szXXX,agtrue); \
		pWndXXX->PostMessage(AGMAGICIP_WM_RECEIVED_OUTPUT_NOTICE,0,(LPARAM)szNoticeMustFreeAuto); \
	} \
}
#else //AGMAGIC_SUPPORT_MFC
#define	POST_OUTPUT_NOTICE(pWndXXX,szXXX) \
{ \
	; \
}
#endif //AGMAGIC_SUPPORT_MFC

/*****************************************class CAGtrainingDataSet******************************/

#include <time.h>
class CAGmarkovModel;
class IAGmmTrainingSystem;
class CAGmmTrainingSystemUIWinThread;
VOID CALLBACK AGmmTrainingSystemUIWinThreadTimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

/*
class AGMAGIC_DECL CAGtrainingDataSet
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGtrainingDataSet : public CAGmagicDBOrg
{
protected:
	CAGuserAccessPatternMatrix	m_use;
	CAGuserAccessFrequencyVec	m_access;
	time_t					tAccessedBegin;
	time_t					tAccessedEnd;

	agbool					m_bIsNorm;
public:

	CAGtrainingDataSet();
	virtual ~CAGtrainingDataSet();

	void	Destroy();//thuc hien duoc moi luc
	agbool	IsBegined();//thuc hien duoc moi luc
	agbool	IsEnded();//thuc hien duoc moi luc
	agbool	IsNorm()		{return m_bIsNorm;}

	void	Begin();//thuc hien duoc moi luc tru truong hop: begined && !ended
	void	End();//chi thuc hien khi: begined

	virtual	agbool	DBRead(time_t begin, time_t end);//thuc hien duoc moi luc tru truong hop: begined && !ended
	virtual	agbool	DBInsert();//chi thuc hien khi: begined && ended
	virtual	agbool	DBUpdate();//chi thuc hien khi: begined && ended

	void			DoWhenReceivedUserAccessMessage(AGUSER_ACCESS_PATTERN_ITEM* usemk, AGUSER_ACCESS_FREQUENCY_ITEM* accessk);//chi thuc hien khi: begined && !ended
	aguint32		use(aguint_id mID, aguint_id kID, agbool throwErr=agfalse);//thuc hien luc nao cung duoc
	aguint32		access(aguint_id kID, agbool throwErr=agfalse);//thuc hien luc nao cung duoc
	agbool			affs(CAGidArray* FilterIDs, agfreal weight, CAGaffArray* aOutAff, CAGaffArray* aOutReversedAff=NULL);//thuc hien luc nao cung duoc
	agfreal		aff(aguint_id mID, aguint_id nID, agbool throwErr=agfalse);//thuc hien luc nao cung duoc
	void			ResetPatternAndFreq(aguint32 pattern_value, aguint32 freq_value);

public:
	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO, thuc hien duoc moi luc
	virtual void*	DBCnnDetach();//khong Release, thuc hien duoc moi luc

protected:
	virtual		agbool	DBDelete();//chi thuc hien khi: begined && ended
	void		GetAllImageIDsNotQuery(CAGidArray* FilterIDs, CAGidArray* aOutImageID);//thuc hien luc nao cung duoc
	void		GetAllQueryImageIDs(CAGidArray* akQueryImageID);//thuc hien luc nao cung duoc
	void		GetAllQueryImageIDs(aguint_id ImageID, CAGidArray* akQueryImageID);//thuc hien luc nao cung duoc
	void		aff_half(CAGidArray* FilterIDs, CAGidArray* aImageID, CAGidArray* akQueryImageID, agfreal weight, CAGaffArray* aOutAff);//thuc hien luc nao cung duoc
	agfreal	aff(aguint_id mID, aguint_id nID, CAGidArray* akQueryImageID, agbool throwErr=agfalse);//thuc hien luc nao cung duoc

	friend class CAGmarkovModel;
	friend class IAGmmTrainingSystem;
	friend class CAGmmTrainingSystemUIWinThread;
	friend VOID	CALLBACK AGmmTrainingSystemUIWinThreadTimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
};

/*****************************************interface IAGmarkovModel, class CAGmarkovModel******************************/
/*
class AGMAGIC_DECL IMarkovModel
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL IAGmarkovModel : public CAGmagicDBOrg
{
public:
	virtual IAGflexfMatrix*	CreateFeaturesMatrix()=0;

	virtual void	Destroy()=0;
	virtual void	Ready(aguint16 mode, agbool bIsNorm)=0;
	virtual agbool	IsReady()=0;

	virtual void		DoWhenReceivedTrainingDataSet(CAGtrainingDataSet* pDataSet, CAGidArray* FilterIDs, agfreal weight, agbool bIsReReadDBForS, agbool bForceUpdateAffAfter)=0;//chi duoc goi khi da Ready

	virtual void		UpdateAff(agfreal update_aff_rario=AGMAGICIS_UPDATE_AFF_RATIO)=0;//cap nhat tat ca: CSDL va noi tai
	virtual void		Refresh()=0;//refresh du lieu noi tai tu thao tac doc CSDL
	virtual agbool		IsNorm()=0;
	virtual	void		SetIsNorm(agbool bIsNorm)=0;

	virtual void		Normalize(CAGmarkovModel* pAGmarkovModel=NULL)=0;
	virtual void		ChangeMode(aguint16 mode, CAGmarkovModel* pAGmarkovModel=NULL)=0;//chi duoc goi khi da Ready
	virtual aguint16	GetMode()=0;//goi duoc moi luc

	virtual CAGimageDBItems*			GetImageDBItems()=0;//goi duoc moi luc
	virtual CAGimageAffMatrix*		GetAffinity()=0;//goi duoc moi luc
	virtual IAGflexfMatrix*	GetFeaturesMatrix()=0;

	virtual	agbool	DBRead(aguint_id ImageIDs[], agint32 nImageIDs, 
							agbool bIsReReady=agtrue, agbool bIsReReadImagesInfoFromDB=agtrue)=0;//chi duoc goi khi da Ready
	virtual	agbool	DBSimpleRead(aguint_id NoCoincideImageIDs[], agint32 nNoCoincideImageIDs, 
							agbool bIsReReady=agtrue, agbool bIsReReadImagesInfoFromDB_ReReadS=agtrue)=0;
	virtual agbool	Add(CAGimage* pInputAGimage, aguint_id ImageType, agbool bIsNegativeImageWhenSegment)=0;

	virtual void*	DBCnnAttach(void* pDBCnnI)=0;//khong AddRef, tra ve Connection cu doi voi ADO
	virtual void*	DBCnnDetach()=0;//khong Release
};

#define AGMAGICIS_MM_UPDATE_MODE		1
#define AGMAGICIS_MM_READONLY_MODE		2

/*
class AGMAGIC_DECL CMarkovModel
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmarkovModel : public IAGmarkovModel
{
//Tat ca moi ham deu phai thuc hien khi da goi ham Ready tru cac ham: Destroy, DBCnnAttach, DBCnnDetach, va cac ham static
protected:
	CAGimageDBItems*			m_S;//a set of images(id) called states
	CAGimageAffMatrix*		m_A;//denotes the states transition probability distribution
	IAGflexfMatrix*	m_B;//the feature matrix
	agbool						m_bIsNorm;
	aguint16					m_mode;
	time_t						m_tLastUpdated;
public:
	CAGmarkovModel();
	virtual ~CAGmarkovModel();
	virtual IAGflexfMatrix*	CreateFeaturesMatrix();

	virtual void	Destroy();//goi duoc moi luc
	virtual void	Ready(aguint16 mode, agbool bIsNorm);//goi duoc moi luc
	virtual agbool	IsReady();//goi duoc moi luc

	virtual void		DoWhenReceivedTrainingDataSet(CAGtrainingDataSet* pDataSet, CAGidArray* FilterIDs, agfreal weight, agbool bIsReReadDBForS, agbool bForceUpdateAffAfter);//chi duoc goi khi da Ready

	virtual void		UpdateAff(agfreal update_aff_ratio=AGMAGICIS_UPDATE_AFF_RATIO);//cap nhat tat ca: CSDL va noi tai, chi duoc goi khi da Ready
	virtual void		Refresh();//refresh du lieu noi tai tu thao tac doc CSDL, chi duoc goi khi da Ready
	virtual agbool		IsNorm();//goi duoc moi luc
	virtual	void		SetIsNorm(agbool bIsNorm);
	virtual void		Normalize(CAGmarkovModel* pAGmarkovModel=NULL);//chi duoc goi khi da Ready
	virtual void		ChangeMode(aguint16 mode, CAGmarkovModel* pAGmarkovModel=NULL);//chi duoc goi khi da Ready
	virtual aguint16	GetMode();//goi duoc moi luc

	virtual CAGimageDBItems*			GetImageDBItems();//goi duoc moi luc
	virtual CAGimageAffMatrix*		GetAffinity();//goi duoc moi luc
	virtual IAGflexfMatrix*	GetFeaturesMatrix();

	virtual	agbool	DBRead(aguint_id ImageIDs[], agint32 nImageIDs, 
							agbool bIsReReady=agtrue, agbool bIsReReadImagesInfoFromDB_ReReadS=agtrue);//chi duoc goi khi da Ready
	virtual	agbool	DBSimpleRead(aguint_id NoCoincideImageIDs[], agint32 nNoCoincideImageIDs, 
							agbool bIsReReady=agtrue, agbool bIsReReadImagesInfoFromDB_ReReadS=agtrue);
	virtual agbool	Add(CAGimage* pInputAGimage, aguint_id ImageType, agbool bIsNegativeImageWhenSegment);
public:
	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO. Goi duoc moi luc
	virtual void*	DBCnnDetach();//khong Release, goi duoc moi luc

protected:
	void	CopyFrom(CAGmarkovModel* AGmarkovModel);//Goi duoc moi luc
};

/*****************************************interface IAGmmSystem***************************/

class AGMAGIC_DECL IAGmmSystem : public CAGmagicDBOrg 
{
protected:
	virtual IAGmarkovModel*		CreateMarkovModel()	{throw _T("You must define");}

public:
	IAGmmSystem() : CAGmagicDBOrg()	{}
	virtual ~IAGmmSystem()			{}

	virtual IAGmarkovModel*	GetMarkovModel()		{throw _T("You must define");}

	virtual void	Init()			{throw _T("You must define");}
	virtual void	Stop()			{throw _T("You must define");}
	virtual void	Start()			{throw _T("You must define");}
	virtual agbool	IsRunning()		{throw _T("You must define");}

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO. Chi duoc goi khi da Ready
	virtual void*	DBCnnDetach();//khong Release, goi duoc moi luc
};

/***************************class IAGmmTrainingSystem***********************************/

class AGMAGIC_DECL IAGmmTrainingSystem : public IAGmmSystem
{
protected:
	IAGmarkovModel*				m_pAGmarkovModel;
	CAGtrainingDataSet*			m_pDataSet;
	virtual IAGmarkovModel*		CreateMarkovModel();

public:
	IAGmmTrainingSystem();
	virtual ~IAGmmTrainingSystem();

	IAGmarkovModel*	GetMarkovModel();

public:

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO. Chi duoc goi khi da Ready
	virtual void*	DBCnnDetach();//khong Release, goi duoc moi luc
};

/***********************************class CAGuserAccessMsg, CAGmmTrainingSystemUIWinThread**********************/

class AGMAGIC_DECL CAGuserAccessMsg
{
public:
	AGUSER_ACCESS_PATTERN_ITEM*		m_usemk;
	AGUSER_ACCESS_FREQUENCY_ITEM*	m_accessk;

	CAGuserAccessMsg()
	{
		m_usemk=NULL;
		m_accessk=NULL;
	}
	virtual ~CAGuserAccessMsg()
	{
		Destroy();
	}
	void Destroy()
	{
		if(m_usemk)		free(m_usemk);		m_usemk=NULL;
		if(m_accessk)	free(m_accessk);	m_accessk=NULL;
	}
	agbool	CopyFrom(CAGuserAccessMsg* pAGuserAccessMsg)
	{
		if(pAGuserAccessMsg==NULL)	throw _T("Invalid parameter");
		Destroy();

		if(pAGuserAccessMsg->m_usemk)
		{
			m_usemk=new AGUSER_ACCESS_PATTERN_ITEM();
			m_usemk->mID=pAGuserAccessMsg->m_usemk->mID;
			m_usemk->kID=m_usemk->kID;
			m_usemk->tAccessed=m_usemk->tAccessed;
			m_usemk->isAccess=m_usemk->isAccess;
		}

		if(pAGuserAccessMsg->m_accessk)
		{
			m_accessk=new AGUSER_ACCESS_FREQUENCY_ITEM();
			m_accessk->kID=pAGuserAccessMsg->m_accessk->kID;
			m_accessk->tAccessed=pAGuserAccessMsg->m_accessk->tAccessed;
			m_accessk->nAccessed=pAGuserAccessMsg->m_accessk->nAccessed;
		}
		return agtrue;
	}


};
class AGMAGIC_DECL CAGuserAccessMsgs : public CAGobjPtrArray<CAGuserAccessMsg>
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGuserAccessMsg();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGuserAccessMsg* pAGuserAccessMsgDst=(CAGuserAccessMsg*)dst;
		CAGuserAccessMsg* pAGuserAccessMsgSrc=(CAGuserAccessMsg*)src;
		pAGuserAccessMsgDst->CopyFrom(pAGuserAccessMsgSrc);
	}
public:
	agbool	m_bDeleteMeInProc;

	CAGuserAccessMsgs() : CAGobjPtrArray<CAGuserAccessMsg>()
	{
		m_bDeleteMeInProc=agtrue;
	}
	virtual ~CAGuserAccessMsgs()
	{
	}

};

#if AGMAGIC_SUPPORT_MFC

#include <afxmt.h>//su dung critical section, mutex

//tinh bang milisecond
#define		AGMAGICIS_RESET_TRAININGDATASET_ELAPSE_TIME_IN_MILISECS		(1000*AGMAGICIS_TRAINING_FREQ_TIME_INTERVAL_IN_SEC)
#define		AGMAGICIS_MYEVENT_WAIT_TIME_IN_MILISECS						200
		
class AGMAGIC_DECL CAGmmTrainingSystemUIWinThread : public CWinThread, public IAGmmTrainingSystem
{
	DECLARE_DYNCREATE(CAGmmTrainingSystemUIWinThread)
protected:
	CMutex		m_Mutex;
	CEvent*		m_pTempNoFreeEvent;//khong tu huy Event nay
	CEvent		m_MyEvent;

	aguint_id	m_ResetTSTimerID;

	agbool		m_bIsRunning;
	agbool		m_bIsInit;

	void		SetTimer();
	void		KillTimer();
	void		MyCleanup();
public:
	CAGmmTrainingSystemUIWinThread(CWnd* pWnd=NULL, CEvent* pTempEvent=NULL);           // protected constructor used by dynamic creation

	virtual void	Init();
	virtual void	Stop();
	virtual void	Start();
	virtual agbool	IsRunning();
	void Test();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmmTrainingSystemUIWinThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmmTrainingSystemUIWinThread();

	// Generated message map functions
	//{{AFX_MSG(CAGmmTrainingSystemUIWinThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnReceivedUserAccess(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend VOID CALLBACK	AGmmTrainingSystemUIWinThreadTimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
};
#endif	//#if AGMAGIC_SUPPORT_MFC

#endif // !defined(AGMMM_H__055B4D06_393B_498D_B1E1_795DC611B057__INCLUDED_)

