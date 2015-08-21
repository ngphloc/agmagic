#include "AGimage.h"
#include "AGimageUtil.h"

#if AGMAGIC_SUPPORT_MFC

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#endif	//#if AGMAGIC_SUPPORT_MFC

/*******************************class CAGimage***************************************/

//////////////////////////////////////////////constructors/////////////////////////////////////////
/*
CAGimage::CAGimage(aguint32 imagetype):CxImage(imagetype)
CAGimage::CAGimage(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype):CxImage(dwWidth,dwHeight,wBpp,imagetype)
CAGimage::CAGimage(const CAGimage &src, agbool copypixels, agbool copyselection, agbool copyalpha):CxImage(src,copypixels,copyselection,copyalpha)
CAGimage::CAGimage(const agint8 * filename, aguint32 imagetype):CxImage(filename,imagetype)
CAGimage::CAGimage(FILE * stream, aguint32 imagetype):CxImage(stream,imagetype)
CAGimage::CAGimage(CxFile * stream, aguint32 imagetype):CxImage(stream,imagetype)
CAGimage::CAGimage(aguint8 * buffer, aguint32 size, aguint32 imagetype):CxImage(buffer,size,imagetype)

Chuc nang:
	Cac ham constructor
Tham so vao:
	imagetype: kieu dinh dang co the cua anh, bao gom cac gia tri sau:
		CXIMAGE_FORMAT_JPG, CXIMAGE_FORMAT_TIF, CXIMAGE_FORMAT_MNG, CXIMAGE_FORMAT_BMP, 
		CXIMAGE_FORMAT_ICO, CXIMAGE_FORMAT_GIF, CXIMAGE_FORMAT_PNG, CXIMAGE_FORMAT_PCX, 
		CXIMAGE_FORMAT_TGA, CXIMAGE_FORMAT_WMF, CXIMAGE_FORMAT_JBG, CXIMAGE_FORMAT_J2K,
		CXIMAGE_FORMAT_JP2, CXIMAGE_FORMAT_JPC, CXIMAGE_FORMAT_PGX, CXIMAGE_FORMAT_PNM, 
		CXIMAGE_FORMAT_RAS, CXIMAGE_FORMAT_WBMP
		voi dinh dang tu dong, tu phat hien kieu dinh dang anh dua tren phan mo rong cua file ta 
			dung kieu CXIMAGE_FORMAT_UNKNOWN
	dwWidth, dwHeight: chieu rong va dai cua anh
	wBpp: so bit cua 1 pixel, bao gom cac gia tri: 1, 4, 8, 16, 24, 32
	src: anh nguon dung de khoi tao mot anh
	copypixels: =agtrue: copy noi dung cua anh nguon, nguoc lai la khong
	copyselection: =agtrue: copy vung selection, nguoc lai la khong
	copyalpha: =agtrue: copy kenh alpha, nguoc lai la khong
	filename: duong dan cua file anh
	stream: con tro dem stream file anh hay con tro den CxFile-dai dien cho file anh
	buffer: vung nho chua anh, tham so nay luon di kem voi tham so size chi kich thuoc cua buffer
	size: kich thuoc cua tham so buffer o tren
Tham so ra:
Tra ve:
Cach dung:
	CAGimage* pAGimage=new CAGimage(CXIMAGE_FORMAT_BMP);
	delete pAGimage;
Ghi chu:
	Tat ca nhung ham khoi tao nay deu goi ham khoi tao cua lop cha CxImage
*/

CAGimage::CAGimage(aguint32 imagetype):CxImage(imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}
CAGimage::CAGimage(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype):CxImage(dwWidth,dwHeight,wBpp,imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}
CAGimage::CAGimage(const CAGimage &src, agbool copypixels, agbool copyselection, agbool copyalpha):CxImage(src,copypixels,copyselection,copyalpha)
{
	SetColorSpace(src.m_eColorSpace,agfalse);
	m_ID=0;
}
CAGimage::CAGimage(const agtchar * filename, aguint32 imagetype):CxImage(filename,imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}
CAGimage::CAGimage(FILE * stream, aguint32 imagetype):CxImage(stream,imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}
CAGimage::CAGimage(CxFile * stream, aguint32 imagetype):CxImage(stream,imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}
CAGimage::CAGimage(aguint8 * buffer, aguint32 size, aguint32 imagetype):CxImage(buffer,size,imagetype)
{
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
	m_ID=0;
	Init();
}

#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"
agbool CAGimage::Load(const agtchar* url, aguint32 imagetype)
{
	Destroy();
	agtchar*	URL=CAGmagicIOUtil::ConvertAndAllocFullURL((agtchar*)url);
	agbool		bLoad=CxImage::Load(URL,imagetype);
	if(URL)		free(URL);

	if(!bLoad)	return agfalse;

	Init();
	return agtrue;
}
////////////////////////////////////////////initialization/////////////////////////////////////

/*
void CAGimage::Init()
Chuc nang:
	Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau khi ham Load, Create, 
		Clear,..day la ham ao nen no se duoc ovverride o cac lop devired, khong nen goi ham nay ngay 
		sau khi khoi tao vi ban than cac ham khoi tao da goi ham Init nay. Noi chung la ham nay chi 
		duoc goi sau khi goi cac ham Initialization cua CxImage nhu: Create, Clear, Copy,
		CreateFromHBITMAP, CreateFromHICON, CreateFromHANDLE, CreateFromARGB, Transfer, Load
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimage* pAGimage=new CAGimage();
	pAGimage->Load(_T("myPicture.gif"));
	pAGimage->Init();
	//do here something...
	//.............
	pAGimage->Create(200,100,8);
	pAGimage->Init();
	//do here something...
	//.............
	delete pAGimage;
Ghi chu:
	Ngay Sau khi khoi tao khong can goi ham Init

	CAGimage* pAGimage=new CAGimage();
	pAGimage->Init();//khong can thiet
	delete pAGimage;
*/
void CAGimage::Init()
{
	if(m_eColorSpace==AGMAGICIP_COLORSPACE_UNKNOWN)
		m_eColorSpace=AGMAGICIP_COLORSPACE_RGB;
	else
		SetColorSpace(AGMAGICIP_COLORSPACE_RGB,agtrue);
}
/*
void CAGimage::Copy()
Chuc nang:
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimage::Copy(CAGimage* psrc, agbool copypixels, agbool copyselection, agbool copyalpha)
{
	CxImage::Copy(*psrc,copypixels,copyselection,copyalpha);

	m_eColorSpace=psrc->GetColorSpace();
	if(m_eColorSpace==AGMAGICIP_COLORSPACE_UNKNOWN)
		m_eColorSpace=AGMAGICIP_COLORSPACE_RGB;
	m_ID=psrc->m_ID;
}
void CAGimage::Copy(CxImage* psrc, agbool copypixels, agbool copyselection, agbool copyalpha)
{
	CxImage::Copy(*psrc,copypixels,copyselection,copyalpha);
	Init();
}
//void CAGimage::MixFromNoTrans(CAGimage* pAGimage, agint_xcoord lXOffset, agint_bu_ycoord lYOffset)
//{
//	AGCLRQUAD rgb;
//
//	agint32 width = pAGimage->GetWidth();
//	agint32 height = pAGimage->GetHeight();
//
//	agint_xcoord	x;
//	agint_bu_ycoord y;
//    for(x = 0; x < width; x++)
//    {
//		for(y = 0; y < height; y++)
//		{
//			rgb = pAGimage->GetPixelColor(x, y);
//			SetPixelColor(x + lXOffset, y + lYOffset, rgb);
//		}
//	}
//}

////////////////////////////////////////////Destruction////////////////////////////////////////////
/*
CAGimage::~CAGimage()
Chuc nang:
	Ham huy mac dinh
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
CAGimage::~CAGimage()
{
}
/*
void CAGimage::Destroy()
Chuc nang:
	Ham nay se huy toan bo du lieu cua anh. Ve ban chat tat ca tac lop ke thua se dinh nghia lai ham 
		huy Destroy nay
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimage* pAGimage=new CAGimage();
	pAGimage->Load(_T("myPicture.gif"));
	pAGimage->Init();
	//do here somthing....
	//..........
	pAGimage->Destroy();
	pAGimage->Create(200,100,24);
	pAGimage->Init();
	//do here somthing
	//............
	delete pAGimage;
Ghi chu:
*/
void CAGimage::Destroy()
{
	CxImage::Destroy();
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;
}

////////////////////////////////MFC Support/////////////////////////////////////////
#if AGMAGIC_SUPPORT_MFC
/*
void CAGimage::Serialize(CArchive& ar)
Chuc nang:
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimage::Serialize(CArchive& ar, aguint32 imagetype)
{
	Destroy();
	BYTE*	buffer=NULL;
	agint32	size=0;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		if(Encode(buffer,size,imagetype))
			ar.Write(buffer,size);
	}
	else
	{
		// TODO: add loading code here
		size=(aguint32)(ar.GetFile()->GetLength());
		if(size==0)	return;
		buffer=(BYTE*)malloc(size);
		ar.Read(buffer,size);

		Decode(buffer,size,imagetype);
	}
	if(buffer)	free(buffer);
	Init();
}
#endif

////////////////////////////////Color conversion utilities/////////////////////////////////////////

/*
AGCLRQUAD CAGimage::CMYKtoRGB(AGCLRQUAD lCMYKColor)
Chuc nang:
	Chuyen 1 mau tu CMYK sang RGB
Tham so vao:
	lCMYKColor: gia tri mau CMYK can chuyen sang RGB. Tham so nay co kieu la AGCLRQUAD bao gom cac 
		truong sau:
		rgbRed: thanh phan C
		rgbGreen: thanh phan M
		rgbBlue: thanh phan Y
		rgbReserved: thanh phan K

Tham so ra:
Tra ve:
	Gia tri mau RGB cua lCMYK
Cach dung:
	//Gia su ta co mau trang trong khong gian CMYK la cmykWhite;
	AGCLRQUAD cmykWhite;
	cmykWhite.rgbRed=cmykWhite.rgbGreen=cmykWhite.rgbBlue=0;
	cmykWhite.rgbReserved=RGB2GRAY(255,255,255);

	AGCLRQUAD rgbWhite=pAGimage->CMYKtoRGB(cmykWhite);
Ghi chu:
*/
AGCLRQUAD CAGimage::CMYKtoRGB(AGCLRQUAD lCMYKColor)
{
	AGCLRQUAD rgb;
	rgb.rgbRed=255-lCMYKColor.rgbRed;
	rgb.rgbGreen=255-lCMYKColor.rgbGreen;
	rgb.rgbBlue=255-lCMYKColor.rgbBlue;
	rgb.rgbReserved=0;

	return rgb;
}
/*
AGCLRQUAD CAGimage::RGBtoCMYK(AGCLRQUAD lRGBColor)
Chuc nang:
	Chuyen 1 mau tu RGB sang CMYK
Tham so vao:
	lRGBColor: gia tri mau RGB can chuyen sang CMYK
Tham so ra:
Tra ve:
	Gia tri mau CMYK cua lRGB, bao gom cac thanh phan
		rgbRed: thanh phan C
		rgbGreen: thanh phan M
		rgbBlue: thanh phan Y
		rgbReserved: thanh phan K
Cach dung:
	AGCLRQUAD rgbWhite=pAGimage->RGBtoRGBQUAD(RGB(255,255,255));//chuyen mau trang tu cach bieu dien 
										//COLORREF sang cach bieu dien AGCLRQUAD
	//ta chuyen mau trang rgbWhite tu khong gian RGB sang khong gian CMYK
	AGCLRQUAD cmykWhite=pAGimage->RGBtoCMYK(rgbWhite);//cmykWhite se chua mau trang trong khong gian CMYK
Ghi chu:
*/
AGCLRQUAD CAGimage::RGBtoCMYK(AGCLRQUAD lRGBColor)
{
	AGCLRQUAD cmyk;
	cmyk.rgbRed=255-lRGBColor.rgbRed;
	cmyk.rgbGreen=255-lRGBColor.rgbGreen;
	cmyk.rgbBlue=255-lRGBColor.rgbBlue;
	cmyk.rgbReserved=(aguint8)RGB2GRAY(lRGBColor.rgbRed,lRGBColor.rgbGreen,lRGBColor.rgbBlue);//thanh phan k la thanh phan xam

	return cmyk;
}
/*
AGCLRQUAD CAGimage::COLORSPACEtoCOLORSPACE(enum_colorspace from, enum_colorspace to, AGCLRQUAD abc)
Chuc nang:
	Chuyen gia tri mau "abc" tu khong gian mau "from" den khong gian mau "to"
Tham so vao:
	from, to: khong gian mau ban dau va khong gian mau sau, bao gom cac gia tri co the co nhu sau:
		AGMAGICIP_COLORSPACE_RGB, 
		AGMAGICIP_COLORSPACE_HSL,	
		AGMAGICIP_COLORSPACE_YUV,
		AGMAGICIP_COLORSPACE_YIQ, 
		AGMAGICIP_COLORSPACE_XYZ, 
		AGMAGICIP_COLORSPACE_CMYK
	abc : gia tri mau tai khong gian mau "from"
		rieng doi voi khong gian CMYK thi thanh phan k chinh la muc xam, duoc dat trong 
		field rgbReserved cua kieu AGCLRQUAD
Tham so ra:
Tra ve:
	Gia tri mau cua abc tai khong gian mau "to"
Cach dung:
	//Gia su ta co mot mau trong khong gian YUV la yuvColor,
	//Ta muon chuyen mau yuvColor thanh mau hslColor trong khong gian HSL
	AGCLRQUAD yuvColor={143,125,211,0};
	AGCLRQUAD hslColor;
	hslColor=pAGimage->COLORSPACEtoCOLORSPACE(AGMAGICIP_COLORSPACE_YUV,AGMAGICIP_COLORSPACE_HSL,yuvColor);
Ghi chu:
*/
AGCLRQUAD CAGimage::COLORSPACEtoCOLORSPACE(enum_colorspace from, enum_colorspace to, AGCLRQUAD abc)
{
	if(from==to)	return abc;
	AGCLRQUAD	out;
	switch(from)
	{
		case AGMAGICIP_COLORSPACE_RGB ://neu abc la RGB thi khong can phai thay doi
			break;
		case AGMAGICIP_COLORSPACE_HSL :
			out=HSLtoRGB(abc);
			break;
		case AGMAGICIP_COLORSPACE_YUV :
			out=YUVtoRGB(abc);
			break;
		case AGMAGICIP_COLORSPACE_YIQ :
			out=YIQtoRGB(abc);
			break;
		case AGMAGICIP_COLORSPACE_XYZ :
			out=XYZtoRGB(abc);
			break;
		case AGMAGICIP_COLORSPACE_CMYK:
			out=CMYKtoRGB(abc);
		default:
			throw _T("Not defined this color space");

	}
	switch(to)
	{
		case AGMAGICIP_COLORSPACE_RGB :
			break;
		case AGMAGICIP_COLORSPACE_HSL :
			out=RGBtoHSL(out);
			break;
		case AGMAGICIP_COLORSPACE_YUV :
			out=RGBtoYUV(out);
			break;
		case AGMAGICIP_COLORSPACE_YIQ :
			out=RGBtoYIQ(out);
			break;
		case AGMAGICIP_COLORSPACE_XYZ :
			out=RGBtoXYZ(out);
			break;
		case AGMAGICIP_COLORSPACE_CMYK:
			out=RGBtoCMYK(out);
		default:
			throw _T("Not defined this color space");
	}
	return out;
}
/*
enum_colorspace CAGimage::GetColorSpace()
Chuc nang:
	Lay khong gian mau hien hanh
Tham so vao:
Tham so ra:
Tra ve:
	Khong gian mau hien hanh bao gom cac tri
		AGMAGICIP_COLORSPACE_RGB, 
		AGMAGICIP_COLORSPACE_HSL,	
		AGMAGICIP_COLORSPACE_YUV,
		AGMAGICIP_COLORSPACE_YIQ, 
		AGMAGICIP_COLORSPACE_XYZ, 
		AGMAGICIP_COLORSPACE_CMYK
Cach dung:
	enum_colorspace myColorSpace=pAGimage->GetColorSpace();
Ghi chu:
*/
enum_colorspace CAGimage::GetColorSpace()
{
	return m_eColorSpace;
}
/*
agbool CAGimage::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
Chuc nang:
	Dat khong gian mau hien hanh
Tham so vao:
	eColorSpace: khong gian mau cac dat, bao gom cac tri
		AGMAGICIP_COLORSPACE_RGB,
		AGMAGICIP_COLORSPACE_HSL,	
		AGMAGICIP_COLORSPACE_YUV,
		AGMAGICIP_COLORSPACE_YIQ, 
		AGMAGICIP_COLORSPACE_XYZ, 
		AGMAGICIP_COLORSPACE_CMYK
	bUpdate : neu la agtrue thi phai cap nhat lai toan bo du lieu theo khong gian mau eColorSpace
			  neu la agfalse thi chi can dat bien m_eColorSpace=eColorSpace, khong can cap nhat lai du lieu
Tham so ra:
Tra ve:
	agtrue : neu thanh cong, nguoc lai la agfalse;
Cach dung:
	enum_colorspace myColorSpace=pAGimage->GetColorSpace();
	if(myColorSpace==AGMAGICIP_COLORSPACE_RGB)
		pAGimage->SetColorSpace(AGMAGICIP_COLORSPACE_HSL);
Ghi chu:
*/
agbool CAGimage::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
{
	if (!pDib) return agfalse;

	if(!bUpdate)
	{
		m_eColorSpace=eColorSpace;
		return agtrue;
	}
	if(m_eColorSpace==eColorSpace)	return agtrue;

	if(GetNumColors())//neu nhu co bang mau thi thao tac tren bang mau de ang huong den toan bo anh
	{
		for(aguint8 idx=0; idx<GetNumColors(); idx++)//duyet tung pt trong bang mau
		{
			AGCLRQUAD abc=GetPaletteColor(idx);
			abc=COLORSPACEtoCOLORSPACE(m_eColorSpace,eColorSpace,abc);
			SetPaletteColor(idx,abc);//chuyen sang khong giang mau moi cua phan nay trong pallete
		}
	}
	else//nguoc lai se thay doi ngay tai moi pixel 
	{
		AGBU_RECT	rc; 
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;

		for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++)
		{
			for(agint_xcoord x=rc.left; x<rc.right; x++)
			{
				AGCLRQUAD abc=GetPixelColor(x,y);
				abc=COLORSPACEtoCOLORSPACE(m_eColorSpace,eColorSpace,abc);
				SetPixelColor(x,y,abc);
			}
		}
	}
	m_eColorSpace=eColorSpace;
	return agtrue;
}
agbool CAGimage::FillColor(AGCLRQUAD abc)
{
	AGBU_RECT	rc;
	if (pSelection)
	{
		COPY_RECT_TO_RECT(rc,info.rSelectionBox)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;
	}

	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++){
		for(agint_xcoord x=rc.left; x<rc.right; x++){
		#if CXIMAGE_SUPPORT_SELECTION
			if (SelectionIsInside(x,y))
		#else
			if (IsInside(x,y))
		#endif //CXIMAGE_SUPPORT_SELECTION
			{
				SetPixelColor(x,y,abc);
			}
		}
	}
	return agtrue;
}

///////////////////////////////////////Pixel operations////////////////////////////////////////////

/*
aguint8 CAGimage::GetPixelMaxI()
Chuc nang:
	Lay gia tri lon nhat co the co cua muc xam 1 pixel
Tham so vao:
Tham so ra:
Tra ve:
	Gia tri lon nhat co the co cua muc xam 1 pixel
Cach dung:
	aguint8 maxValue=pAGimage->GetPixelMaxI();
Ghi chu:
*/
aguint8 CAGimage::GetPixelMaxI()
{
	return 255;
}
/*
aguint8 CAGimage::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimage->GetPixelI();
Ghi chu:
*/
aguint8 CAGimage::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
{
	return (aguint8)((agint32)GetPixelGray(x,y));//ham CxImage::GetPixelGray se goi RGB2GRAY(r,g,b)
					//voi r,g,b la 3 thanh phan mau tai pixel nay
}
/*
aguint8 CAGimage::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y
	Ham nay giong nhu ham GetPixelI(agint_xcoord x, agint_bu_ycoord y) nhung se xu ly nhanh hon do khong kiem 
		tra rang buoc
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimage->GetPixelIFast();
Ghi chu:
*/
aguint8 CAGimage::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
{
	return (aguint8)((agint32)GetPixelGray(x,y));
}
/*
agreal64 CAGimage::GetPixelNormI(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay nang luong cua pixel tai vi tri x, y(nang luong la muc xam duoc chuan hoa ve [0,1])
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Nang luong cua pixel tai vi tri x,y
Cach dung:
	agreal64 normValue=pAGimage->GetPixelNormI();
Ghi chu:
*/
agreal64 CAGimage::GetPixelNormI(agint_xcoord x, agint_bu_ycoord y)
{
	return (agreal64)GetPixelI(x,y)/(agreal64)GetPixelMaxI();
}
agreal64 CAGimage::GetPixelNormIFast(agint_xcoord x, agint_bu_ycoord y)
{
	return (agreal64)GetPixelIFast(x,y)/(agreal64)GetPixelMaxI();
}
/*
agreal64 CAGimage::GetPixelAverage(agint_xcoord x, agint_bu_ycoord y, agint32 k)
Chuc nang:
	Lay tri trung binh tai x,y voi he so k the cong thuc 
	Ak(x,y)=Xichma(j=x-2^(k-1), j=x+2^(k-1)-1, Xichma(i=y-2^(k-1), i=y+2^(k-1)-1, f(j,i)))
	Ham nay dung lam co so de tinh do tho
Tham so vao:
	x,y : toa do
	k : he so
Tham so ra:
Tra ve:
	Tri trung binh can tim duoc chuan hoa trong doan [0..1]
Cach dung:
	agreal64 average=pAGimage->GetPixelAverage();
Ghi chu:
*/
agreal64 CAGimage::GetPixelAverage(agint_xcoord x, agint_bu_ycoord y, agint32 k, AGBU_RECT* prc)
{
	if (k<=0 || !IsInside(x,y))
		return 0.0;

	agint32	n=1<<(k-1);//n=2^(k-1)
	agreal64	A=0.0;
	for(agint_bu_ycoord i=y-n; i<y+n; i++)
		for(agint_xcoord j=x-n; j<x+n; j++)
		{
			if(prc==NULL)
			{
			#if CXIMAGE_SUPPORT_SELECTION
				if(!SelectionIsInside(j,i))	continue;
			#else
				if(!IsInside(j,i))			continue;
			#endif
			}
			else
			{
				if(!AreaIsInside(prc,j,i))		continue;
			}
			A +=GetPixelIFast(j,i);
		}
	return (A/(agreal64)(1<<(2*k)));
}

////////////////////////////////////////Selection//////////////////////////////////////////////////

#if CXIMAGE_SUPPORT_SELECTION
bool CAGimage::SelectionAddRect(AGBU_RECT bur)
{
	RECT r;
	COPY_RECT_TO_RECT(r,bur);
	return CxImage::SelectionAddRect(r);
}
/*
agint32 CAGimage::SelectionGetNumPixels()
Chuc nang:
	Lay tong so pixels cua vung pSelection
Tham so vao:
Tham so ra:
Tra ve:
	Tong so pixels cua vung pSelection
Cach dung:
	agint32 numPixels=pAGimage->SelectionGetNumPixels();
Ghi chu:
*/
agint32 CAGimage::SelectionGetNumPixels()
{
	AGBU_RECT	rc; 
	if (pSelection)
	{
		COPY_RECT_TO_RECT(rc,info.rSelectionBox)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;
	}

	agint32 totalpixels=0;
	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++){
		for(agint_xcoord x=rc.left; x<rc.right; x++){
			if (SelectionIsInside(x,y))
			{
				totalpixels ++;
			}
		}
	}
	return totalpixels;
}

/*
agreal64 CAGimage::SelectionGetEdgeDensity(agreal64 threshold)
Chuc nang:
	Lay mat do bien(duoc chuan hoa trong doan [0..1]) cua vung pSelection 
	theo nguong threshhold
Tham so vao:
	threshhold: nguong(ti le) de nang luong 1 pixel chia voi nang luong 1 pixel khac de no duoc xem 
		la bien, threshold o trong doan [0,1]
		Mot diem duoc xem la bien neu nhu:
			(agreal64)AGABS_OF_SUB(curPixel,neighborPixel)/(agreal64)GetPixelMaxI()>threshold) voi 
			AGABS_OF_SUB la tri tuyet doi cua hieu, curPixel la pixel hien hanh, neighborPixel la pixel 
			lan can, GetPixelMaxI() tra ve gia tri lon nhat co the co cua 1 pixel
Tham so ra:
Tra ve:
	mat do bien duoc chuan hoa trong doan [0..1] cua vung pSelection
Cach dung:
	agreal64 edgeDensity=pAGimage->SelectionGetEdgeDensity();
Ghi chu:
*/
agreal64 CAGimage::SelectionGetEdgeDensity(agreal64 threshold, agbool bIsOneOf)
{
	AGBU_RECT	rc; 
	if (pSelection)
	{
		COPY_RECT_TO_RECT(rc,info.rSelectionBox)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;
	}

	agint32 edgePixels=0;
	agint32 totalPixels=0;
	agint32 n=1;
	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++)
	{
		for(agint_xcoord x=rc.left; x<rc.right; x++)
		{
			agreal64	TotalEnergy=0;
			if (SelectionIsInside(x,y))
			{
				totalPixels++;

				aguint8 curPixel=GetPixelIFast(x,y);//gray level tai x,y

				agint32	nAreaPixels=0;
				for(agint32 i=-n; i<=n; i++)
				{
					for(agint32 j=-n; j<=n; j++)
					{
						if(i==0 && j==0)//neu la tai diem hien hanh thi bo qua
							continue;
						agint_xcoord	xx=x+j;
						agint_bu_ycoord yy=y+i;

						if (!SelectionIsInside(xx,yy))	continue;
						nAreaPixels ++;

						agint32 neighborPixel=GetPixelIFast(xx,yy);//gia tri pixel tai cac diem lan can
						if(bIsOneOf)
						{
							curPixel=(curPixel==0)?1:curPixel;//tranh loi chia cho 0
							if((agreal64)AGABS_OF_SUB(curPixel,neighborPixel)/(agreal64)curPixel>threshold)
							{
								edgePixels++;
								goto end;
							}
						}
						else TotalEnergy +=neighborPixel;
					}
				}
			end:
				if(!bIsOneOf)
				{

					curPixel=(curPixel==0)?1:curPixel;//tranh loi chia cho 0
					agreal64	NormTotalEnergy=(nAreaPixels==0)? 0 : (TotalEnergy/ (agreal64)nAreaPixels);
					if((agreal64)AGABS_OF_SUB(((agreal64)curPixel),NormTotalEnergy)/(agreal64)curPixel>threshold)
						edgePixels++;
				}
			}
		}
	}
	if(edgePixels==0.0)	return edgePixels;
	return (agreal64)edgePixels/(agreal64)totalPixels;
}
/*
agreal64 CAGimage::SelectionGetNormI()
Chuc nang:
	Lay nang luong cua cua vung pSelection (nang luong o day chi muc xam), nang luong nay duoc 
		chuan hoa trong doan [0,1]
Tham so vao:
Tham so ra:
Tra ve:
	Nang luong cua cua vung pSelection can tim duoc chuan hoa trong doan [0..1]
Cach dung:
	agreal64 normValue=pAGimage->SelectionGetNormI();
Ghi chu:
*/
agreal64 CAGimage::SelectionGetNormI()
{
	AGBU_RECT	rc; 
	if (pSelection)
	{
		COPY_RECT_TO_RECT(rc,info.rSelectionBox)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;
	}

	agint32 sumNormValue=0;
	agint32 totalPixels=0;
	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++)
	{
		for(agint_xcoord x=rc.left; x<rc.right; x++)
		{
			if (SelectionIsInside(x,y))
			{
				totalPixels ++;
				sumNormValue +=GetPixelIFast(x,y);
			}
		}
	}
	return (agreal64)sumNormValue/((agreal64)GetPixelMaxI()*(agreal64)totalPixels);
}

