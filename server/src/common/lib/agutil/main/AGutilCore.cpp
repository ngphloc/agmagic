#include "AGutilCore.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/******************************class CAGmagicMicUtil*******************************************/

#if AGMAGIC_SUPPORT_MFC

CAGmagicMicUtil::CAlgTime::CAlgTime()
{
	m_CurBeginTime=m_CurEndTime=0;
	m_pAttachFile=NULL;
}

CAGmagicMicUtil::CAlgTime::~CAlgTime()
{
	m_CurBeginTime=m_CurEndTime=0;
	DetachFile(agtrue);
}

void CAGmagicMicUtil::CAlgTime::Begin()
{
   struct _timeb timebuffer;
   //_ftime_s(&timebuffer);
    _ftime(&timebuffer);
	m_CurBeginTime=timebuffer.time + (agreal64)timebuffer.millitm/1000;
}

void CAGmagicMicUtil::CAlgTime::End()
{
   struct _timeb timebuffer;
   //_ftime_s(&timebuffer);
   _ftime(&timebuffer);
	m_CurEndTime=timebuffer.time + (agreal64)timebuffer.millitm/1000;
}
agreal64 CAGmagicMicUtil::CAlgTime::GetSpan()
{
	return m_CurEndTime-m_CurBeginTime;
}
CString	CAGmagicMicUtil::CAlgTime::GetSpanStr()
{
	agreal64	timevr=GetSpan();
	time_t	timevu=(time_t)((aguint64)(timevr));

	CTimeSpan	ts(timevu);
	CString		result;

	result.Format(_T("%lud:%luh:%lum:%lus:%lums"),ts.GetDays(),
				ts.GetHours(),ts.GetMinutes(),ts.GetSeconds(),
				(aguint32)((timevr-(agreal64)timevu)*1000));
	return result;
}
CString CAGmagicMicUtil::CAlgTime::GetSpanSecsStr()
{
	agreal64	timevr=GetSpan();
	time_t	timevu=(time_t)((aguint64)(timevr));

	CTimeSpan	ts(timevu);
	CString		result;

	result.Format(_T("%lus:%lums"),ts.GetTotalSeconds(),(aguint32)((timevr-(agreal64)timevu)*1000));
	return result;
}
aguint64 CAGmagicMicUtil::CAlgTime::GetTotalSpanSecs()
{
	agreal64	timevr=GetSpan();
	time_t	timevu=(time_t)((aguint64)(timevr));
	aguint64	result;

	CTimeSpan	ts(timevu);
	result=ts.GetTotalSeconds() + (aguint64)(timevr-(agreal64)timevu);
	return result;
}
aguint32 CAGmagicMicUtil::CAlgTime::GetTotalSpanMiliSecs()
{
	return (aguint32)(GetSpan() * 1000);
}
void CAGmagicMicUtil::CAlgTime::AttachFile(const agtchar* FilePath)
{
	DetachFile(agtrue);
	m_pAttachFile=new CStdioFile(FilePath, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::shareDenyNone);
}
void CAGmagicMicUtil::CAlgTime::DetachFile(agbool bDeleteFile)
{
	if(m_pAttachFile)
	{
		m_pAttachFile->Flush();
		m_pAttachFile->Close();
		delete m_pAttachFile;
		m_pAttachFile=NULL;
	}
}
void CAGmagicMicUtil::CAlgTime::OutResult(const agtchar* algName, agbool shorten)
{
	CString tsStr;
	if(shorten)
	{
		tsStr=_T("Algorithm ");
		tsStr +=algName;
		tsStr +=_T(" cost ");
	}
	else
	{
		TCHAR*	timeline=NULL;
		time_t	curTime=time(NULL);
		//TCHAR timeline2[64]; timeline=timeline2;_tctime_s(timeline, 64, &curTime);
		timeline=_tctime(&curTime);
		tsStr +=_T("At ");
		tsStr +=timeline;

		tsStr +=_T(", Algorithm ");
		tsStr +=algName;
		tsStr +=_T(" cost ");
	}

	if(shorten)
		tsStr +=GetSpanSecsStr();
	else
		tsStr +=GetSpanStr();

	tsStr +=_T("\n");
	if(m_pAttachFile==NULL)
		AfxMessageBox(tsStr,MB_OK,0);
	else
	{
		m_pAttachFile->WriteString(tsStr);
		m_pAttachFile->SeekToEnd();
	}
}


void CAGmagicMicUtil::ChangeURLFromWin(CString& URL)
{
	URL.Replace(_T('\\'),_T('/'));
}
void CAGmagicMicUtil::ChangeURLToWin(CString& URL)
{
	CString path;
	CString protocol=_T("://");
	aguint32 idx=URL.Find(protocol);
	path=URL.Right(URL.GetLength()-(idx+protocol.GetLength()));
	path.Replace(_T('/'),_T('\\'));

	protocol=URL.Left(idx)+protocol;
	
	URL=protocol+path;
}
CString CAGmagicMicUtil::GetLocalPathFromURL(CString& URL)
{
	CString path;
	CString protocol=_T("://");
	aguint32 idx=URL.Find(protocol);
	path=URL.Right(URL.GetLength()-(idx+protocol.GetLength()));
	return path;
}
void CAGmagicMicUtil::DrawBitmap(HDC hDC, HBITMAP hBmp, aguint32 x, aguint32 y)
{
	
	HDC hMemDC=::CreateCompatibleDC(hDC);
	HBITMAP hOldBmp=(HBITMAP)::SelectObject(hMemDC,hBmp);
	BITMAP bmp;
	GetObject(hBmp,sizeof(BITMAP),&bmp);
	::BitBlt(hDC,x,y,bmp.bmWidth,bmp.bmHeight,hMemDC,0,0,SRCCOPY);
	SelectObject(hMemDC,hOldBmp);
	
	::DeleteDC(hMemDC);
	
}

void AFXAPI AfxLockGlobals(int nLockType);
void AFXAPI AfxUnlockGlobals(int nLockType);
HINSTANCE CAGmagicMicUtil::FindResourceHandleInDynamicDLL(LPCTSTR szResourceName, LPCTSTR szResourceType)
{
	//Truy tim trong DLL
	AFX_MODULE_STATE*	pModuleState = AfxGetModuleState();
	AfxLockGlobals(0);
	for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL;
		pDLL = pDLL->m_pNextDLL)
	{
		if (!pDLL->m_bSystem && pDLL->m_hResource != NULL &&
			::FindResource(pDLL->m_hResource, szResourceName, szResourceType) != NULL)
		{
			// found it in a DLL
			AfxUnlockGlobals(0);
			return pDLL->m_hResource;
		}
	}
	AfxUnlockGlobals(0);
	return NULL;
}
agbool CAGmagicMicUtil::FindArray(CDWordArray &aDW, aguint32 key, agint32& idx)
{
	idx=-1;
	aguint32 n=aDW.GetSize();
	if(n==0)
		return agfalse;
	aguint32 i=0;
	for(i=0; i<n; i++)
	{
		if(aDW[i]==key)
			break;
	}
	idx=i;
	return ((i<n)?agtrue:agfalse);
}
agbool CAGmagicMicUtil::FindArray(CDWordArray& aDW, aguint32 key, CDWordArray& aIdx)
{
	aguint32 n=aDW.GetSize();
	if(n==0)
		return agfalse;
	aIdx.RemoveAll();
	for(aguint32 i=0; i<n; i++)
	{
		if(aDW[i]==key)
			aIdx.Add(i);
	}
	return ((aIdx.GetSize()>0)?agtrue:agfalse);
}
void CAGmagicMicUtil::SortArray(CDWordArray &aDW, agbool dec)
{
	aguint32 n=aDW.GetSize();
	for(aguint32 i=0; i<n-1; i++)
		for(aguint32 j=i+1; j<n; j++)
		{
			agbool bFlag=(dec)?aDW[i]<aDW[j]:aDW[i]>aDW[j];
			if(bFlag)
			{
				aguint32 t=aDW[i];
				aDW[i]=aDW[j];
				aDW[j]=t;
			}
		}
}
void CAGmagicMicUtil::SortArray(CDWordArray& aDW, CDWordArray& aKey, agbool dec)
{
	aguint32 n=aDW.GetSize();
	for(aguint32 i=0; i<n-1; i++)
		for(aguint32 j=i+1; j<n; j++)
		{
			agbool bFlag=(dec)?aKey[i]<aKey[j]:aKey[i]>aKey[j];
			if(bFlag)
			{
				aguint32 t=aKey[i];
				aKey[i]=aKey[j];
				aKey[j]=t;

				t=aDW[i];
				aDW[i]=aDW[j];
				aDW[j]=t;
			}
		}
}
#endif	//#if AGMAGIC_SUPPORT_MFC

agtchar* CAGmagicMicUtil::AGconvertFromVariantToStr(_variant_t& varValue, agtchar*& strValue)
{
	if(strValue)	free(strValue);	
	strValue=NULL;

	if(varValue.vt==VT_EMPTY || varValue.vt==VT_NULL)
		strValue=NULL;
	else if(varValue.vt==VT_BSTR)
	{
		_bstr_t		bstr_v=varValue;
		agtchar*	str_v=(agtchar*)(bstr_v);
		CAGmagicStrUtil::private_tcscat(strValue,str_v,agtrue);
	}
	else strValue=NULL;

	return strValue;
}
aguint_id CAGmagicMicUtil::AGconvertFromVariantToID(_variant_t& varValue)
{
	return AGconvertFromVariantToNumber<aguint_id>(varValue);
}
void CAGmagicMicUtil::ChangeTDtoBU(agint32 height, AGBU_RECT* pDstRect, AGTD_RECT* pSrcRect)
{
	pDstRect->left=pSrcRect->left;
	pDstRect->top=height-AGMAX(0,AGMIN(pSrcRect->top,height));
	pDstRect->right=pSrcRect->right;
	pDstRect->bottom=height-AGMAX(0,AGMIN(pSrcRect->bottom,height));
}
void CAGmagicMicUtil::ChangeTDtoBU(agint32 height, AGBU_POINT* pDstPoint, AGTD_POINT* pSrcPoint)
{
	pDstPoint->x=pSrcPoint->x;
	pDstPoint->y=height-AGMAX(0,AGMIN(pSrcPoint->y,height));
}
void CAGmagicMicUtil::ChangeBUtoTD(agint32 height, AGTD_RECT* pDstRect, AGBU_RECT* pSrcRect)
{
	pDstRect->left=pSrcRect->left;
	pDstRect->top=height-AGMAX(0,AGMIN(pSrcRect->top,height));
	pDstRect->right=pSrcRect->right;
	pDstRect->bottom=height-AGMAX(0,AGMIN(pSrcRect->bottom,height));
}
void CAGmagicMicUtil::ChangeBUtoTD(agint32 height, AGTD_POINT* pDstPoint, AGBU_POINT* pSrcPoint)
{
	pDstPoint->x=pSrcPoint->x;
	pDstPoint->y=height-AGMAX(0,AGMIN(pSrcPoint->y,height));
}

/************************class CAGmagicStrUtil***********************************/

#if AGMAGIC_SUPPORT_MFC

void CAGmagicStrUtil::SplitString(CString& src, CString key, CStringArray& aS)
{
	if(src.IsEmpty())
		return;
	aS.RemoveAll();
	aguint32	srclen=src.GetLength(), keylen=key.GetLength();
	aguint32	i=0;
	while(i<srclen)
	{
		agint32 idx=src.Find(key,i);
		if(idx==-1)
		{
			aS.Add(src.Right(srclen-i));
			break;
		}
		aS.Add(src.Mid(i,idx-i));
		i=idx+keylen;
	}
	
}
void CAGmagicStrUtil::SplitString(CString& src, CString key, CDWordArray& aDW)
{
	if(src.IsEmpty())
		return;
	aDW.RemoveAll();
	aguint32	srclen=src.GetLength(), keylen=key.GetLength();
	aguint32	i=0;
	while(i<srclen)
	{
		CString sValue;
		agint32 idx=src.Find(key,i);
		if(idx==-1)
		{
			aDW.Add(_ttol(src.Right(srclen-i)));
			break;
		}
		aDW.Add(_ttol(src.Mid(i,idx-i)));
		i=idx+keylen;
	}
	
}
void CAGmagicStrUtil::SplitString(CString& src, CString key, CArray<agreal64, agreal64>& aR)
{
	if(src.IsEmpty())
		return;
	aR.RemoveAll();
	aguint32	srclen=src.GetLength(), keylen=key.GetLength();
	aguint32	i=0;
	while(i<srclen)
	{
		CString sValue;
		agint32 idx=src.Find(key,i);
		if(idx==-1)
		{
		#ifdef	_tstof
			aR.Add(_tstof(src.Right(srclen-i)));
		#else
			throw _T("Implement not yet");
		#endif
			break;
		}
	#ifdef	_tstof
		aR.Add(_tstof(src.Mid(i,idx-i)));
	#else
		throw _T("Implement not yet");
	#endif
		i=idx+keylen;
	}
}
CString CAGmagicStrUtil::CatString(CStringArray& aS, CString key)
{
	CString dst;
	aguint32 n=aS.GetSize();
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
			dst+=aS[i]+key;
		dst+=aS[i];
	}
	else if(n>0)
		dst+=aS[0];
	return dst;
}
CString CAGmagicStrUtil::CatString(CStringArray* paS, CString key)
{
	CString dst;
	if(paS==NULL)	return dst;
	aguint32 n=paS->GetSize();
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
			dst+=paS->GetAt(i)+key;
		dst+=paS->GetAt(i);
	}
	else if(n>0)
		dst+=paS->GetAt(0);
	return dst;
}
CString CAGmagicStrUtil::CatString(CDWordArray& aDW, CString key)
{
	CString dst;
	aguint32 n=aDW.GetSize();
	TCHAR s[64];
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
		{
			//_ltot_s(aDW[i],s,64,10);
			_ltot(aDW[i],s,10);
			dst += s;
			dst+=key;
		}
		//_ltot_s(aDW[i],s,64,10);
		_ltot(aDW[i],s,10);
		dst += s;
	}
	else if(n>0)
	{
		//_ltot_s(aDW[0],s,64,10);
		_ltot(aDW[0],s,10);
		dst += s;
	}
	return dst;
}
CString CAGmagicStrUtil::CatString(CDWordArray* paDW, CString key)
{
	CString dst;
	if(paDW==NULL)	return dst;
	aguint32 n=paDW->GetSize();
	TCHAR s[64];
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
		{
			//_ltot_s(paDW->GetAt(i),s,64,10);
			_ltot(paDW->GetAt(i),s,10);
			dst+=s;
			dst+=key;
		}
		//_ltot_s(paDW->GetAt(i),s,64,10);
		_ltot(paDW->GetAt(i),s,10);
		dst+=s;
	}
	else if(n>0)
	{
		//_ltot_s(paDW->GetAt(0),s,64,10);
		_ltot(paDW->GetAt(0),s,10);
		dst+=s;
	}
	return dst;
}

