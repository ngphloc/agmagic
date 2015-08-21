#if !defined(AGDATA_STRUCT_H__DEE6124F_A429_11D2_84B1_00C0DFF84685__INCLUDED_)
#define AGDATA_STRUCT_H__DEE6124F_A429_11D2_84B1_00C0DFF84685__INCLUDED_

#include "AGutilCore.h"

/*******************************class CAGbaseArray*******************************/

template<class agfdatatype, aguint32 m_ftype> class CAGimagefMatrix;
class AGMAGIC_DECL CAGimageAffMatrix;

/*
template<class AGARRAY_TYPE> class CAGbaseArray
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class AGARRAY_TYPE> 
class CAGbaseArray
{
protected:
	AGARRAY_TYPE*	m_vector;//vector
	agint32			m_ne;//number of element
	agbool			m_bIsNorm;//vector la duoc chuan hoa hay khong, 0: vector co cac gia tri la column MEASURE, 1: vector co cac gia tri la column NORMMEASURE trong ImagesAffinity
public:
	CAGbaseArray()
	{
		m_vector=NULL;
		m_ne=0;
		m_bIsNorm=agfalse;
	}
	virtual ~CAGbaseArray()
	{
		RemoveAll();
	}
	virtual void	RemoveAll();
	agbool			IsEmpty();
	agbool			CopyFrom(const CAGbaseArray* xa);
	void			SetSize(agint32 ne);
	AGARRAY_TYPE	GetAt(agint32 idx);
	AGARRAY_TYPE&	ElementAt(agint32 idx);
	const AGARRAY_TYPE	operator[](agint32 idx) const;	//v=a[0];
	AGARRAY_TYPE&	operator[](agint32 idx);			//a[0]=v;
	void			SetAt(agint32 idx, AGARRAY_TYPE e);
	void			InsertAt(agint32 idx, AGARRAY_TYPE e, agint32 count=1);
	void			InsertAt(agint32 idx, const CAGbaseArray* xa);
	void			Add(AGARRAY_TYPE e, agint32 count=1);
	void			RemoveAt(agint32 idx, agint32 count=1);
	void			Append(const CAGbaseArray* xa);
	
	agint32			GetSize()			{return m_ne;}
	AGARRAY_TYPE*	GetData()			{return m_vector;}

	agbool			Import(const AGARRAY_TYPE* vector, const agint32 ne);
	agbool			Export(AGARRAY_TYPE*& vector, agint32& ne);
	void			SetValueForAll(AGARRAY_TYPE e);

	void	SetIsNorm(agbool bIsNorm);
	agbool	IsNorm();

#if AGMAGIC_MFC_VER	< 0x0800
	friend class CAGimagefMatrix;
#else
	template<class agfdatatype, aguint32 m_ftype> friend class CAGimagefMatrix;
#endif
	friend class CAGimageAffMatrix;
};
typedef AGMAGIC_DECL CAGbaseArray<void*>		CAGptrArray;

template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::RemoveAll()
{
	if(!IsEmpty())
	{
		if(m_vector!=NULL)
		{
			free(m_vector);
			m_vector=NULL;
		}
		m_ne=0;
	}
}
template<class AGARRAY_TYPE>
agbool CAGbaseArray<AGARRAY_TYPE>::IsEmpty()
{
	return (m_vector==NULL);
}
template<class AGARRAY_TYPE>
agbool CAGbaseArray<AGARRAY_TYPE>::CopyFrom(const CAGbaseArray* xa)
{
	if(xa==NULL)	throw _T("feature must be not null");
	SetSize(xa->m_ne);
	if(xa->m_ne>0)	memcpy(m_vector,xa->m_vector,m_ne*sizeof(AGARRAY_TYPE));
	m_bIsNorm=xa->m_bIsNorm;
	return agtrue;
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::SetSize(agint32 ne)
{
	if(ne<0)	throw _T("Error parameter");
	RemoveAll();

	if(ne>0)
	{
		m_ne=ne;
		m_vector=(AGARRAY_TYPE*)malloc(m_ne*sizeof(AGARRAY_TYPE));
		memset(m_vector,0,m_ne*sizeof(AGARRAY_TYPE));
	}
}
template<class AGARRAY_TYPE>
AGARRAY_TYPE CAGbaseArray<AGARRAY_TYPE>::GetAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGARRAY_TYPE>
AGARRAY_TYPE& CAGbaseArray<AGARRAY_TYPE>::ElementAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGARRAY_TYPE>
const AGARRAY_TYPE CAGbaseArray<AGARRAY_TYPE>::operator[](agint32 idx) const
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGARRAY_TYPE>
AGARRAY_TYPE& CAGbaseArray<AGARRAY_TYPE>::operator[](agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::SetAt(agint32 idx, AGARRAY_TYPE e)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	m_vector[idx]=e;//memcpy(m_vector+idx,&e,sizeof(AGARRAY_TYPE));
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::InsertAt(agint32 idx, AGARRAY_TYPE e, agint32 count)
{
	if(idx<0 || idx>=m_ne || count<=0)	throw _T("Access extra dim vector bound or error number element");

	agint32			ne=m_ne;
	AGARRAY_TYPE*	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne+count);

	if(idx>0)	memcpy(m_vector,vector,idx*sizeof(AGARRAY_TYPE));//chep phan truoc idx
	for(agint32 i=0; i<count; i++)
		m_vector[idx+i]=e;//memcpy(m_vector+idx+i,&e,sizeof(AGARRAY_TYPE));
	memcpy(m_vector+idx+count,vector+idx,(ne-idx)*sizeof(AGARRAY_TYPE));

	free(vector);
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::InsertAt(agint32 idx, const CAGbaseArray* xa)
{
	if(idx<0 || idx>=m_ne || xa==NULL)	throw _T("Access extra dim vector bound or invalid pointer");
	if(xa->m_ne==0)						return;

	agint32			ne=m_ne;
	AGARRAY_TYPE*	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne+xa->m_ne);

	if(idx>0)	memcpy(m_vector,vector,idx*sizeof(AGARRAY_TYPE));//chep phan truoc idx
	memcpy(m_vector+idx,xa->m_vector,xa->m_ne*sizeof(AGARRAY_TYPE));
	memcpy(m_vector+idx+xa->m_ne,vector+idx,(ne-idx)*sizeof(AGARRAY_TYPE));

	free(vector);
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::Add(AGARRAY_TYPE e, agint32 count)
{
	if(count<=0)	throw _T("Error number element");

	agint32 ne =m_ne+count;
	if(m_vector==NULL)
		m_vector=(AGARRAY_TYPE*)malloc(ne*sizeof(AGARRAY_TYPE));
	else
		m_vector=(AGARRAY_TYPE*)realloc(m_vector,ne*sizeof(AGARRAY_TYPE));
	for(agint32 i=0; i<count; i++)
		m_vector[m_ne+i]=e;//memcpy(m_vector+m_ne+i,&e,sizeof(AGARRAY_TYPE));
	m_ne =ne;
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::RemoveAt(agint32 idx, agint32 count)
{
	if(idx<0 || idx>=m_ne || count<=0)	throw _T("Access extra dim vector bound or error number element");
	count=AGMIN(count,(m_ne-idx));
	if(m_ne==count)
	{
		RemoveAll();
		return;
	}
	agint32			ne=m_ne;
	AGARRAY_TYPE*	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne-count);

	if(idx>0)
		memcpy(m_vector,vector,idx*sizeof(AGARRAY_TYPE));
	if(ne-idx-count>0)
		memcpy(m_vector+idx,vector+idx+count,(ne-idx-count)*sizeof(AGARRAY_TYPE));

	free(vector);
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::Append(const CAGbaseArray* xa)
{
	if(xa==NULL)			return;
	if(xa->m_ne==0)			return;

	agint32	ne=m_ne + xa->m_ne;
	if(m_vector==NULL)
		m_vector=(AGARRAY_TYPE*)malloc(ne*sizeof(AGARRAY_TYPE));
	else
		m_vector=(AGARRAY_TYPE*)realloc(m_vector,ne*sizeof(AGARRAY_TYPE));
	memcpy(m_vector+m_ne,xa->m_vector,xa->m_ne*sizeof(AGARRAY_TYPE));

	m_ne=ne;
}
template<class AGARRAY_TYPE>
agbool CAGbaseArray<AGARRAY_TYPE>::Import(const AGARRAY_TYPE* vector, const agint32 ne)
{
	if(vector==NULL || ne<=0)	return agfalse;
	SetSize(ne);
	memcpy(m_vector,vector,ne*sizeof(AGARRAY_TYPE));
	return agtrue;
}
template<class AGARRAY_TYPE>
agbool CAGbaseArray<AGARRAY_TYPE>::Export(AGARRAY_TYPE*& vector, agint32& ne)
{
	if(vector)		free(vector);
	vector=NULL;	ne=0;
	if(IsEmpty())	return agfalse;

	ne=m_ne;
	vector=(AGARRAY_TYPE*)malloc(ne*sizeof(AGARRAY_TYPE));
	memcpy(vector,m_vector,ne*sizeof(AGARRAY_TYPE));
	return agtrue;
}
template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::SetValueForAll(AGARRAY_TYPE e)
{
	for(agint32 i=0; i<m_ne; i++)	m_vector[i]=e;
}

template<class AGARRAY_TYPE>
void CAGbaseArray<AGARRAY_TYPE>::SetIsNorm(agbool bIsNorm)
{
	m_bIsNorm=bIsNorm;
}
template<class AGARRAY_TYPE>
agbool CAGbaseArray<AGARRAY_TYPE>::IsNorm()
{
	return m_bIsNorm;
}

/*******************************class CAGarray*******************************/

