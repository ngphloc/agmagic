---------------------------------------------------------
Microsoft(R) ActiveX(R) Data Objects version 2.1 Readme File
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft ADO documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   
2. NEW FEATURES
2.1 Seek and Index
2.2 Row updates and synchronization
2.3 Microsoft OLE DB Persistence Provider
2.4 Microsoft Data Shaping Service for OLE DB
2.5 Microsoft OLE DB Remoting Provider

3. TECHNICAL NOTES
3.1 Security Enhancements
3.2 Restrictive Behavior
3.3 Customizing Security Settings

4. KNOWN BUGS, LIMITATIONS, WORKAROUNDS, AND LATE-BREAKING DOCUMENTATION NOTES

----------------------
1. PRODUCT DESCRIPTION
----------------------

ActiveX Data Objects (ADO) is an Automation-based interface for accessing data. ADO uses the OLE DB interface to access a broad range of data sources, including but not limited to data provided via ODBC.

Users of RDO and DAO should quickly become comfortable with programming to ADO because the overall design of ADO comes from our experience in developing those interfaces.

Microsoft Remote Data Service (RDS) is a component of ADO that provides fast and efficient data connectivity and the data publishing framework for applications hosted in Microsoft Internet Explorer. It is based on a client/server, distributed technology that works over HTTP, HTTPS (HTTP over Secure Sockets layer), and DCOM application protocols. Using data-aware ActiveX controls, RDS provides data access programming in the style of Microsoft Visual Basic(R) to Web developers who need to build distributed, data-intensive applications for use over corporate intranets and the Internet.

---------------
2. NEW FEATURES
---------------

ADO 2.1 adds several new features for developers.

2.1 Seek and Index
The Seek method and Index property add fast, index-based location of rows in a recordset.

2.2 Row updates and synchronization
The new "row fix-up" mode offers the user custom control of row updates and synchronization for recordsets created by a JOIN operation. Seven new dynamic properties control the behavior of five existing methods.

2.3 Microsoft OLE DB Persistence Provider
The Microsoft OLE DB Persistence Provider, in conjunction with the Recordset object's Save and Open methods, saves and restores a recordset to a file. With this release, a recordset can be saved in Extensible Markup Language (XML) format, the standard means of defining user-specified tags for data transported across the Internet.

2.4 Microsoft Data Shaping Service for OLE DB
The Microsoft Data Shaping Service for OLE DB, which supports Data Shaping, can now:

2.4.1 Re-shape a previously shaped recordset. To support this feature, recordsets now have a Name property that exists for the duration of the connection.

2.4.2 Perform aggregate calculations on a column at any level of a shaped recordset, not just the immediate child of the parent. This feature uses fully qualified chapter names to form a path to the desired level and column.

2.4.3 Parameterized COMPUTE commands can have an arbitrary number of intervening COMPUTE clauses between the PARAMETER clause and parameter argument.

2.5 Microsoft OLE DB Remoting Provider
The Microsoft OLE DB Remoting Provider becomes a standard service provider and acquires new dynamic properties for enhanced performance, greater user control, and backwards compatibility with ADO 2.0.


------------------
3. TECHNICAL NOTES
------------------

3.1 Security Enhancements

This release includes security enhancements for ADO and RDS objects so that some of the operations are restricted when Internet Explorer is running in a "safe" mode.

3.1.1. Zones
You can set different security settings for different "zones" in Internet Explorer 4.0 to customize the behavior of ADO/RDS objects in those zones. The following four zones are defined in Internet Explorer 4.0:
*  Internet zone
*  Local intranet zone
*  Restricted sites zone
*  Trusted sites zone

3.1.2. Security Levels
For each of these zones, you can specify the security level to use. The following security levels are available for each zone:
*  High
*  Medium
*  Low
*  Custom

Like any other ActiveX controls, in order for ADO/RDS objects to work at all in Internet Explorer 4.0, the security level must be set to "Medium" or "High." Custom settings are used to set ADO/RDS objects to behave in safe or unsafe mode.

3.2 Restrictive Behavior

By default, any unsafe operations on ADO/RDS objects in Internet Explorer 4.0 will result in a user prompt when accessing pages from "Local trusted zone," "Trusted sites zone," and "Internet zone." Unsafe operations on ADO/RDS objects are disabled, by default, for pages loaded from "Restricted sites zone." The following describes ADO/RDS behavior when running in these modes:

