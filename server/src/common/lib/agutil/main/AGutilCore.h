#if !defined(AGUTIL_CORE_H__DEE61245_A429_11D2_84B1_00C0DFF84685__INCLUDED_)
#define AGUTIL_CORE_H__DEE61245_A429_11D2_84B1_00C0DFF84685__INCLUDED_

#include "../../../include/AGmagicDefs.h"
#include <sys/timeb.h>
#include <time.h>

/*******************************class CAGmagicMicUtil*******************************/
template<class AGARRAY_TYPE>		class CAGbaseArray;
template<class AGOBJ_ARRAY_TYPE>	class CAGobjPtrArray;

/*
class AGMAGIC_DECL CAGmagicMicUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicMicUtil
{
public:

#if AGMAGIC_SUPPORT_MFC

	/*
	class CAlgTime
	Chuc nang:
	Cach dung:
	Ghi chu:
	*/
	class CAlgTime
	{
	protected:
		agreal64		m_CurBeginTime;
		agreal64		m_CurEndTime;
		CStdioFile*		m_pAttachFile;
	public:
		CAlgTime();
		virtual ~CAlgTime();

		void		Begin();
		void		End();
		agreal64	GetSpan();
		CString		GetSpanStr();
		CString		GetSpanSecsStr();

		aguint64	GetTotalSpanSecs();
		aguint32	GetTotalSpanMiliSecs();

		void		AttachFile(const agtchar* FilePath);
		void		DetachFile(agbool bDeleteFile=agtrue);
		void		OutResult(const agtchar* algName, agbool shorten=agtrue);
	};
	static void ChangeURLFromWin(CString& URL);
	static void ChangeURLToWin(CString& URL);
	static CString GetLocalPathFromURL(CString& URL);

	static void DrawBitmap(HDC hDC, HBITMAP hBmp, aguint32 x=0, aguint32 y=0);
	static HINSTANCE FindResourceHandleInDynamicDLL(LPCTSTR szResourceName, LPCTSTR szResourceType);

	static agbool	FindArray(CDWordArray& aDW, aguint32 key, agint32& idx);
	static agbool	FindArray(CDWordArray& aDW, aguint32 key, CDWordArray& aIdx);
	static void		SortArray(CDWordArray& aDW, agbool dec=agfalse);
	static void		SortArray(CDWordArray& aDW, CDWordArray& aKey, agbool dec=agfalse);
#endif	//#if AGMAGIC_SUPPORT_MFC

	static agtchar*	AGconvertFromVariantToStr(_variant_t& varValue, agtchar*& strValue);
	static aguint_id AGconvertFromVariantToID(_variant_t& varValue);

	static void	ChangeTDtoBU(agint32 height, AGBU_RECT* pDstRect, AGTD_RECT* pSrcRect);
	static void	ChangeTDtoBU(agint32 height, AGBU_POINT* pDstPoint, AGTD_POINT* pSrcPoint);
	static void	ChangeBUtoTD(agint32 height, AGTD_RECT* pDstRect, AGBU_RECT* pSrcRect);
	static void	ChangeBUtoTD(agint32 height, AGTD_POINT* pDstPoint, AGBU_POINT* pSrcPoint);
};

#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
template<class T>
T AGconvertFromVariantToNumber(_variant_t&	varValue)
{
	T fValue;
	if(varValue.vt==VT_EMPTY||varValue.vt==VT_NULL)
		fValue=0;
	else
	{
		if(varValue.vt==VT_R4)
			fValue=(T)((float)varValue);
		else if(varValue.vt==VT_R8)
			fValue=(T)((double)varValue);
		else if(varValue.vt==VT_I2||varValue.vt==VT_I4||
				varValue.vt==VT_UI2||varValue.vt==VT_UI4||
				varValue.vt==VT_INT||varValue.vt==VT_UINT)
			fValue=(T)((long)varValue);
		else if(varValue.vt==VT_I8 || varValue.vt==VT_UI8)
		#if _MFC_VER < 0x0700
			fValue=(T)((long)varValue);
		#else
			fValue=(T)((__int64)varValue);
		#endif	//#if _MFC_VER < 0x0700
		else
			fValue=0;
	}
	return fValue;
}
#endif	//#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS


/*******************************class CAGmagicStrUtil*******************************/
/*
class AGMAGIC_DECL CAGmagicStrUtil
Chuc nang:
Cach dung:
Ghi chu:
*/

class AGMAGIC_DECL CAGmagicStrUtil
{
public:

#if AGMAGIC_SUPPORT_MFC
	//
	static void SplitString(CString& src, CString key, CStringArray& aS);
	static void SplitString(CString& src, CString key, CDWordArray& aDW);
	static void SplitString(CString& src, CString key, CArray<agreal64, agreal64>& aR);
	
