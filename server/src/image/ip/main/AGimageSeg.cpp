#include "AGimageSeg.h"
#include "AGimageUtil.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

/*******************************CAGimageSeg***************************************/

CAGimageSeg::CAGimageSeg() : CAGmagicDBOrg()
{
	m_pNoFreeParentAGimage=NULL;
	m_pAGimage=NULL;
	m_pAGimageMask=NULL;
	memset(&m_rcBoundInsideParent_main,0,sizeof(AGBU_RECT));
	m_nPixels_main=0;
	m_label_main=0;
	m_ImageID=0;
}
CAGimageSeg::~CAGimageSeg()
{
	Cleanup();
}
agbool CAGimageSeg::IsValid()
{
	return (m_pAGimage!=NULL && m_nPixels_main>0);
}
void CAGimageSeg::Cleanup()
{
	m_pNoFreeParentAGimage=NULL;
	if(m_pAGimage)				delete m_pAGimage;				m_pAGimage=NULL;
	if(m_pAGimageMask)			delete m_pAGimageMask;			m_pAGimageMask=NULL;
	memset(&m_rcBoundInsideParent_main,0,sizeof(AGBU_RECT));
	m_nPixels_main=0;
	m_label_main=0;
	m_ImageID=0;
}
agbool CAGimageSeg::CopyFrom(CAGimageSeg* pSrcSeg)
{
	if(pSrcSeg==NULL)	throw _T("Invalid parameter");
	Cleanup();
	if(!pSrcSeg->IsValid())	return agfalse;

	m_pNoFreeParentAGimage=pSrcSeg->m_pNoFreeParentAGimage;

	m_pAGimage=pSrcSeg->m_pAGimage->CreateMe();
	m_pAGimage->Copy(pSrcSeg->m_pAGimage);
	memcpy(&m_rcBoundInsideParent_main,&(pSrcSeg->m_rcBoundInsideParent_main),sizeof(AGBU_RECT));

	m_pAGimageMask=pSrcSeg->m_pAGimageMask->CreateMe();
	m_pAGimageMask->Copy(pSrcSeg->m_pAGimageMask);

	m_nPixels_main=pSrcSeg->m_nPixels_main;
	m_label_main=pSrcSeg->m_label_main;
	DBCnnAttach(pSrcSeg->m_pDBCnnI);
	m_ImageID=pSrcSeg->m_ImageID;
	return agtrue;
}
AGBU_POINT CAGimageSeg::MidPoint()
{
	AGBU_POINT center;
	center.x=m_rcBoundInsideParent_main.left + (m_rcBoundInsideParent_main.right-m_rcBoundInsideParent_main.left)/2;
	center.y=m_rcBoundInsideParent_main.bottom + (m_rcBoundInsideParent_main.top-m_rcBoundInsideParent_main.bottom)/2;
	return center;
}

aguint_id CAGimageSeg::GetImageID()
{
	return m_ImageID;
}
void CAGimageSeg::SetImageID(aguint_id ImageID)
{
	m_ImageID=ImageID;
}

/********************************class CAGimageSegs***********************************************/
#include "AGimageFeat.h"
CAGimageSegs::CAGimageSegs() : CAGobjPtrArray<CAGimageSeg>(), CAGmagicDBOrg()
{
	memset(&m_rcBound,0,sizeof(AGBU_RECT));
	m_pNoFreeParentAGimage=NULL;
	m_ImageID=0;
}
CAGimageSegs::~CAGimageSegs()
{
	RemoveAll();
}
void CAGimageSegs::RemoveAll()
{
	memset(&m_rcBound,0,sizeof(AGBU_RECT));
	m_pNoFreeParentAGimage=NULL;
	CAGobjPtrArray<CAGimageSeg>::RemoveAll();
	m_ImageID=0;
}
aguint_id CAGimageSegs::GetImageID()
{
	return m_ImageID;
}
void CAGimageSegs::SetImageID(aguint_id ImageID)
{
	m_ImageID=ImageID;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSeg* seg=GetAt(i);
		if(seg) seg->SetImageID(ImageID);
	}
}
agbool CAGimageSegs::MidPoint(CAGbaseArray<AGBU_POINT>* centers)
{
	if(centers==NULL)	throw _T("Invalid parameter");
	centers->RemoveAll();
	if(m_ne==0)			return agfalse;

	centers->SetSize(m_ne);
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageSeg* seg=m_vector[i];
		centers->SetAt(i,seg->MidPoint());
	}
	return (centers->GetSize() > 0);
}
void CAGimageSegs::GetNumberPixelsOfBounds(CAGint32Array* pixels)
{
	if(pixels==NULL)	throw _T("Invalid parameter");
	pixels->RemoveAll();
	if(m_ne==0)				return;

	pixels->SetSize(m_ne);
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageSeg* seg=m_vector[i];
		pixels->SetAt(i,seg->m_nPixels_main);
	}
}

