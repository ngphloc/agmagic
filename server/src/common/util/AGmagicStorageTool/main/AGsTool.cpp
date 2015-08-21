// AGsTool.cpp: implementation of the AGsTool class.
//
//////////////////////////////////////////////////////////////////////

#include "AGsTool.h"

#if AGMAGIC_SUPPORT_MFC
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

#include "../../../../common/include/AGBEGIN_INCLUDE_LIBRARY.h"
#include "../../../../common/lib/agutil/main/AGutilCore.h"
#include "../../../../common/include/AGEND_INCLUDE_LIBRARY.h"

/////////////////////////////////////////////////////////////////////

void privateDeleteSrcFile(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved)
{
#if AGMAGIC_OS_TYPE ==AGMAGIC_WINDOWS_OS
	WIN32_FIND_DATA FileData=*((WIN32_FIND_DATA*)pAtt);
	if(FileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		FileData.dwFileAttributes  &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes((agtchar*)szSrcPath,FileData.dwFileAttributes);
	::DeleteFile((agtchar*)szSrcPath);
#else
	throw _T("Implement not yet");
#endif

	_tprintf(_T("Delete source file: %s\n"), (agtchar*)szSrcPath);
}
void privateCopyFile(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved)
{
#if AGMAGIC_OS_TYPE ==AGMAGIC_WINDOWS_OS
	::CopyFile((agtchar*)szSrcPath,(agtchar*)szDstPath,FALSE);
#else
	throw _T("Implement not yet");
#endif

	_tprintf(_T("Copy %s to %s\n"), (agtchar*)szSrcPath, (agtchar*)szDstPath);
}
void privateCreateDstDir(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved)
{
#if AGMAGIC_OS_TYPE ==AGMAGIC_WINDOWS_OS
	::CreateDirectory((agtchar*)szDstPath,NULL);
#else
	throw _T("Implement not yet");
#endif

	_tprintf(_T("Create destination directory %s\n"), (agtchar*)szDstPath);
}
void privateRemoveSrcDir(void* pAtt, void* szDstPath, void* szSrcPath, void* pReserved)
{
#if AGMAGIC_OS_TYPE ==AGMAGIC_WINDOWS_OS
	::RemoveDirectory((agtchar*)szSrcPath);
#else
	throw _T("Implement not yet");
#endif

	_tprintf(_T("Remove source directory %s\n"), (agtchar*)szSrcPath);
}

/////////////////////////////////////////////////////////////
#include <stdio.h>
void AGsTool(int argc, TCHAR* argv[])
{
	CAGmagicConfUtil::Init();
	agtchar args[][64]=	{	
						_T("AGmagicCreateHeader"),			_T("AGmagicCreateSource"),
						_T("AGmagicCreateHeaderAndBin"),	_T("AGmagicCreateSourceAndBin"),
						_T("AGmagicCopyHeader"),			_T("AGmagicCopySource"),
						_T("AGmagicCopyHeaderAndBin"),		_T("AGmagicCopySourceAndBin"),
						_T("AGmagicSetEnvVar"),
						_T("AGmagicEnv_session_init"),		_T("AGmagicEnv_session_restore")
					};
	agtchar* szBaseDir=CAGmagicConfUtil::AGmagicBaseDirAbsoluteFromBin();
	if(argc==1)
	{
		FILE*		f=NULL;
		agtchar*	command=NULL;
		aguint8		i=0;
		agtchar		filename[64];

	#if AGMAGIC_OS_TYPE==AGMAGIC_WINDOWS_OS
		for(i=0; i<4; i++)
		{
			_stprintf(filename,_T("%s.bat"),args[i]);
			f=_tfopen(filename,_T("w"));

			_fputts(_T("@echo off\n"),f);
			CAGmagicStrUtil::private_tcscat(command,_T("AGmagicStorageTool "),agtrue);
			CAGmagicStrUtil::private_tcscat(command,args[i],agtrue);
			CAGmagicStrUtil::private_tcscat(command,_T(" ."),agtrue);
			_fputts(command,f);
			_fputts(_T("\n@echo on\n"),f);
			fclose(f);

			_tprintf(_T("created %s\n"),filename);
			if(command) free(command);	command=NULL;
		}

		///////////////////////////////////////////////////////////
		for(i=4; i<8; i++)
		{
			_stprintf(filename,_T("%s.bat"),args[i]);
			f=_tfopen(filename,_T("w"));

			_fputts(_T("@echo off\n"),f);
			_fputts(_T("rem AGMAGIC_DEFAULT_PACKED_FILENAME co gia tri la vn.agmagic.server.rar co nghia la chi chep phan server, chep xong se nen\n"),f);
			_fputts(_T("rem AGMAGIC_DEFAULT_PACKED_FILENAME co gia tri la vn.agmagic.rar co nghia la chi chep toan bo phan agmagic, chep xong se nen\n"),f);
			_fputts(_T("rem AGMAGIC_DEFAULT_PACKED_FILENAME co gia tri la vn.agmagic.rar co nghia la chi chep toan bo phan vn, chep xong se nen, tuy nhien phan nay khong nen dung vi goi vn bao gom nhieu thu khac ngoai agmagic\n"),f);
			_fputts(_T("rem Nhu nay AGMAGIC_DEFAULT_PACKED_FILENAME co chua duoi .rar thi chac chan se nen, neu khong chua thi chi chep thu muc\n"),f);
			CAGmagicStrUtil::private_tcscat(command,_T("AGmagicStorageTool "),agtrue);
			CAGmagicStrUtil::private_tcscat(command,args[i],agtrue);
			CAGmagicStrUtil::private_tcscat(command,_T(" . "),agtrue);

			CAGmagicStrUtil::private_tcscat(command,AGMAGIC_DEFAULT_BACKUP_PATH,agtrue);
			CAGmagicStrUtil::private_tcscat(command,_T(" "),agtrue);
			CAGmagicStrUtil::private_tcscat(command,AGMAGIC_DEFAULT_PACKED_FILENAME,agtrue);

			_fputts(command,f);
			_fputts(_T("\n@echo on\n"),f);
			fclose(f);

			_tprintf(_T("created %s\n"),filename);
			if(command) free(command);	command=NULL;
		}

		///////////////////////////////////////////////////////////
		_stprintf(filename,_T("%s.bat"),args[8]);
		f=_tfopen(filename,_T("w"));

		CAGmagicStrUtil::private_tcscat(command,_T("@echo off\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("AGmagicStorageTool "),agtrue);
		CAGmagicStrUtil::private_tcscat(command,args[8],agtrue);
		_fputts(command,f);
		_tprintf(_T("created %s\n"),filename);
		fclose(f);
		if(command) free(command);	command=NULL;

		///////////////////////////////////////////////////////////

		_stprintf(filename,_T("%s.bat"),args[9]);
		f=_tfopen(filename,_T("w"));
		agtchar* szBinPath=CAGmagicConfUtil::AGmagicBinPathAbsolute();
		agtchar* szProUISBinPath=CAGmagicConfUtil::AGmagicProUISBinPathAbsolute();
		agtchar* szCxImageBinPath=CAGmagicConfUtil::AGmagicCxImageBinPathAbsolute();
		CAGmagicStrUtil::private_tcscat(command,_T("set restore_path=%path%\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("set path=%path%;"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,szBinPath,agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("\nset path=%path%;"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,szProUISBinPath,agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("\nset path=%path%;"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,szCxImageBinPath,agtrue);
		_fputts(command,f);
		_tprintf(_T("created %s\n"),filename);
		if(szBinPath)			free(szBinPath);		szBinPath=NULL;
		if(szProUISBinPath)		free(szProUISBinPath);	szProUISBinPath=NULL;
		if(szCxImageBinPath)	free(szCxImageBinPath);	szCxImageBinPath=NULL;
		fclose(f);
		if(command) free(command);	command=NULL;

		///////////////////////////////////////////////////////////
		_stprintf(filename,_T("%s.bat"),args[10]);
		f=_tfopen(filename,_T("w"));
		CAGmagicStrUtil::private_tcscat(command,_T("@echo off\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("if \"%restore_path%\" == \"\" goto end\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("set path=%restore_path%\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("echo %path%\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T(":end\n"),agtrue);
		CAGmagicStrUtil::private_tcscat(command,_T("echo end"),agtrue);
		_fputts(command,f);
		_tprintf(_T("created %s\n"),filename);
		fclose(f);
		if(command) free(command);	command=NULL;

	#else
		#error _T("Implement not yet")
	#endif

		_tprintf(_T("\nPress any thing to close ..."));_gettchar();
		if(command) free(command);	command=NULL;
		return;
	}

	//Ex: szBaseDir=c:\agmagic;
	if(argc > 2)
	{
		if(_tcscmp(argv[2],_T("."))!=0)
		{
			if(szBaseDir)	free(szBaseDir);	szBaseDir=NULL;
			CAGmagicStrUtil::private_tcscat(szBaseDir,argv[2],agtrue);
		}
	}

	agbool bIsRAR=agfalse;//mac dinh se khong nen file
	//xet xem co chep toan bo client va server khong
	if(argc>4)//neu thong so cuoi co
	{
		agtchar* argv4=NULL;
		CAGmagicStrUtil::private_tcscat(argv4,argv[4],agtrue);
		agtchar*		dot=_tcsrchr(argv4,_T('.'));
		if(dot!=NULL)
		{
			if(_tcsicmp(dot+1, _T("rar"))==0)//phan duoi la rar
			{
				bIsRAR=agtrue;
				*dot=0;//cat bo phan .rar
				CAGmagicStrUtil::replace(argv4,_T('.'),AGMAGIC_DIR_SPLASH);
			}
		}

		agtchar*	instr=NULL;
		agtchar*	oldinstr=NULL;
		instr = _tcsstr(szBaseDir,argv4);
		while(instr!=NULL)
		{
			//kiem tra xem hai dau cua instr phai la '.'
			if( 
				( instr==szBaseDir || *(instr-1)==AGMAGIC_DIR_SPLASH ) && 
				( *(instr+_tcslen(argv4))==0 ||  *(instr+_tcslen(argv4))==AGMAGIC_DIR_SPLASH )
			  )
				oldinstr=instr;

			instr=_tcsstr(instr+_tcslen(argv4),argv4);
			if(instr==NULL)//dung la cai cuoi cung
			{
				instr = oldinstr;
				break;
			}
		}
		if(instr!=NULL)
			szBaseDir[(instr+_tcslen(argv4)) - szBaseDir]=0;

		free(argv4);
	}

	agtchar ch;	_tprintf(_T("Are you sure (Y/N) ?: "));	_tscanf(_T("%c"), &ch);
	if(ch!=_T('Y') && ch!=_T('y') )
	{
		if(szBaseDir)	free(szBaseDir);
		return;
	}
	
	if(_tcscmp(argv[1],args[0])==0)
	{
		CAGmagicIOUtil::Browse(NULL,NULL,privateDeleteSrcFile,NULL,szBaseDir,_T("*"),
						NULL,NULL,NULL,AGMAGIC_HEADER_FILEEXT,agfalse);
	}
	else if(_tcscmp(argv[1],args[1])==0)
	{
		agtchar* fileext=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
		CAGmagicIOUtil::Browse(NULL,NULL,privateDeleteSrcFile,NULL,szBaseDir,_T("*"),
						NULL,NULL,CAGmagicConfUtil::AGMAGIC_WASTE_AND_BIN_FILEEXT(fileext),NULL,agfalse);
		free(fileext);
	}
	else if(_tcscmp(argv[1],args[2])==0)
	{
		agtchar* fileext=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
		CAGmagicIOUtil::Browse(NULL,NULL,privateDeleteSrcFile,NULL,szBaseDir,_T("*"),
						NULL,NULL,NULL,CAGmagicConfUtil::AGMAGIC_HEADER_AND_BIN_FILEEXT(fileext),agfalse);
		free(fileext);
	}
	else if(_tcscmp(argv[1],args[3])==0)
	{
		CAGmagicIOUtil::Browse(NULL,NULL,privateDeleteSrcFile,NULL,szBaseDir,_T("*"),
						NULL,NULL,AGMAGIC_WASTE_FILEEXT,NULL,agfalse);
	}
	else if(
			(_tcscmp(argv[1],args[4])==0) ||
			(_tcscmp(argv[1],args[5])==0) ||
			(_tcscmp(argv[1],args[6])==0) ||
			(_tcscmp(argv[1],args[7])==0)
		   )
	{
		agtchar* szDstDir=NULL;
		CAGmagicStrUtil::private_tcscat(szDstDir,argv[3],agtrue);

		agtchar* szTempDir=NULL;
		CAGmagicStrUtil::private_tcscat(szTempDir,szDstDir,agtrue);
		agtchar* pdest=_tcsrchr(szBaseDir,AGMAGIC_DIR_SPLASH);
		if(pdest)
		{
			CAGmagicStrUtil::private_tcscat(szTempDir,AGMAGIC_DIR_SPLASH,agtrue);
			CAGmagicStrUtil::private_tcscat(szTempDir,++pdest,agtrue);
		}
		//::CreateDirectory(szTempDir,NULL);

		agtchar* SampleImagesExcludeDir=CAGmagicConfUtil::AGmagic_GlobalSampleImagesExcludeDir();
		if(_tcscmp(argv[1],args[4])==0)//Header
		{
			CAGmagicIOUtil::Browse(privateCreateDstDir,NULL,privateCopyFile,szTempDir,szBaseDir,_T("*"),
						NULL,
						SampleImagesExcludeDir,
						AGMAGIC_HEADER_FILEEXT,NULL,agtrue);
		}
		else if(_tcscmp(argv[1],args[5])==0)//Header and Lib
		{
			agtchar* fileext=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
			CAGmagicIOUtil::Browse(privateCreateDstDir,NULL,privateCopyFile,szTempDir,szBaseDir,_T("*"),
						NULL,
						SampleImagesExcludeDir,
						NULL,CAGmagicConfUtil::AGMAGIC_WASTE_AND_BIN_FILEEXT(fileext),agtrue);
			free(fileext);
		}
		else if(_tcscmp(argv[1],args[6])==0)
		{
			agtchar* fileext=(agtchar*)malloc(AGMAGIC_MAX_PATH_LENGTH*sizeof(agtchar));
			CAGmagicIOUtil::Browse(privateCreateDstDir,NULL,privateCopyFile,szTempDir,szBaseDir,_T("*"),
						NULL,
						SampleImagesExcludeDir,
						CAGmagicConfUtil::AGMAGIC_HEADER_AND_BIN_FILEEXT(fileext),NULL,agtrue);
			free(fileext);
		}
		else if(_tcscmp(argv[1],args[7])==0)
		{
			CAGmagicIOUtil::Browse(privateCreateDstDir,NULL,privateCopyFile,szTempDir,szBaseDir,_T("*"),
						NULL,
						SampleImagesExcludeDir,
						NULL,AGMAGIC_WASTE_FILEEXT,agtrue);
		}
		else if(_tcscmp(argv[1],args[8])==0)
		{
			CAGmagicIOUtil::Browse(privateCreateDstDir,NULL,privateCopyFile,szTempDir,szBaseDir,_T("*"),
						NULL,
						SampleImagesExcludeDir,
						NULL,AGMAGIC_WASTE_FILEEXT,agtrue);
		}
		if(SampleImagesExcludeDir) free(SampleImagesExcludeDir); SampleImagesExcludeDir=NULL;
		if(bIsRAR)
		{
			agtchar* WinRAR=NULL;
			CAGmagicStrUtil::private_tcscat(WinRAR,AGMAGIC_DEFAULT_PACKAPP_PATH,agtrue);
			CAGmagicStrUtil::private_tcscat(WinRAR,_T(" m -r "),agtrue);
			CAGmagicStrUtil::private_tcscat(WinRAR,argv[4],agtrue);
			CAGmagicStrUtil::private_tcscat(WinRAR,_T(" "),agtrue);
			if(pdest)	CAGmagicStrUtil::private_tcscat(WinRAR,pdest,agtrue);

			/////////////////////////////////////////////////////////
			::SetCurrentDirectory(szDstDir);
			CAGmagicSysUtil::ExecProgram(WinRAR);
			/////////////////////////////////////////////////////////

			CAGmagicIOUtil::Browse(NULL,privateRemoveSrcDir,privateDeleteSrcFile,NULL,szTempDir,_T("*"),
						NULL,NULL,NULL,NULL,agtrue);
			if(WinRAR)		free(WinRAR);
		}
		if(szTempDir)	free(szTempDir);
		if(szDstDir)	free(szDstDir);
	}
	else if(_tcscmp(argv[1],args[8])==0)
	{
		if(szBaseDir)	free(szBaseDir);	szBaseDir=NULL;

		aguint32 reserved;
		agtchar* szEnvPathVar=NULL;
		if(!CAGmagicConfUtil::AGmagicGetEnvPathVar(szEnvPathVar,&reserved))
		{
			_tprintf(_T("Set environment path variable fail"));
			return;
		}

		agbool	 bShouldRestartOS=agfalse;
		agtchar* szBinPath=CAGmagicConfUtil::AGmagicBinPathAbsolute();
		agtchar* szProUISBinPath=CAGmagicConfUtil::AGmagicProUISBinPathAbsolute();
		agtchar* szCxImageBinPath=CAGmagicConfUtil::AGmagicCxImageBinPathAbsolute();
		if(szEnvPathVar==NULL || _tcsstr(szEnvPathVar,szBinPath)==NULL)
		{
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,_T(";"),agtrue);
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,szBinPath,agtrue);
			bShouldRestartOS=bShouldRestartOS || agtrue;
		}
		if(szEnvPathVar==NULL || _tcsstr(szEnvPathVar,szProUISBinPath)==NULL)
		{
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,_T(";"),agtrue);
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,szProUISBinPath,agtrue);
			bShouldRestartOS=bShouldRestartOS || agtrue;
		}
		if(szEnvPathVar==NULL || _tcsstr(szEnvPathVar,szCxImageBinPath)==NULL)
		{
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,_T(";"),agtrue);
			CAGmagicStrUtil::private_tcscat(szEnvPathVar,szCxImageBinPath,agtrue);
			bShouldRestartOS=bShouldRestartOS || agtrue;
		}
		if(szBinPath)			free(szBinPath);
		if(szProUISBinPath)		free(szProUISBinPath);
		if(szCxImageBinPath)	free(szCxImageBinPath);
		if(szEnvPathVar && bShouldRestartOS)
		{
			if(!CAGmagicConfUtil::AGmagicSetEnvPathVar(szEnvPathVar,&reserved))
			{
				_tprintf(_T("Set environment path variable fail"));
				free(szEnvPathVar);
				return;
			}
		}
		if(szEnvPathVar)
		{
			_tprintf(_T("Set environment path variable successfully. PATH = %s\n"), szEnvPathVar);
			free(szEnvPathVar);

			if(bShouldRestartOS)
			{
				agtchar ch;	_tprintf(_T("You should restart your computer (Y/N) ?: "));	
				_tscanf(_T("%c"), &ch);	_tscanf(_T("%c"), &ch);
				if(ch==_T('Y') || ch==_T('y') )	
				{
					CAGmagicSysUtil::ExitOS(AGMAGIC_OS_REBOOT);
					//CAGmagicSysUtil::ExitOSShowOption();
				}
			}
		}
	}
	if(szBaseDir)	free(szBaseDir);
	_tprintf(_T("\nPress any thing to close ..."));_gettchar();
}