template<class agfdatatype, aguint32 m_ftype> class CAGimagefMatrix;

/*
template<class AGARRAY_TYPE> class CAGarray : public CAGbaseArray<AGARRAY_TYPE>
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class AGARRAY_TYPE> 
class CAGarray : public CAGbaseArray<AGARRAY_TYPE>
{
public:
#if AGMAGIC_SUPPORT_MFC
	CString			ToString();
	static	CString ToString(AGARRAY_TYPE vector[], agint32 ne);
#endif	//#if AGMAGIC_SUPPORT_MFC
	agtchar*			ToString(agtchar*& svector);
	static	agtchar*	ToString(AGARRAY_TYPE vector[], agint32 ne, agtchar*& svector);

	agint32	LSearch(AGARRAY_TYPE value);
	static	agint32	LSearch(AGARRAY_TYPE value, AGARRAY_TYPE array[], agint32 n);
	agbool	LSearch(AGARRAY_TYPE value, CAGarray* idx);

	void	RemoveIfValue(AGARRAY_TYPE e);
	void	RemoveSameValues();
	static	void	RemoveSameValues(AGARRAY_TYPE*& vector, agint32& ne);

	agreal64	Sum();
	agreal64	Mean();
	agbool	Normalize(agreal64*& pNorm, agint32& nNorm);
	agbool	Normalize();
	agbool	Div(agreal64 divisor);

//Cac phep toan tap hop
	void	Common(CAGarray* aIn, CAGarray* aResult=NULL);
	void	Union(const CAGarray* aIn, CAGarray* aResult=NULL);
	void	Complement(CAGarray* aIn, CAGarray* aResult=NULL);

#if AGMAGIC_MFC_VER	< 0x0800
	friend class CAGimagefMatrix;
#else
	template<class agfdatatype, aguint32 m_ftype> friend class CAGimagefMatrix;
#endif
};
typedef AGMAGIC_DECL CAGarray<agint8>		CAGint8Array;
typedef AGMAGIC_DECL CAGarray<aguint8>		CAGuint8Array;
typedef AGMAGIC_DECL CAGarray<agint16>		CAGint16Array;
typedef AGMAGIC_DECL CAGarray<aguint16>		CAGuint16Array;
typedef AGMAGIC_DECL CAGarray<agint32>		CAGint32Array;
typedef AGMAGIC_DECL CAGarray<aguint32>		CAGuint32Array;
typedef AGMAGIC_DECL CAGarray<aguint_id>	CAGidArray;
typedef AGMAGIC_DECL CAGarray<agreal64>		CAGreal64Array;

#include <time.h>
typedef AGMAGIC_DECL CAGarray<time_t>		CAGtimeArray;

#if AGMAGIC_SUPPORT_MFC
template<class AGARRAY_TYPE>
CString CAGarray<AGARRAY_TYPE>::ToString()
{
	return ToString(m_vector,m_ne);
}
template<class AGARRAY_TYPE>
CString CAGarray<AGARRAY_TYPE>::ToString(AGARRAY_TYPE vector[], agint32 ne)
{
	CString			svector; 
	if(vector==NULL || ne==0)	return svector;
	for(agint32 i=0; i<ne; i++)
	{
		svector += AG_ChangeNumberToString(vector[i]);
		if(i!=ne-1)	svector += _T(",");
	}
	return svector;
}
#endif	//#if AGMAGIC_SUPPORT_MFC
template<class AGARRAY_TYPE>
agtchar* CAGarray<AGARRAY_TYPE>::ToString(agtchar*& svector)
{
	return ToString(m_vector,m_ne,svector);
}
template<class AGARRAY_TYPE>
agtchar* CAGarray<AGARRAY_TYPE>::ToString(AGARRAY_TYPE vector[], agint32 ne, agtchar*& svector)
{
	if(svector)	free(svector);	svector=NULL;
	if(vector==NULL || ne==0)	return svector;

	for(agint32 i=0; i<ne; i++)
	{
		AG_private_tcscat_number(svector,vector[i],agtrue);
		if(i!=ne-1)	CAGmagicStrUtil::private_tcscat(svector,_T(","),agtrue);
	}
	return svector;
}

template<class AGARRAY_TYPE>
agint32 CAGarray<AGARRAY_TYPE>::LSearch(AGARRAY_TYPE value)
{
	if(IsEmpty())	return -1;
	agint32 n=GetSize();
	agint32 i=0;
	for(i=0; i<n; i++) if(GetAt(i)==value) 	break;
	if(i==n)	return -1;
	return i;
}
template<class AGARRAY_TYPE>
agint32 CAGarray<AGARRAY_TYPE>::LSearch(AGARRAY_TYPE value, AGARRAY_TYPE array[], agint32 n)
{
	agint32 i=0;
	for(i=0; i<n; i++)
		if(array[i]==value) break;
	if(i==n)	return -1;
	return i;
}
template<class AGARRAY_TYPE>
agbool CAGarray<AGARRAY_TYPE>::LSearch(AGARRAY_TYPE value, CAGarray* idx)
{
	idx->RemoveAll();
	if(IsEmpty())	return agfalse;
	agint32 n=GetSize();
	for(agint32 i=0; i<n; i++)
        if(GetAt(i)==value) idx->Add(value);
	return idx->GetSize()>0;
}
template<class AGARRAY_TYPE>
agreal64	CAGarray<AGARRAY_TYPE>::Sum()
{
	if(IsEmpty())	return 0;
	agreal64	sum=0;
	for(agint32 i=0; i<m_ne; i++)	sum +=(agreal64)(m_vector[i]);
	return sum;
}

template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::RemoveIfValue(AGARRAY_TYPE e)
{
	if(IsEmpty())	return;
	agint32 idx=LSearch(e);
	if(idx==-1)	return;
	RemoveAt(idx);
}
template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::RemoveSameValues()
{
	if(IsEmpty())	return;
	agint32 i, n=GetSize();
	CAGarray<AGARRAY_TYPE> xa;
	for(i=0; i<n; i++)
		if(xa.LSearch(m_vector[i])==-1)	xa.Add(m_vector[i]);
	CopyFrom(&xa);
}
template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::RemoveSameValues(AGARRAY_TYPE*& vector, agint32& ne)
{
	if(vector==NULL || ne==0)	return;
	CAGarray<AGARRAY_TYPE> xa;
	xa.Import(vector,ne);
	xa.RemoveSameValues();
	xa.Export(vector,ne);
}

template<class AGARRAY_TYPE>
agreal64	CAGarray<AGARRAY_TYPE>::Mean()
{
	if(IsEmpty())	return 0;
	return Sum()/(agreal64)m_ne;
}
template<class AGARRAY_TYPE>
agbool CAGarray<AGARRAY_TYPE>::Normalize(agreal64*& pNorm, agint32& nNorm)
{
	if(pNorm) free(pNorm);
	pNorm=NULL;
	nNorm=0;
	if(IsEmpty())	return agfalse;

	nNorm=m_ne;
	pNorm=(agreal64*)malloc(nNorm*sizeof(agreal64));
	memset(pNorm,0,nNorm*sizeof(agreal64));
	if(m_bIsNorm)
	{
		for(agint32 i=0; i<nNorm; i++)
			pNorm[i]=(agreal64)m_vector[i];
	}
	else
	{
		agreal64	sum=Sum();
		for(agint32 i=0; i<nNorm; i++)
			pNorm[i]=(agreal64)(m_vector[i])/sum;
	}
	return agtrue;
}	

template<class AGARRAY_TYPE>
agbool CAGarray<AGARRAY_TYPE>::Normalize()
{
	if(IsEmpty())		return agfalse;
	if(m_bIsNorm)		return agtrue;

	agreal64	sum=Sum();
	for(agint32 i=0; i<m_ne; i++)
		m_vector[i]=(AGARRAY_TYPE)(((agreal64)(m_vector[i]))/sum);
	m_bIsNorm=agtrue;
	return agtrue;
}
template<class AGARRAY_TYPE>
agbool CAGarray<AGARRAY_TYPE>::Div(agreal64 divisor)
{
	if(IsEmpty())		return agfalse;

	for(agint32 i=0; i<m_ne; i++)
		m_vector[i]=(AGARRAY_TYPE)(((agreal64)(m_vector[i]))/divisor);
	return agtrue;
}
template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::Common(CAGarray* aIn, CAGarray* aResult)
{
	if(aResult!=NULL)
	{
		aResult->RemoveAll();
		if(aIn==NULL || IsEmpty())	return;
		agint32 n=GetSize();
		for(agint32 i=0; i<n; i++)
		{
			AGARRAY_TYPE	e=GetAt(i);
			if(aIn->LSearch(e)!=-1)	aResult->Add(e);
		}
	}
	else
	{
		if(aIn==NULL || IsEmpty())	return;
		for(agint32 i=0; i<GetSize(); i++)
		{
			AGARRAY_TYPE	e=GetAt(i);
			if(aIn->LSearch(e)==-1)
			{
				RemoveAt(i);	i--;
			}
		}
	}
}
template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::Union(const CAGarray* aIn, CAGarray* aResult)
{
	if(aResult!=NULL)
	{
		aResult->RemoveAll();
		if(aIn==NULL || IsEmpty())	return;
		aResult->Append(this);
		aResult->Append(aIn);
		aResult->RemoveSameValues();
	}
	else
	{
		Append(aIn);
		RemoveSameValues();
	}
}
template<class AGARRAY_TYPE>
void CAGarray<AGARRAY_TYPE>::Complement(CAGarray* aIn, CAGarray* aResult)
{
	if(aResult!=NULL)
	{
		aResult->RemoveAll();
		if(aIn==NULL || IsEmpty())	return;
		agint32 n=GetSize();
		for(agint32 i=0; i<n; i++)
		{
			AGARRAY_TYPE	e=GetAt(i);
			if(aIn->LSearch(e)==-1)	aResult->Add(e);
		}
	}
	else
	{
		if(aIn==NULL || IsEmpty())	return;
		for(agint32 i=0; i<GetSize(); i++)
		{
			AGARRAY_TYPE	e=GetAt(i);
			if(aIn->LSearch(e)!=-1)
			{
				RemoveAt(i);	i--;
			}
		}
	}
}


/*******************************class CAGobjPtrArray*******************************/
class AGMAGIC_DECL CAGimageAffMatrix;