/*
agreal64 CAGimage::SelectionGetCrudeLevel(agint32 h)
Chuc nang:
	Lay do tho cua vung pSelection voi he so h.
	Thuat toan tinh do tho nhu sau:
		Buoc 1: Lay trung binh tren cac tri lan can cua moi diem voi kich co tang theo mu cua 2.
			Voi kick co (2^k)*(2^k) tai diem (x,y) ta co tri trung binh, k di tu 1..h
				Ak(x,y)=CAGimage::GetPixelAverage(x, y, k)
				       =Xichma(j=x-2^(k-1), j=x+2^(k-1)-1, Xichma(i=y-2^(k-1), i=y+2^(k-1)-1, f(j,i)))
						Trong do f(j,i) la muc xam tai diem (j,i)
		Buoc 2: Tai moi diem, xac dinh khoang cach (hieu) cua tri trung binh cua cap roi nhau, o 2 
			phia doi nguoc cua diem, theo huong nam ngang va huong thang dung
			Ekh=|Ak(x+2^(k-1), y) - Ak(x-2^(k-1), y)| : theo huong nam ngang
			Ekv=|Ak(x, y+2^(k-1)) - Ak(x, y-2^(k-1))| : theo huong nam thang dung
			Tu Ekh va Ekv ta tinh Ek=max(Ekh,Ekv)
		Buoc 3: Tai moi diem, chon kich co thich hop nhat(tuc k) de cho gia tri ket xuat 
			cao nhat Sbest(x,y)=2^k. Trong do k la gia ma tai do E dat gia tri cuc dai:
			Emax=Ek=max(E1, E2, E3, ...,En) (Ek o day am chi mot k nao do)
		Buoc 4: Cuoi cung, lay gia tri trung binh cua Sbest tren toan anh va dung no de tinh do tho 
			Fcrs=Xichma(i=1, i=m, Xichma(j=1, j=n, Sbest(j,i)) /m*n voi m*n la so pixels cua vung pSelection
			Fcrs duoc chuan hoa: Fcrs=Fcrs/2^k
Tham so vao:
	h : he so ma k(trong thua toan) di tu 1..h, ta khong the cho k di tu k den n qua lon duoc
Tham so ra:
Tra ve:
	Do tho can tim trong doan [0..1] cua vung pSelection
Cach dung:
	agreal64 crudeLevel=pAGimage->SelectionGetCrudeLevel(4);
Ghi chu:
*/
agreal64 CAGimage::SelectionGetCrudeLevel(agint32 h)
{
	AGBU_RECT	rc; 
	if (pSelection)
	{
		COPY_RECT_TO_RECT(rc,info.rSelectionBox)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = head.biWidth; 
		rc.top	=head.biHeight;
	}

	agint32		edgepixel=0;
	agint32		totalPixels=0;
	agreal64	Fcrs=0.0;	//day chinh la do tho
	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++)
	{
		//info.nProgress = (agint32)(100*y/head.biHeight);
		//if (info.nEscape) break;
		for(agint_xcoord x=rc.left; x<rc.right; x++)
		{
			if (SelectionIsInside(x,y))
			{
				totalPixels++;

				agreal64	E=0.0;
				agint32	K=0;
				for(agint32 k=1; k<=h; k++)//k di tu 1..h
				{
					agint32	n=((agint32)1)<<(k-1);

					//theo chieu ngang
					agreal64	Akh=GetPixelAverage(x-n,y,k,&rc);//Akh=GetAverage(x-2^(k-1),y,k)
					agreal64	Bkh=GetPixelAverage(x+n,y,k,&rc);//Bkh=GetAverage(x+2^(k-1),y,k)
					agreal64	Ekh=AGABS_OF_SUB(Akh,Bkh);	 //Ekh=|Akh-Bkh|

					//theo chieu doc
					agreal64	Akv=GetPixelAverage(x,y-n,k,&rc);//Akv=GetAverage(x,y-2^(k-1),k)
					agreal64	Bkv=GetPixelAverage(x,y+n,k,&rc);//Bkv=GetAverage(x,y+2^(k-1),k)
					agreal64	Ekv=AGABS_OF_SUB(Akv,Bkv);	 //Ekv=|Akv-Bkv|

					agreal64	Ek=max(Ekh,Ekv);
					
					//tim Ek lon nhat
					if(E<Ek)
					{
						E=Ek;
						K=k;
					}
				}
				if(K>0)
					Fcrs +=(1<<K);
			}
		}
	}
	if(Fcrs==0.0)	return Fcrs;
	return Fcrs /=(agreal64)(totalPixels*(((agint32)1)<<h));
}
#endif

//////////////////////////////////////////////Area/////////////////////////////////////////////////
/*
agbool CAGimage::AreaIsInside(AGBU_RECT* prc, agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Kiem tra xem pixel tai toa do (x,y) co nam trong vung hinh chu nhat(prc) khong?
Tham so vao:
	prc: con tro vung hinh chu nhat ma pixel can kiem tra co nam trong hay khong
	x,y : toa do pixel
Tham so ra:
Tra ve:
	agtrue: neu (x,y) nam trong hinh chu nhat prc, nguoc lai la agfalse
Cach dung:
	AGBU_RECT rc;
	rc.left=0;
	rc.bottom=10;
	rc.right=50;
	rc.top=30;
	agbool isInside=pAGimage->AreaIsInside(&rc,1,20);
Ghi chu:
*/
agbool CAGimage::AreaIsInside(AGBU_RECT* prc, agint_xcoord x, agint_bu_ycoord y)
{
  return (prc->bottom<=y && y<prc->top && prc->left<=x && x<prc->right);
}
agbool CAGimage::AreaIsInside(AGTD_RECT* prc, agint_xcoord x, agint_td_ycoord y)
{
  return (prc->top<=y && y<prc->bottom && prc->left<=x && x<prc->right);
}

void CAGimage::AreaAdjust(AGBU_RECT* prc)
{
	if(prc)
	{
		prc->left  =AGMAX(0,(prc->left));   prc->right=AGMIN((agint32)GetWidth(), prc->right);
		prc->bottom=AGMAX(0,(prc->bottom)); prc->top  =AGMIN((agint32)GetHeight(),prc->top);
	}
}

/*
agreal64 CAGimage::AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc)
Chuc nang:
	Lay mat do bien cua vung hinh chu nhat,mat do bien nay duoc chuan hoa ve [0,1]
	Ham nay tuong tu nhu ham CAGimage::SelectionGetEdgeDensity(agreal64 threshold)
		nhung tinh mat do bien trong hinh chu nhat prc
Tham so vao:
	threshhold: nguong(ti le) de 1 pixel chia voi 1 pixel khac de no duoc xem la bien threshold o 
		trong doan [0,1]
		Mot diem duoc xem la bien neu nhu:
			(agreal64)AGABS_OF_SUB(curPixel,neighborPixel)/(agreal64)GetPixelMaxI()>threshold) voi 
			AGABS_OF_SUB la tri tuyet doi cua hieu, curPixel la pixel hien hanh, neighborPixel la pixel 
			lan can, GetPixelMaxI() tra ve gia tri lon nhat co the co cua 1 pixel
	prc : con tro hinh chu nhat can tinh mat do bien, neu prc=NULL nghia la mat do bien duoc tinh 
		cho toan anh
Tham so ra:
Tra ve:
	Mat do bien cua vung hinh chu nhat, duoc chuan hoa ve doan [0,1]
Cach dung:
	AGBU_RECT rc;
	rc.left=0;
	rc.bottom=10;
	rc.right=50;
	rc.top=30;
	agreal64 edgeDensity=pAGimage->AreaGetEdgeDensity(0.5,&rc);
Ghi chu:
*/
agreal64 CAGimage::AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc, agbool bIsOneOf)
{
	AGBU_RECT rc;
	if (prc)
		AreaAdjust(prc);
	else 
	{
		rc.left=0;			rc.right=GetWidth();
		rc.bottom=0;		rc.top=GetHeight();
		prc=&rc;
	}

	agint32 edgePixels=0;
	agint32	n=1;
	//SetProgress(0);
	for(agint_bu_ycoord y=prc->bottom; y<prc->top; y++)
	{
		//info.nProgress = AGMIN(99,(agint32)(100*y/(prc->top-prc->bottom)));

		for(agint_xcoord x=prc->left; x<prc->right; x++)
		{
			aguint8		curPixel=GetPixelIFast(x,y);//gray level tai x,y
			agreal64	TotalEnergy=0;//chi dung cho truong hop bIsOneOf=false
			agint32		nAreaPixels=0;
			for(agint32 i=-n; i<=n; i++)
			{
				for(agint32 j=-n; j<=n; j++)
				{
					if(i==0 && j==0)
						continue;
					agint_xcoord	xx=x+j;
					agint_bu_ycoord yy=y+i;
					if(!AreaIsInside(prc, xx,yy))	continue;

					nAreaPixels ++;
					agint32 neighborPixel=GetPixelIFast(xx,yy);//gia tri pixel tai cac diem lan can
					if(bIsOneOf)
					{
						curPixel=(curPixel==0)?1:curPixel;//tranh loi chia cho 0
						if((agreal64)AGABS_OF_SUB(curPixel,neighborPixel)/(agreal64)curPixel>threshold)
						{
							edgePixels++;
							goto end;
						}
					}
					else TotalEnergy +=neighborPixel;
				}
			}
		end:
			if(!bIsOneOf)
			{

				agreal64	NormTotalEnergy=(nAreaPixels==0)? 0 : (TotalEnergy/ (agreal64)nAreaPixels);

				curPixel=(curPixel==0)?1:curPixel;//tranh loi chia cho 0
				if((agreal64)AGABS_OF_SUB(((agreal64)curPixel),NormTotalEnergy)/(agreal64)curPixel>threshold)
					edgePixels++;
			}
		}
	}
	if(edgePixels==0.0)	return edgePixels;
	return (agreal64)edgePixels/(agreal64)((prc->top - prc->bottom)*(prc->right - prc->left));
}

/*
agreal64 CAGimage::AreaGetNormI(AGBU_RECT* prc)
Chuc nang:
	Lay nang luong cua cua vung hinh chua nhat prc (nang luong o day chi muc xam), 
	nang luong nay duoc chuan hoa trong doan [0,1]
Tham so vao:
	prc: hinh chu nhat can lay nang luong(cuong do) chuan hoa
Tham so ra:
Tra ve:
	Nang luong cua cua vung hinh chua nhat prc can tim duoc chuan hoa trong doan [0..1]
Cach dung:
	AGBU_RECT rc;
	rc.left=0;
	rc.bottom=10;
	rc.right=50;
	rc.top=30;
	agreal64 normValue=pAGimage->AreaGetEdgeDensity(&rc);
Ghi chu:
*/
agreal64 CAGimage::AreaGetNormI(AGBU_RECT* prc)
{
	AGBU_RECT	rc;
	if (prc)
		AreaAdjust(prc);
	else 
	{
		rc.left=0;			rc.right=GetWidth();
		rc.bottom=0;		rc.top=GetHeight();
		prc=&rc;
	}

	agint32 sumValue=0;
	for(agint_bu_ycoord y=prc->bottom; y<prc->top; y++)
	{
		for(agint_xcoord x=prc->left; x<prc->right; x++)
		{
			sumValue +=GetPixelIFast(x,y);
		}
	}
	if(sumValue==0.0)	return sumValue;
	return (agreal64)sumValue/((agreal64)GetPixelMaxI()*(agreal64)(prc->top - prc->bottom)*(agreal64)(prc->right - prc->left));
}
/*
agreal64 CAGimage::AreaGetCrudeLevel(agint32 h, AGBU_RECT* prc)
Chuc nang:
	Lay do tho cua vung hinh chu nhat prc voi he so h, Ham nay lam co so cho viec phan doan theo 
		Heuristic (ham CAGimage::HeuristicSeg, CAGimageMultiPlans::HeuristicSeg)
	Do tho nay duoc chuan hoa trong doan [0,1]
	Ham nay tuong tua nhu ham CAGimage::SelectionGetCrudeLevel(agint32 h) nhung no ap dung cho hinh 
		chu nhat prc.
	Thuat toan cho ham nay duoc mo ta trong phan ghi chu cua ham CAGimage::SelectionGetCrudeLevel(agint32 h)
Tham so vao:
	h : he so ma k(trong thua toan) di tu 1..h, ta khong the cho k di tu 1 den n qua lon duoc
	prc : hinh chu nhat can lay do tho
Tham so ra:
Tra ve:
	Do tho can tim trong doan [0..1] cua vung hinh chu nhat prc
Cach dung:
	AGBU_RECT rc;
	rc.left=0;
	rc.bottom=10;
	rc.right=50;
	rc.top=30;
	agreal64 crudeLevel=pAGimage->AreaGetEdgeDensity(4,&rc);
Ghi chu:
*/
agreal64 CAGimage::AreaGetCrudeLevel(agint32 h, AGBU_RECT* prc)
{
	AGBU_RECT	rc;
	if (prc)
		AreaAdjust(prc);
	else 
	{
		rc.left=0;			rc.right=GetWidth();
		rc.bottom=0;		rc.top=GetHeight();
		prc=&rc;
	}

	agint32		edgepixel=0;
	agreal64	Fcrs=0.0;	//day chinh la do tho
	//SetProgress(0);
	for(agint_bu_ycoord y=prc->bottom; y<prc->top; y++)
	{
		//info.nProgress = AGMIN(99,(agint32)(100*y/(prc->top-prc->bottom)));

		for(agint_xcoord x=prc->left; x<prc->right; x++)
		{
			agreal64	E=0.0;
			agint32	K=0;
			for(agint32 k=1; k<=h; k++)//k di tu 1..h
			{
				agint32	n=((agint32)1)<<(k-1);
				
				//theo chieu ngang
				agreal64	Akh=GetPixelAverage(x-n,y,k,prc);//Akh=GetAverage(x-2^(k-1),y,k)
				agreal64	Bkh=GetPixelAverage(x+n,y,k,prc);//Bkh=GetAverage(x+2^(k-1),y,k)
				agreal64	Ekh=AGABS_OF_SUB(Akh,Bkh);	 //Ekh=|Akh-Bkh|

				//theo chieu doc
				agreal64	Akv=GetPixelAverage(x,y-n,k,prc);//Akv=GetAverage(x,y-2^(k-1),k)
				agreal64	Bkv=GetPixelAverage(x,y+n,k,prc);//Bkv=GetAverage(x,y+2^(k-1),k)
				agreal64	Ekv=AGABS_OF_SUB(Akv,Bkv);	 //Ekv=|Akv-Bkv|

				agreal64	Ek=max(Ekh,Ekv);
				
				//tim Ek lon nhat
				if(E<Ek)
				{
					E=Ek;
					K=k;
				}
			}
			if(K>0)
				Fcrs +=(1<<K);
		}
	}

	if(Fcrs==0.0)	return Fcrs;
	return Fcrs /=(agreal64)((prc->top - prc->bottom)*(prc->right - prc->left)*(((agint32)1)<<h));
}

///////////////////////////////////////////Neighbor////////////////////////////////////////////////
/*
aguint8	CAGimage::GetNeighbor8Pixels(AGBU_POINT curPixel, AGBU_POINT pNeighborPixels[8])
Chuc nang:
	Lay lan can 8 cua 1 pixel
	Lan can 8 cua 1 pixel(dau +) chinh la 8 pixel xung quanh(dau *)
		***
		*+*
		***
	So pixel lan can 8 cua mot pixel luon <=8
Tham so vao:
	curPixel : toa do cua pixel hien hanh(curPixel.x, curPixel.y)
Tham so ra:
	pNeighborPixels : mang chua toa do cua cac pixel lan can pixel curPixel, mang nay mac dinh gom
		8 phan tu, tuy nhien so phan tu that su co the < 8 vi cac pixel o bien co so pixel lan can < 8 
		(trong truong hop nay phan phan tu doi ra cua pNeighborPixels se duoc dien toa do x=y=-1)
Tra ve:
	So pixel lan can thuc su(cac pixel bien co so pixel lan can <8)
Cach dung:
	AGBU_POINT curPixel;
	curPixel.x=10;
	curPixel.y=20;
	AGBU_POINT pNeighborPixels[8];//pNeighborPixels=(AGBU_POINT*)malloc(sizeof(AGBU_POINT));

	aguint8	NumOfNeighbor8Pixels=GetNeighbor8Pixels(curPixel,pNeighborPixels);
	for(aguint8	i=0; i<NumOfNeighbor8Pixels; i++)
	{
		//...do some thing width pNeighborPixels[i]
		//
	}
	//free(pNeighborPixels);//if used function malloc
Ghi chu:
*/
aguint8	CAGimage::GetNeighbor8Pixels(AGBU_POINT curPixel, AGBU_POINT pNeighborPixels[8])
{
	aguint8 nNeighborPixels=0;//bien chua so pixel lan can thuc su
	for(agint32 i=-1; i<=1; i++)//duyet cac chi so cua cac pixel lan can
	{
		for(agint32 j=-1; j<=1; j++)
		{
			if(i==0 && j==0)	continue;//loai bo pixel hien hanh

			AGBU_POINT neighborPixel;
			neighborPixel.x=curPixel.x + j;//cot cua pixel lan can
			neighborPixel.y=curPixel.y+ i;//dong cua pixel lan can
			if(IsInside(neighborPixel.x,neighborPixel.y))//pixel lan can phai nam trong anh
			{
				pNeighborPixels[nNeighborPixels]=neighborPixel;//gan pixel lan can vao mang tra ve
				nNeighborPixels++;//tang so pixel lan can thuc su
			}
		}
	}
	for(agint32 n=nNeighborPixels; n<8; n++)//nhung phan tu doi ra trong mang se duoc dien toa do x=y=-1
		pNeighborPixels[n].x=pNeighborPixels[n].y=-1;
	return nNeighborPixels;//tra ve so pixel lan can thuc su
}