CString CAGmagicStrUtil::CatString(CArray<agreal64, agreal64>& aR, CString key)
{
	CString dst;
	aguint32 n=aR.GetSize();
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
		{
			dst +=CAGmagicStrUtil::ChangeReal64ToString(aR.GetAt(i));
			dst +=key;
		}
		dst +=CAGmagicStrUtil::ChangeReal64ToString(aR.GetAt(i));
	}
	else if(n>0)
		dst +=CAGmagicStrUtil::ChangeReal64ToString(aR.GetAt(0));
	return dst;
}
CString CAGmagicStrUtil::CatString(CArray<agreal64, agreal64>* paR, CString key)
{
	CString dst;
	aguint32 n=paR->GetSize();
	if(n>1)
	{
		aguint32 i=0;
		for(i=0; i<n-1; i++)
		{
			dst +=CAGmagicStrUtil::ChangeReal64ToString(paR->GetAt(i));
			dst +=key;
		}
		dst +=CAGmagicStrUtil::ChangeReal64ToString(paR->GetAt(i));
	}
	else if(n>0)
		dst +=CAGmagicStrUtil::ChangeReal64ToString(paR->GetAt(0));
	return dst;
}
#endif	//#if AGMAGIC_SUPPORT_MFC

#if AGMAGIC_SUPPORT_MFC
CString CAGmagicStrUtil::ChangeIntegerToString(agint32 x)
{
	agtchar sNumber[64];
	//_ltot_s(x,sNumber,64,10);
	_ltot(x,sNumber,10);
	CString sX=sNumber;
	return sX;
}
CString CAGmagicStrUtil::ChangeIntegerToString(aguint32 x)
{
	agtchar sNumber[64];
	//_ultot_s(x,sNumber,64,10);
	_ultot(x,sNumber,10);
	CString sX=sNumber;
	return sX;
}
CString CAGmagicStrUtil::ChangeIntegerToString(agint64 x)
{
	agtchar sNumber[64];
	//_i64tot_s(x,sNumber,64,10);
	_i64tot(x,sNumber,10);
	CString sX=sNumber;
	return sX;
}
CString CAGmagicStrUtil::ChangeIntegerToString(aguint64 x)
{
	agtchar sNumber[64];
	//_ui64tot_s(x,sNumber,64,10);
	_ui64tot(x,sNumber,10);
	CString sX=sNumber;
	return sX;
}
CString CAGmagicStrUtil::ChangeReal64ToString(agreal64 x)
{
//	CString fi;
//	agchar sNumber[128];
//	_gcvt(x,64,sNumber);
//
//#if defined(UNICODE) || defined(_UNICODE)
//	agwchar wsNumber[64];
//	MultiByteToWideChar(CP_ACP, 0,sNumber,-1,wsNumber,sizeof(wsNumber)/sizeof(wsNumber[0]));
//	fi=wsNumber;
//	//CP_ACP			:ANSI code page 
//	//CP_MACCP			:Macintosh code page 
//	//CP_OEMCP OEM		:code page 
//	//CP_SYMBOL			:Windows 2000/XP: Symbol code page (42) 
//	//CP_THREAD_ACP		:Windows 2000/XP: The current thread's ANSI code page 
//	//CP_UTF7			:Windows 98/Me, Windows NT 4.0 and later: Translate using UTF-7 
//	//CP_UTF8 
//#else	//#if defined(UNICODE) || defined(_UNICODE)
//	fi=sNumber;
//#endif	//#if defined(UNICODE) || defined(_UNICODE)
//	return fi;

	agchar	sNumber[64];
	//_stprintf_s(sNumber,64,_T("%.12f"),x);
	_stprintf(sNumber,_T("%.12f"),x);
	private_tcstrimR(sNumber,_T("0"));
	private_tcstrimR(sNumber,_T("."));
	return CString(sNumber);
}
CString CAGmagicStrUtil::ChangeHighestIntegerToString(agint_highest x)
{
	return ChangeIntegerToString((agint64)x);
}
CString CAGmagicStrUtil::ChangeHighestIntegerToString(aguint_highest x)
{
	return ChangeIntegerToString((aguint64)x);
}
CString CAGmagicStrUtil::ChangeIDToString(aguint_id id)
{
	return ChangeHighestIntegerToString((aguint_highest)id);
}
CString CAGmagicStrUtil::ChangeTimeToNumberString(time_t t)
{
	return ChangeHighestIntegerToString((aguint_highest)t);
}
#endif	//#if AGMAGIC_SUPPORT_MFC

agtchar*	CAGmagicStrUtil::ChangeIntegerToString(agint32 x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//_ltot_s(x,sNumber,size_in_character,10);
	_ltot(x,sNumber,10);
	return sNumber;
}
agtchar*	CAGmagicStrUtil::ChangeIntegerToString(aguint32 x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//_ultot_s(x,sNumber,size_in_character,10);
	_ultot(x,sNumber,10);
	return sNumber;
}

agtchar*	CAGmagicStrUtil::ChangeIntegerToString(agint64 x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//_i64tot_s(x,sNumber,size_in_character,10);
	_i64tot(x,sNumber,10);
	return sNumber;
}
agtchar*	CAGmagicStrUtil::ChangeIntegerToString(aguint64 x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//_ui64tot_s(x,sNumber,size_in_character,10);
	_ui64tot(x,sNumber,10);
	return sNumber;
}
agtchar*	CAGmagicStrUtil::ChangeReal64ToString(agreal64 x, agtchar tcsNumber[]/*, agint32 size_in_character*/)
{
//	agchar sNumber[64];
//	_gcvt(x,64,sNumber);
//
//#if defined(UNICODE) || defined(_UNICODE)
//	agwchar wsNumber[128];
//	MultiByteToWideChar(CP_ACP, 0,sNumber,-1,wsNumber,sizeof(wsNumber)/sizeof(wsNumber[0]));
//	_tcscpy(tcsNumber,wsNumber);
//	//CP_ACP			:ANSI code page 
//	//CP_MACCP			:Macintosh code page 
//	//CP_OEMCP OEM		:code page 
//	//CP_SYMBOL			:Windows 2000/XP: Symbol code page (42) 
//	//CP_THREAD_ACP		:Windows 2000/XP: The current thread's ANSI code page 
//	//CP_UTF7			:Windows 98/Me, Windows NT 4.0 and later: Translate using UTF-7 
//	//CP_UTF8 
//#else	//#if defined(UNICODE) || defined(_UNICODE)
//	_tcscpy(tcsNumber,sNumber);
//#endif	//#if defined(UNICODE) || defined(_UNICODE)
//	return tcsNumber;

	//_stprintf_s(tcsNumber,size_in_character,_T("%.12f"),x);
	_stprintf(tcsNumber,_T("%.12f"),x);
	private_tcstrimR(tcsNumber,_T("0"));
	private_tcstrimR(tcsNumber,_T("."));
	return tcsNumber;
}

agtchar*	CAGmagicStrUtil::ChangeHighestIntegerToString(agint_highest x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//ChangeIntegerToString((agint64)x,sNumber,size_in_character);
	ChangeIntegerToString((agint64)x,sNumber);
	return sNumber;
}
agtchar*	CAGmagicStrUtil::ChangeHighestIntegerToString(aguint_highest x, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//ChangeIntegerToString((aguint64)x,sNumber,size_in_character);
	ChangeIntegerToString((aguint64)x,sNumber);
	return sNumber;
}

agtchar*	CAGmagicStrUtil::ChangeIDToString(aguint_id id, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//return ChangeHighestIntegerToString((aguint_highest)id,sNumber,size_in_character);
	return ChangeHighestIntegerToString((aguint_highest)id,sNumber);
}
agtchar*	CAGmagicStrUtil::ChangeTimeToNumberString(time_t t, agtchar sNumber[]/*, agint32 size_in_character*/)
{
	//return ChangeHighestIntegerToString((aguint_highest)t,sNumber,size_in_character);
	return ChangeHighestIntegerToString((aguint_highest)t,sNumber);
}

agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, const agtchar* src, agbool bIsResize)
{
	if(src==NULL)	return dst;
	if(bIsResize)
	{
		agint32	src_len=(agint32)_tcslen(src);
		agint32	dst_len=(dst==NULL)?0:(agint32)_tcslen(dst);
		if(dst_len==0 && dst!=NULL)	{free(dst); dst=NULL;}
		if(src_len==0)	return dst;
		
		agint32	len=src_len + dst_len;
		if(dst)
		{
			dst=(agtchar*)realloc(dst,(len+1)*sizeof(agtchar));
			//_tcscat_s(dst,len+1,src);
			_tcscat(dst,src);
			return dst;
		}
		else
		{
			dst=(agtchar*)malloc((len+1)*sizeof(agtchar));
			//_tcscpy_s(dst,len+1,src);
			_tcscpy(dst,src);
			return dst;
		}
	}
	else
	{
		return _tcscat(dst,src);
	}
}
agtchar* CAGmagicStrUtil::private_tcscat(agtchar*& dst, const agtchar ch, agbool bIsResize)
{
	if(ch==0)	return dst;
	agtchar	src[]=_T(" ");	src[0]=ch;
	return private_tcscat(dst,src,bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, agint32 x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, aguint32 x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, agint64 x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, aguint64 x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat(agtchar*& dst, agreal64 x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeReal64ToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeReal64ToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat_highest(agtchar*& dst, agint_highest x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeHighestIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeHighestIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat_highest(agtchar*& dst, aguint_highest x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeHighestIntegerToString(x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeHighestIntegerToString(x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat_id(agtchar*& dst, aguint_id x, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeHighestIntegerToString((aguint_highest)x,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeHighestIntegerToString((aguint_highest)x,sNumber),bIsResize);
}
agtchar*	CAGmagicStrUtil::private_tcscat_time(agtchar*& dst, time_t t, agbool bIsResize)
{
	agtchar	sNumber[64];
	//return private_tcscat(dst,ChangeHighestIntegerToString((aguint_highest)t,sNumber,64),bIsResize);
	return private_tcscat(dst,ChangeHighestIntegerToString((aguint_highest)t,sNumber),bIsResize);
}

agtchar*	CAGmagicStrUtil::private_tcstrimL(agtchar pData[], const agtchar* lpszTargets)
{	
	LPCTSTR lpsz = pData;
	while (*lpsz != _T('\0'))
	{
		if (_tcschr(lpszTargets, *lpsz) == NULL)
			break;
		lpsz = _tcsinc(lpsz);
	}

	if (lpsz != pData)
	{
		// fix up data and length
		agint32 nDataLength = _tcslen(pData) - (lpsz - pData);
		memmove(pData, lpsz, (nDataLength+1)*sizeof(agtchar));

		//agtchar*	pOldData=pData;
		//pData=(agtchar*)malloc((nDataLength+1)*sizeof(agtchar));
		//_tcscpy(pData,lpsz);
	}
	return pData;
}
agtchar*	CAGmagicStrUtil::private_tcstrimR(agtchar pData[], const agtchar* lpszTargetList)
{	
	agtchar* lpsz = pData;
	agtchar* lpszLast = NULL;

	while (*lpsz != _T('\0'))
	{
		if (_tcschr(lpszTargetList, *lpsz) != NULL)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = _tcsinc(lpsz);
	}

	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';

		//agint32	nDataLength = lpszLast - pData;
		//pData=(agtchar*)realloc(pData,(nDataLength+1)*sizeof(agtchar));
	}
	return pData;
}
agtchar* CAGmagicStrUtil::private_tcstrim(agtchar pData[], const agtchar* lpszTargetList)
{
	private_tcstrimL(pData,lpszTargetList);
	private_tcstrimR(pData,lpszTargetList);
	return pData;
}
void CAGmagicStrUtil::replace(agtchar data[], agtchar ch, agtchar repch)
{
	agtchar* str=_tcschr(data,ch);
	while(str!=NULL)
	{
		*str=repch;
		str ++;
		str=_tcschr(str,ch);
	}
}
agtchar* CAGmagicStrUtil::private_tcsstr(agtchar string[], agtchar strCharSet[])
{
	if(string==NULL || strCharSet==NULL)
		return _tcsstr(string,strCharSet);

	agtchar* string2=NULL;
	agtchar* strCharSet2=NULL;
	CAGmagicStrUtil::private_tcscat(string2,string,agtrue);
	CAGmagicStrUtil::private_tcscat(strCharSet2,strCharSet,agtrue);
	//_tcslwr_s(string,_tcslen(string)+1);
	_tcslwr(string);
	//_tcslwr_s(strCharSet,_tcslen(strCharSet)+1);
	_tcslwr(strCharSet);
	agtchar* idx=_tcsstr(string,strCharSet);

	_tcscpy(string,string2);
	_tcscpy(strCharSet,strCharSet2);
	if(string2)		free(string2);
	if(strCharSet2) free(strCharSet2);
	return idx;
}
/**********************CAGmagicIOUtil***************************************/
agbool privateBrowseFilesCompare(agtchar str[], agtchar pattern[], agtchar seps[], agbool bIsIn=agfalse)
{
	agbool		result=agfalse;
	aguint8		cmpkind;//0: AND, 1:OR
	if(_tcscmp(seps,AGMAGIC_AND_SEPS)==0)
	{
		cmpkind=0;
		result=agtrue;
	}
	if(_tcscmp(seps,AGMAGIC_OR_SEPS)==0)
	{
		cmpkind=1;
		result=agfalse;
	}

	agint32		patternstr_len=_tcslen(pattern);
	agtchar*	patternstr=(agtchar*)malloc( (patternstr_len+1)*sizeof(agtchar) );
	//_tcscpy_s(patternstr, patternstr_len+1, pattern);
	_tcscpy(patternstr, pattern);

	agtchar*	nexttoken = NULL;
	//agtchar*	token=_tcstok_s(patternstr,seps,&nexttoken);
	agtchar*	token=_tcstok(patternstr,seps);
	if(token==NULL)
	{
		if(str==NULL)	result=agtrue;
		else			result=agfalse;
	}
	else
	{
		while(token != NULL)
		{
			agbool	cmp;
			if(!bIsIn)	cmp=(_tcsicmp(str,token)==0);
			else		cmp=(_tcsstr(str,token)!=NULL);
			if(cmpkind==0)
			{
				result=result && cmp;//AND
				if(!result)	break;
			}
			if(cmpkind==1)
			{
				result =result || cmp;//OR
				if(result)	break;
			}
			//token = _tcstok_s(NULL,seps,&nexttoken);
			token = _tcstok(NULL,seps);
		}
	}
	free(patternstr);
	return result;
}

void CAGmagicIOUtil::Browse(
				  void (*dirFrontFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
				  void (*dirBackFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
				  void (*fileFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),

				  agtchar szDstOrgDir[],
				  agtchar szOrgDir[],			agtchar szBaseFilter[],

				  agtchar szDirInclude[],		agtchar szDirExclude[],
				  agtchar szFileExtInclude[],	agtchar szFileExtExclude[],

				  agbool  isAlwaysDoDirFunction, 
				  agtchar seps[],
				  void* pReserved
				 )
{
	if(dirFrontFunction)
	{
		if(isAlwaysDoDirFunction)
			dirFrontFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
		else if(
				((szDirInclude!=NULL)?privateBrowseFilesCompare(szOrgDir,szDirInclude,seps,agtrue) :TRUE) && 
				((szDirExclude!=NULL)?(!privateBrowseFilesCompare(szOrgDir,szDirExclude,seps,agtrue)):TRUE)
				)
			dirFrontFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
	}

	agtchar* szFindPath=NULL;
	CAGmagicStrUtil::private_tcscat(szFindPath,szOrgDir,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,szBaseFilter,agtrue);
 
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

	WIN32_FIND_DATA FileData; 
	HANDLE			hSearch=NULL; 

	hSearch = FindFirstFile(szFindPath, &FileData); 
	if(hSearch==INVALID_HANDLE_VALUE)	return;

	while (TRUE) 
	{
		agtchar* szFileFullPath=NULL;
		agtchar* szDstFileFullPath=NULL;

		BOOL bIsDots=FALSE;
		if(_tcsicmp(FileData.cFileName,_T("."))==0 || 
		   _tcsicmp(FileData.cFileName,_T(".."))==0 )
		   bIsDots=TRUE;
		
		if(!bIsDots)
		{
			if(szOrgDir)
			{
				CAGmagicStrUtil::private_tcscat(szFileFullPath,szOrgDir,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,AGMAGIC_DIR_SPLASH,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,FileData.cFileName,agtrue);
			}
			if(szDstOrgDir)
			{
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,szDstOrgDir,agtrue);
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,AGMAGIC_DIR_SPLASH,agtrue);
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,FileData.cFileName,agtrue);
			}

			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				Browse(dirFrontFunction,dirBackFunction,fileFunction,szDstFileFullPath,szFileFullPath,szBaseFilter,szDirInclude,szDirExclude,szFileExtInclude,szFileExtExclude,isAlwaysDoDirFunction, seps, pReserved);
			}
			else
			{
				if(	((szDirInclude!=NULL)?privateBrowseFilesCompare(szOrgDir,szDirInclude,seps,agtrue) :TRUE) && 
					((szDirExclude!=NULL)?(!privateBrowseFilesCompare(szOrgDir,szDirExclude,seps,agtrue)):TRUE)
				  )
				{
					agtchar* pdest=_tcsrchr(FileData.cFileName,_T('.'));
					agint    len = (pdest!=NULL)?_tcslen(pdest):0;
					if(len > 1)
					{
						pdest++;

						if( ((szFileExtInclude!=NULL)?privateBrowseFilesCompare(pdest,szFileExtInclude,seps)   :TRUE) && 
							((szFileExtExclude!=NULL)?(!privateBrowseFilesCompare(pdest,szFileExtExclude,seps)):TRUE)
							)
						{
							if(fileFunction) fileFunction(&FileData,szDstFileFullPath,szFileFullPath, pReserved);
						}
					}
					else
					{
						if( ((szFileExtInclude!=NULL)?privateBrowseFilesCompare(_T("blank"),szFileExtInclude,seps)   :TRUE) && 
							((szFileExtExclude!=NULL)?(!privateBrowseFilesCompare(_T("blank"),szFileExtExclude,seps)):TRUE)
						  )
						{
							if(fileFunction) fileFunction(&FileData,szDstFileFullPath,szFileFullPath, pReserved);
						}
					}
				}
			}
		}
		if(szFileFullPath)		free(szFileFullPath);
		if(szDstFileFullPath)	free(szDstFileFullPath);
		if (!FindNextFile(hSearch, &FileData))	break;

	}
	FindClose(hSearch);
#else
	throw _T("Implement not yet");
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	
	if(dirBackFunction)
	{
		if(isAlwaysDoDirFunction)
			dirBackFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
		else if(
				((szDirInclude!=NULL)?privateBrowseFilesCompare(szOrgDir,szDirInclude,seps,agtrue) :TRUE) && 
				((szDirExclude!=NULL)?(!privateBrowseFilesCompare(szOrgDir,szDirExclude,seps,agtrue)):TRUE)
				)
			dirBackFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
	}
	if(szFindPath) free(szFindPath);
} 
void CAGmagicIOUtil::Browse2(
				void (*dirFrontFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
				void (*dirBackFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
				void (*fileFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),

				agtchar szDstOrgDir[],
				agtchar szOrgDir[],		agtchar szBaseFilter[],

				agbool (*dirIncludeFunction)(void* pAtt, agtchar* pReservedPath),
				agbool (*dirExcludeFunction)(void* pAtt, agtchar* pReservedPath),

				agbool (*fileIncludeFunction)(void* pAtt, agtchar* pReservedPath),
				agbool (*fileExcludeFunction)(void* pAtt, agtchar* pReservedPath),

				agbool	isAlwaysDoDirFunction,
				void* pReserved
			)
{
	if(dirFrontFunction)
	{
		if(isAlwaysDoDirFunction)
			dirFrontFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
		else if(
				((dirIncludeFunction!=NULL)?dirIncludeFunction(NULL,szOrgDir) :TRUE) && 
				((dirExcludeFunction!=NULL)?(!dirExcludeFunction(NULL,szOrgDir)):TRUE)
				)
			dirFrontFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
	}

	agtchar* szFindPath=NULL;
	CAGmagicStrUtil::private_tcscat(szFindPath,szOrgDir,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,szBaseFilter,agtrue);
 
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

	WIN32_FIND_DATA FileData; 
	HANDLE			hSearch=NULL; 

	hSearch = FindFirstFile(szFindPath, &FileData); 
	if(hSearch==INVALID_HANDLE_VALUE)	return;

	while (TRUE) 
	{
		agtchar* szFileFullPath=NULL;
		agtchar* szDstFileFullPath=NULL;

		BOOL bIsDots=FALSE;
		if(_tcsicmp(FileData.cFileName,_T("."))==0 || 
		   _tcsicmp(FileData.cFileName,_T(".."))==0 )
		   bIsDots=TRUE;
		
		if(!bIsDots)
		{
			if(szOrgDir)
			{
				CAGmagicStrUtil::private_tcscat(szFileFullPath,szOrgDir,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,AGMAGIC_DIR_SPLASH,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,FileData.cFileName,agtrue);
			}
			if(szDstOrgDir)
			{
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,szDstOrgDir,agtrue);
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,AGMAGIC_DIR_SPLASH,agtrue);
				CAGmagicStrUtil::private_tcscat(szDstFileFullPath,FileData.cFileName,agtrue);
			}

			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				Browse2(dirFrontFunction,dirBackFunction,fileFunction,szDstFileFullPath,szFileFullPath,szBaseFilter,dirIncludeFunction,dirExcludeFunction,fileIncludeFunction,fileExcludeFunction,isAlwaysDoDirFunction, pReserved);
			}
			else
			{
				if(	((dirIncludeFunction!=NULL)?dirIncludeFunction(NULL,szOrgDir) :TRUE) && 
					((dirExcludeFunction!=NULL)?(!dirExcludeFunction(NULL,szOrgDir)):TRUE)
				  )
				{

					if( ((fileIncludeFunction!=NULL)?fileIncludeFunction(&FileData,szFileFullPath)   :TRUE) && 
						((fileExcludeFunction!=NULL)?(!fileExcludeFunction(&FileData,szFileFullPath)):TRUE)
						)
					{
						if(fileFunction) fileFunction(&FileData,szDstFileFullPath,szFileFullPath, pReserved);
					}
				}
			}
		}
		if(szFileFullPath)		free(szFileFullPath);
		if(szDstFileFullPath)	free(szDstFileFullPath);
		if (!FindNextFile(hSearch, &FileData))	break;

	}
	FindClose(hSearch);
#else
	throw _T("Implement not yet");
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	
	if(dirBackFunction)
	{
		if(isAlwaysDoDirFunction)
			dirBackFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
		else if(
				((dirIncludeFunction!=NULL)?dirIncludeFunction(NULL,szOrgDir) :TRUE) && 
				((dirExcludeFunction!=NULL)?(!dirExcludeFunction(NULL,szOrgDir)):TRUE)
				)
			dirBackFunction(NULL,szDstOrgDir,szOrgDir,pReserved);
	}
	if(szFindPath) free(szFindPath);
}
void CAGmagicIOUtil::SimpleBrowseFiles(
						void (*fileFunction)(void* pAtt, void* szPath, void* pReserved),
						agtchar szOrgDir[],
						agtchar szFilter[],
						agtchar seps[],
						void* pReserved
					)
{
	agtchar* szFindPath=NULL;
	CAGmagicStrUtil::private_tcscat(szFindPath,szOrgDir,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szFindPath,_T("*"),agtrue);
 
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS

	WIN32_FIND_DATA FileData; 
	HANDLE			hSearch=NULL; 

	hSearch = FindFirstFile(szFindPath, &FileData); 
	if(hSearch==INVALID_HANDLE_VALUE)	return;

	while (TRUE) 
	{
		agtchar* szFileFullPath=NULL;

		BOOL bIsDots=FALSE;
		if(_tcsicmp(FileData.cFileName,_T("."))==0 || 
		   _tcsicmp(FileData.cFileName,_T(".."))==0 )
		   bIsDots=TRUE;
		
		if(!bIsDots)
		{
			if(szOrgDir)
			{
				CAGmagicStrUtil::private_tcscat(szFileFullPath,szOrgDir,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,AGMAGIC_DIR_SPLASH,agtrue);
				CAGmagicStrUtil::private_tcscat(szFileFullPath,FileData.cFileName,agtrue);
			}

			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				SimpleBrowseFiles(fileFunction,szFileFullPath,szFilter,seps, pReserved);
			}
			else
			{
				agtchar* pdest=_tcsrchr(FileData.cFileName,_T('.'));
				agint    len = (pdest!=NULL)?_tcslen(pdest):0;
				if(len > 1)
				{
					pdest++;

					if( ((szFilter!=NULL)?privateBrowseFilesCompare(pdest,szFilter,seps)   :TRUE)
						)
					{
						if(fileFunction) fileFunction(&FileData,szFileFullPath, pReserved);
					}
				}
				else
				{
					if( ((szFilter!=NULL)?privateBrowseFilesCompare(_T("blank"),szFilter,seps)   :TRUE)
					  )
					{
						if(fileFunction) fileFunction(&FileData,szFileFullPath, pReserved);
					}
				}
			}
		}
		if(szFileFullPath)		free(szFileFullPath);	szFileFullPath=NULL;
		if (!FindNextFile(hSearch, &FileData))	break;

	}
	FindClose(hSearch);
#else
	throw _T("Implement not yet");
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	if(szFindPath) free(szFindPath);	szFindPath=NULL;
}
agbool CAGmagicIOUtil::isFileHeader(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");

	agtchar* pdest=_tcsrchr(pReservedPath,_T('.'));
	agint    len = (pdest!=NULL)?_tcslen(pdest):0;
	if(len > 1)
	{
		pdest++;
		return privateBrowseFilesCompare(pdest,AGMAGIC_HEADER_FILEEXT,AGMAGIC_OR_SEPS);
	}
	return privateBrowseFilesCompare(_T("blank"),AGMAGIC_HEADER_FILEEXT,AGMAGIC_OR_SEPS);
}
agbool CAGmagicIOUtil::isFileBin(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");

	agtchar* pdest=_tcsrchr(pReservedPath,_T('.'));
	agint    len = (pdest!=NULL)?_tcslen(pdest):0;
	if(len > 1)
	{
		pdest++;
		return privateBrowseFilesCompare(pdest,AGMAGIC_BIN_FILEEXT,AGMAGIC_OR_SEPS);
	}
	return privateBrowseFilesCompare(_T("blank"),AGMAGIC_BIN_FILEEXT,AGMAGIC_OR_SEPS);
}
agbool CAGmagicIOUtil::isFileWaste(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");

	agtchar* pdest=_tcsrchr(pReservedPath,_T('.'));
	agint    len = (pdest!=NULL)?_tcslen(pdest):0;
	if(len > 1)
	{
		pdest++;
		return privateBrowseFilesCompare(pdest,AGMAGIC_WASTE_FILEEXT,AGMAGIC_OR_SEPS);
	}
	return privateBrowseFilesCompare(_T("blank"),AGMAGIC_WASTE_FILEEXT,AGMAGIC_OR_SEPS);
}
agbool CAGmagicIOUtil::isFileHeaderAndBin(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");

	agtchar* pdest=_tcsrchr(pReservedPath,_T('.'));
	agint    len = (pdest!=NULL)?_tcslen(pdest):0;
	agtchar  fileext[1024];
	if(len > 1)
	{
		pdest++;
		return privateBrowseFilesCompare(pdest,CAGmagicConfUtil::AGMAGIC_HEADER_AND_BIN_FILEEXT(fileext),AGMAGIC_OR_SEPS);
	}
	return privateBrowseFilesCompare(pdest,CAGmagicConfUtil::AGMAGIC_HEADER_AND_BIN_FILEEXT(fileext),AGMAGIC_OR_SEPS);
}
agbool CAGmagicIOUtil::isFileWasteAndBin(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");
	agtchar* pdest=_tcsrchr(pReservedPath,_T('.'));
	agint    len = (pdest!=NULL)?_tcslen(pdest):0;
	agtchar  fileext[1024];
	if(len > 1)
	{
		pdest++;
		return privateBrowseFilesCompare(pdest,CAGmagicConfUtil::AGMAGIC_WASTE_AND_BIN_FILEEXT(fileext),AGMAGIC_OR_SEPS);
	}
	return privateBrowseFilesCompare(pdest,CAGmagicConfUtil::AGMAGIC_WASTE_AND_BIN_FILEEXT(fileext),AGMAGIC_OR_SEPS);
}
agbool CAGmagicIOUtil::isDirCompile(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");
	return privateBrowseFilesCompare(pReservedPath,AGMAGIC_COMPILE_DIRNAME,AGMAGIC_OR_SEPS,agtrue);
}
agbool CAGmagicIOUtil::isDirBin(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");
	return privateBrowseFilesCompare(pReservedPath,AGMAGIC_BIN_DIRNAME,AGMAGIC_OR_SEPS,agtrue);
}
agbool CAGmagicIOUtil::isDirCompileAndBin(void* pAtt, agtchar* pReservedPath)
{
	if(pAtt) throw _T("Implement not yet");
	agtchar dirname[1024];
	return privateBrowseFilesCompare(pReservedPath,CAGmagicConfUtil::AGMAGIC_COMPILE_AND_BIN_DIRNAME(dirname),AGMAGIC_OR_SEPS,agtrue);
}

agtchar* CAGmagicIOUtil::ConvertAndAllocFullURL(agtchar brief_url[])
{
	if(brief_url==NULL)	return NULL;
	agtchar*			FullURL=NULL;
	agtchar*			str=_tcsstr(brief_url,_T("."));
	agint32				n=_tcslen(brief_url);
	if(str!=NULL && str==brief_url && (n>1?(brief_url[1]!=_T('.')&&brief_url[1]==AGMAGIC_DIR_SPLASH):agtrue) )//str la phan tu dau tien cua url
	{
		CAGmagicStrUtil::private_tcscat(FullURL,CAGmagicConfUtil::AGmagic_GlobalCurDir,agtrue);
		if(n>1)	CAGmagicStrUtil::private_tcscat(FullURL,brief_url+1,agtrue);
	}
	else
		CAGmagicStrUtil::private_tcscat(FullURL,brief_url,agtrue);
	return FullURL;
}
agtchar* CAGmagicIOUtil::ConvertAndAllocBriefURL(agtchar FullURL[])
{
	if(FullURL==NULL)	return NULL;
	agtchar*	brief_url=NULL;

	agtchar*	szSamplePath=CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute();
	agtchar*	idx=CAGmagicStrUtil::private_tcsstr(FullURL,szSamplePath);
	if(idx==NULL)
	{
		if(szSamplePath) free(szSamplePath);	szSamplePath=NULL;
		szSamplePath=CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute2();
		idx=_tcsstr(FullURL,szSamplePath);
	}

	if(idx==NULL)
		CAGmagicStrUtil::private_tcscat(brief_url,FullURL,agtrue);
	else
	{
		if(_tcschr(idx,AGMAGIC_DIR_SPLASH)==NULL)
			CAGmagicStrUtil::private_tcscat(brief_url,FullURL,agtrue);
		else
		{
			CAGmagicStrUtil::private_tcscat(brief_url,_T("."),agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,AGMAGIC_DIR_SPLASH,agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,_T(".."),agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,AGMAGIC_DIR_SPLASH,agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,_T("data"),agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,AGMAGIC_DIR_SPLASH,agtrue);
			CAGmagicStrUtil::private_tcscat(brief_url,_T("sample-images"),agtrue);

			agint32 len=_tcslen(szSamplePath);
			CAGmagicStrUtil::private_tcscat(brief_url,FullURL+len,agtrue);
		}
	}
	if(szSamplePath) free(szSamplePath);	szSamplePath=NULL;
	return brief_url;
}

/**********************CAGmagicDBOrg***************************************/

CAGmagicDBOrg::CAGmagicDBOrg()
{
	m_pDBCnnI=NULL;
}
CAGmagicDBOrg::~CAGmagicDBOrg()
{
	DBCnnDetach();
}
void* CAGmagicDBOrg::DBCnnAttach(void* pDBCnnI)//khong AddRef, tra ve Connection cu doi ADO
{
	void*	old=m_pDBCnnI;
	m_pDBCnnI=pDBCnnI;
	return old;
}
void* CAGmagicDBOrg::DBCnnDetach()//khong Release
{
	if(m_pDBCnnI==NULL)	return NULL;

	void*	old=m_pDBCnnI;
	m_pDBCnnI=NULL;
	return old;
}
agbool CAGmagicDBOrg::DBCnnIsValid()
{
	return (m_pDBCnnI!=NULL);
}
void* CAGmagicDBOrg::DBCnnGet()
{
	return m_pDBCnnI;
}


/**********************CAGmagicDBUtil***************************************/

//pDBCnnI la _Connection* doi voi ADO
agbool CAGmagicDBUtil::CnnCreate(void*& pDBCnnI, agtchar* szDBCnn, DBCONNECTION_CONFIG* pDBCnnConfig, agbool bIsCallCoInitializeForInitADO)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsCallCoInitializeForInitADO)	::CoInitialize(NULL);

		_ConnectionPtr	pADODBCnn;
		pADODBCnn.CreateInstance(_T("ADODB.Connection"));
		pADODBCnn->Open((LPCTSTR)szDBCnn,_T(""),_T(""),adConnectUnspecified);
		
		pDBCnnI=pADODBCnn.Detach();
		if(pDBCnnI==NULL)	return agfalse;
		CnnSetConfig(pDBCnnI,pDBCnnConfig);
		return agtrue;
	}
	catch(_com_error &e)
	{
		if(pDBCnnI!=NULL) DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}
