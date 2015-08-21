#if !defined(AGIMAGEFEAT_H__5A13A0A5_EFBE_4EDE_930F_D1B9D2D813D6__INCLUDED_)
#define AGIMAGEFEAT_H__5A13A0A5_EFBE_4EDE_930F_D1B9D2D813D6__INCLUDED_

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif

#include "AGimage.h"
#include <time.h>
#include "../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../common/lib/agutil/main/AGdataStruct.h"
#include "../../../common/include/AGEND_INCLUDE_LIBRARY.h"


/********interface IAGimagefVec, class CAGimagefVec********/

/*
template<class agfdatatype> class IAGimagefVec
Chuc nang:
Cach dung:
Ghi chu:agfdatatype
*/
template<class agfdatatype>
class IAGimagefVec : public CAGarray<agfdatatype>, public CAGmagicDBOrg
{
public:
	IAGimagefVec() : CAGarray<agfdatatype>(), CAGmagicDBOrg()	{}
	virtual ~IAGimagefVec()										{}

	virtual aguint_id		GetImageID()								{throw _T("You must define");}
	virtual agbool			CreateFrom(CAGimage* pAGimageTempSrc, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs=NULL)		{throw _T("You must define");}
	virtual agfdatatype*	GetAtImageID(aguint_id ImageID)				{throw _T("You must define");}

	virtual agbool	DBRead(aguint_id ImageID, void* pReserved=NULL)	{throw _T("You must define");}//pReserved la time_t*, pReserved[0] va pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
	virtual agbool	DBInsert()										{throw _T("You must define");}
	virtual agbool	DBUpdate()										{throw _T("You must define");}
};

///////////////////////////////////////////////////////////////////////

template<class agfdatatype, aguint32 m_ftype> class CAGimagefMatrix;
class CAGimageAffMatrix;
class CAGaffArray;
class CAGtrainingDataSet;
class CAGmarkovModel;
class CAGmmSearchingSystem;
class CAGimageDBItem;

#if AGMAGIC_SUPPORT_MFC
class CAGmmTrainingSystemUIWinThread;
class CAGmagicISDemoMainFrame;
#endif

