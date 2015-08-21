// AGimage.h: interface for the CAGimage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AGIMAGE_H__92EF1325_2CB0_4CFD_9DCC_AA5670CAFB59__INCLUDED_)
#define AGIMAGE_H__92EF1325_2CB0_4CFD_9DCC_AA5670CAFB59__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

/************************Cac define buoc phai khai bao*******************************************/

/************************Cac import thu vien*******************************************/

/************************Cac include*******************************************/

#include "AGimageDefs.h"

/************************Cac define chung*******************************************/

/************************Mot so khai bao kieu *******************************************/

/************************Luoc do dinh nghia cac lop*******************************************/
class AGMAGIC_DECL CxImage;
	class AGMAGIC_DECL CAGimage;
		class AGMAGIC_DECL CAGimageGrayScale;
		class AGMAGIC_DECL CAGimageMultiPlans;

/********************************class CAGimage***********************************************/

//Gia tri lon nhat cua RGB2GRAY, RGB2GRAY duoc define trong tep ximage.h
#define MAX_RGB2GRAY					RGB2GRAY(255,255,255)

//dinh nghia cac type cua cac lop
//class CAGimage
#define	AGMAGICIP_BASE_CLASSTYPE			1
//class CAGimageGrayScale
#define	AGMAGICIP_GRAYSCALE_CLASSTYPE		2
//class CAGimageMultiPlans
#define	AGMAGICIP_MULTIPLANS_CLASSTYPE		3

#define AGMAGICIP_NEW_AND_COPY(pAGimageHere,pAGimageParam) \
{ \
	switch(pAGimageParam->GetClassType()) \
	{ \
		case AGMAGICIP_BASE_CLASSTYPE: \
			pAGimageHere=new CAGimage(); \
			break; \
		case AGMAGICIP_GRAYSCALE_CLASSTYPE: \
			pAGimageHere=new CAGimageGrayScale(); \
			break; \
		case AGMAGICIP_MULTIPLANS_CLASSTYPE: \
			pAGimageHere=new CAGimageMultiPlans(); \
			break; \
		default: \
			pAGimageHere=new CAGimage(); \
	} \
	pAGimageHere->Copy(pAGimageParam); \
}

#define AGMAGICIP_NEW(pAGimageHere,AGimageClassTypeHere) \
{ \
	switch(AGimageClassTypeHere) \
	{ \
		case AGMAGICIP_BASE_CLASSTYPE: \
			pAGimageHere=new CAGimage(); \
			break; \
		case AGMAGICIP_GRAYSCALE_CLASSTYPE: \
			pAGimageHere=new CAGimageGrayScale(); \
			break; \
		case AGMAGICIP_MULTIPLANS_CLASSTYPE: \
			pAGimageHere=new CAGimageMultiPlans(); \
			break; \
		default: \
			pAGimageHere=new CAGimage(); \
	} \
}

//dinh nghia khoi tao cac thong so phuc vu cho //////////////
//ham HeuristicSeg(phan doan theo phuong phap Heuristic)/////
/////////////////////////////////////////////////////////////
#define DEFAULT_HEURISTIC_SEG_RESOLX		24
#define DEFAULT_HEURISTIC_SEG_RESOLY		24

//block_size neu co gia tri >0 : chinh la kich thuoc 1 khoi tinh bang pixel
//block_size neu co gia tri <0 : chinh la kich thuoc 1 khoi tinh ti le so voi kich thuoc anh. 
							//VD: resol.cx=-10 nghia la resol.cx=cheu rong cua anh chia cho 10
//dKR chinh la delta(K,R)
#define INIT_HEURISTIC_SEG_PARAM(param) \
{ \
	param.block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX; \
	param.block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY; \
    param.hCrude=4; \
	param.thresholdEdge=0.15; \
	param.hEX=0.25; \
	param.hSJ=1.0; \
	param.dKR=1.0; \
	param.hEKCK=0.7; \
}
#define INIT_HEURISTIC_SEG_PARAMPTR(ptrParam) \
{ \
	if(ptrParam!=NULL) \
	{ \
		ptrParam->block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX; \
		ptrParam->block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY; \
		ptrParam->hCrude=4; \
		ptrParam->thresholdEdge=0.10; \
		ptrParam->hEX=0.25; \
		ptrParam->hSJ=1.0; \
		ptrParam->dKR=1.0; \
		ptrParam->hEKCK=0.7; \
	} \
}

//khoi tao mang HEURISTIC_SEG_BLOCK 2 chieu
#define INIT_HEURISTIC_SEG_BLOCK_ARRAYPTR(pARRAY,M,N) \
{ \
	pARRAY=(HEURISTIC_SEG_BLOCK**)malloc(M*sizeof(HEURISTIC_SEG_BLOCK*));/*new HEURISTIC_SEG_BLOCK*[M];*/ \
	for(agint32 i=0; i<(agint32)M; i++) \
		pARRAY[i]=(HEURISTIC_SEG_BLOCK*)malloc(N*sizeof(HEURISTIC_SEG_BLOCK)); /*new HEURISTIC_SEG_BLOCK[N];*/ \
}

//Huy mang HEURISTIC_SEG_BLOCK 2 chieu
#define DESTROY_HEURISTIC_SEG_BLOCK_ARRAYPTR(pARRAY,M,N) \
{ \
	if(pARRAY) \
	{ \
		for(agint32 i=0; i<(agint32)M; i++) \
			free(pARRAY[i]); \
		free(pARRAY); \
		pARRAY=NULL; \
	} \
}