/////////////////////////////////////Heuristic Segmentation////////////////////////////////////////
/*
agint32 CAGimage::HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, aguint8* pReserved)
Chuc nang:
	Ham nay phan doan anh theo Heuristic. Thuat toan phan vung anh theo Heuristic nhu sau:
	Buoc 1: Chia deu anh thanh cac khpo N*N pixels (chon N=24)
	Buoc 2: Dinh nghia E(X) la % mat do bien(edge density) cho moi khoi X
	Buoc 3: Tinh do tho C(X) cho moi khoi X, C(X)=CAGimage::AreaGetCrudeLevel(agint32 h, AGBU_RECT* prc)
	Buoc 4: Bo qua tat ca cac khoi X co E(X)<25% tuc 0.25
	Buoc 5: Tim mot khoi X sao cho S(X)=E(X)+C(X) la lon nhat va dat ten cho no la J
	Buoc 6: Neu S(J)>1.0 thi khoi tao mot vung moi RJ={J}, nguoc lai thuan toan dung(1 vung bao gom nhieu khoi)
	Buoc 7: Khao sat khoi K la lan can cua (vung) RJ, dinh nghia he thuc
			delta(K,RJ)=E(K) + C(K) + H(K,RJ) trong do
				H(K,RJ) do gia tri tuong duong ve mau(histogram) giua K va RJ duoc dinh nghia 
				la H(K,RJ)=1 - min(dhist(K,Y)) voi Y thuoc RJ va Y la lan can cua K va
					dhist(K,Y) la khoang cach duoc chuan hoa trong khong gian mau giua khoi K va khoi Y
	Buoc 8: Neu delta(K,RJ)=E(K) > 1.0 va E(K) + C(K) > 0.7 thi ghep khoi K vao vung RJ 
				RJ: RJ <- RJ+K
	Buoc 9: Lap lai buoc 7 va buoc 8 cho den khi cac khoi lan can K cua vung RJ deu duoc sang loc
	Buoc 10:Tro lai buoc 5
	
	Nhu vay trong thuat toan nay co nhung diem luu y sau:
		* E(K) + C(K) danh gia tinh ket cau cua khoi anh
		* H(K,RJ) danh gia kha nang trung mau cua khoi anh K va vung anh RJ(1 vung bao gom nhieu khoi),
			neu do lech mau min(dhist(K,Y)) > 1.0 (hay lon hon 1 nguong kha lon nau do nhu 0.8, 0.9,..) 
			thi H(K, RJ) <0 ( hay nho hon 1 nguong kha nho nao do nhu 0.001, 0.002,..) se lam giam kha
			nang ket nap khoi K vao vung RJ
		* E(K) + C(K) > 0.7 ngan ngua khoi K khong la ket cau nhung co mau gan voi vung RJ
		* Cac hanh so nguong nhu 0.25, 0.7 va so pixel cua moi khoi co the thay doi theo thuc nghiem
		* dhist(K,Y) chi don gian la hieu cua 2 cuong do mau cua 2 khoi K vaY duoc chuan hoa trong 
			doan [0..1]

Tham so vao:
	pParam : thong so khoi tao cho viec phan doan anh Heuristic, thong so nay co kieu HEURISTIC_SEG_PARAM 
			bao gom cac truong:
		SIZE	block_size;//kich thuoc cua mot khoi
		agint32	hCrude;//chinh la thong so h trong thuat toan tinh do tho: 
					   //AreaGetCrudeLevel(agint32 h), SelectionGetCrudeLevel(agint32 h). hCrude mac
					   //dinh = 4
		agreal64	thresholdEdge;//nguong de tinh mat do bie, day la thong so trong ham tinh mat do bien: 
				//SelectionGetEdgeDensity(agreal64 threshold), AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc)
		agreal64	hEX;//nguong cua mat do bien cua khoi X: E(X) < 25%=hEX (mac dinh)
		agreal64	hSJ;//nguong cua tong mot do bien va do tho cua khoi J: S(J)=E(J)+C(J)>1.0=hSJ (mac dinh)
		agreal64	dKR;//thong so delta cua khoi K: Delta(K,Rj)=E(K) + C(K) + H(K,Rj) > 1.0 = hKR (mac dinh)
		agreal64	hEKCK;//thong so do tho va mat do bien cua khoi K: E(K) + C(K) > 0.7=hEKCK (mac dinh)

		Cac gia tri mac dinh cua cac truong trong pParam co the duoc khoi tao bang macro INIT_HEURISTIC_SEG_PARAM 
			hay	macro INIT_HEURISTIC_SEG_PARAMPTR

	pReserved : danh rieng-khong duoc su dung nen luon bang NULL, tham so nay chi co nghia trong lop 
		CAGimageMultiPlans. Trong lop CAGimageMultiPlans, pReserved mang ngu nghia la quan he-relate
		(and, or, xor) va trat tu phoi hop-order giua cac tang mau, khi do *pReserved la so nguyen 
		voi 2 byte cao la trat tu ket hop giua cac tang mau(VD: first-second-third hay second-first-third,..) 
		va 2 byte thap chi moi quan he giua cac tang mau(and-and hay or-or hay and-or,..). That su 
		trong lop CAGimageMultiPlans, ham phan doan CAGimageMultiPlans::HeuristicSeg se phan doan rieng 
		re tung tang mau, cac ket qua phan doan(pOutSegs) cua tung tang mau se duoc	ket hop theo 1 
		quan he va trat tu nao do->trat tu va quan he nay duoc the hien trong tham so pReserved da 
		noi o tren. Trong ham CAGimageMultiPlans::HeuristicSeg, tham so pReserved duoc doi ten la 
		pOrderRelate
Tham so ra:
	pOutSegs: mang chua nhan cac vung da duoc phan doan, mang nay co kich thuoc bang voi kich thuoc 
		cua anh nhung moi phan tu(pixel) co gia tri la nhan cua vung ma phan tu do thuoc ve, gia tri 
		nhan di tu 1. Nhung phan tu co gia tri 0 thi khong thuoc vung nao, co the xem nhu no la nen 
		trong ngu nghia cua thuat toan phan doan nay. pOutSegs phai duoc khoi tao co kich thuoc=1byte*so_pixel_cua_anh, 
		pOutSegs tuyet doi khong duoc bang NULL khi truyen vao. Sau khi ham duoc goi xong, co the su 
		thao tac tren pOutSegs, nhung sau khi su dung pOutSegs thi phai giai phong no
Tra ve:
	So vung anh phan doan duoc
Cach dung:
	CAGimage* pAGimage=new CAGimage(_T("myPicture.gif"));
	HEURISTIC_SEG_PARAM param;
	INIT_HEURISTIC_SEG_PARAM(param)
	//co the thay doi cac truong cua param o day
	//param.block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX;
	//param.block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY;
    //param.hCrude=4;
	//param.thresholdEdge=0.5;
	//param.hEX=0.25;
	//param.hSJ=1.0;
	//param.dKR=1.0;
	//param.hEKCK=0.7;
	aguint32	nPixels=pAGimage->GetWidth()*pAGimage->GetHeight();
	aguint8*	pOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	memset(pOutSegs,0,nPixels);
	//ham chinh
	aguint32 nSegs=pAGimage->HeuristicSeg(&param,pOutSegs);//nSegs la so vung da phan doan duoc
	if(nSegs==0)	throw _T("Can not sement or error occur");
	//lam gi do voi pOutSegs
	//........

	free(pOutSegs);
	pOutSegs=NULL;
	delete pAGimage;
Ghi chu:
	Khoi co the duoc goi la block(thuat ngu block va khoi duoc dung qua lai lan nhau) vung bao gom 
		nhieu block(khoi) co the duoc goi la mang block hay object
	pOutSegs phai duoc khoi tao co kich thuoc=1byte*so_pixel_cua_anh, pOutSegs tuyet doi khong duoc 
		bang NULL khi truyen vao. Mac khac pOutSeg chi don thuan tinh theo pixel khong nhu anh tuc 
		moi dong quet khong can phai co so byte la boi so cua 4, pOutSeg la mang byte(8 bits)
*/
agint32 CAGimage::HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, HEURISTIC_SEG_BLOCK_MATRIX* pOutBlocksMatrix, aguint8* pReserved)
{
	if(!pDib)				return 0;
	agint32					ImageWidth=GetWidth(), ImageHeight=GetHeight();//kich thuoc cua anh
	if(pOutSegs)			memset(pOutSegs,0,ImageWidth*ImageHeight*sizeof(aguint8));
	if(pOutBlocksMatrix)	{DESTROY_HEURISTIC_SEG_BLOCK_MATRIXPTR(pOutBlocksMatrix,agfalse)}

	//Khoi tao lai thong so SEG_PARAM
	HEURISTIC_SEG_PARAM param;
	if(pParam==NULL)
	{
		INIT_HEURISTIC_SEG_PARAM(param)
		pParam=&param;
	}

	SIZE	block_size;//kich thuoc cua moi khoi duoc chinh sua lai
	if((agint32)(pParam->block_size.cx)<0)//neu nhu do rong cua moi khoi tinh theo ti le voi do rong anh
		block_size.cx=ImageWidth/abs(pParam->block_size.cx);
	else
		block_size.cx=pParam->block_size.cx;
	if(agint32(pParam->block_size.cy)<0)//neu nhu do cao cua moi khoi tinh theo ti le voi do cao anh
		block_size.cy=ImageHeight/abs(pParam->block_size.cy);
	else
		block_size.cy=pParam->block_size.cy;
	if(block_size.cx==0 || block_size.cy==0)	return 0;

	//dinh lai cac tham so
	agint_bu_ycoord		i;
	agint_xcoord		j;
	agint32		hCrude=pParam->hCrude;//thong so de tinh do tho, 1,2,3,4
	agreal64	thresholdEdge=pParam->thresholdEdge;
	agreal64	hEX=pParam->hEX;
	agreal64	hSJ=pParam->hSJ;
	agreal64	dKR=pParam->dKR;
	agreal64	hEKCK=pParam->hEKCK;

	//Khoi tao cac block
	agint32					rows_of_blocks=ImageHeight/block_size.cy, 
							cols_of_blocks=ImageWidth/block_size.cx;//so block the dong va the cot
	HEURISTIC_SEG_BLOCK**	blocks;
	if(rows_of_blocks==0 || cols_of_blocks==0)	return 0;

	INIT_HEURISTIC_SEG_BLOCK_ARRAYPTR(blocks,rows_of_blocks,cols_of_blocks)
	SetProgress(0);
	for(i=0; i<rows_of_blocks; i++)
	{
		info.nProgress = AGMIN(99,(long)(100*i/rows_of_blocks));
		for(j=0; j<cols_of_blocks; j++)
		{
			//Moi blocks[i][j].label =-1: block nay bi bo qua do co blocks[i][j].EX<0.25=hEX
			//						 =0: block nay chua duoc xem xe
			//						 =gia tri khac 0 va khac -1: block thuoc vung label nay
			memset(&(blocks[i][j]),0,sizeof(HEURISTIC_SEG_BLOCK));
			
			//goc trai,duoi 
			blocks[i][j].area.left=j*block_size.cx;
			blocks[i][j].area.bottom=i*block_size.cy;

			//goc phai, tren
			if(j==cols_of_blocks-1)	blocks[i][j].area.right=ImageWidth;
			else					blocks[i][j].area.right=blocks[i][j].area.left + block_size.cx;
			if(i==rows_of_blocks-1)	blocks[i][j].area.top=ImageHeight;
			else					blocks[i][j].area.top=blocks[i][j].area.bottom + block_size.cy;

			if(blocks[i][j].area.left>=blocks[i][j].area.right || 
			   blocks[i][j].area.bottom>=blocks[i][j].area.top)
				blocks[i][j].label=-1;//toa do block sai roi, bo di

			//tinh mat do bien cua moi block
			blocks[i][j].EX=AreaGetEdgeDensity(thresholdEdge,&(blocks[i][j].area),agfalse);
			if(blocks[i][j].EX<hEX)//Neu nhu mat do bien nho hon hEX(tuc 0.25 theo mac dinh)
				blocks[i][j].label=-1;//block nay khong can phai xem xet
			else//nguoc lai mat do bien >= hEX(tuc 0.25 theo mac dinh)
			{
				//tinh do tho va va muc xam(duoc chuan hoa) cua moi block
				blocks[i][j].CX=AreaGetCrudeLevel(hCrude,&(blocks[i][j].area));//lay do tho cua block
				blocks[i][j].GrayLevel=AreaGetNormI(&(blocks[i][j].area));//lay muc xam duoc chuan hoa cua block
			}

		}
	}

	//Thuat toan chinh
	agint32			label=0;//Nhan cua cac vung duoc khoi gan la 0
	agint_bu_ycoord	startI=0;
	agint_xcoord	startJ=0;
	SetProgress(0);
	while(agtrue)
	{
		info.nProgress = AGMIN(99,(long)(100*(startI*cols_of_blocks+startJ)/(cols_of_blocks*rows_of_blocks)));

		agreal64	max=-1.0;//day chinh la gia tri S(X)=E(X) + C(X) lonh nhat tuc mat do bien +  do tho lon nhat
		//chi muc i, j cua blocks ma tai do max=S(X)= lon nhat
		agint_bu_ycoord	maxI=-1;
		agint_xcoord	maxJ=-1;
		//duyet tung block bat dau tu diem khoi dau startI, startJ
		for(i=startI;i<rows_of_blocks;i++)
		{
			for(j=startJ;j<cols_of_blocks;j++)
			{
				if(blocks[i][j].label==-1)		continue;//neu nhu block bi bo qua

				if(blocks[i][j].label==0)//nhung block nao chua duoc xem xet
				{
					if(max<blocks[i][j].EX+blocks[i][j].CX)//tim block co S(X)=E(X)+C(X) lon nhat
					{
						max=blocks[i][j].EX+blocks[i][j].CX;// tim kiem block co E(X)+C(X) lon nhat
						maxI=i;maxJ=j;
					}
				}
					
			}
		}
		if(max==-1.0)	break;//neu nhu tat ca cac khoi deu da duoc danh dau

		//goi blocks[maxI][maxJ] la block co gia tri S(X)=E(X)+C(X) lon nhat
		agreal64 SJ=blocks[maxI][maxJ].EX+blocks[maxI][maxJ].CX;//S(X)=E(X) + C(X) lon nhat tai khoi J
		if(SJ<=hSJ)//neu S(J) <= 1=hSJ thi thuat toan dung
			break;

		//Nguoc lai Neu nhu block[maxI][maxJ] co S(X)=E(X) + C(X) >1=hSJ thi tao vung moi va 
		//block[maxI][maxJ] nay tro thanh block hat giong
		label++;
		blocks[maxI][maxJ].label=label;

		//Duyet de quy tiep
		SIZE		rowscols_of_blocks;
		aguint16	nCurBlock=1;
		AGBU_POINT*	CurBlock=(AGBU_POINT*)malloc(nCurBlock*sizeof(AGBU_POINT));

		rowscols_of_blocks.cy=rows_of_blocks;
		rowscols_of_blocks.cx=cols_of_blocks;
		CurBlock->y=maxI;
		CurBlock->x=maxJ;
		//vieng tham cac block khac(ket nap them cac block voi block[maxI][maxJ] hat giong 
		//de tao vung moi)
		HeuristicSegVisit(label,blocks,rowscols_of_blocks,CurBlock,nCurBlock,dKR,hEKCK);
		free(CurBlock);CurBlock=NULL;

		//xac dinh lai diem khoi dau
		if(startJ<cols_of_blocks-1)	startJ++;//neu nhu chua den gioi han cot cua blocks
		else			
		{
			startI++;
			if(startI==rows_of_blocks)	break;//neu nhu den gioi han dong cua blocks
			else					startJ=0;
		}
	}//thuat toan chinh den day la ket thuc, luc nay ma?ng blocks se chua cac block duoc gan nhan
	 //cua vung ma block do thuoc ve

	//Cong doan nay gan nhan cua vung cho tung pixel
	//thuc te cong doan nay khong co y nghia trong lop CImageEx, nhung no co y nghia trong lop
	//CAGimageMultiPlans boi vi trong lop nay cac vung cua moi tung mau se and hay or hay xor
	//theo mot thu tu nao do voi nhau de ra nhung vung cuoi cung
	if(pOutSegs)
	{
		if(label>0)
		{
			for(i=0; i<rows_of_blocks; i++)
			{
				for(j=0; j<cols_of_blocks; j++)
				{
					if(blocks[i][j].label==-1 || blocks[i][j].label==0)
						continue;

					agint_bu_ycoord ymin = blocks[i][j].area.bottom,	ymax = blocks[i][j].area.top;
					agint_xcoord	xmin = blocks[i][j].area.left,	xmax = blocks[i][j].area.right;
					for (agint_bu_ycoord y=ymin; y<ymax; y++)
						memset(pOutSegs + xmin + y * ImageWidth, blocks[i][j].label, (xmax-xmin)*sizeof(aguint8));
				}
			}
		}
	}
	if(pOutBlocksMatrix)
	{
		pOutBlocksMatrix->m_blocks=blocks;
		pOutBlocksMatrix->m_rows_of_blocks=rows_of_blocks;
		pOutBlocksMatrix->m_cols_of_blocks=cols_of_blocks;
	}
	return label;
}
/*
void CAGimage::HeuristicSegVisit(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT*& curBlock, aguint16 nCurBlock, agreal64 dKR, agreal64 hEKCK)
Chuc nang:
	Ham nay khong the goi 1 cach truc tiep tu ben ngoai duoc, no chinh la ham phu tro cho ham 
		CAGimage::HeuristicSeg, no duoc goi boi ham CAGimage::HeuristicSeg.
	Ham CAGimage::HeuristicSegVisit duoc dung de ket nap cac khoi(block) vao  1 vung(mang block) 
		neu nhu khoi(block) do "tuong tu" voi vung(mang block) do. Dau tien, trong ham 
		CAGimage::HeuristicSeg se xac dinh block "hat giong", sau do ham CAGimage::HeuristicSegVisit
		se duoc goi de ket nap cac block khac vao block "hat giong" do theo nhung uoc luong heuristic, 
		nhung block tuong tu nay se duoc gan cung mot nhan tao thanh mot vung(mang block). Tien trinh 
		nay se duoc tien hanh de quy
	Ham nay la ham co ban trong thuat toan phan doan Heuristic, ban chat cua thuat toan phan doan
		Heuristic la de quy
Tham so vao:
	label: kieu so nguyen co dau 32 bit.Day la nhan cua block "hat giong" va cung la nhan cua 
		vung(mang block) bao gom block "hat giong" va tat ca nhung block "tuong tu" ve ket cau
	blocks: mang 2 chieu kieu HEURISTIC_SEG_BLOCK. Day la mang tat ca cac block cua anh. Tham so nay 
		vua la tham so vao vua la tham so ra. Moi phan tu cua tham so blocks tuong trung cho mot 
		block duoc gan nhan cua vung ma block do thuoc ve. Tien trinh de quy cua thuat toan phan doan 
		Heuristic se gan nhan cho cac khoi(block) nam trong tham so blocks
	rowscols_of_blocks: kieu SIZE. Tham so nay chi dinh kich thuoc dong, cot cua tham so mang 2	chieu 
		blocks
	curBlock: tham chieu mang AGBU_POINT. Tham so nay vua la tham so vao vua la tham so ra. Tham so nay 
		chua toa do cua tat ca cac block cua 1 vung(bao gom block "hat giong" va nhung block "tuong tu" 
		ve ket cau) co nhan mang gia tri cua tham so label. Thuc chat cua ham CAGimage::HeuristicSegVisit 
		la ket nap block de mo rong mang curBlock. Nen nho mang nay chua toa do tuc chi muc cua 1 block 
		trong mang blocks. Sau moi lan goi curBlock se thay doi dia chi neu nhu no no+? rong, vi the
		tham so nay la tham chieu
	nCurBlock: kieu so nguyen 16 bit. Day la kich thuoc cua tham so mang curBlock
	dKR: gia tri cua truong dKR trong cau truc HEURISTIC_SEG_PARAM, duoc dung cho viec xac dinh	tinh
		"tuong tu" ve ket cau trong thuat toan phan doan Heuristic
	hEKCK: gia tri cua truong hEKCK trong cau truc HEURISTIC_SEG_PARAM, duoc dung cho viec xac dinh
		tinh "tuong tu" ve ket cau trong thuat toan phan doan Heuristic
Tham so ra:
	blocks: duoc giai thich o tren
	curBlock: duoc giai thich o tren
Tra ve:
	Ham khong co gia tri tra ve nhung se throw exception khi co loi
Cach dung:
	Ham nay khong the goi truc tiep tu ben ngoai duoc, no duoc goi tu ben trong cua ham 
		CAGimage::HeuristicSeg, ben trong ham CAGimage::HeuristicSeg:

		SIZE		rowscols_of_blocks;
		AGBU_POINT*	curBlock=(AGBU_POINT*)malloc(sizeof(AGBU_POINT));
		
		rowscols_of_blocks.cy=rows_of_blocks;
		rowscols_of_blocks.cx=cols_of_blocks;
		curBlock->y=maxI;
		curBlock->x=maxJ;
		//vieng tham cac block khac(ket nap them cac block voi block[maxI][maxJ] hat giong 
		//de tao vung moi)
		HeuristicSegVisit(label,blocks,rowscols_of_blocks,curBlock,1,dKR,hEKCK);
		free(curBlock);curBlock=NULL;
Ghi chu:
	Ham nay khong the goi truc tiep tu ben ngoai duoc, no duoc goi tu ben trong cua ham	
		CAGimage::HeuristicSeg
	Khoi co the duoc goi la block(thuat ngu block va khoi duoc dung qua lai lan nhau) vung bao gom 
		nhieu block(khoi) co the duoc goi la mang block, hay object
	Toa do cua 1 block am chi vi tri cua block do trong mang block 2 chieu-tham so blocks vi thuat 
		toan phan doan Heuristic se chia anh thanh mang 2 chieu cac block, moi block co kich thuoc 
		co dinh nao do nao do(24*24 pixel, 8*8 pixel,..)
*/
void CAGimage::HeuristicSegVisit(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT*& curBlock, aguint16& nCurBlock, agreal64 dKR, agreal64 hEKCK)
{
	//mang curBlock trong thuat toan goi la vung J
	if(!curBlock)	throw _T("Current Block can not be NULL");

	//lan can cua mang block hien hanh(mang block J, co the goi la vung J-1vung co nhieu block), 
	//nhung block lan can nay goi la nhung block K
	AGBU_POINT*	pKNeighborBlocks=NULL;//mang block chua nhung block lan can cua vung J
	agint32	nKNeighborBlocks=0;//so block lan can cua vung J
	//sau khi ham NeighborBlocks duoc goi neu nKNeighborBlocks=0 thi pKNeighborBlocks=NULL,
	//co nghia la vung J khong co lan can
	nKNeighborBlocks=HeuristicNeighborBlocks(label,blocks,rowscols_of_blocks,curBlock,nCurBlock,pKNeighborBlocks);

	for(agint32 i=0;i<nKNeighborBlocks;i++)//xet tung block lan can(tung block K) cua vung block hien hanh(vung J)
	{
		agint_bu_ycoord KI=pKNeighborBlocks[i].y;
		agint_xcoord	KJ=pKNeighborBlocks[i].x;
		if(blocks[KI][KJ].label!=0)//neu nhu block lan can nay da thuoc 1 vung nao do
			continue;
		
		//lan can 8 cua block K, nhung block lan can nay goi la nhung(mang 8) block Y
		AGBU_POINT	pYNeighbor8Blocks[8];
		agint32	nYNeighbor8Blocks=0;
		nYNeighbor8Blocks=GetNeighbor8Blocks(rowscols_of_blocks,pKNeighborBlocks[i],pYNeighbor8Blocks);
		if(nYNeighbor8Blocks==0)		continue;//block K khong co lan can 8 nao thi bo qua

		//tim H(K,Rj) nho nhat (cua block K)
		agreal64	Ymin=2.0;//Ymin dai dien cho min(dhist(K,Y) trong thuat toan
		for(agint32 j=0;j<nYNeighbor8Blocks;j++)//duyet tung lan can 8(Y) cua block K
		{
			//YI, YJ la dong, cot cua tung lan can 8 Y cua block J
			agint_bu_ycoord YI=pYNeighbor8Blocks[j].y;
			agint_xcoord	YJ=pYNeighbor8Blocks[j].x;
			if(blocks[YI][YJ].label==label)
			{
				//tinh khoang cach ve muc xam giua block K va block Y lan can voi block K
				//KI, KJ lan luot la dong, cot cua block K
				//YI, YJ lan luot la dong, cot cua block J
				agreal64 dis=AGABS_OF_SUB(blocks[KI][KJ].GrayLevel, blocks[YI][YJ].GrayLevel);
				if(dis<Ymin)
				{
					Ymin=dis;
					//YImin=YI; YJmin=YJ;
				}
			}
		}
		if(Ymin==2.0)	continue;// neu nu khong tim duoc Ymin tuc min(dhist(K,Y)) thi bo qua

		agreal64 HK=1-Ymin;//H(K,Rj)=1-min(dhist(K,Y))
		agreal64 deltaK=blocks[KI][KJ].EX + blocks[KI][KJ].CX + HK;//delta(K,Rj)=E(K)+C(K)+H(K,Rj)
		if(deltaK>dKR && blocks[KI][KJ].EX + blocks[KI][KJ].CX > hEKCK)//Neu delta(K,Rj)>1.0 va E(K)+C(K)>0.7
		{
			blocks[KI][KJ].label=label;//ket nap block K vao vung J

			//Nhung thao tac sau chi muc dich gian mang curBlock(vung J) de ket nap block K vao 
			//cuoi mang curBlock(vung J)

			curBlock=(AGBU_POINT*)realloc(curBlock,(nCurBlock+1)*sizeof(AGBU_POINT));//no rong curBlock(vung J) 1 phan tu
			curBlock[nCurBlock].y=KI;//chep block K vao cuoi curBlock(vung J)
			curBlock[nCurBlock].x=KJ;////chep block K vao cuoi curBlock(vung J)

			nCurBlock ++;
			//bay gio curBlock tuc vung J da no rong, duyet de quy de tiep cua no rong vung J
			HeuristicSegVisit(label,blocks,rowscols_of_blocks,curBlock,nCurBlock,dKR,hEKCK);
		}
	}
	if(pKNeighborBlocks)
	{
		free(pKNeighborBlocks);
		pKNeighborBlocks=NULL;
	}
}
/*
aguint8	CAGimage::GetNeighbor8Blocks(SIZE rowscols_of_blocks, AGBU_POINT curBlock, AGBU_POINT pNeighbor8Blocks[8])
Chuc nang:
	Tim lan can can 8 cua mot block (la tham so curBlock), ham nay tuong tu nhu ham 
		CAGimage::GetNeighbor8Pixels nhung thay vi tim cac pixel lan can 8 cua 1 pixel thi bay	gio 
		tim cac block lan can 8 cua 1 block
		***
		*+*
		***
		(block lan can la dau "*")
	So block lan can 8 cua mot block luon <=8
Tham so vao:
	curBlock : toa do cua block hien hanh can tim lan can 8
	rowscols_of_blocks: kieu SIZE. Day la kich thuoc dong cot cua mang block 2 chieu dai dien cho 
		toan bo cac block cua anh. Nen nho toa do cua mot block am chi vi tri cua block do trong 
		mang block 2 chieu cua anh. Thuat toan phan doan Heuristic (hay thuat toan nao do)se chia 
		anh thanh mang 2 chieu cac block, rowscols_of_blocks chinh la kich thuoc dong va cot cua 
		mang 2 chieu cac block nay
Tham so ra:
	pNeighbor8Blocks: kieu mang 8 AGBU_POINT. Tham so nay la Mang chua toa do cua cac block lan can block 
		curBlock, mang nay mac dinh gom 8 phan tu, tuy nhien so phan tu that su co the < 8 vi cac 
		block o bien co so block lan can < 8 (trong truong hop nay phan phan tu doi ra cua pNeighbor8Blocks 
		se duoc dien toa do x=y=-1).
		Tham so nay phai duoc khai bao tuc khoi tao truoc(VD:AGBU_POINT	pNeighbor8Blocks[8])
Tra ve:
	So block lan can thuc su cua curBlock(cac block bien co so block lan can <8)
Cach dung:
	Ham nay duoc goi tu ben trong ham CAGimage::HeuristicSegVisit, CAGimage::HeuristicNeighborBlocks 
		nhung no cung co the duoc goi truc tiep tu ben ngoai.
	VD:
	CAGimage* pAGimage=new CAGimage();
	pAGimage->Load(_T("myPicture.gif"));
	pAGimage->Init();

	SIZE	rowscols_of_blocks;//tong so dong cot cua tat ca cac block cua anh
	rowscols_of_blocks.cy=16;
	rowscols_of_blocks.cx=16;
	AGBU_POINT	curBlock;//block hien hanh can tim lan can
	curBlock.y=4;
	curBlock.x=2;
	AGBU_POINT	pNeighbor8Blocks[8];//mang chua cac block lan can
	aguint8	nBlocks;// so block lan can cua block hien hanh(<=8)
	nBlocks=pAGimage->GetNeighbor8Blocks(rowscols_of_blocks,curBlock, pNeighbor8Blocks);//thuat toan

	//lam cai gi do voi pNeighbor8Blocks;
	//....
	delete pAGimage;

Ghi chu:
	Toa do cua 1 block am chi vi tri cua block do trong mang block 2 chieu vi thuat toan phan doan 
		Heuristic(hay thuat toan nao do) se chia anh thanh mang 2 chieu cac block, moi block co kich 
		thuoc co dinh nao do (24*24 pixel, 8*8 pixel,..)
*/
aguint8	CAGimage::GetNeighbor8Blocks(SIZE rowscols_of_blocks, AGBU_POINT curBlock, AGBU_POINT pNeighbor8Blocks[8])
{
	aguint8	nNeighbor8Blocks=0;
	for(agint32 i=-1; i<=1; i++)
	{
		for(agint32 j=-1; j<=1; j++)
		{
			if(i==0 && j==0)	continue;

			AGBU_POINT neighborBlock;
			neighborBlock.x=curBlock.x + j;
			neighborBlock.y=curBlock.y+ i;
			if(neighborBlock.x>=0 && neighborBlock.x<rowscols_of_blocks.cx && 
			   neighborBlock.y>=0 && neighborBlock.y<rowscols_of_blocks.cy)
			{
				pNeighbor8Blocks[nNeighbor8Blocks]=neighborBlock;
				nNeighbor8Blocks++;
			}
		}
	}
	for(agint32 n=nNeighbor8Blocks; n<8; n++)
		pNeighbor8Blocks[n].x=pNeighbor8Blocks[n].y=-1;
	return nNeighbor8Blocks;
}
/*
aguint16	CAGimage::HeuristicNeighborBlocks(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT* curBlocks, aguint16 nCurBlocks, AGBU_POINT*& pNeighborBlocks)
Chuc nang:
	Tim tat ca cac lan can can cua mot vung (mang block-la tham so curBlocks), ham nay tuong tu nhu 
		ham CAGimage::GetNeighbor8Pixels, CAGimage::GetNeighbor8Blocks nhung thay vi tim cac pixel 
		lan can 8 cua mot pixel hay cac block lan can 8 cua mot block thi bay	gio tim tat cac cac 
		block lan can cua mot vung(mang block)
	Tat ca cac block lan can cua cua mot vung(mang block) co the > 8
	Thuc te ham nay se duyet tung block phan tu cua vung hien hanh curBlocks va tim lan can 8 cua 
		tung block nay, co nghia la ham nay se tim tat ca lan can 8 cua tat ca cac block phan tu cua 
		vung curBlocks hien hanh, do do ham nay se goi ham CAGimage::GetNeighbor8Blocks
Tham so vao:
	lable: nhan chung cua vung curBlocks
	blocks: mang 2 chieu kieu HEURISTIC_SEG_BLOCK. Day la mang tat ca cac block cua anh. Moi phan 
		tu cua tham so blocks tuong trung cho mot block duoc gan nhan cua vung ma block do thuoc ve. 
		Tham so nay o day chi doc(readonly) duoc dung de tham chieu den nhan cua cac block lan can 
		cua bloc hien hanh
	rowscols_of_blocks: kieu SIZE. Day la kich thuoc dong cot cua mang block(tham so blocks) 2 chieu 
		dai dien cho toan bo cac block cua anh. Nen nho toa do cua 1 block am chi vi tri cua block do 
		trong mang block 2 chieu cua anh.Thuat toan phan doan Heuristic (hay thuat toan nao do)se 
		chia anh thanh mang 2 chieu cac block, rowscols_of_blocks chinh la kich thuoc dong va cot cua 
		mang 2 chieu cac block nay(tuc tham so blocks)
	curBlocks : mang cac toa do cac block cua vung(region hay mang block)hien hanh can tim cac lan can.
		Nen nho cac block trong vung curBlocks phai lien ket voi nhau khong duoc roi rac. Co the xem 
		tham so nay nhu la vung hien hanh can tim lan can
Tham so ra:
	pNeighborBlocks: tham chieu kieu mang AGBU_POINT. Tham so nay la Mang chua toa do cua cac block lan can
		vung curBlocks. Tham pNeighborBlocks se duoc cap phai dong trong ham nay, do do ta nen khoi 
		gan tham so pNeighborBlocks la NULL truoc khi goi ham nay, sau khi ham nay thuc hien xong ta 
		nen free(giai phong) tham so pNeighborBlocks neu no khac NULL. Sau moi lan goi pNeighborBlocks
		se thay doi dia chi neu nhu no no+? rong, vi the tham so nay la tham chieu
Tra ve:
	So block lan can thuc su cua vung hien hanh curBlocks(So block lan can nay co the >8)
Cach dung:
	Ham nay duoc goi tu ben trong ham CAGimage::HeuristicSegVisit nhung no cung co the duoc goi 
		truoc tiep tu ben ngoai.
	VD:
	CAGimage* pAGimage=new CAGimage();
	pAGimage->Load(_T("myPicture.gif"));
	pAGimage->Init();

	SIZE	rowscols_of_blocks;
	rowscols_of_blocks.cy=16;
	rowscols_of_blocks.cx=16;
	AGBU_POINT	curBlock[5];
	curBlock[0].y=0;	curBlock[0].x=0;
	curBlock[1].y=0;	curBlock[1].x=1;
	curBlock[2].y=0;	curBlock[2].x=2;
	curBlock[3].y=1;	curBlock[3].x=0;
	curBlock[4].y=1;	curBlock[4].x=1;

	AGBU_POINT	pNeighbor8Blocks=NULL;//mang chua cac block lan can, nen duoc khoi gan la NULL vi 
								//ham CAGimage::HeuristicNeighborBlocks se cap phat vung nho 
								//cho pNeighbor8Blocks
	aguint8	nBlocks;// so block lan can cua vung hien hanh(co the lon hon 8)
	nBlocks=pAGimage->HeuristicNeighborBlocks(rowscols_of_blocks,curBlock,pNeighbor8Blocks);

	//lam cai gi do voi pNeighbor8Blocks;
	//....
	if(pNeighbor8Blocks)	{free(pNeighbor8Blocks); pNeighbor8Blocks=NULL;}
	delete pAGimage;
Ghi chu:
	Toa do cua 1 block am chi vi tri cua block do trong mang block 2 chieu vi thuat toan phan doan 
		Heuristic(hay thuat toan nao do) se chia anh thanh mang 2 chieu cac block, moi block co 
		kich thuoc co dinh nao do (24*24 pixel, 8*8 pixel,..)
	Khoi co the duoc goi la block(thuat ngu block va khoi duoc dung qua lai lan nhau) vung bao gom 
		nhieu block(khoi) co the duoc goi la mang block hay object
*/
aguint16	CAGimage::HeuristicNeighborBlocks(agint32 label, HEURISTIC_SEG_BLOCK** blocks, SIZE rowscols_of_blocks, AGBU_POINT* curBlocks, aguint16 nCurBlocks, AGBU_POINT*& pNeighborBlocks)
{
	if(pNeighborBlocks)	{free(pNeighborBlocks); pNeighborBlocks=NULL;};//free pNeighborBlocks de cap phat lai

	aguint16	nNeighborBlocks=0;
	for(aguint16 i=0; i<nCurBlocks; i++)//duyet tung block cua vung curBlocks
	{
		AGBU_POINT	curBlock=curBlocks[i];//lay ra mot block
		AGBU_POINT	pNeighbor8Blocks[8];
		aguint8	nNeighbor8Blocks;
		nNeighbor8Blocks=GetNeighbor8Blocks(rowscols_of_blocks,curBlock,pNeighbor8Blocks);//tim lan can 8 cua block lay ra
		if(nNeighbor8Blocks==0)	continue;//neu nhu block lay ra do khong co lan can thi bo qua

		AGBU_POINT*	pUsedBlocks=NULL;//mang chua nhung block thuc su lan can voi curBlocks
		aguint16 nUsedBlocks=0;//so block thuc su lan can voi curBlocks
		for(aguint16 j=0; j<nNeighbor8Blocks; j++)//duyet tung block lan can 8
		{
			agint_bu_ycoord row=pNeighbor8Blocks[j].y;
			agint_xcoord	col=pNeighbor8Blocks[j].x;
			//nen nho ta chi tim nhung block lan can voi curBlock nhung chi bao gom :nhung 
			//block nam khong thuoc ve vung(region, object) nao tuc co nhan bang 0, do do ta 
			//phai loai tru nhung nhan !=0
			if(blocks[row][col].label!=0)	continue;
			if(pNeighborBlocks)
			{
				aguint16 k=0;
				for(k=0; k<nNeighborBlocks; k++)
					if(row==pNeighborBlocks[k].y && col==pNeighborBlocks[k].x)
						break;
				if(k<nNeighborBlocks)	continue;//da co roi
			}

			if(pUsedBlocks==NULL)
				pUsedBlocks=(AGBU_POINT*)malloc(sizeof(AGBU_POINT));
			else
				pUsedBlocks=(AGBU_POINT*)realloc(pUsedBlocks,(nUsedBlocks+1)*sizeof(AGBU_POINT));
			pUsedBlocks[nUsedBlocks].y=row;
			pUsedBlocks[nUsedBlocks].x=col;
			nUsedBlocks++;
		}
		if(nUsedBlocks==0)	continue;

		if(pNeighborBlocks==NULL)//neu nhu block lay ra la block dau tien(tuc la pNeighborBlocks==NULL) thi cap phat pNeighborBlocks
		{
			pNeighborBlocks=(AGBU_POINT*)malloc(nUsedBlocks*sizeof(AGBU_POINT));//cap phat pNeighborBlocks
			memcpy(pNeighborBlocks,pUsedBlocks,nUsedBlocks*sizeof(AGBU_POINT));
		}
		else//neu nhu block lay ra la khong la block dau tien(tuc pNeighborBlocks!=NULL) thi no rong vunh nho pNeighborBlocks
		{
			pNeighborBlocks=(AGBU_POINT*)realloc(pNeighborBlocks,(nNeighborBlocks+nUsedBlocks)*sizeof(AGBU_POINT));
			memcpy(pNeighborBlocks+nNeighborBlocks,pUsedBlocks,nUsedBlocks*sizeof(AGBU_POINT));
		}
		nNeighborBlocks +=nUsedBlocks;

		if(pUsedBlocks) free(pUsedBlocks);
	}
	return nNeighborBlocks;
}

/*******************************class CAGimageGrayScale***************************************/

