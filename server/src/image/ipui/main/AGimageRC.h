#if !defined(AGIMAGE_RC_H)
#define AGIMAGE_RC_H
#define AGMAGIC_USE_DEFS_BRIEFLY
#include "../../ip/main/AGimageDefs.h"
#undef AGMAGIC_USE_DEFS_BRIEFLY

#if AGMAGIC_SUPPORT_MFC

#if AGMAGIC_CXIMAGE_VER==5991
#if AGMAGIC_DEV_ENV==AGMAGIC_MSVC
#include "../../ip/lib/cximage/599a/windows/msvc/demo/resource.h"
#else //AGMAGIC_DEV_ENV
#error "Implement not yet"
#endif //AGMAGIC_DEV_ENV
	
#elif AGMAGIC_CXIMAGE_VER==5993 //AGMAGIC_CXIMAGE_VER
#if AGMAGIC_DEV_ENV==AGMAGIC_MSVC
#include "../../ip/lib/cximage/599c/windows/msvc/demo/resource.h"
#else //AGMAGIC_DEV_ENV
#error "Implement not yet"
#endif //AGMAGIC_DEV_ENV

#else //AGMAGIC_CXIMAGE_VER
#error "Implement not yet"
#endif //AGMAGIC_CXIMAGE_VER

//icon	
#define IDI_AGMAGICIP_OK						IDI_OK
#define IDI_AGMAGICIP_CANC                   	IDI_CANC
#define IDI_AGMAGICIP_R                      	IDI_R
#define IDI_AGMAGICIP_G                      	IDI_G
#define IDI_AGMAGICIP_B                      	IDI_B
#define IDI_AGMAGICIP_GRAY                   	IDI_GRAY

//bitmap
#define IDB_AGMAGICIPBITMAP						IDB_BITMAP1

//menu
#define ID_AGMAGICIP_FROM_BITMAP				ID_IMAGE_FROM_BITMAP
#define ID_AGMAGICIP_LOADJPEGRESOURCE			ID_CXIMAGE_LOADJPEGRESOURCE
#define ID_AGMAGICIP_LOADICONRESOURCE			ID_CXIMAGE_LOADICONRESOURCE
#define ID_AGMAGICIP_LOADGIFRESOURCE			ID_CXIMAGE_LOADGIFRESOURCE
#define ID_AGMAGICIP_LOADPNGRESOURCE			ID_CXIMAGE_LOADPNGRESOURCE
#define ID_AGMAGICIP_LOADTIFRESOURCE			ID_CXIMAGE_LOADTIFRESOURCE

#define ID_AGMAGICIP_DEMOSAVEMULTIPAGETIFF		ID_CXIMAGE_DEMOSAVEMULTIPAGETIFF
#define ID_AGMAGICIP_DEMOSAVEANIMATEDGIF 		ID_CXIMAGE_DEMOSAVEANIMATEDGIF
#define ID_AGMAGICIP_DOWNLOADFROMURL			ID_CXIMAGE_DOWNLOADFROMURL
#define ID_AGMAGICIP_DEMOCREATEFROMARRAY		ID_CXIMAGE_DEMOCREATEFROMARRAY

#define ID_AGMAGICIP_MIRROR						ID_CXIMAGE_MIRROR
#define ID_AGMAGICIP_FLIP						ID_CXIMAGE_FLIP
#define ID_AGMAGICIP_ROTATEL					ID_CXIMAGE_ROTATEL
#define ID_AGMAGICIP_ROTATER					ID_CXIMAGE_ROTATER
#define ID_AGMAGICIP_ROTATE						ID_CXIMAGE_ROTATE

#define ID_AGMAGICIP_RESAMPLE					ID_CXIMAGE_RESAMPLE
#define ID_AGMAGICIP_CROP						ID_CXIMAGE_CROP

#define ID_AGMAGICIP_GRAYSCALE					ID_CXIMAGE_GRAYSCALE
#define ID_AGMAGICIP_DITHER						ID_CXIMAGE_DITHER
#define ID_AGMAGICIP_FFT						ID_CXIMAGE_FFT
#define ID_AGMAGICIP_REPAIR						ID_CXIMAGE_REPAIR
#define ID_AGMAGICIP_MIX						ID_FILTERS_MIX
#define ID_AGMAGICIP_OPTIONS					ID_CXIMAGE_OPTIONS