#define INIT_HEURISTIC_SEG_BLOCK_MATRIX(xxxMatrix) \
{ \
	xxxMatrix.m_blocks=NULL; \
	xxxMatrix.m_rows_of_blocks=xxxMatrix.m_cols_of_blocks=0; \
}

#define INIT_HEURISTIC_SEG_BLOCK_MATRIXPTR(pxxxMatrix) \
{ \
	if(pxxxMatrix==NULL) \
		pxxxMatrix=(HEURISTIC_SEG_BLOCK_MATRIX*)malloc(sizeof(HEURISTIC_SEG_BLOCK_MATRIX)); \
	pxxxMatrix->m_blocks=NULL; \
	pxxxMatrix->m_rows_of_blocks=pxxxMatrix->m_cols_of_blocks=0; \
}

#define DESTROY_HEURISTIC_SEG_BLOCK_MATRIX(xxxMatrix) \
{ \
	DESTROY_HEURISTIC_SEG_BLOCK_ARRAYPTR(xxxMatrix.m_blocks,xxxMatrix.m_rows_of_blocks,xxxMatrix.m_cols_of_blocks); \
	xxxMatrix.m_rows_of_blocks=xxxMatrix.m_cols_of_blocks=0; \
}

#define DESTROY_HEURISTIC_SEG_BLOCK_MATRIXPTR(pxxxMatrix,bDeleteMe) \
{ \
	DESTROY_HEURISTIC_SEG_BLOCK_ARRAYPTR(pxxxMatrix->m_blocks,pxxxMatrix->m_rows_of_blocks,pxxxMatrix->m_cols_of_blocks); \
	pxxxMatrix->m_rows_of_blocks=pxxxMatrix->m_cols_of_blocks=0; \
	if(bDeleteMe) \
	{ \
		delete pxxxMatrix; \
		pxxxMatrix=NULL; \
	} \
}

enum enum_colorspace
{
	AGMAGICIP_COLORSPACE_UNKNOWN = -1,
	AGMAGICIP_COLORSPACE_RGB = 0,
	AGMAGICIP_COLORSPACE_HSL = 1,
	AGMAGICIP_COLORSPACE_YUV = 2,
	AGMAGICIP_COLORSPACE_YIQ = 3,
	AGMAGICIP_COLORSPACE_XYZ = 4,
	AGMAGICIP_COLORSPACE_CMYK =5
};

typedef AGMAGIC_DECL struct tagHEURISTIC_SEG_PARAM
{
	SIZE		block_size;//kich thuoc cua mot khoi
	agint32		hCrude;//chinh la thong so h trong thuat toan tinh do tho: 
				   //AreaGetCrudeLevel(agint32 h), SelectionGetCrudeLevel(agint32 h). hCrude mac dinh 4
	agreal64	thresholdEdge;//nguong de tinh mat do bie, day la thong so trong ham tinh mat do bien: 
						  //SelectionGetEdgeDensity(agreal64 threshold), 
						  //AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc)
	agreal64	hEX;//nguong cua mat do bien cua khoi X: E(X) < 25%=hEX (mac dinh)
	agreal64	hSJ;//nguong cua tong mot do bien va do tho cua khoi J: S(J)=E(J)+C(J)>1.0=hSJ (mac dinh)
	agreal64	dKR;//thong so delta cua khoi K: delta(K,Rj)=E(K) + C(K) + H(K,Rj) > 1.0 = hKR (mac dinh)
	agreal64	hEKCK;//thong so do tho va mat do bien cua khoi K: E(K) + C(K) > 0.7=hEKCK (mac dinh)
} HEURISTIC_SEG_PARAM ;

typedef AGMAGIC_DECL struct tagHEURISTIC_SEG_BLOCK
{
	AGBU_RECT	area;				//vung
	agreal64	EX;					//mat do bien
	agreal64	CX;					//do tho
	agreal64	GrayLevel;			//muc xam
	agint32		label;				//nhan
} HEURISTIC_SEG_BLOCK;

typedef AGMAGIC_DECL struct tagHEURISTIC_SEG_BLOCK_MATRIX
{
	HEURISTIC_SEG_BLOCK**	m_blocks;
	agint32					m_rows_of_blocks;
	agint32					m_cols_of_blocks;

} HEURISTIC_SEG_BLOCK_MATRIX;

/********************************class CAGimage***********************************************/