3.2.1 Safe Objects
The following objects are considered "safe." This means that unsafe operations (detailed in 3.2.3) are disallowed in a safe environment (e.g., Internet Explorer, by default; unless custom settings are used to run in an unsafe mode) and allowed in an unsafe environment (e.g., Visual Basic).
a. RDS.DataControl object
b. RDS.DataSpace object
c. ADO Recordset object

3.2.2 Unsafe Objects
The following objects are considered "unsafe." They cannot be created directly or indirectly (and given to a user) when operating in a safe environment.
a. RDSServer.DataFactory object
b. ADO Connection object
c. ADO Command object

3.2.3 Unsafe Operations on Safe Objects
The following are considered unsafe operations on the "safe" objects -- RDS.DataControl, RDS.DataSpace, ADO Recordset. These operations are disallowed in a safe environment but allowed in an unsafe environment.

a. RDS.DataControl
i) All two-tier and DCOM scenarios on the RDS.DataControl object. This means that you cannot open database connections on your local machine or from servers to which you connect using the DCOM protocol.
ii) All three-tier operations over HTTP are restricted to the server from which the page has been downloaded. This means that the Server property on the RDS.DataControl object must be equal to the host name (http://server) from which the page has been downloaded.

b. RDS.DataSpace
i) All two-tier and DCOM scenarios on the RDS.DataSpace object. This means that you cannot use the RDS.DataSpace object to invoke business objects on your local machine or over the DCOM protocol.
ii) All three-tier scenarios over HTTP are restricted to the server from which the page has been downloaded. This means that the second parameter in the CreateObject method call on the DataSpace object must point to the same server from which the page has been downloaded.

c. ADO Recordset
i) Making any connection where provider is not MS Remote. So the connection string must start with "Provider=MS Remote". The "Remote Server" tag in the connection string must also be the same name as the server from which the page has been downloaded. Local two-tier and DCOM connections are not allowed.
ii) Local Persistence operations, like saving a recordset to the local filesystem and opening a recordset from file on the local machine.

3.3 Customizing Security Settings

ADO/RDS behavior is controlled by the setting for the "Initialize and script ActiveX controls not marked as safe" option. You can change the security settings by changing the security level for a specific zone. Default settings for the "Initialize and script ActiveX controls not marked as safe" option for the intranet zone are as follows:
Security level = High		Value = "Disable"
Security level = Medium		Value = "Disable"
Security Level = Low		Value = "Prompt"

For default settings in other security zones, please refer to the documentation for Internet Explorer.

By changing the security level, you can change the behavior of disconnected ADO Recordset objects running in the browser. If you want to enable unsafe operations and do not want to be prompted every time such an operation is attempted, then you must explicitly set the value for the above option to "Enable." Please also note that if you attempt an unsafe operation (such as saving a Recordset to a file in the local filesystem) on an ADO Recordset obtained from the RDS.DataControl, then you must set the value for the above option to "Enable." The setting of "Prompt" acts like "Disable" for such Recordset objects (obtained from the RDS.Datacontrol).

You can override the default settings by directly manipulating the custom settings for the above option. You can choose to completely disable the unsafe operations (described above), or specify that a warning be displayed whenever such an operation is attempted, or enable such an operation without any warning. You can set different custom settings for different security zones. The following steps must be taken to customize your security settings for a specific security zone:

CAUTION: Please be aware that by enabling "Initialize and script ActiveX controls not marked as safe" (step 5 below), you are allowing ANY ActiveX control, safe or unsafe, to be used from within Web pages (which potentially exposes user machines to malicious controls or malicious scripting code). It is recommended that you should do this only in the "intranet" or "Trusted Sites" Security Zones and not on the "Internet" zone.

1. From the View menu in Internet Explorer 4.0, select Internet Options to bring up the Internet Options dialog box. Select the Security tab.
2. From the Zone drop-down list, select the zone that you want to customize settings for.
3. Select Custom for the selected zone. This enables the Settings button on the dialog box.
4. Click Settings to bring up the Security Settings dialog box.
5. If you want to enable unsafe operations (described in 3.2.3) on ADO/RDS objects without any warning being displayed, select "Enable" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
6. If you want a warning to be displayed whenever an unsafe operation (described in 3.2.3) on ADO/RDS objects is attempted, select "Prompt" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
7. If you want to completely disable unsafe operations (described in 3.2.3) on ADO/RDS objects, select "Disable" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
8. If appropriate, repeat these steps to customize the security settings for other security zones.
9. Click OK.