/*
template<class agfdatatype, aguint32 m_ftype> class CAGimagefVec
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class agfdatatype, aguint32 m_ftype>
class CAGimagefVec : public IAGimagefVec<agfdatatype>
{
protected:
	CAGidArray		m_aRelatedImageID;//mang RELATEDIMAGEID trong ImagesAffinity
	CAGtimeArray	m_aTime;//Mang thoi gian dung cho nhung muc dich dac biet
	aguint32		m_Reserved;
	aguint_id		m_ImageID;
////////////////////////////////////////////////////////////////////////////////////////
public:
	CAGimage*	m_pNoFreeTempAGimageSrc;

	agbool CopyFrom(const CAGimagefVec* xa);

public:
	CAGimagefVec();
	virtual ~CAGimagefVec();
	void	Destroy();
	virtual void RemoveAll();
	
	virtual aguint_id	GetImageID()	{return m_ImageID;};
	virtual agbool		CreateFrom(CAGimage* pAGimageTempSrc, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs=NULL);
	virtual agfdatatype*	GetAtImageID(aguint_id ImageID);

////////////////////////////////////////////////////////////////////////////////////////
protected:
	static	agtchar*	DBGet256ClrFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageID);
	static	agtchar*	DBGetClrTxtFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageID);
	static	agtchar*	DBGetAffinitySelectSQL(agtchar*& SQL, aguint_id ImageID, agbool bIsNorm);
	static	agtchar*	DBGetUserAccessPatternSelectSQL(agtchar*& SQL, aguint_id ImageID, time_t tAccessedBegin, time_t tAccessedEnd);
	static	agtchar*	DBGetUserAccessFreqSelectSQL(agtchar*& SQL, time_t tAccessedBegin, time_t tAccessedEnd);

	static	agtchar*	DBGet256ClrFeaturesInsertSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne);
	static	agtchar*	DBGetClrTxtFeaturesInsertSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne);
	static	agtchar*	DBGetAffinityInsertSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, agfdatatype measure, agbool bIsNorm);
	static	agtchar*	DBGetUserAccessPatternInsertSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed, agfdatatype isAccessed);
	static	agtchar*	DBGetUserAccessFreqInsertSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed, agfdatatype nAccessed);

	static	agtchar*	DBGet256ClrFeaturesUpdateSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne);
	static	agtchar*	DBGetClrTxtFeaturesUpdateSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne);
	static	agtchar*	DBGetAffinityUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, agfdatatype measure, agbool bIsNorm);//measure co the duoc chuan hoa, cung co the la khong
	static	agtchar*	DBGetUserAccessPatternUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed, agfdatatype isAccessed);
	static	agtchar*	DBGetUserAccessFreqUpdateSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed, agfdatatype nAccessed);
	
	static	agtchar*	DBGet256ClrFeaturesDeleteSQL(agtchar*& SQL, aguint_id ImageID);
	static	agtchar*	DBGetClrTxtFeaturesDeleteSQL(agtchar*& SQL, aguint_id ImageID);
	static	agtchar*	DBGetAffinityDeleteSQL(agtchar*& SQL, aguint_id ID, agbool bIDIsRelated, agbool bIsNorm);
	static	agtchar*	DBGetUserAccessPatternDeleteSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed);
	static	agtchar*	DBGetUserAccessFreqDeleteSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed);

public:
	virtual agbool	DBRead(aguint_id ImageID, void* pReserved=NULL);//pReserved[0] la RelatedImageID, pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
	virtual agbool	DBInsert();
	virtual agbool	DBUpdate();
	virtual agbool	DBDelete();

	friend class CAGimagefMatrix<agfdatatype,m_ftype>;
	friend class CAGaffArray;
	friend class CAGtrainingDataSet;
	friend class CAGimageAffMatrix;
	friend class CAGmarkovModel;
	friend class CAGmmSearchingSystem;
	friend class CAGimageDBItem;
#if AGMAGIC_SUPPORT_MFC
	friend class CAGmmTrainingSystemUIWinThread;
	friend class CAGmagicISDemoMainFrame;
#endif
};

template<class agfdatatype, aguint32 m_ftype>
CAGimagefVec<agfdatatype, m_ftype>::CAGimagefVec() : IAGimagefVec<agfdatatype>()
{
	m_Reserved=0;
	m_ImageID=0;
	m_pNoFreeTempAGimageSrc=NULL;
}

template<class agfdatatype, aguint32 m_ftype>
CAGimagefVec<agfdatatype, m_ftype>::~CAGimagefVec()
{
	Destroy();
}

template<class agfdatatype, aguint32 m_ftype>
void CAGimagefVec<agfdatatype, m_ftype>::Destroy()
{
	RemoveAll();
	m_Reserved=0;

	m_ImageID=0;
	m_pNoFreeTempAGimageSrc=NULL;
	DBCnnDetach();
}

template<class agfdatatype, aguint32 m_ftype>
void CAGimagefVec<agfdatatype, m_ftype>::RemoveAll()
{
	CAGarray<agfdatatype>::RemoveAll();
	m_aRelatedImageID.RemoveAll(); 
	m_aTime.RemoveAll();
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::CopyFrom(const CAGimagefVec* xa)
{
	if(!CAGarray<agfdatatype>::CopyFrom(xa)) return agfalse;
	m_aRelatedImageID.CopyFrom(&(xa->m_aRelatedImageID));
	m_aTime.CopyFrom(&(xa->m_aTime));
	m_Reserved=xa->m_Reserved;

	m_ImageID=xa->m_ImageID;
	m_pNoFreeTempAGimageSrc=xa->m_pNoFreeTempAGimageSrc;

	DBCnnAttach(xa->m_pDBCnnI);
	return agtrue;
}

//Ham rut trich dac trung
#include "AGimageUtil.h"
#include "AGimageSeg.h"
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::CreateFrom(CAGimage* pAGimageTempSrc, agbool bIsNegativeImageWhenSegment, CAGimageSegs* pSegs)
{
	RemoveAll();
	if(pAGimageTempSrc==NULL)	return agfalse;
	if(m_ftype==AGMAGICIP_256CLR_FEATURE)
	{
		long hr[256]; //histogram
		long hg[256];
		long hb[256];
		long hgray[256];
		memset(hr,0,256*sizeof(long));
		memset(hg,0,256*sizeof(long));
		memset(hb,0,256*sizeof(long));
		memset(hgray,0,256*sizeof(long));
		pAGimageTempSrc->Histogram(hr,hg,hb,hgray);

		SetSize(256);
		for(agint32 i=0; i<256; i++)
			m_vector[i]=(agfdatatype)(hgray[i]);
		if(IsNorm())
		{
			SetIsNorm(agfalse);
			Normalize();
		}
	}
	else if(m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		SetSize(21);

		agint32 histo[AG_HSV_13PRIMARY_COLOR];
		if(!CAGimageColorUtil::HSV13PrimaryGetHisto(pAGimageTempSrc,histo))	return agfalse;
		m_vector[0]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_black)];
		m_vector[0] +=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_gray)];
		m_vector[1]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_white)];
		m_vector[2]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_red)];
		m_vector[3]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_red_yellow)];
		m_vector[4]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_yellow)];
		m_vector[5]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_yellow_green)];
		m_vector[6]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_green)];
		m_vector[7]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_green_blue)];
		m_vector[8]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_blue)];
		m_vector[9]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_blue_purple)];
		m_vector[10]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_purple)];
		m_vector[11]=histo[CAGimageColorUtil::HSV13PrimaryGetIndexInEnum(CAGimageColorUtil::hsv_purple_red)];

		if(IsNorm())	Div(2*Sum());

		AGMAGICIP_DEFAULT_SEGS_CLASS	temp_seg;
		CAGimageSegs*		pUsedSegs=pSegs;
		if(pUsedSegs==NULL)	pUsedSegs=&temp_seg;

		CAGimageGrayScale	m_SegAGimage;
		if(bIsNegativeImageWhenSegment)
		{
			CAGimage			NegativeImage;
			NegativeImage.Copy(pAGimageTempSrc);
			NegativeImage.Negative();
			m_SegAGimage.Copy(&NegativeImage);
		}
		else
			m_SegAGimage.Copy(pAGimageTempSrc);

		pUsedSegs->SegCreate(pAGimageTempSrc,NULL,&m_SegAGimage);
		if(pUsedSegs->GetSize()>0)
		{
			CAGreal64Array	OutTextures;
			if(pUsedSegs->TextureMidPoint(3,3,0.05,&OutTextures))
			{
				if(OutTextures.GetSize()!=9)	throw _T("Fatal error");
				if(IsNorm())	OutTextures.Div(2*OutTextures.Sum());
				for(agint32 i=0; i<9; i++)
					m_vector[12+i]=(agfdatatype)OutTextures.GetAt(i);
			}
		}
	}
	//else if(m_ftype==AGMAGICIP_AFFINITY)
	//{
	//}
	//else if(m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	//{
	//}
	//else if(m_ftype==AGMAGICIP_USER_ACCESS_FREQUENCY)
	//{
	//}
	else throw _T("Feature not support");
	if(IsNorm())
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			agfreal min_value=AGMAGICIP_MIN_NORM_FEAT_VALUE;
			if(m_vector[i]<min_value)	m_vector[i]=0;
		}
	}

	m_ImageID=pAGimageTempSrc->m_ID;
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agfdatatype* CAGimagefVec<agfdatatype, m_ftype>::GetAtImageID(aguint_id ImageID)
{
	if(m_aRelatedImageID.IsEmpty())				return NULL;
	agint32 n=m_aRelatedImageID.GetSize();
	agint32 i=0;
	for(i=0; i<n; i++)
		if(m_aRelatedImageID.GetAt(i)==ImageID)	break;
	if(i==n)			return NULL;
	if(i>=GetSize())	return NULL;
	return m_vector+i;
}

template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGet256ClrFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageID)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image256ClrFeatures WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetClrTxtFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageID)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image9HSVClr12TxtFeatures WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetAffinitySelectSQL(agtchar*& SQL, aguint_id ImageID, agbool bIsNorm)
{
	if(SQL) free(SQL);       SQL=NULL;
	if(!bIsNorm)	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM ImagesAffinity WHERE ImageID="),agtrue);
	else		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM ImagesNormAffinity WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessPatternSelectSQL(agtchar*& SQL, aguint_id ImageID, time_t tAccessedBegin, time_t tAccessedEnd)
{
	if(SQL) free(SQL);       SQL=NULL;
	//tAccessedBegin va tAccessedEnd la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM UserAccessPatern WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed >= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedBegin,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed <= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedEnd,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessFreqSelectSQL(agtchar*& SQL, time_t tAccessedBegin, time_t tAccessedEnd)
{
	if(SQL) free(SQL);       SQL=NULL;
	//tAccessedBegin va tAccessedEnd la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
	//khong su dung ImageID

	//khong su dung ImageID
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM UserAccessFreq WHERE tAccessed >= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedBegin,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed <= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedEnd,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGet256ClrFeaturesInsertSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne)
{
	if(ne!=256)	throw _T("Number of features must be equal 256");
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO Image256ClrFeatures(IMAGEID,"),agtrue);
	for(aguint32	i=0; i<255; i++)
	{
		agtchar field[32];	_stprintf(field,_T("CLR%lu,"),i);
		CAGmagicStrUtil::private_tcscat(SQL,field,agtrue);
	}
	CAGmagicStrUtil::private_tcscat(SQL,_T("CLR255) VALUES("),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	
	agtchar*	svector=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,ToString(vector,ne,svector),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	if(svector)	free(svector);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetClrTxtFeaturesInsertSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne)
{
	if(SQL) free(SQL);       SQL=NULL;
	
	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO Image9HSVClr12TxtFeatures"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(IMAGEID,BLACK,W,RED,RY,Y,YG,G,GB,B,BP,P,PR,L1,L2,L3,L4,L5,L6,L7,L8,L9) VALUES("),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);

	agtchar*	svector=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,ToString(vector,ne,svector),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	if(svector)	free(svector);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetAffinityInsertSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, agfdatatype measure, agbool bIsNorm)
{
	if(SQL) free(SQL);       SQL=NULL;

	if(!bIsNorm)	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO ImagesAffinity"),agtrue);
	else		CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO ImagesNormAffinity"),agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T("(IMAGEID,RELATEDIMAGEID,MEASURE) VALUES("),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);			CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);

	AG_private_tcscat_number(SQL,measure,agtrue);	CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessPatternInsertSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed, agfdatatype isAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO UserAccessPattern(ImageID,RelatedImageID,tAccessed,isAccessed) VALUES("),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);			CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);		CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	AG_private_tcscat_number(SQL,isAccessed,agtrue);				CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessFreqInsertSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed, agfdatatype nAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("INSERT INTO UserAccessFreq(ImageID,tAccessed,nAccessed) VALUES("),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);		CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	AG_private_tcscat_number(SQL,nAccessed,agtrue);					CAGmagicStrUtil::private_tcscat(SQL,_T(")"),agtrue);
	return SQL;
}

template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGet256ClrFeaturesUpdateSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne)
{
	if(ne!=256)	throw _T("Number of features must be equal 256");
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE Image256ClrFeatures SET "),agtrue);
	for(aguint32	i=0; i<256; i++)
	{
		agtchar field[32];	_stprintf(field,_T("CLR%lu="),i);
		CAGmagicStrUtil::private_tcscat(SQL,field,agtrue);
		AG_private_tcscat_number(SQL,vector[i],agtrue);

		if(i<255)	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	}

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}

template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetClrTxtFeaturesUpdateSQL(agtchar*& SQL, aguint_id ImageID, agfdatatype vector[], agint32 ne)
{
	if(ne!=21)	throw _T("Number of features must be equal 21");
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE Image9HSVClr12TxtFeatures SET "),agtrue);
	agtchar* sFields[]=  {
						_T("BLACK"), _T("W"),  _T("RED"), _T("RY"), _T("Y"), _T("YG"),
						_T("G"),     _T("GB"), _T("B"),   _T("BP"), _T("P"), _T("PR"),
						_T("L1"),    _T("L2"), _T("L3"),  _T("L4"), _T("L5"),_T("L6"),
						_T("L7"),    _T("L8"), _T("L9")
						};

	for(aguint32	i=0; i<21; i++)
	{
		CAGmagicStrUtil::private_tcscat(SQL,sFields[i],agtrue);
		CAGmagicStrUtil::private_tcscat(SQL,_T("="),agtrue);
		AG_private_tcscat_number(SQL,vector[i],agtrue);

		if(i<20)	CAGmagicStrUtil::private_tcscat(SQL,_T(","),agtrue);
	}

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}

template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetAffinityUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, agfdatatype measure, agbool bIsNorm)
{
	if(SQL) free(SQL);       SQL=NULL;

	if(!bIsNorm)	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesAffinity SET "),agtrue);
	else		CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE ImagesNormAffinity SET "),agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T("MEASURE="),agtrue);				AG_private_tcscat_number(SQL,measure,agtrue);

	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE IMAGEID="),agtrue);		CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RELATEDIMAGEID="),agtrue);	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessPatternUpdateSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed, agfdatatype isAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE UserAccessPattern SET isAccessed="),agtrue);
	AG_private_tcscat_number(SQL,isAccessed,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);		CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RelatedImageID="),agtrue);	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed="),agtrue);		CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessFreqUpdateSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed, agfdatatype nAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;

	CAGmagicStrUtil::private_tcscat(SQL,_T("UPDATE UserAccessFreq SET nAccessed="),agtrue);
	AG_private_tcscat_number(SQL,nAccessed,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" WHERE ImageID="),agtrue);	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed="),agtrue);	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGet256ClrFeaturesDeleteSQL(agtchar*& SQL, aguint_id ImageID)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM Image256ClrFeatures WHERE IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetClrTxtFeaturesDeleteSQL(agtchar*& SQL, aguint_id ImageID)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM Image9HSVClr12TxtFeatures WHERE IMAGEID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetAffinityDeleteSQL(agtchar*& SQL, aguint_id ID, agbool bIDIsRelated, agbool bIsNorm)
{
	if(SQL) free(SQL);       SQL=NULL;
	if(!bIsNorm)
	{
		if(!bIDIsRelated)	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesAffinity WHERE IMAGEID="),agtrue);
		else				CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesAffinity WHERE RELATEDIMAGEID="),agtrue);
	}
	else
	{
		if(!bIDIsRelated)	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesNormAffinity WHERE IMAGEID="),agtrue);
		else				CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM ImagesNormAffinity WHERE RELATEDIMAGEID="),agtrue);
	}
	CAGmagicStrUtil::private_tcscat_id(SQL,ID,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessPatternDeleteSQL(agtchar*& SQL, aguint_id ImageID, aguint_id RelatedImageID, time_t tAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM UserAccessPattern WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,ImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND RelatedImageID="),agtrue);	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed="),agtrue);		CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefVec<agfdatatype, m_ftype>::DBGetUserAccessFreqDeleteSQL(agtchar*& SQL, aguint_id RelatedImageID, time_t tAccessed)
{
	if(SQL) free(SQL);       SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("DELETE FROM UserAccessFreq WHERE ImageID="),agtrue);
	CAGmagicStrUtil::private_tcscat_id(SQL,RelatedImageID,agtrue); 
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed="),agtrue);	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessed,agtrue);
	return SQL;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::DBRead(aguint_id ImageID, void* pReserved)//pReserved la time_t*, pReserved[0] va pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
{
	agtchar* SQL=NULL;
	//pReserved la time_t*, pReserved[0] va pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
	//UserAccessFreq khong su dung ImageID
	RemoveAll();
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		if(m_ftype==AGMAGICIP_256CLR_FEATURE)
			DBGet256ClrFeaturesSelectSQL(SQL,ImageID);
		else
			DBGetClrTxtFeaturesSelectSQL(SQL,ImageID);

		agint32		fieldsNum=0;
		agfdatatype*	data=NULL;
		if(!AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum))
			return agfalse;

		agint32		ne=fieldsNum-1;
		if(ne<=0)	throw _T("Error database");

		Import(data+1,ne);//bo phan tu dau cua data
		m_ImageID=ImageID;//ImageID=(aguint_id)data[0]
		m_pNoFreeTempAGimageSrc=NULL;
	
		if(data) free(data);
	}
	else if(m_ftype==AGMAGICIP_AFFINITY)
	{
		DBGetAffinitySelectSQL(SQL,ImageID,m_bIsNorm);

		agint32		fieldsNum=0;
		agint32		recordsNum=0;
		agreal64**	data=NULL;
		if(!AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum,recordsNum))
			return agfalse;
		if(fieldsNum!=3)	throw _T("Error database");

		SetSize(recordsNum);
		m_aRelatedImageID.SetSize(recordsNum);
		//m_aTime khong su dung
		for(agint32 i=0; i<recordsNum; i++)
		{
			m_aRelatedImageID.SetAt(i,(aguint_id)(data[i][1]));//column RELATEDIMAGEID la cot 1
			m_vector[i]=(agfdatatype)(data[i][2]);//column MEASURE la cot 2
		}
		m_ImageID=ImageID;//ImageID=(aguint_id)data[0][0]
		m_pNoFreeTempAGimageSrc=NULL;
		
		if(data)
		{
			for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
			free(data);
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		//pReserved la time_t*, pReserved[0] va pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
		if(pReserved==NULL)		throw _T("Lack of parameter");

		time_t*	pAccessedTime=(time_t*)pReserved;
		DBGetUserAccessPatternSelectSQL(SQL,ImageID,pAccessedTime[0],pAccessedTime[1]);

		agint32			fieldsNum=0;
		agint32			recordsNum=0;
		agreal64**		data=NULL;
		if(!AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum,recordsNum))
			return agfalse;
		if(fieldsNum!=4)	throw _T("Error database");//ImageID, RelatedImageID, tAccessed, isAccessed

		SetSize(recordsNum);
		m_aRelatedImageID.SetSize(recordsNum);
		m_aTime.SetSize(recordsNum);
		for(agint32 i=0; i<recordsNum; i++)
		{
			m_aRelatedImageID.SetAt(i,(aguint_id)data[i][1]);
			m_aTime.SetAt(i,(time_t)data[i][2]);
			m_vector[i]=(agfdatatype)(data[i][3]);
		}			
		m_ImageID=ImageID;//ImageID=(aguint_id)data[0][0]
		m_pNoFreeTempAGimageSrc=NULL;

		if(data)
		{
			for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
			free(data);
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_FREQUENCY)
	{
		//pReserved la time_t*, pReserved[0] va pReserved[1] la thoi gian bat dau va thoi gian ket thuc trong table UserAccessPattern, UserAccessFreq
		//UserAccessFreq khong su dung ImageID
		if(pReserved==NULL)		throw _T("Lack of parameter");

		time_t*	pAccessedTime=(time_t*)pReserved;
		DBGetUserAccessFreqSelectSQL(SQL,pAccessedTime[0],pAccessedTime[1]);

		agint32			fieldsNum=0;
		agint32			recordsNum=0;
		agreal64**		data=NULL;
		if(!AGdbRead(m_pDBCnnI,SQL,agfalse,data,fieldsNum,recordsNum))
			return agfalse;
		if(fieldsNum!=3)	throw _T("Error database");

		for(agint32 i=0; i<recordsNum; i++)
		{
			aguint_id	RelatedImageID=(aguint_id)data[i][0];
			if(m_aRelatedImageID.LSearch(RelatedImageID)==-1)
			{
				m_aRelatedImageID.Add(RelatedImageID);;
				m_aTime.Add((time_t)(data[i][1]));
				Add((agfdatatype)(data[i][2]));
			}
		}			
		m_ImageID=0;//khong su dung m_ImageID trong AGMAGICIP_USER_ACCESS_FREQUENCY 
		m_pNoFreeTempAGimageSrc=NULL;

		if(data)
		{
			for(agint32 i=0; i<recordsNum; i++)	free(data[i]);
			free(data);
		}
	}
	else throw _T("Feature not defined");
	if(SQL)	free(SQL);
	return agtrue;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::DBInsert()
{
	if(IsEmpty())	return agfalse;
	agtchar*	SQL=NULL;

	if(m_ftype==AGMAGICIP_256CLR_FEATURE)
	{
		DBGet256ClrFeaturesInsertSQL(SQL,m_ImageID,m_vector,m_ne);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Error Insert");
	}
	else if(m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		DBGetClrTxtFeaturesInsertSQL(SQL,m_ImageID,m_vector,m_ne);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Error Insert");
	}
	else if(m_ftype==AGMAGICIP_AFFINITY)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			DBGetAffinityInsertSQL(SQL,m_ImageID,m_aRelatedImageID.GetAt(i),m_vector[i],m_bIsNorm);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when insert");
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			DBGetUserAccessPatternInsertSQL(SQL,m_ImageID,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i),m_vector[i]);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when insert");
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_FREQUENCY)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			//khong su dung m_ImageID
			DBGetUserAccessFreqInsertSQL(SQL,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i),m_vector[i]);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when insert");
		}
	}
	else throw _T("Feature not defined");
	if(SQL)	free(SQL);	
	return agtrue;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::DBUpdate()
{
	if(IsEmpty())	return agfalse;
	agtchar*	SQL=NULL;
	
	if(m_ftype==AGMAGICIP_256CLR_FEATURE)
	{
		DBGet256ClrFeaturesUpdateSQL(SQL,m_ImageID,m_vector,m_ne);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Error Update");
	}
	else if(m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		DBGetClrTxtFeaturesUpdateSQL(SQL,m_ImageID,m_vector,m_ne);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse)) throw _T("Error Update");
	}
	else if(m_ftype==AGMAGICIP_AFFINITY)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			DBGetAffinityUpdateSQL(SQL,m_ImageID,m_aRelatedImageID.GetAt(i),m_vector[i],m_bIsNorm);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when update");
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			DBGetUserAccessPatternUpdateSQL(SQL,m_ImageID,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i),m_vector[i]);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when insert");
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_FREQUENCY)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			//khong su dung m_ImageID
			DBGetUserAccessFreqUpdateSQL(SQL,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i),m_vector[i]);
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	throw _T("Error when insert");
		}
	}
	else throw _T("Feature not defined");
	if(SQL) free(SQL);	
	return agtrue;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefVec<agfdatatype, m_ftype>::DBDelete()
{
	agtchar*	SQL=NULL;
	agbool	bResult=agtrue;

	if(m_ftype==AGMAGICIP_256CLR_FEATURE)
	{
		DBGet256ClrFeaturesDeleteSQL(SQL,m_ImageID);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))		bResult=agfalse;
	}
	else if(m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		DBGetClrTxtFeaturesDeleteSQL(SQL,m_ImageID);
		if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))		bResult=agfalse;
	}
	else if(m_ftype==AGMAGICIP_AFFINITY)
	{
		DBGetAffinityDeleteSQL(SQL,m_ImageID,agfalse,m_bIsNorm);
		bResult=bResult && CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);

		DBGetAffinityDeleteSQL(SQL,m_ImageID,agtrue,m_bIsNorm);
		bResult=bResult && CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse);
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			DBGetUserAccessPatternDeleteSQL(SQL,m_ImageID,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i));
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	bResult=agfalse;
		}
	}
	else if(m_ftype==AGMAGICIP_USER_ACCESS_FREQUENCY)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			//khong su dung m_ImageID
			DBGetUserAccessFreqDeleteSQL(SQL,m_aRelatedImageID.GetAt(i),m_aTime.GetAt(i));
			if(!CAGmagicDBUtil::ExcuteSQL(m_pDBCnnI,SQL,agfalse))	bResult=agfalse;
		}
	}
	else throw _T("Feature not defined");
	if(SQL)	free(SQL);
	return bResult;
}


/********interface IAGimagefMatrix, class CAGimagefMatrix************/