agbool CAGimageSegs::TextureMidPoint(CAGbuRectVec* pInRects, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures)
{
	pOutTextures->RemoveAll();

	CAGbaseArray<AGBU_POINT> centers;
	if(!MidPoint(&centers))	return agfalse;

	CAGint32Array center_pixels;
	GetNumberPixelsOfBounds(&center_pixels);
	if(center_pixels.GetSize()==0)		return agfalse;

	agint32 nTotalPixels=(m_rcBound.right-m_rcBound.left)*(m_rcBound.top-m_rcBound.bottom);
	if(nTotalPixels<0)	throw _T("Fatal error");
	if(nTotalPixels==0)	return agfalse;

	return CAGfeatUtil::TextureMidPoint(&centers,				pInRects, 
						&center_pixels,			nTotalPixels, 
						ExcludePixelsPercent,	pOutTextures);
}
agbool	CAGimageSegs::TextureMidPoint(SIZE block_size, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures)
{
	pOutTextures->RemoveAll();

	CAGbaseArray<AGBU_POINT> centers;
	if(!MidPoint(&centers))	return agfalse;
	
	CAGint32Array center_pixels;
	GetNumberPixelsOfBounds(&center_pixels);
	if(center_pixels.GetSize()==0)		return agfalse;

	agint32 nTotalPixels=(m_rcBound.right-m_rcBound.left)*(m_rcBound.top-m_rcBound.bottom);
	if(nTotalPixels<0)	throw _T("Fatal error");
	if(nTotalPixels==0)	return agfalse;

	return CAGfeatUtil::TextureMidPoint(&centers,			m_rcBound,		block_size, 
						&center_pixels,			nTotalPixels, 
						ExcludePixelsPercent,	pOutTextures);
}
agbool	CAGimageSegs::TextureMidPoint(agint32 nRows, agint32 nCols, agreal64 ExcludePixelsPercent, CAGreal64Array* pOutTextures)
{
	pOutTextures->RemoveAll();

	CAGbaseArray<AGBU_POINT> centers;
	if(!MidPoint(&centers))	return agfalse;

	CAGint32Array center_pixels;
	GetNumberPixelsOfBounds(&center_pixels);
	if(center_pixels.GetSize()==0)		return agfalse;

	agint32 nTotalPixels=(m_rcBound.right-m_rcBound.left)*(m_rcBound.top-m_rcBound.bottom);
	if(nTotalPixels<0)	throw _T("Fatal error");
	if(nTotalPixels==0)	return agfalse;

	return CAGfeatUtil::TextureMidPoint(&centers, m_rcBound,		nRows, nCols, 
						&center_pixels,			nTotalPixels, 
						ExcludePixelsPercent,	pOutTextures);
}
void* CAGimageSegs::DBCnnAttach(void* pDBCnnI)//khong AddRef doi voi ADO
{
	void*	old=CAGmagicDBOrg::DBCnnAttach(pDBCnnI);

	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSeg* seg=GetAt(i);
		if(seg) seg->DBCnnAttach(pDBCnnI);
	}
	return old;
}
void* CAGimageSegs::DBCnnDetach()//khong Release
{
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageSeg* seg=GetAt(i);
		if(seg) seg->DBCnnDetach();
	}
	return CAGmagicDBOrg::DBCnnDetach();
}
/*******************************CAGimageHSeg***************************************/

