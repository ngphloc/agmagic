#include "AGimageUtil.h"
#include "AGsemantic.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/AGutil/main/AGutilCore.h"
#include "../../../common/lib/AGutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"


/*******************************class CAGmagicIPConfUtil*******************************/
agbool CAGmagicIPConfUtil::bIsInitAGmagicIPConf = agfalse;

agtchar* CAGmagicIPConfUtil::AGmagicIP_Global_Tables[]={
					_T("ImagesType"),
					_T("Images"),
					_T("ImagesInfo"),
					_T("Image256ClrFeatures"),	_T("Image9HSVClr12TxtFeatures"),  _T("ImageMultiClrFeatures"),	_T("ImageMultiFeatures"),
					_T("ImagesNormAffinity"),	_T("ImagesAffinity"),
					_T("UserAccessPattern"),	_T("UserAccessFreq"),
					_T("Semantic"),	            _T("SemanticInfo"),               _T("ImagesSemantic"),			_T("ImagesSemanticWeight"),
					_T("HBlockMatrixIns"),		_T("HBlockMatrix"),
					_T("ImageHSegIns"),			_T("ImageHSeg"),			      _T("ImageHBlock")
				};
agint32	CAGmagicIPConfUtil::AGmagicIP_Global_nTables=20;
agbool	CAGmagicIPConfUtil::AGmagicIP_Global_bTables[]={agtrue,agtrue,agfalse,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,   agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue,agtrue};

agtchar CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable[256]=_T("Images");
agint32 CAGmagicIPConfUtil::AGmagicIP_ClobalFeatures=AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE;

void CAGmagicIPConfUtil::Init()
{
	if(bIsInitAGmagicIPConf)	return;
	else						bIsInitAGmagicIPConf = agtrue;

	_tcscpy(AGmagicIP_GlobalCurImageTable,AGmagicIP_Global_Tables[1]);

#if AGMAGIC_SUPPORT_ADO
	if(CAGmagicConfUtil::AGmagic_GlobalADOProvider==AGMAGIC_SQLSERVER_ADO_PROVIDER)
	{
		AGmagicIP_Global_bTables[5]=agfalse;
		AGmagicIP_Global_bTables[6]=agfalse;
	}
	else if(CAGmagicConfUtil::AGmagic_GlobalADOProvider==AGMAGIC_ACCESS_ADO_PROVIDER)
	{
		AGmagicIP_Global_bTables[3]=agfalse;
		AGmagicIP_Global_bTables[5]=agfalse;
		AGmagicIP_Global_bTables[6]=agfalse;
	}
#else	//#if AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif	//#if AGMAGIC_SUPPORT_ADO

	if(!IsTableNameValid(AGmagicIP_GlobalCurImageTable))
		throw _T("Fatal Error");
	if(!IsTableIndexValid(GetTableIndexFromFeature(AGmagicIP_ClobalFeatures)))
		throw _T("Fatal Error");
}

agint32 CAGmagicIPConfUtil::GetTableIndexFromName(agtchar TableName[])
{
	if(TableName==NULL)	return -1;
	agint32 i=0;
	for(i=0; i<AGmagicIP_Global_nTables; i++)
		if(_tcsicmp(TableName,AGmagicIP_Global_Tables[i])==0)	break;
	if(i==AGmagicIP_Global_nTables)	return -1;
	return i;
}
agint32 CAGmagicIPConfUtil::GetTableIndexFromFeature(agint32 feature)
{
	switch(feature)
	{
		case AGMAGICIP_UNKNOWN_FEATURE :
			return -1;
		case AGMAGICIP_256CLR_FEATURE :
			return 3;
		case AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE :
			return 4;
		case AGMAGICIP_MULTICLR_FEATURE :
			return 5;
		case AGMAGICIP_MULTIATT_FEATURE :
			return 6;
	}
	return -1;
}
agbool CAGmagicIPConfUtil::IsTableIndexValid(agint32 idx)
{
	if(idx<0 || idx >= AGmagicIP_Global_nTables)	return agfalse;
	return AGmagicIP_Global_bTables[idx];
}
agbool CAGmagicIPConfUtil::IsTableNameValid(agtchar TableName[])
{
	return IsTableIndexValid(GetTableIndexFromName(TableName));
}