#define ID_EFFECTS_BLUR_BLUR					ID_CXIMAGE_BLUR
#define ID_EFFECTS_BLUR_SOFTEN					ID_CXIMAGE_SOFTEN
#define ID_EFFECTS_BLUR_GAUSSIAN3X3				ID_CXIMAGE_GAUSSIAN3X3
#define ID_EFFECTS_BLUR_GAUSSIAN5X5				ID_CXIMAGE_GAUSSIAN5X5

#define ID_EFFECTS_SHARPEN_SHARPEN				ID_CXIMAGE_SHARPEN
#define ID_EFFECTS_SHARPEN_UNSHARPMASK			0

#define ID_EFFECTS_EDGE_DILATE					ID_CXIMAGE_DILATE
#define ID_EFFECTS_EDGE_ERODE					ID_CXIMAGE_ERODE
#define ID_EFFECTS_EDGE_EDGE					ID_CXIMAGE_EDGE

#define ID_EFFECTS_NOISE_ADDNOISE				ID_CXIMAGE_ADDNOISE
#define ID_EFFECTS_NOISE_JITTER					ID_CXIMAGE_JITTER
#define ID_EFFECTS_NOISE_MEDIAN					ID_CXIMAGE_MEDIAN

#define ID_EFFECTS_ARTISTIC_CONTOUR				ID_CXIMAGE_CONTOUR

#define ID_EFFECTS_GEOMETRIC_PINCH				ID_CXIMAGE_CIRCLETRANSFORM_PINCH
#define ID_EFFECTS_GEOMETRIC_PUNCH				ID_CXIMAGE_CIRCLETRANSFORM_PUNCH
#define ID_EFFECTS_GEOMETRIC_SWIRL				ID_CXIMAGE_CIRCLETRANSFORM_SWIRL
#define ID_EFFECTS_GEOMETRIC_CYLINDER			ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER
#define ID_EFFECTS_GEOMETRIC_BATHROOM			ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM
#define ID_EFFECTS_GEOMETRIC_ELLIPSE			ID_TRANSFORM_ELLIPSE

#define ID_EFFECTS_TEXTURE_EMBOSS				ID_CXIMAGE_EMBOSS

#define ID_COLORS_ADJUST_LIGHTEN				ID_CXIMAGE_LIGHTEN
#define ID_COLORS_ADJUST_DARKEN					ID_CXIMAGE_DARKEN
#define ID_COLORS_ADJUST_CONTRAST				ID_CXIMAGE_CONTRAST
#define ID_COLORS_ADJUST_LESSCONTRAST			ID_CXIMAGE_LESSCONTRAST
#define ID_COLORS_ADJUST_THRESHOLD				ID_CXIMAGE_THRESHOLD
#define ID_COLORS_COLORIZE						ID_CXIMAGE_COLORIZE
#define ID_COLORS_GAMMA							ID_CXIMAGE_GAMMA

#define ID_COLORS_HISTOGRAM_STRETCH				ID_CXIMAGE_HISTOGRAM_STRETCH
#define ID_COLORS_HISTOGRAM_STRETCH1			ID_CXIMAGE_HISTOGRAM_STRETCH1
#define ID_COLORS_HISTOGRAM_STRETCH2			ID_CXIMAGE_HISTOGRAM_STRETCH2
#define ID_COLORS_HISTOGRAM_EQUALIZE			ID_CXIMAGE_HISTOGRAM_EQUALIZE
#define ID_COLORS_HISTOGRAM_NORMALIZE			ID_CXIMAGE_HISTOGRAM_NORMALIZE
#define ID_COLORS_HISTOGRAM_LOG					ID_CXIMAGE_HISTOGRAM_LOG
#define ID_COLORS_HISTOGRAM_ROOT				ID_CXIMAGE_HISTOGRAM_ROOT

#define ID_COLORS_NEGATIVE						ID_CXIMAGE_NEGATIVE
#define ID_COLORS_PSEUDOCOLORS					ID_CXIMAGE_PSEUDOCOLORS