//////////////////////////////////constructors/////////////////////////////////////////////////////
/*
CAGimageGrayScale::CAGimageGrayScale(aguint32 imagetype):CAGimage(imagetype)
CAGimageGrayScale::CAGimageGrayScale(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype):CAGimage(dwWidth,dwHeight,wBpp,imagetype)
CAGimageGrayScale::CAGimageGrayScale(const CAGimage &src, agbool copypixels, agbool copyselection, agbool copyalpha):CAGimage(src,copypixels,copyselection,copyalpha)
CAGimageGrayScale::CAGimageGrayScale(const agint8 * filename, aguint32 imagetype):CAGimage(filename,imagetype)
CAGimageGrayScale::CAGimageGrayScale(FILE * stream, aguint32 imagetype):CAGimage(stream,imagetype)
CAGimageGrayScale::CAGimageGrayScale(CxFile * stream, aguint32 imagetype):CAGimage(stream,imagetype)
CAGimageGrayScale::CAGimageGrayScale(aguint8 * buffer, aguint32 size, aguint32 imagetype):CAGimage(buffer,size,imagetype)

Chuc nang:
	Cac ham constructor cho lop CAGimageGrayScale
Tham so vao:
	imagetype: kieu dinh dang co the cua anh, bao gom cac gia tri sau:
		CXIMAGE_FORMAT_JPG, CXIMAGE_FORMAT_TIF, CXIMAGE_FORMAT_MNG, CXIMAGE_FORMAT_BMP, 
		CXIMAGE_FORMAT_ICO, CXIMAGE_FORMAT_GIF, CXIMAGE_FORMAT_PNG, CXIMAGE_FORMAT_PCX, 
		CXIMAGE_FORMAT_TGA, CXIMAGE_FORMAT_WMF, CXIMAGE_FORMAT_JBG, CXIMAGE_FORMAT_J2K,
		CXIMAGE_FORMAT_JP2, CXIMAGE_FORMAT_JPC, CXIMAGE_FORMAT_PGX, CXIMAGE_FORMAT_PNM, 
		CXIMAGE_FORMAT_RAS, CXIMAGE_FORMAT_WBMP
		voi dinh dang tu dong, tu phat hien kieu dinh dang anh dua tren phan mo rong cua file ta 
			dung kieu CXIMAGE_FORMAT_UNKNOWN
	dwWidth, dwHeight: chieu rong va dai cua anh
	wBpp: so bit cua 1 pixel, bao gom cac gia tri: 1, 4, 8, 16, 24, 32
	src: anh nguon dung de khoi tao mot anh
	copypixels: =agtrue: copy noi dung cua anh nguon, nguoc lai la khong
	copyselection: =agtrue: copy vung selection, nguoc lai la khong
	copyalpha: =agtrue: copy kenh alpha, nguoc lai la khong
	filename: duong dan cua file anh
	stream: con tro dem stream file anh hay con tro den CxFile-dai dien cho file anh
	buffer: vung nho chua anh, tham so nay luon di kem voi tham so size chi kich thuoc cua buffer
	size: kich thuoc cua tham so buffer o tren
Tham so ra:
Tra ve:
Cach dung:
	CAGimageGrayScale* pAGimageGrayScale=new CAGimageGrayScale(CXIMAGE_FORMAT_BMP);
	delete pAGimageGrayScale;
Ghi chu:
	Tat ca nhung ham khoi tao nay deu goi ham khoi tao cua lop cha CAGimage, sau do tat ca cac ham 
		khoi tao nay deu goi ham CAGimageGrayScale::Init de khoi tao cac thong so dac biet danh rieng 
		cho lop CAGimageGrayScale
*/
CAGimageGrayScale::CAGimageGrayScale(aguint32 imagetype):CAGimage(imagetype)
{
	Init();
}
CAGimageGrayScale::CAGimageGrayScale(aguint32 dwWidth, aguint32 dwHeight, aguint32 imagetype):CAGimage(dwWidth,dwHeight,8,imagetype)
{
	Init();
}
CAGimageGrayScale::CAGimageGrayScale(const CAGimageGrayScale &src, agbool copypixels, agbool copyselection, agbool copyalpha):CAGimage(src,copypixels,copyselection,copyalpha)
{
	m_eColorSpace=src.m_eColorSpace;
	m_nPixelMaxValue=src.m_nPixelMaxValue;
}
CAGimageGrayScale::CAGimageGrayScale(const agtchar * filename, aguint32 imagetype):CAGimage(filename,imagetype)
{
	Init();
}
CAGimageGrayScale::CAGimageGrayScale(FILE * stream, aguint32 imagetype):CAGimage(stream,imagetype)
{
	Init();
}
CAGimageGrayScale::CAGimageGrayScale(CxFile * stream, aguint32 imagetype):CAGimage(stream,imagetype)
{
	Init();
}
CAGimageGrayScale::CAGimageGrayScale(aguint8 * buffer, aguint32 size, aguint32 imagetype):CAGimage(buffer,size,imagetype)
{
	Init();
}

////////////////////////////////////////////initialization/////////////////////////////////////
/*
void CAGimageGrayScale::Init()
Chuc nang:
	Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau khi ham Load, Create, 
		Clear,..day la ham ao nen no se duoc ovverride o cac lop devired, khong nen goi ham nay ngay 
		sau khi khoi tao vi ban than cac ham khoi tao da goi ham Init nay. Noi chung la ham nay chi
		duoc goi sau khi goi cac ham Initialization cua CAGimage nhu: Create, Clear, Copy, CreateFromHBITMAP, 
		CreateFromHICON, CreateFromHANDLE, CreateFromARGB, Transfer
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimageGrayScale* pAGimageGrayScale=new CAGimageGrayScale();
	pAGimageGrayScale->Load(_T("myPicture.gif"));
	pAGimageGrayScale->Init();
	//do here something...
	//.............
	pAGimageGrayScale->Create(200,100,8);
	pAGimageGrayScale->Init();
	//do here something...
	//.............
	delete pAGimageGrayScale;
Ghi chu:
	Ngay Sau khi khoi tao khong can goi ham Init

	CAGimageGrayScale* pAGimageGrayScale=new CAGimageGrayScale();
	pAGimageGrayScale->Init();//khong can thiet
	delete pAGimageGrayScale;
*/

void CAGimageGrayScale::Init()
{
	if(GetBpp()<8)		IncreaseBpp(8);
	else if(GetBpp()>8)	DecreaseBpp(8,agtrue);

	if(!IsGrayScale())	GrayScale();
	m_eColorSpace=AGMAGICIP_COLORSPACE_UNKNOWN;//Trong anh gray scale, khong gian mau khong co ngu nghia
	m_nPixelMaxValue=255;
}
/*
void CAGimage::Copy()
Chuc nang:
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageGrayScale::Copy(CAGimage* psrc, agbool copypixels, agbool copyselection, agbool copyalpha)
{
	CAGimage::Copy(psrc,copypixels,copyselection,copyalpha);
	
	if(psrc->GetClassType()!=AGMAGICIP_GRAYSCALE_CLASSTYPE)
		Init();
	else
	{
		m_eColorSpace=psrc->GetColorSpace();//Trong anh gray scale, khong gian mau khong co ngu nghia
		m_nPixelMaxValue=psrc->GetPixelMaxI();
	}
}

////////////////////////////////////////////Destruction////////////////////////////////////////////
/*
CAGimageGrayScale::~CAGimageGrayScale()
Chuc nang:
	Ham huy mac dinh
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
CAGimageGrayScale::~CAGimageGrayScale()
{
}
/*
void CAGimageGrayScale::Destroy()
Chuc nang:
	Ham huy tu tao
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimageGrayScale* pAGimageGrayScale=new CAGimageGrayScale();
	pAGimageGrayScale->Load(_T("myPicture.gif"));
	pAGimageGrayScale->Init();
	//do here somthing....
	//..........
	pAGimageGrayScale->Destroy();
	pAGimageGrayScale->Create(200,100,24);
	pAGimageGrayScale->Init();
	//do here somthing
	//.............
	delete pAGimageGrayScale;
Ghi chu:
*/
void CAGimageGrayScale::Destroy()
{
	CAGimage::Destroy();
}

/////////////////////////////Color conversion utilities////////////////////////////////////////////

/*
agbool CAGimageGrayScale::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
Chuc nang:
	Ham nay override ham lop cha, no se throw 1 exception do trong anh gray scale khong gian mau 
		khong co ngu nghia
Tham so vao: khong can quan tam
Tham so ra: khong can quan tam
Tra ve: khong can quan tam
Cach dung:
Ghi chu:
*/
agbool CAGimageGrayScale::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
{
	throw _T("Color Space not meaning in gray scale image");
}

////////////////////////////////////Pixel operations///////////////////////////////////////////////

/*
aguint8 CAGimageGrayScale::GetPixelMaxI()
Chuc nang:
	Lay gia tri lon nhat co the co cua muc xam 1 pixel. Ham nay override lop cha
Tham so vao:
Tham so ra:
Tra ve:
	Gia tri lon nhat co the co cua muc xam 1 pixel
Cach dung:
	aguint8 maxValue=pAGimageGrayScale->GetPixelMaxI();
Ghi chu:
*/
aguint8 CAGimageGrayScale::GetPixelMaxI()
{
	return m_nPixelMaxValue;
}
/*
aguint8 CAGimageGrayScale::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y. Ham nay override lop cha CAGimage
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimageGrayScale->GetPixelI();
Ghi chu:
*/
aguint8 CAGimageGrayScale::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
{
	if(!IsInside(x,y))	return 0;
	return info.pImage[y*info.dwEffWidth + x];
}

/*
aguint8 CAGimageGrayScale::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y. Ham nay override lop cha CAGimage
	Ham nay giong nhu ham GetPixelI(agint_xcoord x, agint_bu_ycoord y) nhung se xu ly nhanh hon do khong kiem 
		tra rang buoc
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimageGrayScale->GetPixelIFast();
Ghi chu:
*/
aguint8 CAGimageGrayScale::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
{
	return info.pImage[y*info.dwEffWidth + x];
}
/*
void CAGimageGrayScale::SetPixelMaxI(aguint8 value)
Chuc nang:
	Dat gia tri lon nhat cho muc xam 1 pixel
Tham so vao:
	value: gia tri lon nhat can dat cho pixel
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageGrayScale::SetPixelMaxI(aguint8 value)
{
	m_nPixelMaxValue=value;
}
/*
void CAGimageGrayScale::SetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8 value)
Chuc nang:
	Dat gia tri cho 1 pixel
Tham so vao:
	x,y : toa do cua pixel
	value: gia tri can dat cho pixel
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageGrayScale::SetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8 value)
{
	if(!IsInside(x,y)) return;
	info.pImage[y*info.dwEffWidth + x]=value;
}
/*
void CAGimageGrayScale::SetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8 value)
Chuc nang:
	Dat gia tri cho 1 pixel. 
	Ham nay giong nhu ham SetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8 value) nhung nhanh hon do khong 
		kiem tra rang buoc
Tham so vao:
	x,y : toa do cua pixel
	value: gia tri can dat cho pixel
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageGrayScale::SetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8 value)
{
	info.pImage[y*info.dwEffWidth + x]=value;
}

/*******************************class CAGimageMultiPlans***************************************/

///////////////////////////////////////constructors////////////////////////////////////////////////
/*
CAGimageMultiPlans::CAGimageMultiPlans(aguint32 imagetype):CAGimage(imagetype)
CAGimageMultiPlans::CAGimageMultiPlans(aguint32 dwWidth, aguint32 dwHeight, aguint32 wBpp, aguint32 imagetype):CAGimage(dwWidth,dwHeight,wBpp,imagetype)
CAGimageMultiPlans::CAGimageMultiPlans(const CAGimage &src, agbool copypixels, agbool copyselection, agbool copyalpha):CAGimage(src,copypixels,copyselection,copyalpha)
CAGimageMultiPlans::CAGimageMultiPlans(const agint8 * filename, aguint32 imagetype):CAGimage(filename,imagetype)
CAGimageMultiPlans::CAGimageMultiPlans(FILE * stream, aguint32 imagetype):CAGimage(stream,imagetype)
CAGimageMultiPlans::CAGimageMultiPlans(CxFile * stream, aguint32 imagetype):CAGimage(stream,imagetype)
CAGimageMultiPlans::CAGimageMultiPlans(aguint8 * buffer, aguint32 size, aguint32 imagetype):CAGimage(buffer,size,imagetype)

Chuc nang:
	Cac ham constructor cho lop CAGimageMultiPlans
Tham so vao:
	imagetype: kieu dinh dang co the cua anh, bao gom cac gia tri sau:
		CXIMAGE_FORMAT_JPG, CXIMAGE_FORMAT_TIF, CXIMAGE_FORMAT_MNG, CXIMAGE_FORMAT_BMP, 
		CXIMAGE_FORMAT_ICO, CXIMAGE_FORMAT_GIF, CXIMAGE_FORMAT_PNG, CXIMAGE_FORMAT_PCX, 
		CXIMAGE_FORMAT_TGA, CXIMAGE_FORMAT_WMF, CXIMAGE_FORMAT_JBG, CXIMAGE_FORMAT_J2K,
		CXIMAGE_FORMAT_JP2, CXIMAGE_FORMAT_JPC, CXIMAGE_FORMAT_PGX, CXIMAGE_FORMAT_PNM, 
		CXIMAGE_FORMAT_RAS, CXIMAGE_FORMAT_WBMP
		voi dinh dang tu dong, tu phat hien kieu dinh dang anh dua tren phan mo rong cua file ta 
			dung kieu CXIMAGE_FORMAT_UNKNOWN
	dwWidth, dwHeight: chieu rong va dai cua anh
	wBpp: so bit cua 1 pixel, bao gom cac gia tri: 1, 4, 8, 16, 24, 32
	src: anh nguon dung de khoi tao mot anh
	copypixels: =agtrue: copy noi dung cua anh nguon, nguoc lai la khong
	copyselection: =agtrue: copy vung selection, nguoc lai la khong
	copyalpha: =agtrue: copy kenh alpha, nguoc lai la khong
	filename: duong dan cua file anh
	stream: con tro dem stream file anh hay con tro den CxFile-dai dien cho file anh
	buffer: vung nho chua anh, tham so nay luon di kem voi tham so size chi kich thuoc cua buffer
	size: kich thuoc cua tham so buffer o tren
Tham so ra:
Tra ve:
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans(CXIMAGE_FORMAT_BMP);
	delete pAGimageMultiPlans;
Ghi chu:
	Tat ca nhung ham khoi tao nay deu goi ham khoi tao cua lop cha CAGimage, sau do tat ca cac ham 
		khoi tao nay deu goi ham CAGimageMultiPlans::Init de khoi tao cac thong so dac biet danh rieng 
		cho lop CAGimageMultiPlans de cap nhat du lieu cac tang mau
	Khong gian mau mac dinh la khong gian RGB
*/
CAGimageMultiPlans::CAGimageMultiPlans(aguint32 imagetype):CAGimage(imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}
CAGimageMultiPlans::CAGimageMultiPlans(aguint32 dwWidth, aguint32 dwHeight, aguint32 imagetype):CAGimage(dwWidth,dwHeight,24,imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}
CAGimageMultiPlans::CAGimageMultiPlans(const CAGimageMultiPlans &src, agbool copypixels, agbool copyselection, agbool copyalpha):CAGimage(src,copypixels,copyselection,copyalpha)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	if(src.m_pFirstPlan && src.m_pSecondPlan && src.m_pThirdPlan)
	{
		m_pFirstPlan=new CAGimageGrayScale(*src.m_pFirstPlan);
		m_pSecondPlan=new CAGimageGrayScale(*src.m_pSecondPlan);
		m_pThirdPlan=new CAGimageGrayScale(*src.m_pThirdPlan);
	}
#if CXIMAGE_SUPPORT_ALPHA
	if(src.m_pAlphaPlan)
		m_pAlphaPlan=new CAGimageGrayScale(*src.m_pAlphaPlan);
#endif
	if(src.m_pGrayPlan)
		m_pGrayPlan=new CAGimageGrayScale(*src.m_pGrayPlan);

	m_mode=src.m_mode;//AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
					//AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau
	m_bConsistent=src.m_bConsistent;
}
CAGimageMultiPlans::CAGimageMultiPlans(const agtchar * filename, aguint32 imagetype):CAGimage(filename,imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}
CAGimageMultiPlans::CAGimageMultiPlans(FILE * stream, aguint32 imagetype):CAGimage(stream,imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}
CAGimageMultiPlans::CAGimageMultiPlans(CxFile * stream, aguint32 imagetype):CAGimage(stream,imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}
CAGimageMultiPlans::CAGimageMultiPlans(aguint8 * buffer, aguint32 size, aguint32 imagetype):CAGimage(buffer,size,imagetype)
{
	m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;
	Init();
}

////////////////////////////////////////////initialization/////////////////////////////////////
/*
void CAGimageMultiPlans::Init()
Chuc nang:
	Ham nay khoi tao them 1 so dieu can thiet, ham nay phai duoc goi ngay sau khi ham Load, Create, 
	Clear, Copy, CreateFromHBITMAP, CreateFromHICON, CreateFromHANDLE, CreateFromARGB, Transfer. Day 
	la ham ao nen no se duoc override o cac lop devired, khong nen goi ham nay ngay sau khi khoi tao
	vi ban than cac ham khoi tao da goi ham Init nay. Noi chung la ham nay chi duoc goi sau khi goi 
	cac ham Initialization cua CAGimage nhu: Create, Clear, Copy, CreateFromHBITMAP, CreateFromHICON, 
	CreateFromHANDLE, CreateFromARGB, Transfer
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans();
	pAGimageMultiPlans->Load(_T("myPicture.gif"));
	pAGimageMultiPlans->Init();
	//do here something...
	//.............
	pAGimageMultiPlans->Create(200,100,8);
	pAGimageMultiPlans->Init();
	//do here something...
	//.............
	delete pAGimageMultiPlans;
Ghi chu:
	Ngay Sau khi khoi tao khong can goi ham Init
		CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans();
		//pAGimageMultiPlans->Init();//khong can thiet
		delete pAGimageMultiPlans;
*/
void CAGimageMultiPlans::Init()
{
	if(GetBpp()!=24) IncreaseBpp(24);
	m_eColorSpace=AGMAGICIP_COLORSPACE_RGB;

	PlansDestroy();
	SetMode(AGMAGICIP_MULTIPLANS_INSIDEMODE);
	SetNotConsistent();//xem nhu du lieu noi tai va cac tang mau chua nhat quan
	UpdateConsistent();//cap nhat de nhat quan giua du lieu noi tai va cac tang mau
}
/*
void CAGimage::Copy()
Chuc nang:
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageMultiPlans::Copy(CAGimage* psrc, agbool copypixels, agbool copyselection, agbool copyalpha)
{
	CAGimage::Copy(psrc,copypixels,copyselection,copyalpha);
	
	if(psrc->GetClassType()!=AGMAGICIP_MULTIPLANS_CLASSTYPE)
		Init();
	else
	{
		m_eColorSpace=psrc->GetColorSpace();
		m_pFirstPlan=m_pSecondPlan=m_pThirdPlan=m_pAlphaPlan=m_pGrayPlan=NULL;

		CAGimageMultiPlans* pAGimageMultiPlans=(CAGimageMultiPlans*)psrc;
		if(pAGimageMultiPlans->m_pFirstPlan && pAGimageMultiPlans->m_pSecondPlan && pAGimageMultiPlans->m_pThirdPlan)
		{
			m_pFirstPlan=new CAGimageGrayScale(*(pAGimageMultiPlans->m_pFirstPlan));
			m_pSecondPlan=new CAGimageGrayScale(*(pAGimageMultiPlans->m_pSecondPlan));
			m_pThirdPlan=new CAGimageGrayScale(*(pAGimageMultiPlans->m_pThirdPlan));
		}
	#if CXIMAGE_SUPPORT_ALPHA
		if(pAGimageMultiPlans->m_pAlphaPlan)
			m_pAlphaPlan=new CAGimageGrayScale(*(pAGimageMultiPlans->m_pAlphaPlan));
	#endif
		if(pAGimageMultiPlans->m_pGrayPlan)
			m_pGrayPlan=new CAGimageGrayScale(*(pAGimageMultiPlans->m_pGrayPlan));

		m_mode=pAGimageMultiPlans->m_mode;//AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
						//AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau
		m_bConsistent=pAGimageMultiPlans->m_bConsistent;

	}
}


///////////////////////////////////////Destruction/////////////////////////////////////////////////

CAGimageMultiPlans::~CAGimageMultiPlans()
{
	Destroy();
}
/*
void CAGimageMultiPlans::Destroy()
Chuc nang:
	Ham huy tu tao
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans();
	pAGimageMultiPlans->Load(_T("myPicture.gif"));
	pAGimageMultiPlans->Init();
	//do here somthing....
	//..........
	pAGimageMultiPlans->Destroy();
	pAGimageMultiPlans->Create(200,100,24);
	pAGimageMultiPlans->Init();
	//do here somthing
	//............
	delete pAGimageMultiPlans;
Ghi chu:
*/
void CAGimageMultiPlans::Destroy()
{
	PlansDestroy();
	CAGimage::Destroy();
}

///////////////////////////////////Color conversion utilities////////////////////////////////////////////
/*
agbool CAGimageMultiPlans::CAGimage::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
Chuc nang:
	Dat khong gian mau hien hanh
Tham so vao:
	eColorSpace: khong gian mau cac dat, bao gom cac tri
		AGMAGICIP_COLORSPACE_RGB,
		AGMAGICIP_COLORSPACE_HSL,	
		AGMAGICIP_COLORSPACE_YUV,
		AGMAGICIP_COLORSPACE_YIQ, 
		AGMAGICIP_COLORSPACE_XYZ, 
		AGMAGICIP_COLORSPACE_CMYK
	bUpdate : neu la agtrue thi phai cap nhat lai toan bo du lieu theo khong gian mau eColorSpace
			  neu la agfalse thi chi can dat bien m_eColorSpace=eColorSpace, khong can cap nhat lai du lieu
Tham so ra:
Tra ve:
	agtrue : neu thanh cong, nguoc lai la agfalse;
Cach dung:
	enum_colorspace myColorSpace=pAGimageMultiPlans->GetColorSpace();
	if(myColorSpace==AGMAGICIP_COLORSPACE_RGB)
		pAGimageMultiPlans->SetColorSpace(AGMAGICIP_COLORSPACE_HSL);
	if(!pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->UpdateConsistent();
Ghi chu:
	Ham nay se tu dong goi ham SetNotConsistent neu nhu nhan thay giua du lieu noi tai va cac tang mau 
		chua nhat quan voi nhau. Cho nen, au khi su dung ham nay ta phai goi ham 
		CAGimageMultiPlans::IsConsistent de kiem tra su nhat quan, neu can ta se goi ham 
		CAGimageMultiPlans::SetConsistent() de ep nhat quan
*/
agbool CAGimageMultiPlans::SetColorSpace(enum_colorspace eColorSpace, agbool bUpdate)
{
	switch(m_mode)
	{
		case AGMAGICIP_MULTIPLANS_INSIDEMODE:
			if(!CAGimage::SetColorSpace(eColorSpace,bUpdate))	return agfalse;

			if(bUpdate)	SetNotConsistent();
			return agtrue;
		case AGMAGICIP_MULTIPLANS_PLANSMODE:
			if(!PlansIsValid())		return agfalse;
			if (!pDib)				return agfalse;

			if(!bUpdate)
			{
				m_eColorSpace=eColorSpace;
				return agtrue;
			}
			if(m_eColorSpace==eColorSpace)	return agtrue;

			agint_xcoord	xmin,xmax;
			agint_bu_ycoord ymin,ymax;
			xmin = ymin = 0;
			xmax = head.biWidth; ymax=head.biHeight;
			for(agint_bu_ycoord y=ymin; y<ymax; y++)
			{
				for(agint_xcoord x=xmin; x<xmax; x++)
				{
					aguint8		gray;
					AGCLRQUAD	abc;
					PlansGetPixelIFast(x,y,abc,gray);//luc nay rgbReserved trong AGCLRQUAD la tang alpha
					abc.rgbReserved=gray;//boi vi trong he mau CMYK: ta phai chuyen truong rgbReserved
										//trong AGCLRQUAD thanh thanh phan K (tuc gray)
					abc=COLORSPACEtoCOLORSPACE(m_eColorSpace,eColorSpace,abc);
					PlansSetPixelIFast(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,NULL,&gray);
				}
			}
			SetNotConsistent();
			return agtrue;
	}
	return agfalse;
}

/////////////////////////////////////Pixel operations//////////////////////////////////////////////

/*
aguint8 CAGimageMultiPlans::GetPixelMaxI()
Chuc nang:
	Lay gia tri lon nhat co the co cua muc xam 1 pixel. Ham nay override lop cha CAGimage
Tham so vao:
Tham so ra:
Tra ve:
	Gia tri lon nhat co the co cua muc xam 1 pixel
Cach dung:
	aguint8 maxValue=pAGimageMultiPlans->GetPixelMaxI();
Ghi chu:
	Ham nay tuong duong voi ham m_pGrayPlan->GetPixelMaxI, vi the ham nay khong cam thiet lam, muc 
		dich dua ham nay ra chi de cho tuong thich ma thoi
*/
aguint8 CAGimageMultiPlans::GetPixelMaxI()
{
	return m_pGrayPlan->GetPixelMaxI();
}
/*
aguint8 CAGimageMultiPlans::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y. Ham nay override lop cha CAGimage
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimageMultiPlans->GetPixelI();
Ghi chu:
	Ham nay tuong duong voi ham m_pGrayPlan->GetPixelI, vi the ham nay khong cam thiet lam, muc 
		dich dua ham nay ra chi de cho tuong thich ma thoi
*/
aguint8 CAGimageMultiPlans::GetPixelI(agint_xcoord x, agint_bu_ycoord y)
{
	return m_pGrayPlan->GetPixelI(x,y);
}
/*
aguint8 CAGimageMultiPlans::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
Chuc nang:
	Lay muc xam cua pixel tai vi tri x, y. Ham nay override lop cha CAGimage
	Ham nay giong nhu ham GetPixelI(agint_xcoord x, agint_bu_ycoord y) nhung se xu ly nhanh hon do khong kiem 
		tra rang buoc
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
Tra ve:
	Muc xam cua pixel tai vi tri x,y
Cach dung:
	aguint8 value=pAGimageMultiPlans->GetPixelIFast();
Ghi chu:
	Ham nay tuong duong voi ham m_pGrayPlan->GetPixelIFast, vi the ham nay khong cam thiet lam, muc 
		dich dua ham nay ra chi de cho tuong thich ma thoi
*/
aguint8 CAGimageMultiPlans::GetPixelIFast(agint_xcoord x, agint_bu_ycoord y)
{
	return m_pGrayPlan->GetPixelIFast(x,y);
}

////////////////////////////////////////Mode///////////////////////////////////////////////////////

/*
void CAGimageMultiPlans::SetMode(agint8 mode)
Chuc nang:
	Dat che do hien hanh
Tham so vao:
	mode : gia tri can co cua che do hien hanh, co the co cac gia tri
	  AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
	  AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau
Tham so ra:
Tra ve:
	agtrue: neu cap nhat thanh cong
Cach dung:
	//....
	agint8 new_mode=AGMAGICIP_MULTIPLANS_PLANSMODE;
	if(pAGimageMultiPlans->GetMode()!=new_mode)
		pAGimageMultiPlans->SetMode(new_mode);
	if(!pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->UpdateConsistent();
	//..
Ghi chu:
	Ham nay se tu dong goi ham CAGimageMultiPlans::SetNotConsistent. Xem nhu khi chuyen mode moi (neu 
		nhu ham nay phat hien tham so mode truyen vao khac voi thuoc tinh m_mode noi tai) la vi pham 
		su nhat quan giua du lieu noi tai va cac tang mau
*/
void CAGimageMultiPlans::SetMode(agint8 mode)
{
	if(m_mode!=mode)
	{
		m_mode=mode;
		SetNotConsistent();//xem nhu du lieu noi tai va cac tang mau chua nhat quan
	}
}
/*
agint8 CAGimageMultiPlans::GetMode()
Chuc nang:
	Lay che do hien hanh, co the co cac gia tri
	  AGMAGICIP_MULTIPLANS_INSIDEMODE=0: dang o che do chinh sua du lieu noi tai
	  AGMAGICIP_MULTIPLANS_PLANSMODE=1:dang o che do chinh sua cac tang mau
Tham so vao:
Tham so ra:
Tra ve:
	Che do hien hanh
Cach dung:
	//....
	agint8 new_mode=AGMAGICIP_MULTIPLANS_PLANSMODE;
	if(pAGimageMultiPlans->GetMode()!=new_mode)
		pAGimageMultiPlans->SetMode(new_mode);
	if(!pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->UpdateConsistent();
	//..
Ghi chu:
*/
agint8 CAGimageMultiPlans::GetMode()
{
	return m_mode;
}
//////////////////////////Consistent////////////////////////////////////////////
/*
agbool CAGimageMultiPlans::IsConsistent()
Chuc nang:
	Kiem tra du lieu noi tai va cac tang mau co nhat quan khong?
Tham so vao:
Tham so ra:
Tra ve:
	agtrue: neu du lieu noi tai va cac tang mau nhat quan
	agfalse: nguoc lai
Cach dung:
	enum_colorspace myColorSpace=pAGimageMultiPlans->GetColorSpace();
	if(myColorSpace==AGMAGICIP_COLORSPACE_RGB)
		pAGimageMultiPlans->SetColorSpace(AGMAGICIP_COLORSPACE_HSL);
	if(!pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->UpdateConsistent();
Ghi chu:
*/
agbool CAGimageMultiPlans::IsConsistent()
{
	return m_bConsistent;
}

/*
agbool CAGimageMultiPlans::UpdateConsistent()
Chuc nang:
	Cap nhat giua du lieu noi tai va cac tang mau, nham muc dich giu su nhat quan giua cac tang mau 
		va du lieu noi tai
Tham so vao:
Tham so ra:
Tra ve:
	agtrue: neu cap nhat thanh cong
Cach dung:
	enum_colorspace myColorSpace=pAGimageMultiPlans->GetColorSpace();
	if(myColorSpace==AGMAGICIP_COLORSPACE_RGB)
		pAGimageMultiPlans->SetColorSpace(AGMAGICIP_COLORSPACE_HSL);
	if(!pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->UpdateConsistent();
Ghi chu:
*/