/*******************************class CAGimageMicUtil*******************************/
#include "AGimage.h"
#ifdef WIN32
//Pal
//goi ham nay xong phai huy bang free
AGCLRQUAD* CAGimageMicUtil::CreateDemoMonoColorsPal()
{
	AGCLRQUAD* pImgEntries=(AGCLRQUAD*)malloc(2*sizeof(AGCLRQUAD));
	pImgEntries[  0].rgbReserved=  0; pImgEntries[  0].rgbRed=  0; pImgEntries[  0].rgbGreen=  0; pImgEntries[  0].rgbBlue=  0;
	pImgEntries[  1].rgbReserved=  0; pImgEntries[  1].rgbRed=255; pImgEntries[  1].rgbGreen=255; pImgEntries[  1].rgbBlue=255;
	return pImgEntries;
}
//goi ham nay xong phai huy bang free
AGCLRQUAD* CAGimageMicUtil::CreateDemo16ColorsPal()
{
	AGCLRQUAD* pImgEntries=(AGCLRQUAD*)malloc(16*sizeof(AGCLRQUAD));
	pImgEntries[  0].rgbReserved=  0; pImgEntries[  0].rgbRed=  0; pImgEntries[  0].rgbGreen=  0; pImgEntries[  0].rgbBlue=  0;
	pImgEntries[  1].rgbReserved=  0; pImgEntries[  1].rgbRed=128; pImgEntries[  1].rgbGreen=  0; pImgEntries[  1].rgbBlue=  0;
	pImgEntries[  2].rgbReserved=  0; pImgEntries[  2].rgbRed=  0; pImgEntries[  2].rgbGreen=128; pImgEntries[  2].rgbBlue=  0;
	pImgEntries[  3].rgbReserved=  0; pImgEntries[  3].rgbRed=128; pImgEntries[  3].rgbGreen=128; pImgEntries[  3].rgbBlue=  0;
	pImgEntries[  4].rgbReserved=  0; pImgEntries[  4].rgbRed=  0; pImgEntries[  4].rgbGreen=  0; pImgEntries[  4].rgbBlue=128;
	pImgEntries[  5].rgbReserved=  0; pImgEntries[  5].rgbRed=128; pImgEntries[  5].rgbGreen=  0; pImgEntries[  5].rgbBlue=128;
	pImgEntries[  6].rgbReserved=  0; pImgEntries[  6].rgbRed=  0; pImgEntries[  6].rgbGreen=128; pImgEntries[  6].rgbBlue=128;
	pImgEntries[  7].rgbReserved=  0; pImgEntries[  7].rgbRed=128; pImgEntries[  7].rgbGreen=128; pImgEntries[  7].rgbBlue=128;
	pImgEntries[  8].rgbReserved=  0; pImgEntries[  8].rgbRed=192; pImgEntries[  8].rgbGreen=192; pImgEntries[  8].rgbBlue=192;
	pImgEntries[  9].rgbReserved=  0; pImgEntries[  9].rgbRed=255; pImgEntries[  9].rgbGreen=  0; pImgEntries[  9].rgbBlue=  0;
	pImgEntries[ 10].rgbReserved=  0; pImgEntries[ 10].rgbRed=  0; pImgEntries[ 10].rgbGreen=255; pImgEntries[ 10].rgbBlue=  0;
	pImgEntries[ 11].rgbReserved=  0; pImgEntries[ 11].rgbRed=255; pImgEntries[ 11].rgbGreen=255; pImgEntries[ 11].rgbBlue=  0;
	pImgEntries[ 12].rgbReserved=  0; pImgEntries[ 12].rgbRed=  0; pImgEntries[ 12].rgbGreen=  0; pImgEntries[ 12].rgbBlue=255;
	pImgEntries[ 13].rgbReserved=  0; pImgEntries[ 13].rgbRed=255; pImgEntries[ 13].rgbGreen=  0; pImgEntries[ 13].rgbBlue=255;
	pImgEntries[ 14].rgbReserved=  0; pImgEntries[ 14].rgbRed=  0; pImgEntries[ 14].rgbGreen=255; pImgEntries[ 14].rgbBlue=255;
	pImgEntries[ 15].rgbReserved=  0; pImgEntries[ 15].rgbRed=255; pImgEntries[ 15].rgbGreen=255; pImgEntries[ 15].rgbBlue=255;
	return pImgEntries;
}
//goi ham nay xong phai huy bang free
AGCLRQUAD* CAGimageMicUtil::CreateDemo256ColorsPal()
{
	AGCLRQUAD* pImgEntries=(AGCLRQUAD*)malloc(256*sizeof(AGCLRQUAD));
	pImgEntries[  0].rgbReserved=  0; pImgEntries[  0].rgbRed=  0; pImgEntries[  0].rgbGreen=  0; pImgEntries[  0].rgbBlue=  0;
	pImgEntries[  1].rgbReserved=  0; pImgEntries[  1].rgbRed=  0; pImgEntries[  1].rgbGreen=  0; pImgEntries[  1].rgbBlue= 64;
	pImgEntries[  2].rgbReserved=  0; pImgEntries[  2].rgbRed=  0; pImgEntries[  2].rgbGreen=  0; pImgEntries[  2].rgbBlue=128;
	pImgEntries[  3].rgbReserved=  0; pImgEntries[  3].rgbRed=  0; pImgEntries[  3].rgbGreen=  0; pImgEntries[  3].rgbBlue=255;
	pImgEntries[  4].rgbReserved=  0; pImgEntries[  4].rgbRed=  0; pImgEntries[  4].rgbGreen= 32; pImgEntries[  4].rgbBlue=  0;
	pImgEntries[  5].rgbReserved=  0; pImgEntries[  5].rgbRed=  0; pImgEntries[  5].rgbGreen= 32; pImgEntries[  5].rgbBlue= 64;
	pImgEntries[  6].rgbReserved=  0; pImgEntries[  6].rgbRed=  0; pImgEntries[  6].rgbGreen= 32; pImgEntries[  6].rgbBlue=128;
	pImgEntries[  7].rgbReserved=  0; pImgEntries[  7].rgbRed=  0; pImgEntries[  7].rgbGreen= 32; pImgEntries[  7].rgbBlue=255;
	pImgEntries[  8].rgbReserved=  0; pImgEntries[  8].rgbRed=  0; pImgEntries[  8].rgbGreen= 64; pImgEntries[  8].rgbBlue=  0;
	pImgEntries[  9].rgbReserved=  0; pImgEntries[  9].rgbRed=  0; pImgEntries[  9].rgbGreen= 64; pImgEntries[  9].rgbBlue= 64;
	pImgEntries[ 10].rgbReserved=  0; pImgEntries[ 10].rgbRed=  0; pImgEntries[ 10].rgbGreen= 64; pImgEntries[ 10].rgbBlue=128;
	pImgEntries[ 11].rgbReserved=  0; pImgEntries[ 11].rgbRed=  0; pImgEntries[ 11].rgbGreen= 64; pImgEntries[ 11].rgbBlue=255;
	pImgEntries[ 12].rgbReserved=  0; pImgEntries[ 12].rgbRed=  0; pImgEntries[ 12].rgbGreen= 96; pImgEntries[ 12].rgbBlue=  0;
	pImgEntries[ 13].rgbReserved=  0; pImgEntries[ 13].rgbRed=  0; pImgEntries[ 13].rgbGreen= 96; pImgEntries[ 13].rgbBlue= 64;
	pImgEntries[ 14].rgbReserved=  0; pImgEntries[ 14].rgbRed=  0; pImgEntries[ 14].rgbGreen= 96; pImgEntries[ 14].rgbBlue=128;
	pImgEntries[ 15].rgbReserved=  0; pImgEntries[ 15].rgbRed=  0; pImgEntries[ 15].rgbGreen= 96; pImgEntries[ 15].rgbBlue=255;
	pImgEntries[ 16].rgbReserved=  0; pImgEntries[ 16].rgbRed=  0; pImgEntries[ 16].rgbGreen=128; pImgEntries[ 16].rgbBlue=  0;
	pImgEntries[ 17].rgbReserved=  0; pImgEntries[ 17].rgbRed=  0; pImgEntries[ 17].rgbGreen=128; pImgEntries[ 17].rgbBlue= 64;
	pImgEntries[ 18].rgbReserved=  0; pImgEntries[ 18].rgbRed=  0; pImgEntries[ 18].rgbGreen=128; pImgEntries[ 18].rgbBlue=128;
	pImgEntries[ 19].rgbReserved=  0; pImgEntries[ 19].rgbRed=  0; pImgEntries[ 19].rgbGreen=128; pImgEntries[ 19].rgbBlue=255;
	pImgEntries[ 20].rgbReserved=  0; pImgEntries[ 20].rgbRed=  0; pImgEntries[ 20].rgbGreen=160; pImgEntries[ 20].rgbBlue=  0;
	pImgEntries[ 21].rgbReserved=  0; pImgEntries[ 21].rgbRed=  0; pImgEntries[ 21].rgbGreen=160; pImgEntries[ 21].rgbBlue= 64;
	pImgEntries[ 22].rgbReserved=  0; pImgEntries[ 22].rgbRed=  0; pImgEntries[ 22].rgbGreen=160; pImgEntries[ 22].rgbBlue=128;
	pImgEntries[ 23].rgbReserved=  0; pImgEntries[ 23].rgbRed=  0; pImgEntries[ 23].rgbGreen=160; pImgEntries[ 23].rgbBlue=255;
	pImgEntries[ 24].rgbReserved=  0; pImgEntries[ 24].rgbRed=  0; pImgEntries[ 24].rgbGreen=192; pImgEntries[ 24].rgbBlue=  0;
	pImgEntries[ 25].rgbReserved=  0; pImgEntries[ 25].rgbRed=  0; pImgEntries[ 25].rgbGreen=192; pImgEntries[ 25].rgbBlue= 64;
	pImgEntries[ 26].rgbReserved=  0; pImgEntries[ 26].rgbRed=  0; pImgEntries[ 26].rgbGreen=192; pImgEntries[ 26].rgbBlue=128;
	pImgEntries[ 27].rgbReserved=  0; pImgEntries[ 27].rgbRed=  0; pImgEntries[ 27].rgbGreen=192; pImgEntries[ 27].rgbBlue=255;
	pImgEntries[ 28].rgbReserved=  0; pImgEntries[ 28].rgbRed=  0; pImgEntries[ 28].rgbGreen=255; pImgEntries[ 28].rgbBlue=  0;
	pImgEntries[ 29].rgbReserved=  0; pImgEntries[ 29].rgbRed=  0; pImgEntries[ 29].rgbGreen=255; pImgEntries[ 29].rgbBlue= 64;
	pImgEntries[ 30].rgbReserved=  0; pImgEntries[ 30].rgbRed=  0; pImgEntries[ 30].rgbGreen=255; pImgEntries[ 30].rgbBlue=128;
	pImgEntries[ 31].rgbReserved=  0; pImgEntries[ 31].rgbRed=  0; pImgEntries[ 31].rgbGreen=255; pImgEntries[ 31].rgbBlue=255;
	pImgEntries[ 32].rgbReserved=  0; pImgEntries[ 32].rgbRed= 32; pImgEntries[ 32].rgbGreen=  0; pImgEntries[ 32].rgbBlue=  0;
	pImgEntries[ 33].rgbReserved=  0; pImgEntries[ 33].rgbRed= 32; pImgEntries[ 33].rgbGreen=  0; pImgEntries[ 33].rgbBlue= 64;
	pImgEntries[ 34].rgbReserved=  0; pImgEntries[ 34].rgbRed= 32; pImgEntries[ 34].rgbGreen=  0; pImgEntries[ 34].rgbBlue=128;
	pImgEntries[ 35].rgbReserved=  0; pImgEntries[ 35].rgbRed= 32; pImgEntries[ 35].rgbGreen=  0; pImgEntries[ 35].rgbBlue=255;
	pImgEntries[ 36].rgbReserved=  0; pImgEntries[ 36].rgbRed= 32; pImgEntries[ 36].rgbGreen= 32; pImgEntries[ 36].rgbBlue=  0;
	pImgEntries[ 37].rgbReserved=  0; pImgEntries[ 37].rgbRed= 32; pImgEntries[ 37].rgbGreen= 32; pImgEntries[ 37].rgbBlue= 64;
	pImgEntries[ 38].rgbReserved=  0; pImgEntries[ 38].rgbRed= 32; pImgEntries[ 38].rgbGreen= 32; pImgEntries[ 38].rgbBlue=128;
	pImgEntries[ 39].rgbReserved=  0; pImgEntries[ 39].rgbRed= 32; pImgEntries[ 39].rgbGreen= 32; pImgEntries[ 39].rgbBlue=255;
	pImgEntries[ 40].rgbReserved=  0; pImgEntries[ 40].rgbRed= 32; pImgEntries[ 40].rgbGreen= 64; pImgEntries[ 40].rgbBlue=  0;
	pImgEntries[ 41].rgbReserved=  0; pImgEntries[ 41].rgbRed= 32; pImgEntries[ 41].rgbGreen= 64; pImgEntries[ 41].rgbBlue= 64;
	pImgEntries[ 42].rgbReserved=  0; pImgEntries[ 42].rgbRed= 32; pImgEntries[ 42].rgbGreen= 64; pImgEntries[ 42].rgbBlue=128;
	pImgEntries[ 43].rgbReserved=  0; pImgEntries[ 43].rgbRed= 32; pImgEntries[ 43].rgbGreen= 64; pImgEntries[ 43].rgbBlue=255;
	pImgEntries[ 44].rgbReserved=  0; pImgEntries[ 44].rgbRed= 32; pImgEntries[ 44].rgbGreen= 96; pImgEntries[ 44].rgbBlue=  0;
	pImgEntries[ 45].rgbReserved=  0; pImgEntries[ 45].rgbRed= 32; pImgEntries[ 45].rgbGreen= 96; pImgEntries[ 45].rgbBlue= 64;
	pImgEntries[ 46].rgbReserved=  0; pImgEntries[ 46].rgbRed= 32; pImgEntries[ 46].rgbGreen= 96; pImgEntries[ 46].rgbBlue=128;
	pImgEntries[ 47].rgbReserved=  0; pImgEntries[ 47].rgbRed= 32; pImgEntries[ 47].rgbGreen= 96; pImgEntries[ 47].rgbBlue=255;
	pImgEntries[ 48].rgbReserved=  0; pImgEntries[ 48].rgbRed= 32; pImgEntries[ 48].rgbGreen=128; pImgEntries[ 48].rgbBlue=  0;
	pImgEntries[ 49].rgbReserved=  0; pImgEntries[ 49].rgbRed= 32; pImgEntries[ 49].rgbGreen=128; pImgEntries[ 49].rgbBlue= 64;
	pImgEntries[ 50].rgbReserved=  0; pImgEntries[ 50].rgbRed= 32; pImgEntries[ 50].rgbGreen=128; pImgEntries[ 50].rgbBlue=128;
	pImgEntries[ 51].rgbReserved=  0; pImgEntries[ 51].rgbRed= 32; pImgEntries[ 51].rgbGreen=128; pImgEntries[ 51].rgbBlue=255;
	pImgEntries[ 52].rgbReserved=  0; pImgEntries[ 52].rgbRed= 32; pImgEntries[ 52].rgbGreen=160; pImgEntries[ 52].rgbBlue=  0;
	pImgEntries[ 53].rgbReserved=  0; pImgEntries[ 53].rgbRed= 32; pImgEntries[ 53].rgbGreen=160; pImgEntries[ 53].rgbBlue= 64;
	pImgEntries[ 54].rgbReserved=  0; pImgEntries[ 54].rgbRed= 32; pImgEntries[ 54].rgbGreen=160; pImgEntries[ 54].rgbBlue=128;
	pImgEntries[ 55].rgbReserved=  0; pImgEntries[ 55].rgbRed= 32; pImgEntries[ 55].rgbGreen=160; pImgEntries[ 55].rgbBlue=255;
	pImgEntries[ 56].rgbReserved=  0; pImgEntries[ 56].rgbRed= 32; pImgEntries[ 56].rgbGreen=192; pImgEntries[ 56].rgbBlue=  0;
	pImgEntries[ 57].rgbReserved=  0; pImgEntries[ 57].rgbRed= 32; pImgEntries[ 57].rgbGreen=192; pImgEntries[ 57].rgbBlue= 64;
	pImgEntries[ 58].rgbReserved=  0; pImgEntries[ 58].rgbRed= 32; pImgEntries[ 58].rgbGreen=192; pImgEntries[ 58].rgbBlue=128;
	pImgEntries[ 59].rgbReserved=  0; pImgEntries[ 59].rgbRed= 32; pImgEntries[ 59].rgbGreen=192; pImgEntries[ 59].rgbBlue=255;
	pImgEntries[ 60].rgbReserved=  0; pImgEntries[ 60].rgbRed= 32; pImgEntries[ 60].rgbGreen=255; pImgEntries[ 60].rgbBlue=  0;
	pImgEntries[ 61].rgbReserved=  0; pImgEntries[ 61].rgbRed= 32; pImgEntries[ 61].rgbGreen=255; pImgEntries[ 61].rgbBlue= 64;
	pImgEntries[ 62].rgbReserved=  0; pImgEntries[ 62].rgbRed= 32; pImgEntries[ 62].rgbGreen=255; pImgEntries[ 62].rgbBlue=128;
	pImgEntries[ 63].rgbReserved=  0; pImgEntries[ 63].rgbRed= 32; pImgEntries[ 63].rgbGreen=255; pImgEntries[ 63].rgbBlue=255;
	pImgEntries[ 64].rgbReserved=  0; pImgEntries[ 64].rgbRed= 64; pImgEntries[ 64].rgbGreen=  0; pImgEntries[ 64].rgbBlue=  0;
	pImgEntries[ 65].rgbReserved=  0; pImgEntries[ 65].rgbRed= 64; pImgEntries[ 65].rgbGreen=  0; pImgEntries[ 65].rgbBlue= 64;
	pImgEntries[ 66].rgbReserved=  0; pImgEntries[ 66].rgbRed= 64; pImgEntries[ 66].rgbGreen=  0; pImgEntries[ 66].rgbBlue=128;
	pImgEntries[ 67].rgbReserved=  0; pImgEntries[ 67].rgbRed= 64; pImgEntries[ 67].rgbGreen=  0; pImgEntries[ 67].rgbBlue=255;
	pImgEntries[ 68].rgbReserved=  0; pImgEntries[ 68].rgbRed= 64; pImgEntries[ 68].rgbGreen= 32; pImgEntries[ 68].rgbBlue=  0;
	pImgEntries[ 69].rgbReserved=  0; pImgEntries[ 69].rgbRed= 64; pImgEntries[ 69].rgbGreen= 32; pImgEntries[ 69].rgbBlue= 64;
	pImgEntries[ 70].rgbReserved=  0; pImgEntries[ 70].rgbRed= 64; pImgEntries[ 70].rgbGreen= 32; pImgEntries[ 70].rgbBlue=128;
	pImgEntries[ 71].rgbReserved=  0; pImgEntries[ 71].rgbRed= 64; pImgEntries[ 71].rgbGreen= 32; pImgEntries[ 71].rgbBlue=255;
	pImgEntries[ 72].rgbReserved=  0; pImgEntries[ 72].rgbRed= 64; pImgEntries[ 72].rgbGreen= 64; pImgEntries[ 72].rgbBlue=  0;
	pImgEntries[ 73].rgbReserved=  0; pImgEntries[ 73].rgbRed= 64; pImgEntries[ 73].rgbGreen= 64; pImgEntries[ 73].rgbBlue= 64;
	pImgEntries[ 74].rgbReserved=  0; pImgEntries[ 74].rgbRed= 64; pImgEntries[ 74].rgbGreen= 64; pImgEntries[ 74].rgbBlue=128;
	pImgEntries[ 75].rgbReserved=  0; pImgEntries[ 75].rgbRed= 64; pImgEntries[ 75].rgbGreen= 64; pImgEntries[ 75].rgbBlue=255;
	pImgEntries[ 76].rgbReserved=  0; pImgEntries[ 76].rgbRed= 64; pImgEntries[ 76].rgbGreen= 96; pImgEntries[ 76].rgbBlue=  0;
	pImgEntries[ 77].rgbReserved=  0; pImgEntries[ 77].rgbRed= 64; pImgEntries[ 77].rgbGreen= 96; pImgEntries[ 77].rgbBlue= 64;
	pImgEntries[ 78].rgbReserved=  0; pImgEntries[ 78].rgbRed= 64; pImgEntries[ 78].rgbGreen= 96; pImgEntries[ 78].rgbBlue=128;
	pImgEntries[ 79].rgbReserved=  0; pImgEntries[ 79].rgbRed= 64; pImgEntries[ 79].rgbGreen= 96; pImgEntries[ 79].rgbBlue=255;
	pImgEntries[ 80].rgbReserved=  0; pImgEntries[ 80].rgbRed= 64; pImgEntries[ 80].rgbGreen=128; pImgEntries[ 80].rgbBlue=  0;
	pImgEntries[ 81].rgbReserved=  0; pImgEntries[ 81].rgbRed= 64; pImgEntries[ 81].rgbGreen=128; pImgEntries[ 81].rgbBlue= 64;
	pImgEntries[ 82].rgbReserved=  0; pImgEntries[ 82].rgbRed= 64; pImgEntries[ 82].rgbGreen=128; pImgEntries[ 82].rgbBlue=128;
	pImgEntries[ 83].rgbReserved=  0; pImgEntries[ 83].rgbRed= 64; pImgEntries[ 83].rgbGreen=128; pImgEntries[ 83].rgbBlue=255;
	pImgEntries[ 84].rgbReserved=  0; pImgEntries[ 84].rgbRed= 64; pImgEntries[ 84].rgbGreen=160; pImgEntries[ 84].rgbBlue=  0;
	pImgEntries[ 85].rgbReserved=  0; pImgEntries[ 85].rgbRed= 64; pImgEntries[ 85].rgbGreen=160; pImgEntries[ 85].rgbBlue= 64;
	pImgEntries[ 86].rgbReserved=  0; pImgEntries[ 86].rgbRed= 64; pImgEntries[ 86].rgbGreen=160; pImgEntries[ 86].rgbBlue=128;
	pImgEntries[ 87].rgbReserved=  0; pImgEntries[ 87].rgbRed= 64; pImgEntries[ 87].rgbGreen=160; pImgEntries[ 87].rgbBlue=255;
	pImgEntries[ 88].rgbReserved=  0; pImgEntries[ 88].rgbRed= 64; pImgEntries[ 88].rgbGreen=192; pImgEntries[ 88].rgbBlue=  0;
	pImgEntries[ 89].rgbReserved=  0; pImgEntries[ 89].rgbRed= 64; pImgEntries[ 89].rgbGreen=192; pImgEntries[ 89].rgbBlue= 64;
	pImgEntries[ 90].rgbReserved=  0; pImgEntries[ 90].rgbRed= 64; pImgEntries[ 90].rgbGreen=192; pImgEntries[ 90].rgbBlue=128;
	pImgEntries[ 91].rgbReserved=  0; pImgEntries[ 91].rgbRed= 64; pImgEntries[ 91].rgbGreen=192; pImgEntries[ 91].rgbBlue=255;
	pImgEntries[ 92].rgbReserved=  0; pImgEntries[ 92].rgbRed= 64; pImgEntries[ 92].rgbGreen=255; pImgEntries[ 92].rgbBlue=  0;
	pImgEntries[ 93].rgbReserved=  0; pImgEntries[ 93].rgbRed= 64; pImgEntries[ 93].rgbGreen=255; pImgEntries[ 93].rgbBlue= 64;
	pImgEntries[ 94].rgbReserved=  0; pImgEntries[ 94].rgbRed= 64; pImgEntries[ 94].rgbGreen=255; pImgEntries[ 94].rgbBlue=128;
	pImgEntries[ 95].rgbReserved=  0; pImgEntries[ 95].rgbRed= 64; pImgEntries[ 95].rgbGreen=255; pImgEntries[ 95].rgbBlue=255;
	pImgEntries[ 96].rgbReserved=  0; pImgEntries[ 96].rgbRed= 96; pImgEntries[ 96].rgbGreen=  0; pImgEntries[ 96].rgbBlue=  0;
	pImgEntries[ 97].rgbReserved=  0; pImgEntries[ 97].rgbRed= 96; pImgEntries[ 97].rgbGreen=  0; pImgEntries[ 97].rgbBlue= 64;
	pImgEntries[ 98].rgbReserved=  0; pImgEntries[ 98].rgbRed= 96; pImgEntries[ 98].rgbGreen=  0; pImgEntries[ 98].rgbBlue=128;
	pImgEntries[ 99].rgbReserved=  0; pImgEntries[ 99].rgbRed= 96; pImgEntries[ 99].rgbGreen=  0; pImgEntries[ 99].rgbBlue=255;
	pImgEntries[100].rgbReserved=  0; pImgEntries[100].rgbRed= 96; pImgEntries[100].rgbGreen= 32; pImgEntries[100].rgbBlue=  0;
	pImgEntries[101].rgbReserved=  0; pImgEntries[101].rgbRed= 96; pImgEntries[101].rgbGreen= 32; pImgEntries[101].rgbBlue= 64;
	pImgEntries[102].rgbReserved=  0; pImgEntries[102].rgbRed= 96; pImgEntries[102].rgbGreen= 32; pImgEntries[102].rgbBlue=128;
	pImgEntries[103].rgbReserved=  0; pImgEntries[103].rgbRed= 96; pImgEntries[103].rgbGreen= 32; pImgEntries[103].rgbBlue=255;
	pImgEntries[104].rgbReserved=  0; pImgEntries[104].rgbRed= 96; pImgEntries[104].rgbGreen= 64; pImgEntries[104].rgbBlue=  0;
	pImgEntries[105].rgbReserved=  0; pImgEntries[105].rgbRed= 96; pImgEntries[105].rgbGreen= 64; pImgEntries[105].rgbBlue= 64;
	pImgEntries[106].rgbReserved=  0; pImgEntries[106].rgbRed= 96; pImgEntries[106].rgbGreen= 64; pImgEntries[106].rgbBlue=128;
	pImgEntries[107].rgbReserved=  0; pImgEntries[107].rgbRed= 96; pImgEntries[107].rgbGreen= 64; pImgEntries[107].rgbBlue=255;
	pImgEntries[108].rgbReserved=  0; pImgEntries[108].rgbRed= 96; pImgEntries[108].rgbGreen= 96; pImgEntries[108].rgbBlue=  0;
	pImgEntries[109].rgbReserved=  0; pImgEntries[109].rgbRed= 96; pImgEntries[109].rgbGreen= 96; pImgEntries[109].rgbBlue= 64;
	pImgEntries[110].rgbReserved=  0; pImgEntries[110].rgbRed= 96; pImgEntries[110].rgbGreen= 96; pImgEntries[110].rgbBlue=128;
	pImgEntries[111].rgbReserved=  0; pImgEntries[111].rgbRed= 96; pImgEntries[111].rgbGreen= 96; pImgEntries[111].rgbBlue=255;
	pImgEntries[112].rgbReserved=  0; pImgEntries[112].rgbRed= 96; pImgEntries[112].rgbGreen=128; pImgEntries[112].rgbBlue=  0;
	pImgEntries[113].rgbReserved=  0; pImgEntries[113].rgbRed= 96; pImgEntries[113].rgbGreen=128; pImgEntries[113].rgbBlue= 64;
	pImgEntries[114].rgbReserved=  0; pImgEntries[114].rgbRed= 96; pImgEntries[114].rgbGreen=128; pImgEntries[114].rgbBlue=128;
	pImgEntries[115].rgbReserved=  0; pImgEntries[115].rgbRed= 96; pImgEntries[115].rgbGreen=128; pImgEntries[115].rgbBlue=255;
	pImgEntries[116].rgbReserved=  0; pImgEntries[116].rgbRed= 96; pImgEntries[116].rgbGreen=160; pImgEntries[116].rgbBlue=  0;
	pImgEntries[117].rgbReserved=  0; pImgEntries[117].rgbRed= 96; pImgEntries[117].rgbGreen=160; pImgEntries[117].rgbBlue= 64;
	pImgEntries[118].rgbReserved=  0; pImgEntries[118].rgbRed= 96; pImgEntries[118].rgbGreen=160; pImgEntries[118].rgbBlue=128;
	pImgEntries[119].rgbReserved=  0; pImgEntries[119].rgbRed= 96; pImgEntries[119].rgbGreen=160; pImgEntries[119].rgbBlue=255;
	pImgEntries[120].rgbReserved=  0; pImgEntries[120].rgbRed= 96; pImgEntries[120].rgbGreen=192; pImgEntries[120].rgbBlue=  0;
	pImgEntries[121].rgbReserved=  0; pImgEntries[121].rgbRed= 96; pImgEntries[121].rgbGreen=192; pImgEntries[121].rgbBlue= 64;
	pImgEntries[122].rgbReserved=  0; pImgEntries[122].rgbRed= 96; pImgEntries[122].rgbGreen=192; pImgEntries[122].rgbBlue=128;
	pImgEntries[123].rgbReserved=  0; pImgEntries[123].rgbRed= 96; pImgEntries[123].rgbGreen=192; pImgEntries[123].rgbBlue=255;
	pImgEntries[124].rgbReserved=  0; pImgEntries[124].rgbRed= 96; pImgEntries[124].rgbGreen=255; pImgEntries[124].rgbBlue=  0;
	pImgEntries[125].rgbReserved=  0; pImgEntries[125].rgbRed= 96; pImgEntries[125].rgbGreen=255; pImgEntries[125].rgbBlue= 64;
	pImgEntries[126].rgbReserved=  0; pImgEntries[126].rgbRed= 96; pImgEntries[126].rgbGreen=255; pImgEntries[126].rgbBlue=128;
	pImgEntries[127].rgbReserved=  0; pImgEntries[127].rgbRed= 96; pImgEntries[127].rgbGreen=255; pImgEntries[127].rgbBlue=255;
	pImgEntries[128].rgbReserved=  0; pImgEntries[128].rgbRed=128; pImgEntries[128].rgbGreen=  0; pImgEntries[128].rgbBlue=  0;
	pImgEntries[129].rgbReserved=  0; pImgEntries[129].rgbRed=128; pImgEntries[129].rgbGreen=  0; pImgEntries[129].rgbBlue= 64;
	pImgEntries[130].rgbReserved=  0; pImgEntries[130].rgbRed=128; pImgEntries[130].rgbGreen=  0; pImgEntries[130].rgbBlue=128;
	pImgEntries[131].rgbReserved=  0; pImgEntries[131].rgbRed=128; pImgEntries[131].rgbGreen=  0; pImgEntries[131].rgbBlue=255;
	pImgEntries[132].rgbReserved=  0; pImgEntries[132].rgbRed=128; pImgEntries[132].rgbGreen= 32; pImgEntries[132].rgbBlue=  0;
	pImgEntries[133].rgbReserved=  0; pImgEntries[133].rgbRed=128; pImgEntries[133].rgbGreen= 32; pImgEntries[133].rgbBlue= 64;
	pImgEntries[134].rgbReserved=  0; pImgEntries[134].rgbRed=128; pImgEntries[134].rgbGreen= 32; pImgEntries[134].rgbBlue=128;
	pImgEntries[135].rgbReserved=  0; pImgEntries[135].rgbRed=128; pImgEntries[135].rgbGreen= 32; pImgEntries[135].rgbBlue=255;
	pImgEntries[136].rgbReserved=  0; pImgEntries[136].rgbRed=128; pImgEntries[136].rgbGreen= 64; pImgEntries[136].rgbBlue=  0;
	pImgEntries[137].rgbReserved=  0; pImgEntries[137].rgbRed=128; pImgEntries[137].rgbGreen= 64; pImgEntries[137].rgbBlue= 64;
	pImgEntries[138].rgbReserved=  0; pImgEntries[138].rgbRed=128; pImgEntries[138].rgbGreen= 64; pImgEntries[138].rgbBlue=128;
	pImgEntries[139].rgbReserved=  0; pImgEntries[139].rgbRed=128; pImgEntries[139].rgbGreen= 64; pImgEntries[139].rgbBlue=255;
	pImgEntries[140].rgbReserved=  0; pImgEntries[140].rgbRed=128; pImgEntries[140].rgbGreen= 96; pImgEntries[140].rgbBlue=  0;
	pImgEntries[141].rgbReserved=  0; pImgEntries[141].rgbRed=128; pImgEntries[141].rgbGreen= 96; pImgEntries[141].rgbBlue= 64;
	pImgEntries[142].rgbReserved=  0; pImgEntries[142].rgbRed=128; pImgEntries[142].rgbGreen= 96; pImgEntries[142].rgbBlue=128;
	pImgEntries[143].rgbReserved=  0; pImgEntries[143].rgbRed=128; pImgEntries[143].rgbGreen= 96; pImgEntries[143].rgbBlue=255;
	pImgEntries[144].rgbReserved=  0; pImgEntries[144].rgbRed=128; pImgEntries[144].rgbGreen=128; pImgEntries[144].rgbBlue=  0;
	pImgEntries[145].rgbReserved=  0; pImgEntries[145].rgbRed=128; pImgEntries[145].rgbGreen=128; pImgEntries[145].rgbBlue= 64;
	pImgEntries[146].rgbReserved=  0; pImgEntries[146].rgbRed=128; pImgEntries[146].rgbGreen=128; pImgEntries[146].rgbBlue=128;
	pImgEntries[147].rgbReserved=  0; pImgEntries[147].rgbRed=128; pImgEntries[147].rgbGreen=128; pImgEntries[147].rgbBlue=255;
	pImgEntries[148].rgbReserved=  0; pImgEntries[148].rgbRed=128; pImgEntries[148].rgbGreen=160; pImgEntries[148].rgbBlue=  0;
	pImgEntries[149].rgbReserved=  0; pImgEntries[149].rgbRed=128; pImgEntries[149].rgbGreen=160; pImgEntries[149].rgbBlue= 64;
	pImgEntries[150].rgbReserved=  0; pImgEntries[150].rgbRed=128; pImgEntries[150].rgbGreen=160; pImgEntries[150].rgbBlue=128;
	pImgEntries[151].rgbReserved=  0; pImgEntries[151].rgbRed=128; pImgEntries[151].rgbGreen=160; pImgEntries[151].rgbBlue=255;
	pImgEntries[152].rgbReserved=  0; pImgEntries[152].rgbRed=128; pImgEntries[152].rgbGreen=192; pImgEntries[152].rgbBlue=  0;
	pImgEntries[153].rgbReserved=  0; pImgEntries[153].rgbRed=128; pImgEntries[153].rgbGreen=192; pImgEntries[153].rgbBlue= 64;
	pImgEntries[154].rgbReserved=  0; pImgEntries[154].rgbRed=128; pImgEntries[154].rgbGreen=192; pImgEntries[154].rgbBlue=128;
	pImgEntries[155].rgbReserved=  0; pImgEntries[155].rgbRed=128; pImgEntries[155].rgbGreen=192; pImgEntries[155].rgbBlue=255;
	pImgEntries[156].rgbReserved=  0; pImgEntries[156].rgbRed=128; pImgEntries[156].rgbGreen=255; pImgEntries[156].rgbBlue=  0;
	pImgEntries[157].rgbReserved=  0; pImgEntries[157].rgbRed=128; pImgEntries[157].rgbGreen=255; pImgEntries[157].rgbBlue= 64;
	pImgEntries[158].rgbReserved=  0; pImgEntries[158].rgbRed=128; pImgEntries[158].rgbGreen=255; pImgEntries[158].rgbBlue=128;
	pImgEntries[159].rgbReserved=  0; pImgEntries[159].rgbRed=128; pImgEntries[159].rgbGreen=255; pImgEntries[159].rgbBlue=255;
	pImgEntries[160].rgbReserved=  0; pImgEntries[160].rgbRed=160; pImgEntries[160].rgbGreen=  0; pImgEntries[160].rgbBlue=  0;
	pImgEntries[161].rgbReserved=  0; pImgEntries[161].rgbRed=160; pImgEntries[161].rgbGreen=  0; pImgEntries[161].rgbBlue= 64;
	pImgEntries[162].rgbReserved=  0; pImgEntries[162].rgbRed=160; pImgEntries[162].rgbGreen=  0; pImgEntries[162].rgbBlue=128;
	pImgEntries[163].rgbReserved=  0; pImgEntries[163].rgbRed=160; pImgEntries[163].rgbGreen=  0; pImgEntries[163].rgbBlue=255;
	pImgEntries[164].rgbReserved=  0; pImgEntries[164].rgbRed=160; pImgEntries[164].rgbGreen= 32; pImgEntries[164].rgbBlue=  0;
	pImgEntries[165].rgbReserved=  0; pImgEntries[165].rgbRed=160; pImgEntries[165].rgbGreen= 32; pImgEntries[165].rgbBlue= 64;
	pImgEntries[166].rgbReserved=  0; pImgEntries[166].rgbRed=160; pImgEntries[166].rgbGreen= 32; pImgEntries[166].rgbBlue=128;
	pImgEntries[167].rgbReserved=  0; pImgEntries[167].rgbRed=160; pImgEntries[167].rgbGreen= 32; pImgEntries[167].rgbBlue=255;
	pImgEntries[168].rgbReserved=  0; pImgEntries[168].rgbRed=160; pImgEntries[168].rgbGreen= 64; pImgEntries[168].rgbBlue=  0;
	pImgEntries[169].rgbReserved=  0; pImgEntries[169].rgbRed=160; pImgEntries[169].rgbGreen= 64; pImgEntries[169].rgbBlue= 64;
	pImgEntries[170].rgbReserved=  0; pImgEntries[170].rgbRed=160; pImgEntries[170].rgbGreen= 64; pImgEntries[170].rgbBlue=128;
	pImgEntries[171].rgbReserved=  0; pImgEntries[171].rgbRed=160; pImgEntries[171].rgbGreen= 64; pImgEntries[171].rgbBlue=255;
	pImgEntries[172].rgbReserved=  0; pImgEntries[172].rgbRed=160; pImgEntries[172].rgbGreen= 96; pImgEntries[172].rgbBlue=  0;
	pImgEntries[173].rgbReserved=  0; pImgEntries[173].rgbRed=160; pImgEntries[173].rgbGreen= 96; pImgEntries[173].rgbBlue= 64;
	pImgEntries[174].rgbReserved=  0; pImgEntries[174].rgbRed=160; pImgEntries[174].rgbGreen= 96; pImgEntries[174].rgbBlue=128;
	pImgEntries[175].rgbReserved=  0; pImgEntries[175].rgbRed=160; pImgEntries[175].rgbGreen= 96; pImgEntries[175].rgbBlue=255;
	pImgEntries[176].rgbReserved=  0; pImgEntries[176].rgbRed=160; pImgEntries[176].rgbGreen=128; pImgEntries[176].rgbBlue=  0;
	pImgEntries[177].rgbReserved=  0; pImgEntries[177].rgbRed=160; pImgEntries[177].rgbGreen=128; pImgEntries[177].rgbBlue= 64;
	pImgEntries[178].rgbReserved=  0; pImgEntries[178].rgbRed=160; pImgEntries[178].rgbGreen=128; pImgEntries[178].rgbBlue=128;
	pImgEntries[179].rgbReserved=  0; pImgEntries[179].rgbRed=160; pImgEntries[179].rgbGreen=128; pImgEntries[179].rgbBlue=255;
	pImgEntries[180].rgbReserved=  0; pImgEntries[180].rgbRed=160; pImgEntries[180].rgbGreen=160; pImgEntries[180].rgbBlue=  0;
	pImgEntries[181].rgbReserved=  0; pImgEntries[181].rgbRed=160; pImgEntries[181].rgbGreen=160; pImgEntries[181].rgbBlue= 64;
	pImgEntries[182].rgbReserved=  0; pImgEntries[182].rgbRed=160; pImgEntries[182].rgbGreen=160; pImgEntries[182].rgbBlue=128;
	pImgEntries[183].rgbReserved=  0; pImgEntries[183].rgbRed=160; pImgEntries[183].rgbGreen=160; pImgEntries[183].rgbBlue=255;
	pImgEntries[184].rgbReserved=  0; pImgEntries[184].rgbRed=160; pImgEntries[184].rgbGreen=192; pImgEntries[184].rgbBlue=  0;
	pImgEntries[185].rgbReserved=  0; pImgEntries[185].rgbRed=160; pImgEntries[185].rgbGreen=192; pImgEntries[185].rgbBlue= 64;
	pImgEntries[186].rgbReserved=  0; pImgEntries[186].rgbRed=160; pImgEntries[186].rgbGreen=192; pImgEntries[186].rgbBlue=128;
	pImgEntries[187].rgbReserved=  0; pImgEntries[187].rgbRed=160; pImgEntries[187].rgbGreen=192; pImgEntries[187].rgbBlue=255;
	pImgEntries[188].rgbReserved=  0; pImgEntries[188].rgbRed=160; pImgEntries[188].rgbGreen=255; pImgEntries[188].rgbBlue=  0;
	pImgEntries[189].rgbReserved=  0; pImgEntries[189].rgbRed=160; pImgEntries[189].rgbGreen=255; pImgEntries[189].rgbBlue= 64;
	pImgEntries[190].rgbReserved=  0; pImgEntries[190].rgbRed=160; pImgEntries[190].rgbGreen=255; pImgEntries[190].rgbBlue=128;
	pImgEntries[191].rgbReserved=  0; pImgEntries[191].rgbRed=160; pImgEntries[191].rgbGreen=255; pImgEntries[191].rgbBlue=255;
	pImgEntries[192].rgbReserved=  0; pImgEntries[192].rgbRed=192; pImgEntries[192].rgbGreen=  0; pImgEntries[192].rgbBlue=  0;
	pImgEntries[193].rgbReserved=  0; pImgEntries[193].rgbRed=192; pImgEntries[193].rgbGreen=  0; pImgEntries[193].rgbBlue= 64;
	pImgEntries[194].rgbReserved=  0; pImgEntries[194].rgbRed=192; pImgEntries[194].rgbGreen=  0; pImgEntries[194].rgbBlue=128;
	pImgEntries[195].rgbReserved=  0; pImgEntries[195].rgbRed=192; pImgEntries[195].rgbGreen=  0; pImgEntries[195].rgbBlue=255;
	pImgEntries[196].rgbReserved=  0; pImgEntries[196].rgbRed=192; pImgEntries[196].rgbGreen= 32; pImgEntries[196].rgbBlue=  0;
	pImgEntries[197].rgbReserved=  0; pImgEntries[197].rgbRed=192; pImgEntries[197].rgbGreen= 32; pImgEntries[197].rgbBlue= 64;
	pImgEntries[198].rgbReserved=  0; pImgEntries[198].rgbRed=192; pImgEntries[198].rgbGreen= 32; pImgEntries[198].rgbBlue=128;
	pImgEntries[199].rgbReserved=  0; pImgEntries[199].rgbRed=192; pImgEntries[199].rgbGreen= 32; pImgEntries[199].rgbBlue=255;
	pImgEntries[200].rgbReserved=  0; pImgEntries[200].rgbRed=192; pImgEntries[200].rgbGreen= 64; pImgEntries[200].rgbBlue=  0;
	pImgEntries[201].rgbReserved=  0; pImgEntries[201].rgbRed=192; pImgEntries[201].rgbGreen= 64; pImgEntries[201].rgbBlue= 64;
	pImgEntries[202].rgbReserved=  0; pImgEntries[202].rgbRed=192; pImgEntries[202].rgbGreen= 64; pImgEntries[202].rgbBlue=128;
	pImgEntries[203].rgbReserved=  0; pImgEntries[203].rgbRed=192; pImgEntries[203].rgbGreen= 64; pImgEntries[203].rgbBlue=255;
	pImgEntries[204].rgbReserved=  0; pImgEntries[204].rgbRed=192; pImgEntries[204].rgbGreen= 96; pImgEntries[204].rgbBlue=  0;
	pImgEntries[205].rgbReserved=  0; pImgEntries[205].rgbRed=192; pImgEntries[205].rgbGreen= 96; pImgEntries[205].rgbBlue= 64;
	pImgEntries[206].rgbReserved=  0; pImgEntries[206].rgbRed=192; pImgEntries[206].rgbGreen= 96; pImgEntries[206].rgbBlue=128;
	pImgEntries[207].rgbReserved=  0; pImgEntries[207].rgbRed=192; pImgEntries[207].rgbGreen= 96; pImgEntries[207].rgbBlue=255;
	pImgEntries[208].rgbReserved=  0; pImgEntries[208].rgbRed=192; pImgEntries[208].rgbGreen=128; pImgEntries[208].rgbBlue=  0;
	pImgEntries[209].rgbReserved=  0; pImgEntries[209].rgbRed=192; pImgEntries[209].rgbGreen=128; pImgEntries[209].rgbBlue= 64;
	pImgEntries[210].rgbReserved=  0; pImgEntries[210].rgbRed=192; pImgEntries[210].rgbGreen=128; pImgEntries[210].rgbBlue=128;
	pImgEntries[211].rgbReserved=  0; pImgEntries[211].rgbRed=192; pImgEntries[211].rgbGreen=128; pImgEntries[211].rgbBlue=255;
	pImgEntries[212].rgbReserved=  0; pImgEntries[212].rgbRed=192; pImgEntries[212].rgbGreen=160; pImgEntries[212].rgbBlue=  0;
	pImgEntries[213].rgbReserved=  0; pImgEntries[213].rgbRed=192; pImgEntries[213].rgbGreen=160; pImgEntries[213].rgbBlue= 64;
	pImgEntries[214].rgbReserved=  0; pImgEntries[214].rgbRed=192; pImgEntries[214].rgbGreen=160; pImgEntries[214].rgbBlue=128;
	pImgEntries[215].rgbReserved=  0; pImgEntries[215].rgbRed=192; pImgEntries[215].rgbGreen=160; pImgEntries[215].rgbBlue=255;
	pImgEntries[216].rgbReserved=  0; pImgEntries[216].rgbRed=192; pImgEntries[216].rgbGreen=192; pImgEntries[216].rgbBlue=  0;
	pImgEntries[217].rgbReserved=  0; pImgEntries[217].rgbRed=192; pImgEntries[217].rgbGreen=192; pImgEntries[217].rgbBlue= 64;
	pImgEntries[218].rgbReserved=  0; pImgEntries[218].rgbRed=192; pImgEntries[218].rgbGreen=192; pImgEntries[218].rgbBlue=128;
	pImgEntries[219].rgbReserved=  0; pImgEntries[219].rgbRed=192; pImgEntries[219].rgbGreen=192; pImgEntries[219].rgbBlue=255;
	pImgEntries[220].rgbReserved=  0; pImgEntries[220].rgbRed=192; pImgEntries[220].rgbGreen=255; pImgEntries[220].rgbBlue=  0;
	pImgEntries[221].rgbReserved=  0; pImgEntries[221].rgbRed=192; pImgEntries[221].rgbGreen=255; pImgEntries[221].rgbBlue= 64;
	pImgEntries[222].rgbReserved=  0; pImgEntries[222].rgbRed=192; pImgEntries[222].rgbGreen=255; pImgEntries[222].rgbBlue=128;
	pImgEntries[223].rgbReserved=  0; pImgEntries[223].rgbRed=192; pImgEntries[223].rgbGreen=255; pImgEntries[223].rgbBlue=255;
	pImgEntries[224].rgbReserved=  0; pImgEntries[224].rgbRed=255; pImgEntries[224].rgbGreen=  0; pImgEntries[224].rgbBlue=  0;
	pImgEntries[225].rgbReserved=  0; pImgEntries[225].rgbRed=255; pImgEntries[225].rgbGreen=  0; pImgEntries[225].rgbBlue= 64;
	pImgEntries[226].rgbReserved=  0; pImgEntries[226].rgbRed=255; pImgEntries[226].rgbGreen=  0; pImgEntries[226].rgbBlue=128;
	pImgEntries[227].rgbReserved=  0; pImgEntries[227].rgbRed=255; pImgEntries[227].rgbGreen=  0; pImgEntries[227].rgbBlue=255;
	pImgEntries[228].rgbReserved=  0; pImgEntries[228].rgbRed=255; pImgEntries[228].rgbGreen= 32; pImgEntries[228].rgbBlue=  0;
	pImgEntries[229].rgbReserved=  0; pImgEntries[229].rgbRed=255; pImgEntries[229].rgbGreen= 32; pImgEntries[229].rgbBlue= 64;
	pImgEntries[230].rgbReserved=  0; pImgEntries[230].rgbRed=255; pImgEntries[230].rgbGreen= 32; pImgEntries[230].rgbBlue=128;
	pImgEntries[231].rgbReserved=  0; pImgEntries[231].rgbRed=255; pImgEntries[231].rgbGreen= 32; pImgEntries[231].rgbBlue=255;
	pImgEntries[232].rgbReserved=  0; pImgEntries[232].rgbRed=255; pImgEntries[232].rgbGreen= 64; pImgEntries[232].rgbBlue=  0;
	pImgEntries[233].rgbReserved=  0; pImgEntries[233].rgbRed=255; pImgEntries[233].rgbGreen= 64; pImgEntries[233].rgbBlue= 64;
	pImgEntries[234].rgbReserved=  0; pImgEntries[234].rgbRed=255; pImgEntries[234].rgbGreen= 64; pImgEntries[234].rgbBlue=128;
	pImgEntries[235].rgbReserved=  0; pImgEntries[235].rgbRed=255; pImgEntries[235].rgbGreen= 64; pImgEntries[235].rgbBlue=255;
	pImgEntries[236].rgbReserved=  0; pImgEntries[236].rgbRed=255; pImgEntries[236].rgbGreen= 96; pImgEntries[236].rgbBlue=  0;
	pImgEntries[237].rgbReserved=  0; pImgEntries[237].rgbRed=255; pImgEntries[237].rgbGreen= 96; pImgEntries[237].rgbBlue= 64;
	pImgEntries[238].rgbReserved=  0; pImgEntries[238].rgbRed=255; pImgEntries[238].rgbGreen= 96; pImgEntries[238].rgbBlue=128;
	pImgEntries[239].rgbReserved=  0; pImgEntries[239].rgbRed=255; pImgEntries[239].rgbGreen= 96; pImgEntries[239].rgbBlue=255;
	pImgEntries[240].rgbReserved=  0; pImgEntries[240].rgbRed=255; pImgEntries[240].rgbGreen=128; pImgEntries[240].rgbBlue=  0;
	pImgEntries[241].rgbReserved=  0; pImgEntries[241].rgbRed=255; pImgEntries[241].rgbGreen=128; pImgEntries[241].rgbBlue= 64;
	pImgEntries[242].rgbReserved=  0; pImgEntries[242].rgbRed=255; pImgEntries[242].rgbGreen=128; pImgEntries[242].rgbBlue=128;
	pImgEntries[243].rgbReserved=  0; pImgEntries[243].rgbRed=255; pImgEntries[243].rgbGreen=128; pImgEntries[243].rgbBlue=255;
	pImgEntries[244].rgbReserved=  0; pImgEntries[244].rgbRed=255; pImgEntries[244].rgbGreen=160; pImgEntries[244].rgbBlue=  0;
	pImgEntries[245].rgbReserved=  0; pImgEntries[245].rgbRed=255; pImgEntries[245].rgbGreen=160; pImgEntries[245].rgbBlue= 64;
	pImgEntries[246].rgbReserved=  0; pImgEntries[246].rgbRed=255; pImgEntries[246].rgbGreen=160; pImgEntries[246].rgbBlue=128;
	pImgEntries[247].rgbReserved=  0; pImgEntries[247].rgbRed=255; pImgEntries[247].rgbGreen=160; pImgEntries[247].rgbBlue=255;
	pImgEntries[248].rgbReserved=  0; pImgEntries[248].rgbRed=255; pImgEntries[248].rgbGreen=192; pImgEntries[248].rgbBlue=  0;
	pImgEntries[249].rgbReserved=  0; pImgEntries[249].rgbRed=255; pImgEntries[249].rgbGreen=192; pImgEntries[249].rgbBlue= 64;
	pImgEntries[250].rgbReserved=  0; pImgEntries[250].rgbRed=255; pImgEntries[250].rgbGreen=192; pImgEntries[250].rgbBlue=128;
	pImgEntries[251].rgbReserved=  0; pImgEntries[251].rgbRed=255; pImgEntries[251].rgbGreen=192; pImgEntries[251].rgbBlue=255;
	pImgEntries[252].rgbReserved=  0; pImgEntries[252].rgbRed=255; pImgEntries[252].rgbGreen=255; pImgEntries[252].rgbBlue=  0;
	pImgEntries[253].rgbReserved=  0; pImgEntries[253].rgbRed=255; pImgEntries[253].rgbGreen=255; pImgEntries[253].rgbBlue= 64;
	pImgEntries[254].rgbReserved=  0; pImgEntries[254].rgbRed=255; pImgEntries[254].rgbGreen=255; pImgEntries[254].rgbBlue=128;
	pImgEntries[255].rgbReserved=  0; pImgEntries[255].rgbRed=255; pImgEntries[255].rgbGreen=255; pImgEntries[255].rgbBlue=255;
	return pImgEntries;
}
agbool CAGimageMicUtil::DecreasePal(AGCLRQUAD*& pEntries, aguint32 NUMENTRIES/*old*/, aguint32 numEntries/*new*/)
{
	if(pEntries==NULL || NUMENTRIES==0||NUMENTRIES<numEntries||numEntries==0)
		return agfalse;
	if(NUMENTRIES==numEntries)
		return agtrue;

	AGCLRQUAD*	pTmpEntries=(AGCLRQUAD*)malloc(numEntries*sizeof(AGCLRQUAD));
	aguint32		ratio=NUMENTRIES/numEntries;

	memset(pTmpEntries,0,numEntries*sizeof(AGCLRQUAD));
	for(aguint32 i=0;i<numEntries/*-1*/;i++)
	{
		pTmpEntries[i].rgbRed=pEntries[i*ratio].rgbRed;
		pTmpEntries[i].rgbGreen=pEntries[i*ratio].rgbGreen;
		pTmpEntries[i].rgbBlue=pEntries[i*ratio].rgbBlue;
		pTmpEntries[i].rgbReserved=pEntries[i*ratio].rgbReserved;
	}

	free(pEntries);
	pEntries=pTmpEntries;
	return agtrue;
}