/*
class AGMAGIC_DECL CAGimage : public CxImage  
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimage : public CxImage
{
protected:
	enum_colorspace		m_eColorSpace;//khong gian mau
public:
	aguint_id			m_ID;

	//Constructors
	CAGimage(aguint32 imagetype = 0);
	CAGimage(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype = 0);
	CAGimage(const CAGimage &src, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);
	CAGimage(const agtchar * filename, aguint32 imagetype);
	CAGimage(FILE * stream, aguint32 imagetype);
	CAGimage(CxFile * stream, aguint32 imagetype);
	CAGimage(aguint8 * buffer, aguint32 size, aguint32 imagetype);
	
	agbool Load(const agtchar* url, aguint32 imagetype=0);

	//Class Type
	virtual aguint32	GetClassType()	{return AGMAGICIP_BASE_CLASSTYPE;}
	virtual	CAGimage*	CreateMe()		{return new CAGimage();}
	//initialization
	virtual void Init();//Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau 
						//khi ham Load. Ham nay duoc goi ngay sau khi doi tuong duoc khoi tao, day 
						//la ham ao nen no se duoc ovverride o cac lop devired, khong nen goi ham 
						//nay ngay sau khi khoi tao vi ban than cac ham khoi tao da goi ham Init nay 
						//.Noi chung la ham nay chi duoc goi sau khi goi cac ham Initialization cua 
						//CxImage nhu: Create, Clear, Copy, CreateFromHBITMAP, CreateFromHICON, 
						//CreateFromHANDLE, CreateFromARGB, Transfer
	virtual void Copy(CAGimage* psrc, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);
	virtual void Copy(CxImage* psrc, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);
	//void	MixFromNoTrans(CAGimage* pAGimage, agint_xcoord lXOffset, agint_bu_ycoord lYOffset);

public:
	//Destructors
	virtual ~CAGimage();
	virtual void Destroy();//Ham huy

	//MFC Support
#if AGMAGIC_SUPPORT_MFC
	virtual void Serialize(CArchive& ar, aguint32 imagetype=0);// overridden for document i/o
#endif	//#if AGMAGIC_SUPPORT_MFC

	//Color conversion utilities
	AGCLRQUAD CMYKtoRGB(AGCLRQUAD lCMYKColor);//Chuyen 1 mau tu CMYK sang RGB
	AGCLRQUAD RGBtoCMYK(AGCLRQUAD lRGBColor);//Chuyen 1 mau tu RGB sang CMYK
	AGCLRQUAD COLORSPACEtoCOLORSPACE(enum_colorspace from, enum_colorspace to, AGCLRQUAD abc);//Chuyen 
										//gia tri mau "abc" tu khong gian mau "from" den khong gian mau "to"

	enum_colorspace GetColorSpace();//Lay khong gian mau hien hanh bao gom cac tri 	
						//AGMAGICIP_COLORSPACE_UNKNOWN, AGMAGICIP_COLORSPACE_RGB, AGMAGICIP_COLORSPACE_HSL, 
						//AGMAGICIP_COLORSPACE_YUV, AGMAGICIP_COLORSPACE_YIQ , AGMAGICIP_COLORSPACE_XYZ, 
						//AGMAGICIP_COLORSPACE_CMYK

	virtual agbool	SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate);//Dat khong gian mau 
						//hien hanh bao gom cac tri AGMAGICIP_COLORSPACE_UNKNOWN, 
						//AGMAGICIP_COLORSPACE_RGB, AGMAGICIP_COLORSPACE_HSL, AGMAGICIP_COLORSPACE_YUV, 
						//AGMAGICIP_COLORSPACE_YIQ , AGMAGICIP_COLORSPACE_XYZ, AGMAGICIP_COLORSPACE_CMYK
	virtual agbool	FillColor(AGCLRQUAD abc);

	
	//Pixel operation
	virtual aguint8 GetPixelMaxI();//Lay gia tri lon nhat co the co cua muc xam 1 pixel
	virtual aguint8 GetPixelI(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y
	virtual aguint8 GetPixelIFast(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y. Ham 
									//nay giong nhu ham GetPixelI(agint_xcoord x, agint_bu_ycoord y) nhung se 
									//xu ly nhanh hon do khong kiem tra rang buoc
	agreal64	GetPixelNormI(agint_xcoord x, agint_bu_ycoord y);//Lay nang luong cua pixel tai vi tri x, y(nang luong 
												 //la muc xam duoc chuan hoa ve [0,1])
	agreal64	GetPixelNormIFast(agint_xcoord x, agint_bu_ycoord y);
	agreal64	GetPixelAverage(agint_xcoord x, agint_bu_ycoord y, agint32 k, AGBU_RECT* prc);//Lay tri trung binh tai x,y voi he so k theo 
		//cong thuc Ak(x,y)=Xichma(j=x-2^(k-1), j=x+2^(k-1)-1, Xichma(i=y-2^(k-1), i=y+2^(k-1)-1, f(j,i)))

	//Selection
#if CXIMAGE_SUPPORT_SELECTION
	bool		SelectionAddRect(AGBU_RECT bur);
	agint32		SelectionGetNumPixels();//Lay tong so pixels cua vung pSelection
	agreal64	SelectionGetEdgeDensity(agreal64 threshold, agbool bIsOneOf);//Lay mat do bien cua vung pSelection theo 
													   //nguong threshhold
	agreal64	SelectionGetNormI();//Lay nang luong cua cua vung pSelection (nang luong o day chi 
								   //muc xam duoc chuan hoa ve doan [0,1])
	agreal64	SelectionGetCrudeLevel(agint32 h);//Lay do tho cua vung pSelection voi he so h
#endif
	agbool	AreaIsInside(AGBU_RECT* prc, agint_xcoord x, agint_bu_ycoord y);//Kiem tra xem pixel tai toa do (x,y) co nam 
														//trong vung hinh chu nhat(prc) khong?
	agbool	AreaIsInside(AGTD_RECT* prc, agint_xcoord x, agint_td_ycoord y);//Kiem tra xem pixel tai toa do (x,y) co nam 
														//trong vung hinh chu nhat(prc) khong?
	void		AreaAdjust(AGBU_RECT* prc);//dieu chinh vung prc cho phu hop voi kich thuoc anh
	agreal64	AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc, agbool bIsOneOf);//Lay mat do bien cua vung hinh 
										//chu nhat,mat do bien nay duoc chuan hoa ve [0,1]
	agreal64	AreaGetNormI(AGBU_RECT* prc=NULL);//Lay nang luong cua cua vung hinh chua nhat prc (nang 
							//luong o day chi muc xam duoc chuan hoa ve doan [0,1]), nang luong 
							//nay duoc chuan hoa trong doan [0,1]
	agreal64	AreaGetCrudeLevel(agint32 h, AGBU_RECT* prc=NULL);//Lay do tho cua vung hinh chu nhat prc voi 
											//he so h, do tho nay duoc chuan hoa trong doan [0,1]
	
	//Neighbor
	aguint8	GetNeighbor8Pixels(AGBU_POINT xy, AGBU_POINT pNeighborPixels[8]);

	//Heuristic Segmentation
	virtual agint32	HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, HEURISTIC_SEG_BLOCK_MATRIX* pOutBlocksMatrix=NULL, aguint8* pReserved=NULL);//Ham nay phan doan anh theo Heuristic
private:
	void		HeuristicSegVisit(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT*& curBlock, aguint16& nCurBlock, agreal64 dKR, agreal64 hEKCK);
	aguint8		GetNeighbor8Blocks(SIZE rowscols_of_blocks, AGBU_POINT curBlock, AGBU_POINT pNeighborBlock8[8]);
	aguint16	HeuristicNeighborBlocks(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT* curBlocks, aguint16 nCurBlocks, AGBU_POINT*& pNeighborBlocks);
public:
};

/********************************class CAGimageGrayScale***********************************************/