/*
template<class agfdatatype> class IAGimagefMatrix
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class agfdatatype>
class IAGimagefMatrix : public CAGobjPtrArray< IAGimagefVec<agfdatatype> >, public CAGmagicDBOrg
{
public:
	virtual	void*	newAGOBJ_ARRAY_TYPE()							{throw _T("You must define");}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)	{throw _T("You must define");}

public:
	IAGimagefMatrix() : CAGobjPtrArray< IAGimagefVec<agfdatatype> >(), CAGmagicDBOrg()	{}
	virtual	~IAGimagefMatrix()	{}

	virtual void	Destroy()								{throw _T("You must define");}
	virtual void	GetAllImageIDs(CAGidArray* ImageIDs)	{throw _T("You must define");}
	virtual	agint32	LSearchImageID(aguint_id ImageID)		{throw _T("You must define");}
	virtual void	RemoveIfImageID(aguint_id ImageID)		{throw _T("You must define");}
	virtual void	RemoveIfImageID(aguint_id ImageIDs[], agint32 nImageIDs)		{throw _T("You must define");}

	virtual agbool	Export(agfdatatype**& Matrix, agint32& nVectors, agint32& ne)		{throw _T("You must define");}

	virtual	IAGimagefVec<agfdatatype>*		GetAtImageID(aguint_id ImageID)		{throw _T("You must define");}

	virtual void*	DBCnnAttach(void* pDBCnnI);	//khong AddRef, tra ve Connection cu doi voi ADO
	virtual void*	DBCnnDetach();				//khong Release

	virtual agbool	DBRead(aguint_id ImageIDs[], aguint32 nImageIDs, void* pReserved=NULL)	{throw _T("You must define");}
	virtual agbool	DBInsert()	{throw _T("You must define");}
	virtual agbool	DBUpdate()	{throw _T("You must define");}
};

template<class agfdatatype>
void* IAGimagefMatrix<agfdatatype>::DBCnnAttach(void* pDBCnnI)//khong AddRef doi voi ADO
{
	void*	old=CAGmagicDBOrg::DBCnnAttach(pDBCnnI);
	if(m_vector!=NULL)
	{
		for(agint32 i=0; i<m_ne; i++)
			m_vector[i]->DBCnnAttach(m_pDBCnnI);
	}
	return old;
}
template<class agfdatatype>
void* IAGimagefMatrix<agfdatatype>::DBCnnDetach()//khong Release
{
	if(m_vector!=NULL)
	{
		for(agint32 i=0; i<m_ne; i++)
			m_vector[i]->DBCnnDetach();
	}
	return CAGmagicDBOrg::DBCnnDetach();
}

///////////////////////////////////////////////////////////////////////////////////////

class CAGtrainingDataSet;
/*
template<class agfdatatype, aguint32 m_ftype> class CAGimagefMatrix
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class agfdatatype, aguint32 m_ftype>
class CAGimagefMatrix : public IAGimagefMatrix<agfdatatype>
{
public:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGimagefVec<agfdatatype,m_ftype>();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGimagefVec<agfdatatype,m_ftype>*	dstFeat=(CAGimagefVec<agfdatatype,m_ftype>*)dst;
		CAGimagefVec<agfdatatype,m_ftype>*	srcFeat=(CAGimagefVec<agfdatatype,m_ftype>*)src;
		dstFeat->CopyFrom(srcFeat);
	}
public:
	CAGimagefMatrix();
	virtual	~CAGimagefMatrix();
	virtual void	Destroy();
	virtual void	GetAllImageIDs(CAGidArray* ImageIDs);

	virtual agbool	CreateFrom(CAGimage** ppAGimageTempSrc, aguint32 ni);
	virtual agbool	CopyFrom(const CAGimagefMatrix* xa, agbool bIsCopy=agfalse);
	virtual agbool	TransferFrom(CAGimagefMatrix* xa);

	virtual void	SetIsNorm(agbool bIsNormVector);
	virtual agbool	IsNorm();

	virtual	agbool	Normalize();

	virtual	agint32	LSearchImageID(aguint_id ImageID);
	virtual void	RemoveIfImageID(aguint_id ImageID);
	virtual void	RemoveIfImageID(aguint_id ImageIDs[], agint32 nImageIDs);
	void	RemoveSameImageIDs();
	void	RemoveNULLOrEmptyElements();

	virtual agbool	Export(agfdatatype**& Matrix, agint32& nVectors, agint32& ne);

	virtual	IAGimagefVec<agfdatatype>*	GetAtImageID(aguint_id ImageID);
protected:
	static agtchar*	DBGet256ClrFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageIDs[], aguint32 nImageIDs);//ImageIDs==NULL || nImageIDs==0: lay tat ca
	static agtchar*	DBGetClrTxtFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageIDs[], aguint32 nImageIDs);//ImageIDs==NULL || nImageIDs==0: lay tat ca
	static void DBGetUserAccessPatternImageIDs(void* pDBCnnI, time_t tAccessedBegin, time_t tAccessedEnd, aguint_id*& ImageIDs, agint32& nImageIDs);

public:
	
	virtual agbool	DBRead(aguint_id ImageIDs[], aguint32 nImageIDs, void* pReserved=NULL);
	virtual agbool	DBInsert();
	virtual agbool	DBUpdate();
	virtual agbool	DBDelete();

	agfdatatype*		operator[](agint32 idx);
	friend class	CAGtrainingDataSet;
};

template<class agfdatatype, aguint32 m_ftype>
CAGimagefMatrix<agfdatatype, m_ftype>::CAGimagefMatrix() : IAGimagefMatrix<agfdatatype>()
{
}

template<class agfdatatype, aguint32 m_ftype>
CAGimagefMatrix<agfdatatype, m_ftype>::~CAGimagefMatrix()
{
	Destroy();
}

template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::Destroy()
{
	RemoveAll();
	DBCnnDetach();
}
template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::GetAllImageIDs(CAGidArray* ImageIDs)
{
	ImageIDs->RemoveAll();
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			IAGimagefVec<agfdatatype>*	pfVec=(IAGimagefVec<agfdatatype>*)(m_vector[i]);
			aguint_id							ImageID=pfVec->GetImageID();
			ImageIDs->Add(ImageID);
		}
	}
	else if(m_ftype==AGMAGICIP_AFFINITY || m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			CAGimagefVec<agfdatatype,m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
			aguint_id									ImageID=pfVec->GetImageID();
			if(ImageIDs->LSearch(ImageID)==-1)
				ImageIDs->Add(ImageID);

			agint32 n=pfVec->m_aRelatedImageID.GetSize();
			for(agint32 j=0; j<n; j++)
			{
				aguint_id									RelatedImageID=pfVec->m_aRelatedImageID.GetAt(j);
				if(ImageIDs->LSearch(RelatedImageID)==-1)
					ImageIDs->Add(RelatedImageID);
			}
		}
	}
	else throw _T("Error feature");
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::CreateFrom(CAGimage** ppAGimageTempSrc, aguint32 ni)
{
	if(ppAGimageTempSrc==NULL)	return agfalse;
	RemoveAll();
	throw _T("Implement not yet");
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::CopyFrom(const CAGimagefMatrix* xa, agbool bIsCopy)
{
	if(!CAGobjPtrArray< IAGimagefVec<agfdatatype> >::CopyFrom((CAGobjPtrArray< IAGimagefVec<agfdatatype> >*)xa,bIsCopy))
		return agfalse;
	DBCnnAttach(xa->m_pDBCnnI);
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::TransferFrom(CAGimagefMatrix* xa)
{
	if(!CAGobjPtrArray< IAGimagefVec<agfdatatype> >::TransferFrom(xa))
		return agfalse;
	void*	pDBCnnI=xa->DBCnnDetach();
	DBCnnAttach(pDBCnnI);
	return agtrue;
}

template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::SetIsNorm(agbool bIsNorm)
{
	m_bIsNorm=bIsNorm;
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
		pfVec->SetIsNorm(m_bIsNorm);
	}
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::IsNorm()
{
	return m_bIsNorm;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::Normalize()
{
	if(IsEmpty())		return agfalse;
	if(m_bIsNorm)	return agtrue;
	m_bIsNorm=agtrue;
	for(agint32 i=0; i<m_ne; i++)
	{
		CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
		pfVec->Normalize();
	}
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agint32 CAGimagefMatrix<agfdatatype, m_ftype>::LSearchImageID(aguint_id ImageID)
{
	if(IsEmpty())	return -1;
	agint32 n=GetSize();
	agint32 i=0;
	for(i=0; i<n; i++)
	{
		IAGimagefVec<agfdatatype>* pfVect=(IAGimagefVec<agfdatatype>*)m_vector[i];
		if(pfVect==NULL)						continue;
		if(pfVect->GetImageID()==ImageID)	break;
	}
	if(i==n)	return -1;
	return i;
}
template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::RemoveIfImageID(aguint_id ImageID)
{
	for(agint32 i=0; i<GetSize(); i++)
	{
		if(((IAGimagefVec<agfdatatype>*)m_vector[i])->GetImageID()==ImageID)
		{
			RemoveAt(i);
			i--;
		}
	}
}
template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::RemoveIfImageID(aguint_id ImageIDs[], agint32 nImageIDs)
{
	for(agint32 i=0; i<GetSize(); i++)
	{
		aguint_id ImageID=((IAGimagefVec<agfdatatype>*)m_vector[i])->GetImageID();
		if(CAGidArray::LSearch(ImageID,ImageIDs,nImageIDs)!=-1)
		{
			RemoveAt(i);
			i--;
		}
	}
}
template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::RemoveNULLOrEmptyElements()
{
	if(IsEmpty())		return;
	for(agint32 i=0; i<GetSize(); i++)
	{
		CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
		if(pfVec==NULL || pfVec->IsEmpty())
		{
			RemoveAt(i);
			i--;
		}
	}
}
template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::RemoveSameImageIDs()
{
	if(IsEmpty())		return;
	CAGimagefMatrix<agfdatatype, m_ftype>	xa;
	xa.TransferFrom(this);
	Destroy();
	
	agint32 n=xa.GetSize();
	for(agint32 i=0; i<n; i++)
	{
		if(LSearchImageID(xa.GetAt(i)->GetImageID())==-1)
		{
			Add(xa.GetAt(i));
			xa.SetNULLAt(i);
		}
	}
	SetIsNorm(xa.m_bIsNorm);
	DBCnnAttach(xa.m_pDBCnnI);
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::Export(agfdatatype**& Matrix, agint32& nVectors, agint32& ne)
{
	if(Matrix)
	{
		for(agint32 i=0; i<nVectors; i++)	
			if(Matrix[i])	free(Matrix[i]);
		free(Matrix);	Matrix=NULL;
	}
	nVectors=ne=0;
	if(IsEmpty())	return agfalse;
	agint32 i=0;
	for(i=0; i<m_ne; i++)
	{
		IAGimagefVec<agfdatatype>* pIAGimagefVec=(IAGimagefVec<agfdatatype>*)(m_vector[i]);
		if(pIAGimagefVec==NULL)		continue;
		if(pIAGimagefVec->IsEmpty())	continue;

		if(ne==0)
			ne=pIAGimagefVec->GetSize();
		else if(ne!=pIAGimagefVec->GetSize())
			return agfalse;
		nVectors ++;
	}
	if(nVectors==0)	return agfalse;
	Matrix=(agfdatatype**)malloc(nVectors*sizeof(agfdatatype*));
	memset(Matrix,0,nVectors*sizeof(agfdatatype*));
	for(i=0; i<nVectors; i++)
	{
		IAGimagefVec<agfdatatype>* pIAGimagefVec=(IAGimagefVec<agfdatatype>*)(m_vector[i]);
		if(pIAGimagefVec==NULL)		continue;
		if(pIAGimagefVec->IsEmpty())	continue;

		pIAGimagefVec->Export(Matrix[i],ne);
	}
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
IAGimagefVec<agfdatatype>*	CAGimagefMatrix<agfdatatype, m_ftype>::GetAtImageID(aguint_id ImageID)
{
	
	agint32 i=LSearchImageID(ImageID);
	if(i==-1)	return NULL;
	return (IAGimagefVec<agfdatatype>*)(m_vector[i]);
	
}

template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefMatrix<agfdatatype, m_ftype>::DBGet256ClrFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageIDs[], aguint32 nImageIDs)
{
	if(SQL)	free(SQL);	SQL=NULL;
	if(ImageIDs==NULL || nImageIDs==0)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image256ClrFeatures"),agtrue);
		return SQL;
	}

	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image256ClrFeatures WHERE "),agtrue);
	for(aguint32 i=0; i<nImageIDs; i++)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("IMAGEID="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,ImageIDs[i],agtrue);
		if(i<nImageIDs-1)	CAGmagicStrUtil::private_tcscat(SQL,_T(" OR "),agtrue);
	}
	return SQL;
}
template<class agfdatatype, aguint32 m_ftype>
agtchar* CAGimagefMatrix<agfdatatype, m_ftype>::DBGetClrTxtFeaturesSelectSQL(agtchar*& SQL, aguint_id ImageIDs[], aguint32 nImageIDs)
{
	if(SQL)	free(SQL);	SQL=NULL;
	if(ImageIDs==NULL || nImageIDs==0)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image9HSVClr12TxtFeatures"),agtrue);
		return SQL;
	}

	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM Image256ClrFeatures WHERE "),agtrue);
	for(aguint32 i=0; i<nImageIDs; i++)
	{
		CAGmagicStrUtil::private_tcscat(SQL,_T("IMAGEID="),agtrue);
		CAGmagicStrUtil::private_tcscat_id(SQL,ImageIDs[i],agtrue);
		if(i<nImageIDs-1)	CAGmagicStrUtil::private_tcscat(SQL,_T(" OR "),agtrue);
	}
	return SQL;
}

template<class agfdatatype, aguint32 m_ftype>
void CAGimagefMatrix<agfdatatype, m_ftype>::DBGetUserAccessPatternImageIDs(void* pDBCnnI, time_t tAccessedBegin, time_t tAccessedEnd, aguint_id*& ImageIDs, agint32& nImageIDs)
{
	if(ImageIDs)	free(ImageIDs);
	ImageIDs=NULL;	nImageIDs=0;

	agtchar*	SQL=NULL;
	CAGmagicStrUtil::private_tcscat(SQL,_T("SELECT * FROM UserAccessPatern WHERE tAccessed >= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedBegin,agtrue);
	CAGmagicStrUtil::private_tcscat(SQL,_T(" AND tAccessed <= "),agtrue);
	CAGmagicStrUtil::private_tcscat_time(SQL,tAccessedEnd,agtrue);

	AGdbReadOneField(pDBCnnI,SQL,0,agfalse,ImageIDs,nImageIDs);
	CAGidArray::RemoveSameValues(ImageIDs,nImageIDs);

	if(SQL)	free(SQL);
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::DBRead(aguint_id ImageIDs[], aguint32 nImageIDs, void* pReserved)
{
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE || 
			m_ftype==AGMAGICIP_AFFINITY || m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		RemoveAll();
		SetSize(nImageIDs,agtrue);
		for(aguint32 i=0; i<nImageIDs; i++)
		{
			CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
			pfVec->m_bIsNorm=m_bIsNorm;
			pfVec->m_pNoFreeTempAGimageSrc=NULL;
			pfVec->DBCnnAttach(m_pDBCnnI);

			if(!pfVec->DBRead(ImageIDs[i],pReserved))	continue;//throw _T("Error Read Database");
			if(pfVec->IsEmpty())						continue;//throw _T("Error Read Database");
		}
		RemoveNULLOrEmptyElements();
	}
	else throw _T("Feature not defined");
	return agtrue;
}

template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::DBInsert()
{
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE || m_ftype==AGMAGICIP_AFFINITY || m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
			if(!pfVec->DBInsert())					throw _T("Error Insert Database");
		}
	}
	else throw _T("Feature not defined");
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::DBUpdate()
{
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE || m_ftype==AGMAGICIP_AFFINITY || m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
			if(!pfVec->DBUpdate())	throw _T("Error Update Database");
		}
	}
	else throw _T("Feature not defined");
	return agtrue;
}
template<class agfdatatype, aguint32 m_ftype>
agbool CAGimagefMatrix<agfdatatype, m_ftype>::DBDelete()
{
	agbool	bResult=agtrue;
	if(m_ftype==AGMAGICIP_256CLR_FEATURE || m_ftype==AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE || m_ftype==AGMAGICIP_AFFINITY || m_ftype==AGMAGICIP_USER_ACCESS_PATTERN)
	{
		for(agint32 i=0; i<m_ne; i++)
		{
			CAGimagefVec<agfdatatype, m_ftype>*	pfVec=(CAGimagefVec<agfdatatype,m_ftype>*)(m_vector[i]);
			bResult=bResult && pfVec->DBDelete();
		}
	}
	else throw _T("Feature not defined");
	return bResult;
}

template<class agfdatatype, aguint32 m_ftype>
agfdatatype* CAGimagefMatrix<agfdatatype, m_ftype>::operator[](agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx]->m_vector;
}

typedef AGMAGIC_DECL IAGimagefVec<agfreal>		IAGflexfVec;
typedef AGMAGIC_DECL IAGimagefMatrix<agfreal>	IAGflexfMatrix;

typedef AGMAGIC_DECL CAGimagefVec<agfreal,AGMAGICIP_256CLR_FEATURE>				CAGimage256ClrfVec;
typedef AGMAGIC_DECL CAGimagefVec<agfreal,AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE>	CAGimage12HSVClr9GridTxtfVec;
typedef AGMAGIC_DECL CAGimagefVec<agfreal,AGMAGICIP_AFFINITY>					CAGimageAffVec;
typedef AGMAGIC_DECL CAGimagefVec<aguint32,AGMAGICIP_USER_ACCESS_FREQUENCY>		CAGuserAccessFrequencyVec;
typedef AGMAGIC_DECL CAGimagefVec<aguint32,AGMAGICIP_USER_ACCESS_PATTERN>		CAGuserAccessPatternVec;

typedef AGMAGIC_DECL CAGimagefMatrix<agfreal,AGMAGICIP_256CLR_FEATURE>				CAGimage256ClrfMatrix;
typedef AGMAGIC_DECL CAGimagefMatrix<agfreal,AGMAGICIP_12HSVCLR_9GRIDTXT_FEATURE>	CAGimage12HSVClr9GridTxtfMatrix;
typedef AGMAGIC_DECL CAGimagefMatrix<aguint32,AGMAGICIP_USER_ACCESS_PATTERN>		CAGuserAccessPatternMatrix;

/*********************************class CAGfeatUtil************************/

