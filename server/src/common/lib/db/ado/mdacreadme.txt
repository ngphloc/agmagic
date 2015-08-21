---------------------------------------------------------
Microsoft Data Access Components version 2.1 Readme File
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft Data Access Components (MDAC) documentation.

------------------------
1. MDAC TECHNICAL NOTES
------------------------

MDAC Release Notes

This file, MDACReadme.txt, contains technical notes, information on bugs and workarounds, and information too late to include in the documentation for the Microsoft Data Access Components. 

The release notes for each of the Microsoft Data Access Components can be found in the following locations:
*  ADO and RDS 2.1
     <drive>:\Program files\Common files\System\ADO\ADOreadme.txt
*  ADO MD
     <drive>:\Program files\Common files\System\ADO\ADOMDreadme.txt
*  ADOX
     <drive>:\Program files\Common files\System\ADO\ADOXreadme.txt
*  JRO
     <drive>:\Program files\Common files\System\ADO\JROreadme.txt
*  OLE DB Provider for ODBC
     <drive>:\Program files\Common files\System\OLE DB\MSDASQLreadme.txt
*  SQL ODBC Driver
     <drive>:\<windir>\<system>\SQLSRdMe.txt
*  SQL OLE DB Provider
     <drive>:\Program files\Common files\System\OLE DB\SQLOLEDB.txt
*  Oracle ODBC Driver
     <drive>:\<windir>\<system>\MsOracle32Readme.txt
*  Oracle OLE DB Provider
     <drive>:\Program files\Common files\System\OLE DB\MSOrclOLEDBreadme.txt
*  Visual FoxPro ODBC Driver
     <drive>:\<windir>\<system>\Vfpodbc.txt
*  OLE DB Service Components
     <drive>:\Program files\Common files\System\OLE DB\Msdasc.txt

---------------------------------------------------
2. MDAC KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS
---------------------------------------------------
2.1 When using ADSI 2.0 with MDAC 2.1, ADSI will disable its ADO functionality. Other features of ADSI will continue to work. MDAC 2.1 does not affect accessing ADSI via ADSI Interfaces.

For example, opening an ADO Connection object in ADSI will fail when MDAC 2.1 is installed.

Con.Provider = "ADsDSOObject"
Con.Open "Active Directory Srv Interface" <= This line fails

ADSI will be posted a resolution to this problem on http://www.microsoft.com/adsi 

2.2 On Windows 95, if you install MDAC from a UNC, you receive an error. This error does not occur if you map a drive instead of using the UNC, even if the drive is not persistent. 

2.3 The MDAC 2.1 redist is not supported on Terminal Server.

2.4 If you install MDAC 2.1 on a computer running applications that access SQL Server 6.5 through the OLE DB Provider for SQL Server or the SQL Server ODBC Driver, and if the catalog stored procedures installed on that SQL Server 6.5 are not current, the provider or driver will generate the following warning message:

OLE DB Provider for SQL Server:
The catalog stored procedures installed on server <server_name> are version <version#>; version <version#> or later is required to support IDBSchemaRowset.  Please contact your system administrator.

SQL Server ODBC Driver:
The ODBC catalog stored procedures installed on server <server_name> are version <version#>; version <version#> or later is required to ensure proper operation.  Please contact your system administrator.

If an application ignores this message, it may experience some problems (such as loss of schema information).

To correct this:
* You must install instcat.sql that comes with MDAC 2.1 on the 6.5 server
- or -
* Install SQL Server 6.5 SP5 on the server. Installing SQL Server 6.5 SP5 automatically runs instcat.sql.

-----------------------------------------------------
3. MDAC FILELIST AND FILE INFORMATION
-----------------------------------------------------