/*
class AGMAGIC_DECL CAGimageGrayScale : public CAGimage
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageGrayScale : public CAGimage
{
	aguint8	m_nPixelMaxValue;
public:
	//Constructors
	CAGimageGrayScale(aguint32 imagetype = 0);
	CAGimageGrayScale(aguint32 dwWidth, aguint32 dwHeight, aguint32 imagetype = 0);
	CAGimageGrayScale(const CAGimageGrayScale &src, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);
	CAGimageGrayScale(const agtchar * filename, aguint32 imagetype);
	CAGimageGrayScale(FILE * stream, aguint32 imagetype);
	CAGimageGrayScale(CxFile * stream, aguint32 imagetype);
	CAGimageGrayScale(aguint8 * buffer, aguint32 size, aguint32 imagetype);

	//Class Type
	virtual aguint32	GetClassType() {return AGMAGICIP_GRAYSCALE_CLASSTYPE;}
	virtual	CAGimage*	CreateMe()		{return new CAGimageGrayScale();}

	//initialization
	virtual void Init();//Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau khi 
				 //ham Load. Ham nay duoc goi ngay sau khi doi tuong duoc khoi tao, day la ham ao nen 
				 //no se duoc ovverride o cac lop devired. Khong nen goi ham nay ngay sau khi khoi 
				 //tao vi ban than cac ham khoi tao da goi ham Init nay. Noi chung la ham nay chi 
				 //duoc goi sau khi goi cac ham Initialization cua CxImage nhu:  Create, Clear, Copy, 
				 //CreateFromHBITMAP, CreateFromHICON, CreateFromHANDLE, CreateFromARGB, Transfer
	virtual void Copy(CAGimage* psrc, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);

public:
	//Destructors
	virtual ~CAGimageGrayScale();
	virtual void Destroy();//Ham huy

	//Color conversion utilities
	virtual agbool	SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate);//Ham nay override ham 
					//lop cha, no se throw 1 exception do trong anh gray scale khong gian mau khong co ngu nghia

	//Pixel operation
	virtual aguint8 GetPixelMaxI();//Lay gia tri lon nhat co the co cua muc xam 1 pixel. Ham nay 
									  //override lop cha
	virtual aguint8 GetPixelI(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y. Ham 
													 //nay override lop cha CAGimage
	virtual aguint8 GetPixelIFast(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y. 
				   //Ham nay override lop cha CAGimage. Ham nay giong nhu ham GetPixelI(agint_xcoord x, agint_bu_ycoord y) 
				   //nhung se xu ly nhanh hon do khong kiem tra rang buoc
	void	SetPixelMaxI(aguint8 value);//Dat gia tri lon nhat cho muc xam 1 pixel
	void	SetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8 value);//Dat gia tri cho 1 pixel
	void	SetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8 value);//Dat gia tri cho 1 pixel. Ham nay 
			//giong nhu ham SetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8 value) nhung nhanh hon do khong 
			//kiem tra rang buoc
	#define GET_BU_PIXEL_VALUE_FAST(xxx,yyy)		(info.pImage[(yyy)*info.dwEffWidth + (xxx)])
	#define SET_BU_PIXEL_VALUE_FAST(xxx,yyy,vvv)	(info.pImage[(yyy)*info.dwEffWidth + (xxx)]=(vvv))
	#define GET_INSIDE_DATA							(info.pImage)
};

/********************************class CAGimageMultiPlans***********************************************/

#define		AGMAGICIP_MULTIPLANS_INSIDEMODE		0
#define		AGMAGICIP_MULTIPLANS_PLANSMODE		1

#define		AGMAGICIP_AND_HEURISTIC_ORDER_RELATE	AGMAKE_UINT32(AGMAGICIP_AND_AND3,AGMAGICIP_FIRST_SECOND_THIRD3)
#define		AGMAGICIP_OR_HEURISTIC_ORDER_RELATE		AGMAKE_UINT32(AGMAGICIP_OR_OR3,AGMAGICIP_FIRST_SECOND_THIRD3)