//hPal truyen vao phai bang NULL, sau khi su dung phai tu huy
aguint32 CAGimageMicUtil::CreatePal(CAGimage* pAGimage, HPALETTE& hPal)
{
	if(hPal)	{::DeleteObject(hPal); hPal=NULL;}

	aguint32			nBits,n;
	LPLOGPALETTE	pLogPal;

	nBits=pAGimage->GetBpp();
	if(nBits>=24)	return 0;

	aguint32 NUMENTRIES=pAGimage->GetNumColors();
	if(NUMENTRIES==0) return 0;
	n=sizeof(LOGPALETTE)+(NUMENTRIES-1)*sizeof(PALETTEENTRY);
	
	pLogPal=(LPLOGPALETTE)malloc(n*sizeof(BYTE));
	pLogPal->palVersion=0x300;
	pLogPal->palNumEntries=(WORD)NUMENTRIES;

	AGCLRQUAD*	pEntries=pAGimage->GetPalette();
	for(aguint32 i=0;i<NUMENTRIES;i++)
	{
		pLogPal->palPalEntry[i].peRed=pEntries[i].rgbRed;
		pLogPal->palPalEntry[i].peGreen=pEntries[i].rgbGreen;
		pLogPal->palPalEntry[i].peBlue=pEntries[i].rgbBlue;
		pLogPal->palPalEntry[i].peFlags=pEntries[i].rgbReserved;
	}
	hPal=::CreatePalette(pLogPal);
	free(pLogPal);

	return (hPal==NULL)? 0 : NUMENTRIES;
}

