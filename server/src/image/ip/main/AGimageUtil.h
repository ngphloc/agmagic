#if !defined(AGIMAGEUTIL_H__D4970B63_8AD1_487D_87B5_0C58587EF71D__INCLUDED_)
#define AGIMAGEUTIL_H__D4970B63_8AD1_487D_87B5_0C58587EF71D__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "AGimageDefs.h"

/*******************************class CAGimageConfUtil*******************************/

class AGMAGIC_DECL CAGmagicIPConfUtil
{
private:
	static agbool		bIsInitAGmagicIPConf;
public:
	static agtchar*		AGmagicIP_Global_Tables[];
	static agint32		AGmagicIP_Global_nTables;
	static agbool		AGmagicIP_Global_bTables[];

	static agtchar		AGmagicIP_GlobalCurImageTable[256];
	static agint32		AGmagicIP_ClobalFeatures;

	static void			Init();

private:
	static agint32		GetTableIndexFromName(agtchar TableName[]);
	static agint32		GetTableIndexFromFeature(agint32 feature);

	static agbool		IsTableIndexValid(agint32 idx);
	static agbool		IsTableNameValid(agtchar TableName[]);
};
/*******************************class CAGimageMicUtil*******************************/
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"

class CAGimage;
class CAGimageObjPtrbuMatrix;
template<class AGARRAY_TYPE>		class CAGbaseArray;
typedef CAGbaseArray<void*>		CAGptrArray;

/*
class AGMAGIC_DECL CAGimageMicUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageMicUtil
{
public:

#ifdef WIN32
	//Pal
	static	AGCLRQUAD*	CreateDemoMonoColorsPal();
	static	AGCLRQUAD*	CreateDemo16ColorsPal();
	static	AGCLRQUAD*	CreateDemo256ColorsPal();
	static	agbool		DecreasePal(AGCLRQUAD*& pEntries, aguint32 NUMENTRIES/*old*/, aguint32 numEntries/*new*/);

	static	aguint32		CreatePal(CAGimage* pAGimage, HPALETTE& hPal);
	static	aguint32		CreatePal(HDC hDC, AGCLRQUAD*& pRGBQUADEntries);
	static	aguint32		GetRGBQUADFromHPALETTE(HPALETTE hPal, AGCLRQUAD*& pRGBQUADEntries);

#endif

#if AGMAGIC_SUPPORT_MFC
//////////////////////////
	struct DocType
	{
	public:
		int nID;
		BOOL bRead;
		BOOL bWrite;
		const TCHAR* description;
		const TCHAR* ext;
	};
	static	DocType doctypes[CMAX_IMAGE_FORMATS];
	static	BOOL	doctypesPromptForFileName(CString& fileName, UINT nIDSTitle, 
						DWORD dwFlags, BOOL bOpenFileDialog, int* pType=NULL);
	static	int		doctypesGetIndexFromType(int nDocType, BOOL bOpenFileDialog);
	static	int		doctypesGetTypeFromIndex(int nIndex, BOOL bOpenFileDialog);
	static	CString doctypesGetExtFromType(int nDocType);
	static	CString doctypesGetDescFromType(int nDocType);
	static	CString doctypesGetFileTypes(BOOL bOpenFileDialog);
	static	BOOL	doctypesGetWritableType(int nDocType);
//////////////////////////

	//Image List
	static	CImageList*	CreateImageList(CAGptrArray* pAGimageA, CSize* pListItemSize, CDC* pDC=NULL, COLORREF* pcrMask=NULL, agbool bAllSameSizeImage=agtrue);

	//Draw
	static	void DrawA(CPoint xy, aguint32& nCols, CAGptrArray* pAGimageA, HDC hDC, CSize* pSize, CSize sizeHinge/*ban le:khoang cach giua 2 anh theo chieu ngang va doc*/);
	static	void DrawAA(CPoint xy, CAGptrArray* pAGimageAA, HDC hDC, CSize* pSize, CSize sizeHinge);

	//Pallete
	static	agbool		DrawPal(CPoint xy, AGCLRQUAD*	pEntries, aguint32 nColors, CSize squareXY, aguint32 nCols, agbool bRainbow, CDC* pDC, CSize* pSize, CSize sizeHinge);
	static	agbool		DrawPal(CPoint xy, CAGimage* pAGimage, CSize squareXY, aguint32 nCols, agbool bRainbow, CDC* pDC, CSize* pSize, CSize sizeHinge);

	static	aguint32	CreatePal(CAGimage* pAGimage, CPalette*& pPal);