CAGimageHSeg::CAGimageHSeg() : CAGimageSeg()
{
}
CAGimageHSeg::~CAGimageHSeg()
{
	Cleanup();
}
void CAGimageHSeg::Cleanup()
{
	CAGimageSeg::Cleanup();
	m_seg_blockA_main.RemoveAll();
}
agbool CAGimageHSeg::CopyFrom(CAGimageSeg* pSrcSeg)
{
	Cleanup();
	agbool			bIsSuccess=CAGimageSeg::CopyFrom(pSrcSeg);
	CAGimageHSeg*	pSrcHSeg=(CAGimageHSeg*)pSrcSeg;
	m_seg_blockA_main.CopyFrom(&(pSrcHSeg->m_seg_blockA_main));
	return bIsSuccess;
}
agbool CAGimageHSeg::DBInsert()
{
	if(m_ImageID==0) return agfalse;
	agtchar* SQL=NULL;

//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSeg"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,
		_T("(ImageID, label, nBlocks, nTotalPixels, lBound, tBound, rBound, bBound) VALUES("),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_label_main,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_seg_blockA_main.GetSize(),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);
	
	CAGmagicStrUtil::private_tcscat(SQL,m_nPixels_main,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBoundInsideParent_main.left,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBoundInsideParent_main.top,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBoundInsideParent_main.right,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBoundInsideParent_main.bottom,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;

//////////////////
	agint32 n=m_seg_blockA_main.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		HEURISTIC_SEG_BLOCK block=m_seg_blockA_main.GetAt(i);

		CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHBlock"),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,
			_T("(ImageID, label, idx, lBound, tBound, rBound, bBound, EX, CX, GrayLevel) VALUES("),agtrue);

		CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,m_label_main,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,i,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.area.left,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.area.top,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.area.right,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.area.bottom,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.EX,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.CX,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

		CAGmagicStrUtil::private_tcscat(SQL,block.GrayLevel,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

		CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
		if(SQL) free(SQL); SQL=NULL;
	}
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimageHSeg::DBRead(aguint_id ImageID, agint32 label)
{
	Cleanup();
	if(ImageID==0) return agfalse;

	agtchar* SQL=NULL;

///////////////////////HBlockMatrixIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSeg"),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND label="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,label,agtrue);

	aguint_id*	data=NULL;
	agint32		n=0;
	AGdbRead(m_pDBCnnI, SQL, agfalse, data, n);
	if(SQL) free(SQL); SQL=NULL;
	if(data==NULL)	return agfalse;

	m_ImageID=data[0];
	m_label_main=(agint32)data[1];
	agint32 nBlocks=(agint32)data[2];
	m_nPixels_main=(agint32)data[3];
	m_rcBoundInsideParent_main.left=(agint_xcoord)data[4];
	m_rcBoundInsideParent_main.top=(agint_bu_ycoord)data[5];
	m_rcBoundInsideParent_main.right=(agint_xcoord)data[6];
	m_rcBoundInsideParent_main.bottom=(agint_bu_ycoord)data[7];

	free(data); data=NULL;

	if(nBlocks>0)
	{
		m_seg_blockA_main.SetSize(nBlocks);
		for(agint32 i=0; i<nBlocks; i++)
		{
			HEURISTIC_SEG_BLOCK block;
			memset(&block,0,sizeof(HEURISTIC_SEG_BLOCK));

			CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHBlock"),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND label="),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,m_label_main,agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND idx="),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,i,agtrue);

			agreal64*	data=NULL;
			agint32		n=0;
			AGdbRead(m_pDBCnnI, SQL, agfalse, data, n);
			if(SQL) free(SQL); SQL=NULL;
			if(data==NULL)	throw _T("Fatal Error");

			block.label=m_label_main;
			block.area.left=(agint_xcoord)data[3];
			block.area.top=(agint_bu_ycoord)data[4];
			block.area.right=(agint_xcoord)data[5];
			block.area.bottom=(agint_bu_ycoord)data[6];
			block.EX=data[7];
			block.CX=data[8];
			block.GrayLevel=data[9];
	
			m_seg_blockA_main.SetAt(i,block);

			free(data); data=NULL;
		}
	}
	if(SQL) free(SQL); SQL=NULL;

	CAGimage ParentImage;
	if(CAGimageDBUtil::Load(ImageID,m_pDBCnnI,&ParentImage))
		UpdateImageAndMask_From_ParentImage(&ParentImage);
	return agtrue;
}
agbool CAGimageHSeg::DBDelete()
{
	throw _T("Implement not yet");
}
/*
Ham nay cap nhat m_pAGimage va m_pAGimageMask khi 
tat ca bien cac thanh vien khac deu duoc xac dinh
*/
void CAGimageHSeg::UpdateImageAndMask_From_ParentImage(CAGimage* pParenAGimage, AGCLRQUAD* fill_color)
{
	if(pParenAGimage==NULL) return;
	agint32  n=m_seg_blockA_main.GetSize();
	if(n==0) return;

	if(m_pAGimage) delete m_pAGimage;
	m_pAGimage=pParenAGimage->CreateMe();

	RECT rcCropBound;
	COPY_RECT_TO_RECT(rcCropBound,m_rcBoundInsideParent_main)
	rcCropBound.bottom=pParenAGimage->GetHeight()-rcCropBound.bottom;
	rcCropBound.top=pParenAGimage->GetHeight()-rcCropBound.top;
	pParenAGimage->Crop(rcCropBound,m_pAGimage);

	//toan bo m_pAGimage la duoc khoi tao la 0
	m_pAGimage->SelectionDelete();
	if(fill_color)
		m_pAGimage->FillColor(*fill_color);
	else
		m_pAGimage->FillColor(m_pAGimage->RGBtoRGBQUAD(RGB(0,0,0)));

	m_pAGimage->Init();

	//toan bo m_pAGimageMask la duoc khoi tao la 0
	aguint32 bound_width=m_rcBoundInsideParent_main.right- m_rcBoundInsideParent_main.left;
	aguint32 bound_height=m_rcBoundInsideParent_main.top- m_rcBoundInsideParent_main.bottom;
	if(bound_width!=m_pAGimage->GetWidth() || bound_height!=m_pAGimage->GetHeight())
		throw _T("Fatal error");
	if(m_pAGimageMask) delete m_pAGimageMask;
	m_pAGimageMask=new CAGimage(bound_width, bound_height, 8);
	m_pAGimageMask->Init();

	for(agint32 k=0; k<n; k++)
	{
		HEURISTIC_SEG_BLOCK block=m_seg_blockA_main.GetAt(k);
		CAGimage* pBlockAGimage=pParenAGimage->CreateMe();

		RECT rcCropBlock;
		COPY_RECT_TO_RECT(rcCropBlock,block.area)
		rcCropBlock.bottom=pParenAGimage->GetHeight()-rcCropBlock.bottom;
		rcCropBlock.top=pParenAGimage->GetHeight()-rcCropBlock.top;
		pParenAGimage->Crop(rcCropBlock,pBlockAGimage);

		pBlockAGimage->Init();
		aguint32 w=block.area.right-block.area.left;
		aguint32 h=block.area.top-block.area.bottom;
		if(w!=pBlockAGimage->GetWidth() || h!=pBlockAGimage->GetHeight())
			throw _T("Fatal error");

		//seg->m_pAGimage
		agint_xcoord	xOffset=block.area.left   - m_rcBoundInsideParent_main.left;
		agint_bu_ycoord yOffset=block.area.bottom - m_rcBoundInsideParent_main.bottom;
		if(xOffset<0 || yOffset<0)	throw _T("Fatal error");
		m_pAGimage->MixFrom(*pBlockAGimage, xOffset, yOffset);
		delete pBlockAGimage;

		//seg->m_pAGimageMask
		AGBU_RECT rcFill;
		rcFill.left=xOffset;
		rcFill.bottom=yOffset;
		rcFill.right=xOffset+ w;
		rcFill.top=yOffset+ h;
		m_pAGimageMask->SelectionDelete();
		m_pAGimageMask->SelectionAddRect(rcFill);
		AGCLRQUAD clr={0,0,0,0};
		clr.rgbRed=clr.rgbGreen=clr.rgbBlue=255;

		m_pAGimageMask->FillColor(clr);
	}
}