//pDBCnnI la _Connection* doi voi ADO
agbool CAGmagicDBUtil::CnnDestroy(void*& pDBCnnI, agbool bIsCallCoUninitialize)
{
	if(pDBCnnI==NULL)	return agtrue;
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_Connection*	pADODBCnnI=(_Connection*)pDBCnnI;
		pADODBCnnI->Close();
		pADODBCnnI->Release();
		pDBCnnI=NULL;

		if(bIsCallCoUninitialize)	::CoUninitialize();
		return agtrue;
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}

//pDBCnnI la _Connection* doi voi ADO
void CAGmagicDBUtil::CnnSetConfig(void* pDBCnnI, DBCONNECTION_CONFIG* pDBCnnConfig)
{
	DBCONNECTION_CONFIG TempDBCnnConfig;
	if(pDBCnnConfig==NULL)
	{
		INIT_DBCONNECTION_CONFIG_PTR(&TempDBCnnConfig)
		pDBCnnConfig=&TempDBCnnConfig;
	}
	//throw _T("Implement not yet");
}

//pDBCnnI la _Connection* doi voi ADO
void CAGmagicDBUtil::CnnGetConfig(void* pDBCnnI, DBCONNECTION_CONFIG* pDBCnnConfig)
{
	//throw _T("Implement not yet");
}
//pDBCnnI la _Connection* doi voi ADO
void CAGmagicDBUtil::BeginTrans(void* pDBCnnI)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		((_Connection*)pDBCnnI)->BeginTrans();
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}
//pDBCnnI la _Connection* doi voi ADO
void CAGmagicDBUtil::CommitTrans(void* pDBCnnI)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		((_Connection*)pDBCnnI)->CommitTrans();
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}
//pDBCnnI la _Connection* doi voi ADO
void CAGmagicDBUtil::RollbackTrans(void* pDBCnnI)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		((_Connection*)pDBCnnI)->RollbackTrans();
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}

#if AGMAGIC_SUPPORT_MFC
//pDBCnnI la _Connection* doi voi ADO
agbool CAGmagicDBUtil::ExcuteSQL(void* pDBCnnI, CStringArray& aSQL, agbool bIsTrans)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();

		_CommandPtr	pCmd(_T("ADODB.Command"));
		pCmd->PutRefActiveConnection((_Connection*)pDBCnnI);
		for(agint32 i=0; i<aSQL.GetSize(); i++)
		{
			_bstr_t bsSQL(aSQL.GetAt(i));
			if(bsSQL.length()==0)	throw _T("serious error");
			pCmd->PutCommandText(bsSQL);
			pCmd->Execute(NULL,NULL,adCmdText);
		}
		
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return agtrue;
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
}
#endif	//#if AGMAGIC_SUPPORT_MFC

//pDBCnnI la _Connection* voi ADO
agbool CAGmagicDBUtil::ExcuteSQL(void* pDBCnnI, agtchar SQL[], agbool bIsTrans)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		_bstr_t bsSQL(SQL);
		if(bsSQL.length()==0)	return agfalse;
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();

		_CommandPtr	pCmd(_T("ADODB.Command"));
		pCmd->PutRefActiveConnection((_Connection*)pDBCnnI);
		pCmd->PutCommandText(bsSQL);
		pCmd->Execute(NULL,NULL,adCmdText);
		
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return agtrue;
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
}

//pDBCnnI la _Connection* voi ADO
agbool CAGmagicDBUtil::ExcuteSQL(void* pDBCnnI, agtchar* aSQL[], aguint32 nSQL, agbool bIsTrans)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();

		_CommandPtr	pCmd(_T("ADODB.Command"));
		pCmd->PutRefActiveConnection((_Connection*)pDBCnnI);
		for(aguint32 i=0; i<nSQL; i++)
		{
			_bstr_t bsSQL(aSQL[i]);
			if(bsSQL.length()==0)		throw _T("serious error");
			pCmd->PutCommandText(bsSQL);
			pCmd->Execute(NULL,NULL,adCmdText);
		}
		
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return agtrue;
	}
	catch(_com_error &e)
	{
		DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else	//#if	AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif
}
//pDBCnnI la _Connection* voi ADO
void CAGmagicDBUtil::DisplayErrors(void* pDBCnnI)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		ErrorsPtr errors=((_Connection*)pDBCnnI)->Errors;
		for(agint32 i=0; i<errors->Count; i++)
		{
			ErrorPtr error=errors->Item[i];
			::MessageBox(::GetDesktopWindow(),error->Description,_T("ADO Error"),MB_OK|MB_ICONSTOP);
		}
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


