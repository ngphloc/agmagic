#if !defined(AGSEMANTIC_H__A2325CDB_D4B8_4E3C_9BE3_62E694ED1166__INCLUDED_)
#define AGSEMANTIC_H__A2325CDB_D4B8_4E3C_9BE3_62E694ED1166__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "AGimage.h"
#include "AGimageUtil.h"

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

/***********************class CAGimageSemantic, class CAGimageSemanticInfo****************************/

class AGMAGIC_DECL CAGimageSemanticInfo : public CAGmagicDBOrg
{
public:
	aguint_id				m_SemanticID;
	agtchar*				m_Descs;

	CAGimageSemanticInfo();
	virtual ~CAGimageSemanticInfo();
	void	Destroy();
	
	void	Create(aguint_id SemanticID, agtchar* Descs);

	agbool	CopyFrom(CAGimageSemanticInfo*	pSrc);
	agbool	DBRead(aguint_id SemanticID);
	agbool	DBInsert();
	agbool	DBDelete();
};

class AGMAGIC_DECL CAGimageSemantic : public CAGmagicDBOrg
{
protected:
	agbool	DBRead(agtchar SQL[], agbool bIsMoveLast=agfalse);

public:
	static	agtchar	szSemanticTable[32];
	static	agtchar	szSemanticInfoTable[32];
	static	agtchar	szImagesSemanticTable[32];
	static	agtchar	szImagesSemanticWeightTable[32];

	aguint_id				m_ID;
	agtchar*				m_Name;
	aguint_id				m_ParentID;
	aguint_id				m_ImageType;

	CAGimageSemanticInfo*	m_pInfo;

	CAGimageSemantic();
	virtual ~CAGimageSemantic();
	void	Destroy();

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO
	virtual void*	DBCnnDetach();//khong Release

	agbool	CopyFrom(CAGimageSemantic*	pSrc);
	agbool	DBSemanticRead(aguint_id SemanticID);
	agbool	DBImageTypeTopLevelRead(aguint_id ImageType);
	agbool	DBInsert(agbool bReRead=agfalse);
	agbool	DBDelete();

	void	Create(aguint_id ID, agtchar Name[], aguint_id ParentID, aguint_id ImageType, CAGimageSemanticInfo* pInfo=NULL);
	void	Create(aguint_id ID, agtchar Name[], aguint_id ParentID, aguint_id ImageType, agtchar Descs[]);

	void	ExportXML(agtchar szFirstAlign[], agtchar*& xml);

	static void DBUpdateSemanticOfImage(void* pDBCnnI, aguint_id ImageID, agint32 Threshold=4);
	static void DBUpdateSemanticOfImages(void* pDBCnnI, aguint_id ImageType, agint32 Threshold=4);
};

/***********************class CAGimages_Semantic****************************/

class AGMAGIC_DECL CAGimages_Semantic : public CAGmagicDBOrg
{
public:
	aguint_id m_ImageID;
	aguint_id m_SemanticID;

	CAGimages_Semantic();
	virtual ~CAGimages_Semantic();
	
	void Reset();

	agbool	DBReadAndTest(agtchar SQL[]);
	agbool	DBReadAndTest(aguint_id ImageID, aguint_id SemanticID);
	agbool	DBInsert();
	agbool	DBInsertIntel();
	agbool	DBDelete();
	agbool	DBMove(aguint_id NewImageID, aguint_id NewSemanticID);
	agbool	DBMoveIntel(aguint_id NewImageID, aguint_id NewSemanticID);

	static	void	DBReadImageIDsFromSemantic(void* pDBCnnI, aguint_id SemanticID, CAGimageIDs* pOutImageIDs);
	static	void	DBReadImageIDsFromSemanticEx(void* pDBCnnI, aguint_id SemanticID, CAGimageIDs* pOutImageIDs);
	static	void	DBReadSemanticsFromImageID(void* pDBCnnI, aguint_id ImageID, CAGidArray* pOutSemanticIDs);
};

class AGMAGIC_DECL CAGimages_SemanticWeight : public CAGmagicDBOrg
{
public:
	aguint_id	m_ImageID;
	aguint_id	m_SemanticID;
	agreal64	m_Weight;

	CAGimages_SemanticWeight();
	virtual ~CAGimages_SemanticWeight();

	void Reset();

	agbool	DBReadAndTest(agtchar SQL[]);
	agbool	DBReadAndTest(aguint_id ImageID, aguint_id SemanticID);
	agbool	DBInsert();
	agbool	DBUpdate();
	agbool	DBUpdateIntel();
	agbool	DBUpdateIntelAccum(agreal64 accum_weight);
};

/***********************class CAGimageSemanticNodeData, CAGimageSemanticNode****************************/

class CAGimageSemanticNodeData
{
public:

	CAGimageSemantic*	m_pSemantic;
	CAGimageIDs*		m_pImageIDs;
	agreal64			m_weight;

	CAGimageSemanticNodeData();
	virtual ~CAGimageSemanticNodeData();
	void Destroy();

	agbool	CopyFrom(CAGimageSemanticNodeData*	pSrc);
	void ExportXML(agtchar szFirstAlign[], agtchar*& xml);
};

class AGMAGIC_DECL CAGimageSemanticNode
{
protected:
	virtual CAGobjPtrArray<CAGimageSemanticNode>* CreateChilds();

public:
	//noi dung
	CAGimageSemanticNodeData*				m_pData;