#endif	//#if AGMAGIC_SUPPORT_MFC
	static agtchar*	FindFileExtension(const agtchar* FileName, agtchar out_ext[]);
	static agint32	FindFileType(const agtchar* ext);
	static agtchar* FindFileTypeStr(agint32 type, agtchar ext[]);

	//Storage
};

/*******************************class CAGimageIOUtil*******************************/
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
/*
class AGMAGIC_DECL CAGimageIOUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageIOUtil
{
public:
	static void GetAllSupportImageExt(agtchar exts[], agtchar seps[]=AGMAGIC_OR_SEPS);
	static void AnalyzeImagePathAndAlloc(agtchar szImagePath[], agtchar*& szBaseSampleDir, agtchar*& szDirTypeName, agtchar*& szImageName);

	static agbool LoadA(CAGptrArray*  pAGimageA,  agtchar szDir[], agtchar szKey[], CAGimage* pTempImage=NULL, aguint32 imagetype=0);
	static agbool LoadAA_TD(CAGptrArray* pAGimageAA_TD, agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage=NULL, aguint32 imagetype=0);

	static agbool SaveA(CAGptrArray* pAGimageA, agtchar szFilePathAndName[], aguint32 imagetype=0);
	static agbool SaveAA_TD(CAGptrArray* pAGimageAA_TD, agtchar szFilePathAndName[], aguint32 imagetype=0);

};

/*******************************class CAGimageDBUtil*******************************/

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/AGutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
struct AGMAGIC_DECL IMAGE_ID_TYPE
{
	aguint_id	ImageID;
	aguint_id	ImageType;
};
typedef AGMAGIC_DECL CAGbaseArray<IMAGE_ID_TYPE>	CAGidTypeArray;

/*
class AGMAGIC_DECL CAGimageDBUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageDBUtil
{
public:
	static	void	EraseDB(void* pDBCnnI);
	static	void	AddToDBFromURL(agtchar url[], aguint_id ImageType, void* pDBCnnI);
	static	void	CreateDBFromURL(agtchar base_url[], void* pDBCnnI);

	static	agbool	Load(aguint_id ImageID, void* pDBCnnI, CAGimage* pOutAGimage);
	static	agbool	FindImageID(void* pDBCnnI, aguint_id ImageType, agtchar szName[], agtchar szURL[], CAGidArray* ImageIDs);
	static	agbool	FindImage(void* pDBCnnI, agtchar szName[], agtchar szURL[], CAGidTypeArray* ImageIDTypes);
	static	agbool	FindImageIntel(void* pDBCnnI, agtchar szBaseSampleDir[], agtchar szDirTypeName[], agtchar szImageName[], CAGidTypeArray* ImageIDTypes);
	static	agbool	FindImageIntel(void* pDBCnnI, agtchar szImagePath[], CAGidTypeArray* ImageIDTypes);

	static	void	ResetAffInDB(void* pDBCnnI);
	static	void	ReadAllImagesIDs(void* pDBCnnI, aguint_id ImageType, CAGidArray* OutIDs);
};

/*******************************class CAGimageColorUtil*******************************/