enum enum_heuristic_order
{
	AGMAGICIP_FIRST_SECOND_THIRD3 = 1, 
	AGMAGICIP_FIRST_THIRD_SECOND3 = 2,	
	AGMAGICIP_SECOND_FIRST_THIRD3 = 3,	
	AGMAGICIP_SECOND_THIRD_FIRST3 = 4, 
	AGMAGICIP_THIRD_FIRST_SECOND3 = 5,	
	AGMAGICIP_THIRD_SECOND_FIRST3 = 6,
};
enum enum_heuristic_relate
{
	AGMAGICIP_AND_AND3 = 1, AGMAGICIP_AND_OR3 = 2,	AGMAGICIP_AND_XOR3 = 3,	
	AGMAGICIP_OR_AND3  = 4, AGMAGICIP_OR_OR3  = 5,	AGMAGICIP_OR_XOR3 = 6,
	AGMAGICIP_XOR_AND3 = 7, AGMAGICIP_XOR_OR3 = 8,	AGMAGICIP_XOR_XOR3 = 9	
};
/*
class AGMAGIC_DECL CAGimageMultiPlans : public CAGimage
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageMultiPlans : public CAGimage
{
protected:
	CAGimageGrayScale*	m_pFirstPlan;//tang mau thu nhat
	CAGimageGrayScale*	m_pSecondPlan;//tang mau thu hai
	CAGimageGrayScale*	m_pThirdPlan;//tang mau thu ba
	CAGimageGrayScale*	m_pAlphaPlan;//tang alpha
	CAGimageGrayScale*	m_pGrayPlan;//tang gray scale

	agint8	m_mode;//AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
	               //AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau
	agbool	m_bConsistent;//agtrue: du lieu noi tai va cac tang mau da nhat quan
public:
	//constructor
	CAGimageMultiPlans(aguint32 imagetype = 0);
	CAGimageMultiPlans(aguint32 dwWidth, aguint32 dwHeight, aguint32 imagetype = 0);
	CAGimageMultiPlans(const CAGimageMultiPlans &src, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);
	CAGimageMultiPlans(const agtchar * filename, aguint32 imagetype);
	CAGimageMultiPlans(FILE * stream, aguint32 imagetype);
	CAGimageMultiPlans(CxFile * stream, aguint32 imagetype);
	CAGimageMultiPlans(aguint8 * buffer, aguint32 size, aguint32 imagetype);

	//Class Type
	virtual aguint32	GetClassType()	{return AGMAGICIP_MULTIPLANS_CLASSTYPE;}
	virtual	CAGimage*	CreateMe()		{return new CAGimageMultiPlans();}

	//initialization
	virtual void Init();//Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau 
				 //khi ham Load ham nay duoc goi ngay sau khi doi tuong duoc khoi tao, day la ham ao 
				 //nen no se duoc ovverride o cac lop devired, khong nen goi ham nay ngay sau khi 
				 //khoi tao vi ban than cac ham khoi tao da goi ham Init nay. Noi chung la ham nay 
				 //chi duoc goi sau khi goi cac ham Initialization cua CxImage nhu: Create, Clear, 
				 //Copy, CreateFromHBITMAP, CreateFromHICON, CreateFromHANDLE, CreateFromARGB, Transfer
	virtual void Copy(CAGimage* psrc, agbool copypixels = agtrue, agbool copyselection = agtrue, agbool copyalpha = agtrue);

public:
	//destructors
	virtual ~CAGimageMultiPlans();
	virtual void Destroy();//Ham huy

	//Color conversion utilities
	virtual agbool	SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate);//Ham nay override ham lop cha, 


	//Pixel operation
	virtual aguint8 GetPixelMaxI();//Lay gia tri lon nhat co the co cua muc xam 1 pixel tai tang 
				   //mau gray. Ham nay override lop cha CAGimage
	virtual aguint8 GetPixelI(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y tai tang 
				   //mau gray. Ham nay override lop cha CAGimage
	virtual aguint8 GetPixelIFast(agint_xcoord x, agint_bu_ycoord y);//Lay muc xam cua pixel tai vi tri x, y tai 
				   //tang mau gray. Ham nay override lop cha CAGimage. Ham nay giong nhu ham 
				   //GetPixelI(agint_xcoord x, agint_bu_ycoord y) nhung se xu ly nhanh hon do khong kiem tra rang buoc

	//Mode
	void	SetMode(agint8 mode);//Dat che do hien hanh
	agint8	GetMode();//Lay che do hien hanh, co the co cac gia tri
					  //AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
	                  //AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau

	//Consistent
	agbool IsConsistent();//Kiem tra du lieu noi tai va cac tang mau co nhat quan khong?
	agbool UpdateConsistent();//Cap nhat giua du lieu noi tai va cac tang mau, nham muc dich giu su 
							 //nhat quan giua cac tang mau va du lieu noi tai
	void SetNotConsistent();//bao hieu du lieu noi tai va cac tang mau khong nhat quan

	//Plans
protected:
	void PlansDestroy();//Huy tat ca cac tang mau
public:
	agbool	PlansIsValid();//Kiem tra xem tat cac tang mau co hop le(khac rong) khong
	void	PlansGetPixelMaxI(aguint8& maxa, aguint8& maxb, aguint8& maxc, aguint8& maxalpha, aguint8& maxgray);//Lay gia tri 
												//lon nhat co the co cua 1 pixel tai cac tang mau
	void	PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& alpha, aguint8& gray);//Lay gia tri 
												//cua 1 pixel tai cac tang mau
	void	PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray);//Lay gia tri 
												//cua 1 pixel tai cac tang mau
	void	PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& alpha, aguint8& gray);//Lay gia tri 
			//cua 1 pixel tai cac tang mau ham nay giong nhu ham 
			//PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& gray, aguint8& alpha) 
			//nhung xu ly nhanh hon do khong kiem tra rang buoc
	void	PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray);//Lay gia tri 
			//cua 1 pixel tai cac tang mau. Ham nay giong nhu 
			//PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray) 
			//nhung xu ly nhanh hon do khong kiem tra rang buoc

	agbool	PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray);//Dat gia tri cua 1 pixel tai cac tang mau
	agbool	PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray);//Dat gia tri cua 1 pixel tai cac tang mau
	agbool	PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray);//Dat gia tri cua 1 pixel tai cac tang mau
			//ham nay giong nhu PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& gray, aguint8& alpha) 
			//nhung xu ly nhanh hon do khong kiem tra rang buoc
	agbool	PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray);//Dat gia tri cua 1 pixel tai cac tang mau
			//ham nay giong nhu PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray) 
			//nhung xu ly nhanh hon do khong kiem tra rang buoc

	//Plan
	CAGimageGrayScale*	GetFirstPlan();//lay tang mau 1
	CAGimageGrayScale*	GetSecondPlan();//lay tang mau 2
	CAGimageGrayScale*	GetThirdPlan();//lay tang mau 3
#if CXIMAGE_SUPPORT_ALPHA
	CAGimageGrayScale*	GetAlphaPlan();//lay tang mau alpha
#endif
	CAGimageGrayScale*	GetGrayPlan();//lay tang mau xam(cuoi cung)

	//Heuristic Segmentation
	virtual agint32	HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, HEURISTIC_SEG_BLOCK_MATRIX* pOutBlocksMatrix=NULL, aguint32* pOrderRelate=NULL);//Ham nay phan doan anh theo Heuristic
	//Goi HeuristicSeg=Goi Heuristic3Seg + Goi HeuristicCombine3Seg
	AGCLRQUAD	Heuristic3Seg(HEURISTIC_SEG_PARAM* pParam, aguint16 order, aguint8* pFirstOutSegs, aguint8* pSecondOutSegs, aguint8* pThirdOutSegs);//ham nay phan doan cac tang mau 1 cach rieng re
	agint32	HeuristicCombine3Seg(aguint16 relate, aguint8* pFirstSegs, aguint8* pSecondSegs, aguint8* pThirdSegs, aguint8* pOutSegs);//Ham nay dung de ket hop 3 ket qua phan doan 
			//cua tung tang mau rieng re the mot quan he de cho ra ket qua phan doan cuoi cung
private:
	void	HeuristicMakeLabel(agint32 label, AGBU_POINT curPixel, aguint8* pOutSegs);//ham nay dung danh nhan lan toa de quy, 
			//no duoc goi trong ham HeuristicCombine3Seg
public:
};

/********************************CAGimageObjPtrVec****************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class AGMAGIC_DECL CAGimageObjPtrbuMatrix;
class AGMAGIC_DECL CAGimageObjPtrtdMatrix;
class AGMAGIC_DECL CAGimageObjPtrVec : public CAGobjPtrArray<CAGimage>
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimage();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimage* pAGimageDst=(CAGimage*)dst;
		CAGimage* pAGimageSrc=(CAGimage*)src;
		pAGimageDst->Copy(pAGimageSrc);
	}
	agint32 TotalWidth(agint32 wHinge=0);
	agint32 TotalHeight();
public:
	CAGimageObjPtrVec();
	virtual ~CAGimageObjPtrVec();

	void Import(CAGptrArray*  pInAGimageA, agbool bIsCopy=agfalse);
	void Export(CAGptrArray*  pOutAGimageA, agbool bIsCopy=agfalse);

	agbool Load(agtchar szDir[], agtchar szKey[], CAGimage* pTempImage=NULL, aguint32 imagetype=0);
	agbool Save(agtchar szFilePathAndName[], aguint32 imagetype=0);

	friend class AGMAGIC_DECL CAGimageObjPtrbuMatrix;
	friend class AGMAGIC_DECL CAGimageObjPtrtdMatrix;
};
/********************************CAGimageObjPtrMatrix****************************************/
class AGMAGIC_DECL CAGimageObjPtrMatrix : public CAGobjPtrArray<CAGimageObjPtrVec>
{
protected:
	virtual agint32 TotalWidth(agint32 wHinge=0)=0;
	virtual agint32 TotalHeight(agint32 hHinge=0)=0;
public:
	CAGimageObjPtrMatrix() {}
	virtual ~CAGimageObjPtrMatrix() {}