/********************************class CAGimageHSegs***********************************************/

CAGimageHSegs::CAGimageHSegs() : CAGimageSegs()
{
}
CAGimageHSegs::~CAGimageHSegs()
{
	RemoveAll();
}
void CAGimageHSegs::RemoveAll()
{
	CAGimageSegs::RemoveAll();
}
void CAGimageHSegs::SegCreateHeuristic(HEURISTIC_SEG_BLOCK_MATRIX* pInBlocksMatrix, CAGimage* pParenAGimage, AGCLRQUAD* fill_clr)
{
	if(pInBlocksMatrix==NULL)	throw _T("Invalid parameter");
	RemoveAll();

	HEURISTIC_SEG_BLOCK**	blocks=pInBlocksMatrix->m_blocks;
	agint32					rows=pInBlocksMatrix->m_rows_of_blocks;
	agint32					cols=pInBlocksMatrix->m_cols_of_blocks;
	if(blocks==NULL || rows==0 || cols==0)	return;

	agint32					maxLabel=-1;
	agint_bu_ycoord			i;
	agint_xcoord			j;
	for(i=0; i<rows; i++)
		for(j=0; j<cols; j++)
			if(maxLabel<blocks[i][j].label)	maxLabel=blocks[i][j].label;
	if(maxLabel==-1 || maxLabel==0)	return;

	agint32 label;
	//tai m_rcBound
	m_rcBound.left=m_rcBound.bottom=m_rcBound.right=m_rcBound.top=0;
	for(label=1; label<=maxLabel; label++)
	{
		CAGimageHSeg* seg=new CAGimageHSeg();
		seg->DBCnnAttach(m_pDBCnnI);
		seg->m_pNoFreeParentAGimage=pParenAGimage;
		seg->m_label_main=label;

		agbool	bFirstMeetLabel=agfalse;
		for(i=0; i<rows; i++)
		{
			for(j=0; j<cols; j++)
			{
				// tao m_rcBound
				m_rcBound.right=AGMAX(m_rcBound.right,blocks[i][j].area.right);
				m_rcBound.top=AGMAX(m_rcBound.top,blocks[i][j].area.top);

				if(blocks[i][j].label!=label)	continue;
				if(!bFirstMeetLabel)
				{
					seg->m_rcBoundInsideParent_main.left=blocks[i][j].area.left;
					seg->m_rcBoundInsideParent_main.bottom=blocks[i][j].area.bottom;

					seg->m_rcBoundInsideParent_main.right=blocks[i][j].area.right;
					seg->m_rcBoundInsideParent_main.top=blocks[i][j].area.top;
					bFirstMeetLabel=agtrue;
				}
				else
				{
					seg->m_rcBoundInsideParent_main.left=AGMIN(seg->m_rcBoundInsideParent_main.left,blocks[i][j].area.left);
					seg->m_rcBoundInsideParent_main.bottom=AGMIN(seg->m_rcBoundInsideParent_main.bottom,blocks[i][j].area.bottom);

					seg->m_rcBoundInsideParent_main.right=AGMAX(seg->m_rcBoundInsideParent_main.right,blocks[i][j].area.right);
					seg->m_rcBoundInsideParent_main.top=AGMAX(seg->m_rcBoundInsideParent_main.top,blocks[i][j].area.top);
				}

				agint32 block_pixels=(blocks[i][j].area.right-blocks[i][j].area.left) * (blocks[i][j].area.top-blocks[i][j].area.bottom);
				if(block_pixels <= 0)	throw _T("Fatatl error");

				seg->m_nPixels_main +=block_pixels;
				seg->m_seg_blockA_main.Add(blocks[i][j]);
			}
		}
		agint32 n=seg->m_seg_blockA_main.GetSize();
		if(n==0)
		{
			delete seg;
			continue;
		}
		//seg da co m_pNoFreeParentAGimage, m_rcBoundInsideParent_main, m_nPixels_main, m_seg_blockA_main, m_label_main, m_ImageID
		//chi con thieu m_pAGimage, va m_pAGimageMask
		if(pParenAGimage)
		{
			seg->m_pAGimage=pParenAGimage->CreateMe();

			RECT rcCropBound;
			COPY_RECT_TO_RECT(rcCropBound,seg->m_rcBoundInsideParent_main)
			rcCropBound.bottom=pParenAGimage->GetHeight()-rcCropBound.bottom;
			rcCropBound.top=pParenAGimage->GetHeight()-rcCropBound.top;
			pParenAGimage->Crop(rcCropBound,seg->m_pAGimage);

			seg->m_pAGimage->SelectionDelete();
			if(fill_clr)
				seg->m_pAGimage->FillColor(*fill_clr);
			else
				seg->m_pAGimage->FillColor(seg->m_pAGimage->RGBtoRGBQUAD(RGB(0,0,0)));
			seg->m_pAGimage->Init();

			aguint32 bound_width=seg->m_rcBoundInsideParent_main.right- seg->m_rcBoundInsideParent_main.left;
			aguint32 bound_height=seg->m_rcBoundInsideParent_main.top- seg->m_rcBoundInsideParent_main.bottom;
			if(bound_width!=seg->m_pAGimage->GetWidth() || bound_height!=seg->m_pAGimage->GetHeight())
				throw _T("Fatal error");
			seg->m_pAGimageMask=new CAGimage(bound_width, bound_height, 8);
			seg->m_pAGimageMask->Init();

			for(agint32 k=0; k<n; k++)
			{
				HEURISTIC_SEG_BLOCK block=seg->m_seg_blockA_main.GetAt(k);
				CAGimage* pBlockAGimage=pParenAGimage->CreateMe();

				RECT rcCropBlock;
				COPY_RECT_TO_RECT(rcCropBlock,block.area)
				rcCropBlock.bottom=pParenAGimage->GetHeight()-rcCropBlock.bottom;
				rcCropBlock.top=pParenAGimage->GetHeight()-rcCropBlock.top;
				pParenAGimage->Crop(rcCropBlock,pBlockAGimage);

				pBlockAGimage->Init();
				aguint32 w=block.area.right-block.area.left;
				aguint32 h=block.area.top-block.area.bottom;
				if(w!=pBlockAGimage->GetWidth() || h!=pBlockAGimage->GetHeight())
					throw _T("Fatal error");

				//seg->m_pAGimage
				agint_xcoord	xOffset=block.area.left   - seg->m_rcBoundInsideParent_main.left;
				agint_bu_ycoord yOffset=block.area.bottom - seg->m_rcBoundInsideParent_main.bottom;
				if(xOffset<0 || yOffset<0)	throw _T("Fatal error");
				seg->m_pAGimage->MixFrom(*pBlockAGimage, xOffset, yOffset);
				delete pBlockAGimage;

				//seg->m_pAGimageMask
				AGBU_RECT rcFill;
				rcFill.left=xOffset;
				rcFill.bottom=yOffset;
				rcFill.right=xOffset+ w;
				rcFill.top=yOffset+ h;
				seg->m_pAGimageMask->SelectionDelete();
				seg->m_pAGimageMask->SelectionAddRect(rcFill);
				AGCLRQUAD clr={0,0,0,0};
				clr.rgbRed=clr.rgbGreen=clr.rgbBlue=255;

				seg->m_pAGimageMask->FillColor(clr);
			}
		}
		Add(seg);
	}

	m_rcBound.left=0;
	m_rcBound.bottom=0;
	m_rcBound.right=pParenAGimage->GetWidth();
	m_rcBound.top=pParenAGimage->GetHeight();

	m_pNoFreeParentAGimage=pParenAGimage;
}
void CAGimageHSegs::SegCreateHeuristic(CAGdbHBlockMatrix* pInDBHBlockMatrix, AGCLRQUAD* fill_clr)
{
	if(pInDBHBlockMatrix==NULL)	throw _T("Invalid parameter");

	if(pInDBHBlockMatrix->m_pParenImage)
		SegCreateHeuristic(pInDBHBlockMatrix,pInDBHBlockMatrix->m_pParenImage, fill_clr);
	else if(pInDBHBlockMatrix->m_ParentImageID!=0)
	{
		CAGimage* pParenImage=new CAGimage();
		if(!CAGimageDBUtil::Load(pInDBHBlockMatrix->m_ParentImageID,pInDBHBlockMatrix->DBCnnGet(),pParenImage))
		{
			delete pParenImage;
			pParenImage=NULL;
		}
		SegCreateHeuristic(pInDBHBlockMatrix,pParenImage,fill_clr);
	}
	else
		SegCreateHeuristic(pInDBHBlockMatrix,NULL,fill_clr);
}
void CAGimageHSegs::SegCreateHeuristic(CAGimage* pAGimage, HEURISTIC_SEG_PARAM* pHSegParam, 
									   CAGimage* pAGimageToSeg, CAGdbHBlockMatrix* pOutDBHBlockMatrix, 
									   AGCLRQUAD* fill_clr)
{
	if(pAGimage==NULL)	throw _T("Invalid parameter");
	if(pAGimageToSeg!=NULL)
	{
		if(pAGimageToSeg->GetWidth()!=pAGimage->GetWidth() ||
		   pAGimageToSeg->GetHeight()!=pAGimage->GetHeight() )
		   throw _T("Fatal error");
	}
	RemoveAll();

	HEURISTIC_SEG_PARAM HSegParam;
	if(pHSegParam==NULL)
	{
		INIT_HEURISTIC_SEG_PARAM(HSegParam)
		pHSegParam=&HSegParam;
	}

	HEURISTIC_SEG_BLOCK_MATRIX BlockMatrix;
	INIT_HEURISTIC_SEG_BLOCK_MATRIX(BlockMatrix)

	if(pAGimageToSeg!=NULL)
	{
		if(pAGimageToSeg->HeuristicSeg(pHSegParam,NULL,&BlockMatrix,NULL)==0)
			return;
	}
	else
	{
		if(pAGimage->HeuristicSeg(pHSegParam,NULL,&BlockMatrix,NULL)==0)
			return;
	}
	if(pOutDBHBlockMatrix)
	{
		pOutDBHBlockMatrix->CopyFrom(&BlockMatrix,pAGimage);
	}
	SegCreateHeuristic(&BlockMatrix,pAGimage,fill_clr);
	DESTROY_HEURISTIC_SEG_BLOCK_MATRIX(BlockMatrix)

}
void CAGimageHSegs::SegCreate(CAGimage* pAGimage, void* pHSegParam, CAGimage* pAGimageToSeg, void* fill_clr)
{
	SegCreateHeuristic(pAGimage, (HEURISTIC_SEG_PARAM*)pHSegParam, pAGimageToSeg, NULL, (AGCLRQUAD*)fill_clr);
}