/*
class AGMAGIC_DECL CAGimageColorUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageColorUtil
{
public:
	static agint32		GradianByteToDegree(aguint8 gradian_byte);//trong he HSL
	static aguint8		DegreeToGradianByte(agint32 degree);//Trong he HSL

	static agint32	PalFindColorIndex(AGCLRQUAD clr, AGCLRQUAD Pal[], agint32 nPal);
	static agint32	PalFindNearestColorIndexByEucDis(AGCLRQUAD clr, AGCLRQUAD Pal[], agint32 nPal);
	static agbool	LutByEucDis(CAGimage* pInOutAGimage, AGCLRQUAD Lut[], agint32 nLut);
	static int		RGBCompareGray(const void* pRGB1, const void* pRGB2);
	static void		RGBPalSort(AGCLRQUAD Pal[], agint32 nPal);

	#define	AG_HSV_13PRIMARY_COLOR		13
	enum hsv_13primary_color
	{
		hsv_white=0,		hsv_black=1,			hsv_gray=2,
		hsv_red=3,			hsv_red_yellow=4,
		hsv_yellow=5,		hsv_yellow_green=6,
		hsv_green=7,		hsv_green_blue=8,
		hsv_blue=9,			hsv_blue_purple=10,
		hsv_purple=11,		hsv_purple_red=12
	};
	static hsv_13primary_color	HSV13PrimaryReduce(AGCLRQUAD hsv);
	static agbool				HSV13PrimaryGetHisto(CAGimage* pAGimage, agint32 histo[AG_HSV_13PRIMARY_COLOR]);
	static agint32				HSV13PrimaryGetIndexInEnum(hsv_13primary_color color);

	#define	AG_RGB_25PRIMARY_COLOR		25
	enum rgb_25primary_color
	{
		rgb_black=0,			rgb_sea_green=1,
		rgb_light_green=2,		rgb_olive_green=3,
		rgb_aqua=4,				rgb_bright_green=5,
		rgb_blue=6,				rgb_green=7,
		rgb_turquoise=8,		rgb_brown=9,
		rgb_blue_gray=10,		rgb_lime=11,
		rgb_lavender=12,		rgb_plum=13,
		rgb_teal=14,			rgb_dark_red=15,
		rgb_magenta=16,			rgb_yellow_green=17,
		rgb_flouro_green=18,	rgb_red=19,
		rgb_rose=20,			rgb_yellow=21,
		rgb_pink=22,			rgb_orange=23,
		rgb_white=24
	};
	static void		RGB25PrimaryFillPal(AGCLRQUAD pal[AG_RGB_25PRIMARY_COLOR]);
	static agbool	RGB25PrimaryLut(CAGimage* pInOutAGimage/*, agbool bIsSortLut=agfalse*/);
	static agbool	RGB25PrimaryGetHisto(CAGimage* pAGimage, agbool bIs25PrimaryImage, agint32 histo[AG_RGB_25PRIMARY_COLOR]);
};

/*******************************class CAGimageDrawUtil*******************************/

/*
class AGMAGIC_DECL CAGimageDrawUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageDrawUtil
{
public:
	struct LineDDA_DrawStruct
	{
		void*	m_pDrawTool;//HDC doi voi Windows
		agint32 m_SelShift;
		agint32 m_SelCount;
	};
	#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
		friend void CALLBACK LineDDAProc2(int x, int y, CAGimageDrawUtil::LineDDA_DrawStruct* pDrawStruct);
	#endif
public:
	static void LineDDA_Screen(LineDDA_DrawStruct* pDrawStruct, AGBU_POINT pts[], agint32 n_pts, agreal64 zoom, POINT start_pos);
	//static aguint_id LineDDA_Screen_StartMotive(void* draw_tool, AGBU_POINT pts[], agint32 n_pts, agreal64 zoom, POINT start_pos);
	//static void		 LineDDA_Screen_StopMotive();
};

/*******************************class CQuantizer*******************************/

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
//#include "../lib/CQuantizer/Quantize.h"
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

#endif // !defined(AGIMAGEUTIL_H__D4970B63_8AD1_487D_87B5_0C58587EF71D__INCLUDED_)