/******************************class CAGmagicConfigUtil*******************************************/
agbool		CAGmagicConfUtil::bIsInitAGmagicConf = agfalse;
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS || AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
agbool		CAGmagicConfUtil::AGmagicUtil_bIsShowCopyright = agfalse;
#endif //AGMAGIC_OS_TYPE
HANDLE		CAGmagicConfUtil::AGmagicUtil_hModule = NULL;
agtchar		CAGmagicConfUtil::AGmagic_GlobalCurDir[AGMAGIC_MAX_PATH_LENGTH];

#if AGMAGIC_SUPPORT_ADO
agint32									CAGmagicConfUtil::AGmagic_GlobalADOProvider=AGMAGIC_DEFAULT_ADO_PROVIDER;
#endif
agtchar									CAGmagicConfUtil::AGmagic_GlobalDBCnnStr[1024];
CAGmagicDBUtil::DBCONNECTION_CONFIG		CAGmagicConfUtil::AGmagic_GlobalDBCnnConfig;

agtchar*	CAGmagicConfUtil::AGmagic_GlobalSampleImagesDirNames[]= 
	{
		_T("animal"),	_T("animal_alphas"),	_T("cloud"),	_T("flag"), 
		_T("flower-spec"),_T("moto"),			_T("papers"),	_T("people"), 
		_T("plant"),	_T("rock"),				_T("rock2"),	_T("rodeo"), 
		_T("roof"),		_T("rug"),				_T("sign"),		_T("sunset"), 
		_T("vegetable"),_T("wall"),				_T("waterfall"),_T("wood"), 
		_T("label"),	_T("mic"),				_T("leaf"),		_T("money")
	};
agint32		CAGmagicConfUtil::nAGmagic_GlobalSampleImagesDirNames=22;
agbool		CAGmagicConfUtil::bAGmagic_GlobalSampleImagesDirNames[]=
	{
		agtrue,	  agtrue,    agtrue,    agtrue,
		agtrue,   agtrue,    agtrue,    agtrue,
		agtrue,   agtrue,    agtrue,    agtrue,
		agtrue,   agtrue,    agtrue,    agtrue,
		agtrue,   agtrue,    agtrue,    agtrue,
		agtrue,   agtrue,    agtrue,    agtrue
	};
aguint_id	CAGmagicConfUtil::idAGmagic_GlobalSampleImagesDirNames[]=
	{
		1,    2,    3,   4,
		5,    6,    7,   8,
		9,    10,   11,  12,
		13,   14,   15,  16,
		17,   18,   19,  20,
		21,   22,	23,	 24
	};

#include <direct.h>
void CAGmagicConfUtil::Init()
{
	if(bIsInitAGmagicConf)	return;
	else					bIsInitAGmagicConf = agtrue;

	memset(AGmagic_GlobalCurDir,0,AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
	//_tgetcwd(AGmagic_GlobalCurDir,AGMAGIC_MAX_PATH_LENGTH);

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS || AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	GetModuleFileName((HMODULE)AGmagicUtil_hModule,AGmagic_GlobalCurDir,AGMAGIC_MAX_PATH_LENGTH);
	agtchar* splash=_tcsrchr(AGmagic_GlobalCurDir,AGMAGIC_DIR_SPLASH);
	if(splash) *splash=0;
#else
	#error _T("Implement not yet")
#endif

#if AGMAGIC_SUPPORT_ADO
	if(AGmagic_GlobalADOProvider==AGMAGIC_SQLSERVER_ADO_PROVIDER)
	{
		//_tcscpy_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("Provider=SQLOLEDB;Persist Security Info=False;User ID=sa;Password=;Initial Catalog=AGmagic;Data Source=(local)"));
		_tcscpy(AGmagic_GlobalDBCnnStr,_T("Provider=SQLOLEDB;Persist Security Info=False;User ID=sa;Password=;Initial Catalog=AGmagic;Data Source=(local)"));
	}
	else if(AGmagic_GlobalADOProvider==AGMAGIC_ACCESS_ADO_PROVIDER)
	{
		//_tcscpy_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("Provider=Microsoft.Jet.OLEDB.4.0; Persist Security Info=False; Data Source="));
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),AGmagicBaseDirAbsoluteFromBin());
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),AGMAGIC_DIR_SPLASH_STR);
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("data"));
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),AGMAGIC_DIR_SPLASH_STR);
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("db"));
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),AGMAGIC_DIR_SPLASH_STR);
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("access-2000"));
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),AGMAGIC_DIR_SPLASH_STR);
		//_tcscat_s(AGmagic_GlobalDBCnnStr,sizeof(AGmagic_GlobalDBCnnStr),_T("AGmagic.mdb"));

		_tcscpy(AGmagic_GlobalDBCnnStr,_T("Provider=Microsoft.Jet.OLEDB.4.0; Persist Security Info=False; Data Source="));
		_tcscat(AGmagic_GlobalDBCnnStr,AGmagicBaseDirAbsoluteFromBin());
		_tcscat(AGmagic_GlobalDBCnnStr,AGMAGIC_DIR_SPLASH_STR);
		_tcscat(AGmagic_GlobalDBCnnStr,_T("data"));
		_tcscat(AGmagic_GlobalDBCnnStr,AGMAGIC_DIR_SPLASH_STR);
		_tcscat(AGmagic_GlobalDBCnnStr,_T("db"));
		_tcscat(AGmagic_GlobalDBCnnStr,AGMAGIC_DIR_SPLASH_STR);
		_tcscat(AGmagic_GlobalDBCnnStr,_T("access-2000"));
		_tcscat(AGmagic_GlobalDBCnnStr,AGMAGIC_DIR_SPLASH_STR);
		_tcscat(AGmagic_GlobalDBCnnStr,_T("AGmagic.mdb"));
	}
	else
		throw _T("Not support");
#else	//#if AGMAGIC_SUPPORT_ADO
	throw _T("Implement not yet");
#endif	//#if AGMAGIC_SUPPORT_ADO
}
agbool CAGmagicConfUtil::IsNegativeImageWhenSegment(aguint_id ImageType)
{
	if(ImageType==idAGmagic_GlobalSampleImagesDirNames[4]  || 
	   ImageType==idAGmagic_GlobalSampleImagesDirNames[15] ||
	   ImageType==idAGmagic_GlobalSampleImagesDirNames[18] )
	   return agtrue;
	return agfalse;
}
aguint_id CAGmagicConfUtil::GetTypeOfSampleImagesDirNames(agtchar szDirName[])
{
	if(szDirName==NULL || _tcslen(szDirName)==0)	return 0;
	agint32 i=0;
	for(i=0; i<nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		if(_tcsicmp(szDirName,AGmagic_GlobalSampleImagesDirNames[i])==0)
			break;
	}
	if(i==nAGmagic_GlobalSampleImagesDirNames)	return 0;
	return idAGmagic_GlobalSampleImagesDirNames[i];
}
void AGMAGIC_COPY_OS_PATH_PREFIX(agtchar szPath[], aguint32 nChar)
{
	memset(szPath,0,nChar*sizeof(agtchar));
	#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
		_tcscpy(szPath,_T("windows\\"));
	#elif AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
		_tcscpy(szPath,_T("wince\\"));
	#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS
		_tcscpy(szPath,_T("linux/"));
	#elif AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
		_tcscpy(szPath,_T("unix/"));
	#else
		#error _T("Implement not yet")
	#endif
}
void AGMAGIC_PREFIX_OF_BASE_FROM_BIN(agtchar szPath[], aguint32 nChar)
{
	memset(szPath,0,nChar*sizeof(agtchar));
	//_tcscat_s(szPath,nChar,_T(".."));
	_tcscat(szPath,_T(".."));
	//_tcscat_s(szPath,nChar,AGMAGIC_DIR_SPLASH_STR);
	_tcscat(szPath,AGMAGIC_DIR_SPLASH_STR);
}

agtchar* CAGmagicConfUtil::AGMAGIC_BIN_RELATED_BIN_PATH()
{
	return _T(".");
}
agtchar* CAGmagicConfUtil::AGMAGIC_BIN_RELATED_PROUIS_BIN_PATH()
{
	agtchar* path=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
	AGMAGIC_PREFIX_OF_BASE_FROM_BIN(path,AGMAGIC_MAX_PATH_LENGTH);
	//_tcscat_s(path,AGMAGIC_MAX_PATH_LENGTH,AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH);
	_tcscat(path,AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH);
	return path;
}
agtchar* CAGmagicConfUtil::AGMAGIC_BIN_RELATED_CXIMAGE_BIN_PATH()
{
	agtchar* path=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
	AGMAGIC_PREFIX_OF_BASE_FROM_BIN(path,AGMAGIC_MAX_PATH_LENGTH);
	//_tcscat_s(path,AGMAGIC_MAX_PATH_LENGTH,AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH);
	_tcscat(path,AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH);
	return path;
}

agtchar* CAGmagicConfUtil::AGMAGIC_HEADER_AND_BIN_FILEEXT(agtchar fileext[])
{
	_tcscpy(fileext,AGMAGIC_HEADER_FILEEXT);
	_tcscat(fileext,_T("||"));
	_tcscat(fileext,AGMAGIC_BIN_FILEEXT);
	return fileext;
}
agtchar* CAGmagicConfUtil::AGMAGIC_WASTE_AND_BIN_FILEEXT(agtchar fileext[])
{
	_tcscpy(fileext,AGMAGIC_WASTE_FILEEXT);
	_tcscat(fileext,_T("||"));
	_tcscat(fileext,AGMAGIC_BIN_FILEEXT);
	return fileext;
}
agtchar* CAGmagicConfUtil::AGMAGIC_COMPILE_AND_BIN_DIRNAME(agtchar dirnames[])
{
	_tcscpy(dirnames,AGMAGIC_COMPILE_DIRNAME);
	_tcscat(dirnames,_T("||"));
	_tcscat(dirnames,AGMAGIC_BIN_DIRNAME);
	return dirnames;
}
//su khi goi ham nay ban phai chiu trach nhiem free
agtchar* CAGmagicConfUtil::AGmagicBaseDirAbsoluteFromBin()
{
	agtchar* szBaseDir=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
	memset(szBaseDir,0,AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
	//_tcscpy_s(szBaseDir,AGMAGIC_MAX_PATH_LENGTH,AGmagic_GlobalCurDir);
	_tcscpy(szBaseDir,AGmagic_GlobalCurDir);

	agtchar* bin=NULL;
	CAGmagicStrUtil::private_tcscat(bin,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(bin,AGMAGIC_BASE_RELATED_BIN_PATH,agtrue);
	agtchar* idx=_tcsstr(szBaseDir,bin);
	if(idx!=NULL)	*idx=0;
	return szBaseDir;
}

agtchar* CAGmagicConfUtil::AGmagicBinPathAbsolute()
{
	agtchar* szBinPath=AGmagicBaseDirAbsoluteFromBin();
	CAGmagicStrUtil::private_tcscat(szBinPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szBinPath,AGMAGIC_BASE_RELATED_BIN_PATH,agtrue);
	return szBinPath;
}
agtchar* CAGmagicConfUtil::AGmagicProUISBinPathAbsolute()
{
	agtchar* szProUISBinPath=AGmagicBaseDirAbsoluteFromBin();
	CAGmagicStrUtil::private_tcscat(szProUISBinPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szProUISBinPath,AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH,agtrue);
	return szProUISBinPath;
}
agtchar* CAGmagicConfUtil::AGmagicCxImageBinPathAbsolute()
{
	agtchar* szCxImageBinPath=AGmagicBaseDirAbsoluteFromBin();
	CAGmagicStrUtil::private_tcscat(szCxImageBinPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szCxImageBinPath,AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH,agtrue);
	return szCxImageBinPath;
}
agtchar* CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute()
{
	agtchar* szSampleImagesPath=AGmagicBaseDirAbsoluteFromBin();
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,_T("data"),agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,_T("sample-images"),agtrue);
	return szSampleImagesPath;
}
agtchar* CAGmagicConfUtil::AGmagicSampleImagesPathAbsolute2()
{
	agtchar* szSampleImagesPath=NULL;
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGmagic_GlobalCurDir,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,_T(".."),agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,_T("data"),agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,AGMAGIC_DIR_SPLASH,agtrue);
	CAGmagicStrUtil::private_tcscat(szSampleImagesPath,_T("sample-images"),agtrue);
	return szSampleImagesPath;
}
agtchar* CAGmagicConfUtil::AGmagic_GlobalSampleImagesExcludeDir()
{
	agtchar* szSampleImagesExcludeDir=NULL;
	for(agint32 i=0; i<nAGmagic_GlobalSampleImagesDirNames; i++)
	{
		if(bAGmagic_GlobalSampleImagesDirNames[i])
			continue;
		CAGmagicStrUtil::private_tcscat(szSampleImagesExcludeDir,AGmagic_GlobalSampleImagesDirNames[i],agtrue);
		if(i<nAGmagic_GlobalSampleImagesDirNames-1)
			CAGmagicStrUtil::private_tcscat(szSampleImagesExcludeDir,AGMAGIC_OR_SEPS,agtrue);
	}
	return szSampleImagesExcludeDir;
}
agbool CAGmagicConfUtil::AGmagicGetEnvPathVar(agtchar*& szEnvPathVar, aguint32* reserved)
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	if(szEnvPathVar)	free(szEnvPathVar);	szEnvPathVar=NULL;

	HKEY		hKey=NULL;
    DWORD		PathLength;
	::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Environment"), 0, KEY_READ, &hKey );
	if(hKey==NULL)		return agfalse;
	DWORD	dwType;
    if(::RegQueryValueEx(hKey, _T("path"), NULL, &dwType, NULL, &PathLength)!=ERROR_SUCCESS)
		return agfalse;
	if(PathLength==0)	return agtrue;

	szEnvPathVar=(TCHAR*)malloc(PathLength*sizeof(TCHAR));
	memset(szEnvPathVar,0,PathLength*sizeof(TCHAR));
	::RegQueryValueEx(hKey, _T("path"), NULL, &dwType, (LPBYTE)szEnvPathVar, &PathLength);
	::RegCloseKey(hKey);
	
	if(_tcslen(szEnvPathVar)==0)	{free(szEnvPathVar);szEnvPathVar=NULL;}
	*reserved=(aguint32)dwType;
	return agtrue;