//pRGBEntries truyen vao phai bang NULL, sau khi su dung phai huy bang free
aguint32 CAGimageMicUtil::CreatePal(HDC hDC, AGCLRQUAD*& pRGBQUADEntries)
{
	if(pRGBQUADEntries)	{free(pRGBQUADEntries); pRGBQUADEntries=NULL;}

	aguint32 cColors;
	if(hDC==NULL)	return 0;
	else
	{
		cColors = ::GetSystemPaletteEntries(hDC,0,0,NULL);
		if(cColors==0)	return 0;
	}

	PALETTEENTRY* palEntries=(PALETTEENTRY*)malloc(cColors*sizeof(PALETTEENTRY));;
	::GetSystemPaletteEntries(hDC,0,cColors,palEntries);

	pRGBQUADEntries=(AGCLRQUAD*)malloc(cColors*sizeof(AGCLRQUAD));
	memset(pRGBQUADEntries,0,cColors*sizeof(AGCLRQUAD));
	for(aguint32 i=0; i<cColors; i++)
	{
		pRGBQUADEntries[i].rgbRed=palEntries[i].peRed;
		pRGBQUADEntries[i].rgbGreen=palEntries[i].peGreen;
		pRGBQUADEntries[i].rgbBlue=palEntries[i].peBlue;
		pRGBQUADEntries[i].rgbReserved=palEntries[i].peFlags;
	}
	free(palEntries);

	return cColors;
}
//pRGBEntries truyen vao phai bang NULL, sau khi su dung phai huy bang free
aguint32 CAGimageMicUtil::GetRGBQUADFromHPALETTE(HPALETTE hPal, AGCLRQUAD*& pRGBQUADEntries)
{
	if(pRGBQUADEntries)	{free(pRGBQUADEntries); pRGBQUADEntries=NULL;}

	aguint32 cColors;
	if(hPal==NULL)	return 0;
	else
	{
		cColors = ::GetPaletteEntries(hPal,0,0,NULL);
		if(cColors==0)	return 0;
	}
	
	PALETTEENTRY* palEntries=(PALETTEENTRY*)malloc(cColors*sizeof(PALETTEENTRY));;
	::GetPaletteEntries(hPal,0,cColors,palEntries);

	pRGBQUADEntries=(AGCLRQUAD*)malloc(cColors*sizeof(AGCLRQUAD));
	memset(pRGBQUADEntries,0,cColors*sizeof(AGCLRQUAD));
	for(aguint32 i=0; i<cColors; i++)
	{
		pRGBQUADEntries[i].rgbRed=palEntries[i].peRed;
		pRGBQUADEntries[i].rgbGreen=palEntries[i].peGreen;
		pRGBQUADEntries[i].rgbBlue=palEntries[i].peBlue;
		pRGBQUADEntries[i].rgbReserved=palEntries[i].peFlags;
	}
	free(palEntries);

	return cColors;
}

#endif	//#ifdef WIN32

#if AGMAGIC_SUPPORT_MFC