agbool CAGimageMultiPlans::UpdateConsistent()
{
	if(IsConsistent())	return agtrue;
	switch(m_mode)
	{
		case AGMAGICIP_MULTIPLANS_INSIDEMODE:
			if(!pDib)	return agfalse;
			PlansDestroy();

			m_pFirstPlan=new CAGimageGrayScale();
			m_pSecondPlan=new CAGimageGrayScale();
			m_pThirdPlan=new CAGimageGrayScale();
#if CXIMAGE_SUPPORT_ALPHA
			m_pAlphaPlan=new CAGimageGrayScale();
#endif
			m_pGrayPlan =new CAGimageGrayScale();

			if(!SplitRGB(m_pFirstPlan,m_pSecondPlan,m_pThirdPlan))
			{
				PlansDestroy();
				return agfalse;
			}
#if CXIMAGE_SUPPORT_ALPHA
			if(!AlphaSplit(m_pAlphaPlan))
			{
				delete m_pAlphaPlan;
				m_pAlphaPlan=NULL;
			}
			else
				m_pAlphaPlan->SetPixelMaxI(AlphaGetMax());
#endif
			m_pGrayPlan->Transfer(*this);
			m_pGrayPlan->GrayScale();

#if CXIMAGE_SUPPORT_SELECTION
			m_pFirstPlan->SelectionCopy(*this);
			m_pSecondPlan->SelectionCopy(*this);
			m_pThirdPlan->SelectionCopy(*this);
			if(m_pAlphaPlan)
				m_pAlphaPlan->SelectionCopy(*this);
			m_pGrayPlan->SelectionCopy(*this);
#endif
			if(!m_pFirstPlan->IsGrayScale())	throw _T("First Plans not gray scale");
			if(!m_pSecondPlan->IsGrayScale())	throw _T("Second Plans not gray scale");
			if(!m_pThirdPlan->IsGrayScale())	throw _T("Third Plans not gray scale");
			if(m_pAlphaPlan)
				if(!m_pAlphaPlan->IsGrayScale())throw _T("Alpha Plans not gray scale if exist");
			if(!m_pGrayPlan->IsGrayScale())		throw _T("Gray Plans not gray scale");

			break;
		case AGMAGICIP_MULTIPLANS_PLANSMODE:
			if(!PlansIsValid())
				return agfalse;
			if(!Combine(m_pFirstPlan,m_pSecondPlan,m_pThirdPlan,m_pAlphaPlan,0))
				return agfalse;

			if(GetBpp()!=24)
				throw _T("The object of class CAGimageMultiPlans not have 24 bits");
			break;
	}
	m_bConsistent=agtrue;
	return agtrue;
}
/*
void CAGimageMultiPlans::SetNotConsistent()
Chuc nang:
	Bao hieu du lieu noi tai va cac tang mau khong nhat quan
Tham so vao:
Tham so ra:
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageMultiPlans::SetNotConsistent()
{
	m_bConsistent=agfalse;
}

//////////////////////////Plans////////////////////////////////////////////

/*
void CAGimageMultiPlans::PlansDestroy()
Chuc nang:
	Huy tat ca cac tang mau
Tham so vao:
	bFlag: neu la agtrue thi cap nhat tu du lieu noi tai vao tang mau va 
				  agfalse la cap nhat tu tang mau vao du lieu noi tai
Tham so ra:
Tra ve:
	agtrue: neu cap nhat thanh cong
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans();
	pAGimageMultiPlans->Load(_T("myPicture.gif"));
	pAGimageMultiPlans->Init();

	pAGimageMultiPlans->PlansDestroy();//huy cac tang mau

	//tai tao cac tang mau
	if(pAGimageMultiPlans->GetMode()!=AGMAGICIP_MULTIPLANS_INSIDEMODE)
		pAGimageMultiPlans->SetMode(AGMAGICIP_MULTIPLANS_INSIDEMODE);//chuyen sang mode du lieu noi tai
						   //de co the cap nhat (tuc tai tao duoc cac tang mau) tu du lieu noi tai
	if(pAGimageMultiPlans->IsConsistent())
		pAGimageMultiPlans->SetNotConsistent();//phai goi ham nay de bao dam ham 
						   //CAGimageMultiPlans::UpdateConsistent duoc goi ngay sau se luon thuc hien
						   //vi ham CAGimageMultiPlans::UpdateConsistent chi thuc hien khi no phat hien
						   //du lieu noi tai va cac tang mau chua nhat quan
	pAGimageMultiPlans->UpdateConsistent();//tai tao lai cac tang mau

	//do here somthing
	//............
	delete pAGimageMultiPlans;
Ghi chu:
*/
void CAGimageMultiPlans::PlansDestroy()
{
	if(m_pFirstPlan)
	{
		delete m_pFirstPlan;
		m_pFirstPlan=NULL;
	}
	if(m_pSecondPlan)
	{
		delete m_pSecondPlan;
		m_pSecondPlan=NULL;
	}
	if(m_pThirdPlan)
	{
		delete m_pThirdPlan;
		m_pThirdPlan=NULL;
	}
	if(m_pGrayPlan)
	{
		delete m_pGrayPlan;
		m_pGrayPlan=NULL;
	}
	if(m_pAlphaPlan)
	{
		delete m_pAlphaPlan;
		m_pAlphaPlan=NULL;
	}
	SetNotConsistent();
}
/*
void CAGimageMultiPlans::PlansGetPixelMaxI(aguint8& maxa, aguint8& maxb, aguint8& maxc, aguint8& maxgray, aguint8& maxalpha)
Chuc nang:
	Lay gia tri lon nhat co the co cua 1 pixel tai cac tang mau
Tham so vao:
Tham so ra:
	maxa: gia tri lon nhat co the co cua pixel tai tang mau thu nhat
	maxb: gia tri lon nhat co the co cua pixel tai tang mau thu hai
	maxc: gia tri lon nhat co the co cua pixel tai tang mau thu ba
	maxgray: gia tri lon nhat co the co cua pixel tai tang mau gray
	maxalpha: gia tri lon nhat co the co cua pixel tai tang mau alpha
Tra ve:
Cach dung:
Ghi chu:
*/
void CAGimageMultiPlans::PlansGetPixelMaxI(aguint8& maxa, aguint8& maxb, aguint8& maxc, aguint8& maxalpha, aguint8& maxgray)
{
	maxa=m_pFirstPlan->GetPixelMaxI();
	maxb=m_pSecondPlan->GetPixelMaxI();
	maxc=m_pThirdPlan->GetPixelMaxI();
#if CXIMAGE_SUPPORT_ALPHA
	if(m_pAlphaPlan!=NULL)	maxalpha=m_pAlphaPlan->GetPixelMaxI();
#endif
	maxgray=m_pGrayPlan->GetPixelMaxI();
}
/*
void CAGimageMultiPlans::PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& gray, aguint8& alpha)
void CAGimageMultiPlans::PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray)
void CAGimageMultiPlans::PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& gray, aguint8& alpha)
void CAGimageMultiPlans::PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray)
Chuc nang:
	Lay gia tri cua 1 pixel tai cac tang mau
Tham so vao:
	x,y : toa do cua pixel
Tham so ra:
	a: gia tri cua pixel tai tang mau thu nhat
	b: gia tri cua pixel tai tang mau thu hai
	c: gia tri cua pixel tai tang mau thu ba
	gray: gia tri cua pixel tai tang mau gray

	abc_alpha: gia tri cua pixel tai cac tang mau: 1, 2, 3 va alpha, 
		tham so nay co kieu la AGCLRQUAD, voi cac thanh phan nhu sau:
		rgbRed: gia tri tang mau 1
		rgbGreen: gia tri tang mau 2
		rgbBlue: gia tri tang mau 3
		rgbReserved: gia tri tang mau alpha

	alpha: gia tri cua pixel tai tang mau alpha
Tra ve:
Cach dung:

	VD1:
	//..
	agint_xcoord 	x=20;
	agint_bu_ycoord y=10;
	aguint8	a,b,c,alpha,gray;
	PlansGetPixelI(x,y,a,b,c,alpha,gray);
	//PlansGetPixelIFast(x,y,a,b,c,alpha,gray);

	AGCLRQUAD abc;
	abc.rgbRed=a;
	abc.rgbGreen=b;
	abc.rgbBlue=c;
	abc.rgbReserved=gray;//boi vi trong he mau CMYK: ta phai chuyen truong rgbReserved trong 
						 //AGCLRQUAD thanh thanh phan K (tuc gray)
	abc=COLORSPACEtoCOLORSPACE(pAGimageMultiPlans->GetColorSpace,AGMAGICIP_COLORSPACE_CMYK,abc);
	pAGimageMultiPlans->PlansSetPixelI(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,&alpha,&abc.rgbReserved);//thanh phan rgbReserved la tang gray
	//pAGimageMultiPlans->PlansSetPixelIFast(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,&alpha,&abc.rgbReserved);//thanh phan rgbReserved la tang gray

	VD2:
	//....
	agint_xcoord 	x=20;
	agint_bu_ycoord y=10;
	aguint8	gray;
	AGCLRQUAD abc;
	pAGimageMultiPlans->PlansGetPixelI(x,y,abc,gray);//luc nay rgbReserved trong AGCLRQUAD la tang alpha
	//pAGimageMultiPlans->PlansGetPixelIFast(x,y,abc,gray);//luc nay rgbReserved trong AGCLRQUAD la tang alpha

	abc.rgbReserved=gray;//boi vi trong he mau CMYK: ta phai chuyen truong rgbReserved trong 
						 //AGCLRQUAD thanh thanh phan K (tuc gray)
	abc=COLORSPACEtoCOLORSPACE(pAGimageMultiPlans->GetColorSpace,AGMAGICIP_COLORSPACE_CMYK,abc);
	pAGimageMultiPlans->PlansSetPixelI(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,NULL,&gray);
	//pAGimageMultiPlans->PlansSetPixelIFast(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,NULL,&gray);
Ghi chu:
*/
void CAGimageMultiPlans::PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& alpha, aguint8& gray)
{
	a=b=c=gray=alpha=0;
	if(!PlansIsValid())
		return;
	a=m_pFirstPlan->GetPixelI(x,y);
	b=m_pSecondPlan->GetPixelI(x,y);
	c=m_pThirdPlan->GetPixelI(x,y);
#if CXIMAGE_SUPPORT_ALPHA
	if(m_pAlphaPlan!=NULL)	alpha=m_pAlphaPlan->GetPixelI(x,y);
#endif

	gray=m_pGrayPlan->GetPixelI(x,y);
}
void CAGimageMultiPlans::PlansGetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray)
{
	abc_alpha.rgbRed=abc_alpha.rgbGreen=abc_alpha.rgbBlue=abc_alpha.rgbReserved=gray=0;
	if(!PlansIsValid())
		return;
	abc_alpha.rgbRed=m_pFirstPlan->GetPixelI(x,y);
	abc_alpha.rgbGreen=m_pSecondPlan->GetPixelI(x,y);
	abc_alpha.rgbBlue=m_pThirdPlan->GetPixelI(x,y);
#if CXIMAGE_SUPPORT_ALPHA
	if(m_pAlphaPlan!=NULL)	abc_alpha.rgbReserved=m_pAlphaPlan->GetPixelI(x,y);
#endif

	gray=m_pGrayPlan->GetPixelI(x,y);
}
void CAGimageMultiPlans::PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8& a, aguint8& b, aguint8& c, aguint8& alpha, aguint8& gray)
{
	a=m_pFirstPlan->GetPixelIFast(x,y);
	b=m_pSecondPlan->GetPixelIFast(x,y);
	c=m_pThirdPlan->GetPixelIFast(x,y);
#if CXIMAGE_SUPPORT_ALPHA
	if(m_pAlphaPlan!=NULL)	alpha=m_pAlphaPlan->GetPixelIFast(x,y);
#endif

	gray=m_pGrayPlan->GetPixelIFast(x,y);
}
void CAGimageMultiPlans::PlansGetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD& abc_alpha, aguint8& gray)
{
	abc_alpha.rgbRed=m_pFirstPlan->GetPixelIFast(x,y);
	abc_alpha.rgbGreen=m_pSecondPlan->GetPixelIFast(x,y);
	abc_alpha.rgbBlue=m_pThirdPlan->GetPixelIFast(x,y);
#if CXIMAGE_SUPPORT_ALPHA
	if(m_pAlphaPlan!=NULL)	abc_alpha.rgbReserved=m_pAlphaPlan->GetPixelIFast(x,y);
#endif

	gray=m_pGrayPlan->GetPixelIFast(x,y);
}


/*
agbool CAGimageMultiPlans::PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray)
agbool CAGimageMultiPlans::PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray)
agbool CAGimageMultiPlans::PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray)
agbool CAGimageMultiPlans::PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray)
Chuc nang:
	Dat gia tri cua 1 pixel tai cac tang mau
Tham so vao:
	x,y : toa do cua pixel

	a: con tro gia tri cua pixel can dat tai tang mau thu nhat, neu la NULL se khong dat gia tri nay
	b: con tro gia tri cua pixel can dat tai tang mau thu hai, neu la NULL se khong dat gia tri nay
	c: con tro gia tri cua pixel can dat tai tang mau thu ba, neu la NULL se khong dat gia tri nay
	alpha: con tro gia tri cua pixel can dat tai tang mau alpha, neu la NULL se khong dat gia tri nay

	abc_alpha: con tro gia tri cua pixel can dat tai cac tang mau: 1, 2, 3 va alpha, 
		tham so nay co kieu la AGCLRQUAD, voi cac thanh phan nhu sau:
		rgbRed: gia tri tang mau 1
		rgbGreen: gia tri tang mau 2
		rgbBlue: gia tri tang mau 3
		rgbReserved: gia tri tang mau alpha

	gray: con tro gia tri cua pixel can dat tai tang mau gray, neu la NULL se khong dat gia tri nay
Tham so ra:
Tra ve:
	agtrue: neu toa do pixel can dat la hop le, nguoc lai la agfalse. Ham PlansSetPixelIFast luon 
		tra ve agtrue.
Cach dung:
	VD1:
	//..
	agint_xcoord 	x=20;
	agint_bu_ycoord y=10;
	aguint8	a,b,c,alpha,gray;
	PlansGetPixelI(x,y,a,b,c,alpha,gray);
	//PlansGetPixelIFast(x,y,a,b,c,alpha,gray);

	AGCLRQUAD abc;
	abc.rgbRed=a;
	abc.rgbGreen=b;
	abc.rgbBlue=c;
	abc.rgbReserved=gray;//boi vi trong he mau CMYK: ta phai chuyen truong rgbReserved trong 
						 //AGCLRQUAD thanh thanh phan K (tuc gray)
	abc=COLORSPACEtoCOLORSPACE(pAGimageMultiPlans->GetColorSpace,AGMAGICIP_COLORSPACE_CMYK,abc);
	pAGimageMultiPlans->PlansSetPixelI(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,&alpha,&abc.rgbReserved);//thanh phan rgbReserved la tang gray
	//pAGimageMultiPlans->PlansSetPixelIFast(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,&alpha,&abc.rgbReserved);//thanh phan rgbReserved la tang gray

	VD2:
	//....
	agint_xcoord 	x=20;
	agint_bu_ycoord y=10;
	aguint8	gray;
	AGCLRQUAD abc;
	pAGimageMultiPlans->PlansGetPixelI(x,y,abc,gray);//luc nay rgbReserved trong AGCLRQUAD la tang alpha
	//pAGimageMultiPlans->PlansGetPixelIFast(x,y,abc,gray);//luc nay rgbReserved trong AGCLRQUAD la tang alpha

	abc.rgbReserved=gray;//boi vi trong he mau CMYK: ta phai chuyen truong rgbReserved trong 
						 //AGCLRQUAD thanh thanh phan K (tuc gray)
	abc=COLORSPACEtoCOLORSPACE(pAGimageMultiPlans->GetColorSpace,AGMAGICIP_COLORSPACE_CMYK,abc);
	pAGimageMultiPlans->PlansSetPixelI(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,NULL,&gray);
	//pAGimageMultiPlans->PlansSetPixelIFast(x,y,&abc.rgbRed,&abc.rgbGreen,&abc.rgbBlue,NULL,&gray);
Ghi chu:
*/
agbool CAGimageMultiPlans::PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray)
{
	if(!PlansIsValid())
		return agfalse;

	if(a)		m_pFirstPlan->SetPixelI(x,y,*a);
	if(b)		m_pSecondPlan->SetPixelI(x,y,*b);
	if(c)		m_pThirdPlan->SetPixelI(x,y,*c);
#if CXIMAGE_SUPPORT_ALPHA
	if(alpha)
	{
		if(m_pAlphaPlan)	m_pAlphaPlan->SetPixelI(x,y,*alpha);
	}
#endif
	if(gray)	m_pGrayPlan->SetPixelI(x,y,*gray);

	return agtrue;
}
agbool CAGimageMultiPlans::PlansSetPixelI(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray)
{
	if(!PlansIsValid())	return agfalse;

	if(abc_alpha)
	{
		AGCLRQUAD	tmp_abc_alpha=*abc_alpha;
		m_pFirstPlan->SetPixelI(x,y,tmp_abc_alpha.rgbRed);
		m_pSecondPlan->SetPixelI(x,y,tmp_abc_alpha.rgbGreen);
		m_pThirdPlan->SetPixelI(x,y,tmp_abc_alpha.rgbBlue);
		#if CXIMAGE_SUPPORT_ALPHA
			if(m_pAlphaPlan)	m_pAlphaPlan->SetPixelI(x,y,tmp_abc_alpha.rgbReserved);
		#endif
	}
	if(gray)	m_pGrayPlan->SetPixelI(x,y,*gray);

	return agtrue;
}
agbool CAGimageMultiPlans::PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, aguint8* a, aguint8* b, aguint8* c, aguint8* alpha, aguint8* gray)
{
	if(a)		m_pFirstPlan->SetPixelIFast(x,y,*a);
	if(b)		m_pSecondPlan->SetPixelIFast(x,y,*b);
	if(c)		m_pThirdPlan->SetPixelIFast(x,y,*c);
#if CXIMAGE_SUPPORT_ALPHA
	if(alpha)
	{
		if(m_pAlphaPlan)	m_pAlphaPlan->SetPixelIFast(x,y,*alpha);
	}
#endif
	if(gray)	m_pGrayPlan->SetPixelIFast(x,y,*gray);

	return agtrue;
}
agbool CAGimageMultiPlans::PlansSetPixelIFast(agint_xcoord x, agint_bu_ycoord y, AGCLRQUAD* abc_alpha, aguint8* gray)
{
	if(abc_alpha)
	{
		AGCLRQUAD	tmp_abc_alpha=*abc_alpha;
		m_pFirstPlan->SetPixelIFast(x,y,tmp_abc_alpha.rgbRed);
		m_pSecondPlan->SetPixelIFast(x,y,tmp_abc_alpha.rgbGreen);
		m_pThirdPlan->SetPixelIFast(x,y,tmp_abc_alpha.rgbBlue);
		#if CXIMAGE_SUPPORT_ALPHA
			if(m_pAlphaPlan)	m_pAlphaPlan->SetPixelIFast(x,y,tmp_abc_alpha.rgbReserved);
		#endif
	}
	if(gray)	m_pGrayPlan->SetPixelIFast(x,y,*gray);

	return agtrue;
}

/*
agbool CAGimageMultiPlans::PlansIsValid()
Chuc nang:
	Kiem tra xem cac tang mau(1,2,3,gray) co hop le(khac rong) khong?
Tham so vao:
Tham so ra:
Tra ve:
	agtrue: cac tang mau(1,2,3,gray) deu hop le(khac rong)
	agfalse: nguoc lai
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans();
	pAGimageMultiPlans->Load(_T("myPicture.gif"));
	pAGimageMultiPlans->Init();

	if(pAGimageMultiPlans->PlansIsValid())
	{
		CAGimageGrayScale* pFirstPlan=pAGimageMultiPlans->GetFirstPlan();
		//do here some thing;
		//.....
	}
	else
		throw _T("Image is invalid");
	delete pAGimageMultiPlans;
Ghi chu:
*/
agbool CAGimageMultiPlans::PlansIsValid()
{
	return (m_pFirstPlan!=NULL && m_pSecondPlan!=NULL && m_pThirdPlan!=NULL && m_pGrayPlan!=NULL);
}

//////////////////////////////////////Plan/////////////////////////////////////////////////////////

/*
CAGimageGrayScale*	CAGimageMultiPlans::GetFirstPlan()
CAGimageGrayScale*	CAGimageMultiPlans::GetSecondPlan()
CAGimageGrayScale*	CAGimageMultiPlans::GetThirdPlan()
CAGimageGrayScale*	CAGimageMultiPlans::GetAlphaPlan()
CAGimageGrayScale*	CAGimageMultiPlans::GetGrayPlan()
Chuc nang:
	Lay cac tang mau
Tham so vao:
Tham so ra:
Tra ve:
	Tang mau yeu cau
Cach dung:
	CAGimageGrayScale* pFirstPlan=pAGimageMultiPlans->GetFirstPlan();
	CAGimageGrayScale* pSecondPlan=pAGimageMultiPlans->GetSecondPlan();
	CAGimageGrayScale* pThirdPlan=pAGimageMultiPlans->GetThirdPlan();
#if CXIMAGE_SUPPORT_ALPHA
	CAGimageGrayScale* pAlphaPlan=pAGimageMultiPlans->GetAlphaPlan();
#endif
	CAGimageGrayScale* pGrayPlan=pAGimageMultiPlans->GetGrayPlan();
Ghi chu:
*/
CAGimageGrayScale*	CAGimageMultiPlans::GetFirstPlan()
{
	return m_pFirstPlan;
}
CAGimageGrayScale*	CAGimageMultiPlans::GetSecondPlan()
{
	return m_pSecondPlan;
}
CAGimageGrayScale*	CAGimageMultiPlans::GetThirdPlan()
{
	return m_pThirdPlan;
}
#if CXIMAGE_SUPPORT_ALPHA
CAGimageGrayScale*	CAGimageMultiPlans::GetAlphaPlan()
{
	return m_pAlphaPlan;
}
#endif
CAGimageGrayScale*	CAGimageMultiPlans::GetGrayPlan()
{
	return m_pGrayPlan;
}