#else
	throw _T("Implement not yet");
#endif
}
agbool CAGmagicConfUtil::AGmagicSetEnvPathVar(agtchar szEnvPathVar[], aguint32* reserved)
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	if(szEnvPathVar==NULL)	throw _T("Fatal error. Environment Variable must not empty");

	HKEY		hKey=NULL;
	::RegOpenKeyEx(HKEY_CURRENT_USER,_T("Environment"),0, KEY_WRITE, &hKey );
	if(hKey==NULL)		return agfalse;

	DWORD dwType=(DWORD)(*reserved);
	if(::RegSetValueEx(hKey, _T("path"), NULL, dwType,
		               (LPBYTE)szEnvPathVar,(_tcslen(szEnvPathVar)+1)*sizeof(agtchar)
					   )!=ERROR_SUCCESS
	  )
		return agfalse;
	return agtrue;
#else
	throw _T("Implement not yet");
#endif
}

/****************************class CAGmagicSysUtil***********************************/

agbool CAGmagicSysUtil::ExitOS(aguint32 flag)
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	 
	// Get a token for this process.
	if (!::OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		{_putts(_T("OpenProcessToken"));return agfalse;}
	 
	// Get the LUID for the shutdown privilege. 
	::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
			&tkp.Privileges[0].Luid); 
	 
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	 
	// Get the shutdown privilege for this process. 
	::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
			(PTOKEN_PRIVILEGES)NULL, 0); 
	 
	// Cannot test the return value of AdjustTokenPrivileges. 
	if (::GetLastError() != ERROR_SUCCESS) 
		{_putts(_T("AdjustTokenPrivileges"));return agfalse;}
	 
	// Shut down the system and force all applications to close.
	UINT uFlags=0;
	switch(flag)
	{
		case AGMAGIC_OS_LOGOFF:
			uFlags |= EWX_LOGOFF;
			break;
		case AGMAGIC_OS_POWEROFF:
			uFlags |= EWX_POWEROFF;
			break;
		case AGMAGIC_OS_REBOOT:
			uFlags |= EWX_REBOOT;
			break;
		case AGMAGIC_OS_SHUTDOWN:
			uFlags |= EWX_SHUTDOWN;
			break;
		case AGMAGIC_OS_LOCK:
			throw _T("Implement not yets");
			break;
	}
	if (!::ExitWindowsEx(uFlags/*|EWX_FORCE*/, 0)) 
		{_putts("ExitWindowsEx error");return agfalse;}
#else
	throw _T("Implement not yet");
#endif
	return agtrue;
}
void CAGmagicSysUtil::ExitOSShowOption(aguint32 timeout_sec, agbool bIsRebootAfterShutdown)
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
		
	BOOL fResult;               // system shutdown flag 
		
	// Get the current process token handle so we can get shutdown 
	// privilege. 
	if (!OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		{_putts(_T("OpenProcessToken failed."));return;}
		
	// Get the LUID for shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
			&tkp.Privileges[0].Luid); 
		
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
		
	// Get shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES) NULL, 0); 
		
	// Cannot test the return value of AdjustTokenPrivileges. 
	if (GetLastError() != ERROR_SUCCESS) 
		{_putts(_T("AdjustTokenPrivileges enable failed."));return;}
	
	// Display the shutdown dialog box and start the time-out countdown. 
	fResult = InitiateSystemShutdown( 
		NULL,                                  // shut down local computer 
		"Click on the main window and press \
		the Escape key to cancel shutdown.",   // message to user 
		timeout_sec,                           // time-out period 
		FALSE,                                 // ask user to close apps 
		(bIsRebootAfterShutdown)? TRUE:FALSE  // reboot after shutdown 
	   );
	if (!fResult) 
	{ 
		{_putts(_T("InitiateSystemShutdown failed."));return;}
	} 
		
	// Disable shutdown privilege. 
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
			(PTOKEN_PRIVILEGES) NULL, 0); 
		
	if (GetLastError() != ERROR_SUCCESS) 
	{
		{_putts(_T("AdjustTokenPrivileges disable failed."));return;}
	} 
#else
	throw _T("Implement not yet");
#endif
}
void CAGmagicSysUtil::ExitOSShowOptionAbort()
{
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	 
	BOOL fResult;               // system shutdown flag 

	// Get the current process token handle  so we can get shutdown 
	// privilege. 
	if (!OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		{_putts(_T("OpenProcessToken failed."));return;}
	}

	// Get the LUID for shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
			&tkp.Privileges[0].Luid); 

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	// Get shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES)NULL, 0); 

	// Cannot test the return value of AdjustTokenPrivileges. 
	if (GetLastError() != ERROR_SUCCESS) 
	{
		{_putts(_T("AdjustTokenPrivileges enable failed."));return;}
	}

	// Prevent the system from shutting down. 
	fResult = AbortSystemShutdown(NULL); 

	if (!fResult) 
	{ 
		{_putts(_T("AbortSystemShutdown failed."));return;}
	} 

	// Disable shutdown privilege. 
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES) NULL, 0); 

	if (GetLastError() != ERROR_SUCCESS) 
	{
		{_putts(_T("AdjustTokenPrivileges disable failed."));return;}
	}
#else
	throw _T("Implement not yet");
#endif
}
void CAGmagicSysUtil::ExecProgram(agtchar szProgramPath[])
{
	if(szProgramPath==NULL)	throw _T("Invalid paramter");

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset(&si,0,sizeof(si) );
	si.cb = sizeof(si);
	memset(&pi,0,sizeof(pi) );

	// Start the child process. 
	if( !CreateProcess( NULL,	// No module name (use command line). 
		szProgramPath,			// Command line. 
		NULL,					// Process handle not inheritable. 
		NULL,					// Thread handle not inheritable. 
		FALSE,					// Set handle inheritance to FALSE. 
		0,						// No creation flags. 
		NULL,					// Use parent's environment block. 
		NULL,					// Use parent's starting directory. 
		&si,					// Pointer to STARTUPINFO structure.
		&pi )					// Pointer to PROCESS_INFORMATION structure.
	  ) 
	{
		//ErrorExit( "CreateProcess failed." );
	}

	// Wait until child process exits.
	if(pi.hProcess) WaitForSingleObject(pi.hProcess,INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
#else
	throw _T("Implement not yet");
#endif
}
agbool CAGmagicSysUtil::Invoke_FARPROC_LibFunc(agtchar szLibPath[], agtchar szFuncName[], agint32& vReturn)
{
	if(szLibPath==NULL  || szFuncName==NULL)	throw _T("Invalid paramter");

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	vReturn=-1;

	agbool		bRunTimeLinkSuccess=agfalse;
	HINSTANCE	hLib = ::LoadLibrary(szLibPath);
	if (hLib!=NULL)//Neu load libary thanh cong
	{
		// Find the entry point.
		FARPROC	lpDllEntryPoint = ::GetProcAddress(hLib, szFuncName);
		if(lpDllEntryPoint != NULL)
		{
			bRunTimeLinkSuccess=agtrue;
			vReturn=(lpDllEntryPoint)();
			if(vReturn!=0)
			{
				agtchar szText[256];
				//_stprintf_s(szText,256,_T("Call %s failed"), szFuncName);
				_stprintf(szText,_T("Call %s failed"), szFuncName);
				::MessageBox(NULL,szText,_T("Not success"),MB_OK|MB_ICONEXCLAMATION);
			}
		}
		else  ::MessageBox(NULL,_T("Call GetProcAddress failed "),_T("Not success"),MB_OK|MB_ICONEXCLAMATION);

		::FreeLibrary(hLib);
	}
	else ::MessageBox(NULL,_T("Call LoadLibrary failed "),_T("Not success"),MB_OK|MB_ICONEXCLAMATION);

	return bRunTimeLinkSuccess;
#else
	throw _T("Implement not yet");
#endif
}

agbool CAGmagicSysUtil::RegSvr(agtchar szSvrPath[])
{
	agint32 vReturn;
	if(!Invoke_FARPROC_LibFunc(szSvrPath,_T("DllRegisterServer"),vReturn))
		return agfalse;

	if(vReturn!=S_OK)	return agfalse;
	return agtrue;
}
agbool CAGmagicSysUtil::UnregSvr(agtchar szSvrPath[])
{
	agint32 vReturn;
	if(!Invoke_FARPROC_LibFunc(szSvrPath,_T("DllUnregisterServer"),vReturn))
		return agfalse;

	if(vReturn!=S_OK)	return agfalse;
	return agtrue;
}

/***********************class CAGoutputConsole****************************/

CAGoutputConsole::CAGoutputConsole()
{
	m_f=NULL;
}
CAGoutputConsole::~CAGoutputConsole()
{
	if(m_f) fclose(m_f);
}
FILE* CAGoutputConsole::Attach(FILE* f)
{
	FILE* fOld=m_f;
	m_f=f;
	return fOld;
}
FILE* CAGoutputConsole::Attach(agtchar szFilePath[])
{
	FILE* f=NULL;
	//_tfopen_s(&f,szFilePath,_T("w"));
	f=_tfopen(szFilePath,_T("w"));
	return Attach(f);
}

void CAGoutputConsole::Out(agtchar szMsg[])
{
	if(szMsg==NULL)	return;

	if(m_f)		_fputts(szMsg,m_f);
}

/****************************class CAGmagicEhancedUtil***********************************/

//Cac ham tien ich chuoi enhanced
#if (AGMAGIC_SUPPORT_MFC && AGMAGIC_SUPPORT_UTIL_ENHANCED)
int CAGmagicEhancedUtil::FindUInt(unsigned int x, CUIntArray& aUInt)
{
	for(int i=0;i<aUInt.GetSize();i++)
		if(x==aUInt[i])
			return i;
	return -1;
}
long CAGmagicEhancedUtil::FindString(CString& x, CStringArray& aS)
{
	for(long i=0; i<aS.GetSize();i++)
		if(aS.ElementAt(i).Find(x)!=-1)
			return i;
	return -1;
}
agbool CAGmagicEhancedUtil::FindUInt(unsigned int x, CArray<CUIntArray, CUIntArray&>& aUInt)
{
	for(int i=0;i<aUInt.GetSize();i++)
		for(int j=0;j<aUInt[i].GetSize();j++)
			if(aUInt[i].GetAt(j) == x)
				return agtrue;
	return agfalse;
}
agbool CAGmagicEhancedUtil::FindUInt(unsigned int x, CArray<CUIntArray, CUIntArray&>& aUInt,int& seg,int& off)
{
	for(int i=0;i<aUInt.GetSize();i++)
		for(int j=0;j<aUInt[i].GetSize();j++)
			if(aUInt[i].GetAt(j) == x)
			{
				seg = i ; off = j;
				return agtrue;
			}
	seg = off = -1;
	return agfalse;

}
agbool CAGmagicEhancedUtil::FindMapKey(CString& x, CMapStringToString& map, CString& rKey, CString& rValue)
{
	agbool		bFound=agfalse;
	POSITION	pos=map.GetStartPosition();

	while(pos!=NULL)
	{
		map.GetNextAssoc(pos,rKey,rValue);
		if(rKey.Compare(x)==0)
		{
			bFound=agtrue;
			break;
		}
	}
	return bFound;
}
agbool CAGmagicEhancedUtil::FindMapValue(CString& x, CMapStringToString& map, CString& rKey, CString& rValue)
{
	agbool		bFound=agfalse;
	POSITION	pos=map.GetStartPosition();
	while(pos!=NULL)
	{
		map.GetNextAssoc(pos,rKey,rValue);
		if(rValue.Compare(x)==0)
		{
			bFound=agtrue;
			break;
		}
	}
	return bFound;
}
CString CAGmagicEhancedUtil::MinMapKey(CMapStringToString& map)
{
	agbool		bFirst=agtrue;
	CString		min;
	POSITION	pos=map.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		map.GetNextAssoc(pos,rKey,rValue);
		if(bFirst)
		{
			min=rKey;
			bFirst=agfalse;
		}
		else
		{
			if(min.Compare(rKey)>0)
				min=rKey;
		}
	}
	return min;
}
CString CAGmagicEhancedUtil::MaxMapKey(CMapStringToString& map)
{
	agbool		bFirst=agtrue;
	CString		max;
	POSITION	pos=map.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		map.GetNextAssoc(pos,rKey,rValue);
		if(bFirst)
		{
			max=rKey;
			bFirst=agfalse;
		}
		else
		{
			if(max.Compare(rKey)<0)
				max=rKey;
		}
	}
	return max;
}