agbool CAGimageHSegs::DBInsert()
{
	if(m_ImageID==0) return agfalse;

//////////////////
	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSegIns"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,
		_T("(ImageID, nSegs, lBound, tBound, rBound, bBound) VALUES("),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,GetSize(),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBound.left,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBound.top,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBound.right,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rcBound.bottom,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;
//////////////////

	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageHSeg* seg=(CAGimageHSeg*)GetAt(i);
		if(seg) seg->DBInsert();
	}
	return agtrue;
}
agbool CAGimageHSegs::DBRead(aguint_id ImageID)
{
	RemoveAll();
	if(ImageID==0) return agfalse;

	agtchar* SQL=NULL;

///////////////////////HBlockMatrixIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSegIns"),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	aguint_id*	data=NULL;
	agint32		n=0;
	AGdbRead(m_pDBCnnI, SQL, agfalse, data, n);
	if(SQL) free(SQL); SQL=NULL;
	if(data==NULL)	return agfalse;

	m_ImageID=data[0];
	agint32	nSegs=(agint32)data[1];
	m_rcBound.left=(agint_xcoord)data[2];
	m_rcBound.top=(agint_bu_ycoord)data[3];
	m_rcBound.right=(agint_xcoord)data[4];
	m_rcBound.bottom=(agint_bu_ycoord)data[5];

	free(data); data=NULL;
	if(nSegs==0) return agtrue;
/////////////////////////////

	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSeg"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	agint32* labels=NULL;
	AGdbReadOneField(m_pDBCnnI, SQL, 1,agfalse, labels, n);
	if(SQL) free(SQL); SQL=NULL;
	if(labels==NULL || n!=nSegs) throw _T("Fatal Error");
	for(agint32 i=0; i<n ;i++)
	{
		CAGimageHSeg* seg=new CAGimageHSeg();
		seg->DBCnnAttach(m_pDBCnnI);
		seg->DBRead(ImageID,labels[i]);
		Add(seg);
	}
	free(labels); labels=NULL;

/////////////////////////////
	return agtrue;
}
agbool	CAGimageHSegs::DBDelete()
{
	if(m_ImageID==0) return agfalse;
	agtchar* SQL=NULL;

///////////////////////ImageHBlock//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHBlock"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;

///////////////////////ImageHSeg//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSeg"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;

///////////////////////ImageHSegIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("ImageHSegIns"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;

	return agtrue;
}
/*******************************class CAGdbHBlockMatrix***************************************/