	static CString CatString(CStringArray& aS, CString key);
	static CString CatString(CStringArray* paS, CString key);
	static CString CatString(CDWordArray& aDW, CString key);
	static CString CatString(CDWordArray* paDW, CString key);
	static CString CatString(CArray<agreal64, agreal64>* paR, CString key);
	static CString CatString(CArray<agreal64, agreal64>& aR, CString key);
	//
#endif	//#if AGMAGIC_SUPPORT_MFC

//
#if AGMAGIC_SUPPORT_MFC
	static CString	ChangeIntegerToString(agint32 x);
	static CString	ChangeIntegerToString(aguint32 x);

	static CString ChangeIntegerToString(agint64 x);
	static CString ChangeIntegerToString(aguint64 x);

	static CString ChangeHighestIntegerToString(agint_highest x);
	static CString ChangeHighestIntegerToString(aguint_highest x);

	static CString ChangeReal64ToString(agreal64 x);
	static CString ChangeIDToString(aguint_id id);
	static CString ChangeTimeToNumberString(time_t t);
#endif	//#if AGMAGIC_SUPPORT_MFC
	static agtchar*	ChangeIntegerToString(agint32 x, agtchar sNumber[]/*, agint32 size_in_character*/);
	static agtchar*	ChangeIntegerToString(aguint32 x, agtchar sNumber[]/*, agint32 size_in_character*/);

	static agtchar*	ChangeIntegerToString(agint64 x, agtchar sNumber[]/*, agint32 size_in_character*/);
	static agtchar*	ChangeIntegerToString(aguint64 x, agtchar sNumber[]/*, agint32 size_in_character*/);

	static agtchar*	ChangeHighestIntegerToString(agint_highest x, agtchar sNumber[]/*, agint32 size_in_character*/);
	static agtchar*	ChangeHighestIntegerToString(aguint_highest x, agtchar sNumber[]/*, agint32 size_in_character*/);

	static agtchar*	ChangeReal64ToString(agreal64 x, agtchar tcsNumber[]/*, agint32 size_in_character*/);
	static agtchar*	ChangeIDToString(aguint_id id, agtchar sNumber[]/*, agint32 size_in_character*/);
	static agtchar*	ChangeTimeToNumberString(time_t t, agtchar sNumber[]/*, agint32 size_in_character*/);
	
	static agtchar*	private_tcscat(agtchar*& dst, const agtchar* src, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, const agtchar ch, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, agint32 x, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, aguint32 x, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, agint64 x, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, aguint64 x, agbool bIsResize);
	static agtchar*	private_tcscat(agtchar*& dst, agreal64 x, agbool bIsResize);
	static agtchar*	private_tcscat_highest(agtchar*& dst, agint_highest x, agbool bIsResize);
	static agtchar*	private_tcscat_highest(agtchar*& dst, aguint_highest x, agbool bIsResize);
	static agtchar*	private_tcscat_id(agtchar*& dst, aguint_id x, agbool bIsResize);
	static agtchar*	private_tcscat_time(agtchar*& dst, time_t t, agbool bIsResize);

	static agtchar*	private_tcstrimL(agtchar pData[], const agtchar* lpszTargets);
	static agtchar*	private_tcstrimR(agtchar pData[], const agtchar* lpszTargetList);
	static agtchar*	private_tcstrim(agtchar pData[], const agtchar* lpszTargetList);

	static void		replace(agtchar data[], agtchar ch, agtchar repch);
	static agtchar* private_tcsstr(agtchar string[], agtchar strCharSet[]);
//
};

#if AGMAGIC_SUPPORT_MFC
template<class T>
CString AG_ChangeNumberToString(T number)
{
	return CAGmagicStrUtil::ChangeReal64ToString((agreal64)number);
}
#endif	//#if AGMAGIC_SUPPORT_MFC

template<class T>
agtchar*	AG_ChangeNumberToString(T number, agtchar sNumber[])
{
	return CAGmagicStrUtil::ChangeReal64ToString((agreal64)number,sNumber);
}
template<class T>
agtchar*	AG_private_tcscat_number(agtchar*& dst, T number, agbool bIsResize)
{
	return CAGmagicStrUtil::private_tcscat(dst,(agreal64)number,bIsResize);
}

/*******************************class CAGmagicIOUtil*******************************/
#define	AGMAGIC_AND_SEPS		_T("&&")
#define	AGMAGIC_OR_SEPS			_T("||")

typedef agbool (*AGMAGIC_IO_TEST_FUNC) (void* , agtchar* );

