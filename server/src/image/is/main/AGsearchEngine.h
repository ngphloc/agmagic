
#if !defined(AGSEARCHENGINE_H__87FD4E83_6FEA_4F56_98CF_1345A0192C5C__INCLUDED_)
#define AGSEARCHENGINE_H__87FD4E83_6FEA_4F56_98CF_1345A0192C5C__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "AGmmm.h"

/***********************interface IAGmmSearchingSystem****************************/
#define AGMAGICIS_NUMBER_RECORDS_OF_PAGE	10000
#define AGMAGICIS_TABLE_COUNT				1
/*
class AGMAGIC_DECL IAGmmSearchingSystem
Chuc nang:
Cach dung:
Ghi chu:
*/
struct OUT_SIM
{
	agfreal		sim;
	aguint_id		id;
};
class AGMAGIC_DECL COutSim : public CAGmagicElement, public OUT_SIM
{
public:
	COutSim();
	virtual ~COutSim();

	virtual CAGmagicElement*	CreateMe();
	virtual agbool				CopyFrom(CAGmagicElement* pAGmagicElement);
	virtual aguint_id			GetID();
	virtual agfreal			GetValue();

};
class AGMAGIC_DECL CAGoutSimPtrArray : public CAGmagicElementPtrArray
{
public:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new COutSim();
	}

public:
	CAGoutSimPtrArray() : CAGmagicElementPtrArray()
	{
	}
	virtual ~CAGoutSimPtrArray()
	{
	}
};

class AGMAGIC_DECL IAGmmSearchingSystem :  public IAGmmSystem
{
protected:
	IAGmarkovModel*				m_pAGmarkovModel;
	virtual IAGmarkovModel*		CreateMarkovModel();

	agint32						m_NumberRecordsOfPage;
	agint32						m_InitPageCount;
	agint32						m_TableCount;
	
	void IncreaseTablePage(agint32& iTable, agint32& iPage);
public:
	IAGmmSearchingSystem();
	virtual ~IAGmmSearchingSystem();

	IAGmarkovModel*	GetMarkovModel();

	virtual void	PreFilter(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32 iTable, agint32 iPage);
	virtual void	PreFilterEx(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32 iTable, agint32 iPage);
	virtual void	Search(aguint_id ImageID, aguint_id ImageType, CAGinteractImagesMsg* pOutputItems, agint32& iTable, agint32& iPage, CAGimage* pInputAGimage=NULL, agint32 nFeatures=0, agfreal Threshold=0);
	
	//nhung ham vi du tim kien khong quan trong
	static void SampleSearch(aguint_id QueryImageType, CString szImagePath, CStringArray& strOuts);
	static void SampleSearch(aguint_id QueryImageType, CString szImagePath, CString& strOut, CString token=_T("@@"));

protected:
	#define AGMAGICIS_DEFAULT_ADDITIVE		AGMAGICIP_MIN_NORM_FEAT_VALUE
	static	agfreal EdgeWeightFromImage_i_ToQueryImage_q_AtFeature_t(agfreal aqi, agfreal bi[], 
															agfreal bq[], aguint32 t);

	static	agfreal SimilarityFromImage_i_ToQueryImage_q(agfreal aqi, agfreal bi[], 
												agfreal bq[], aguint32 T);
	static	int			CompareTwoSimValueInDecreaseOrder(const void* sim1, const void* sim2);
	static	int			CompareTwoSimValueInIncreaseOrder(const void* sim1, const void* sim2);
	static	OUT_SIM*	SimilarityFromCandidateImagesToQueryImage_q(agint32 C, agfreal aq[], agfreal* B[], agfreal bq[], aguint32 T, 
							aguint_id ids[], OUT_SIM*& OutSim, agint32& nOutSim, agint32 pIndexForB[]=NULL, agfreal SimThreshold=0);
};

/***********************class CAGmmSearchingSystemUIWinThread****************************/

#if AGMAGIC_SUPPORT_MFC
class AGMAGIC_DECL CAGmmSearchingSystemUIWinThread : public CWinThread , public IAGmmSearchingSystem
{
	DECLARE_DYNCREATE(CAGmmSearchingSystemUIWinThread)
protected:
	CMutex		m_Mutex;
	CEvent*		m_pTempEvent;//khong tu huy Event nay

	agbool		m_bIsRunning;
	agbool		m_bIsInit;

	void		MyCleanup();
public:
	CAGmmSearchingSystemUIWinThread(CWnd* pWnd=NULL, CEvent* pTempEvent=NULL);   // protected constructor used by dynamic creation

	virtual void	Init();
	virtual void	Stop();
	virtual void	Start();
	virtual agbool	IsRunning();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAGmmSearchingSystemUIWinThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAGmmSearchingSystemUIWinThread();

	// Generated message map functions
	//{{AFX_MSG(CAGmmSearchingSystemUIWinThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnReceivedSearchRequire(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
#endif	//#if AGMAGIC_SUPPORT_MFC

#endif // !defined(AGSEARCHENGINE_H__87FD4E83_6FEA_4F56_98CF_1345A0192C5C__INCLUDED_)