CAGdbHBlockMatrix::CAGdbHBlockMatrix() : CAGmagicDBOrg()
{
	INIT_HEURISTIC_SEG_PARAM(m_HSegParam)
	m_blocks=NULL;
	m_rows_of_blocks=m_cols_of_blocks=0;
	m_ParentImageID=0;
	m_pParenImage=NULL;
	m_bIsStoreImage=agfalse;
}
CAGdbHBlockMatrix::~CAGdbHBlockMatrix()
{
	Destroy();
}
void CAGdbHBlockMatrix::Destroy()
{
	INIT_HEURISTIC_SEG_PARAM(m_HSegParam)
	DESTROY_HEURISTIC_SEG_BLOCK_ARRAYPTR(m_blocks,m_rows_of_blocks,m_cols_of_blocks)
	m_rows_of_blocks=m_cols_of_blocks=0;

	m_ParentImageID=0;
	if(m_pParenImage) delete m_pParenImage; m_pParenImage=NULL;
}

void CAGdbHBlockMatrix::CopyFrom(HEURISTIC_SEG_BLOCK_MATRIX* pBlocksMatrix, CAGimage* pParenImage)
{
	Destroy();

	if(pBlocksMatrix->m_blocks && 
	   pBlocksMatrix->m_rows_of_blocks>0 && pBlocksMatrix->m_cols_of_blocks>0)
	{
		m_rows_of_blocks=pBlocksMatrix->m_rows_of_blocks;
		m_cols_of_blocks=pBlocksMatrix->m_cols_of_blocks;
		INIT_HEURISTIC_SEG_BLOCK_ARRAYPTR(m_blocks,m_rows_of_blocks,m_cols_of_blocks)
		for(agint_bu_ycoord i=0; i<m_rows_of_blocks; i++)
		{
			for(agint_xcoord j=0; j<m_cols_of_blocks; j++)
				memcpy(&(m_blocks[i][j]),&(pBlocksMatrix->m_blocks[i][j]),sizeof(HEURISTIC_SEG_BLOCK));
		}
	}

	if(pParenImage && m_bIsStoreImage)
	{
		m_ParentImageID=pParenImage->m_ID;
		m_pParenImage=pParenImage->CreateMe();
		m_pParenImage->Copy(pParenImage);
	}
}
agbool CAGdbHBlockMatrix::CopyFrom(CAGdbHBlockMatrix* pDBHBlockMatrix)
{
	Destroy();
	if(pDBHBlockMatrix) return agtrue;

	m_HSegParam=pDBHBlockMatrix->m_HSegParam;
	CopyFrom(pDBHBlockMatrix, pDBHBlockMatrix->m_pParenImage);
	m_ParentImageID=pDBHBlockMatrix->m_ParentImageID;
	DBCnnAttach(pDBHBlockMatrix->m_pDBCnnI);
	return agtrue;
}
agbool	CAGdbHBlockMatrix::IsStoreImage()
{
	return m_bIsStoreImage;
}
void CAGdbHBlockMatrix::SetIsStoreImage(agbool bIsStoreImage)
{
	m_bIsStoreImage=bIsStoreImage;
}

