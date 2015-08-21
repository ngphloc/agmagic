// AGimageSeg.h: interface for the CAGimageHSeg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AGIMAGESEG_H__B58F4BFD_822F_4367_A632_4DF45CD9FC8B__INCLUDED_)
#define AGIMAGESEG_H__B58F4BFD_822F_4367_A632_4DF45CD9FC8B__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "AGimage.h"
#define AGMAGICIP_DEFAULT_SEGS_CLASS	CAGimageHSegs
#define AGMAGICIP_DEFAULT_SEG_CLASS		CAGimageHSeg

/********************************class CAGimageSeg***********************************************/
class AGMAGIC_DECL CAGimageSeg : public CAGmagicDBOrg
{
protected:
	aguint_id		m_ImageID;
	virtual void	Cleanup();
public:
	CAGimage*	m_pNoFreeParentAGimage;//anh cha cua phan doan nay

	CAGimage*	m_pAGimage;//anh chua phan segment
	CAGimage*	m_pAGimageMask;//anh mask phan segment
	AGBU_RECT	m_rcBoundInsideParent_main;//vi tri cua m_pAGimage, m_pAGimageMask trong anh cha
	agint32		m_nPixels_main;//tong so pixel that su trong segment
	agint32		m_label_main;//nhan hay so thu tu hay dinh danh cua segment

	CAGimageSeg();
	virtual ~CAGimageSeg();
	agbool			IsValid();
	virtual agbool	CopyFrom(CAGimageSeg* pSrcSeg);
	AGBU_POINT		MidPoint();

	aguint_id	GetImageID();
	void		SetImageID(aguint_id ImageID);

	virtual agbool	DBInsert(){throw _T("You must code");}
	virtual agbool	DBRead(aguint_id ImageID, agint32 label){throw _T("You must code");}
	virtual agbool	DBDelete(){throw _T("You must code");}
};

/********************************class CAGimageSegs***********************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class AGMAGIC_DECL CAGimageSegs : public CAGobjPtrArray<CAGimageSeg>, public CAGmagicDBOrg
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageSeg();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageSeg* pAGimageSegDst=(CAGimageSeg*)dst;
		CAGimageSeg* pAGimageSegSrc=(CAGimageSeg*)src;
		pAGimageSegDst->CopyFrom(pAGimageSegSrc);
	}
	AGBU_RECT	m_rcBound;//tuc la left=0,top=ImageHeight,right=ImageWidth,bottom=0
	aguint_id	m_ImageID;
public:
	CAGimage*	m_pNoFreeParentAGimage;

	CAGimageSegs();
	virtual ~CAGimageSegs();
	virtual void	RemoveAll();

	aguint_id	GetImageID();
	void		SetImageID(aguint_id ImageID);

	agbool	MidPoint(CAGbaseArray<AGBU_POINT>* centers);
	void	GetNumberPixelsOfBounds(CAGint32Array* pixels);

	agbool	TextureMidPoint(CAGbuRectVec* pInRects, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures);
	agbool	TextureMidPoint(SIZE block_size, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures);
	agbool	TextureMidPoint(agint32 nRows, agint32 nCols, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures);

	virtual void SegCreate(CAGimage* pAGimage, void* pParam=NULL, CAGimage* pAGimageToSeg=NULL, void* pReserved=NULL){throw _T("You must code");}

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO
	virtual void*	DBCnnDetach();//khong Release
	
	virtual agbool	DBInsert(){throw _T("You must code");}
	virtual agbool	DBRead(aguint_id ImageID){throw _T("You must code");}
	virtual agbool	DBDelete(){throw _T("You must code");}
};

/********************************class CAGimageHSeg***********************************************/
class AGMAGIC_DECL CAGimageHSeg : public CAGimageSeg
{
protected:
	virtual void	Cleanup();
	void	UpdateImageAndMask_From_ParentImage(CAGimage* pParenAGimage, AGCLRQUAD* fill_color=NULL);
public:
	CAGbaseArray<HEURISTIC_SEG_BLOCK>	m_seg_blockA_main;

	CAGimageHSeg();
	virtual ~CAGimageHSeg();
	virtual agbool	CopyFrom(CAGimageSeg* pSrcSeg);

	virtual agbool	DBInsert();
	virtual agbool	DBRead(aguint_id ImageID, agint32 label);
	virtual agbool	DBDelete();
};

/********************************class CAGimageHSegs***********************************************/

class CAGdbHBlockMatrix;
class AGMAGIC_DECL CAGimageHSegs : public CAGimageSegs
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageHSeg();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageHSeg* pAGimageSegDst=(CAGimageHSeg*)dst;
		CAGimageHSeg* pAGimageSegSrc=(CAGimageHSeg*)src;
		pAGimageSegDst->CopyFrom(pAGimageSegSrc);
	}
	void SegCreateHeuristic(HEURISTIC_SEG_BLOCK_MATRIX* pInBlocksMatrix, CAGimage* pParenAGimage, AGCLRQUAD* fill_clr=NULL);
	void SegCreateHeuristic(CAGdbHBlockMatrix* pInDBHBlockMatrix, AGCLRQUAD* fill_clr=NULL);
	void SegCreateHeuristic(CAGimage* pAGimage, HEURISTIC_SEG_PARAM* pHSegParam=NULL, CAGimage* pAGimageToSeg=NULL, CAGdbHBlockMatrix* pOutDBHBlockMatrix=NULL, AGCLRQUAD* fill_clr=NULL);
public:

	CAGimageHSegs();
	virtual ~CAGimageHSegs();
	virtual void	RemoveAll();

	virtual void SegCreate(CAGimage* pAGimage, void* pHSegParam=NULL, CAGimage* pAGimageToSeg=NULL, void* fill_clr=NULL);

	virtual agbool	DBInsert();
	virtual agbool	DBRead(aguint_id ImageID);
	virtual agbool	DBDelete();
};

/********************************class CAGdbHBlockMatrix***********************************************/

class AGMAGIC_DECL CAGdbHBlockMatrix : public HEURISTIC_SEG_BLOCK_MATRIX, public CAGmagicDBOrg
{
protected:
	agbool m_bIsStoreImage;

public:

	HEURISTIC_SEG_PARAM			m_HSegParam;

	aguint_id					m_ParentImageID;
	CAGimage*					m_pParenImage;

	CAGdbHBlockMatrix();
	virtual ~CAGdbHBlockMatrix();
	void Destroy();

	void	CopyFrom(HEURISTIC_SEG_BLOCK_MATRIX* pBlocksMatrix, CAGimage* pParenImage);
	agbool	CopyFrom(CAGdbHBlockMatrix* pDBHBlockMatrix);

	agbool	IsStoreImage();
	void	SetIsStoreImage(agbool bIsStoreImage);

	agbool	DBInsert();
	agbool	DBRead(aguint_id ParentImageID, agbool bIsReadImage);
	agbool	DBDelete();
	agbool	DBInsertIntel();
};

#endif // !defined(AGIMAGESEG_H__B58F4BFD_822F_4367_A632_4DF45CD9FC8B__INCLUDED_)