class AGMAGIC_DECL CAGmagicIOUtil
{
public:
	static void Browse(
							void (*dirFrontFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
							void (*dirBackFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),
							void (*fileFunction)(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved),

							agtchar szDstOrgDir[],
							agtchar szOrgDir[],		agtchar szBaseFilter[],

							agtchar szDirInclude[],		agtchar szDirExclude[],
							agtchar szFileExtInclude[],	agtchar szFileExtExclude[],

							agbool	isAlwaysDoDirFunction,
							agtchar seps[]=AGMAGIC_OR_SEPS,
							void* pReserved=NULL
						);
	static void Browse2(
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
							void* pReserved=NULL
						);
	static void SimpleBrowseFiles(
							void (*fileFunction)(void* pAtt, void* szPath,void* pReserved),
							agtchar szOrgDir[],
							agtchar szFilter[],
							agtchar seps[]=AGMAGIC_OR_SEPS,
							void* pReserved=NULL
						);

	static agbool isFileHeader(void* pAtt, agtchar* pReservedPath);
	static agbool isFileBin(void* pAtt, agtchar* pReservedPath);
	static agbool isFileWaste(void* pAtt, agtchar* pReservedPath);
	static agbool isFileHeaderAndBin(void* pAtt, agtchar* pReservedPath);
	static agbool isFileWasteAndBin(void* pAtt, agtchar* pReservedPath);

	static agbool isDirCompile(void* pAtt, agtchar* pReservedPath);
	static agbool isDirBin(void* pAtt, agtchar* pReservedPath);
	static agbool isDirCompileAndBin(void* pAtt, agtchar* pReservedPath);

	static agtchar*	ConvertAndAllocFullURL(agtchar brief_url[]);
	static agtchar*	ConvertAndAllocBriefURL(agtchar full_url[]);
};

/*******************************class CAGmagicDBOrg*******************************/

class AGMAGIC_DECL CAGmagicDBOrg
{
protected:
	void*		m_pDBCnnI;
public:

	CAGmagicDBOrg();
	virtual ~CAGmagicDBOrg();

	virtual void*	DBCnnAttach(void* pDBCnnI);//khong AddRef, tra ve Connection cu doi ADO
	virtual void*	DBCnnDetach();//khong Release
	virtual agbool	DBCnnIsValid();
	void*			DBCnnGet();
};

/*******************************class CAGmagicDBUtil*******************************/
/*
class AGMAGIC_DECL CAGmagicDBUtil
Chuc nang:
Cach dung:
Ghi chu:
*/

class AGMAGIC_DECL CAGmagicDBUtil
{
public:

//Database
	typedef struct tagDBCONNECTION_CONFIG
	{
		//throw _T("Implement not yet");
	} DBCONNECTION_CONFIG;

	#define INIT_DBCONNECTION_CONFIG_PTR(pxxxDBCnnConfig) \
	{ \
	}

	//pDBCnnI la _Connection* doi voi ADO
	static agbool	CnnCreate(void*& pDBCnnI, agtchar* szDBCnn, DBCONNECTION_CONFIG* pDBCnnConfig=NULL, agbool bIsCallCoInitializeForInitADO=agtrue);
	//pDBCnnI la _Connection* doi voi ADO
	static agbool	CnnDestroy(void*& pDBCnnI, agbool bIsCallCoUninitialize=agtrue);
	//pDBCnnI la _Connection* doi voi ADO
	static void		CnnSetConfig(void* pDBCnnI, DBCONNECTION_CONFIG* pDBCnnConfig);
	//pDBCnnI la _Connection* doi voi ADO
	static void		CnnGetConfig(void* pDBCnnI, DBCONNECTION_CONFIG* pDBCnnConfig);

	//pDBCnnI la _Connection* doi voi ADO
	static void		BeginTrans(void* pDBCnnI);
	//pDBCnnI la _Connection* doi voi ADO
	static void		CommitTrans(void* pDBCnnI);
	//pDBCnnI la _Connection* doi voi ADO
	static void		RollbackTrans(void* pDBCnnI);

#if AGMAGIC_SUPPORT_MFC
	//pDBCnnI la _Connection* doi voi ADO
	static agbool	ExcuteSQL(void* pDBCnnI, CStringArray& aSQL, agbool bIsTrans);
#endif	//#if AGMAGIC_SUPPORT_MFC
	//pDBCnnI la _Connection* doi voi ADO
	static agbool	ExcuteSQL(void* pDBCnnI, agtchar SQL[], agbool bIsTrans);
	//pDBCnnI la _Connection* doi voi ADO
	static agbool	ExcuteSQL(void* pDBCnnI, agtchar* aSQL[], aguint32 nSQL, agbool bIsTrans);

	//pDBCnnI la _Connection* doi voi ADO
	static void		DisplayErrors(void* pDBCnnI);
};

template<class T>//pDBCnnI la _Connection* doi voi ADO
agbool AGdbRead(void* pDBCnnI, agtchar SQL[], agbool bIsTrans, T*& data, agint32& fieldsNum)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agbool bResult=AGadodbRead((_Recordset*)pRs,data,fieldsNum);
		pRs->Close();
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return bResult;
	}
	catch(_com_error &e)
	{
		CAGmagicDBUtil::DisplayErrors(pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
#else
	throw _T("Implement not yet");
#endif
}

template<class T>//pDBCnnI la _Connection* doi voi ADO
agbool AGdbRead(void* pDBCnnI, agtchar SQL[], agbool bIsTrans, T**& data, agint32& fieldsNum, agint32& recordsNum)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agbool bResult=AGadodbRead((_Recordset*)pRs,data,fieldsNum,recordsNum);
		pRs->Close();
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return bResult;
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
}