	virtual void Import(CAGptrArray*  pInAGimageAA, agbool bIsCopy=agfalse)=0;
	virtual void Export(CAGptrArray*  pOutAGimageAA, agbool bIsCopy=agfalse)=0;

	virtual agbool Load(agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage=NULL, aguint32 imagetype=0)=0;
	virtual agbool Save(agtchar szFilePathAndName[], aguint32 imagetype=0)=0;

	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)=0;
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, SIZE block_size)=0;
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 nRows, agint32 nCols)=0;

	virtual CAGimage* NewImageByJoin(AGCLRQUAD* fill_clr=NULL, agint32 wHinge=0, agint32 hHinge=0)=0;
};

/********************************CAGimageObjPtrbuMatrix****************************************/
class AGMAGIC_DECL CAGimageObjPtrtdMatrix;
class AGMAGIC_DECL CAGimageObjPtrbuMatrix : public CAGimageObjPtrMatrix
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageObjPtrVec();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageObjPtrVec* pAGimageObjPtrDst=(CAGimageObjPtrVec*)dst;
		CAGimageObjPtrVec* pAGimageObjPtrSrc=(CAGimageObjPtrVec*)src;
		pAGimageObjPtrDst->CopyFrom(pAGimageObjPtrSrc,agtrue);
	}
	virtual agint32 TotalWidth(agint32 wHinge=0);
	virtual agint32 TotalHeight(agint32 hHinge=0);