CAGimageMicUtil::DocType CAGimageMicUtil::doctypes[CMAX_IMAGE_FORMATS] =
{
	{ -1, TRUE, TRUE, _T("Supported files"), _T("*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.ico;*.tif;*.tiff;*.tga;*.pcx;*.wbmp;*.wmf;*.emf;*.j2k;*.jp2;*.jbg;*.j2c;*.jpc;*.pgx;*.pnm;*.pgm;*.ppm;*.ras") },
#if CXIMAGE_SUPPORT_BMP
	{ CXIMAGE_FORMAT_BMP, TRUE, TRUE, _T("BMP files"), _T("*.bmp") },
#endif
#if CXIMAGE_SUPPORT_GIF
	{ CXIMAGE_FORMAT_GIF, TRUE, TRUE, _T("GIF files"), _T("*.gif") },
#endif
#if CXIMAGE_SUPPORT_JPG
	{ CXIMAGE_FORMAT_JPG, TRUE, TRUE, _T("JPG files"), _T("*.jpg;*.jpeg") },
#endif
#if CXIMAGE_SUPPORT_PNG
	{ CXIMAGE_FORMAT_PNG, TRUE, TRUE, _T("PNG files"), _T("*.png") },
#endif
#if CXIMAGE_SUPPORT_MNG
	{ CXIMAGE_FORMAT_MNG, TRUE, TRUE, _T("MNG files"), _T("*.mng;*.jng;*.png") },
#endif
#if CXIMAGE_SUPPORT_ICO
	{ CXIMAGE_FORMAT_ICO, TRUE, TRUE, _T("ICO CUR files"), _T("*.ico;*.cur") },
#endif
#if CXIMAGE_SUPPORT_TIF
	{ CXIMAGE_FORMAT_TIF, TRUE, TRUE, _T("TIF files"), _T("*.tif;*.tiff") },
#endif
#if CXIMAGE_SUPPORT_TGA
	{ CXIMAGE_FORMAT_TGA, TRUE, TRUE, _T("TGA files"), _T("*.tga") },
#endif
#if CXIMAGE_SUPPORT_PCX
	{ CXIMAGE_FORMAT_PCX, TRUE, TRUE, _T("PCX files"), _T("*.pcx") },
#endif
#if CXIMAGE_SUPPORT_WBMP
	{ CXIMAGE_FORMAT_WBMP, TRUE, TRUE, _T("WBMP files"), _T("*.wbmp") },
#endif
#if CXIMAGE_SUPPORT_WMF
	{ CXIMAGE_FORMAT_WMF, TRUE, FALSE, _T("WMF EMF files"), _T("*.wmf;*.emf") },
#endif
#if CXIMAGE_SUPPORT_J2K
	{ CXIMAGE_FORMAT_J2K, TRUE, TRUE, _T("J2K files"), _T("*.j2k;*.jp2") },
#endif
#if CXIMAGE_SUPPORT_JBG
	{ CXIMAGE_FORMAT_JBG, TRUE, TRUE, _T("JBG files"), _T("*.jbg") },
#endif
#if CXIMAGE_SUPPORT_JP2
	{ CXIMAGE_FORMAT_JP2, TRUE, TRUE, _T("JP2 files"), _T("*.j2k;*.jp2") },
#endif
#if CXIMAGE_SUPPORT_JPC
	{ CXIMAGE_FORMAT_JPC, TRUE, TRUE, _T("JPC files"), _T("*.j2c;*.jpc") },
#endif
#if CXIMAGE_SUPPORT_PGX
	{ CXIMAGE_FORMAT_PGX, TRUE, TRUE, _T("PGX files"), _T("*.pgx") },
#endif
#if CXIMAGE_SUPPORT_RAS
	{ CXIMAGE_FORMAT_RAS, TRUE, TRUE, _T("RAS files"), _T("*.ras") },
#endif
#if CXIMAGE_SUPPORT_PNM
	{ CXIMAGE_FORMAT_PNM, TRUE, TRUE, _T("PNM files"), _T("*.pnm;*.pgm;*.ppm") }
#endif
};
BOOL CAGimageMicUtil::doctypesPromptForFileName(CString& fileName, UINT nIDSTitle, 
	DWORD dwFlags, BOOL bOpenFileDialog, int* pType)
{
	CFileDialog dlgFile(bOpenFileDialog);
	CString title;
	if (bOpenFileDialog) title=_T("Open image file"); else title=_T("Save image file");

	dlgFile.m_ofn.Flags |= dwFlags;

	int nDocType = (pType != NULL) ? *pType : CXIMAGE_FORMAT_BMP;
	if (nDocType==0) nDocType=1;

	int nIndex = doctypesGetIndexFromType(nDocType, bOpenFileDialog);
	if (nIndex == -1) nIndex = 0;

	dlgFile.m_ofn.nFilterIndex = nIndex +1;
	// strDefExt is necessary to hold onto the memory from GetExtFromType
	CString strDefExt = doctypesGetExtFromType(nDocType).Mid(2,3);
	dlgFile.m_ofn.lpstrDefExt = strDefExt;
		
	CString strFilter = doctypesGetFileTypes(bOpenFileDialog);
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	if (bRet){
		if (pType != NULL){
			int nIndex = (int)dlgFile.m_ofn.nFilterIndex - 1;
			ASSERT(nIndex >= 0);
			*pType = doctypesGetTypeFromIndex(nIndex, bOpenFileDialog);
		}
	}
	return bRet;
}
//////////////////////////////////////////////////////////////////////////////
int CAGimageMicUtil::doctypesGetIndexFromType(int nDocType, BOOL bOpenFileDialog)
{
	int nCnt = 0;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog ? doctypes[i].bRead : doctypes[i].bWrite){
			if (doctypes[i].nID == nDocType) return nCnt;
			nCnt++;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////
int CAGimageMicUtil::doctypesGetTypeFromIndex(int nIndex, BOOL bOpenFileDialog)
{
	int nCnt = 0;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog ? doctypes[i].bRead : doctypes[i].bWrite){
			if (nCnt == nIndex)
//              return i; // PJO - Buglet ?
                return doctypes[i].nID;
			nCnt++;
		}
	}
	ASSERT(FALSE);
	return -1;
}
//////////////////////////////////////////////////////////////////////////////
CString CAGimageMicUtil::doctypesGetExtFromType(int nDocType)
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].ext;
	}
	return CString(_T(""));
}
//////////////////////////////////////////////////////////////////////////////
CString CAGimageMicUtil::doctypesGetDescFromType(int nDocType)
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].description;
	}
	return CString(_T(""));
}
//////////////////////////////////////////////////////////////////////////////

BOOL CAGimageMicUtil::doctypesGetWritableType(int nDocType){
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].bWrite;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
CString CAGimageMicUtil::doctypesGetFileTypes(BOOL bOpenFileDialog)
{
	CString str;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog && doctypes[i].bRead){
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		} else if (!bOpenFileDialog && doctypes[i].bWrite) {
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		}
	}
	return str;
}

//bAllSameSizeImage=agtrue: moi bitmap co cung kich co voi ImageList
//Tao ra roi phai delete CImageList*
CImageList*	CAGimageMicUtil::CreateImageList(CAGptrArray* pAGimageA, CSize* pListItemSize, CDC* pDC, COLORREF* pcrMask, agbool bAllSameSizeImage)
{
	if(pAGimageA==NULL || pAGimageA->GetSize()==0)
		return NULL;
	aguint32		n=pAGimageA->GetSize();
	CImageList*	pImageList=new CImageList();
	pImageList->Create(pListItemSize->cx,pListItemSize->cy,ILC_COLOR24, 0, n);
	
	for(aguint32 i=0; i<n; i++)
	{
		HBITMAP		hBmp=NULL;
		CAGimage*	pAGimage=(CAGimage*)(pAGimageA->GetAt(i));
		if(bAllSameSizeImage)
		{
			aguint32 w=pAGimage->GetWidth(), h=pAGimage->GetHeight();
			agreal64 w_ratio=(agreal64)w/pListItemSize->cx + 0.5;
			agreal64 h_ratio=(agreal64)h/pListItemSize->cy + 0.5;
			agreal64 ratio;

			if(w_ratio>1 || h_ratio>1)
				ratio=(w_ratio>h_ratio)?((agreal64)1/w_ratio) : ((agreal64)1/h_ratio);
			else
				ratio=(w_ratio>h_ratio)?h_ratio : h_ratio;

			w=(aguint32)(ratio*w);
			h=(aguint32)(ratio*h);
			CxImage	iDst(*pAGimage);
			pAGimage->Resample(w,h,1,&iDst);
			hBmp=iDst.MakeBitmap(pDC->GetSafeHdc());
		}
		else
		{
			hBmp=pAGimage->MakeBitmap(pDC->GetSafeHdc());
		}
		if(hBmp!=NULL)
		{
			if(pcrMask==NULL)
				pImageList->Add(CBitmap::FromHandle(hBmp),(CBitmap*)NULL);
			else
				pImageList->Add(CBitmap::FromHandle(hBmp),*pcrMask);
			::DeleteObject(hBmp);
		}
	}
	return pImageList;
}

//sizeHinge la khoang dem giua cac hinh
void CAGimageMicUtil::DrawA(CPoint xy, aguint32& nCols, CAGptrArray* pAGimageA, HDC hDC, CSize* pSize, CSize sizeHinge)
{
	if(pAGimageA==NULL)	return;
	aguint32 n=pAGimageA->GetSize();
	nCols=AGMIN(n,nCols);
	if(nCols==0)	return;

	aguint32 nRows=n/nCols;
	aguint32 nEx=n%nCols;
	sizeHinge.cx=sizeHinge.cx<0?0:sizeHinge.cx;
	sizeHinge.cy=sizeHinge.cy<0?0:sizeHinge.cy;
	if(pSize!=NULL)
	{
		aguint32	maxW=0, maxH=0;
		aguint32 w, h;
		aguint32 i=0;
		for(i=0; i<nRows; i++)
		{
			w=h=0;
			for(aguint32 j=0; j<nCols; j++)
			{
				w+=((CAGimage*)(pAGimageA->GetAt(i*nCols+j)))->GetWidth();
				h=AGMAX(((CAGimage*)(pAGimageA->GetAt(i*nCols+j)))->GetHeight() , h);
			}
			maxW=AGMAX(w,maxW);
			maxH+=h;
		}
		if(nRows==0)	i=0;
		if(nEx>0)
		{
			w=h=0;
			for(aguint32 k=0; k<nEx; k++)
			{
				w+=((CAGimage*)(pAGimageA->GetAt(i*nCols+k)))->GetWidth();
				h=AGMAX(((CAGimage*)(pAGimageA->GetAt(i*nCols+k)))->GetHeight() , h);
			}
			maxW=AGMAX(w,maxW);
			maxH+=h;
		}		
		pSize->cx=xy.x + maxW+(nCols+1)*sizeHinge.cx;
		pSize->cy=xy.y + maxH+((nEx>0?nRows+1:nRows)+1)*sizeHinge.cy;
	}

	if(hDC==NULL)	return;
	CPoint pos=xy;
	aguint32 i=0;
	for(i=0; i<nRows; i++)
	{
		pos.x=sizeHinge.cx;
		pos.y+=sizeHinge.cy;
		aguint32 h=0;
		for(aguint32 j=0; j<nCols; j++)
		{
			CAGimage* pAGimage=(CAGimage*)(pAGimageA->GetAt(i*nCols+j));
			//
			pAGimage->Draw(hDC,pos.x,pos.y);
			//
			h=AGMAX(pAGimage->GetHeight(),h);
			pos.x+=pAGimage->GetWidth()+sizeHinge.cx;
		}
		pos.y+=h;
	}
	if(nRows==0)	i=0;
	if(nEx>0)
	{
		pos.x=sizeHinge.cx;
		pos.y+=sizeHinge.cy;
		for(aguint32 k=0; k<nEx; k++)
		{
			CAGimage* pAGimage=(CAGimage*)(pAGimageA->GetAt(i*nCols+k));
			//
			pAGimage->Draw(hDC,pos.x,pos.y);
			//
			pos.x+=pAGimage->GetWidth()+sizeHinge.cx;
		}
	}
}
void CAGimageMicUtil::DrawAA(CPoint xy, CAGptrArray* pAGimageAA, HDC hDC, CSize* pSize, CSize sizeHinge)
{
	sizeHinge.cx=sizeHinge.cx<0?0:sizeHinge.cx;
	sizeHinge.cy=sizeHinge.cy<0?0:sizeHinge.cy;
	if(pSize!=NULL)
	{
		aguint32	nRows=pAGimageAA->GetSize();
		aguint32	maxCols=0;
		aguint32	maxW=0, maxH=0;
		aguint32	w, h;
		for(aguint32 i=0; i<nRows; i++)
		{
			w=h=0;
			CAGptrArray*	pAGimageA=(CAGptrArray*)(pAGimageAA->GetAt(i));
			aguint32		nCols=pAGimageA->GetSize();
			for(aguint32 j=0; j<nCols; j++)
			{
				w+=((CAGimage*)(pAGimageA->GetAt(j)))->GetWidth();
				h=AGMAX(((CAGimage*)(pAGimageA->GetAt(j)))->GetHeight() , h);
			}
			maxW=AGMAX(w,maxW);
			maxH+=h;
			maxCols=AGMAX(nCols,maxCols);
		}
		pSize->cx=xy.x + maxW+(maxCols+1)*sizeHinge.cx;
		pSize->cy=xy.y + maxH+(nRows+1)*sizeHinge.cy;
	}

	if(hDC==NULL)		return;
	CPoint	pos(0,0);
	aguint32	nRows=pAGimageAA->GetSize();
	for(aguint32 i=0; i<nRows; i++)
	{
		CAGptrArray*	pAGimageA=(CAGptrArray*)(pAGimageAA->GetAt(i));
		aguint32		nCols=pAGimageA->GetSize();

		pos.x=sizeHinge.cx;
		pos.y+=sizeHinge.cy;
		aguint32 h=0;
		for(aguint32 j=0; j<nCols; j++)
		{
			CAGimage *pAGimage=(CAGimage*)(pAGimageA->GetAt(j));
			//
			pAGimage->Draw(hDC,pos.x,pos.y);
			//
			h=AGMAX(pAGimage->GetHeight(),h);
			pos.x+=pAGimage->GetWidth()+sizeHinge.cx;
		}
		pos.y+=h;
	}
}

agbool CAGimageMicUtil::DrawPal(CPoint xy, AGCLRQUAD* pEntries, aguint32 nColors, CSize squareXY, aguint32 nCols, agbool bRainbow, CDC* pDC, CSize* pSize, CSize sizeHinge)
{
	if(pEntries==NULL || nColors==0 || squareXY.cx==0 || squareXY.cy==0 || nCols==0)
		return agfalse;
	aguint32	nColsMode=0;
	aguint32	nRows=0,nRowsMode=0;

	nCols=(nCols>nColors)?nColors:nCols;
	nColsMode=nColors%nCols;
	nRows=nColors/nCols;
	nRowsMode=nColsMode>0?1:0;
	
	if(pSize!=NULL)
	{
		if(bRainbow)//neu ve lien nhau thanh vet cau vong, khoang cach giua cac o la 0
		{
			pSize->cx=xy.x + squareXY.cx*nColors;
			pSize->cy=xy.y + squareXY.cy;
		}
		else
		{
			pSize->cx=xy.x + squareXY.cx*nCols + (nCols+1)*sizeHinge.cx;
			pSize->cy=xy.x + squareXY.cy*(nRows+nRowsMode) + (nRows+nRowsMode+1)*sizeHinge.cy;
		}
	}
	if(pDC!=NULL)
	{
		if(bRainbow)//neu ve lien nhau thanh vet cau vong, khoang cach giua cac o la 0
		{
			CPoint pos=xy;
			for(aguint32 i=0; i<nColors; i++)
			{
				CPen	pen(PS_SOLID,1,RGB(pEntries[i].rgbRed,pEntries[i].rgbGreen,pEntries[i].rgbBlue));
				CBrush	brush(RGB(pEntries[i].rgbRed,pEntries[i].rgbGreen,pEntries[i].rgbBlue));
				CPen*	pOldPen=NULL;
				CBrush*	pOldBrush=NULL;

				pOldPen=pDC->SelectObject(&pen);
				pOldBrush=pDC->SelectObject(&brush);
				pDC->Rectangle(pos.x,pos.y,pos.x+squareXY.cx,pos.y+squareXY.cy);

				pDC->SelectObject(pOldPen);
				pDC->SelectObject(pOldBrush);

				pos.x+=squareXY.cx;
			}
		}
		else
		{
			CPoint pos=xy;
			pos.y +=sizeHinge.cy;
			for(aguint32 i=0; i<nRows+nRowsMode; i++)
			{
				pos.x=sizeHinge.cx;

				aguint32 n;
				if(i==nRows)
					n=nColsMode;
				else
					n=nCols;
				for(aguint32 j=0; j<n; j++)
				{
					CPen	pen(PS_SOLID,1,RGB(pEntries[i*nCols+j].rgbRed,pEntries[i*nCols+j].rgbGreen,pEntries[i*nCols+j].rgbBlue));
					CBrush	brush(RGB(pEntries[i*nCols+j].rgbRed,pEntries[i*nCols+j].rgbGreen,pEntries[i*nCols+j].rgbBlue));
					CPen*	pOldPen=NULL;
					CBrush*	pOldBrush=NULL;

					pOldPen=pDC->SelectObject(&pen);
					pOldBrush=pDC->SelectObject(&brush);
					pDC->Rectangle(pos.x,pos.y,pos.x+squareXY.cx,pos.y+squareXY.cy);

					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldBrush);

					pos.x+=squareXY.cx+sizeHinge.cx;
				}
				pos.y+=sizeHinge.cy+squareXY.cy;
			}

		}
	}
	return agtrue;
}
agbool CAGimageMicUtil::DrawPal(CPoint xy, CAGimage* pAGimage, CSize squareXY, aguint32 nCols, agbool bRainbow, CDC* pDC, CSize* pSize, CSize sizeHinge)
{
	if(pAGimage==NULL)
		return agfalse;
	aguint32 nColors=pAGimage->GetNumColors();
	if(nColors==0)
		return agfalse;

	AGCLRQUAD* pEntries=NULL;
	if(nColors==2)
	{
		pEntries=(AGCLRQUAD*)malloc(nColors*sizeof(AGCLRQUAD));
		memset(&(pEntries[0]),0x00,sizeof(AGCLRQUAD));
		memset(&(pEntries[1]),0xFF,sizeof(AGCLRQUAD));
	}
	else
		pEntries=pAGimage->GetPalette();

	if(pEntries==NULL)
		return agfalse;

	agbool result=DrawPal(xy,pEntries,nColors,squareXY,nCols,bRainbow,pDC,pSize,sizeHinge);
	if(nColors==2)
		free(pEntries);
	return result;
}