template<class T>//pCnnI la _Connection* doi voi ADO
agbool AGdbReadOneField(void* pDBCnnI, agtchar SQL[], agint32 idxOfField, agbool bIsTrans, T*& data, agint32& ne)
{
#if	AGMAGIC_SUPPORT_ADO
	try
	{
		if(bIsTrans) ((_Connection*)pDBCnnI)->BeginTrans();
		_RecordsetPtr	pRs(_T("ADODB.Recordset"));
		pRs->PutRefActiveConnection((_Connection*)pDBCnnI);
		pRs->Open((LPCTSTR)SQL, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdText);

		agbool bResult=AGadodbReadOneField((_Recordset*)pRs,idxOfField,data,ne);
		pRs->Close();
		if(bIsTrans) ((_Connection*)pDBCnnI)->CommitTrans();
		return bResult;
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
}

#if	AGMAGIC_SUPPORT_ADO
template<class COMMANDPTR>//COMMANDPTR=_Command*
agbool AGadodbCmdExcuteSQL(COMMANDPTR pCmdI, agtchar SQL[], agbool bIsTrans)
{
	try
	{
		_bstr_t bsSQL(SQL);
		if(bsSQL.length()==0)	throw _T("SQL string empty");
		if(bIsTrans) pADODBCnnI->BeginTrans();

		pCmdI->PutCommandText(bsSQL);
		pCmdI->Execute(NULL,NULL,adCmdText);
		
		if(bIsTrans) pADODBCnnI->CommitTrans();
		return agtrue;
	}
	catch(_com_error &e)
	{
		_ConnectionPtr pDBCnnI=pCmdI->ActiveConnection;
		CAGmagicDBUtil::DisplayErrors((_Connection*)pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
}

template<class RECORDSETPTR>//RECORDSETPTR=_Recordset*
agint32 AGadodbGetRecordCount(RECORDSETPTR pRsI, agbool bSupportBookmark)
{
	agint32 rCount=0;

	_variant_t bookmark;
	if(bSupportBookmark)
		bookmark=pRsI->Bookmark;
	else
		pRsI->MoveFirst();

	while(!(pRsI->EndOfFile))
	{
		rCount ++;
		pRsI->MoveNext();
	}

	if(bSupportBookmark)
		pRsI->Bookmark=bookmark;
	else
		pRsI->MoveFirst();

	return rCount;
}
template<class RECORDSETPTR>//RECORDSETPTR=_Recordset*
agint32 AGadodbGetNumberOfPages(RECORDSETPTR pRsI, agint32 NumberRecordsOfPage)
{
	throw _T("Implement not yet");
}
template<class RECORDSETPTR, class T>//RECORDSETPTR=_Recordset*
agbool AGadodbRead(RECORDSETPTR pRsI, T*& data, agint32& fieldsNum)
{
	if(data!=NULL)	free(data);
	data=NULL;
	fieldsNum=0;
	try
	{
        if((pRsI->EndOfFile))	return agfalse;
		fieldsNum=pRsI->GetFields()->GetCount();
		if(fieldsNum<=0)	{fieldsNum=0;return agfalse;}

		data=(T*)malloc(fieldsNum*sizeof(T));
		memset(data,0,fieldsNum*sizeof(T));

		for(agint32 i=0; i<fieldsNum; i++)//bat sau tu field 1 tro di
		{
			//_bstr_t		bsName = pRsI->Fields->GetItem((long)i)->Name;
			_variant_t	varValue = pRsI->Fields->GetItem((long)i)->Value;
			data[i]=AGconvertFromVariantToNumber<T>(varValue);
		}
		return agtrue;
	}
	catch(_com_error &e)
	{
		//CAGmagicDBUtil::DisplayErrors((_Connection*)pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}

}

template<class RECORDSETPTR, class T>//RECORDSETPTR=_Recordset*
agbool AGadodbRead(RECORDSETPTR pRsI, T**& data, agint32& fieldsNum, agint32& recordsNum)
{
	if(data!=NULL)	free(data);
	data=NULL;
	fieldsNum=0;
	recordsNum=0;
	try
	{
        if((pRsI->EndOfFile))	return agfalse;
		recordsNum=AGadodbGetRecordCount(pRsI,agfalse);
		data=(T**)malloc(recordsNum*sizeof(T*));
		memset(data,NULL,recordsNum*sizeof(T*));

		aguint32	count=0;
		while(!(pRsI->EndOfFile))
        {
			if(!AGadodbRead(pRsI,data[count],fieldsNum))//cap phat vung nho cho data[count]
				throw _T("Read Error");
				
			pRsI->MoveNext();
			count++;
		}
		return agtrue;
	}
	catch(_com_error &e)
	{
		//CAGmagicDBUtil::DisplayErrors((_Connection*)pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
}
template<class RECORDSETPTR, class T>//RECORDSETPTR=_Recordset*
agbool AGadodbReadOneField(RECORDSETPTR pRsI, agint32 idxOfField, T*& data, agint32& ne)
{
	if(data!=NULL)	free(data);
	data=NULL;
	ne=0;
	try
	{
        if((pRsI->EndOfFile))	return agfalse;
		ne=AGadodbGetRecordCount(pRsI,agfalse);
		data=(T*)malloc(ne*sizeof(T));
		memset(data,NULL,ne*sizeof(T));

		agint32	count=0;
		while(!(pRsI->EndOfFile))
        {
			//_bstr_t		bsName = pRsI->Fields->GetItem((long)idxOfField)->Name;
			_variant_t	varValue = pRsI->Fields->GetItem((long)idxOfField)->Value;
			data[count]=AGconvertFromVariantToNumber<T>(varValue);

			pRsI->MoveNext();
			count++;
		}
		if(count!=ne)	throw _T("Serious error. Error database");
		return agtrue;
	}
	catch(_com_error &e)
	{
		//CAGmagicDBUtil::DisplayErrors((_Connection*)pDBCnnI);
		::MessageBox(::GetDesktopWindow(),e.ErrorMessage(),_T("ADO Error"),MB_OK|MB_ICONSTOP);
		throw e;
	}
}

#endif	//#if	AGMAGIC_SUPPORT_ADO


/*******************************class CAGmagicConfUtil*******************************/
//Thu muc base cua ung dung duoc xem nhu la noi chua agmagic. Vi du: C:\agmagic
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
	#define	AGMAGIC_WINRAR_PATH					_T("C:\\Program Files\\WinRAR\\WinRAR.exe")
	#define	AGMAGIC_DEFAULT_PACKAPP_PATH		AGMAGIC_WINRAR_PATH
	#define	AGMAGIC_DEFAULT_BACKUP_PATH			_T("D:\\backup")

	#define	AGMAGIC_BASE_RELATED_BIN_PATH		_T("bin")

	#if		AGMAGIC_MFC_VER < 0x0700
		#define	AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH	_T("src\\common\\lib\\Prof-UIS\\Bin_600")
	#elif	AGMAGIC_MFC_VER == 0x0700
		#define	AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH	_T("src\\common\\lib\\Prof-UIS\\Bin_700")
	#elif	AGMAGIC_MFC_VER == 0x0710
		#define	AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH	_T("src\\common\\lib\\Prof-UIS\\Bin_710")
	#elif	AGMAGIC_MFC_VER == 0x0800
		#define	AGMAGIC_BASE_RELATED_PROUIS_BIN_PATH	_T("src\\common\\lib\\Prof-UIS\\Bin_800")
	#else
		#error _T("Implement not yet")
	#endif
	#define	AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH		_T("src\\image\\ip\\lib\\CxImage\\bin")
#elif AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	#define	AGMAGIC_DEFAULT_BACKUP_PATH					_T("D:\\backup")

	#define	AGMAGIC_BASE_RELATED_BIN_PATH				_T("bin")
	#define	AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH		_T("src\\image\\ip\\lib\\CxImage\\bin")
#elif AGMAGIC_OS_TYPE==AGMAGIC_LINUX_OS
	#define	AGMAGIC_DEFAULT_BACKUP_PATH					_T("/backup")
	#define	AGMAGIC_BASE_RELATED_BIN_PATH				_T("bin")
	#define	AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH		_T("src/image/ip/lib/CxImage/bin")
#elif AGMAGIC_OS_TYPE==AGMAGIC_UNIX_OS
	#define	AGMAGIC_DEFAULT_BACKUP_PATH					_T("/backup")

	#define	AGMAGIC_BASE_RELATED_BIN_PATH				_T("bin")
	#define	AGMAGIC_BASE_RELATED_CXIMAGE_BIN_PATH		_T("src/image/ip/lib/CxImage/bin")
#else
	#error _T("Implement not yet")
#endif
#define	AGMAGIC_DEFAULT_PACKED_FILENAME					_T("vn.agmagic.server.rar")


#define	AGMAGIC_HEADER_FILEEXT			_T("h||hpp||idl||inl||hm||tli||blank||inc")
#define	AGMAGIC_BIN_FILEEXT				_T("lib||dll||exe||bat||tlb||class||sh")
#define	AGMAGIC_WASTE_FILEEXT_RESTRICT	_T("bsc||exp||idb||ilk||obj||pch||pdb||res||sbr||tmp||rsp")
#define	AGMAGIC_WASTE_FILEEXT			_T("exp||obj||pch||sbr")
#define	AGMAGIC_COMPILE_DIRNAME			_T("Debug||DebugDll||Release||output")
#define	AGMAGIC_BIN_DIRNAME				_T("bin||Bin_600||Bin_700||Bin_710")

/*
class AGMAGIC_DECL CAGmagicConfUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicConfUtil
{
private:
	static agbool	bIsInitAGmagicConf;
public:
#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS || AGMAGIC_OS_TYPE==AGMAGIC_WINCE_OS
	static HANDLE	AGmagicUtil_hModule;
#endif
	static agbool	AGmagicUtil_bIsShowCopyright;
	static agtchar	AGmagic_GlobalCurDir[AGMAGIC_MAX_PATH_LENGTH];

//Cac bien cau hinh
#if AGMAGIC_SUPPORT_ADO
	static agint32								AGmagic_GlobalADOProvider;
#endif
	static agtchar								AGmagic_GlobalDBCnnStr[1024];
	static CAGmagicDBUtil::DBCONNECTION_CONFIG	AGmagic_GlobalDBCnnConfig;

	static agtchar*		AGmagic_GlobalSampleImagesDirNames[];
	static agint32		nAGmagic_GlobalSampleImagesDirNames;
	static agbool		bAGmagic_GlobalSampleImagesDirNames[];
	static aguint_id	idAGmagic_GlobalSampleImagesDirNames[];

	static void			Init();
	static agbool		IsNegativeImageWhenSegment(aguint_id ImageType);
	static aguint_id	GetTypeOfSampleImagesDirNames(agtchar szDirName[]);
//cac ham config

	static 	agtchar* AGMAGIC_BIN_RELATED_BIN_PATH();
	static 	agtchar* AGMAGIC_BIN_RELATED_PROUIS_BIN_PATH();
	static 	agtchar* AGMAGIC_BIN_RELATED_CXIMAGE_BIN_PATH();

	static	agtchar* AGMAGIC_HEADER_AND_BIN_FILEEXT(agtchar fileext[]);
	static	agtchar* AGMAGIC_WASTE_AND_BIN_FILEEXT(agtchar fileext[]);
	static	agtchar* AGMAGIC_COMPILE_AND_BIN_DIRNAME(agtchar dirname[]);

	static agtchar* AGmagicBaseDirAbsoluteFromBin();

	static agtchar* AGmagicBinPathAbsolute();
	static agtchar* AGmagicProUISBinPathAbsolute();
	static agtchar* AGmagicCxImageBinPathAbsolute();
	static agtchar* AGmagicSampleImagesPathAbsolute();
	static agtchar* AGmagicSampleImagesPathAbsolute2();
	static agtchar*	AGmagic_GlobalSampleImagesExcludeDir();

	static agbool	AGmagicGetEnvPathVar(agtchar*& szEnvPathVar, aguint32* reserved);
	static agbool	AGmagicSetEnvPathVar(agtchar szEnvPathVar[], aguint32* reserved);

};

/*******************************class CAGmagicSysUtil*******************************/
/*
class AGMAGIC_DECL CAGmagicSysUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
#define AGMAGIC_OS_LOGOFF		0
#define AGMAGIC_OS_POWEROFF		1
#define AGMAGIC_OS_REBOOT		2
#define AGMAGIC_OS_SHUTDOWN		3
#define AGMAGIC_OS_LOCK			4

class AGMAGIC_DECL CAGmagicSysUtil
{
public:
	static agbool	ExitOS(aguint32 flag=AGMAGIC_OS_SHUTDOWN);
	static void		ExitOSShowOption(aguint32 timeout=30, agbool bIsRebootAfterShutdown=agtrue);
	static void		ExitOSShowOptionAbort();
	static void		ExecProgram(agtchar szProgramPath[]);

	//typedef int (FAR WINAPI *FARPROC)();
	static agbool	Invoke_FARPROC_LibFunc(agtchar szLibPath[], agtchar szFuncName[], agint32& vReturn);

	//STDAPI DllRegisterServer(void);
	//STDAPI DllUnregisterServer(void);
	//#define STDAPI	EXTERN_C HRESULT STDAPICALLTYPE
	static agbool	RegSvr(agtchar szSvrPath[]);//tuong duong voi RegSrv32 szSvrPath
	static agbool	UnregSvr(agtchar szSvrPath[]);//tuong duong voi RegSrv32 /u szSvrPath

};

/***********************class CAGoutputConsole****************************/

class AGMAGIC_DECL CAGoutputConsole
{
protected:
	FILE* m_f;

public:
	CAGoutputConsole();
	virtual ~CAGoutputConsole();
	FILE* Attach(FILE* f);
	FILE* Attach(agtchar szFilePath[]);

	void Out(agtchar szMsg[]);
};

/*******************************class CAGmagicEhancedUtil*******************************/

/*
class AGMAGIC_DECL CAGmagicEhancedUtil
Chuc nang:
Cach dung:
Ghi chu:
*/
class AGMAGIC_DECL CAGmagicEnhancedUtil
{
public:
	CAGmagicEnhancedUtil()
	{
	}
	virtual ~CAGmagicEnhancedUtil()
	{
	}
//Cac ham tien ich enhanced
#define	AGMAGIC_SUPPORT_UTIL_ENHANCED		0
#if (AGMAGIC_SUPPORT_MFC && AGMAGIC_SUPPORT_UTIL_ENHANCED)
	int		FindUInt(unsigned int x, CUIntArray& aUInt);
	long	FindString(CString& x, CStringArray& aS);
	agbool	FindUInt(unsigned int x, CArray<CUIntArray, CUIntArray&>& aUInt);
	agbool	FindUInt(unsigned int x, CArray<CUIntArray, CUIntArray&>& aUInt,int& seg,int& off);

	agbool	FindMapKey(CString& x, CMapStringToString& map, CString& rKey, CString& rValue);//x la key can tim
	agbool	FindMapValue(CString& x, CMapStringToString& map, CString& rKey, CString& rValue);//x la value can tim

	CString MinMapKey(CMapStringToString& map);
	CString MaxMapKey(CMapStringToString& map);
	CString MinMapValue(CMapStringToString& map);
	CString MaxMapValue(CMapStringToString& map);

	void	Alpha(CString szX,CString& szY);//loai bo nhung ky tu thong phai la ky tu Alphabe
	void	Alpha(CStringArray& aszS);
	CString CharToString(TCHAR ch);

	void	SplitStringEx(CString szS,TCHAR ch, CStringArray& aszR);//Tach chuoi
	void	SplitStringEx(CString szS,LPCTSTR lpszS, CStringArray& aszR);

	void	StringArrayToString(CStringArray& aszX, CString& szY, LPCTSTR phancach);
	void	StringArrayToString(CStringArray* aszX, CString& szY, LPCTSTR phancach);
	void	RemoveStringFromStringArray(CString szS, CStringArray& aszS);

	void	StringMapToKeyString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach);//lay tat ca cac khoa cua aszX vao szY
	void	StringMapToKeyString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach);
	void	StringMapToValueString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach);//lay tat ca cac khoa cua aszX vao szY
	void	StringMapToValueString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach);
	void	StringMapToKeyValueString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach);//lay tat ca cac khoa va tri cua aszX vao szY dang key1:value1,key2:value2,...
	void	StringMapToKeyValueString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach);//lay tat ca cac khoa va tri cua aszX vao szY dang key1:value1,key2:value2,..
	void	StringMapToString(CMapStringToString& mszX, CString& szY, LPCTSTR phancach);//lay tat ca cac khoa cua aszX vao szY
	void	StringMapToString(CMapStringToString* pmszX, CString& szY, LPCTSTR phancach);

	void	StringMapToKeyUIntArray(CMapStringToString& mszX, CUIntArray& aUInt);//lay tat ca cac khoa cua aszX thanh mang so nguyen
	void	StringMapToKeyUIntArray(CMapStringToString* pmszX, CUIntArray& aUInt);
	void	StringMapToKeyStringArray(CMapStringToString& mszX, CStringArray& aszS);//lay tat ca cac khoa cua aszX thanh mang so nguyen
	void	StringMapToKeyStringArray(CMapStringToString* pmszX, CStringArray& aszS);

	void	StringMapToValueUIntArray(CMapStringToString& mszX, CUIntArray& aUInt);//lay tat ca cac khoa cua aszX thanh mang so nguyen
	void	StringMapToValueUIntArray(CMapStringToString* pmszX, CUIntArray& aUInt);
	void	StringMapToValueStringArray(CMapStringToString& mszX, CStringArray& aszS);//lay tat ca cac khoa cua aszX thanh mang so nguyen
	void	StringMapToValueStringArray(CMapStringToString* pmszX, CStringArray& aszS);

	void	CopyStringMap(CMapStringToString& mszDst, CMapStringToString& mszSrc);
	void	CopyStringMap(CMapStringToString* pmszDst, CMapStringToString* pmszSrc);

	void	StringToStringMap(CString szX, CMapStringToString& mszY);
	void	StringToStringMap(CString szX, CMapStringToString* pmszY);

	CString  Essence(CString szX);//Loai bo nhung phan tu trung nhau
	void     Essence(CStringArray& aszX,CStringArray& aszY);//Loai bo nhung phan tu trung nhau
	void     Essence(CUIntArray& aX,CUIntArray& aY);//Loai bo nhung phan tu trung nhau

	CString  Common(CString szX, CString szY);//Giao cua 2 tap hop
	CString  Common(CStringArray& aszX);//Giao cua cac tap hop
	CString  Common(CStringArray& aszX, CStringArray& aszY);//Giao cua cac tap hop
	CString  Common(CString szX, CStringArray& aszY);//Giao cua cac tap hop
	CString  Common(CStringArray& aszX, CString szY);//Giao cua cac tap hop
	void     Common(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Giao cua cac tap hop

	CString  Union(CString szX, CString szY);//Hop cua 2 tap hop
	CString  Union(CStringArray& aszX);//Hop cua cac tap hop
	CString  Union(CStringArray& aszX, CStringArray& aszY);//Giao cua cac tap hop
	CString  Union(CString szX, CStringArray& aszY);//Giao cua cac tap hop
	CString  Union(CStringArray& aszX, CString szY);//Giao cua cac tap hop
	void     Union(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Hop cua cac tap hop

	CString	 Sub(CString szX, CString szY);//Hieu cua 2 tap hop
	CString  Sub(CStringArray& aszX);//Hieu cua cac tap hop
	CString  Sub(CStringArray& aszX, CStringArray& aszY);//Hieu cua 2 tap hop
	CString  Sub(CString szX, CStringArray& aszY);//Hieu cua 2 tap hop
	CString  Sub(CStringArray& aszX, CString szY);//Hieu cua 2 tap hop
	void     Sub(CUIntArray& aX,CUIntArray& aY,CUIntArray& aZ );//Hieu cua cac tap hop

	//X co chua trong Y hay khong
	//Qui uoc X=Y van co the xem X chua trong Y
	agbool IsInLeast(CString szX, CString szY);//szX co 1 phan tu nam trong szY khong

	agbool IsIn(CString szX, CString szY);//szX co nam trong szY khong
	agbool IsIn(CString szX, CStringArray& aszY,agbool Flag = agtrue);//Flag=FALSE: chi can szX nam trong 1 trong nhung phan tu cua aszY
	agbool IsIn(CStringArray& aszX, CString szY, agbool Flag = agtrue);
	agbool IsIn(CStringArray& aszX, CStringArray& aszY,agbool Flag = agtrue);
	agbool IsInF(CString szX, CStringArray& aszY,int& index);
	agbool IsInF(CStringArray& aszX, CString szY,int& index);
	agbool IsInF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2);

	agbool IsEqual(CString szX, CString szY);//X co bang Y khong
	agbool IsEqual(CString szX, CStringArray& aszY,agbool Flag = agtrue);//Flag=FALSE: chi can szX nam trong 1 trong nhung phan tu cua aszY
	agbool IsEqual(CStringArray& aszX, CString szY,agbool Flag = agtrue);
	agbool IsEqual(CStringArray& aszX, CStringArray& aszY, agbool Flag = TRUE);
	agbool IsEqualF(CString szX, CStringArray& aszY,int& index1,int& index2);
	agbool IsEqualF(CStringArray& aszX, CString szY,int& index1,int& index2);
	agbool IsEqualF(CStringArray& aszX, CStringArray& aszY,int& index1,int& index2);
	agbool IsEqualSpecial(CStringArray& aszX, CStringArray& aszY);

	//Ham tim to hop cua tap szX
	void Combine(CString szX, CString s, int k,CStringArray& aszC);
	void Combine(CStringArray& aszX, CString s, int k,CStringArray& aszC);

	//Ham sap xep
	void Sort(CStringArray& aszX);
	void Sort(CStringArray* aszX);

	//tim min, max
	long Min(CUIntArray& array);
	long Min(CUIntArray* parray);
	long Max(CUIntArray& array);
	long Max(CUIntArray* parray);

	//Ham tim co so toi thieu roi nhau
	//Vao: aszX
	//Ra : aszY
	void Minimum(CStringArray& aszX, CStringArray& aszY );

	//Ham tao toa do cho cac dinh cua do thi sao cho chung deu nhau
	agbool CreatePoint(int xr, int yr, int R,CArray<CPoint,CPoint&>& aPoint );

	//Class CMapStringToString2 new
	class CMapStringToString2: public CMapStringToString
	{
	protected:
		void SetMapStringToString2(CMapStringToString2& map2)
		{
			RemoveAll();
			POSITION	pos=map2.GetStartPosition();
			while(pos!=NULL)
			{
				CString rKey,rValue;
				map2.GetNextAssoc(pos,rKey,rValue);

				SetAt(rKey,rValue);
			}
		}
	public:
		CMapStringToString2():CMapStringToString()
		{
		}
		CMapStringToString2(CMapStringToString2& map2):CMapStringToString()
		{
			SetMapStringToString2(map2);
		}
		virtual ~CMapStringToString2()
		{
		}
		CMapStringToString2&	operator =  (CMapStringToString2& map2)
		{
			SetMapStringToString2(map2);
			return *this;
		}
	};
#endif	//#if (AGMAGIC_SUPPORT_MFC && AGMAGIC_SUPPORT_UTIL_ENHANCED)
};
/**************************class CMemDC************************************************/
#if AGMAGIC_SUPPORT_MFC
#include "../../sys/memdc/memdc.h"
#endif

#endif // !defined(AGUTIL_CORE_H__DEE61245_A429_11D2_84B1_00C0DFF84685__INCLUDED_)