///////////////////////////////////////////Heuristic Segmentation///////////////////////////////////
/*
agint32 CAGimageMultiPlans::HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, aguint32* pOrderRelate)//Ham nay phan doan anh theo Heuristic
Chuc nang:
	Ham nay phan doan anh theo Heuristic. Thuat toan phan vung anh theo Heuristic duoc mo ta trong 
		ham CAGimage::HeuristicSeg(xem lai phia tren)
	Thuc chat ham nay se goi lan luoc ham CAGimage::HeuristicSeg tren moi tang mau(moi tang mau 
		duoc xem nhu la 1 anh CAGimageGrayScale ke thua CAGimage). Cac tang mau se cho ra cac ket 
		qua phan doan(pOutSegs cua tung tang mau), cac ket qua phan doan nay se duoc ket hop voi 
		nhau theo mot quan he(and-and, or-or hay and-or,..) va mot trat tu(first-second-third hay second-first-last,..) 
		de cho ra ket qua phan doan cuoi cung. Quan he(and-and, or-or hay and-or,..) va trat tu(first-second-third hay 
		second-first-last,..) ket hop yeu cau duoc truyen vao theo tham so pOrderRelate
Tham so vao:
	pParam : thong so khoi tao cho viec phan doan anh Heuristic, thong so nay co kieu HEURISTIC_SEG_PARAM 
			bao gom cac truong:
			SIZE	block_size;//kich thuoc cua mot khoi
			agint32	hCrude;//chinh la thong so h trong thuat toan tinh do tho: 
						   //AreaGetCrudeLevel(agint32 h), SelectionGetCrudeLevel(agint32 h). hCrude mac
						   //dinh = 4
			agreal64	thresholdEdge;//nguong de tinh mat do bie, day la thong so trong ham tinh mat do bien: 
					//SelectionGetEdgeDensity(agreal64 threshold), AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc)
			agreal64	hEX;//nguong cua mat do bien cua khoi X: E(X) < 25%=hEX (mac dinh)
			agreal64	hSJ;//nguong cua tong mot do bien va do tho cua khoi J: S(J)=E(J)+C(J)>1.0=hSJ (mac dinh)
			agreal64	dKR;//thong so delta cua khoi K: Delta(K,Rj)=E(K) + C(K) + H(K,Rj) > 1.0 = hKR (mac dinh)
			agreal64	hEKCK;//thong so do tho va mat do bien cua khoi K: E(K) + C(K) > 0.7=hEKCK (mac dinh)
		Cac gia tri mac dinh cua cac truong trong pParam co the duoc khoi tao bang macro INIT_HEURISTIC_SEG_PARAM 
			hay	macro INIT_HEURISTIC_SEG_PARAMPTR

	pOrderRelate : day chinh la tham so pReserved trong CAGimage.Trong CAGimage khong su dung tham 
		so nay nhung tham so nay duoc su dung o day.Tham so nay chi co nghia trong lop CAGimageMultiPlans. 
		Trong lop CAGimageMultiPlans, pOrderRelate mang ngu nghia la quan he-relate(and, or, xor) va 
		trat tu phoi hop-order giua cac tang mau, khi do *pOrderRelate la so nguyen voi 2 byte cao 
		la trat tu ket hop giua cac tang mau(VD: first-second-third hay second-first-third,..) va 
		2 byte thap chi moi quan he giua cac tang mau(and-and hay or-or hay and-or,..).	
		That su trong lop CAGimageMultiPlans, ham phan doan CAGimageMultiPlans::HeuristicSeg se phan 
		doan rieng re tung tang mau, cac ket qua phan doan(pOutSegs) cua tung tang mau se duoc ket 
		hop theo 1 quan he va trat tu nao do->trat tu va quan he nay duoc the hien trong tham so 
		pOrderRelate da noi o tren. Neu pOrderRelate=NULL thi gia tri trat tu va quan he giua cac 
		tang mau se la AGMAGICIP_AND_HEURISTIC_ORDER_RELATE co nghia la quan he "and" lan luot 
		tang mau 1, tang mau 2, tang mau 3(tang mau 1 "and" tang mau 2 "and" tang mau 3")

		2 byte cao cua *pOrderRelate la trat tu phan doan giua cac tang mau bao gom cac gia tri sau:
			AGMAGICIP_FIRST_SECOND_THIRD3 = 1: tang mau 1, tang mau 2, tang mau 3 
			AGMAGICIP_FIRST_THIRD_SECOND3 = 2: tang mau 1, tang mau 3, tang mau 2
			AGMAGICIP_SECOND_FIRST_THIRD3 = 3: tang mau 2, tang mau 1, tang mau 3	
			AGMAGICIP_SECOND_THIRD_FIRST3 = 4: tang mau 2, tang mau 3, tang mau 1
			AGMAGICIP_THIRD_FIRST_SECOND3 = 5: tang mau 3, tang mau 1, tang mau 2
			AGMAGICIP_THIRD_SECOND_FIRST3 = 6: tang mau 3, tang mau 2, tang mau 1
		2 byte thap cua *pOrderRelate la quan he(theo trat tu) giua cac tang mau, nen nho quan he nay 
			khong phai theo tang mau 1, 2, 3 ma lai theo trat tu cua 2 byte cao o tren:
			AGMAGICIP_AND_AND3 = 1: FIRST "and" SECOND "and" THIRD
			AGMAGICIP_AND_OR3  = 2: FIRST "and" SECOND "or" THIRD
			AGMAGICIP_AND_XOR3 = 3: FIRST "and" SECOND "xor" THIRD
			AGMAGICIP_OR_AND3  = 4: FIRST "or" SECOND "and" THIRD
			AGMAGICIP_OR_OR3   = 5: FIRST "or" SECOND "or" THIRD
			AGMAGICIP_OR_XOR3  = 6: FIRST "or" SECOND "xor" THIRD
			AGMAGICIP_XOR_AND3 = 7: FIRST "xor" SECOND "and" THIRD
			AGMAGICIP_XOR_OR3  = 8: FIRST "xor" SECOND "or" THIRD
			AGMAGICIP_XOR_XOR3 = 9: FIRST "xor" SECOND "xor" THIRD
			voi FIRST. SECOND, THIRD la ket qua cua viec phan doan 3 tang mau theo trat tu cua 
			2 byte cao
Tham so ra:
	pOutSegs: mang chua nhan cac vung da duoc phan doan, mang nay co kich thuoc bang voi kich thuoc 
		cua anh nhung moi phan tu(pixel) co gia tri la nhan cua vung ma phan tu do thuoc ve, gia tri 
		nhan di tu 1. Nhung phan tu co gia tri 0 thi khong thuoc vung nao, co the xem nhu no la nen 
		trong ngu nghia cua thuat toan phan doan nay. pOutSegs phai duoc khoi tao co 
		kich thuoc=1byte*so_pixel_cua_anh, pOutSegs tuyet doi khong duoc bang NULL khi truyen vao. 
		Sau khi ham duoc goi xong, co the su thao tac tren pOutSegs, nhung sau khi su dung pOutSegs 
		thi phai giai phong no. pOutSegs(ket qua phan doan) nay chinh la ket qua cua su ket hop cac 
		pOutSegs(ket qua phan doan) cua cac tang mau theo mot quan he va trat tu(the hien trong tham 
		so pOrderRelate)
Tra ve:
	So vung anh phan doan duoc
Cach dung:
	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans(_T("myPicture.gif"));
	HEURISTIC_SEG_PARAM param;
	INIT_HEURISTIC_SEG_PARAM(param)
	//co the thay doi cac truong cua param o day
	//param.block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX;
	//param.block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY;
    //param.hCrude=4;
	//param.thresholdEdge=0.5;
	//param.hEX=0.25;
	//param.hSJ=1.0;
	//param.dKR=1.0;
	//param.hEKCK=0.7;
	aguint32	nPixels=pAGimage->GetWidth()*pAGimage->GetHeight();
	aguint8*	pOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	aguint32	OrderRelate=AGMAGICIP_AND_HEURISTIC_ORDER_RELATE;
	//OrderRelate co the khoi tao bang macro MAKE_AGUINT32(lo,hi)
	//OrderRelate=MAKE_AGUINT32(AGMAGICIP_AND_OR3,AGMAGICIP_FIRST_SECOND_THIRD3)//nghia la tang mau 1 "and" tang mau 2 "or" tang mau 3
	memset(pOutSegs,0,nPixels);

	//ham chinh
	aguint32 nSegs=pAGimageMultiPlans->HeuristicSeg(&param,pOutSegs,&OrderRelate);//nSegs la so vung da phan doan duoc
	if(nSegs==0)
		throw _T("Can not sement or error occur");
	//lam gi do voi pOutSegs
	//........

	free(pOutSegs);
	pOutSegs=NULL;
	delete pAGimageMultiPlans;
Ghi chu:
	pOutSegs phai duoc khoi tao co kich thuoc=1byte*so_pixel_cua_anh, pOutSegs tuyet doi khong duoc 
		bang NULL khi truyen vao. Mac khac pOutSeg chi don thuan tinh theo pixel khong nhu anh tuc 
		moi dong quet khong can phai co so byte la boi so cua 4, pOutSeg la mang byte(8 bits)
*/
agint32 CAGimageMultiPlans::HeuristicSeg(HEURISTIC_SEG_PARAM* pParam, aguint8* pOutSegs, HEURISTIC_SEG_BLOCK_MATRIX* pOutBlocksMatrix, aguint32* pOrderRelate)//Ham nay phan doan anh theo Heuristic
{
	throw _T("Implement not yet");
	if(!PlansIsValid())	throw _T("Plans invalid");

	agint32	ImageWidth=GetWidth(), ImageHeight=GetHeight();	
	aguint8*	pFirstSegs=NULL, *pSecondSegs=NULL, *pThirdSegs=NULL;
	pFirstSegs =(aguint8*)malloc(ImageWidth*ImageHeight);
	pSecondSegs=(aguint8*)malloc(ImageWidth*ImageHeight);
	pThirdSegs =(aguint8*)malloc(ImageWidth*ImageHeight);
	memset(pFirstSegs,0,ImageWidth*ImageHeight);
	memset(pSecondSegs,0,ImageWidth*ImageHeight);
	memset(pThirdSegs,0,ImageWidth*ImageHeight);
	memset(pOutSegs,0,ImageWidth*ImageHeight);

	aguint32	OrderRelate=AGMAGICIP_OR_HEURISTIC_ORDER_RELATE;
	if(!pOrderRelate)	OrderRelate=*pOrderRelate;
	aguint16	order=AGHI_UINT16_OF(OrderRelate);
	aguint16	relate=AGLO_UINT16_OF(OrderRelate);

	AGCLRQUAD	rgbLabel=Heuristic3Seg(pParam,order,pFirstSegs,pSecondSegs,pThirdSegs);
	if(rgbLabel.rgbRed==0 && rgbLabel.rgbGreen==0 && rgbLabel.rgbBlue==0)	return 0;
	agint32	nLabel  =HeuristicCombine3Seg(relate, pFirstSegs, pSecondSegs, pThirdSegs, pOutSegs);

	if(pFirstSegs)		free(pFirstSegs);
	if(pSecondSegs)		free(pSecondSegs);
	if(pThirdSegs)		free(pThirdSegs);
	return	nLabel;
}
/*
AGCLRQUAD	CAGimageMultiPlans::Heuristic3Seg(HEURISTIC_SEG_PARAM* pParam, aguint16 order, aguint8* pFirstOutSegs, aguint8* pSecondOutSegs, aguint8* pThirdOutSegs)
Chuc nang:
	Ham nay phan doan 3 tang mau rieng re theo Heuristic. Thuat toan phan vung anh theo Heuristic 
		duoc mo ta trong ham CAGimage::HeuristicSeg(xem lai phia tren). Thuc chat ham nay se goi 
		lan luoc ham CAGimage::HeuristicSeg tren 3 tang mau(moi tang mau duoc xem nhu la 1 anh 
		CAGimageGrayScale ke thua CAGimage) theo mot trang tu nao do. Moi tang mau se cho ra moi ket 
		qua phan doan(pFirstOutSegs, pSecondOutSegs, pThirdOutSegs). Nen nho pFirstOutSegs, 
		pSecondOutSegs, pThirdOutSegs khong nhat thiet phai tuong ung voi tang mau 1, tang mau 2, 
		tang mau 3 ma thu tu tuong ung cua no phu thuoc vao tham so order
	Ta nhan thay rang ham nay se duoc goi boi ham CAGimageMultiPlans::HeuristicSeg, ro rang ham 
		CAGimageMultiPlans::HeuristicSeg goi ham nay va ket hop cac ket qua phan doan tu ham nay	theo 
		mot quan he nao do. Ham nay co the duoc goi truc tiep tu ben ngoai de co the customize viec 
		ket hop cac ket qua phan doan

	Goi CAGimageMultiPlans::HeuristicSeg = Goi CAGimageMultiPlans::Heuristic3Seg + Goi CAGimageMultiPlans::HeuristicCombine3Seg
Tham so vao:
	pParam : thong so khoi tao cho viec phan doan anh Heuristic, thong so nay co kieu HEURISTIC_SEG_PARAM 
			bao gom cac truong:
			SIZE	block_size;//kich thuoc cua mot khoi
			agint32	hCrude;//chinh la thong so h trong thuat toan tinh do tho: 
						   //AreaGetCrudeLevel(agint32 h), SelectionGetCrudeLevel(agint32 h). hCrude mac
						   //dinh = 4
			agreal64	thresholdEdge;//nguong de tinh mat do bie, day la thong so trong ham tinh mat do bien: 
					//SelectionGetEdgeDensity(agreal64 threshold), AreaGetEdgeDensity(agreal64 threshold, AGBU_RECT* prc)
			agreal64	hEX;//nguong cua mat do bien cua khoi X: E(X) < 25%=hEX (mac dinh)
			agreal64	hSJ;//nguong cua tong mot do bien va do tho cua khoi J: S(J)=E(J)+C(J)>1.0=hSJ (mac dinh)
			agreal64	dKR;//thong so delta cua khoi K: Delta(K,Rj)=E(K) + C(K) + H(K,Rj) > 1.0 = hKR (mac dinh)
			agreal64	hEKCK;//thong so do tho va mat do bien cua khoi K: E(K) + C(K) > 0.7=hEKCK (mac dinh)
		Cac gia tri mac dinh cua cac truong trong pParam co the duoc khoi tao bang macro INIT_HEURISTIC_SEG_PARAM hay
		macro INIT_HEURISTIC_SEG_PARAMPTR

	order : Tham so nay giong nhu 2 byte cao cua tham so *pOrderRelate trong ham 
		CAGimageMultiPlans::HeuristicSeg la trat tu phan doan giua cac tang mau bao gom cac gia tri sau:
			AGMAGICIP_FIRST_SECOND_THIRD3 = 1: tang mau 1, tang mau 2, tang mau 3 
			AGMAGICIP_FIRST_THIRD_SECOND3 = 2: tang mau 1, tang mau 3, tang mau 2
			AGMAGICIP_SECOND_FIRST_THIRD3 = 3: tang mau 2, tang mau 1, tang mau 3	
			AGMAGICIP_SECOND_THIRD_FIRST3 = 4: tang mau 2, tang mau 3, tang mau 1
			AGMAGICIP_THIRD_FIRST_SECOND3 = 5: tang mau 3, tang mau 1, tang mau 2
			AGMAGICIP_THIRD_SECOND_FIRST3 = 6: tang mau 3, tang mau 2, tang mau 1

Tham so ra:
	pFirstOutSegs, pSecondOutSegs, pThirdOutSegs: cac mang chua nhan cac vung da duoc phan doan lan 
		luoc theo trat tu cac tang mau trong tham so order, cac mang nay co kich thuoc bang voi 
		kich thuoc cua anh nhung moi phan tu(pixel) cua moi mang co gia tri la nhan cua vung(trong moi mang) 
		ma phan tu do thuoc ve, gia tri nhan di tu 1. Nhung phan tu co gia tri 0 thi khong thuoc 
		vung(cua moi mang) nao, co the xem nhu no la nen trong ngu nghia cua thuat toan phan doan nay. 
		pFirstOutSegs, pSecondOutSegs, pThirdOutSegs tat ca phai duoc cap phat khi truyen vao , moi 
		cai giong nhu pOutSegs trong ham CAGimage::HeuristicSeg phai duoc khoi tao co 
		kich thuoc=1byte*so_pixel_cua_anh. Cac mang nay(pFirstOutSegs, pSecondOutSegs,pThirdOutSegs) 
		tuyet doi khong duoc bang NULL khi truyen vao. Sau khi ham duoc goi xong, co the thuc hien 
		cac thao tac tren chung, nhung sau khi su dung chung thi phai giai phong chung.
Tra ve:
	La gia tri kieu cau truc AGCLRQUAD voi ngu nghia cac truong nhu sau
		rgbRed: So vung anh phan doan duoc cua tang mau thu 1 theo trat tu cua tham so order
		rgbGreen: So vung anh phan doan duoc cua tang mau thu 2 theo trat tu cua tham so order
		rgbBlue: So vung anh phan doan duoc cua tang mau thu 3 theo trat tu cua tham so order
Cach dung: Ham nay duoc goi trong ham CAGimageMultiPlans::HeuristicSeg, tuy nhien no cung co the	duoc 
	goi truc tiep tu ben ngoai, de customize viec ket hop giua cac ket qua phan doan

	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans(_T("myPicture.gif"));
	HEURISTIC_SEG_PARAM param;
	INIT_HEURISTIC_SEG_PARAM(param)
	//co the thay doi cac truong cua param o day
	//param.block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX;
	//param.block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY;
    //param.hCrude=4;
	//param.thresholdEdge=0.5;
	//param.hEX=0.25;
	//param.hSJ=1.0;
	//param.dKR=1.0;
	//param.hEKCK=0.7;
	aguint32	nPixels=pAGimage->GetWidth()*pAGimage->GetHeight();
	aguint8*	pFirstOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	aguint8*	pSecondOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	aguint8*	pThirdOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	memset(pFirstOutSegs,0,nPixels);
	memset(pSecondOutSegs,0,nPixels);
	memset(pThirdOutSegs,0,nPixels);

	//n3Segs cau truc AGCLRQUAD chua so vung da phan doan duoc cua moi tang mau
	AGCLRQUAD n3Segs=pAGimageMultiPlans->Heuristic3Seg(&param,order,pFirstOutSegs,
							pSecondOutSegs, pThirdOutSegs);

	if(n3Segs.rgbRed==0||n3Segs.rgbGreen==0||n3Segs.rgbBlue==0)
		throw _T("Can not sement or error occur");
	//lam gi do voi pFirstOutSegs, pSecondOutSegs, pThirdOutSegs
	//....
	//gom 3 ket qua phan doan: pFirstOutSegs, pSecondOutSegs, pThirdOutSegs theo quan he 
	//"and" "and" de co ket qua phan doan cuoi cung la pOutSegs
	aguint8*	pOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	//nSegs la so vung vung sau khi ket hop 3 ket qua phan doan
	aguint8 nSegs=pAGimageMultiPlans->HeuristicCombine3Seg(AGMAGICIP_AND_AND3,pFirstSegs,pSecondSegs,pThirdSegs,pOutSegs);
	
	free(pFirstOutSegs);
	free(pSecondOutSegs);
	free(pThirdOutSegs);
	free(pOutSegs);
	pFirstOutSegs=pSecondOutSegs=pThirdOutSegs=NULL;
	pOutSegs=NULL;
	delete pAGimageMultiPlans;
Ghi chu:
	pFirstOutSegs, pSecondOutSegs, pThirdOutSegs phai duoc khoi tao co kich thuoc=1byte*so_pixel_cua_anh, 
		chung tuyet doi khong duoc bang NULL khi truyen vao. Mac khac chung chi don thuan tinh theo 
		pixel khong nhu anh tuc moi dong quet khong can phai co so byte la boi so cua 4, chung la cac 
		mang byte(8 bits)
*/
AGCLRQUAD CAGimageMultiPlans::Heuristic3Seg(HEURISTIC_SEG_PARAM* pParam, aguint16 order, aguint8* pFirstOutSegs, aguint8* pSecondOutSegs, aguint8* pThirdOutSegs)
{
	AGCLRQUAD	rgbLable={0,0,0,0};
	if(!PlansIsValid())	return rgbLable;

	//Tham sopFirstOutSegs, pSecondOutSegs,pThirdOutSegs nhat thiet phai khac NULL khi 
	//truyen vao
	if(pFirstOutSegs==NULL || pSecondOutSegs==NULL || pThirdOutSegs==NULL)	
		throw _T("Have least one Segmnet that invalid equal NULL - error in function CAGimageMultiPlans::Heuristic3Seg");

	CAGimageGrayScale*	pFirstPlan=NULL, *pSecondPlan=NULL, *pThirdPlan=NULL;
	//Thiet lap lai trat tu theo tham so order
	switch(order)
	{
		case AGMAGICIP_FIRST_SECOND_THIRD3:
			pFirstPlan=m_pFirstPlan; pSecondPlan=m_pSecondPlan;pThirdPlan=m_pThirdPlan;
			break;
		case AGMAGICIP_FIRST_THIRD_SECOND3:
			pFirstPlan=m_pFirstPlan; pSecondPlan=m_pThirdPlan; pThirdPlan=m_pSecondPlan;
			break;
		case AGMAGICIP_SECOND_FIRST_THIRD3:
			pFirstPlan=m_pSecondPlan;pSecondPlan=m_pFirstPlan; pThirdPlan=m_pThirdPlan;
			break;
		case AGMAGICIP_SECOND_THIRD_FIRST3:
			pFirstPlan=m_pSecondPlan;pSecondPlan=m_pThirdPlan; pThirdPlan=m_pFirstPlan;
			break;
		case AGMAGICIP_THIRD_FIRST_SECOND3:
			pFirstPlan=m_pThirdPlan; pSecondPlan=m_pFirstPlan; pThirdPlan=m_pSecondPlan;
			break;
		case AGMAGICIP_THIRD_SECOND_FIRST3:
			pFirstPlan=m_pThirdPlan; pSecondPlan=m_pSecondPlan;pThirdPlan=m_pFirstPlan;
			break;
		default:
			throw _T("The order of Segmentation of Plans not defined");
	}
	//phan doan rieng re tung tang mau
	rgbLable.rgbRed  = (aguint8)pFirstPlan->HeuristicSeg(pParam,pFirstOutSegs,NULL);
	rgbLable.rgbGreen= (aguint8)pSecondPlan->HeuristicSeg(pParam,pSecondOutSegs,NULL);
	rgbLable.rgbBlue = (aguint8)pThirdPlan->HeuristicSeg(pParam,pThirdOutSegs,NULL);
	
	return rgbLable;
}
/*
agint32 CAGimageMultiPlans::HeuristicCombine3Seg(aguint16 relate, aguint8* pFirstSegs, aguint8* pSecondSegs, aguint8* pThirdSegs, aguint8* pOutSegs)
Chuc nang:
	Ket hop cac ket qua cua viec phan doan(pFirstSegs, pSecondSegs, pThirdSegs) theo mot quan he nao 
		do duoc truyen vao theo tham so relate->de co duoc ket qua phan doan cuoi cung(	tham so ra pOutSegs). 
		Cac pFirstSegs, pSecondSegs, pThirdSegs la cac ket qua cua viec phan doan cac tang mau bang 
		ham Heuristic3Seg hay bang ham phan doan rieng re cua tung tang mau CAGimageGrayScale::HeuristicSeg. 
		pFirstSegs, pSecondSegs, pThirdSegs co the la bat ky nhung chung phai cung ngu nghia, cung 
		kich thuoc
	Ta thay: Goi CAGimageMultiPlans::HeuristicSeg = Goi CAGimageMultiPlans::Heuristic3Seg + Goi CAGimageMultiPlans::HeuristicCombine3Seg
Tham so vao:
	relate: giong nhu 2 byte thap cua tham so *pOrderRelate trong ham CAGimageMultiPlans::HeuristicSeg 
		la quan he(theo trat tu) giua cac ket qua phan doan cua cac tang mau
			AGMAGICIP_AND_AND3 = 1: FIRST "and" SECOND "and" THIRD
			AGMAGICIP_AND_OR3  = 2: FIRST "and" SECOND "or" THIRD
			AGMAGICIP_AND_XOR3 = 3: FIRST "and" SECOND "xor" THIRD
			AGMAGICIP_OR_AND3  = 4: FIRST "or" SECOND "and" THIRD
			AGMAGICIP_OR_OR3   = 5: FIRST "or" SECOND "or" THIRD
			AGMAGICIP_OR_XOR3  = 6: FIRST "or" SECOND "xor" THIRD
			AGMAGICIP_XOR_AND3 = 7: FIRST "xor" SECOND "and" THIRD
			AGMAGICIP_XOR_OR3  = 8: FIRST "xor" SECOND "or" THIRD
			AGMAGICIP_XOR_XOR3 = 9: FIRST "xor" SECOND "xor" THIRD
			voi FIRST. SECOND, THIRD lan luot la pFirstSegs, pSecondSegs, pThirdSegs
	pFirstSegs, pSecondSegs, pThirdSegs: cac ket qua phan doan cua cac tang mau, cac ket qua nay can 
		ket hop theo quan he duoc khai bao trong tham so relate o tren. pFirstSegs, pSecondSegs, 
		pThirdSegs nhat thiet phai khac NULL khi truyen vao va phai duoc giai phong khi het su dung chung

  Tham so ra:
	pOutSegs: mang chua ket qua cua viec phan doan cuoi cung bang cach ket hop cac ket qua phan doan 
		o 3 tham so pFirstSegs, pSecondSegs, pThirdSegs theo quan he duoc khai bao trong tham so 
		relate. Mang nay chua nhan cac vung da duoc phan doan, mang nay co kich thuoc bang voi kich	
		thuoc cua anh nhung moi phan tu(pixel) co gia tri la nhan cua vung ma phan tu do thuoc ve, 
		gia tri nhan di tu 1. Nhung phan tu co gia tri 0 thi khong thuoc vung nao,	co the xem nhu 
		no la nen trong ngu nghia cua thuat toan phan doan nay.	pOutSegs phai duoc khoi tao co 
		kich thuoc=1byte*so_pixel_cua_anh, pOutSegs tuyet doi khong duoc bang NULL khi truyen vao. 
		Sau khi ham duoc goi xong, co the su thao tac tren pOutSegs, nhung sau khi su dung pOutSegs 
		thi phai giai phong no.
Tra ve:
	So vung anh co duoc trong mang pOutSegs, sau khi ket hop pFirstSegs, pSecondSegs, pThirdSegs
Cach dung:
	Ham nay duoc goi trong ham CAGimageMultiPlans::HeuristicSeg, tuy nhien no cung co the duoc goi 
	truc tiep tu ben ngoai, de customize viec ket hop giua cac ket qua phan doan

	CAGimageMultiPlans* pAGimageMultiPlans=new CAGimageMultiPlans(_T("myPicture.gif"));
	HEURISTIC_SEG_PARAM param;
	INIT_HEURISTIC_SEG_PARAM(param)
	//co the thay doi cac truong cua param o day
	//param.block_size.cx=DEFAULT_HEURISTIC_SEG_RESOLX;
	//param.block_size.cy=DEFAULT_HEURISTIC_SEG_RESOLY;
    //param.hCrude=4;
	//param.thresholdEdge=0.5;
	//param.hEX=0.25;
	//param.hSJ=1.0;
	//param.dKR=1.0;
	//param.hEKCK=0.7;
	aguint32	nPixels=pAGimage->GetWidth()*pAGimage->GetHeight();
	aguint8*	pFirstOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	aguint8*	pSecondOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	aguint8*	pThirdOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	memset(pFirstOutSegs,0,nPixels);
	memset(pSecondOutSegs,0,nPixels);
	memset(pThirdOutSegs,0,nPixels);

	//n3Segs cau truc AGCLRQUAD chua so vung da phan doan duoc cua moi tang mau
	AGCLRQUAD n3Segs=pAGimageMultiPlans->Heuristic3Seg(&param,order,pFirstOutSegs,
							pSecondOutSegs, pThirdOutSegs);

	if(n3Segs.rgbRed==0||n3Segs.rgbGreen==0||n3Segs.rgbBlue==0)
		throw _T("Can not sement or error occur");
	//lam gi do voi pFirstOutSegs, pSecondOutSegs, pThirdOutSegs
	//....
	//gom 3 ket qua phan doan: pFirstOutSegs, pSecondOutSegs, pThirdOutSegs theo quan he 
	//"and" "and" de co ket qua phan doan cuoi cung la pOutSegs
	aguint8*	pOutSegs=(aguint8*)malloc(nPixels*sizeof(aguint8));//dong nay rat quan trong
	//nSegs la so vung vung sau khi ket hop 3 ket qua phan doan
	aguint8 nSegs=pAGimageMultiPlans->HeuristicCombine3Seg(AGMAGICIP_AND_AND3,pFirstSegs,pSecondSegs,pThirdSegs,pOutSegs);
	
	free(pFirstOutSegs);
	free(pSecondOutSegs);
	free(pThirdOutSegs);
	free(pOutSegs);
	pFirstOutSegs=pSecondOutSegs=pThirdOutSegs=NULL;
	pOutSegs=NULL;
	delete pAGimageMultiPlans;

Ghi chu:
	pFirstSegs, pSecondSegs, pThirdSegs phai khac NULL khi truyen vao
	pOutSegs phai duoc khoi tao co kich thuoc=1byte*so_pixel_cua_anh, pOutSegs tuyet doi khong duoc 
		bang NULL khi truyen vao. Mac khac pOutSeg chi don thuan tinh theo pixel khong nhu anh tuc 
		moi dong quet khong can phai co so byte la boi so cua 4, pOutSeg la mang byte(8 bits)
*/
agint32 CAGimageMultiPlans::HeuristicCombine3Seg(aguint16 relate, aguint8* pFirstSegs, aguint8* pSecondSegs, aguint8* pThirdSegs, aguint8* pOutSegs)
{
	if(pFirstSegs==NULL || pSecondSegs==NULL || pThirdSegs==NULL || pOutSegs==NULL)	
		throw _T("Have least one Segmnet that invalid equal NULL - error in function CAGimageMultiPlans::HeuristicCombine3Seg");

	agint32	ImageWidth=GetWidth(), ImageHeight=GetHeight();//kich thuoc cua anh
	memset(pOutSegs,-1,ImageWidth*ImageHeight);//khoi gan cac pt cua pOutSegs =-1 am chi chung chua duoc xet duyet
	agint_bu_ycoord i;
	agint_xcoord 	j;
	for(i=0; i<ImageHeight; i++)//duyet tung pixel
	{
		for(j=0; j<ImageWidth; j++)
		{
			//o day co mot quy uoc la: khi ket hop cac ket qua phan doan rieng re thi so nhan(label)
			//cua tung ket qua phan doan khong con y nghia ma thay vao do moi pt cua moi mang ket 
			//qua phan doan chi duoc xem thuoc nen(==0) hay thuoc vung(!=0), va sau do cac gia tri(==0 hay !0) 
			//nay se duoc ket hop voi nhau theo cac quan he "and", "or", hay "xor" de cho ra ket qua 
			//phan doan cuoi cung(pOutSegs). Tuy nhien co mot diem can luu y la cac phan tu cua pOutSegs 
			//lai chi chua  2 gia tri: la -1 neu la nen va 0 neu la vung(object,region), vi the cac 
			//phan tu cua pOutSegs se duoc gan nhan(label) tro lai de phan ly cac vung(object) trong 
			//pOutSegs

			aguint8	firstExist=0, secondExist=0, thirdExist=0;
			if(pFirstSegs)	firstExist=(pFirstSegs[i*ImageWidth+j]!=0)?1:0;
			if(pSecondSegs)	secondExist=(pSecondSegs[i*ImageWidth+j]!=0)?1:0;
			if(pThirdSegs)	thirdExist=(pThirdSegs[i*ImageWidth+j]!=0)?1:0;
			
			aguint8	exist;
			switch(relate)
			{
				case AGMAGICIP_AND_AND3:
					exist=(firstExist & secondExist) & thirdExist;
					break;
				case AGMAGICIP_AND_OR3:
					exist=(firstExist & secondExist) | thirdExist;
					break;
				case AGMAGICIP_AND_XOR3:
					exist=(firstExist & secondExist) ^ thirdExist;
					break;
				case AGMAGICIP_OR_AND3:
					exist=(firstExist | secondExist) & thirdExist;
					break;
				case AGMAGICIP_OR_OR3:
					exist=(firstExist | secondExist) | thirdExist;
					break;
				case AGMAGICIP_OR_XOR3:
					exist=(firstExist | secondExist) ^ thirdExist;
					break;
				case AGMAGICIP_XOR_AND3:
					exist=(firstExist ^ secondExist) & thirdExist;
					break;
				case AGMAGICIP_XOR_OR3:
					exist=(firstExist ^ secondExist) | thirdExist;
					break;
				case AGMAGICIP_XOR_XOR3:
					exist=(firstExist ^ secondExist) ^ thirdExist;
					break;
				default:
					throw _T("The order of Segmentation of Plans not defined");
			}
			if(exist)
				pOutSegs[i*ImageWidth+j]=0;
		}
	}


	//Bay gio cac phan tu cua pOutSegs chi chua gia tri:
	//    ==-1: la nen
	//    ==0: la object, vung
	//Do do ta phai gan nhan(label) tro lai cac phan tu cua pOutSegs de phan ly cac object cac vung

	agint32	label=0;
	agint_bu_ycoord	startI=0;
	agint_xcoord	startJ=0;
	while(agtrue)	
	{
		agbool bFoundZero=agfalse;
		for(i=startI;i<ImageHeight;i++)//duyet tung phan tu
		{
			for(j=startJ;j<ImageWidth;j++)
			{
				if(pOutSegs[i*ImageWidth+j]==0)//neu phan tu do la vung(region, object)
				{
					bFoundZero=agtrue;
					break;
				}
			}
			if(bFoundZero)	break;//neu tim thay phan tu la vung(region, object)
		}
		if(!bFoundZero)	break;
		label ++;
		pOutSegs[i*ImageWidth+j]=(aguint8)label;//gan nhan moi cho phan tu la vung(region, object)

		AGBU_POINT curPixel;
		curPixel.x=j;
		curPixel.y=i;
		HeuristicMakeLabel(label,curPixel,pOutSegs);//gan nhan lan toa cho cac pixel lan can voi
													//pixel o tren va dong thoi la vung
													//(region, object) tuc ==0 

		//xac dinh lai diem khoi dau de duyet tiep
		if(startJ<ImageWidth-1)	startJ++;
		else			
		{
			startI++;
			if(startI==ImageHeight)	break;
			else					startJ=0;
		}
	}

	agint32	n=ImageWidth*ImageHeight;
	for(i=0; i<n; i++)
		if(pOutSegs[i]==-1)	pOutSegs[i]=0;//nhung phan tu ==-1(la nen) se duoc gan tro la 0
	//Nhu vay cuoi cung pOutSegs se tro lai co cac phan tu co gia tri ==0 la nen va cac phan tu co 
	//gia tri >0 se la vung(object, region)

	return label;
}
/*
void CAGimageMultiPlans::HeuristicMakeLabel(agint32 label, AGBU_POINT curPixel, aguint8* pOutSegs)
Chuc nang:
	Ham nay duoc goi tu ham CAGimageMultiPlans::HeuristicCombine3Seg, khong the duoc goi truc tiep 
		tu ben ngoai
	Nhu ta da thay pOutSegs trong CAGimageMultiPlans::HeuristicCombine3Seg ban dau khi chua goi ham 
		nay chi chua gia tri:
	    ==-1: la nen
	    ==0: la object, vung
		Do do ta phai gan nhan(label) tro lai cac phan tu cua pOutSegs de phan ly cac object (cac vung). 
		Vi the ham nay co muc dich dung de danh nhan lan toa de quy de phan ly cac vung(object), ham 
			se bo qua cac phan tu nen(co gia tri ==-1) va danh nhan cac phan tu la 
			vung(region, object co gia tri==0). Nhu vay cuoi cung pOutSegs se tro lai co cac phan tu 
			co gia tri ==0 la nen va cac phan tu co gia tri >0 se la vung(object, region()

Tham so vao:
	label: nhan can danh cho cac phan tu thuoc vung(region, object)
	curPixel: pixel hien hanh can tim lan can voi no de danh nhan
	pOutSegs: mang ket qua phan doan can phan ly cac vung(region, object). Gia tri cac phan tu trong 
		mang nay da duoc noi o tren phan chuc nang. Tham so nay vua la tham so vao vua la tham so ra
Tham so ra:
	pOutSegs: Day vua la tham so vao vua la tham so ra nhu da noi o phia tren
Tra ve:
	Khong co gia tri tra ve
Cach dung:
	Ham nay khong the goi truc tiep tu ben ngoai, no chi duoc goi tu ham 
		CAGimageMultiPlans::HeuristicCombine3Seg nhu sau:
		agint32	label=0;
		agint_bu_ycoord	startI=0;
		agint_xcoord	startJ=0;
		while(agtrue)	
		{
			agbool bFoundZero=agfalse;
			for(i=startI;i<ImageHeight;i++)//duyet tung phan tu
			{
				for(j=startJ;j<ImageWidth;j++)
				{
					if(pOutSegs[i*ImageWidth+j]==0)//neu phan tu do la vung(region, object)
					{
						bFoundZero=agtrue;
						break;
					}
				}
				if(bFoundZero)	break;//neu tim thay phan tu la vung(region, object)
			}
			if(!bFoundZero)	break;
			label ++;
			pOutSegs[i*ImageWidth+j]=(aguint8)label;//gan nhan moi cho phan tu la vung(region, object)

			AGBU_POINT curPixel;
			curPixel.x=j;
			curPixel.y=i;
			HeuristicMakeLabel(label,curPixel,pOutSegs);//gan nhan lan toa cho cac pixel lan can voi
														//pixel o tren va dong thoi la vung
														//(region, object) tuc ==0 

			//xac dinh lai diem khoi dau de duyet tiep
			if(startJ<ImageWidth-1)	startJ++;
			else			
			{
				startI++;
				if(startI==ImageHeight)	break;
				else					startJ=0;
			}
		}

Ghi chu:
	pOutSegs buoc phai khac NULL khi truyen vao
*/
void CAGimageMultiPlans::HeuristicMakeLabel(agint32 label, AGBU_POINT curPixel, aguint8* pOutSegs)
{
	AGBU_POINT	pNeighbor8Pixels[8];
	aguint8	nNeighbor8Pixels;
	nNeighbor8Pixels=GetNeighbor8Pixels(curPixel,pNeighbor8Pixels);
	if(nNeighbor8Pixels==0)	return;

	agint32	ImageWidth=GetWidth();//do rong cua anh
	for(aguint8 i=0; i<nNeighbor8Pixels; i++)
	{
		agint32 pos=pNeighbor8Pixels[i].y*ImageWidth +  pNeighbor8Pixels[i].x;
		if(pOutSegs[pos]==0)
		{
			pOutSegs[pos]=(aguint8)label;
			HeuristicMakeLabel(label,pNeighbor8Pixels[i],pOutSegs);//chay de quy cho chinh diem lan can nay
		}
	}
}