This section lists the files installed by Microsoft Data Access Components 2.1 SP1 Setup.  It contains information on file versions, descriptions, and install locations.
    
    
	  Filename       	Version      	InstallLocation                         	Description

	  ADO
	-----------
	  ADOReadme.txt  	             	\Program Files\Common Files\System\ADO  	Release Notes for ADO
	  adoapt15.reg   	             	\Program Files\Common Files\System\ADO  	Apartment Thread Model batch file
	  adofre15.reg   	             	\Program Files\Common Files\System\ADO  	Free Thread Model batch file
	  adojavas.inc   	             	\Program Files\Common Files\System\ADO  	JavaScript Include file for ADO
	  adovbs.inc     	             	\Program Files\Common Files\System\ADO  	VBScript Include file for ADO
	  makapt15.bat   	             	\Program Files\Common Files\System\ADO  	Apartment Thread Model batch file
	  makfre15.bat   	             	\Program Files\Common Files\System\ADO  	Free Thread Model batch file
	  msader15.dll   	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Error String Library
	  msado15.dll    	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Library
	  msado20.tlb    	             	\Program Files\Common Files\System\ADO  	ADO Type-Library
	  msador15.dll   	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Resource Library
	  msadrh15.dll   	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Rowset Helper

	  ADOMD
	-----------
	  ADOMDReadme.txt	             	\Program Files\Common Files\System\ADO  	Release Notes for ADOMD
	  msadomd.dll    	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Multi-Dimensional Library

	  ADOX
	-----------
	  ADOXReadme.txt 	             	\Program Files\Common Files\System\ADO  	ADOX Release Notes
	  msadox.dll     	2.10.3711.0  	\Program Files\Common Files\System\ADO  	ADO Extensions Library

	  JRO
	-----------
	  JROreadme.txt  	             	\Program Files\Common Files\System\ADO  	Release Notes for JRO
	  msjro.dll      	2.10.3711.0  	\Program Files\Common Files\System\ADO  	Jet Replication Objects Library

	  Jet98
	-----------
	  expsrv.dll     	6.0.0.8268   	<system directory>                      	VBA Expression Service
	  msexch40.dll   	4.0.2510.0   	<system directory>                      	Exchange IISAM
	  msexcl40.dll   	4.0.2510.0   	<system directory>                      	Excel IISAM
	  msjet40.dll    	4.0.2510.0   	<system directory>                      	Jet Engine
	  msjetoledb40.dll	4.0.2510.0   	<system directory>                      	OLE DB Provider for Jet
	  msjint40.dll   	4.0.2510.0   	<system directory>                      	Jet International Library
	  msjter40.dll   	4.0.2510.0   	<system directory>                      	Jet Error Library
	  msjtes40.dll   	4.0.2510.0   	<system directory>                      	Jet 4.0 Expression Service
	  msltus40.dll   	4.0.2510.0   	<system directory>                      	Lotus IISAM
	  mspbde40.dll   	4.0.2510.0   	<system directory>                      	Paradox IISAM
	  msrclr40.dll   	4.0.2510.0   	<system directory>                      	Replication Reconciler
	  msrd2x40.dll   	4.0.2510.0   	<system directory>                      	ISAM for Jet 2.0 Databases
	  msrd3x40.dll   	4.0.2510.0   	<system directory>                      	ISAM for Jet 3.0 Databases
	  msrecr40.dll   	4.0.2510.0   	<system directory>                      	Replication Reconciler Resource Library
	  msrepl40.dll   	4.0.2510.0   	<system directory>                      	Replication Library
	  mstext40.dll   	4.0.2510.0   	<system directory>                      	Text IISAM
	  mswdat10.dll   	4.0.2510.0   	<system directory>                      	Jet Sorting Data Library
	  mswstr10.dll   	4.0.2510.0   	<system directory>                      	Jet Sorting Library
	  msxbde40.dll   	4.0.2510.0   	<system directory>                      	dBase IISAM
	  vbajet32.dll   	6.0.1.8268   	<system directory>                      	VBA Expression Service Loader

	  JetODBC
	-----------
	  odbcjet.cnt    	             	<system directory>                      	Jet ODBC Help Contents
	  odbcjet.hlp    	             	<system directory>                      	Jet ODBC Help
	  odbcji32.dll   	4.0.3711.0   	<system directory>                      	ODBC Driver for Desktop Databases Resource Library
	  odbcjt32.dll   	4.0.3711.0   	<system directory>                      	ODBC Driver for Desktop Databases
	  oddbse32.dll   	4.0.3711.0   	<system directory>                      	Installable dBase IISAM
	  odexl32.dll    	4.0.3711.0   	<system directory>                      	Installable Excel IISAM
	  odfox32.dll    	4.0.3711.0   	<system directory>                      	Installable FoxPro IISAM
	  odpdx32.dll    	4.0.3711.0   	<system directory>                      	Installable Paradox IISAM
	  odtext32.dll   	4.0.3711.0   	<system directory>                      	Installable Text IISAM

	  MTxOCI
	-----------
	  mtxoci.dll     	1998.2.715.0 	<system directory>                      	Oracle Database support Library

	  ODBC
	-----------
	  ds16gt.dll     	3.510.3711.0 	<system directory>                      	ODBC 16-bit driver setup generic thunking
	  ds32gt.dll     	3.510.3711.0 	<system directory>                      	ODBC 32-bit driver setup generic thunking
	  mtxdm.dll      	1997.11.532.0	<system directory>                      	ODBC Connection Pooling Manager
	  odbc16gt.dll   	3.510.3711.0 	<system directory>                      	ODBC 16-bit generic thunking
	  odbc32.dll     	3.510.3711.0 	<system directory>                      	ODBC Driver Manager
	  odbc32gt.dll   	3.510.3711.0 	<system directory>                      	ODBC 32-bit generic thunking
	  odbcad32.exe   	3.510.3711.0 	<system directory>                      	ODBC Administrator Executable
	  odbccp32.cpl   	3.510.3711.0 	<system directory>                      	ODBC Control Panel Applet
	  odbccp32.dll   	3.510.3711.0 	<system directory>                      	ODBC Control Panel Library
	  odbccr32.dll   	3.510.3711.0 	<system directory>                      	ODBC ANSI Cursor Library
	  odbccu32.dll   	3.510.3711.0 	<system directory>                      	ODBC Unicode Cursor Library
	  odbcinst.cnt   	             	<system directory>                      	ODBC Installer Help Contents
	  odbcinst.hlp   	             	<system directory>                      	ODBC Installer Help
	  odbcint.dll    	3.510.3711.0 	<system directory>                      	ODBC 16-bit Installer
	  odbctrac.dll   	3.510.3711.0 	<system directory>                      	ODBC Tracing Library

	  OLEDB
	-----------
	  MSDASQLreadme.txt	             	\Program Files\Common Files\System\OLE DB	OLE DB Provider for ODBC Release Notes
	  msdadc.dll     	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Data Conversion Library
	  msdaenum.dll   	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Services Enumerator
	  msdaer.dll     	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Errors Object
	  msdaosp.dll    	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Simple Provider
	  msdaps.dll     	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Interface Remote
	  msdasc.cnt     	             	\Program Files\Common Files\System\OLE DB	OLE DB Service Components Help Contents
	  msdasc.dll     	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Service Components Library
	  msdasc.hlp     	             	\Program Files\Common Files\System\OLE DB	OLE DB Service Components Help
	  msdasc.txt     	             	\Program Files\Common Files\System\OLE DB	Release Notes for OLE DB Service Components
	  msdasql.dll    	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Provider for ODBC
	  msdasqlr.dll   	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Provider for ODBC Resource Library
	  msdatl2.dll    	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Tools Library
	  msdatt.dll     	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Temporary Table Service Provider
	  msxactps.dll   	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Transactions Proxies / Stubs
	  oledb32.dll    	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Core Services Library
	  oledb32r.dll   	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Resource Library
	  oledb32x.dll   	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Extensions Library

	  Oracle ODBC
	-----------
	  MSOracle32Readme.txt	             	<system directory>                      	Oracle ODBC Driver Release Notes
	  mscpxl32.dll   	3.60.3.20    	<system directory>                      	ANSI Codepage Translator
	  msorcl32.cnt   	             	<system directory>                      	Oracle ODBC Help Contents
	  msorcl32.dll   	2.573.3711.0 	<system directory>                      	Oracle ODBC Driver
	  msorcl32.hlp   	             	<system directory>                      	Oracle ODBC Help

	  Oracle OLEDB
	-----------
	  MSOrclOLEDBreadme.txt	             	\Program Files\Common Files\System\OLE DB	Oracle OLE DB Provider Release Notes
	  msdaora.dll    	2.10.3711.0  	\Program Files\Common Files\System\OLE DB	OLE DB Provider for Oracle

	  RDS
	-----------
	  HANDLER.reg    	             	\Program Files\Common Files\System\MSADC	Register and Include file
	  adcjavas.inc   	             	\Program Files\Common Files\System\MSADC	JavaScript Include file for RDS/ADC
	  adcvbs.inc     	             	\Program Files\Common Files\System\MSADC	VBScript Include file for RDS/ADC
	  handsafe.reg   	             	\Program Files\Common Files\System\MSADC	Handler settings for safe mode/restricted access
	  handunsf.reg   	             	\Program Files\Common Files\System\MSADC	Handler settings for unrestricted access
	  msadce.dll     	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Client-Side Cursor Engine
	  msadcer.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Client-Side Cursor Engine Resource Library
	  msadcf.dll     	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Data-Factory Object
	  msadcfr.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Data-Factory Object Resource Library
	  msadco.dll     	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Databinding HTML Control
	  msadcor.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Databinding HTML Control Resource Library
	  msadcs.dll     	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS ISAPI Library
	  msadds.dll     	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS DataShape Provider
	  msaddsr.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS DataShape Provider Resource Library
	  msdaprsr.dll   	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Proxies / Stubs Resource Library
	  msdaprst.dll   	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Proxies / Stubs Library
	  msdarem.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Remoting
	  msdaremr.dll   	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Remoting Resource Library
	  msdatsrc.tlb   	             	<system directory>                      	RDS DataBinding Type-Library
	  msdfmap.dll    	2.10.3711.0  	\Program Files\Common Files\System\MSADC	RDS Data-Factory Handler Core
	  msdfmap.ini    	             	<windows directory>                     	RDS Data-Factory Handler Core INI file

	  SQL Server ODBC
	-----------
	  12520437.cpx   	             	<system directory>                      	Translation Code Page
	  12520850.cpx   	             	<system directory>                      	Translation Code Page
	  Sqlsrdme.txt   	             	<system directory>                      	SQL Server ODBC Driver Release Notes
	  cliconf.hlp    	             	<system directory>                      	SQL Server Client Configuration Help file
	  cliconfg.DLL   	1998.11.13.0 	<system directory>                      	SQL Server Client Configuration Library
	  cliconfg.exe   	1998.11.13.0 	<system directory>                      	SQL Server Client Configuration Executable
	  odbcbcp.dll    	3.70.6.23    	<system directory>                      	SQL Server BCP Library
	  sqlsodbc.hlp   	             	<system directory>                      	SQL Server ODBC Help
	  sqlsrv32.dll   	3.70.6.23    	<system directory>                      	SQL Server ODBC Driver
	  sqlstr.dll     	1998.11.13.0 	<system directory>                      	SQL Server String Function Library
	  sqlwid.dll     	1998.11.13.0 	<system directory>                      	SQL Server UNICODE Function Library
	  sqlwoa.dll     	1998.11.13.0 	<system directory>                      	SQL Server ANSI / UNICODE Function Library

	  SQL Server OLEDB
	-----------
	  SQLOLEDB.txt   	             	\Program Files\Common Files\System\OLE DB	SQL Server OLEDB Provider Release Notes
	  SQLSOLDB.hlp   	             	\Program Files\Common Files\System\OLE DB	SQL Server OLEDB Help
	  dbmsadsn.dll   	1998.11.13.0 	<system directory>                      	SQL Server AppleTalk Net-Library
	  dbmsrpcn.dll   	1998.11.13.0 	<system directory>                      	SQL Server RPC Net-Library
	  dbmsshrn.dll   	1998.11.13.0 	<system directory>                      	SQL Server Shared-Memory Net-Library
	  dbmssocn.dll   	1998.11.13.0 	<system directory>                      	SQL Server TCP/IP Sockets Net-Library
	  dbmsspxn.dll   	1998.11.13.0 	<system directory>                      	SQL Server SPX Net-Library
	  dbmsvinn.dll   	1998.11.13.0 	<system directory>                      	SQL Server Vines Networking Net-Library
	  dbnmpntw.dll   	1998.11.13.0 	<system directory>                      	SQL Server Named Pipes Net-Library
	  instcat.sql    	             	<system directory>                      	Updated System Stored Procedure Catalog
	  sqloledb.dll   	7.1.6.23     	\Program Files\Common Files\System\OLE DB	SQL Server OLEDB Provider

	  Setup
	-----------
	  common98.dll   	             	<system directory>                      	Setup Library
	  odbcconf.exe   	             	<system directory>                      	Setup Library
	  odbckey.inf    	             	<system directory>                      	Setup Library
	  odbcstf.dll    	             	<system directory>                      	Setup Library
	  qfeupd.exe     	             	<system directory>                      	Setup Executable

	  System
	-----------
	  asycfilt.dll   	2.40.4268.1  	<system directory>                      	OLE Automation System Library
	  msvcirt.dll    	5.0.0.7022   	<system directory>                      	Microsoft C-Runtime Library
	  msvcrt.dll     	5.0.0.7128   	<system directory>                      	Microsoft C-Runtime Library
	  oleaut32.dll   	2.40.4268.1  	<system directory>                      	OLE Automation System Library
	  olepro32.dll   	5.0.4268.1   	<system directory>                      	OLE Automation System Library
	  stdole2.tlb    	2.40.4268.1  	<system directory>                      	OLE Automation System Library

	  Visual FoxPro
	-----------
	  drvvfp.cnt     	             	<system directory>                      	Visual FoxPro ODBC Driver Help Contents
	  drvvfp.hlp     	             	<system directory>                      	Visual FoxPro ODBC Driver Help
	  vfpodbc.dll    	6.0.8352.0   	<system directory>                      	Visual FoxPro ODBC Driver
	  vfpodbc.txt    	             	<system directory>                      	VFPODBC Release Notes