/*
template<class AGOBJ_ARRAY_TYPE> class CAGobjPtrArray
Chuc nang:
Cach dung:
Ghi chu:
*/
template<class AGOBJ_ARRAY_TYPE>
class CAGobjPtrArray
{
protected:
	AGOBJ_ARRAY_TYPE**	m_vector;//vector
	agint32				m_ne;//number of element
	agbool				m_bIsNorm;//vector la duoc chuan hoa hay khong, 0: vector co cac gia tri la column MEASURE, 1: vector co cac gia tri la column NORMMEASURE trong ImagesAffinity

	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		throw _T("You must define in devired class");
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		throw _T("You must define in devired class");
	}
	//virtual void	deleteAGOBJ_ARRAY_TYPE(void* the)
	//{
	//	throw _T("You must define in devired class");
	//}
public:

	CAGobjPtrArray();
	virtual ~CAGobjPtrArray();
	virtual void CopyInfoFrom(CAGobjPtrArray* xa);

	virtual void		RemoveAll();
	void				RemoveAllNULL();
	agbool				IsEmpty();
	agbool				CopyFrom(CAGobjPtrArray* xa, agbool bIsCopy=agfalse);
	agbool				TransferFrom(CAGobjPtrArray* xa);
	void				SetSize(agint32 ne, agbool bInit=agfalse);
	AGOBJ_ARRAY_TYPE*	GetAt(agint32 idx, agbool bDetach=agfalse);
	AGOBJ_ARRAY_TYPE*&	ElementAt(agint32 idx);
	const AGOBJ_ARRAY_TYPE*	operator[](agint32 idx) const;
	AGOBJ_ARRAY_TYPE*&	operator[](agint32 idx);
	AGOBJ_ARRAY_TYPE*	CopyAt(agint32 idx);
	void				SetAt(agint32 idx, AGOBJ_ARRAY_TYPE* e, agbool bIsCopy=agfalse);
	void				SetNULLAt(agint32 idx);
	void				InsertAt(agint32 idx, AGOBJ_ARRAY_TYPE* e, agbool bIsCopy=agfalse);
	void				InsertAt(agint32 idx, CAGobjPtrArray*	xa, agbool bIsCopy=agfalse);
	void				Add(AGOBJ_ARRAY_TYPE* e, agbool bIsCopy=agfalse);
	void				RemoveAt(agint32 idx);
	void				DeleteAt(agint32 idx);
	void				DeleteAll();
	void				SetNULLAll();
	void				Append(CAGobjPtrArray* xa, agbool bIsCopy=agfalse);

	agint32				GetSize()		{return m_ne;}
	AGOBJ_ARRAY_TYPE**	GetData()		{return m_vector;}

	agbool				Attach(AGOBJ_ARRAY_TYPE** vector, agint32 ne);
	AGOBJ_ARRAY_TYPE**	Detach(agint32& ne);

	agbool	Import(const AGOBJ_ARRAY_TYPE** vector, const agint32 ne);
	agbool	Export(AGOBJ_ARRAY_TYPE**& vector, agint32& ne);

	virtual void	SetIsNorm(agbool bIsNormVector)	{throw _T("Implement not yet");}
	virtual agbool	IsNorm()							{throw _T("Implement not yet");}
	virtual	agbool	Normalize()					{throw _T("Implement not yet");}

	AGOBJ_ARRAY_TYPE**	private_malloc(agint32 size_of_element);
	AGOBJ_ARRAY_TYPE**	private_realloc(AGOBJ_ARRAY_TYPE** pobj, agint32 old_size, agint32 size);
	void				private_free(AGOBJ_ARRAY_TYPE** pobj, agint32 size_of_element);

	friend class CAGimageAffMatrix;
};