/********************************CAGimageObjPtrVec, CAGimageObjPtrbuMatrix****************************************/
CAGimageObjPtrVec::CAGimageObjPtrVec() : CAGobjPtrArray<CAGimage>()
{
}
CAGimageObjPtrVec::~CAGimageObjPtrVec()
{
}
agint32 CAGimageObjPtrVec::TotalWidth(agint32 wHinge)
{
	agint32 total_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimage*		pImage=GetAt(i);
		if(pImage)
		{
			agint32		w=(agint32)pImage->GetWidth();
			total_width +=w;
			if(i!=n-1)	total_width +=(w>0?wHinge:0);
		}
	}
	return total_width;
}
agint32 CAGimageObjPtrVec::TotalHeight()
{
	agint32 max_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimage*	pImage=GetAt(i);
		if(pImage)	max_height =AGMAX(max_height,(agint32)pImage->GetHeight());
	}
	return max_height;
}

void CAGimageObjPtrVec::Import(CAGptrArray* pInAGimageA, agbool bIsCopy)
{
	RemoveAll();
	agint32		n=pInAGimageA->GetSize();
	if(n==0)	return;
	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
	{
		CAGimage* pAGimage=(CAGimage*)pInAGimageA->GetAt(i);
		CAGimage* pNewAGimage=NULL;
		if(bIsCopy)
		{
			pNewAGimage=pAGimage->CreateMe();
			pNewAGimage->Copy(pAGimage);
		}
		else 
			pNewAGimage=pAGimage;
		SetAt(i,pNewAGimage,agfalse);
	}
}
void CAGimageObjPtrVec::Export(CAGptrArray* pOutAGimageA, agbool bIsCopy)
{
	DELETE_AGMAGICIP_ARRAYPTR(pOutAGimageA,agfalse)
	agint32		n=GetSize();
	if(n==0)	return;
	pOutAGimageA->SetSize(n);
	for(agint32 i=0; i<n; i++)
	{
		CAGimage* pAGimage=GetAt(i,agfalse);
		CAGimage* pNewAGimage=NULL;
		if(bIsCopy)
		{
			pNewAGimage=pAGimage->CreateMe();
			pNewAGimage->Copy(pAGimage);
		}
		else 
			pNewAGimage=pAGimage;
		pOutAGimageA->SetAt(i,pNewAGimage);
	}
}
agbool CAGimageObjPtrVec::Load(agtchar szDir[], agtchar szKey[], CAGimage* pTempImage, aguint32 imagetype)
{
	RemoveAll();

	CAGptrArray	OutAGimageA;
	agbool		bResult=CAGimageIOUtil::LoadA(&OutAGimageA, szDir, szKey, pTempImage, imagetype);
    if(bResult) Import(&OutAGimageA,agfalse);

	return bResult;
}
agbool CAGimageObjPtrVec::Save(agtchar szFilePathAndName[], aguint32 imagetype)
{
	if(IsEmpty())	return agfalse;

	CAGptrArray		OutAGimageA;
	Export(&OutAGimageA,agfalse);
	
    return CAGimageIOUtil::SaveA(&OutAGimageA, szFilePathAndName, imagetype);
}
/********************************CAGimageObjPtrbuMatrix****************************************/
CAGimageObjPtrbuMatrix::CAGimageObjPtrbuMatrix()
{
}
CAGimageObjPtrbuMatrix::~CAGimageObjPtrbuMatrix()
{
}
agint32 CAGimageObjPtrbuMatrix::TotalWidth(agint32 wHinge)
{
	agint32 max_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(pImageObjPtrVec)
			max_width = AGMAX(max_width,pImageObjPtrVec->TotalWidth(wHinge));
	}
	return max_width;
}
agint32 CAGimageObjPtrbuMatrix::TotalHeight(agint32 hHinge)
{
	agint32 total_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(pImageObjPtrVec)
		{

			agint32			h=pImageObjPtrVec->TotalHeight();
			total_height	+= h;
			if(i!=n-1)		total_height +=(h>0?hHinge:0);
		}
	}
	return total_height;
}

void CAGimageObjPtrbuMatrix::Import(CAGptrArray*  pInAGimageAA, agbool bIsCopy)
{
	RemoveAll();
	agint32		n=pInAGimageAA->GetSize();
	if(n==0)	return;
	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec* pAGimageObjPtrArray=new CAGimageObjPtrVec();
		pAGimageObjPtrArray->Import((CAGptrArray*)pInAGimageAA->GetAt(i),bIsCopy);
		SetAt(i,pAGimageObjPtrArray,agfalse);
	}
}
void CAGimageObjPtrbuMatrix::Export(CAGptrArray*  pOutAGimageAA, agbool bIsCopy)
{
	DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(pOutAGimageAA,agfalse)
	agint32		n=GetSize();
	if(n==0)	return;
	pOutAGimageAA->SetSize(n);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec* pAGimageObjPtrArray=GetAt(i,agfalse);
		CAGptrArray*  pOutAGimageA=new CAGptrArray();
		pAGimageObjPtrArray->Export(pOutAGimageA,bIsCopy);
		pOutAGimageAA->SetAt(i,pOutAGimageA);
	}
}
void CAGimageObjPtrbuMatrix::Import(CAGimageObjPtrtdMatrix* ptdMatrix, agbool bIsCopy)
{
	RemoveAll();
	if(ptdMatrix==NULL) return;

	agint32		n=ptdMatrix->GetSize();
	if(n==0)	return;

	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*&	pMeVec=ElementAt(i);
		CAGimageObjPtrVec*	pVec=ptdMatrix->GetAt(n-1-i);
		if(pVec)
		{
			pMeVec=(CAGimageObjPtrVec*)newAGOBJ_ARRAY_TYPE();
			pMeVec->CopyFrom(pVec,bIsCopy);
		}
	}
}
void CAGimageObjPtrbuMatrix::Export(CAGbuRectMatrix* pbuRectMatrix)
{
	pbuRectMatrix->RemoveAll();

	agint32 m=GetSize();
	agint32 accum_cy=0;
	for(agint32 i=0; i<m; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		agint32				n=pImageObjPtrVec->GetSize();
		if(n==0)			continue;

		CAGbuRectVec*		pbuRectVec=new CAGbuRectVec();
		agint32				accum_cx=0;
		AGBU_RECT			buRect={0,0,0,0};
		for(agint32 j=0; j<n; j++)
		{
			CAGimage* pImage=pImageObjPtrVec->GetAt(j);
			if(pImage==NULL) continue;
			agint32 image_width=pImage->GetWidth();
			agint32 image_height=pImage->GetHeight();
			if(image_width==0 || image_height==0)
				continue;

			memset(&buRect,0,sizeof(AGBU_RECT));
			buRect.left = accum_cx;
			buRect.bottom = accum_cy;
			buRect.right = buRect.left + image_width;
			buRect.top = buRect.bottom + image_height;
			
			pbuRectVec->Add(buRect);
			accum_cx +=image_width;
		}
		if(pbuRectVec->GetSize() > 0)
		{
			pbuRectMatrix->Add(pbuRectVec,agfalse);
			accum_cy += buRect.top-buRect.bottom;
		}
		else
			delete pbuRectVec;
	}
}
void CAGimageObjPtrbuMatrix::Flip()
{
	agint32		n=GetSize();
	if(n==0)	return;
	CAGimageObjPtrbuMatrix temp;
	temp.CopyFrom(this,agfalse);
	SetNULLAll();//tranh xoa

	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
		SetAt(i,temp.GetAt(n-1-i,agtrue),agfalse);
}

agbool CAGimageObjPtrbuMatrix::Load(agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage, aguint32 imagetype)
{
	RemoveAll();

	CAGptrArray	tdOutAGimageAA;
	agbool		bResult=CAGimageIOUtil::LoadAA_TD(&tdOutAGimageAA, szDir, szKey, numCols, pTempImage, imagetype);
    if(bResult)
	{
		Import(&tdOutAGimageAA,agfalse);
		Flip();
	}
	DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdOutAGimageAA)
	return bResult;
}
agbool CAGimageObjPtrbuMatrix::Save(agtchar szFilePathAndName[], aguint32 imagetype)
{
	if(IsEmpty())	return agfalse;

	CAGptrArray		tdOutAGimageAA;
	Flip();
	Export(&tdOutAGimageAA,agfalse);
	Flip();

    agbool	bResult=CAGimageIOUtil::SaveAA_TD(&tdOutAGimageAA, szFilePathAndName, imagetype);
	DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdOutAGimageAA)
	return bResult;
}
agbool CAGimageObjPtrbuMatrix::CreateByCut(CAGimage* pAGimageSrc, CAGbuRectMatrix* pRectMatrix)
{
	//kiem tra cac thong so
	if(pAGimageSrc==NULL || pRectMatrix==NULL)
		throw _T("Invalid parameter");
	agint32		m=pRectMatrix->GetSize();
	SetSize(m,agfalse);

	for(agint32 i=0; i<m; i++)
	{
		CAGbuRectVec*		pRectVec=pRectMatrix->GetAt(i);
		if(pRectVec==NULL)	continue;
		agint32				n=pRectVec->GetSize();
		if(n==0)			continue;

		CAGimageObjPtrVec*	pOutImageVec=new CAGimageObjPtrVec();
		pOutImageVec->SetSize(n,agfalse);//tat ca cac phan tu deu la NULL
		for(agint32 j=0; j<n; j++)
		{
			AGBU_RECT	crop_bu_rc=pRectVec->GetAt(j);
			AGTD_RECT	crop_td_rc;
			RECT		crop_rc;
			CAGmagicMicUtil::ChangeBUtoTD(pAGimageSrc->GetHeight(),&crop_td_rc,&crop_bu_rc);
			COPY_RECT_TO_RECT(crop_rc,crop_td_rc)
			
			CAGimage*	pCropImage=pAGimageSrc->CreateMe();
			if(pAGimageSrc->Crop(crop_rc, pCropImage))
				pOutImageVec->SetAt(j,pCropImage,agfalse);
		}
		SetAt(i,pOutImageVec,agfalse);
	}
	return agtrue;
}
agbool CAGimageObjPtrbuMatrix::CreateByCut(CAGimage* pAGimageSrc, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	CAGbuRectMatrix	RectMatrix;
	AGBU_RECT		TotalRect;
	TotalRect.left=TotalRect.bottom=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.top=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,CXsizes,nCXsizes,CYsizes,nCYsizes))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
agbool CAGimageObjPtrbuMatrix::CreateByCut(CAGimage* pAGimageSrc, SIZE block_size)
{
	CAGbuRectMatrix	RectMatrix;
	AGBU_RECT		TotalRect;
	TotalRect.left=TotalRect.bottom=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.top=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,block_size))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
agbool CAGimageObjPtrbuMatrix::CreateByCut(CAGimage* pAGimageSrc, agint32 nRows, agint32 nCols)
{
	CAGbuRectMatrix	RectMatrix;
	AGBU_RECT		TotalRect;
	TotalRect.left=TotalRect.bottom=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.top=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,nRows,nCols))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
CAGimage* CAGimageObjPtrbuMatrix::NewImageByJoin(AGCLRQUAD* fill_clr, agint32 wHinge, agint32 hHinge)
{
	CAGbuRectMatrix		buRectMatrix;
	Export(&buRectMatrix);

	agint32 max_width=buRectMatrix.TotalWidth(wHinge);
	agint32 max_height=buRectMatrix.TotalHeight(hHinge);
	if(max_width==0 || max_height==0)
		return NULL;

	CAGimage*			pResultImage=new CAGimage(max_width,max_height,24);
	if(fill_clr!=NULL)	pResultImage->FillColor(*fill_clr);

	agint32				m=buRectMatrix.GetSize();
	if(m!=GetSize())	throw _T("Fatal error");
	for(agint32 i=0; i<m; i++)
	{
		CAGbuRectVec*		pbuRectVec=buRectMatrix.GetAt(i);
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(pbuRectVec==NULL || pImageObjPtrVec==NULL)
			throw _T("Fatal error");
		agint32	n=pbuRectVec->GetSize();
		if(n==0 || n!=pImageObjPtrVec->GetSize())
			throw _T("Fatal error");

		for(agint32 j=0; j<n; j++)
		{
			AGBU_RECT	rc=pbuRectVec->GetAt(j);
			agint32		image_width=rc.right-rc.left;
			agint32		image_height=rc.top-rc.bottom;

			CAGimage*	pImage=pImageObjPtrVec->GetAt(j);
			if(pImage==NULL)
				throw _T("Fatal error");
			if( image_width!=(agint32)(pImage->GetWidth()) || image_height!=(agint32)(pImage->GetHeight()) )
				throw _T("Fatal error");
			pResultImage->MixFrom(*pImage,rc.left+j*wHinge,rc.bottom+i*hHinge);
		}
	}
	return pResultImage;
}
/********************************CAGimageObjPtrtdMatrix****************************************/
CAGimageObjPtrtdMatrix::CAGimageObjPtrtdMatrix()
{
}
CAGimageObjPtrtdMatrix::~CAGimageObjPtrtdMatrix()
{
}
agint32 CAGimageObjPtrtdMatrix::TotalWidth(agint32 wHinge)
{
	agint32 max_width=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(pImageObjPtrVec)
			max_width = AGMAX(max_width,pImageObjPtrVec->TotalWidth(wHinge));
	}
	return max_width;
}
agint32 CAGimageObjPtrtdMatrix::TotalHeight(agint32 hHinge)
{
	agint32 total_height=0;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(pImageObjPtrVec)
		{

			agint32			h=pImageObjPtrVec->TotalHeight();
			total_height	+= h;
			if(i!=n-1)		total_height +=(h>0?hHinge:0);
		}
	}
	return total_height;
}

void CAGimageObjPtrtdMatrix::Import(CAGptrArray*  pInAGimageAA, agbool bIsCopy)
{
	RemoveAll();
	agint32		n=pInAGimageAA->GetSize();
	if(n==0)	return;
	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec* pAGimageObjPtrArray=new CAGimageObjPtrVec();
		pAGimageObjPtrArray->Import((CAGptrArray*)pInAGimageAA->GetAt(i),bIsCopy);
		SetAt(i,pAGimageObjPtrArray,agfalse);
	}
}
void CAGimageObjPtrtdMatrix::Export(CAGptrArray*  pOutAGimageAA, agbool bIsCopy)
{
	DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(pOutAGimageAA,agfalse)
	agint32		n=GetSize();
	if(n==0)	return;
	pOutAGimageAA->SetSize(n);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec* pAGimageObjPtrArray=GetAt(i,agfalse);
		CAGptrArray*  pOutAGimageA=new CAGptrArray();
		pAGimageObjPtrArray->Export(pOutAGimageA,bIsCopy);
		pOutAGimageAA->SetAt(i,pOutAGimageA);
	}
}
void CAGimageObjPtrtdMatrix::Import(CAGimageObjPtrbuMatrix* pbuMatrix, agbool bIsCopy)
{
	RemoveAll();
	if(pbuMatrix==NULL) return;

	agint32		n=pbuMatrix->GetSize();
	if(n==0)	return;

	SetSize(n,agfalse);
	for(agint32 i=0; i<n; i++)
	{
		CAGimageObjPtrVec*&	pMeVec=ElementAt(i);
		CAGimageObjPtrVec*	pVec=pbuMatrix->GetAt(n-1-i);
		if(pVec)
		{
			pMeVec=(CAGimageObjPtrVec*)newAGOBJ_ARRAY_TYPE();
			pMeVec->CopyFrom(pVec,bIsCopy);
		}
	}
}

void CAGimageObjPtrtdMatrix::Export(CAGtdRectMatrix* ptdRectMatrix)
{
	ptdRectMatrix->RemoveAll();

	agint32 m=GetSize();
	agint32 accum_cy=0;
	for(agint32 i=0; i<m; i++)
	{
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		agint32				n=pImageObjPtrVec->GetSize();
		if(n==0)			continue;

		CAGtdRectVec*		ptdRectVec=new CAGtdRectVec();
		agint32				accum_cx=0;
		AGTD_RECT			tdRect={0,0,0,0};
		for(agint32 j=0; j<n; j++)
		{
			CAGimage* pImage=pImageObjPtrVec->GetAt(j);
			if(pImage==NULL) continue;
			agint32 image_width=pImage->GetWidth();
			agint32 image_height=pImage->GetHeight();
			if(image_width==0 || image_height==0)
				continue;

			memset(&tdRect,0,sizeof(AGTD_RECT));
			tdRect.left = accum_cx;
			tdRect.top = accum_cy;
			tdRect.right = tdRect.left + image_width;
			tdRect.bottom = tdRect.top + image_height;
			
			ptdRectVec->Add(tdRect);
			accum_cx +=image_width;
		}
		if(ptdRectVec->GetSize() > 0)
		{
			ptdRectMatrix->Add(ptdRectVec,agfalse);
			accum_cy += tdRect.bottom-tdRect.top;
		}
		else
			delete ptdRectVec;
	}
}
agbool CAGimageObjPtrtdMatrix::Load(agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage, aguint32 imagetype)
{
	RemoveAll();

	CAGptrArray	tdOutAGimageAA;
	agbool		bResult=CAGimageIOUtil::LoadAA_TD(&tdOutAGimageAA, szDir, szKey, numCols, pTempImage, imagetype);
	Import(&tdOutAGimageAA,agfalse);

	DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdOutAGimageAA)
	return bResult;
}
agbool CAGimageObjPtrtdMatrix::Save(agtchar szFilePathAndName[], aguint32 imagetype)
{
	if(IsEmpty())	return agfalse;

	CAGptrArray		tdOutAGimageAA;
	Export(&tdOutAGimageAA,agfalse);

    agbool	bResult=CAGimageIOUtil::SaveAA_TD(&tdOutAGimageAA, szFilePathAndName, imagetype);
	DELETE_AGMAGICIP_ARRAYPTR_ARRAY_ONLY_ROW(tdOutAGimageAA)
	return bResult;
}
agbool CAGimageObjPtrtdMatrix::CreateByCut(CAGimage* pAGimageSrc, CAGtdRectMatrix* pRectMatrix)
{
	//kiem tra cac thong so
	if(pAGimageSrc==NULL || pRectMatrix==NULL)
		throw _T("Invalid parameter");
	agint32		m=pRectMatrix->GetSize();
	SetSize(m,agfalse);

	for(agint32 i=0; i<m; i++)
	{
		CAGtdRectVec*		pRectVec=pRectMatrix->GetAt(i);
		if(pRectVec==NULL)	continue;
		agint32				n=pRectVec->GetSize();
		if(n==0)			continue;

		CAGimageObjPtrVec*	pOutImageVec=new CAGimageObjPtrVec();
		pOutImageVec->SetSize(n,agfalse);//tat ca cac phan tu deu la NULL
		for(agint32 j=0; j<n; j++)
		{
			AGTD_RECT	crop_td_rc=pRectVec->GetAt(j);
			RECT		crop_rc;
			COPY_RECT_TO_RECT(crop_rc,crop_td_rc)
			
			CAGimage*	pCropImage=pAGimageSrc->CreateMe();
			if(pAGimageSrc->Crop(crop_rc, pCropImage))
				pOutImageVec->SetAt(j,pCropImage,agfalse);
		}
		SetAt(i,pOutImageVec,agfalse);
	}
	return agtrue;
}
agbool CAGimageObjPtrtdMatrix::CreateByCut(CAGimage* pAGimageSrc, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes)
{
	CAGtdRectMatrix	RectMatrix;
	AGTD_RECT		TotalRect;
	TotalRect.left=TotalRect.top=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.bottom=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,CXsizes,nCXsizes,CYsizes,nCYsizes))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
agbool CAGimageObjPtrtdMatrix::CreateByCut(CAGimage* pAGimageSrc, SIZE block_size)
{
	CAGtdRectMatrix	RectMatrix;
	AGTD_RECT		TotalRect;
	TotalRect.left=TotalRect.top=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.bottom=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,block_size))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
agbool CAGimageObjPtrtdMatrix::CreateByCut(CAGimage* pAGimageSrc, agint32 nRows, agint32 nCols)
{
	CAGtdRectMatrix	RectMatrix;
	AGTD_RECT		TotalRect;
	TotalRect.left=TotalRect.top=0;
	TotalRect.right=pAGimageSrc->GetWidth();
	TotalRect.bottom=pAGimageSrc->GetHeight();
	if(!RectMatrix.CreateByCut(TotalRect,nRows,nCols))
		return agfalse;
	return CreateByCut(pAGimageSrc,&RectMatrix);
}
CAGimage* CAGimageObjPtrtdMatrix::NewImageByJoin(AGCLRQUAD* fill_clr, agint32 wHinge, agint32 hHinge)
{
	CAGtdRectMatrix		tdRectMatrix;
	Export(&tdRectMatrix);

	agint32 max_width=tdRectMatrix.TotalWidth(wHinge);
	agint32 max_height=tdRectMatrix.TotalHeight(hHinge);
	if(max_width==0 || max_height==0)
		return NULL;

	CAGimage*			pResultImage=new CAGimage(max_width,max_height,24);
	if(fill_clr!=NULL)	pResultImage->FillColor(*fill_clr);

	agint32				m=tdRectMatrix.GetSize();
	if(m!=GetSize())	throw _T("Fatal error");
	for(agint32 i=0; i<m; i++)
	{
		CAGtdRectVec*		ptdRectVec=tdRectMatrix.GetAt(i);
		CAGimageObjPtrVec*	pImageObjPtrVec=GetAt(i);
		if(ptdRectVec==NULL || pImageObjPtrVec==NULL)
			throw _T("Fatal error");
		agint32	n=ptdRectVec->GetSize();
		if(n==0 || n!=pImageObjPtrVec->GetSize())
			throw _T("Fatal error");

		for(agint32 j=0; j<n; j++)
		{
			AGTD_RECT	rc=ptdRectVec->GetAt(j);
			agint32		image_width=rc.right-rc.left;
			agint32		image_height=rc.bottom-rc.top;

			CAGimage*	pImage=pImageObjPtrVec->GetAt(j);
			if(pImage==NULL)
				throw _T("Fatal error");
			if( image_width!=(agint32)(pImage->GetWidth()) || image_height!=(agint32)(pImage->GetHeight()) )
				throw _T("Fatal error");

			AGTD_POINT td_p;
			td_p.x=rc.left+j*wHinge;
			td_p.y=rc.top+i*hHinge;
			AGBU_POINT bu_p;
			CAGmagicMicUtil::ChangeTDtoBU(max_height,&bu_p,&td_p);

			pResultImage->MixFrom(*pImage,bu_p.x,bu_p.y);
		}
	}
	return pResultImage;
}
/********************************CAGimageIDs****************************************/

void CAGimageIDs::DBRead(aguint_id ImageType)
{
	RemoveAll();

	agint32		fieldsNum=0;
	agint32		recordsNum=0;
	aguint_id**	data=NULL;

	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ID FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	if(ImageType!=0)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Type="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);
	}

	AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum,recordsNum);
	if(SQL)				free(SQL);
	if(recordsNum==0)	return;

	SetSize(recordsNum);
	for(agint32 i=0; i<recordsNum; i++)
		m_vector[i]=data[i][0];
	
	if(data)
	{
		for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
		free(data);
	}
}

/********************************CAGimageDBItemType****************************************/

CAGimageDBItemType::CAGimageDBItemType() : CAGmagicDBOrg()
{
	m_ID=0;
	m_Name=NULL;
}
CAGimageDBItemType::~CAGimageDBItemType()
{
	Destroy();
}
void CAGimageDBItemType::Destroy()//Ham huy
{
	m_ID=0;
	if(m_Name) free(m_Name);	m_Name=NULL;
}
agbool CAGimageDBItemType::CopyFrom(CAGimageDBItemType* item_type)
{
	if(item_type==NULL)	throw _T("Parameter must not NULL");
	Destroy();

	DBCnnAttach(item_type->DBCnnGet());
	m_ID=item_type->m_ID;
	CAGmagicStrUtil::private_tcscat(m_Name,item_type->m_Name,agtrue);
	return agtrue;
}

/********************************CAGimageDBItemTypes****************************************/

CAGimageDBItemTypes::CAGimageDBItemTypes() : CAGobjPtrArray<CAGimageDBItemType>(), CAGmagicDBOrg()
{
}
CAGimageDBItemTypes::~CAGimageDBItemTypes()
{
}
agbool CAGimageDBItemTypes::DBRead(agtchar SQL[])
{
	if(SQL==NULL)	throw _T("Invalid Parameter");
	RemoveAll();

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agint32 count=0;
		while(!(pRs->EndOfFile))
        {
			CAGimageDBItemType*	item_type=new CAGimageDBItemType();
			item_type->DBCnnAttach(m_pDBCnnI);

			//ID
			_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
			item_type->m_ID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
	
			//Name
			varValue = pRs->Fields->GetItem(_T("Description"))->Value;
			CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,item_type->m_Name);

			Add(item_type);
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
	return agtrue;
}
void CAGimageDBItemTypes::DBReadAll()
{
	agtchar SQL[256];
	_tcscpy(SQL,_T("SELECT * FROM ImagesType"));

	DBRead(SQL);
}
/********************************CAGimageDBItem****************************************/
#include "AGsemantic.h"
#include "AGimageSeg.h"