#define ID_COLORS_SPLIT							ID_FILTERS_SPLIT
#define ID_COLORS_SPLIT_SPLITRGB				ID_CXIMAGE_SPLITRGB
#define ID_COLORS_SPLIT_SPLITHSL				ID_CXIMAGE_SPLITHSL
#define ID_COLORS_SPLIT_SPLITYUV				ID_CXIMAGE_SPLITYUV
#define ID_COLORS_SPLIT_SPLITYIQ				ID_CXIMAGE_SPLITYIQ
#define ID_COLORS_SPLIT_SPLITXYZ				ID_CXIMAGE_SPLITXYZ
#define ID_COLORS_SPLIT_SPLITCMYK				ID_CXIMAGE_SPLITCMYK
#define ID_COLORS_COMBINE						ID_CXIMAGE_COMBINE

#define ID_COLORS_SPLITCHANNELS					ID_CXIMAGE_SPLITCHANNELS

#define ID_COLORS_SETTRANSPARENCY				ID_CXIMAGE_SETTRANSPARENCY
#define ID_COLORS_REMOVETRANSPARENCY			ID_CXIMAGE_REMOVETRANSPARENCY
#define ID_COLORS_ALPHA_OPACITY					ID_CXIMAGE_OPACITY
#define ID_COLORS_ALPHA_REMOVEALPHACHANNEL		ID_CXIMAGE_REMOVEALPHACHANNEL
#define ID_COLORS_ALPHA_ALPHACHANNEL_SPLIT		ID_CXIMAGE_ALPHACHANNEL_SPLIT
#define ID_COLORS_ALPHA_ALPHASTRIP				ID_CXIMAGE_ALPHASTRIP
#define ID_COLORS_ALPHA_INVERTALPHA				ID_CXIMAGE_INVETALPHA
#define ID_COLORS_ALPHA_ALPHAPALETTETOGGLE		ID_CXIMAGE_ALPHAPALETTETOGGLE
#define ID_COLORS_ALPHA_ALPHACREATE				ID_CXIMAGE_ALPHACREATE

#define ID_COLORS_DECREASEBPP					ID_CXIMAGE_DECREASEBPP
#define ID_COLORS_INCREASEBPP					ID_CXIMAGE_INCREASEBPP

//indicator of status bar
#define	ID_AGMAGICIPINDICATOR1					ID_INDICATOR1
#define	ID_AGMAGICIPINDICATOR2					ID_INDICATOR2
#define	ID_AGMAGICIPINDICATOR3					ID_INDICATOR3
#define	ID_AGMAGICIPINDICATOR4					ID_INDICATOR4

//String table
#define	ID_AGMAGICIP_RESOURCES					ID_CXIMAGE_RESOURCES

/***********************Phan rieng cua AGmagicIP*****************/
//main
#define IDR_AGMAGICIPMAINFRAME					11100
#define IDR_AGMAGICIPTYPE						11101

//bitmap 
#define	IDR_AGMAGICIP_JPG1						11105
#define	IDR_AGMAGICIP_JPG2						11106

//tool bar
#define IDM_AGMAGICIP_CONTEXT					11110
//menu
#define ID_SEGMENTATION_SEGMENT					11111
#define ID_SEGMENTATION_SEGMENT_INTEL           11112
#define ID_SEGMENTATION_SEGMENT_INVERSE         11113
#define ID_SEGMENTATION_SEGMENT_LOAD            11114
#define ID_SEGMENTATION_SHOW					11115
#define ID_SEGMENTATION_OPTION					11116
	
#define ID_DATABASE_INSERT                      11120
#define ID_DATABASE_UPDATE                      11121
#define ID_DATABASE_DELETE                      11122
#define ID_DATABASE_SELECT                      11123

#define	ID_HELP_TEST_AGMAGICIP					11130

//dialog & control
#define	IDD_AGMAGICIPABOUTBOX					11150

#define	IDD_AGMAGICIPDLL_SERIAL					11151
#define	IDC_AGMAGICDLL_SERIALKEY				11152

#define	IDD_AGMAGICIP_DEFAULT					11153


#endif	//#if AGMAGIC_SUPPORT_MFC
#endif	//#if !defined(AGIMAGE_RC_H)