public:
	CAGimageObjPtrbuMatrix();
	virtual ~CAGimageObjPtrbuMatrix();

	virtual void Import(CAGptrArray*  pInAGimageAA, agbool bIsCopy=agfalse);
	virtual void Export(CAGptrArray*  pOutAGimageAA, agbool bIsCopy=agfalse);
	void Import(CAGimageObjPtrtdMatrix* ptdMatrix, agbool bIsCopy=agfalse);
	void Export(CAGbuRectMatrix* pbuRectMatrix);
	void Flip();

	virtual agbool Load(agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage=NULL, aguint32 imagetype=0);
	virtual agbool Save(agtchar szFilePathAndName[], aguint32 imagetype=0);

	agbool CreateByCut(CAGimage* pAGimageSrc, CAGbuRectMatrix* pRectMatrix);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, SIZE block_size);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 nRows, agint32 nCols);

	virtual CAGimage* NewImageByJoin(AGCLRQUAD* fill_clr=NULL, agint32 wHinge=0, agint32 hHinge=0);
};
/********************************CAGimageObjPtrtdMatrix****************************************/
class AGMAGIC_DECL CAGimageObjPtrtdMatrix : public CAGimageObjPtrMatrix
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageObjPtrVec();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageObjPtrVec* pAGimageObjPtrDst=(CAGimageObjPtrVec*)dst;
		CAGimageObjPtrVec* pAGimageObjPtrSrc=(CAGimageObjPtrVec*)src;
		pAGimageObjPtrDst->CopyFrom(pAGimageObjPtrSrc,agtrue);
	}
	virtual agint32 TotalWidth(agint32 wHinge=0);
	virtual agint32 TotalHeight(agint32 hHinge=0);
public:
	CAGimageObjPtrtdMatrix();
	virtual ~CAGimageObjPtrtdMatrix();

	virtual void Import(CAGptrArray*  pInAGimageAA, agbool bIsCopy=agfalse);
	virtual void Export(CAGptrArray*  pOutAGimageAA, agbool bIsCopy=agfalse);

	void Import(CAGimageObjPtrbuMatrix* pbuMatrix, agbool bIsCopy=agfalse);
	void Export(CAGtdRectMatrix* ptdRectMatrix);

	virtual agbool Load(agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage=NULL, aguint32 imagetype=0);
	virtual agbool Save(agtchar szFilePathAndName[], aguint32 imagetype=0);

	agbool CreateByCut(CAGimage* pAGimageSrc, CAGtdRectMatrix* pRectMatrix);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, SIZE block_size);
	virtual agbool CreateByCut(CAGimage* pAGimageSrc, agint32 nRows, agint32 nCols);

	virtual CAGimage* NewImageByJoin(AGCLRQUAD* fill_clr=NULL, agint32 wHinge=0, agint32 hHinge=0);
};

/********************************CAGimageIDs****************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class AGMAGIC_DECL CAGimageIDs : public CAGidArray, public CAGmagicDBOrg
{
public:
	void DBRead(aguint_id ImageType);
};

/********************************CAGimageDBItemType****************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class AGMAGIC_DECL CAGimageDBItemType : public CAGmagicDBOrg
{
public:
	aguint_id	m_ID;
	agtchar*	m_Name;

	CAGimageDBItemType();
	virtual ~CAGimageDBItemType();
	void Destroy();//Ham huy

	virtual agbool	CopyFrom(CAGimageDBItemType* item_type);
};

/********************************CAGimageDBItemTypes****************************************/

class AGMAGIC_DECL CAGimageDBItemTypes : public CAGobjPtrArray<CAGimageDBItemType>, public CAGmagicDBOrg
{
protected:

	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageDBItemType();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageDBItemType* pAGimageDBItemTypeDst=(CAGimageDBItemType*)dst;
		CAGimageDBItemType* pAGimageDBItemTypeSrc=(CAGimageDBItemType*)src;
		pAGimageDBItemTypeDst->CopyFrom(pAGimageDBItemTypeSrc);
	}

	agbool DBRead(agtchar SQL[]);
public:
	CAGimageDBItemTypes();
	~CAGimageDBItemTypes();

	void DBReadAll();
};

/********************************CAGimageDBItem****************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class CAGimageDBItems;
class CAGimageSemanticTree;
/*
class AGMAGIC_DECL CAGimageDBItem
Chuc nang:
Cach dung:
Ghi chu:
*/
class CAGdbHBlockMatrix;
class CAGimageSegs;
class AGMAGIC_DECL CAGimageDBItem : public CAGmagicDBOrg
{
protected:
	agbool	m_bIsRestoreImage;

public:
	aguint_id	m_ImageID;
	aguint_id	m_ImageType;
	agtchar*	m_Name;
	agtchar*	m_URL;
public:
	CAGimage*				m_pAGimageSrc;
	CAGmagicElement*		m_pReservedAGmagicElement;
	CAGimageSemanticTree*   m_pSemanticTree;

	virtual CAGimage*	CreateAGimage();

public:
	CAGimageDBItem();
	virtual ~CAGimageDBItem();
	void Destroy();//Ham huy