CAGimageDBItem::CAGimageDBItem() : CAGmagicDBOrg()
{
	m_bIsRestoreImage=agfalse;
	m_ImageID=0;
	m_ImageType=0;
	m_Name=NULL;
	m_URL=NULL;
	m_pAGimageSrc=NULL;
	m_pReservedAGmagicElement=NULL;
	m_pSemanticTree=NULL;
}
CAGimageDBItem::~CAGimageDBItem()
{
	Destroy();
	DBCnnDetach();
}

CAGimage* CAGimageDBItem::CreateAGimage()
{
	return new CAGimage();
}
agbool CAGimageDBItem::CopyFrom(CAGimageDBItem* item)
{
	if(item==NULL)	throw _T("Parameter must not NULL");
	Destroy();
	m_bIsRestoreImage=item->m_bIsRestoreImage;

	DBCnnAttach(item->DBCnnGet());
	m_ImageID=item->m_ImageID;
	m_ImageType=item->m_ImageType;
	if(item->m_Name)	CAGmagicStrUtil::private_tcscat(m_Name,item->m_Name,agtrue);
	if(item->m_URL)		CAGmagicStrUtil::private_tcscat(m_URL,item->m_URL,agtrue);
	if(item->m_pAGimageSrc && IsStoreImage())
	{
		m_pAGimageSrc=CreateAGimage();
		m_pAGimageSrc->Copy(item->m_pAGimageSrc);
	}
	if(item->m_pReservedAGmagicElement)
	{
		m_pReservedAGmagicElement=item->m_pReservedAGmagicElement->CreateMe();
		m_pReservedAGmagicElement->CopyFrom(item->m_pReservedAGmagicElement);
	}
	if(item->m_pSemanticTree)
	{
		m_pSemanticTree=new CAGimageSemanticTree();
		m_pSemanticTree->CopyFrom(item->m_pSemanticTree);
	}
	return agtrue;
}
void CAGimageDBItem::SetSemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy)
{
	if(m_pSemanticTree) delete m_pSemanticTree; m_pSemanticTree=NULL;
	if(!bIsCopy) m_pSemanticTree=pSemanticTree;
	else if(pSemanticTree!=NULL)
	{
		m_pSemanticTree=new CAGimageSemanticTree();
		m_pSemanticTree->CopyFrom(pSemanticTree);
	}
}
void CAGimageDBItem::AllocName(agtchar Name[])
{
	if(m_Name)	free(m_Name);	m_Name=NULL;
	if(Name)	CAGmagicStrUtil::private_tcscat(m_Name,Name,agtrue);
}
void CAGimageDBItem::AllocURL(agtchar URL[])
{
	if(m_URL)	free(m_URL);	m_URL=NULL;
	if(URL)		CAGmagicStrUtil::private_tcscat(m_URL,URL,agtrue);
}
void CAGimageDBItem::Destroy()//Ham huy
{
	m_ImageID=0;
	m_ImageType=0;
	if(m_Name)			{free(m_Name);			m_Name=NULL;}
	if(m_URL)			{free(m_URL);			m_URL=NULL;}
	if(m_pAGimageSrc)	{delete m_pAGimageSrc;	m_pAGimageSrc=NULL;}

	if(m_pReservedAGmagicElement)		{delete m_pReservedAGmagicElement;	m_pReservedAGmagicElement=NULL;}
	if(m_pSemanticTree)	delete m_pSemanticTree;	m_pSemanticTree=NULL;
}

agbool CAGimageDBItem::IsStoreImage()
{
	return m_bIsRestoreImage;
}
void CAGimageDBItem::SetIsStoreImage(agbool bIsRestoreImage)
{
	if(m_pAGimageSrc)	{delete m_pAGimageSrc;	m_pAGimageSrc=NULL;}
	m_bIsRestoreImage=bIsRestoreImage;
}

agtchar* CAGimageDBItem::DBGetSelectSQL(agtchar SQL[], aguint_id ImageID)
{
	SQL[0]=0;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agfalse);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agfalse);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agfalse);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agfalse);
	return SQL;
}
agtchar* CAGimageDBItem::DBGetInsertSQL(agtchar*& SQL, aguint_id ImageType, agtchar Name[], agtchar URL[])
{
	if(SQL) free(SQL);	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(Type,Name,URL) VALUES("),agtrue);
	
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);

	if(Name)
	{
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,Name,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);
	}
	else CAGmagicStrUtil::private_tcscat(SQL,_T("NULL, "),agtrue);

	if(URL)
	{
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,URL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}
	else CAGmagicStrUtil::private_tcscat(SQL,_T("NULL"),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	return SQL;
}
agtchar* CAGimageDBItem::DBGetUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id ImageType, agtchar Name[], agtchar URL[])
{
	if(SQL) free(SQL);	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" SET Type="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);

	if(Name)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(", Name="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,Name,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}
	if(URL)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(", URL="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,URL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	return SQL;
}
agtchar* CAGimageDBItem::DBGetDeleteSQL(agtchar*& SQL, aguint_id ImageID)
{
	if(SQL) free(SQL);	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
agbool CAGimageDBItem::LoadURL(agtchar URL[])
{
	if(URL==NULL)	return agfalse;
	Destroy();
	
	if(m_bIsRestoreImage)
	{
		m_pAGimageSrc=CreateAGimage();
		if(m_pAGimageSrc->Load(URL))
			m_ImageID=m_pAGimageSrc->m_ID;
		else
		{
			delete m_pAGimageSrc;	m_pAGimageSrc=NULL;
			return agfalse;
		}
	}
	
	agtchar*	Name=_tcsrchr(URL,AGMAGIC_DIR_SPLASH);
	if(Name)
	{
		Name++;
		AllocName(Name);
	}
	AllocURL(URL);
	return agtrue;
}
agbool CAGimageDBItem::DBRead(aguint_id ImageID)
{
	Destroy();
	agtchar SQL[1024];
	DBGetSelectSQL(SQL,ImageID);
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);
        if((pRs->EndOfFile))	return agfalse;

		_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
		m_ImageID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);
		if(m_ImageID!=ImageID)	throw _T("Fatal error");

		varValue = pRs->Fields->GetItem(_T("Type"))->Value;
		m_ImageType=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

		varValue = pRs->Fields->GetItem(_T("Name"))->Value;
		CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_Name);

		varValue = pRs->Fields->GetItem(_T("URL"))->Value;
		CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_URL);

		if(m_bIsRestoreImage)
		{
			if(m_pAGimageSrc)	delete m_pAGimageSrc;
			m_pAGimageSrc=CreateAGimage();
			if(m_pAGimageSrc->Load(m_URL))
				m_pAGimageSrc->m_ID=m_ImageID;
			else
			{
				if(m_pAGimageSrc)	delete m_pAGimageSrc;
				m_pAGimageSrc=NULL;
			}
		}
		pRs->Close();
	}
	catch(_com_error &e)
	{
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif

	return agtrue;
}

#include "AGimageFeat.h"
agbool CAGimageDBItem::DBInsert(agbool IsInsertFeatures, agbool bIsNormWhenInsertFeatures, agbool bIsInsertAff, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs)
{
	agtchar* SQL=NULL;
	DBGetInsertSQL(SQL,m_ImageType,m_Name,m_URL);
	if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) return agfalse;
	if(SQL) free(SQL); SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Type="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,m_ImageType,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND Name="),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,m_Name,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);

	//CAGmagicStrUtil::private_tcscat(SQL,_T(" AND URL="),agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,m_URL,agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenStatic, adLockReadOnly, adCmdText);
        if((pRs->EndOfFile))	throw _T("Insert Error");
		pRs->MoveLast();

		_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
		m_ImageID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

		varValue = pRs->Fields->GetItem(_T("Type"))->Value;
		if(m_ImageType!=CAGmagicMicUtil::AGconvertFromVariantToID(varValue))
			throw _T("Fatal error");

		//varValue = pRs->Fields->GetItem(_T("Name"))->Value;
		//CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_Name);

		//varValue = pRs->Fields->GetItem(_T("URL"))->Value;
		//CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,m_URL);

		pRs->Close();
	}
	catch(_com_error &e)
	{
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif

	if(SQL) free(SQL); SQL=NULL;
	if(!IsInsertFeatures || m_pAGimageSrc==NULL)	return agtrue;
	m_pAGimageSrc->m_ID=m_ImageID;

//Them vao table Image256ClrFeatures hay Image9HSVClr12TxtFeatures
	IAGflexfVec*	fVector=CAGfeatUtil::CreateFeaturesVector();
	fVector->SetIsNorm(bIsNormWhenInsertFeatures);
	if(!fVector->CreateFrom(m_pAGimageSrc,bIsNegativeImageWhenSegment,pSegs))	return agtrue;
	fVector->DBCnnAttach(m_pDBCnnI);
	fVector->DBInsert();
	delete fVector;
	
	if(pSegs)//luu tru lai cac phan doan
	{
		pSegs->DBCnnAttach(m_pDBCnnI);
		pSegs->SetImageID(m_ImageID);
		pSegs->DBInsert();
	}
////////Insert Aff/////////////////////////////////
	if(!bIsInsertAff)	return agtrue;

	CAGimageIDs ImageIDs;
	ImageIDs.DBCnnAttach(m_pDBCnnI);
	ImageIDs.DBRead(m_ImageType);
	ImageIDs.RemoveIfValue(m_ImageID);
	agint32		m=ImageIDs.GetSize();
	if(m==0)	return agtrue;

	CAGimageAffVec main_affs, norm_main_affs;
	main_affs.DBCnnAttach(m_pDBCnnI);
	norm_main_affs.DBCnnAttach(m_pDBCnnI);
	main_affs.SetIsNorm(agfalse);
	norm_main_affs.SetIsNorm(agfalse);

	main_affs.SetSize(m);
	norm_main_affs.SetSize(m);
	main_affs.m_aRelatedImageID.SetSize(m);
	norm_main_affs.m_aRelatedImageID.SetSize(m);
	main_affs.m_ImageID=norm_main_affs.m_ImageID=m_ImageID;

	agint32 i=0;
	for(i=0; i<m; i++)
	{
		aguint_id ImageID=ImageIDs.GetAt(i);
		if(ImageID==m_ImageID)	throw _T("Fatal Error");

		main_affs.m_aRelatedImageID.SetAt(i,ImageID);//column RELATEDIMAGEID la cot 1
		main_affs.m_vector[i]=1;

		norm_main_affs.m_aRelatedImageID.SetAt(i,ImageID);//column RELATEDIMAGEID la cot 1
		norm_main_affs.m_vector[i]=1;
	}
	main_affs.m_pNoFreeTempAGimageSrc=norm_main_affs.m_pNoFreeTempAGimageSrc=NULL;
	norm_main_affs.Normalize();

	main_affs.DBInsert();
	norm_main_affs.DBInsert();
/////////////////////////////////////////////////

	for(i=0; i<m; i++)
	{
		aguint_id ImageID=ImageIDs.GetAt(i);
		if(ImageID==m_ImageID)	throw _T("Fatal Error");

		CAGimageAffVec affs, norm_affs;
		affs.DBCnnAttach(m_pDBCnnI);
		norm_affs.DBCnnAttach(m_pDBCnnI);
		affs.SetIsNorm(agfalse);
		norm_affs.SetIsNorm(agfalse);

		affs.SetSize(1);
		norm_affs.SetSize(1);
		affs.m_aRelatedImageID.SetSize(1);
		norm_affs.m_aRelatedImageID.SetSize(1);
		affs.m_ImageID=norm_affs.m_ImageID=ImageID;

		affs.m_aRelatedImageID.SetAt(0,m_ImageID);//column RELATEDIMAGEID la cot 1
		affs.m_vector[0]=1;

		norm_affs.m_aRelatedImageID.SetAt(0,m_ImageID);//column RELATEDIMAGEID la cot 1
		norm_affs.m_vector[0]=1;

		affs.m_pNoFreeTempAGimageSrc=norm_affs.m_pNoFreeTempAGimageSrc=NULL;
		norm_affs.Normalize();

		affs.DBInsert();
		norm_affs.DBInsert();
	}
	return agtrue;
}
agbool CAGimageDBItem::DBUpdate()
{
	agtchar* SQL=NULL;
	DBGetUpdateSQL(SQL,m_ImageType,m_ImageID,m_Name,m_URL);
	if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Update Error");
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}
agbool CAGimageDBItem::DBDelete()
{
	agtchar* SQL=NULL;
	DBGetDeleteSQL(SQL,m_ImageID);
	if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Delete Error");
	if(SQL) free(SQL); SQL=NULL;
	return agtrue;
}


/********************************CAGimageDBItems****************************************/

CAGimageDBItems::CAGimageDBItems() : CAGobjPtrArray<CAGimageDBItem>(), CAGmagicDBOrg()
{
	m_bIsRestoreImage=agfalse;
}
CAGimageDBItems::~CAGimageDBItems()
{
}
void CAGimageDBItems::CopyInfoFrom(CAGobjPtrArray<CAGimageDBItem>* xa)
{
	CAGobjPtrArray<CAGimageDBItem>::CopyInfoFrom(xa);
	CAGimageDBItems* pAGimageDBItems=(CAGimageDBItems*)xa;
	DBCnnAttach(pAGimageDBItems->DBCnnGet());
	SetIsStoreImage(pAGimageDBItems->IsStoreImage());
}
agbool CAGimageDBItems::IsStoreImage()
{
	return m_bIsRestoreImage;
}
void CAGimageDBItems::SetIsStoreImage(agbool bIsRestoreImage)
{
	m_bIsRestoreImage=bIsRestoreImage;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageDBItem*	pAGimageDBItem=(CAGimageDBItem*)GetAt(i);
		pAGimageDBItem->SetIsStoreImage(m_bIsRestoreImage);
	}
}
agbool CAGimageDBItems::CopyFrom(CAGimageDBItems* xa, agbool bIsCopy)
{
	if(!CAGobjPtrArray<CAGimageDBItem>::CopyFrom((CAGobjPtrArray<CAGimageDBItem>*)xa,bIsCopy))
		return agfalse;
	CopyInfoFrom(xa);
	return agtrue;
}
agbool CAGimageDBItems::TransferFrom(CAGimageDBItems* xa)
{
	if(!CAGobjPtrArray<CAGimageDBItem>::TransferFrom(xa))
		return agfalse;
	CopyInfoFrom(xa);
	xa->DBCnnDetach();
	return agtrue;
}
void AGimageDBItem_ReadImageFiles(void* pAtt, void* szPath, void* pReserved)
{
//#if AGMAGIC_OS_TYPE ==AGMAGIC_WINDOWS_OS
//	WIN32_FIND_DATA FileData=*((WIN32_FIND_DATA*)pAtt);
//#else
//	throw _T("Implement not yet");
//#endif
	CAGimageDBItems*	pAGimageDBItems=(CAGimageDBItems*)pReserved;
	agtchar*			URL=(agtchar*)szPath;
	CAGimageDBItem*		pAGimageDBItem=new CAGimageDBItem();
	pAGimageDBItem->SetIsStoreImage(pAGimageDBItems->IsStoreImage());
	pAGimageDBItem->DBCnnAttach(pAGimageDBItems->DBCnnGet());
	if(!pAGimageDBItem->LoadURL(URL))	delete pAGimageDBItem;
	else								pAGimageDBItems->Add(pAGimageDBItem);	
}
void CAGimageDBItems::LoadDir(agtchar szOrgDir[], agtchar szFilter[])
{
	RemoveAll();
	CAGmagicIOUtil::SimpleBrowseFiles(AGimageDBItem_ReadImageFiles,szOrgDir,szFilter,AGMAGIC_OR_SEPS,this);
}
void CAGimageDBItems::AddURL(agtchar URL[])
{
	CAGimageDBItem*		pAGimageDBItem=new CAGimageDBItem();
	pAGimageDBItem->SetIsStoreImage(IsStoreImage());
	pAGimageDBItem->DBCnnAttach(DBCnnGet());
	if(!pAGimageDBItem->LoadURL(URL))	delete pAGimageDBItem;
	else								Add(pAGimageDBItem);	
}

agint32 CAGimageDBItems::LSearchImageID(aguint_id ImageID)
{
	agint32 i=0;
	for(i=0; i<m_ne; i++)
		if(m_vector[i]->m_ImageID==ImageID) break;
	if(i==m_ne)	return -1;
	return i;
}
void CAGimageDBItems::RemoveSameImageIDs()
{
	if(IsEmpty())		return;
	CAGimageDBItems	xa;
	xa.TransferFrom(this);
	RemoveAll();
	
	agint32 n=xa.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		if(LSearchImageID(xa.GetAt(i)->m_ImageID)==-1)
		{
			Add(xa.GetAt(i));
			xa.SetNULLAt(i);
		}
	}
	CopyInfoFrom(&xa);
}
void CAGimageDBItems::GetAllImageIDs(CAGidArray* ImageIDs)
{
	ImageIDs->RemoveAll();
	if(IsEmpty())		return;
	ImageIDs->SetSize(m_ne);
	for(agint32 i=0; i<m_ne; i++)
	{
		aguint_id ImageID=m_vector[i]->m_ImageID;
		ImageIDs->SetAt(i,ImageID);
	}
}
void CAGimageDBItems::Import(aguint_id ImageIDs[], agint32 nImageIDs)//nhap ImageIDs
{
	if(ImageIDs==NULL)	throw _T("Parameter Invalid");
	RemoveAll();
	if(nImageIDs==0)	return;
	for(agint32 i=0; i<nImageIDs; i++)
	{
		CAGimageDBItem*		pAGimageDBItem=new CAGimageDBItem();
		pAGimageDBItem->SetIsStoreImage(IsStoreImage());
		pAGimageDBItem->DBCnnAttach(DBCnnGet());
		pAGimageDBItem->m_ImageID=ImageIDs[i];
		Add(pAGimageDBItem);
	}
}
void CAGimageDBItems::Import(CAGidArray* ImageIDs)
{
	Import(ImageIDs->GetData(), ImageIDs->GetSize());
}
CAGimage* CAGimageDBItems::GetImageAt(agint32 idx)
{
	CAGimageDBItem* item=GetAt(idx);
	return item->m_pAGimageSrc;
}
aguint_id CAGimageDBItems::GetIDAt(agint32 idx)
{
	CAGimageDBItem* item=GetAt(idx);
	return item->m_ImageID;;
}
CAGimageDBItem*	CAGimageDBItems::GetAtID(aguint_id ImageID)
{
	agint32		idx=LSearchImageID(ImageID);
	if(idx==-1)	return NULL;
	else		return GetAt(idx);
}
void CAGimageDBItems::RemoveIfImageID(aguint_id ImageID)
{
	agint32		idx=LSearchImageID(ImageID);
	if(idx!=-1)	RemoveAt(idx);
}
agbool CAGimageDBItems::IsContentImageIDs(CAGidArray* ImageIDs)
{
	if(ImageIDs==NULL)	throw _T("Parameter Invalid");
	agint32		n=ImageIDs->GetSize();
	if(n==0)	agtrue;
	for(agint32 i=0; i<n; i++)
	{
		if(LSearchImageID(GetIDAt(i))==-1)	return agfalse;
	}
	return agtrue;
}
agbool CAGimageDBItems::DBRead(aguint_id ImageIDs[], aguint32 nImageIDs)
{
	CAGobjPtrArray<CAGimageDBItem>::RemoveAll();
	for(aguint32 i=0; i<nImageIDs; i++)
	{
		CAGimageDBItem*	item=new CAGimageDBItem();
		item->SetIsStoreImage(IsStoreImage());
		item->DBCnnAttach(m_pDBCnnI);

		if(!item->DBRead(ImageIDs[i]))	{delete item; continue;}//throw _T("Error Read Database");
		Add(item);
	}
	return agtrue;
}
agbool CAGimageDBItems::DBRead(agtchar SQL[], agbool bIsReadURL)
{
	if(SQL==NULL) throw _T("Invalid Database");
	RemoveAll();

#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)m_pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agint32 count=0;
		while(!(pRs->EndOfFile))
        {
			CAGimageDBItem*	item=new CAGimageDBItem();
			item->SetIsStoreImage(IsStoreImage());
			item->DBCnnAttach(m_pDBCnnI);

			_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
			item->m_ImageID=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

			varValue = pRs->Fields->GetItem(_T("Type"))->Value;
			item->m_ImageType=CAGmagicMicUtil::AGconvertFromVariantToID(varValue);

			varValue = pRs->Fields->GetItem(_T("Name"))->Value;
			CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,item->m_Name);

			if(bIsReadURL)
			{
				varValue = pRs->Fields->GetItem(_T("URL"))->Value;
				CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,item->m_URL);
			}
			if(item->IsStoreImage() && item->m_URL)
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

			count++;
			Add(item);
			pRs->MoveNext();
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
agbool CAGimageDBItems::DBRead()
{
	agtchar SQL[1024];
	_tcscpy(SQL,_T("SELECT * FROM "));
	_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable);

	return DBRead(SQL);
}
agbool CAGimageDBItems::DBInsert(agbool IsInsertFeatures, agbool bIsNormWhenInsertFeatures, agbool bIsInsertAff, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs)
{
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageDBItem*	item=m_vector[i];
		if(!item->DBInsert(IsInsertFeatures, bIsNormWhenInsertFeatures, bIsInsertAff, bIsNegativeImageWhenSegment,pSegs))	throw _T("Error Insert");
	}
	return agtrue;
}
agbool CAGimageDBItems::DBUpdate()
{
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageDBItem*	item=m_vector[i];
		if(!item->DBUpdate())	throw _T("Error Update");
	}
	return agtrue;
}
agbool CAGimageDBItems::DBDelete()
{
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageDBItem*	item=m_vector[i];
		if(!item->DBDelete())	throw _T("Error Delete");
	}
	return agtrue;
}
agbool CAGimageDBItems::DBAppendDistinctImageIDs(aguint_id ImageIDs[], aguint32 nImageIDs, agbool bIsReReadDB)
{
	if(ImageIDs==NULL || nImageIDs==0)	return agfalse;
	CAGidArray	IDs;
	for(aguint32 i=0; i<nImageIDs; i++)
		if(LSearchImageID(ImageIDs[i])==-1)	IDs.Add(ImageIDs[i]);
	if(IDs.GetSize()==0)	return agtrue;
	CAGimageDBItems	DBItems;
	DBItems.CopyInfoFrom(this);

	if(bIsReReadDB)
	{
		if(!DBItems.DBRead(IDs.GetData(),IDs.GetSize()))	return agfalse;
	}
	else
		DBItems.Import(&IDs);	
	Append(&DBItems);
	DBItems.SetNULLAll();//de DBItems dung huy nhung item da append cho this
	return agtrue;
}
void CAGimageDBItems::CopyAGmagicElementsTo(CAGmagicElementPtrArray* pAGmagicElementPtrArray)
{
	if(pAGmagicElementPtrArray==NULL) throw _T("Invalid parameter");
	pAGmagicElementPtrArray->RemoveAll();
	if(IsEmpty())	return;

	pAGmagicElementPtrArray->SetSize(m_ne);
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimageDBItem*	item=m_vector[i];
		if(item!=NULL)
		{
			CAGmagicElement* e=item->m_pReservedAGmagicElement->CreateMe();
			e->CopyFrom(item->m_pReservedAGmagicElement);
			pAGmagicElementPtrArray->SetAt(i,e);
		}
	}

}

/********************************CAGinteractImagesMsg****************************************/

CAGinteractImagesMsg::CAGinteractImagesMsg()
{
	m_szNotice=NULL;
	m_bIsDeleteImages=agtrue;
	m_bIsDeleteMeInProc=agtrue;
	m_bIsPassID=agtrue;

	m_pNoFreeReserved=NULL;
	m_pSemanticTree=NULL;
	m_CandidateCount=0;
}
CAGinteractImagesMsg::~CAGinteractImagesMsg()
{
	RemoveAll();
	if(m_pSemanticTree) delete m_pSemanticTree; m_pSemanticTree=NULL;
}
void CAGinteractImagesMsg::CopyInfoFrom(CAGobjPtrArray<CAGimageDBItem>* xa)
{
	CAGimageDBItems::CopyInfoFrom(xa);
	CAGinteractImagesMsg*	pMsg=(CAGinteractImagesMsg*)xa;

	m_bIsDeleteImages=pMsg->m_bIsDeleteImages;
	m_bIsDeleteMeInProc=pMsg->m_bIsDeleteMeInProc;
	m_bIsPassID=pMsg->m_bIsPassID;
	m_pNoFreeReserved=pMsg->m_pNoFreeReserved;

	if(pMsg->m_szNotice==NULL)
		m_szNotice=NULL;
	else
		SetNotice(pMsg->m_szNotice);

	m_CandidateCount=pMsg->m_CandidateCount;
}
agbool CAGinteractImagesMsg::CopyFrom(CAGinteractImagesMsg* xa, agbool bIsCopy)
{
	if(!CAGimageDBItems::CopyFrom((CAGimageDBItems*)xa, bIsCopy))
		return agfalse;
	if(m_pSemanticTree) delete m_pSemanticTree; m_pSemanticTree=NULL;
	if(xa->m_pSemanticTree)
	{
		m_pSemanticTree=new CAGimageSemanticTree();
		m_pSemanticTree->CopyFrom(xa->m_pSemanticTree);
	}
	return agtrue;
}
agbool CAGinteractImagesMsg::TransferFrom(CAGinteractImagesMsg* xa)
{
	if(!CAGimageDBItems::TransferFrom((CAGimageDBItems*)xa))
		return agfalse;
	if(m_pSemanticTree) delete m_pSemanticTree; m_pSemanticTree=NULL;
	m_pSemanticTree=xa->m_pSemanticTree; xa->m_pSemanticTree=NULL;
	return agtrue;
}
void CAGinteractImagesMsg::SetSemanticTree(CAGimageSemanticTree* pSemanticTree, agbool bIsCopy)
{
	if(m_pSemanticTree) delete m_pSemanticTree; m_pSemanticTree=NULL;
	if(!bIsCopy) m_pSemanticTree=pSemanticTree;
	else if(pSemanticTree!=NULL)
	{
		m_pSemanticTree=new CAGimageSemanticTree();
		m_pSemanticTree->CopyFrom(pSemanticTree);
	}
}
void CAGinteractImagesMsg::RemoveAll()
{
	if(!m_bIsDeleteImages)
	{
		agint32 n=GetSize();
		for(agint32 i=0; i<n; i++)
		{
			CAGimageDBItem* item=GetAt(i);
			item->m_pAGimageSrc=NULL;
		}
	}
	if(m_szNotice)	free(m_szNotice);	m_szNotice=NULL;
	m_pNoFreeReserved=NULL;
	CAGimageDBItems::RemoveAll();
}
void CAGinteractImagesMsg::SetNotice(agtchar szNotice[])
{
	if(m_szNotice)	free(m_szNotice);	m_szNotice=NULL;
	if(szNotice)
		CAGmagicStrUtil::private_tcscat(m_szNotice,szNotice,agtrue);
}
agtchar* CAGinteractImagesMsg::GetNotice()
{
	return m_szNotice;
}

agtchar* CAGinteractImagesMsg::GetTextAt(agint32 idx)
{
	CAGimageDBItem* item=GetAt(idx);
	return item->m_URL;
}

agbool CAGinteractImagesMsg::IsDeleteImages()
{
	return m_bIsDeleteImages;
}
agbool CAGinteractImagesMsg::IsDeleteMeInProc()
{
	return m_bIsDeleteMeInProc;
}
agbool CAGinteractImagesMsg::IsPassID()
{
	return m_bIsPassID;
}

void CAGinteractImagesMsg::SetDeleteImages(agbool bIsDeleteImages)
{
	m_bIsDeleteImages=bIsDeleteImages;
}
void CAGinteractImagesMsg::SetDeleteMeInProc(agbool bIsDeleteMeInProc)
{
	m_bIsDeleteMeInProc=bIsDeleteMeInProc;
}
void CAGinteractImagesMsg::SetIsPassID(agbool bIsPassID)
{
	m_bIsPassID=bIsPassID;
	m_bIsRestoreImage=!bIsPassID;
}
void CAGinteractImagesMsg::CopyIDsTo(CAGidArray* pIDs)
{
	if(pIDs==NULL)	return ;
	pIDs->RemoveAll();
	agint32	n=GetSize();
	for(agint32 i=0; i<n; i++)
	{
		CAGimageDBItem* pAGimageDBItem=GetAt(i);
		if(IsPassID())	
			pIDs->Add(pAGimageDBItem->m_ImageID);
		else if(pAGimageDBItem->m_pAGimageSrc)
			pIDs->Add(pAGimageDBItem->m_pAGimageSrc->m_ID);
	}
}
void CAGinteractImagesMsg::DefaultInit(CAGinteractImagesMsg* pMsg)
{
	pMsg->RemoveAll();
	pMsg->SetIsStoreImage(agfalse);
	pMsg->SetDeleteMeInProc(agtrue);
	pMsg->SetDeleteImages(agtrue);
	pMsg->SetIsPassID(agtrue);
	pMsg->m_CandidateCount=0;
}