#include "AGimageUtil.h"
class AGMAGIC_DECL CAGfeatUtil
{
public:
	static IAGflexfVec*		CreateFeaturesVector();
	static IAGflexfMatrix*	CreateFeaturesMatrix();

	static	agbool	TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers,	CAGbuRectVec* pInRects, 
								CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures);

	static	agbool	TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers,	AGBU_RECT TotalRect, SIZE block_size, 
								CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures);

	static	agbool	TextureMidPoint(CAGbaseArray<AGBU_POINT>* centers,	AGBU_RECT TotalRect, agint32 nRows, agint32 nCols, 
								CAGint32Array* center_pixels,	agint32 nTotalPixels, 
								agreal64 ExcludePixelsPercent,	CAGreal64Array* pOutTextures);
};

/************************struct AGUSER_ACCESS_PATTERN_ITEM, struct AGUSER_ACCESS_FREQUENCY_ITEM****************/

class AGMAGIC_DECL AGUSER_ACCESS_PATTERN_ITEM
{
public:

	aguint_id	mID;
	aguint_id	kID;//anh duoc dung de truy van
	time_t		tAccessed;
	aguint32	isAccess;//0,1

	AGUSER_ACCESS_PATTERN_ITEM()
	{
		mID=0;
		kID=0;
		tAccessed=0;
		isAccess=0;
	}
	virtual ~AGUSER_ACCESS_PATTERN_ITEM()
	{
	}

};