//pPal truyen vao phai bang NULL, sau khi su dung phai tu huy
aguint32	CAGimageMicUtil::CreatePal(CAGimage* pAGimage, CPalette*& pPal)
{
	HPALETTE	hPal=NULL;
	aguint32		NUMENTRIES=CreatePal(pAGimage,hPal);
	
	if(NUMENTRIES>0 && hPal!=NULL)
	{
		pPal=new CPalette();
		pPal->Attach(hPal);

		return NUMENTRIES;
	}
	return 0;
}

#endif	//#if AGMAGIC_SUPPORT_MFC

agtchar* CAGimageMicUtil::FindFileExtension(const agtchar* FileName, agtchar out_ext[])
{
#if AGMAGIC_SUPPORT_MFC
	CString	name=FileName;
	int len = name.GetLength();
	for (int i = len-1; i >= 0; i--){
		if (name[i] == _T('.')){
			_tcscpy(out_ext,name.Mid(i+1));
			break;
		}
	}
#else
	throw _T("Implement not yet");
#endif
	return out_ext;
}

//Tra ve 0 la CXIMAGE_FORMAT_UNKNOWN
agint32 CAGimageMicUtil::FindFileType(const agtchar* ext)
{
	agint32		type = 0;

#if CXIMAGE_SUPPORT_BMP
	if (_tcsicmp(ext,_T("bmp"))==0)											type = CXIMAGE_FORMAT_BMP;
#endif
#if CXIMAGE_SUPPORT_JPG
	else if (_tcsicmp(ext,_T("jpg"))==0 ||_tcsicmp(ext,_T("jpeg"))==0)		type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (_tcsicmp(ext,_T("gif"))==0)									type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (_tcsicmp(ext,_T("png"))==0)									type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (_tcsicmp(ext,_T("mng"))==0||_tcsicmp(ext,_T("jng"))==0)		type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (_tcsicmp(ext,_T("ico"))==0)									type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (_tcsicmp(ext,_T("tiff"))==0||_tcsicmp(ext,_T("tif"))==0)		type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (_tcsicmp(ext,_T("tga"))==0)									type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (_tcsicmp(ext,_T("pcx"))==0)									type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (_tcsicmp(ext,_T("wbmp"))==0)									type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (_tcsicmp(ext,_T("wmf"))==0||_tcsicmp(ext,_T("emf"))==0)		type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (_tcsicmp(ext,_T("j2k"))==0||_tcsicmp(ext,_T("jp2"))==0)		type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (_tcsicmp(ext,_T("jbg"))==0)									type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (_tcsicmp(ext,_T("jp2"))==0||_tcsicmp(ext,_T("j2k"))==0)		type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (_tcsicmp(ext,_T("jpc"))==0||_tcsicmp(ext,_T("j2c"))==0)		type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (_tcsicmp(ext,_T("pgx"))==0)									type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (_tcsicmp(ext,_T("ras"))==0)									type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (_tcsicmp(ext,_T("pnm"))==0 || 
		     _tcsicmp(ext,_T("pgm"))==0 ||_tcsicmp(ext,_T("ppm"))==0)		type = CXIMAGE_FORMAT_PNM;
#endif
	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}

//Tra ve _T("") la CXIMAGE_FORMAT_UNKNOWN
agtchar* CAGimageMicUtil::FindFileTypeStr(agint32 type, agtchar ext[])
{
#if CXIMAGE_SUPPORT_BMP
	if (type == CXIMAGE_FORMAT_BMP)			_tcscpy(ext,_T("bmp"));
#endif
#if CXIMAGE_SUPPORT_JPG
	else if (type==CXIMAGE_FORMAT_JPG)		_tcscpy(ext,_T("jpg"));
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (type == CXIMAGE_FORMAT_GIF)	_tcscpy(ext,_T("gif"));
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (type == CXIMAGE_FORMAT_PNG)	_tcscpy(ext,_T("png"));
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (type==CXIMAGE_FORMAT_MNG)		_tcscpy(ext,_T("mng"));
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (type == CXIMAGE_FORMAT_ICO)	_tcscpy(ext,_T("ico"));
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (type==CXIMAGE_FORMAT_TIF)		_tcscpy(ext,_T("tif"));
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (type==CXIMAGE_FORMAT_TGA)		_tcscpy(ext,_T("tga"));
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (type==CXIMAGE_FORMAT_PCX)		_tcscpy(ext,_T("pcx"));
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (type==CXIMAGE_FORMAT_WBMP)		_tcscpy(ext,_T("wbmp"));
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (type==CXIMAGE_FORMAT_WMF)		_tcscpy(ext,_T("wmf"));
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (type==CXIMAGE_FORMAT_J2K)		_tcscpy(ext,_T("j2k"));
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (type==CXIMAGE_FORMAT_JBG)		_tcscpy(ext,_T("jbg"));
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (type==CXIMAGE_FORMAT_JP2)		_tcscpy(ext,_T("jp2"));
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (type==CXIMAGE_FORMAT_JPC)		_tcscpy(ext,_T("jpc"));
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (type==CXIMAGE_FORMAT_PGX)		_tcscpy(ext,_T("pgx"));
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (type==CXIMAGE_FORMAT_RAS)		_tcscpy(ext,_T("ras"));
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (type==CXIMAGE_FORMAT_PNM)		_tcscpy(ext,_T("pnm"));
#endif
	else _tcscpy(ext,_T(""));

	return ext;
}

/*******************************class CAGimageIOUtil*******************************/