agbool	CAGdbHBlockMatrix::DBInsert()
{
	agtchar* SQL=NULL;

///////////////////////HBlockMatrixIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrixIns"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,
		_T("(ImageID, rows, cols, cx, cy, hCrude, ThresholdEdge, hEX, hSJ, dKR, hEKCK) VALUES("),agtrue);

	CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_rows_of_blocks,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_cols_of_blocks,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(") "),agtrue);
	
	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.block_size.cx,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.block_size.cy,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.hCrude,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.thresholdEdge,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.hEX,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.hSJ,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.dKR,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,m_HSegParam.hEKCK,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	

	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	if(SQL) free(SQL); SQL=NULL;


///////////////////////HBlockMatrix//////////////////
	for(agint_bu_ycoord i=0; i<m_rows_of_blocks; i++)
	{
		for(agint_xcoord j=0; j<m_cols_of_blocks; j++)
		{
			HEURISTIC_SEG_BLOCK	block=m_blocks[i][j];

			CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrix"),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,
				_T("(ImageID, row, col, left, top, right, bottom, EX, CX, GrayLevel, label) VALUES("),agtrue);
		
			CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentImageID,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,i,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,j,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.area.left,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.area.top,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.area.right,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.area.bottom,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.EX,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);
			
			CAGmagicStrUtil::private_tcscat(SQL,block.CX,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.GrayLevel,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,block.label,agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);

			CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
			if(SQL) free(SQL); SQL=NULL;
		}
	}