CString CAGmagicEhancedUtil::MinMapValue(CMapStringToString& map)
{
	agbool		bFirst=agtrue;
	CString		min;
	POSITION	pos=map.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		map.GetNextAssoc(pos,rKey,rValue);
		if(bFirst)
		{
			min=rValue;
			bFirst=agfalse;
		}
		else
		{
			if(min.Compare(rValue)>0)
				min=rValue;
		}
	}
	return min;
}
CString CAGmagicEhancedUtil::MaxMapValue(CMapStringToString& map)
{
	agbool		bFirst=agtrue;
	CString		max;
	POSITION	pos=map.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		map.GetNextAssoc(pos,rKey,rValue);
		if(bFirst)
		{
			max=rValue;
			bFirst=agfalse;
		}
		else
		{
			if(max.Compare(rValue)<0)
				max=rValue;
		}
	}
	return max;
}
void CAGmagicEhancedUtil::Alpha(CString szX,CString& szY)
{
	szY.Empty();
	for(int i=0;i<szX.GetLength();i++)
		//if(isalpha(szX[i]))		szY +=szX[i];
		if(szX[i]!=0 && szX[i]!=10 && szX[i]!=13 && szX[i]!=_T(' '))		szY +=szX[i];
}
void CAGmagicEhancedUtil::Alpha(CStringArray& aszS)
{
	int i=0;
	while(i<aszS.GetSize())
	{
		CString tempS;
		Alpha(aszS[i],tempS);
		if(tempS.IsEmpty())
			aszS.RemoveAt(i);
		else
		{
			aszS.SetAt(i,tempS);
			i++;
		}
	}

}
CString CAGmagicEhancedUtil::CharToString(TCHAR ch)
{
	CString szS=_T(" ");
	szS.SetAt(0,ch);
	return szS;
}

void CAGmagicEhancedUtil::SplitStringEx(CString szS,TCHAR ch, CStringArray& aszR)
{
	aszR.RemoveAll();
	szS.TrimLeft(ch);
	szS.TrimLeft();
	szS.TrimRight(ch);
	szS.TrimRight();
	while(!szS.IsEmpty())
	{
		int index = szS.Find(ch);
		if(index == -1)		
		{
			aszR.Add(szS);
			break;
		}
		CString tempS = szS.Left(index);
		tempS.TrimRight();
		if(!tempS.IsEmpty())
			aszR.Add(tempS);
		szS.TrimLeft((LPCTSTR)tempS);
		szS.TrimLeft(ch);
		szS.TrimLeft();
	}
}
void CAGmagicEhancedUtil::SplitStringEx(CString szS,LPCTSTR lpszS, CStringArray& aszR)
{
	aszR.RemoveAll();
	szS.TrimLeft(lpszS);
	szS.TrimLeft();
	szS.TrimRight(lpszS);
	szS.TrimRight();
	while(!szS.IsEmpty())
	{
		int index = szS.Find(lpszS);
		if(index == -1)		
		{
			aszR.Add(szS);
			break;
		}
		CString tempS = szS.Left(index);
		tempS.TrimRight();
		if(!tempS.IsEmpty())
			aszR.Add(tempS);
		szS.TrimLeft((LPCTSTR)tempS);
		szS.TrimLeft(lpszS);
		szS.TrimLeft();
	}
}

void CAGmagicEhancedUtil::StringArrayToString(CStringArray& aszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	if(aszX.GetSize()==0)	return;
	for(int i=0;i<aszX.GetSize()-1;i++)
	{
		szY += aszX[i];
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	szY +=aszX[i];

}
void CAGmagicEhancedUtil::StringArrayToString(CStringArray* aszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	if(aszX->GetSize()==0)	return;
	for(int i=0;i<aszX->GetSize()-1;i++)
	{
		szY += aszX->GetAt(i);
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	szY +=aszX->GetAt(i);

}
void CAGmagicEhancedUtil::RemoveStringFromStringArray(CString szS, CStringArray& aszS)
{
	long n=aszS.GetSize();
	for(long i=0; i<n; i++)
	{
		if(aszS.ElementAt(i).Compare(szS)==0)
		{
			aszS.RemoveAt(i);
			i--;
			n--;
			if(n==0)
				break;
		}
	}
}
void CAGmagicEhancedUtil::StringMapToKeyString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		szY +=rKey;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToKeyString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		szY +=rKey;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToValueString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach)//lay tat ca cac fia tri cua aszX vao szY
{
	szY.Empty();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		szY +=rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToValueString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		szY +=rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToKeyValueString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach)//lay tat ca cac khoa va tri cua aszX vao szY dang key1:value1,key2:value2,...
{
	szY.Empty();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		szY += (rKey+ _T(":")) + rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToKeyValueString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach)//lay tat ca cac khoa va tri cua aszX vao szY dang key1:value1,key2:value2,..
{
	szY.Empty();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		szY += (rKey+ _T(":")) + rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach)//lay tat ca cac fia tri cua aszX vao szY
{
	szY.Empty();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		szY +=rKey+_T(":");
		szY +=rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach)
{
	szY.Empty();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		szY +=rKey+_T(":");
		szY +=rValue;
		if(phancach==NULL)
			;
		else
			szY +=phancach;
	}
	if(phancach!=NULL)
		szY.TrimRight(phancach);
}
void CAGmagicEhancedUtil::StringMapToKeyUIntArray(CMapStringToString& mszX, CUIntArray& aUInt)//lay tat ca cac khoa cua aszX thanh mang so nguyen
{
	aUInt.RemoveAll();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		aUInt.Add(rKey[0]);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToKeyUIntArray(CMapStringToString* pmszX, CUIntArray& aUInt)
{
	aUInt.RemoveAll();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		aUInt.Add(rKey[0]);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToKeyStringArray(CMapStringToString& mszX, CStringArray& aszS)//lay tat ca cac khoa cua aszX thanh mang so nguyen
{
	aszS.RemoveAll();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		aszS.Add(rKey);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToKeyStringArray(CMapStringToString* pmszX, CStringArray& aszS)
{
	aszS.RemoveAll();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		aszS.Add(rKey);//lay ky tu dau tien;
	}
}
//
void CAGmagicEhancedUtil::StringMapToValueUIntArray(CMapStringToString& mszX, CUIntArray& aUInt)//lay tat ca cac khoa cua aszX thanh mang so nguyen
{
	aUInt.RemoveAll();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		aUInt.Add(rValue[0]);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToValueUIntArray(CMapStringToString* pmszX, CUIntArray& aUInt)
{
	aUInt.RemoveAll();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		aUInt.Add(rValue[0]);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToValueStringArray(CMapStringToString& mszX, CStringArray& aszS)//lay tat ca cac khoa cua aszX thanh mang so nguyen
{
	aszS.RemoveAll();
	POSITION	pos=mszX.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszX.GetNextAssoc(pos,rKey,rValue);
		aszS.Add(rValue);//lay ky tu dau tien;
	}
}
void CAGmagicEhancedUtil::StringMapToValueStringArray(CMapStringToString* pmszX, CStringArray& aszS)
{
	aszS.RemoveAll();
	POSITION	pos=pmszX->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszX->GetNextAssoc(pos,rKey,rValue);
		aszS.Add(rValue);//lay ky tu dau tien;
	}
}

void CAGmagicEhancedUtil::CopyStringMap(CMapStringToString& mszDst, CMapStringToString& mszSrc)
{
	mszDst.RemoveAll();

	POSITION	pos=mszSrc.GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		mszSrc.GetNextAssoc(pos,rKey,rValue);

		mszDst.SetAt(rKey,rValue);
	}
}
void CAGmagicEhancedUtil::CopyStringMap(CMapStringToString* pmszDst, CMapStringToString* pmszSrc)
{
	pmszDst->RemoveAll();

	POSITION	pos=pmszSrc->GetStartPosition();
	while(pos!=NULL)
	{
		CString rKey,rValue;
		pmszSrc->GetNextAssoc(pos,rKey,rValue);

		pmszDst->SetAt(rKey,rValue);
	}
}
void CAGmagicEhancedUtil::StringToStringMap(CString szX, CMapStringToString& mszY)
{
	CStringArray aszR;
	SplitStringEx(szX,_T(','),aszR);
	long n=aszR.GetSize();
	if(n==0) return ;

	mszY.RemoveAll();
	for(long i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitStringEx(aszR.ElementAt(i),_T(":"),aszRi);
		if(aszRi.GetSize()!=2)
			return ;
		mszY.SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}

}
void CAGmagicEhancedUtil::StringToStringMap(CString szX, CMapStringToString* pmszY)
{
	CStringArray aszR;
	SplitStringEx(szX,_T(','),aszR);
	long n=aszR.GetSize();
	if(n==0) return ;

	pmszY->RemoveAll();
	for(long i=0; i<n; i++)
	{
		CStringArray aszRi;
		SplitStringEx(aszR.ElementAt(i),_T(":"),aszRi);
		if(aszRi.GetSize()!=2)
			return ;
		pmszY->SetAt(aszRi.ElementAt(0),aszRi.ElementAt(1));
	}

}
CString CAGmagicEhancedUtil::Essence(CString szX)//Loai bo nhung phan tu trung nhau
{
	CString tempS;
	for(int i=0;i<szX.GetLength();i++)
		if(tempS.Find(szX[i])==-1)//Neu khong tim thay
			tempS +=szX[i];
	return tempS;

}
void CAGmagicEhancedUtil::Essence(CStringArray& aszX,CStringArray& aszY)//Loai bo nhung phan tu trung nhau
{
	int i,j;
	aszY.RemoveAll();
	for(i=0;i<aszX.GetSize();i++)
	{
		for(j=0;j<aszY.GetSize();j++)
			if(IsEqual(aszY[j],aszX[i]))
				break;
		if(j==aszY.GetSize())//Neu Khong tim thay
			aszY.Add(aszX[i]);
	}
}
void CAGmagicEhancedUtil::Essence(CUIntArray& aX,CUIntArray& aY)//loai bo nhung phan tu trung nhau
{
	aY.RemoveAll();
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)==-1)//Neu khong tim thay
			aY.Add(aX[i]);
}
CString CAGmagicEhancedUtil::Common(CString szX, CString szY)//Giao cua 2 tap hop
{
	CString tempS;
	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])!=-1)	tempS +=szX[i];
	tempS=Essence(tempS);
	return tempS;
}
CString CAGmagicEhancedUtil::Common(CStringArray& aszX)//Giao cua cac tap hop
{
	CString tempS=aszX[0];
	for(int i=1;i<aszX.GetSize();i++)
		tempS = Common(tempS,aszX[i]);

	return tempS;
}
CString CAGmagicEhancedUtil::Common(CStringArray& aszX, CStringArray& aszY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(Common(aszX),Common(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Common(CString szX, CStringArray& aszY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(szX,Common(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Common(CStringArray& aszX, CString szY)//Giao cua cac tap hop
{
	CString tempS;
	tempS = Common(Common(aszX),szY);
	return tempS;
}
void CAGmagicEhancedUtil::Common(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)!=-1)//Neu tim thay
			aTemp.Add(aX[i]);
	Essence(aTemp,aZ);
}
CString CAGmagicEhancedUtil::Union(CString szX, CString szY)//Hop cua 2 tap hop
{
	CString tempS;
	tempS = szX + szY;
	tempS = Essence(tempS);
	return tempS;
}
CString CAGmagicEhancedUtil::Union(CStringArray& aszX)//Hop cua cac tap hop
{
	CString tempS;
	for(int i=0;i<aszX.GetSize();i++)
		tempS +=aszX[i];
	tempS = Essence(tempS);
	return tempS;
}
CString CAGmagicEhancedUtil::Union(CStringArray& aszX, CStringArray& aszY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(Union(aszX),Union(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Union(CString szX, CStringArray& aszY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(szX,Union(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Union(CStringArray& aszX, CString szY)//Hop cua cac tap hop
{
	CString tempS;
	tempS = Union(Union(aszX),szY);
	return tempS;
}
void CAGmagicEhancedUtil::Union(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	aTemp.Append(aX);
	aTemp.Append(aY);
	Essence(aTemp,aZ);
}
CString CAGmagicEhancedUtil::Sub(CString szX, CString szY)//Hieu cua 2 tap hop
{
	CString tempS;

	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])==-1)	tempS +=szX[i];
	tempS = Essence(tempS);
	return tempS;
		
}
CString CAGmagicEhancedUtil::Sub(CStringArray& aszX)//Hieu cua cac tap hop
{
	CString tempS=aszX[0];

	for(int i=1;i<aszX.GetSize();i++)
		tempS=Sub(tempS,aszX[i]);
	return tempS;
		
}
CString CAGmagicEhancedUtil::Sub(CStringArray& aszX, CStringArray& aszY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(Union(aszX),Union(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Sub(CString szX, CStringArray& aszY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(szX,Union(aszY));
	return tempS;
}
CString CAGmagicEhancedUtil::Sub(CStringArray& aszX, CString szY)//Hieu cua cac tap hop
{
	CString tempS;
	tempS = Sub(Union(aszX),szY);
	return tempS;
}
void CAGmagicEhancedUtil::Sub(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ )
{
	CUIntArray aTemp;
	for(int i=0;i<aX.GetSize();i++)
		if(FindUInt(aX[i],aY)==-1)//Neu khong tim thay
			aTemp.Add(aX[i]);
	Essence(aTemp,aZ);
	
}
//X co chua trong Y hay khong
//Qui uoc X=Y van co the xem X chua trong Y
agbool CAGmagicEhancedUtil::IsInLeast(CString szX, CString szY)//szX co 1 phan tu nam trong szY khong
{
	if(szX.IsEmpty())	return agtrue;
	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])!=-1)	return agtrue;

	return agfalse;
}
agbool CAGmagicEhancedUtil::IsIn(CString szX, CString szY)
{
	if(szX.IsEmpty())	return agtrue;
	for(int i=0;i<szX.GetLength();i++)
		if(szY.Find(szX[i])==-1)	return agfalse;

	return agtrue;
}

agbool CAGmagicEhancedUtil::IsIn(CString szX, CStringArray& aszY,agbool Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszY);
		return (IsIn(szX,tempS));	
	}
	else
	{
		for(int i=0;i<aszY.GetSize();i++)
			if(!IsIn(szX,aszY[i]))	return agfalse;
		return agtrue;
	}
}
agbool CAGmagicEhancedUtil::IsIn(CStringArray& aszX, CString szY, agbool Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return (IsIn(tempS,szY));
	}
	else
	{
		for(int i=0;i<aszX.GetSize();i++)
			if(!IsIn(aszX[i],szY))	return agfalse;
		return agtrue;
	}
}
agbool CAGmagicEhancedUtil::IsIn(CStringArray& aszX, CStringArray& aszY,agbool Flag)
{
	if(Flag)
	{
		CString tempX,tempY;
		tempX = Union(aszX);
		tempY = Union(aszY);
		return (IsIn(tempX,tempY));
	}
	else
	{
		for(int i=0;i<aszX.GetSize();i++)
			if(!IsIn(aszX[i],aszY,agfalse))	return agfalse;

		return agtrue;
	}
}
agbool CAGmagicEhancedUtil::IsInF(CString szX, CStringArray& aszY,int& index)
{
	for(int i=0;i<aszY.GetSize();i++)
		if(IsIn(szX,aszY[i]))	
		{
			index=i;
			return agtrue;
		}
	return agfalse;
}
agbool CAGmagicEhancedUtil::IsInF(CStringArray& aszX, CString szY,int& index)
{
	for(int i=0;i<aszX.GetSize();i++)
		if(IsIn(aszX[i],szY))	
		{
			index=i;
			return agtrue;
		}
	return agfalse;
}
agbool CAGmagicEhancedUtil::IsInF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2)
{
	//index1 : chi so trong aszX
	//index2 : chi so trong aszY
	for(int i=0;i<aszX.GetSize();i++)
		if(IsInF(aszX[i],aszY,index2))	
		{
			index1=i;
			return agtrue;
		}
	return agfalse;
}

agbool CAGmagicEhancedUtil::IsEqual(CString szX, CString szY)//X co bang Y khong
{
	return (IsIn(szX,szY) && IsIn(szY,szX));
}
agbool CAGmagicEhancedUtil::IsEqual(CString szX, CStringArray& aszY,agbool Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszY);
		return (IsEqual(szX,tempS));
	}
	else
		return(IsIn(szX,aszY,agfalse)&&IsIn(aszY,szX,agfalse));
}
agbool CAGmagicEhancedUtil::IsEqual(CStringArray& aszX, CString szY,agbool Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return (IsEqual(tempS,szY));
	}
	else
		return(IsIn(aszX,szY,agfalse)&&IsIn(szY,aszX,agfalse));
		
}
agbool CAGmagicEhancedUtil::IsEqual(CStringArray& aszX, CStringArray& aszY, agbool Flag)
{
	if(Flag)
	{
		CString tempS;
		tempS = Union(aszX);
		return(IsEqual(tempS,aszY));
	}
	else
		return(IsIn(aszX,aszY,agfalse) && IsIn(aszY,aszX,agfalse));
}
agbool CAGmagicEhancedUtil::IsEqualF(CString szX, CStringArray& aszY,int& index1,int& index2)
{
	agbool ret=(IsInF(szX,aszY,index1)&&IsInF(aszY,szX,index2));
	return ret&&(index1==index2);
}
agbool CAGmagicEhancedUtil::IsEqualF(CStringArray& aszX, CString szY,int& index1,int& index2)
{
	agbool ret=(IsInF(aszX,szY,index1)&&IsInF(szY,aszX,index2));
	return ret&&(index1==index2);
}
agbool CAGmagicEhancedUtil::IsEqualF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2)
{
	int index3,index4,index5,index6;
	agbool ret=(IsInF(aszX,aszY,index3,index4) && IsInF(aszY,aszX,index5,index6));
	if(ret)
		if(index5==index4&&index3==index6)
		{
			index1=index3;
			index2=index4;
			return agtrue;
		}
	return agfalse;
}
agbool CAGmagicEhancedUtil::IsEqualSpecial(CStringArray& aszX, CStringArray& aszY)
{
	int i,j;
	for(i=0;i<aszX.GetSize();i++)
		for(j=0;j<aszY.GetSize();j++)
		{
			CString tempSi=aszX[i];
			CString tempSj=aszY[j];

			if(IsIn(aszX[i],aszY[j])&&IsIn(aszY[j],aszX[i]))	
						return agtrue;
		}
	return agfalse;
}