template<class AGOBJ_ARRAY_TYPE>
CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::CAGobjPtrArray()
{
	m_vector=NULL;
	m_ne=0;
	m_bIsNorm=agfalse;
}
template<class AGOBJ_ARRAY_TYPE>
CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::~CAGobjPtrArray()
{
	RemoveAll();
}

template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::RemoveAll()
{
	if(!IsEmpty())
	{
		if(m_vector!=NULL)
		{
			for(agint32 i=0; i<m_ne; i++)
				if(m_vector[i])	delete m_vector[i];

			free(m_vector);
			m_vector=NULL;
		}
		m_ne=0;
	}
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::RemoveAllNULL()
{
	if(IsEmpty())		return;
	for(agint32 i=0; i<m_ne; i++)
	{
		if(m_vector[i]==NULL)
		{
			RemoveAt(i);
			i--;
		}
	}
}
template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::IsEmpty()
{
	return (m_vector==NULL);
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::CopyInfoFrom(CAGobjPtrArray* xa)
{
	m_bIsNorm=xa->m_bIsNorm;
}
template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::CopyFrom(CAGobjPtrArray* xa, agbool bIsCopy)
{
	if(xa==NULL)		throw _T("feature must be not null");
	if(xa->IsEmpty())	return agfalse;
	if(!bIsCopy)
	{
		SetSize(xa->m_ne,agfalse);
		memcpy(m_vector,xa->m_vector,m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
	}
	else
	{
		SetSize(xa->m_ne,agtrue);
		for(agint32 i=0; i<xa->m_ne;i++)
		{
			if(xa->m_vector[i])
				cpyAGOBJ_ARRAY_TYPE(m_vector[i],xa->m_vector[i]);
			else
			{
				if(m_vector[i])		delete m_vector[i];
				m_vector[i]=NULL;
			}
		}
	}
	CopyInfoFrom(xa);
	return agtrue;
}
template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::TransferFrom(CAGobjPtrArray* xa)
{
	if(!CopyFrom(xa,agfalse))	return agfalse;
	if(!xa->IsEmpty())			memset(xa->m_vector,NULL,xa->m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
	CopyInfoFrom(xa);
	return agtrue;
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::SetSize(agint32 ne, agbool bInit)
{
	if(ne<0)	throw _T("Error parameter");
	RemoveAll();

	if(ne>0)
	{
		m_ne=ne;
		m_vector=(AGOBJ_ARRAY_TYPE**)malloc(m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
		memset(m_vector,NULL,m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
		if(bInit)
		{
			for(agint32 i=0; i<m_ne; i++)	m_vector[i]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();
		}
	}
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE* CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::GetAt(agint32 idx, agbool bDetach)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");

	AGOBJ_ARRAY_TYPE*	e=m_vector[idx];
	if(bDetach)			m_vector[idx]=NULL;
	return e;
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE*& CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::ElementAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGOBJ_ARRAY_TYPE>
const AGOBJ_ARRAY_TYPE*	CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::operator[](agint32 idx) const
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE*& CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::operator[](agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	return m_vector[idx];
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE* CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::CopyAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");

	if(m_vector[idx]==NULL)	return NULL;
	AGOBJ_ARRAY_TYPE*		obj=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();
	cpyAGOBJ_ARRAY_TYPE(obj,m_vector[idx]);
	return obj;
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::SetAt(agint32 idx, AGOBJ_ARRAY_TYPE* e, agbool bIsCopy)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	
	if(!bIsCopy)
	{
		if(m_vector[idx]!=NULL)
			delete m_vector[idx];
		m_vector[idx]=e;
	}
	else
	{
		if(e)
		{
			if(m_vector[idx]==NULL)
				m_vector[idx]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();
			cpyAGOBJ_ARRAY_TYPE(m_vector[idx],e);
		}
		else
		{
			if(m_vector[idx]!=NULL)
				delete m_vector[idx];
			m_vector[idx]=NULL;
		}
	}
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::SetNULLAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	m_vector[idx]=NULL;
}

template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::InsertAt(agint32 idx, AGOBJ_ARRAY_TYPE* e, agbool bIsCopy)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");

	agint32				ne=m_ne;
	AGOBJ_ARRAY_TYPE**	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne+1,agfalse);

	//chep phan truoc
	if(idx>0)	memcpy(m_vector,vector,idx*sizeof(AGOBJ_ARRAY_TYPE*));
	SetAt(idx,e,bIsCopy);
	memcpy(m_vector+idx+1,vector+idx,(ne-idx)*sizeof(AGOBJ_ARRAY_TYPE*));

	free(vector);
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::InsertAt(agint32 idx, CAGobjPtrArray* xa, agbool bIsCopy)
{
	if(idx<0 || idx>=m_ne || xa==NULL)	throw _T("Access extra dim vector bound or invalid pointer");
	if(xa->IsEmpty())					return;

	agint32				ne=m_ne;
	AGOBJ_ARRAY_TYPE**	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne+xa->m_ne,agfalse);

	//chep phan truoc
	if(idx>0)	memcpy(m_vector,vector,idx*sizeof(AGOBJ_ARRAY_TYPE*));
	for(agint32 i=0; i<xa->m_ne; i++)
		SetAt(idx+i,xa->m_vector[i],bIsCopy);
	memcpy(m_vector+idx+xa->m_ne,vector+idx,(ne-idx)*sizeof(AGOBJ_ARRAY_TYPE*));

	free(vector);
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Add(AGOBJ_ARRAY_TYPE* e, agbool bIsCopy)
{
	m_ne++;
	if(m_vector==NULL)
		m_vector=(AGOBJ_ARRAY_TYPE**)malloc(m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
	else
		m_vector=(AGOBJ_ARRAY_TYPE**)realloc(m_vector,m_ne*sizeof(AGOBJ_ARRAY_TYPE*));

	m_vector[m_ne-1]=NULL;
	SetAt(m_ne-1,e,bIsCopy);
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::RemoveAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	if(m_ne==1)
	{
		RemoveAll();
		return;
	}
	agint32				ne=m_ne;
	AGOBJ_ARRAY_TYPE**	vector=m_vector;
	m_ne=0;
	m_vector=NULL;	
	SetSize(ne-1,agfalse);

	if(idx>0)
		memcpy(m_vector,vector,idx*sizeof(AGOBJ_ARRAY_TYPE*));
	memcpy(m_vector+idx,vector+idx+1,(ne-idx-1)*sizeof(AGOBJ_ARRAY_TYPE*));

	if(vector[idx]!=NULL)	delete vector[idx];
	free(vector);
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::DeleteAt(agint32 idx)
{
	if(idx<0 || idx>=m_ne)	throw _T("Access extra dim vector bound");
	if(m_vector[idx]!=NULL)
	{
		delete m_vector[idx];
		m_vector[idx]=NULL;
	}
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::DeleteAll()
{
	if(IsEmpty()) return;
	for(agint32 i=0; i<m_ne; i++)
	{
		if(m_vector[i]!=NULL)
		{
			delete m_vector[i];
			m_vector[i]=NULL;
		}
	}
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::SetNULLAll()
{
	if(IsEmpty())	return;
	memset(m_vector,NULL,m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
}

template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Append(CAGobjPtrArray* xa, agbool bIsCopy)
{
	if(xa==NULL)			throw _T("Invalid pointer parameter");
	if(xa->m_ne==0)			return;

	agint32	ne=m_ne + xa->m_ne;
	if(m_vector==NULL)
		m_vector=(AGOBJ_ARRAY_TYPE**)malloc(ne*sizeof(AGOBJ_ARRAY_TYPE*));
	else
		m_vector=(AGOBJ_ARRAY_TYPE**)realloc(m_vector,ne*sizeof(AGOBJ_ARRAY_TYPE*));
	memset(m_vector+m_ne,NULL,xa->m_ne*sizeof(AGOBJ_ARRAY_TYPE*));

	if(!bIsCopy)
		memcpy(m_vector+m_ne,xa->m_vector,xa->m_ne*sizeof(AGOBJ_ARRAY_TYPE*));
	else
	{
		for(agint32 i=0; i<xa->m_ne; i++)
		{
			if(xa->m_vector[i]==NULL)
			{
				if(m_vector[m_ne+i]!=NULL)
					delete m_vector[m_ne+i];
				m_vector[m_ne+i]=NULL;
			}
			else
			{
				if(m_vector[m_ne+i]==NULL)
					m_vector[m_ne+i]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();
				cpyAGOBJ_ARRAY_TYPE(m_vector[m_ne+i],xa->m_vector[i]);
			}
		}
	}

	m_ne=ne;
}
template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Attach(AGOBJ_ARRAY_TYPE** vector, agint32 ne)
{
	if(vector==NULL || ne==0)	return agfalse;
	RemoveAll();
	m_vector=vector;
	m_ne=ne;
	return agtrue;
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE** CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Detach(agint32& ne)
{
	if(IsEmpty())
	{
		ne=0;
		return NULL;
	}
	ne=m_ne;
	return m_vector;
}

template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Import(const AGOBJ_ARRAY_TYPE** vector, const agint32 ne)
{
	if(vector==NULL || ne<=0)	return agfalse;

	SetSize(ne,agtrue);
	for(agint32 i=0; i<ne;i++)
	{
		if(vector[i]!=NULL)
			cpyAGOBJ_ARRAY_TYPE(m_vector[i],vector[i]);
		else
		{
			if(m_vector[i]!=NULL)	delete m_vector[i];
			m_vector[i]=NULL;
		}
	}
	return agtrue;
}
template<class AGOBJ_ARRAY_TYPE>
agbool CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::Export(AGOBJ_ARRAY_TYPE**& vector, agint32& ne)
{
	if(IsEmpty())	return agfalse;
	ne=m_ne;
	vector=(AGOBJ_ARRAY_TYPE**)malloc(ne*sizeof(AGOBJ_ARRAY_TYPE*));
	for(agint32 i=0; i<ne;i++)
	{
		if(m_vector[i]!=NULL)
		{
			vector[i]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();
			cpyAGOBJ_ARRAY_TYPE(vector[i],m_vector[i]);
		}
		else
			vector[i]=NULL;
	}
	return agtrue;
}

template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE** CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::private_malloc(agint32 size_of_element)
{
	AGOBJ_ARRAY_TYPE** pobj=(AGOBJ_ARRAY_TYPE**)malloc((size_t)size_of_element*sizeof(AGOBJ_ARRAY_TYPE*));
	for(agint32 i=0; i<size_of_element; i++)
		pobj[i]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE(); 
	return pobj;
}
template<class AGOBJ_ARRAY_TYPE>
AGOBJ_ARRAY_TYPE** CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::private_realloc(AGOBJ_ARRAY_TYPE** pobj, agint32 old_size, agint32 size)
{
	if(old_size > size)
	{
		agint32 n=old_size-size;
		for(agint32 i=0; i<n; i++)
		{
			if(pobj[i+size]!=NULL)
				delete pobj[i+size];
		}
	}
	pobj=(AGOBJ_ARRAY_TYPE**)realloc(pobj,size*sizeof(AGOBJ_ARRAY_TYPE*));
	if(old_size < size)
	{
		agint32 n=size-old_size;
		for(agint32 i=0; i<n; i++)
			pobj[i+old_size]=(AGOBJ_ARRAY_TYPE*)newAGOBJ_ARRAY_TYPE();	
	}
	return pobj;
}
template<class AGOBJ_ARRAY_TYPE>
void CAGobjPtrArray<AGOBJ_ARRAY_TYPE>::private_free(AGOBJ_ARRAY_TYPE** pobj, agint32 size_of_element)
{
	for(agint32 i=0; i<size_of_element; i++)
	{
		if(pobj[i]!=NULL)
			delete pobj[i];
	}
	free(pobj);
}

/*******************************class CAGmagicElement*******************************/

class AGMAGIC_DECL CAGmagicElement
{
public:
	virtual CAGmagicElement*	CreateMe()=0;
	virtual agbool				CopyFrom(CAGmagicElement* pAGmagicElement)=0;

	virtual aguint_id		GetID()=0;
	virtual agfreal			GetValue()=0;
};

class AGMAGIC_DECL CAGmagicElementPtrArray : public CAGobjPtrArray<CAGmagicElement>
{
protected:
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGmagicElement* pAGmagicElementDst=(CAGmagicElement*)dst;
		CAGmagicElement* pAGmagicElementSrc=(CAGmagicElement*)src;
		pAGmagicElementDst->CopyFrom(pAGmagicElementSrc);
	}
public:
	CAGmagicElementPtrArray();
	virtual ~CAGmagicElementPtrArray();

	agbool		GetValueAt(agint32 idx, agfreal& value);
	agbool		GetIDAt(agint32 idx, aguint_id& ID);

	agint32		LSearchID(aguint_id ID);
	agbool		GetValueAtID(aguint_id ID, agfreal& value);

};

/*******************************class CAGbuRectVec*******************************/
class AGMAGIC_DECL CAGtdRectVec;
class AGMAGIC_DECL CAGbuRectMatrix;
class AGMAGIC_DECL CAGbuRectVec : public CAGbaseArray<AGBU_RECT>
{
public:
	CAGbuRectVec();
	virtual ~CAGbuRectVec();

	agint32 TotalWidth(agint32 wHinge=0);
	agint32 TotalHeight();

	void	Import(CAGtdRectVec* pRectVec);
	void	Import(CAGbuRectMatrix* pRectMatrix);

	agbool	CreateByCut(AGBU_RECT TotalRect, SIZE block_size);
	agbool	CreateByCut(AGBU_RECT TotalRect, agint32 nRows, agint32 nCols);
	agbool	CreateByCut(AGBU_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
};
/*******************************class CAGbuRectMatrix*******************************/
class AGMAGIC_DECL CAGtdRectMatrix;
class AGMAGIC_DECL CAGbuRectMatrix : public CAGobjPtrArray<CAGbuRectVec>
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGbuRectVec();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGbuRectVec*	dstRectVec=(CAGbuRectVec*)dst;
		CAGbuRectVec*	srcRectVec=(CAGbuRectVec*)src;
		dstRectVec->CopyFrom(srcRectVec);
	}
public:
	CAGbuRectMatrix();
	virtual ~CAGbuRectMatrix();

	agint32 TotalWidth(agint32	wHinge=0);
	agint32 TotalHeight(agint32	hHinge=0);

	void	Import(CAGtdRectMatrix* pRectMatrix);

	agbool	CreateByCut(AGBU_RECT TotalRect, SIZE block_size);
	agbool	CreateByCut(AGBU_RECT TotalRect, agint32 nRows, agint32 nCols);
	agbool	CreateByCut(AGBU_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
};

/*******************************class CAGtdRectVec*******************************/
class AGMAGIC_DECL CAGtdRectMatrix;
class AGMAGIC_DECL CAGtdRectVec : public CAGbaseArray<AGTD_RECT>
{
public:
	CAGtdRectVec();
	virtual ~CAGtdRectVec();

	agint32 TotalWidth(agint32 wHinge=0);
	agint32 TotalHeight();

	void	Import(CAGbuRectVec* pRectVec);
	void	Import(CAGtdRectMatrix* pRectMatrix);

	agbool	CreateByCut(AGTD_RECT TotalRect, SIZE block_size);
	agbool	CreateByCut(AGTD_RECT TotalRect, agint32 nRows, agint32 nCols);
	agbool	CreateByCut(AGTD_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
};
/*******************************class CAGtdRectMatrix*******************************/

class AGMAGIC_DECL CAGtdRectMatrix : public CAGobjPtrArray<CAGtdRectVec>
{
protected:
	virtual	void*	newAGOBJ_ARRAY_TYPE()
	{
		return new CAGtdRectVec();
	}
	virtual	void	cpyAGOBJ_ARRAY_TYPE(void* dst, const void* src)
	{
		CAGtdRectVec*	dstRectVec=(CAGtdRectVec*)dst;
		CAGtdRectVec*	srcRectVec=(CAGtdRectVec*)src;
		dstRectVec->CopyFrom(srcRectVec);
	}
public:
	CAGtdRectMatrix();
	virtual ~CAGtdRectMatrix();

	agint32 TotalWidth(agint32	wHinge=0);
	agint32 TotalHeight(agint32	hHinge=0);

	void Import(CAGbuRectMatrix* pRectMatrix);

	agbool	CreateByCut(AGTD_RECT TotalRect, SIZE block_size);
	agbool	CreateByCut(AGTD_RECT TotalRect, agint32 nRows, agint32 nCols);
	agbool	CreateByCut(AGTD_RECT TotalRect, agint32 CXsizes[], agint32 nCXsizes, agint32 CYsizes[], agint32 nCYsizes);
};

#endif // !defined(AGDATA_STRUCT_H__DEE6124F_A429_11D2_84B1_00C0DFF84685__INCLUDED_)
