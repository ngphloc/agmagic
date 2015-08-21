---------------------------------------------------------
Microsoft Jet and Replication Objects Readme File
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft Jet and Replication Objects documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   
2. TECHNICAL NOTES

3. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS

----------------------
1. PRODUCT DESCRIPTION
----------------------
Microsoft Jet and Replication objects (JRO) allow you to add features to your application that are specific to the Microsoft Jet Database Engine. The Jet and Replication objects are based fundamentally on Microsoft ActiveX Data Objects (ADO), because they are connected to an ADO Connection object. However, the Jet and Replication objects function only with Microsoft Jet databases. 

------------------
2. TECHNICAL NOTES
------------------
There are no technical notes at this time.

-----------------
3. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS
-----------------

The following is a list of Jet and Replication Objects known bugs.

Databases made replicable in code which have never been opened in Microsoft Access will always have local projects (forms, reports, macros, modules) and they can never be changed to make the project replicable. This is because the system table which controls this functionality (mSysAccessObjects) does not exist if the database was never opened in Access prior to making the database replicable. Once the database is made replicable the user cannot change the replicability of the project.