class AGMAGIC_DECL AGUSER_ACCESS_FREQUENCY_ITEM
{
public:
	aguint_id	kID;
	time_t		tAccessed;
	aguint32	nAccessed;

	AGUSER_ACCESS_FREQUENCY_ITEM()
	{
		kID=0;
		tAccessed=0;
		nAccessed=0;
	}
	virtual ~AGUSER_ACCESS_FREQUENCY_ITEM()
	{
	}
};


/************************class CAGimageAffMatrix, class CAGaffArray******************************/
/*
class AGMAGIC_DECL CAGimageAffMatrix
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGimageAffMatrix : public CAGimagefMatrix<agfreal, AGMAGICIP_AFFINITY>
{
public:
	CAGimageAffMatrix();
	virtual ~CAGimageAffMatrix();

	agfreal*	paff(aguint_id mID, aguint_id nID, agbool throwErr=agfalse);
	agfreal		aff(aguint_id mID, aguint_id nID, agbool throwErr=agfalse);
	void			SetAff(aguint_id mID, aguint_id nID, agfreal value);

	static void		DeleteAllAffInDB(void* pDBCnnI);
	static agbool	CreateAffInDB(void* pDBCnnI, aguint_id ImageType);

	static	void		SetAffToDB(void* pDBCnnI, aguint_id mID, aguint_id nID, agfreal value, agbool bIsNorm);
	static	agbool		ReplaceImageID(void* pDBCnnI, aguint_id ImageID, aguint_id ReplaceImageID, agbool bIsNorm);
	static	agbool		ReplaceRelatedImageID(void* pDBCnnI, aguint_id RelatedImageID, aguint_id ReplaceRelatedImageID, agbool bIsNorm);
};

typedef AGMAGIC_DECL struct AGMAGIC_DECL tagAGAFFINITY_ITEM
{
	aguint_id	mID;
	aguint_id	nID;
	agfreal	value;
	agbool		bIsNorm;
} AGAFFINITY_ITEM;

/*
class AGMAGIC_DECL CAGaffArray
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGaffArray : public CAGbaseArray<AGAFFINITY_ITEM>
{
public:
	CAGaffArray();
	virtual ~CAGaffArray();
	agfreal	aff(aguint_id mID, aguint_id nID, agbool throwErr=agfalse);
	agint32		LSearch(aguint_id mID, aguint_id nID, AGAFFINITY_ITEM* pFoundAffItem=NULL);

	void		DBInsertAt(agint32 idx, void* pDBCnnI);
	void		DBUpdateAt(agint32 idx, void* pDBCnnI);

	void		DBInsert(void* pDBCnnI);
	void		DBUpdate(void* pDBCnnI);
};
/************************class CAGimageHisto******************************/