Now ADO/RDS objects will behave in specified custom mode. These settings affect the following behavior of ADO/RDS objects (as described in 3.2.3) in the specified security zone -- opening local two-tier connections; working over DCOM; connecting to a server other than the one from which the page was originally downloaded; saving and opening a recordset to/from files on the local machine.

If you set your custom options to "Prompt", the following warning is displayed when an unsafe operation is attempted on ADO/RDS objects:

"The page is accessing a data source on another domain. Do you want to allow this?" The user has the option of replying "Yes" or "No". If the reply is "Yes", the operation is completed; otherwise it fails.

--------------------------------------------------
4. KNOWN BUGS, LIMITATIONS, WORKAROUNDS, AND LATE-BREAKING DOCUMENTATION NOTES
--------------------------------------------------

4.1 Client impersonation in RDS is not currently supported due to missing support from the operating system.

4.2 When creating "Virtual Servers" in Internet Information Server 4.0, the following two extra steps are needed in order to configure the server to work with RDS:

A) When setting up the server, check "Allow Execute Access."
B) Move msadcs.dll to vroot\msadc, where vroot is the home directory of your virtual server.

4.3 When using RDS on an IIS server, the number of threads created per processor can be controlled by manipulating the registry on the Web server.  The number of threads per processor can affect performance in a high traffic situation, or in low traffic but large query size scenarios. The user should experiment for best results. The specific value to be adjusted is:

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W3SVC\Parameters\ADCThreads

where ADCThreads is a user-added REG_DWORD. The range of valid values is 1 to 50. The default value is 6. If the value specified by the registry key is greater than 50, then the maximum value is used (50). The user should not need to create this registry value; it is not included in the registry by default.

4.4 By default, ADO is installed with a "safe" RDS Server DataFactory configuration. Safe mode for RDS Server components means that following are true:

	1. Handler is required with the DataFactory 
	   (this is mandated by a registry key setting)

	2. Our default handler, msdfmap.handler, is registered, present 
	   in the safe-handler list, and marked as the default handler.

	3. Msdfmap.ini file is installed in the Windows directory. You 
	   must configure this file according to your needs, before using 
	   RDS in three-tier mode.

Optionally, you can configure an unrestricted DataFactory installation. DataFactory can be used 
directly without the custom handler. Users can still use a custom handler by modifying the connection strings, but it is not required.

We have provided the registry file handsafe.reg to setup the handler registry entries for a safe configuration.
To run in safe mode, run handsafe.reg. 

We have provided the registry file handunsf.reg to setup the handler registry entries for a unrestricted configuration. To run in unrestricted mode, run handunsf.reg.

For more information about using the Customization Handler feature of RDS, see the technical article "Using the Customization Handler Feature in RDS 2.0," available at http://www.microsoft.com/data/techmat.htm

4.5 The Find method searches a Recordset in the specified direction from the current row position for the record that satisfies the specified criteria. If no current row position has been set before calling Find, an error occurs.

4.6 In order to use ADO FetchProgress and FetchComplete Events with Visual Basic, at least Visual Basic version 6 is required.

4.7 The following operations are considered "safe" to use in Data Shaping CALC expressions:

Abs, Asc, Atn, CBool, CByte, CCur, CDate, CDbl, Chr, ChrB, ChrW, Chr$, ChrB$, CInt, CLng, Cos, CSng, CStr, Cvar, CVDate, CVErr, Date, Date$, DateAdd, DateDiff, DatePart, DateSerial, DateValue, Day, DDB, Error, Error$, Exp, Fix, Format, Format$, FV, Hex, Hex$, Hour, IIF, InStr, Int, IPmt, IRR, IsDate, IsEmpty, IsError, IsNull, IsNumeric, IsObject, LCase, LCase$, Left, LeftB, Left$, LeftB$, Len, Log, LTrim, LTrim$, Mid, Mid$, Minute, MIRR, Month, Now, NPer, NPV, Oct, Oct$, Pmt, PPmt, PV, QBColor, Rate, RGB, Right, RightB, Right$, RightB$, Rnd, RTrim, RTrim$, Second, Sgn, Sin, SLN, Space, Space$, Sqr, Str, Str$, StrComp, StrConv, String, String$, SYD, Tan, Time,Time$, Timer, TimeSerial, TimeValue, Trim, Trim$, TypeName, UCase, UCase$, Val, VarType , Weekday, Year

4.8 ADO 2.1 does not support persisting hierarchical Recordset objects in XML format. 