	agbool	IsStoreImage();
	void SetIsStoreImage(agbool	bIsRestoreImage);

	virtual agbool	CopyFrom(CAGimageDBItem* item);

	void	SetSemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy);
	void	AllocName(agtchar Name[]);
	void	AllocURL(agtchar URL[]);

	agbool	LoadURL(agtchar URL[]);
	agbool	DBRead(aguint_id ImageID);
	agbool	DBInsert(agbool IsInsertFeatures, agbool bIsNormWhenInsertFeatures, agbool bIsInsertAff, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs=NULL);
	agbool	DBUpdate();
	agbool	DBDelete();

	friend	class CAGimageDBItems;
protected:
	agtchar*	DBGetSelectSQL(agtchar SQL[], aguint_id ImageID);
	agtchar*	DBGetInsertSQL(agtchar*& SQL, aguint_id ImageType, agtchar Name[], agtchar URL[]);
	agtchar*	DBGetUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id ImageType, agtchar Name[], agtchar URL[]);
	agtchar*	DBGetDeleteSQL(agtchar*& SQL, aguint_id ImageID);
};


/********************************CAGimageDBItems****************************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

/*
class AGMAGIC_DECL CAGimageDBItems
Chuc nang:
Cach dung:
Ghi chu:
*/

class AGMAGIC_DECL CAGimageDBItems : public CAGobjPtrArray<CAGimageDBItem>, public CAGmagicDBOrg
{
protected:
	agbool	m_bIsRestoreImage;

	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimageDBItem();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimageDBItem* pAGimageDBItemDst=(CAGimageDBItem*)dst;
		CAGimageDBItem* pAGimageDBItemSrc=(CAGimageDBItem*)src;
		pAGimageDBItemDst->CopyFrom(pAGimageDBItemSrc);
	}
public:
	CAGimageDBItems();
	~CAGimageDBItems();
	virtual void CopyInfoFrom(CAGobjPtrArray<CAGimageDBItem>* xa);

	agbool	IsStoreImage();
	void	SetIsStoreImage(agbool bIsRestoreImage);

	virtual agbool	CopyFrom(CAGimageDBItems* xa, agbool bIsCopy=agfalse);
	virtual agbool	TransferFrom(CAGimageDBItems* xa);
	void			LoadDir(agtchar szOrgDir[], agtchar szFilter[]);
	void			AddURL(agtchar URL[]);

	agint32	LSearchImageID(aguint_id ImageID);
	void	RemoveSameImageIDs();
	void	GetAllImageIDs(CAGidArray* ImageIDs);
	void	Import(aguint_id ImageIDs[], agint32 nImageIDs);//nhap ImageIDs
	void	Import(CAGidArray* ImageIDs);//nhap ImageIDs

	CAGimage*		GetImageAt(agint32 idx);
	aguint_id		GetIDAt(agint32 idx);
	CAGimageDBItem*	GetAtID(aguint_id ImageID);
	void			RemoveIfImageID(aguint_id ImageID);
	agbool			IsContentImageIDs(CAGidArray* ImageIDs);

	void	CopyAGmagicElementsTo(CAGmagicElementPtrArray* pAGmagicElementPtrArray);

	agbool	DBRead(aguint_id ImageIDs[], aguint32 nImageIDs);
	agbool	DBRead(agtchar SQL[], agbool bIsReadURL=agtrue);
	agbool	DBRead();
	agbool	DBInsert(agbool IsInsertFeatures, agbool bIsNormWhenInsertFeatures, agbool bIsInsertAff, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs=NULL);
	agbool	DBUpdate();
	agbool	DBDelete();

	agbool	DBAppendDistinctImageIDs(aguint_id ImageIDs[], aguint32 nImageIDs, agbool bIsReReadDB);
};

/********************************CAGinteractImagesMsg****************************************/

class AGMAGIC_DECL CAGinteractImagesMsg : public CAGimageDBItems
{
protected:
	agbool		m_bIsDeleteImages;
	agbool		m_bIsDeleteMeInProc;
	agbool		m_bIsPassID;

protected:
	agtchar*	m_szNotice;
public:
	void*					m_pNoFreeReserved;//thuong la CEvent
	CAGimageSemanticTree*   m_pSemanticTree;
	agint32					m_CandidateCount;//=0: se lay het

	CAGinteractImagesMsg();
	virtual ~CAGinteractImagesMsg();

	virtual void CopyInfoFrom(CAGobjPtrArray<CAGimageDBItem>* xa);
	virtual void	RemoveAll();

	virtual agbool	CopyFrom(CAGinteractImagesMsg* xa, agbool bIsCopy=agfalse);
	virtual agbool	TransferFrom(CAGinteractImagesMsg* xa);

	void		SetNotice(agtchar szNotice[]);
	agtchar*	GetNotice();
	void		SetSemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy);

	virtual agtchar*	GetTextAt(agint32 idx);

	agbool IsDeleteImages();
	agbool IsDeleteMeInProc();
	agbool IsPassID();

	void SetDeleteImages(agbool bIsDeleteImages);
	void SetDeleteMeInProc(agbool bIsDeleteMeInProc);
	void SetIsPassID(agbool bIsPassID);

	void CopyIDsTo(CAGidArray* pIDs);
	static void DefaultInit(CAGinteractImagesMsg* pMsg);
};


#endif // !defined(AGIMAGE_H__92EF1325_2CB0_4CFD_9DCC_AA5670CAFB59__INCLUDED_)