typedef AGMAGIC_DECL struct tagHISTO_ELEMENT
{
	AGCLRQUAD	clr;
	agreal64	value;
} HISTO_ELEMENT;

class AGMAGIC_DECL CAGimageHisto : public CAGbaseArray<HISTO_ELEMENT>
{
protected:
	agbool m_bIsNorm;
	static int	HISTO_ELEMENTCompareInc(const void* pHISTO_ELEMENT1, const void* pHISTO_ELEMENT2);
	static int	HISTO_ELEMENTCompareDec(const void* pHISTO_ELEMENT1, const void* pHISTO_ELEMENT2);
public:
	CAGimageHisto();
	virtual ~CAGimageHisto();
	agbool	CopyFrom(const CAGimageHisto* histo);
	void	SetNorm(agbool bIsNorm);
	agbool	IsNorm();

	void	SortInc();
	void	SortDec();
	agbool	Export(AGCLRQUAD*& clrs, agint32& ne);
	agbool	Export(agreal64*& values, agint32& ne);
	agbool	Import(const AGCLRQUAD* clrs, const agreal64* values, const agint32 ne);
};
#endif	// !defined(AGIMAGEFEAT_H__5A13A0A5_EFBE_4EDE_930F_D1B9D2D813D6__INCLUDED_)
