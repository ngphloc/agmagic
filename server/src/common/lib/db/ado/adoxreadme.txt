---------------------------------------------------------
Microsoft ActiveX(R) Data Objects Extensions for DDL and Security
Readme File
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft ADO Extensions for DDL and Security (ADOX) documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   
2. FEATURES
   
3. TECHNICAL NOTES

4. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS

----------------------
1. PRODUCT DESCRIPTION
----------------------

Microsoft� ActiveX� Data Objects Extensions for Data Definition Language and Security (ADOX) is an extension to the ADO objects and programming model. ADOX includes objects for schema creation and modification, as well as security. Because it is an object-based approach to schema manipulation, you can write code that will work against various data sources regardless of differences in their native syntaxes.

---------------
2. FEATURES
---------------

ADOX is a companion library to the core ADO objects. It exposes additional objects for creating, modifying, and deleting schema objects such as tables and procedures. It also includes security objects to maintain users and groups and to grant and revoke permissions on objects.

------------------
3. TECHNICAL NOTES
------------------

3.1 Required/Optional Properties of Tables, Indexes, and Columns

Not all properties of Table, Index, and Column objects may be supported by your data provider. An error will occur if you have set a value for a property that is not supported by the provider.  For new Tables, Indexes, or Columns the error will occur when the object is appended to the collection.  For existing objects, the error will occur when setting the property.

When creating Table, Index, or Column objects, the existence of an appropriate default value for an optional property does not guarantee that the property is supported by your provider. For more information about which properties are supported by your provider, see your provider documentation.

3.2 Using ADOX with Microsoft OLE DB Providers

Certain features of ADOX are unsupported, depending upon your OLE DB data provider. ADOX is fully supported with the Microsoft OLE DB Provider for the Microsoft Jet Database Engine. For the Microsoft SQL Server OLE DB Provider, the Microsoft OLE DB Provider for ODBC, or the Microsoft OLE DB Provider for Oracle see below. ADOX is not supported by any other Microsoft OLE DB providers.

Microsoft SQL Server OLE DB Provider

All ADOX objects, collections, properties, and methods are supported except for those listed here:

Catalog: Create method.
Tables: Properties for existing tables are read-only (properties for new tables can be read/write).
Views: Not supported.
Procedures: Append method, Delete method, Command property.
Keys: Append method, Delete method.
Users: Not supported.
Groups: Not supported.

Microsoft OLE DB Provider for ODBC

All ADOX objects, collections, properties, and methods are supported except for those listed here:

Catalog: Create method.
Tables: Append method, Delete method. Properties for existing tables are read-only (properties for new tables can be read/write).
Views: Append method, Delete method, Command property.
Procedures: Append method, Delete method, Command property.
Indexes: Append method, Delete method.
Keys: Append method, Delete method.
Users: Not supported.
Groups: Not supported.

Microsoft OLE DB Provider for Oracle

All ADOX objects, collections, properties, and methods are supported except for those listed here:

Catalog: Create method.
Tables: Append method, Delete method. Properties for existing tables are read-only (properties for new tables can be read/write).
Views: Append method, Delete method, Command property.
Procedures: Append method, Delete method, Command property.
Indexes: Append method, Delete method.
Keys: Append method, Delete method.
Users: Not supported.
Groups: Not supported.


-----------------
4. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS
-----------------

The following is a list of ADOX known bugs.

4.1 DateCreated/DateModified properties require Refresh

The DateCreated and DateModified properties are NULL for newly appended objects. After appending a new View or Procedure, you must call the Refresh method of the Views or Procedures collection to obtain values for the DateCreated and DateModified properties.

4.2 No ParentCatalog property for Index objects

In ADOX help, ParentCatalog is incorrectly listed as a property of Index objects. ParentCatalog is actually a property of Column and Table objects only.

4.3 adAccessRevoke overrides Rights parameter of SetPermissions

When calling the SetPermissions method of a Group or User, setting the Actions parameter to adAccessRevoke overrides any settings of the Rights parameter. Do not set Actions to adAccessRevoke if you want the rights specified in the Rights parameter to take effect.

4.4 RelatedColumn parameter of Append method (Keys collection)

The documentation for the Append method of the Keys collection should include an optional fourth parameter called RelatedColumn. The updated syntax is:

Keys.Append Key [, KeyType] [, Column] [, RelatedTable] [, RelatedColumn]

The RelatedColumn parameter is optional. RelatedColumn is a String value specifying the name of the related column for a foreign key. The RelatedTable parameter can correspond to the value of the Name property of a Column object.

4.5 adIndexNullsAllow Enum value of IndexNulls property

The documentation for the IndexNulls property of the Index object should include one more Enum constant in the table of valid values:

adIndexNullsAllow     The index does allow entries where the key columns are Null. If a Null value is entered in a key column, the entry is inserted into the index. 