	//contro
	CAGimageSemanticNode*					m_pParent;
	CAGobjPtrArray<CAGimageSemanticNode>*	m_pChilds;//luon luon khac NULL

	CAGimageSemanticNode();
	virtual ~CAGimageSemanticNode();

	CAGimageSemantic*	GetSemantic();
	CAGimageIDs*		GetIDs();

	agbool				IsHaveIDs();
	agbool				IsHaveChilds();

	agreal64			GetWeight();
	agbool				SetWeight(agreal64 weight);

	void	ExportXML(agtchar* szAutoFreeFirstAlign, agtchar*& xml);
	agbool	CopyFrom(CAGimageSemanticNode*	pSrc);

	void	DBUpdateSemanticWeight(void* pDBCnnI, aguint_id ImageID, agbool bIsReset);
	void	GetTotalWeightAndNode(agreal64& sum_weight, aguint32& sum_node);
};


/***********************class CAGimageSemanticNodes****************************/

class AGMAGIC_DECL CAGimageSemanticNodes : public CAGobjPtrArray<CAGimageSemanticNode>
{
protected:

	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageSemanticNode();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		//CAGimageSemanticNode*	pSemanticDst=(CAGimageSemanticNode*)dst;
		//CAGimageSemanticNode*	pSemanticSrc=(CAGimageSemanticNode*)src;
		//pSemanticDst->CopyFrom(pSemanticSrc);
		throw _T("Implement not yet");
	}

public:
	CAGimageSemanticNodes();
	virtual ~CAGimageSemanticNodes();
};

/***********************class CAGimageSemanticTree****************************/

#if AGMAGIC_SUPPORT_MFC
class CAGsemanticOptionsTree;
class CAGsemanticCheckedTree;
#endif //AGMAGIC_SUPPORT_MFC
class AGMAGIC_DECL CAGimageSemanticTree : public CAGmagicDBOrg
{
protected:
	CAGimageSemanticNode*	m_pRoot;
	static CAGimageSemanticNode*	newNode(agbool bIsNewSemantic, void* pDBCnnI, agbool bIsNewImageIDs);
	static CAGimageSemanticNode*	newNode(CAGimageSemantic* pSemantic);

	static agbool					InsertNode(CAGimageSemanticNode* pParentNode, CAGimageSemanticNode* pNode);
	static CAGimageSemanticNode*	InsertSemantic(CAGimageSemanticNode* pParentNode, CAGimageSemantic* pSemantic);
	CAGimageSemanticNode*			InsertImageID(aguint_id ImageID, aguint_id	SemanticID);

	CAGimageSemanticNode*	FindNode(CAGimageSemanticNode* pFirstNode, aguint_id SemanticID);

	void	DBBuild(CAGimageSemanticNode* pFirstNode);
	void    Traverse(CAGimageSemanticNode* pFirstNode, void (*DoTask)(CAGimageSemanticNode* pNode, void* pReserved1, void* pReserved2), void* pReserved1=NULL, void* pReserved2=NULL);
	void	OutputXML(CAGoutputConsole* pConsole);

	static void CollectSemanticIDs(CAGimageSemanticNode* pFirstNode, void* pDBCnnI, agbool bIsShrinkTree, CAGimageIDs* pOutImageIDs);
public:

	CAGimageSemanticTree();
	virtual ~CAGimageSemanticTree();
	void Destroy();

	aguint_id GetImageType();

	CAGimageSemanticNode*	FindNode(aguint_id SemanticID);
	void	DBBuild(aguint_id ImageType, agbool bIsInsertImageIDs=agfalse);

	static	void	DBReadSemantics(void* pDBCnnI, agtchar SQL[], CAGobjPtrArray<CAGimageSemantic>* pSemantics);
	static	void	DBReadTopLevelSemantics(void* pDBCnnI, CAGobjPtrArray<CAGimageSemantic>* pTopLevelSemantics);
	static	void	DBReadSemanticsFromParentID(void* pDBCnnI, aguint_id ParentID, CAGobjPtrArray<CAGimageSemantic>* pSemantics);

	static void DBDeleteSemanticsRecure(void* pDBCnnI, aguint_id SemanticID);
	static void DBDeleteSemanticsRecure(void* pDBCnnI);
	static void	DBResetAndInsertSampleTopLevelSemantics(void* pDBCnnI);
	static void	DBResetAndInsertSampleTopLevelImageIDs(void* pDBCnnI);

	void	ExportXML(agtchar*& xml);
	void	OutputXML(agtchar szFilePath[]);

	agbool	CopyFrom(CAGimageSemanticTree*	pSrcTree);
	agbool	IsEmpty();

	void		CollectSemanticIDs(agbool bIsShrinkTree, CAGimageIDs* pOutImageIDs);
	void		DBUpdateSemanticWeight(aguint_id ImageID, agbool bIsReset);
	agreal64	GetNormWeight();

#if AGMAGIC_SUPPORT_MFC
	friend class CAGsemanticOptionsTree;
	friend class CAGsemanticCheckedTree;
#endif //AGMAGIC_SUPPORT_MFC
};


#endif // !defined(AGSEMANTIC_H__A2325CDB_D4B8_4E3C_9BE3_62E694ED1166__INCLUDED_)