4.9  You cannot update the data in a read-only Recordset by saving the data to XML and editing the XML file. An error will occur when you attempt to reopen the Recordset from the XML file if the XML data has been changed.

4.10 When using adUseClient or remoting against SQL Server 6.5 Service Pack 4, using the DISTINCT keyword in queries will be ignored for updatable result sets. This is a SQL Server issue and should be resolved in a future service pack.

4.11 The DataTypeEnum values listed in the Type Property topic in the ActiveX Data Objects Programmer's Reference contain errors. The following enum values are listed but do not exist and cannot be used:

adArray, adByRef, adVector

The following values are missing from the list but do exist and can be used:

adChapter     A 4-byte chapter value used to identify rows in a child rowset (DBTYPE_HCHAPTER).

adDBFileTime  A file time value (DBTYPE_DBFILETIME).

adFileTime    A 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (DBTYPE_FILETIME).

adPropVariant An Automation PROPVARIANT (DBTYPE_PROP_VARIANT).

adVarNumeric  A numeric value (Parameter object only).

4.12 The list of valid values for the Options parameter of the Execute method of Connection and Command objects contains errors. The following ExecuteOptionEnum value is incorrectly listed twice. It should be listed once as such:

adCmdTable    Indicates that ADO should evaluate CommandText as a table name and generate an SQL query to return all rows from the table named in CommandText.

The following CommandTypeEnum value is missing from the list but does exist and can be used:

adCmdFile     Indicates that the provider should evaluate CommandText as a file name.

The following ExecuteOptionEnum values are missing from the list but do exist and can be used:

adAsyncFetchNonBlocking   Indicates that the main thread never blocks while fetching. If the requested row has not been fetched, the current row automatically moves to the end of the file.

adExecuteNoRecords        Indicates CommandText is a command or stored procedure that does not return rows (for example, a command that only inserts data). If any rows are retrieved, they are discarded and not returned. Always combined with adCmdText or adCmdStoredProc. 

4.13 The list of QueryType Enum values for the OpenSchema method of a Connection object contains errors. The following values are missing from the list but do exist and can be used:

Enum			Restriction Columns

adSchemaDBInfoKeywords	none

adSchemaDBInfoLiterals	none

adSchemaCubes		CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME

adSchemaDimensions	CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			DIMENSION_NAME
			DIMENSION_UNIQUE_NAME

adSchemaHierarchies	CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			DIMENSION_UNIQUE_NAME
			HIERARCHY_NAME
			HIERARCHY_UNIQUE_NAME

adSchemaLevels		CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			DIMENSION_UNIQUE_NAME
			HIERARCHY_UNIQUE_NAME
			LEVEL_NAME
			LEVEL_UNIQUE_NAME

adSchemaMeasures	CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			MEASURE_NAME
			MEASURE_UNIQUE_NAME

adSchemaProperties	CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			DIMENSION_UNIQUE_NAME
			HIERARCHY_UNIQUE_NAME
			LEVEL_UNIQUE_NAME
			MEMBER_UNIQUE_NAME
			PROPERTY_TYPE
			PROPERTY_NAME

adSchemaMembers		CATALOG_NAME
			SCHEMA_NAME
			CUBE_NAME
			DIMENSION_UNIQUE_NAME
			HIERARCHY_UNIQUE_NAME
			LEVEL_UNIQUE_NAME
			LEVEL_NUMBER
			MEMBER_NAME
			MEMBER_UNIQUE_NAME
			MEMBER_CAPTION
			MEMBER_TYPE
			Tree operator (see below)

Note that the last seven Enum values (adSchemaCubes to adSchemaMembers) should be used with multidimensional data providers. For more information including the definition of the tree operator restriction of adSchemaMembers, see the OLE DB for OLAP Programmer's Reference.

4.14 The AffectEnum values listed in the CancelBatch method topic in the ActiveX Data Objects Programmer's Reference contains an error. The following values are missing from the list but do exist and can be used:

adAffectAllChapters     Cancel pending changes for all chapters.

4.15 The adModeShareDenyNone ConnectModeEnum value is incorrectly described in the Mode property topic. It should be listed as such:

adModeShareDenyNone	Allow others to open connection with any permissions. Neither read nor write access can be denied to others.

4.16
The Index property formerly returned an error if no Index was set on the Recordset object.
As of ADO 2.1 in MDAC 2.1 Service Pack 1, it returns an Empty String, and success.