//Ham tim to hop cua tap szX
void CAGmagicEhancedUtil::Combine(CString szX, CString s, int k,CStringArray& aszC)
{
	if(szX.GetLength() > 12)
	{
		AfxMessageBox(_T("So to hop qua lon"),MB_OK);
		szX = szX.Left(12);
	}

	int i,j;
	CStringArray  aszTemp;
	for(i=k;i<szX.GetLength();i++)
	{
		aszTemp.Add(s + szX[i]);
		aszC.Add( Union(s , CharToString(szX[i])) );
	}
	k++;
	for(j=0;j<aszTemp.GetSize();j++)
		Combine(szX,aszTemp[j],j+k,aszC);
}

void CAGmagicEhancedUtil::Combine(CStringArray& aszX, CString s, int k,CStringArray& aszC)
{
	if(aszX.GetSize() > 10)
	{
		AfxMessageBox(_T("So to hop qua lon"),MB_OK);
		aszX.SetSize(10);
	}

	int i,j;
	CStringArray  aszTemp;
	for(i=k;i<aszX.GetSize();i++)
	{
		aszTemp.Add(s + aszX[i]);
		aszC.Add(Union(s , aszX[i]));
	}
	k++;
	for(j=0;j<aszTemp.GetSize();j++)
		Combine(aszX,aszTemp[j],j+k,aszC);
}
void CAGmagicEhancedUtil::Sort(CStringArray& aszX)
{
	int i,j;
	CString x;
	for (i=1;i<aszX.GetSize();i++)
	{
		x=aszX[i];j=i;
		while((j>0)&&(x.GetLength()<aszX[j-1].GetLength()))
		{
			aszX[j]=aszX[j-1];
			j--;
		}
		aszX[j]=x;
	}

}
void CAGmagicEhancedUtil::Sort(CStringArray* aszX)
{
	int i,j;
	CString x;
	for (i=1;i<aszX->GetSize();i++)
	{
		x=aszX->GetAt(i);j=i;
		while((j>0)&&(x.GetLength()<aszX->GetAt(j-1).GetLength()))
		{
			aszX->SetAt(j,aszX->GetAt(j-1));
			j--;
		}
		aszX->SetAt(j,x);
	}

}
//tim min, max
long CAGmagicEhancedUtil::Min(CUIntArray& array)
{
	long n=array.GetSize();
	long min=array.ElementAt(0);
	for(long i=1; i<n; i++)
	{
		if(min>(long)array.ElementAt(i))
			min=array.ElementAt(i);
	}
	return min;
}
//tim min, max
long CAGmagicEhancedUtil::Min(CUIntArray* parray)
{
	long n=parray->GetSize();
	long min=parray->ElementAt(0);
	for(long i=1; i<n; i++)
	{
		if(min>(long)parray->ElementAt(i))
			min=parray->ElementAt(i);
	}
	return min;
}
long CAGmagicEhancedUtil::Max(CUIntArray& array)
{
	long n=array.GetSize();
	long max=array.ElementAt(0);
	for(long i=1; i<n; i++)
	{
		if(max<(long)array.ElementAt(i))
			max=array.ElementAt(i);
	}
	return max;

}
long CAGmagicEhancedUtil::Max(CUIntArray* parray)
{
	long n=parray->GetSize();
	long max=parray->ElementAt(0);
	for(long i=1; i<n; i++)
	{
		if(max<(long)parray->ElementAt(i))
			max=parray->ElementAt(i);
	}
	return max;

}

//Ham tim co so toi thieu roi nhau
//Vao: aszX
//Ra : aszY
void CAGmagicEhancedUtil::Minimum(CStringArray& aszX, CStringArray& aszY )
{
	aszY.RemoveAll();
	CStringArray aszTemp;
	int i;
	aszTemp.Append(aszX);
	while(aszTemp.GetSize())
	{
		CString tempS1,tempS2,S1,S2,S3;
		tempS1 = aszTemp[0];
		aszTemp.RemoveAt(0);

		for(i=0;i<aszTemp.GetSize();i++)
		{
			S1 = Common(tempS1,aszTemp[i]);
			if(!S1.IsEmpty())
				break;
		}
		if(i==aszTemp.GetSize())//Neu X,Y khong co thuoc tinh chung
		{
			if(!tempS1.IsEmpty())
				aszY.Add(tempS1);
		}
		else
		{
			tempS2 = aszTemp[i];
			aszTemp.RemoveAt(i);

			if(!S1.IsEmpty())
				aszTemp.Add(S1);
			S2 = Sub(tempS1,tempS2);
			if((!S2.IsEmpty())&&(S2 != S1))	
				aszTemp.Add(S2);
			S3 = Sub(tempS2,tempS1);
			if((!S3.IsEmpty())&&(S3 != S1)&&(S3 != S2))	
				aszTemp.Add(S3);

		}
	}
}
agbool CAGmagicEhancedUtil::CreatePoint(int xr, int yr, int R,CArray<CPoint,CPoint&>& aPoint )
{

	if(R==0) return agfalse;
	aPoint.RemoveAll();

	int x=0,y=R;
	int p;
	int d1,d2;
	int i,n;
	CPoint point;
	CSize  size;
	CArray<CSize,CSize&> aTemp; 

	p=1-R;
	d1=2*x+3;
	d2=2*(x-y)+5;

	size.cx=x;
	size.cy=y;
	aTemp.Add(size);


	while (x<=y)
	{
		if(p<0)
		{
			p+=d1;
			d2+=2;
		}
		else
		{
			p+=d2;
			y--;
			d2+=4;
		}
		x++;
		d1+=2;
		size.cx=x;
		size.cy=y;
		aTemp.Add(size);
	}

	n=aTemp.GetSize();
	if(n==0)
		return agfalse;
	for(i=0;i<n;i++)//thu 1
	{
		point.x=xr+aTemp[i].cx;
		point.y=yr-aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=n-3;i>=0;i--) //thu2 
	{
		point.x=xr+aTemp[i].cy;
		point.y=yr-aTemp[i].cx;
		aPoint.Add(point);
	}
		
	for(i=1;i<n-1;i++)//thu 3 
	{
		point.x=xr+aTemp[i].cy;
		point.y=yr+aTemp[i].cx;
		aPoint.Add(point);
	}

	for(i=n-2;i>=1;i--)//thu 4
	{
		point.x=yr+aTemp[i].cx;
		point.y=xr+aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=0;i<n-1;i++)//thu 5
	{
		point.x=xr-aTemp[i].cx;
		point.y=yr+aTemp[i].cy;
		aPoint.Add(point);
	}
	for(i=n-2;i>=1;i--) //thu 6
	{
		point.x=xr-aTemp[i].cy;
		point.y=yr+aTemp[i].cx;
		aPoint.Add(point);
	}
	for(i=0;i<n-1;i++) //thu 7
	{
		point.x=xr-aTemp[i].cy;
		point.y=yr-aTemp[i].cx;
		aPoint.Add(point);
	}

	for(i=n-2;i>=1;i--)//thu 8
	{
		point.x=xr-aTemp[i].cx;
		point.y=yr-aTemp[i].cy;
		aPoint.Add(point);
	}
		
	return agtrue;
}
#endif	//#if (AGMAGIC_SUPPORT_MFC && AGMAGIC_SUPPORT_UTIL_ENHANCED)