///////////////////////HBlockMatrix//////////////////

	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGdbHBlockMatrix::DBRead(aguint_id ParentImageID, agbool bIsReadImage)
{
	Destroy();
	agtchar* SQL=NULL;

///////////////////////HBlockMatrixIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrixIns"),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ParentImageID,agtrue);

	agreal64*	data=NULL;
	agint32		n=0;
	AGdbRead(m_pDBCnnI, SQL, agfalse, data, n);
	if(data==NULL)
	{
		if(SQL) free(SQL); SQL=NULL;
		return agfalse;
	}

	m_ParentImageID=(aguint_id)data[0];
	m_rows_of_blocks=(agint32)data[1];
	m_cols_of_blocks=(agint32)data[2];
	if(m_rows_of_blocks > 0 && m_cols_of_blocks > 0)
	{
		INIT_HEURISTIC_SEG_BLOCK_ARRAYPTR(m_blocks,m_rows_of_blocks,m_cols_of_blocks)
	}

	m_HSegParam.block_size.cx=(agint32)data[3];
	m_HSegParam.block_size.cy=(agint32)data[4];
	m_HSegParam.hCrude=(agint32)data[5];
	m_HSegParam.thresholdEdge=data[6];
	m_HSegParam.hEX=data[7];
	m_HSegParam.hSJ=data[8];
	m_HSegParam.dKR=data[9];
	m_HSegParam.hEKCK=data[10];

	if(data) free(data); data=NULL;

	if(bIsReadImage && m_bIsStoreImage)
	{
		m_pParenImage=new CAGimage();
		if(!CAGimageDBUtil::Load(m_ParentImageID,m_pDBCnnI,m_pParenImage))
		{
			delete m_pParenImage;
			m_pParenImage=NULL;
		}
	}
	if(SQL) free(SQL); SQL=NULL;

///////////////////////HBlockMatrix//////////////////
	for(agint_bu_ycoord i=0; i<m_rows_of_blocks; i++)
	{
		for(agint_xcoord j=0; j<m_cols_of_blocks; j++)
		{
			HEURISTIC_SEG_BLOCK	block;
			memset(&block,0,sizeof(HEURISTIC_SEG_BLOCK));

			CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrix"),agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
			CAGmagicStrUtil::private_tcscat_id(SQL,ParentImageID,agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND row="),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,i,agtrue);

			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND col="),agtrue);
			CAGmagicStrUtil::private_tcscat(SQL,j,agtrue);

			agreal64*	data=NULL;
			agint32		n=0;
			AGdbRead(m_pDBCnnI, SQL, agfalse, data, n);
			if(data==NULL) throw _T("Fata Error");

			block.area.left=(agint_xcoord)data[3];				//vung
			block.area.top=(agint_bu_ycoord)data[4];			//vung
			block.area.right=(agint_xcoord)data[5];				//vung
			block.area.bottom=(agint_bu_ycoord)data[6];			//vung
			block.EX=(agint32)data[7];					//mat do bien
			block.CX=(agint32)data[8];					//do tho
			block.GrayLevel=(agint32)data[9];			//muc xam
			block.label=(agint32)data[10];				//nhan

			m_blocks[i][j]=block;

			if(data) free(data); data=NULL;
			if(SQL) free(SQL); SQL=NULL;
		}
	}

	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGdbHBlockMatrix::DBDelete()
{
	agtchar* SQL=NULL;

///////////////////////HBlockMatrixIns//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrixIns"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentImageID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

	if(SQL) free(SQL); SQL=NULL;

///////////////////////HBlockMatrix//////////////////
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("HBlockMatrix"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ParentImageID,agtrue);
	CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

	if(SQL) free(SQL); SQL=NULL;
	return agtrue;

}
agbool CAGdbHBlockMatrix::DBInsertIntel()
{
	CAGdbHBlockMatrix	DBHBlockMatrix;
	if(!DBHBlockMatrix.DBRead(m_ParentImageID,agfalse))
		DBInsert();
	else
	{
		DBDelete();
		DBInsert();
	}
	return agtrue;
}