void CAGimageIOUtil::GetAllSupportImageExt(agtchar exts[], agtchar seps[])
{
#if CXIMAGE_SUPPORT_BMP
	_tcscpy(exts,_T("bmp"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_GIF
	_tcscat(exts,_T("gif"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_JPG
	_tcscat(exts,_T("jpg"));	_tcscat(exts,seps);
	_tcscat(exts,_T("jpeg"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_PNG
	_tcscat(exts,_T("png"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_MNG
	_tcscat(exts,_T("mng"));	_tcscat(exts,seps);
	_tcscat(exts,_T("jng"));	_tcscat(exts,seps);
	_tcscat(exts,_T("png"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_ICO
	_tcscat(exts,_T("ico"));	_tcscat(exts,seps);
	_tcscat(exts,_T("cur"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_TIF
	_tcscat(exts,_T("tif"));	_tcscat(exts,seps);
	_tcscat(exts,_T("tiff"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_TGA
	_tcscat(exts,_T("tga"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_PCX
	_tcscat(exts,_T("pcx"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_WBMP
	_tcscat(exts,_T("wbmp"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_WMF
	_tcscat(exts,_T("wmf"));	_tcscat(exts,seps);
	_tcscat(exts,_T("emf"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_J2K
	_tcscat(exts,_T("j2k"));	_tcscat(exts,seps);
	_tcscat(exts,_T("jp2"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_JBG
	_tcscat(exts,_T("jbg"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_JP2
	_tcscat(exts,_T("j2k"));	_tcscat(exts,seps);
	_tcscat(exts,_T("jp2"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_JPC
	_tcscat(exts,_T("j2c"));	_tcscat(exts,seps);
	_tcscat(exts,_T("jpc"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_PGX
	_tcscat(exts,_T("pgx"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_RAS
	_tcscat(exts,_T("ras"));	_tcscat(exts,seps);
#endif
#if CXIMAGE_SUPPORT_PNM
	_tcscat(exts,_T("pnm"));	_tcscat(exts,seps);
	_tcscat(exts,_T("pgm"));	_tcscat(exts,seps);
	_tcscat(exts,_T("ppm"));	_tcscat(exts,seps);
#endif
}
void CAGimageIOUtil::AnalyzeImagePathAndAlloc(agtchar szImagePath[], agtchar*& szBaseSampleDir, agtchar*& szDirTypeName, agtchar*& szImageName)
{
	if(szImageName)		free(szImageName);		szImageName=NULL;
	if(szBaseSampleDir)	free(szBaseSampleDir);	szBaseSampleDir=NULL;
	if(szDirTypeName)	free(szDirTypeName);	szDirTypeName=NULL;		
	if(szImagePath==NULL || _tcslen(szImagePath)==0)	return;
	agint32	len=_tcslen(szImagePath);

	agtchar*		idx=_tcsrchr(szImagePath,AGMAGIC_DIR_SPLASH);
	if(idx==NULL)	return;

	//Lat ten file
	CAGmagicStrUtil::private_tcscat(szImageName,idx+1,agtrue);
	if(szImageName==NULL)	return;

	//Lay thu muc chua file
	agtchar*	szDir=NULL;
	agtchar		ch=*idx;	*idx=0;
	CAGmagicStrUtil::private_tcscat(szDir,szImagePath,agtrue);
	*idx=ch;
	if(szDir==NULL)	return;

	//Lay thu muc chua thu muc chua file:szBaseSampleDir va thu muc Type cua anh
	idx=_tcsrchr(szDir,AGMAGIC_DIR_SPLASH);
	if(idx==NULL)	szBaseSampleDir=szDir;
	else
	{
		szBaseSampleDir=szDir;
		CAGmagicStrUtil::private_tcscat(szDirTypeName,idx+1,agtrue);
		*idx=0;//cat szDir de szDir la szBaseSampleDir
	}
}
/*
--szDir la thu muc chua anh
--szKey la dang file. VD: *.*, *.BMP, *.JPEG, ...
*/
agbool CAGimageIOUtil::LoadA(CAGptrArray* pAGimageA, agtchar szDir[], agtchar szKey[], CAGimage* pTempImage, aguint32 imagetype)
{
	if(pAGimageA==NULL)	return agfalse;
	DELETE_AGMAGICIP_ARRAYPTR(pAGimageA,agfalse)

#if AGMAGIC_SUPPORT_MFC
	CString		szFindPath =szDir;	szFindPath +=_T("\\");	szFindPath +=szKey;

	CFileFind	FileFinder;
	CAGimage*	pAGimage=NULL;
	if(FileFinder.FindFile(szFindPath))
	{
		CString FilePath;
		CString FileURL;
		while(FileFinder.FindNextFile())
		{
			FilePath=FileFinder.GetFilePath();
			//FileURL=FileFinder.GetFileURL();
			//CAGmagicMicUtil::ChangeURLFromWin(FileURL);//chuyen ve dang URL chuan
			if(FileFinder.IsDots())
				continue;
			else if(FileFinder.IsDirectory())
			{
				agtchar* szDir2=NULL;	CAGmagicStrUtil::private_tcscat(szDir2,FilePath,agtrue);
				LoadA(pAGimageA,szDir2,szKey,pTempImage,imagetype);//de qui
				if(szDir2)	free(szDir2);
			}
			else
			{
				pAGimage=NULL;
				if(pTempImage==NULL)	pAGimage=new CAGimage();
				else					pAGimage=pTempImage->CreateMe();
				pAGimage->Load(FilePath,imagetype);
				pAGimageA->Add(pAGimage);
			}
		}
		FilePath=FileFinder.GetFilePath();
		//FileURL=FileFinder.GetFileURL();
		//CAGmagicMicUtil::ChangeURLFromWin(FileURL);
		if(!FileFinder.IsDirectory())
		{
			pAGimage=NULL;
			if(pTempImage==NULL)	pAGimage=new CAGimage();
			else					pAGimage=pTempImage->CreateMe();
			pAGimage->Load(FilePath,imagetype);
			pAGimageA->Add(pAGimage);
		}
	}
	FileFinder.Close();
#else
	throw _T("Implement not yet");
#endif
	return agtrue;
}

agbool CAGimageIOUtil::LoadAA_TD(CAGptrArray* pAGimageAA_TD, agtchar szDir[], agtchar szKey[], aguint32 numCols, CAGimage* pTempImage, aguint32 imagetype)
{
	if(numCols==0 || pAGimageAA_TD==NULL)	return agfalse;
	DELETE_AGMAGICIP_ARRAYPTR_ARRAYPTR(pAGimageAA_TD,agfalse)

	CAGptrArray aAGimage;
	if(!LoadA(&aAGimage,szDir,szKey,pTempImage,imagetype))
	{
		DELETE_AGMAGICIP_ARRAY(aAGimage)
		return agfalse;
	}
	aguint32 n=aAGimage.GetSize();
	if(n==0)
		return agfalse;

	for(aguint32 i=0; i<n; i+=numCols)
	{
		CAGptrArray* pAGimageA=new CAGptrArray();
		for(aguint32 j=0; j<numCols && i+j<n; j++)
			pAGimageA->Add(aAGimage.GetAt(i+j));
		pAGimageAA_TD->Add(pAGimageA);
	}

	return agtrue;
}

/*
--szFilePathAndName co dang c:\\data\\a voi a la ten anh, sau se duoc ghep voi nhu sau
	c:\\data\\a-0.bmp hay c:\\data\\a-0-0.bmp
*/
agbool CAGimageIOUtil::SaveA(CAGptrArray* pAGimageA, agtchar szFilePathAndName[], aguint32 imagetype)
{
	if(pAGimageA==NULL || szFilePathAndName==NULL)	return agfalse;
	aguint32 n=pAGimageA->GetSize();
	for(aguint32 i=0; i<n; i++)
	{
		CAGimage*	pAGimage=(CAGimage*)(pAGimageA->GetAt(i));

		agtchar*	szFile=NULL;
		CAGmagicStrUtil::private_tcscat(szFile,szFilePathAndName,agtrue);
		CAGmagicStrUtil::private_tcscat(szFile,_T("-"),agtrue);
		CAGmagicStrUtil::private_tcscat(szFile,i,agtrue);
		CAGmagicStrUtil::private_tcscat(szFile,_T("."),agtrue);
		agtchar	ext[64];
		CAGmagicStrUtil::private_tcscat(szFile,CAGimageMicUtil::FindFileTypeStr(imagetype,ext),agtrue);

		pAGimage->Save(szFile,imagetype);
		if(szFile)	free(szFile);
	}
	return agtrue;
}

agbool CAGimageIOUtil::SaveAA_TD(CAGptrArray* pAGimageAA_TD, agtchar szFilePathAndName[], aguint32 imagetype)
{
	if(pAGimageAA_TD==NULL || szFilePathAndName==NULL)
		return agfalse;
	aguint32 m=pAGimageAA_TD->GetSize();
	for(aguint32 i=0; i<m; i++)
	{
		CAGptrArray*	pAGimageA=(CAGptrArray*)(pAGimageAA_TD->GetAt(i));
		aguint32		n=pAGimageA->GetSize();
		for(aguint32 j=0; j<n; j++)
		{
			CAGimage*	pAGimage=(CAGimage*)(pAGimageA->GetAt(j));

			agtchar*	szFile=NULL;
			CAGmagicStrUtil::private_tcscat(szFile,szFilePathAndName,agtrue);
			CAGmagicStrUtil::private_tcscat(szFile,_T("-"),agtrue);
			CAGmagicStrUtil::private_tcscat(szFile,i,agtrue);

			CAGmagicStrUtil::private_tcscat(szFile,_T("-"),agtrue);
			CAGmagicStrUtil::private_tcscat(szFile,j,agtrue);

			CAGmagicStrUtil::private_tcscat(szFile,_T("."),agtrue);
			agtchar	ext[64];
			CAGmagicStrUtil::private_tcscat(szFile,CAGimageMicUtil::FindFileTypeStr(imagetype,ext),agtrue);

			pAGimage->Save(szFile,imagetype);
			if(szFile)	free(szFile);
		}
	}
	return agtrue;
}

/*******************************class CAGimageDBUtil*******************************/
#include "AGimageSeg.h"
void CAGimageDBUtil::EraseDB(void* pDBCnnI)
{
	for(agint32 i=CAGmagicIPConfUtil::AGmagicIP_Global_nTables-1; i>=0; i--)
	{
		if(!CAGmagicIPConfUtil::AGmagicIP_Global_bTables[i])	continue;
		if(_tcsicmp(CAGmagicIPConfUtil::AGmagicIP_Global_Tables[i],_T("Semantic"))==0)
			CAGimageSemanticTree::DBDeleteSemanticsRecure(pDBCnnI);

		agtchar* SQL=NULL;
		CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_Global_Tables[i],agtrue);
		CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
		if(SQL) free(SQL); SQL=NULL;
	}
}
struct INSERT_IMAGE_TO_DB_PARAM
{
	void*		pDBCnnI;
	aguint_id	ImageType;

	agbool		bIsInsertFeatures;
	agbool		bIsNormWhenInsertFeatures;
	agbool		bIsInsertAff;
	agbool		bIsNegativeImageWhenSegment;
};

void privateInsertImageToDB(void* pAtt, void* szPath, void* pReserved)
{

	agtchar* URL=(agtchar*)szPath;
	if(URL==NULL)	return;

	INSERT_IMAGE_TO_DB_PARAM  InsertParam;
	memcpy(&InsertParam,(INSERT_IMAGE_TO_DB_PARAM*)pReserved,sizeof(INSERT_IMAGE_TO_DB_PARAM));

	void*			pDBCnnI=InsertParam.pDBCnnI;
	aguint_id		ImageType=InsertParam.ImageType;

	CAGimageDBItem	item;
	item.DBCnnAttach(pDBCnnI);
	item.SetIsStoreImage(agtrue);
	if(!item.LoadURL(URL))	return;
	agtchar* brief_url=CAGmagicIOUtil::ConvertAndAllocBriefURL(URL);
	item.AllocURL(brief_url);
	if(brief_url)	free(brief_url);
	item.m_ImageType=ImageType;

	InsertParam.bIsNegativeImageWhenSegment=CAGmagicConfUtil::IsNegativeImageWhenSegment(ImageType);
	AGMAGICIP_DEFAULT_SEGS_CLASS segs;
	item.DBInsert(InsertParam.bIsInsertFeatures, InsertParam.bIsNormWhenInsertFeatures, 
		InsertParam.bIsInsertAff, InsertParam.bIsNegativeImageWhenSegment,&segs);
}
void CAGimageDBUtil::AddToDBFromURL(agtchar url[], aguint_id ImageType, void* pDBCnnI)
{
	if(url==NULL || pDBCnnI==NULL)	return;

	agtchar exts[1024];
	CAGimageIOUtil::GetAllSupportImageExt(exts,AGMAGIC_OR_SEPS);

	INSERT_IMAGE_TO_DB_PARAM Param;
	memset(&Param,0,sizeof(INSERT_IMAGE_TO_DB_PARAM));
	Param.pDBCnnI=pDBCnnI;
	Param.ImageType=ImageType;
	Param.bIsInsertFeatures=agtrue;
	Param.bIsNormWhenInsertFeatures=agtrue;
	Param.bIsInsertAff=agfalse;
	Param.bIsNegativeImageWhenSegment=agfalse;

	CAGmagicIOUtil::SimpleBrowseFiles(
						privateInsertImageToDB,
						url,
						exts,
						AGMAGIC_OR_SEPS,
						&Param
					);
}
#include "AGimageFeat.h"
void CAGimageDBUtil::CreateDBFromURL(agtchar base_url[], void* pDBCnnI)
{
	EraseDB(pDBCnnI);
	agint32 i;

	agtchar* SQL=NULL;
	//CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO IMAGESTYPE(ID,DESCRIPTION) VALUES(0, "),agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,_T("General"),agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	//CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	//CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	//if(SQL) free(SQL); SQL=NULL;
	for(i=0; i<CAGmagicConfUtil::nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO IMAGESTYPE(ID,DESCRIPTION) VALUES("),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,CAGmagicConfUtil::idAGmagic_GlobalSampleImagesDirNames[i],agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(", "),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,CAGmagicConfUtil::AGmagic_GlobalSampleImagesDirNames[i],agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
		CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
		if(SQL) free(SQL); SQL=NULL;
	}

	for(i=0; i<CAGmagicConfUtil::nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		if(!CAGmagicConfUtil::bAGmagic_GlobalSampleImagesDirNames[i])
			continue;

		agtchar* url=NULL;
		CAGmagicStrUtil::private_tcscat(url,base_url,agtrue);
		CAGmagicStrUtil::private_tcscat(url,AGMAGIC_DIR_SPLASH,agtrue);
		CAGmagicStrUtil::private_tcscat(url,CAGmagicConfUtil::AGmagic_GlobalSampleImagesDirNames[i],agtrue);
		AddToDBFromURL(url,CAGmagicConfUtil::idAGmagic_GlobalSampleImagesDirNames[i],pDBCnnI);
		if(url) free(url); url=NULL;
	}

	CAGimageAffMatrix::DeleteAllAffInDB(pDBCnnI);
	for(i=0; i<CAGmagicConfUtil::nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		if(!CAGmagicConfUtil::bAGmagic_GlobalSampleImagesDirNames[i])
			continue;
		CAGimageAffMatrix::CreateAffInDB(pDBCnnI,CAGmagicConfUtil::idAGmagic_GlobalSampleImagesDirNames[i]);
	}

	CAGimageSemanticTree::DBResetAndInsertSampleTopLevelSemantics(pDBCnnI);
	CAGimageSemanticTree::DBResetAndInsertSampleTopLevelImageIDs(pDBCnnI);
}
agbool CAGimageDBUtil::Load(aguint_id ImageID, void* pDBCnnI, CAGimage* pOutAGimage)
{
	if(pOutAGimage==NULL)	throw _T("Parameter invalid");

	agtchar* SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);

	agtchar* URL=NULL;
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);
		free(SQL);
		if((pRs->EndOfFile))	return agfalse;
		
		//URL
		_variant_t	varValue = pRs->Fields->GetItem(_T("URL"))->Value;
		pRs->Close();

		CAGmagicMicUtil::AGconvertFromVariantToStr(varValue,URL);
	}
	catch(_com_error &e)
	{
		CAGmagicDBUtil::DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
	if(URL==NULL)	return agfalse;

	if(!pOutAGimage->Load(URL))
	{
		free(URL);
		return agfalse;
	}
	pOutAGimage->m_ID=ImageID;
	free(URL);
	return agtrue;
}
agbool	CAGimageDBUtil::FindImageID(void* pDBCnnI, aguint_id ImageType, agtchar szName[], agtchar szURL[], CAGidArray* ImageIDs)
{
	if(pDBCnnI==NULL || ImageIDs==NULL)	throw _T("Invalid parameter");
	ImageIDs->RemoveAll();

	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ID FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Type="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageType,agtrue);

	if(szName!=NULL)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(" AND Name="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,szName,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}	
	if(szURL!=NULL)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(" AND URL="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,szURL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}

	agint32			fieldsNum, recordNums;
	aguint_id**		data=NULL;
	if(!AGdbRead(pDBCnnI,SQL,agfalse,data,fieldsNum,recordNums))
		return agfalse;
	if(fieldsNum!=1)	throw _T("Error database");

	ImageIDs->SetSize(recordNums);
	for(agint32 i=0; i<recordNums; i++)
	{
		ImageIDs->SetAt(i,data[i][0]);
		free(data[i]);
	}
	free(data);
	return agtrue;
}
agbool	CAGimageDBUtil::FindImage(void* pDBCnnI, agtchar szName[], agtchar szURL[], CAGidTypeArray* ImageIDTypes)
{
	if(pDBCnnI==NULL || ImageIDTypes==NULL)	throw _T("Invalid parameter");
	ImageIDTypes->RemoveAll();

	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT ID, Type FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);

	if(szName!=NULL)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE Name="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,szName,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}	
	if(szURL!=NULL)
	{
		if(szName!=NULL)
			CAGmagicStrUtil::private_tcscat(SQL,_T(" AND URL="),agtrue);
		else
			CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE URL="),agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,szURL,agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,AG_DAU_NHAY_CSDL,agtrue);
	}

	agint32			fieldsNum, recordNums;
	aguint_id**		data=NULL;
	if(!AGdbRead(pDBCnnI,SQL,agfalse,data,fieldsNum,recordNums))
		return agfalse;
	if(fieldsNum!=2)	throw _T("Error database");

	ImageIDTypes->SetSize(recordNums);
	for(agint32 i=0; i<recordNums; i++)
	{
		IMAGE_ID_TYPE	ImageIDType;
		ImageIDType.ImageID=data[i][0];
		ImageIDType.ImageType=data[i][1];
		ImageIDTypes->SetAt(i,ImageIDType);
		free(data[i]);
	}
	free(data);
	return agtrue;
}
agbool CAGimageDBUtil::FindImageIntel(void* pDBCnnI, agtchar szBaseSampleDir[], agtchar szDirTypeName[], agtchar szImageName[], CAGidTypeArray* ImageIDTypes)
{
	if(pDBCnnI==NULL || ImageIDTypes==NULL)			throw _T("Invalid parameter");
	ImageIDTypes->RemoveAll();
	if(szImageName==NULL||szBaseSampleDir==NULL)	return agfalse;

	agtchar*	base_sample_dir=CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute();

	agtchar*	FullURL=NULL;
	CAGmagicStrUtil::private_tcscat(FullURL,szBaseSampleDir,agtrue);
	if(szDirTypeName)
	{
		CAGmagicStrUtil::private_tcscat(FullURL,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(FullURL,szDirTypeName,agtrue);
	}
	if(szImageName)
	{
		CAGmagicStrUtil::private_tcscat(FullURL,AGMAGIC_DIR_SPLASH_STR,agtrue);
		CAGmagicStrUtil::private_tcscat(FullURL,szImageName,agtrue);
	}
	agtchar*	brief_url=CAGmagicIOUtil::ConvertAndAllocBriefURL(FullURL);
	if(FullURL) free(FullURL);

	if(szDirTypeName==NULL || base_sample_dir==NULL || _tcsicmp(szBaseSampleDir,base_sample_dir)!=0)
	{
		agbool bResult=FindImage(pDBCnnI, szImageName, brief_url, ImageIDTypes);
		if(base_sample_dir)	free(base_sample_dir);
		if(brief_url)		free(brief_url);
		return bResult;
	}
	aguint_id	ImageType=CAGmagicConfUtil::GetTypeOfSampleImagesDirNames(szDirTypeName);
	if(ImageType==0)
	{
		if(base_sample_dir)	free(base_sample_dir);
		if(brief_url)		free(brief_url);
		return agfalse;
	}

	
	CAGidArray	ids;
	CAGimageDBUtil::FindImageID(pDBCnnI, ImageType, szImageName, brief_url, &ids);
	agint32	n=ids.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		IMAGE_ID_TYPE	ImageIDType;
		ImageIDType.ImageID=ids.GetAt(i);
		ImageIDType.ImageType=ImageType;
		ImageIDTypes->Add(ImageIDType);
	}

	if(base_sample_dir)	free(base_sample_dir);
	if(brief_url)		free(brief_url);
	return (ImageIDTypes->GetSize()>0);
}
agbool CAGimageDBUtil::FindImageIntel(void* pDBCnnI, agtchar szImagePath[], CAGidTypeArray* ImageIDTypes)
{
	if(pDBCnnI==NULL || ImageIDTypes==NULL)		throw _T("Invalid parameter");
	ImageIDTypes->RemoveAll();
	if(szImagePath==NULL)						return agfalse;

	agtchar*	szImageName=NULL;
	agtchar*	szBaseSampleDir=NULL;
	agtchar*	szDirTypeName=NULL;

	CAGimageIOUtil::AnalyzeImagePathAndAlloc(szImagePath,szBaseSampleDir, szDirTypeName, szImageName);
	agbool bResult=FindImageIntel(pDBCnnI, szBaseSampleDir, szDirTypeName, szImageName, ImageIDTypes);

	if(szImageName)		free(szImageName);
	if(szBaseSampleDir) free(szBaseSampleDir);
	if(szDirTypeName)	free(szDirTypeName);
	return bResult;
}
void CAGimageDBUtil::ResetAffInDB(void* pDBCnnI)
{
	if(pDBCnnI==NULL)	throw _T("Invalid paramter");
	agtchar*	SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesAffinity SET MEASURE=1"),agtrue);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;

	////////////////////////////////////
	CAGidArray OutIDs;
	ReadAllImagesIDs(pDBCnnI, 0, &OutIDs);
	agint32 n=OutIDs.GetSize();
	if(n==0)	return;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesNormAffinity SET MEASURE="),agtrue);
	AG_private_tcscat_number(SQL,(agfreal)1/(agfreal)n, agtrue);
	CAGmagicDBUtil::ExcuteSQL(pDBCnnI,SQL,agfalse);
	if(SQL)	free(SQL);	SQL=NULL;
}
void CAGimageDBUtil::ReadAllImagesIDs(void* pDBCnnI, aguint_id ImageType, CAGidArray* OutIDs)
{
	if(pDBCnnI==NULL || OutIDs==NULL)	throw _T("Invalid paramter");
	OutIDs->RemoveAll();

	agtchar* SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM "),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,CAGmagicIPConfUtil::AGmagicIP_GlobalCurImageTable,agtrue);
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
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);
		if(SQL)	free(SQL); SQL=NULL;
		agint32 n=AGadodbGetRecordCount((_Recordset*)pRs,agfalse);

		agint32 count=0;
		OutIDs->SetSize(n);
		while(!(pRs->EndOfFile))
        {
			//ID
			_variant_t	varValue = pRs->Fields->GetItem(_T("ID"))->Value;
			OutIDs->SetAt(count,CAGmagicMicUtil::AGconvertFromVariantToID(varValue));

			pRs->MoveNext();
			count++;
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
}

/*******************************class CAGimageColorUtil*******************************/
agint32	CAGimageColorUtil::GradianByteToDegree(aguint8 gradian_byte)//trong he HSL
{
	return ((agint32)gradian_byte*(agint32)360) / (agint32)255;
}
aguint8	CAGimageColorUtil::DegreeToGradianByte(agint32 degree)//Trong he HSL
{
	return (aguint8)((degree*255) / 360);
}
CAGimageColorUtil::hsv_13primary_color CAGimageColorUtil::HSV13PrimaryReduce(AGCLRQUAD hsv)
{
	aguint8	h=hsv.rgbRed;
	aguint8	s=hsv.rgbGreen;
	aguint8 v=hsv.rgbBlue;

	agint32 h_degree=GradianByteToDegree(h);
	if(s<20 && 85<=v)				return hsv_white;
	else if( v==25 )				return hsv_black;//day la phan mo rong, khong co trong danh sach
	else if( v<25 )					return hsv_black;
	else if( s<20 && 25<v && v<85 )	return hsv_gray;
	else if( ((350<=h_degree && h_degree<=360)||(0<=h_degree && h_degree<25)) && 20<=s && 25<=v)
		return hsv_red;
	else if( 25<=h_degree && h_degree<45 && 20<=s && 25<=v )
		return hsv_red_yellow;
	else if( 45<=h_degree && h_degree<65 && 20<=s && 25<=v )
		return hsv_yellow;
	else if( 65<=h_degree && h_degree<85 && 20<=s && 25<=v )
		return hsv_yellow_green;
	else if( 85<=h_degree && h_degree<160 && 20<=s && 25<=v )
		return hsv_green;
	else if( 160<=h_degree && h_degree<180 && 20<=s && 25<=v )
		return hsv_green_blue;
	else if( 180<=h_degree && h_degree<270 && 20<=s && 25<=v )
		return hsv_blue;
	else if( 270<=h_degree && h_degree<290 && 20<=s && 25<=v )
		return hsv_blue_purple;
	else if( 290<=h_degree && h_degree<330 && 20<=s && 25<=v )
		return hsv_purple;
	else if( 330<=h_degree && h_degree<350 && 20<=s && 25<=v )
		return hsv_purple_red;
	else
		return (CAGimageColorUtil::hsv_13primary_color)-1;
}
agbool CAGimageColorUtil::HSV13PrimaryGetHisto(CAGimage* pAGimage, agint32 histo[AG_HSV_13PRIMARY_COLOR])
{
	if(pAGimage==NULL || histo==NULL)	throw _T("Invalid parameter");
	if (!pAGimage->IsValid())			return agfalse;

	memset(histo,0,AG_HSV_13PRIMARY_COLOR*sizeof(agint32));

	agint_xcoord	xmin,xmax;
	agint_bu_ycoord ymin,ymax;
	if (pAGimage->SelectionIsValid())
	{
		RECT rSelectionBox={0,0,0,0};
		pAGimage->SelectionGetBox(rSelectionBox);
		xmin = rSelectionBox.left;		xmax = rSelectionBox.right;
		ymin = rSelectionBox.bottom;	ymax = rSelectionBox.top;
	}
	else
	{
		xmin = ymin = 0;
		xmax = pAGimage->GetWidth(); ymax=pAGimage->GetHeight();
	}

	AGCLRQUAD color;
	for(agint_bu_ycoord y=ymin; y<ymax; y++)
	{
		for(agint_bu_ycoord x=xmin; x<xmax; x++)
		{
#if CXIMAGE_SUPPORT_SELECTION
			if (pAGimage->SelectionIsInside(x,y))
#endif //CXIMAGE_SUPPORT_SELECTION
			{
				switch (pAGimage->GetColorSpace())
				{
					case AGMAGICIP_COLORSPACE_RGB:
						color = pAGimage->RGBtoHSL(pAGimage->GetPixelColor(x,y));
						break;
					case AGMAGICIP_COLORSPACE_HSL:
						color = pAGimage->GetPixelColor(x,y);
						break;
					case AGMAGICIP_COLORSPACE_YUV:
						color = pAGimage->COLORSPACEtoCOLORSPACE(AGMAGICIP_COLORSPACE_YUV, AGMAGICIP_COLORSPACE_HSL, pAGimage->GetPixelColor(x,y));
						break;
					case AGMAGICIP_COLORSPACE_YIQ:
						color = pAGimage->COLORSPACEtoCOLORSPACE(AGMAGICIP_COLORSPACE_YIQ, AGMAGICIP_COLORSPACE_HSL, pAGimage->GetPixelColor(x,y));
						break;
					case AGMAGICIP_COLORSPACE_XYZ:
						color = pAGimage->COLORSPACEtoCOLORSPACE(AGMAGICIP_COLORSPACE_XYZ, AGMAGICIP_COLORSPACE_HSL, pAGimage->GetPixelColor(x,y));
						break;
					case AGMAGICIP_COLORSPACE_CMYK:
						color = pAGimage->COLORSPACEtoCOLORSPACE(AGMAGICIP_COLORSPACE_CMYK, AGMAGICIP_COLORSPACE_HSL, pAGimage->GetPixelColor(x,y));
						break;
					default:
						return agfalse;
				}
				agint32 idx=HSV13PrimaryGetIndexInEnum(HSV13PrimaryReduce(color));
				if(idx!=-1)//neu co that su index nay
					histo[idx]++;
			}
		}
	}
	return agtrue;
}
agint32 CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_13primary_color color)
{
	switch(color)
	{
		case hsv_white:
			return 0;
		case hsv_black:
			return 1;
		case hsv_gray:
			return 2;
		case hsv_red:
			return 3;
		case hsv_red_yellow:
			return 4;
		case hsv_yellow:
			return 5;
		case hsv_yellow_green:
			return 6;
		case hsv_green:
			return 7;
		case hsv_green_blue:
			return 8;
		case hsv_blue:
			return 9;
		case hsv_blue_purple:
			return 10;
		case hsv_purple:
			return 11;
		case hsv_purple_red:
			return 12;
	}
	return -1;
}
agint32	CAGimageColorUtil::PalFindColorIndex(AGCLRQUAD clr, AGCLRQUAD Pal[], agint32 nPal)
{
	if(Pal==NULL || nPal==NULL) throw _T("Invalid parameter");
	for(agint32 i=0; i<nPal; i++)
	{
		AGCLRQUAD clr2=Pal[i];
		if(clr2.rgbRed==clr.rgbRed && clr2.rgbGreen==clr.rgbGreen && clr2.rgbBlue==clr.rgbBlue)
			return i;
	}
	return -1;
}
agint32 CAGimageColorUtil::PalFindNearestColorIndexByEucDis(AGCLRQUAD clr, AGCLRQUAD Pal[], agint32 nPal)
{
	if(Pal==NULL || nPal==NULL) throw _T("Invalid parameter");
	agint32		idx=0;
	AGCLRQUAD	clr2=Pal[idx];
	agreal64 min_dis=AG_EUC_DIS_NOTSQRT_2(clr2.rgbRed-clr.rgbRed,clr2.rgbGreen-clr.rgbGreen,clr2.rgbBlue-clr.rgbBlue);

	if(min_dis==0) return idx;
	for(agint32 i=idx+1; i<nPal; i++)
	{
		clr2=Pal[i];
		agreal64   dis=AG_EUC_DIS_NOTSQRT_2(clr2.rgbRed-clr.rgbRed,clr2.rgbGreen-clr.rgbGreen,clr2.rgbBlue-clr.rgbBlue);
		if(dis==0) return i;
		if(min_dis > dis)
		{
			min_dis=dis;
			idx=i;
		}
	}
	return idx;
}
agbool CAGimageColorUtil::LutByEucDis(CAGimage* pInOutAGimage, AGCLRQUAD Lut[], agint32 nLut)
{
	if(pInOutAGimage==NULL || Lut==NULL || nLut==NULL) throw _T("Invalid parameter");

	agint32			pal_size=pInOutAGimage->GetPaletteSize();
	if(pal_size!=0)	pInOutAGimage->SetPalette(Lut,nLut);
	agint32			clr_used=AGMIN(pal_size,nLut);

	AGBU_RECT	rc;
	if (pInOutAGimage->SelectionIsValid())
	{
		RECT sel_box;
		pInOutAGimage->SelectionGetBox(sel_box);
		COPY_RECT_TO_RECT(rc,sel_box)
	}
	else
	{
		rc.left= rc.bottom = 0;
		rc.right = pInOutAGimage->GetWidth(); 
		rc.top	= pInOutAGimage->GetHeight();
	}

	for(agint_bu_ycoord y=rc.bottom; y<rc.top; y++){
		for(agint_xcoord x=rc.left; x<rc.right; x++){
		#if CXIMAGE_SUPPORT_SELECTION
			if (pInOutAGimage->SelectionIsInside(x,y))
		#else
			if (pInOutAGimage->IsInside(x,y))
		#endif //CXIMAGE_SUPPORT_SELECTION
			{
				AGCLRQUAD clr=pInOutAGimage->GetPixelColor(x,y);
				agint32 idx=PalFindNearestColorIndexByEucDis(clr, Lut, nLut);
				if(pal_size==0)//Khong dung bang mau
					pInOutAGimage->SetPixelColor(x,y,Lut[idx]);
				else
					pInOutAGimage->SetPixelIndex(x,y,(BYTE)AGMIN(idx,clr_used-1));
			}
		}
	}
	return agtrue;
}
int CAGimageColorUtil::RGBCompareGray(const void* pRGB1, const void* pRGB2)
{
	AGCLRQUAD *rgb1=(AGCLRQUAD*)pRGB1, *rgb2=(AGCLRQUAD*)pRGB2;
	agint32 gray1=RGB2GRAY(rgb1->rgbRed,rgb1->rgbGreen,rgb1->rgbBlue);
	agint32 gray2=RGB2GRAY(rgb2->rgbRed,rgb2->rgbGreen,rgb2->rgbBlue);
	return gray1-gray2;
}
void CAGimageColorUtil::RGBPalSort(AGCLRQUAD Pal[], agint32 nPal)
{
	if(Pal==NULL || nPal==NULL) throw _T("Invalid parameter");
	qsort((void*)Pal,(size_t)nPal,sizeof(AGCLRQUAD),(agcmpfunc)RGBCompareGray);
}
void CAGimageColorUtil::RGB25PrimaryFillPal(AGCLRQUAD pal[AG_RGB_25PRIMARY_COLOR])
{
	pal[0].rgbRed=0;			pal[1].rgbRed=0;		pal[2].rgbRed=0;
	pal[0].rgbGreen=0;			pal[1].rgbGreen=182;	pal[2].rgbGreen=255;
	pal[0].rgbBlue=0;			pal[1].rgbBlue=0;		pal[2].rgbBlue=170;
	pal[0].rgbReserved=0;		pal[1].rgbReserved=0;	pal[2].rgbReserved=0;
	
	pal[3].rgbRed=36;			pal[4].rgbRed=36;		pal[5].rgbRed=36;
	pal[3].rgbGreen=73;			pal[4].rgbGreen=146;	pal[5].rgbGreen=255;
	pal[3].rgbBlue=0;			pal[4].rgbBlue=170;		pal[5].rgbBlue=0;
	pal[3].rgbReserved=0;		pal[4].rgbReserved=0;	pal[5].rgbReserved=0;

	pal[6].rgbRed=73;			pal[7].rgbRed=73;		pal[8].rgbRed=73;
	pal[6].rgbGreen=36;			pal[7].rgbGreen=146;	pal[8].rgbGreen=219;
	pal[6].rgbBlue=170;			pal[7].rgbBlue=0;		pal[8].rgbBlue=170;
	pal[6].rgbReserved=0;		pal[7].rgbReserved=0;	pal[8].rgbReserved=0;

	pal[9].rgbRed=109;			pal[10].rgbRed=109;		pal[11].rgbRed=109;
	pal[9].rgbGreen=36;			pal[10].rgbGreen=109;	pal[11].rgbGreen=219;
	pal[9].rgbBlue=0;			pal[10].rgbBlue=170;	pal[11].rgbBlue=0;
	pal[9].rgbReserved=0;		pal[10].rgbReserved=0;	pal[11].rgbReserved=0;

	pal[12].rgbRed=146;			pal[13].rgbRed=146;		pal[14].rgbRed=146;
	pal[12].rgbGreen=0;			pal[13].rgbGreen=109;	pal[14].rgbGreen=182;
	pal[12].rgbBlue=170;		pal[13].rgbBlue=0;		pal[14].rgbBlue=170;
	pal[12].rgbReserved=0;		pal[13].rgbReserved=0;	pal[14].rgbReserved=0;

	pal[15].rgbRed=182;			pal[16].rgbRed=182;		pal[17].rgbRed=182;
	pal[15].rgbGreen=0;			pal[16].rgbGreen=73;	pal[17].rgbGreen=182;
	pal[15].rgbBlue=0;			pal[16].rgbBlue=170;	pal[17].rgbBlue=0;
	pal[15].rgbReserved=0;		pal[16].rgbReserved=0;	pal[17].rgbReserved=0;

	pal[18].rgbRed=182;			pal[19].rgbRed=219;		pal[20].rgbRed=219;
	pal[18].rgbGreen=255;		pal[19].rgbGreen=73;	pal[20].rgbGreen=146;
	pal[18].rgbBlue=170;		pal[19].rgbBlue=0;		pal[20].rgbBlue=170;
	pal[18].rgbReserved=0;		pal[19].rgbReserved=0;	pal[20].rgbReserved=0;

	pal[21].rgbRed=219;			pal[22].rgbRed=255;		pal[23].rgbRed=255;
	pal[21].rgbGreen=255;		pal[22].rgbGreen=36;	pal[23].rgbGreen=146;
	pal[21].rgbBlue=0;			pal[22].rgbBlue=170;	pal[23].rgbBlue=0;
	pal[21].rgbReserved=0;		pal[22].rgbReserved=0;	pal[23].rgbReserved=0;

	pal[24].rgbRed=255;
	pal[24].rgbGreen=255;
	pal[24].rgbBlue=255;
	pal[24].rgbReserved=0;
}
agbool CAGimageColorUtil::RGB25PrimaryLut(CAGimage* pInOutAGimage/*, agbool bIsSortLut*/)
{
	AGCLRQUAD pal_25Prime[AG_RGB_25PRIMARY_COLOR];
	RGB25PrimaryFillPal(pal_25Prime);
	//if(bIsSortLut)
	//	RGBPalSort(pal_25Prime,AG_RGB_25PRIMARY_COLOR);
	if(pInOutAGimage->GetColorSpace()!=AGMAGICIP_COLORSPACE_RGB)
		pInOutAGimage->SetColorSpace(AGMAGICIP_COLORSPACE_RGB,agtrue);
	return LutByEucDis(pInOutAGimage, pal_25Prime, AG_RGB_25PRIMARY_COLOR);
}
agbool CAGimageColorUtil::RGB25PrimaryGetHisto(CAGimage* pAGimage, agbool bIs25PrimaryImage, agint32 histo[AG_RGB_25PRIMARY_COLOR])
{
	if(pAGimage==NULL || histo==NULL)	throw _T("Invalid parameter");
	if (!pAGimage->IsValid())			return agfalse;
	memset(histo,0,AG_RGB_25PRIMARY_COLOR*sizeof(agint32));

	AGCLRQUAD pal_25Prime[AG_RGB_25PRIMARY_COLOR];
	RGB25PrimaryFillPal(pal_25Prime);

	agint_xcoord	xmin,xmax;
	agint_bu_ycoord ymin,ymax;
	if (pAGimage->SelectionIsValid())
	{
		RECT rSelectionBox={0,0,0,0};
		pAGimage->SelectionGetBox(rSelectionBox);
		xmin = rSelectionBox.left;		xmax = rSelectionBox.right;
		ymin = rSelectionBox.bottom;	ymax = rSelectionBox.top;
	}
	else
	{
		xmin = ymin = 0;
		xmax = pAGimage->GetWidth(); ymax=pAGimage->GetHeight();
	}

	AGCLRQUAD color;
	for(agint_bu_ycoord y=ymin; y<ymax; y++)
	{
		for(agint_bu_ycoord x=xmin; x<xmax; x++)
		{
#if CXIMAGE_SUPPORT_SELECTION
			if (pAGimage->SelectionIsInside(x,y))
#endif //CXIMAGE_SUPPORT_SELECTION
			{
				color = pAGimage->GetPixelColor(x,y);
				agint32 idx;
				if(bIs25PrimaryImage)
					idx=PalFindColorIndex(color,pal_25Prime,AG_RGB_25PRIMARY_COLOR);
				else
					idx=PalFindNearestColorIndexByEucDis(color,pal_25Prime,AG_RGB_25PRIMARY_COLOR);
				if(idx!=-1)//neu co that su index nay
					histo[idx]++;
			}
		}
	}
	return agtrue;
}
/*******************************class CAGimageDrawUtil*******************************/
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
void CALLBACK LineDDAProc2(int x, int y, CAGimageDrawUtil::LineDDA_DrawStruct* pDrawStruct)
{
	HDC hDC=(HDC)(pDrawStruct->m_pDrawTool);
	if(hDC)
	{
		pDrawStruct->m_SelCount++;
		if (pDrawStruct->m_SelCount <= 4)
			SetPixelV(hDC,x,y,RGB(255,255,255));
		else SetPixelV(hDC,x,y,RGB(0,0,0));
		if (pDrawStruct->m_SelCount == 8)
			pDrawStruct->m_SelCount=0;
	}
}
#endif //AGMAGIC_OS_TYPE

void CAGimageDrawUtil::LineDDA_Screen(LineDDA_DrawStruct* pDrawStruct, AGBU_POINT pts[], agint32 n_pts, agreal64 zoom, POINT start_pos)
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	if(pDrawStruct==NULL || pts==NULL || n_pts==0)
		throw _T("Invalid parameter");

	HDC hDC=(HDC)(pDrawStruct->m_pDrawTool);
	if (n_pts>2)
	{
		pDrawStruct->m_SelCount=pDrawStruct->m_SelShift;
//		pDC->MoveTo(zoom*pts[0].x - start_pos.x,zoom*pts[0].y - start_pos.y);
		for(int i=1;i<n_pts;i++){
//			pDC->LineTo(zoom*pts[i].x - start_pos.x,zoom*pts[i].y - start_pos.y);
			LineDDA((int)(zoom*pts[i-1].x - start_pos.x),
				    (int)(zoom*pts[i-1].y - start_pos.y),
					(int)(zoom*pts[i].x - start_pos.x),
					(int)(zoom*pts[i].y - start_pos.y),
					(LINEDDAPROC)LineDDAProc2,(LPARAM)hDC);
		}
	}
#else	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
#error _T("Implement not yet")
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
}

/*******************************class CQuantizer*******************************/

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
//#include "../lib/CQuantizer/Quantize.cpp"
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

