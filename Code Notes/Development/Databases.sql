/*/////////////////////////////////////////////////////////////////////////////////////////////////
//DATABASES
///////////////////////////////////////////////////////////////////////////////////////////////////

DATABASE: Collection of tables that stores structured data
TABLE: Collection of rows/columns for the data and controls to help validate it
ROW: Row of individual records
COLUMN: Attributes/category
CONTROLS: Constraints, triggers, defaults, and customized user data types
SNAPSHOT: Read-only, static view of a database
SUBQUERY: Connect one or more queries together; query more than one table at a time

COLUMN TYPES
• Raw data columns store specific data
• Categorical columns classify/group the data
• Identifier columns provide an ID 
• Relational/referential columns create a link between tables

FILEGROUP
• Has primary, secondary and log files assigned to it
• These files an be duplicated across multiple drives and accessed through the one filegroup
• Can have multiple filegroups

PRIMARY FILE (.MDF)
• Contains the startup information for the database and points to the other files in the database
• Can store user data and objects if secondary file not used

SECDONARY FILE (.NDF)
• Multiple, optional, user-defined and store user data and objects

LOG FILE (.LDF)
• Contain the information that is required to recover all transactions in the database
• Allows recovery/rollback of the database to a stable state
• Required for database mirroring

--------------------------------------------------------------------------------------------------
DATABASE STATES
--------------------------------------------------------------------------------------------------
ONLINE              Available for access
OFFLINE             Unavailable for access
RESTORING           Unavailable; Files from the filegroup are being restored
RECOVERING          Unavailable; If success will become ONLINE, if fail will become SUSPECT
RECOVERY PENDING    Unavailable; Resource-related error during recovery, files may be missing
SUSPECT             Unavailable; Filegroup may be damaged
EMERGENCY           Read-only, logging disabled, access limited for troubleshooting

--------------------------------------------------------------------------------------------------
FILE STATE
--------------------------------------------------------------------------------------------------
ONLINE              Available for all operations
OFFLINE             Unavailable for access
RESTORING           Unavailable; File is being restored
RECOVERY PENDING    Recovery of file is postponed
SUSPECT             Recovery of file failed; if lives in primary filegroup, database marked as suspect
DEFUNCT             The file was dropped when it was not online

///////////////////////////////////////////////////////////////////////////////////////////////////
//SYSTEM DATABASES
///////////////////////////////////////////////////////////////////////////////////////////////////

SQL SERVER
• Database management system (DBMS) containing 5 system databases that are used to manage user-created databases
• Maximum of 32,767 databases can be created on an instance of SQL Server

MASTER DATABASE
• Records all the system-level information for an instance of SQL Server
• Logon accounts, endpoints, linked servers, system configuration settings
• Records location of all other databases

MODEL DATABASE
• Template for all databases created
• For any changes all databases created afterward will inherit those changes
    
MSDB DATABASE
• Scheduling alerts, mail and jobs

RESOURCE DATABASE
• Read-only database that contains all the system objects
• Makes upgrading to new version of SQL Server easier/faster

TEMPDB
• Global resource that is available to all users connected to the instance of SQL Server
• Holds temporary objects such as global and local temporary tables and stored procedures
• Recreated every time SQL Server starts

//////////////////////////////////////////////////////////////////////////////////////////////////
//DATABASE DESIGN
//////////////////////////////////////////////////////////////////////////////////////////////////

DESIGN RULES
• Each table should have an primary key column where each row has a unique value
• A table should avoid nullable columns as they increase complexity of operations

DATA NORMALIZATION
• Goal is to achieve several narrow tables with few columns by applying the normalization forms
• Too much and number and complexity of joins will increase reducing performance
• A good amount improves performance
    - Faster sorting and index creation
    - Fewer indexes per table improving performance of INSERT, UPDATE and DELETE statements
    - Fewer null values and less opportunity for inconsistency

1ST NORMAL FORM: A table should not have a row entry as a list of values or repeating columns to list the values
2ND NORMAL FORM: If composite key is used, all non-key entries must depend on both keys
3RD NORMAL FORM: All non-key entries must depend only the primary key and not on another non-key entry

DATA INTEGRITY
• Entity integrity: enforces Identifier columns to have unique values within a table
• Domain integrity: enforces particular data types for a column
• User-defined integrity: user created column and table rules
• Referential integrity: ensures relationship between tables remains constant
    - Cannot add entry to the child table with a foreign key unless the parent table has it
    - Prevents changing parent table values that will create orphaned rows in the child table 
    - Prevents deleting parent table rows that are in the child table

DATABASE KEYS
• Primary Key: One or more columns holding a unique id for the table, cannot be null
• Foreign Key: Column used to create parent-child relationships between tables
• Clustered Key: Sorts the rows by column with it, only one per table, defaults to primary key
• Composite Key: When there are two primary keys

EXTENDED PROPERTIES
• Should not contain sensitive information
• Used for captions, input masks for querying data, formatting rules, size/window location for display

//////////////////////////////////////////////////////////////////////////////////////////////////
//STRUCTURED QUERY LANGUAGE (SQL)
//////////////////////////////////////////////////////////////////////////////////////////////////
• Not case sensitive- use [] if using a name that's also a keyword
• Data Definition Language (DDL): Used to define the database structure, cannot be undone
• Data Manipulation Language (DML): Used to managing data, can be undone
• Syntax chosen mostly from SQL server, other DBMS can have different
*/
 
/*TYPE		           BYTES     RANGE*/
bigint                   8       -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
int                      4       -2,147,483,648 to 2,147,483,647
smallint                 2       -32,768 to 32,767
tinyint                  1        0 to 255
money                    8       -922,337,203,685,477.5808 to 922,337,203,685,477.5807 /*uses currency symbol*/
smallmoney               4       -214,748.3648 to 214,748.3647 /*uses currency symbol*/
bit				         1        1,0,NULL /*up to 8 bit variables in table will be store in the 1 byte*/
real                     4        3.40E +/- 38			  
float(1-24)              4        7 digits /*equivalent to float*/
float(25-53)             8        15 digits /*equivalent to double*/
decimal/numeric(1-9)     5        10.0E +/- precision
decimal/numeric(10-19)   9        10.0E +/- precision
decimal/numeric(20-28)   13       10.0E +/- precision
decimal/numeric(29-38)   17       10.0E +/- precision
char(n)                  n        non-unicode character set where n = [0,8000] /*size is fixed n bytes*/
varchar(n/max)           n        non-unicode character set where n = [0,8000] /*size is length of input string*/
nchar(n)                 2xn      unicode character set where n = [0,4000] /*size is fixed n bytes*/
nvarchar(n/max)          2xn      unicode character set where n = [0,4000] /*size is length of input string*/
binary(n)		         n        1 to 8000 /*size is fixed n bytes*/
varbinary(n/max)         n        1 to 8000 /*size is length of input values*/
				  		 
/*DATE/TIME*/	  		 
date              3      0001-01-01 to 9999-12-31, January 1, 1 A.D. to December 31, 9999 A.D.
time              5      00:00:00.0000000 to 23:59:59.9999999
datetimeoffset    10     0001-01-01 to 9999-12-31, January 1,1 A.D. to December 31, 9999 A.D, 00:00:00 to 23:59:59.9999999
smalldatetime     4      1900-01-01 to 2079-06-06, January 1, 1900 to June 6, 2079, 00:00:00 to 23:59:59
datetime          8      0001-01-01 to 9999-12-31, January 1,1 AD to December 31, 9999 AD, 00:00:00 to 23:59:59.9999999

/*****************************************************************************
 DATA MANIPULATION LANGUAGE COMMANDS
*****************************************************************************/

/*SELECT*/
SELECT * FROM MyTable;                            /*select all from table*/
SELECT MyCol1, MyCol2 FROM MyTable;               /*select columns from table, determines reported order of columns*/
SELECT DISTINCT MyCol FROM MyTable;               /*select only unique entries from column*/
SELECT MyCol AS MyAlias FROM MyTable;             /*display column under a different name*/
SELECT (MyCol+1.0) AS MyAlias FROM MyTable;       /*Adding values to columns, use alias as auto assigns name*/
SELECT (MyCol1-MyCol2) AS MyAlias FROM MyTable;   /*Difference of two value columns*/
SELECT (MyCol & 'temp') AS MyAlias FROM MyTable;  /*strings, can also use + for symbol*/
SELECT MyTable.MyColumn FROM MyTable;			  /*qualification of column names*/
SELECT MyCol1, (MyCol2+MyCol3) AS MyAlias FROM MyTable;

/*INSERT*/
INSERT INTO MyTable (MyCol1, MyCol2) VALUES (10, 'example'); /*insert entry into table, entries can be omitted*/

/*UPDATE*/
UPDATE MyTable SET MyCol1=v1, MyCol2='example';   /*update all given columns to given values*/
UPDATE MyTable SET MyCol1=v1 WHERE MyPK=v3;       /*update for primary key the column values*/

/*DELETE*/
DELETE * FROM MyTable; /*or*/ DELETE FROM MyTable;  /*deletes all data, can be undone though slower than TRUNCATE*/
DELETE FROM MyTable WHERE MyColumn=value;           /*delete entry if column holds value*/

/*WHERE*/
/*filters individual rows of data*/
.. WHERE MyCol=value;                        /*select all equal to value, strings use ''*/
.. WHERE MyCol<>value;                       /*select all not equal to value (can be !=)*/
.. WHERE MyCol BETWEEN v1 AND v2;            /*select all between 1 and 2*/
.. WHERE MyCol IN (v1, v2);                  /*select all in given array of values*/
.. WHERE MyCol IN (SELECT * FROM MyTable2);  /*select all that exist in Table2 (Subquery)*/
.. WHERE MyCol NOT IN (v1, v2);              /*select all not in given array of values*/
.. WHERE MyCol LIKE 's*';                    /*select all starting with letter, can also use % for wildcard*/
.. WHERE MyCol LIKE '*s';                    /*select all ending with letter*/
.. WHERE MyCol LIKE '[ST]*';                 /*select all starting with S or T*/
.. WHERE MyCol LIKE '*temp*';                /*select all with substring 'temp'*/
.. WHERE MyCol NOT LIKE '*temp*';            /*select all without substring 'temp'*/
.. WHERE MyCol IS NULL;                      /*select all values from column that are null*/
.. WHERE MyCol1=v1 AND MyCol2=v2;            /*select all where both conditions are true*/
.. WHERE MyCol1=v1 OR MyCol2=v2;             /*select all where one or more conditions are true*/
.. WHERE MyCol1=v1 AND (MyCol2=v2 OR MyCol3=v3);

/*ORDERING*/
/*sort individual rows of data*/
.. ORDER BY MyColumn;   /*orders rows by given column, default is descending*/
.. ORDER BY 1 DESC;     /*orders rows by column number 1*/
.. ORDER BY 1,2 ASC;    /*orders by column 1 and if duplicate values, orders by column 2*/
.. WHERE .. ORDER BY .. /*after WHERE or standalone*/

/*GROUPING*/
/*• sort groups of data calculated by an aggregate function
  • When using one or more aggregate function, must have group by
  • All column names except names used in aggregate/alias must be in GROUP BY clause*/
SELECT Count(MyColumn1), MyColumn2 FROM MyTable GROUP BY MyColumn2

/*GROUP FILTERING*/
/*filters groups of data calculated by an aggregate function*/
.. GROUP BY .. HAVING Count(MyColumn1) > 2

/*SUBQUERIES*/
SELECT MyTable2.C1, MyTable2.C2, 
(SELECT MIN(MyTable1.C1) FROM MyTable1 WHERE MyTable1.ID = MyTable2.ID) AS MyAlias
FROM MyTable2 ORDER BY MyTable2.C2

/*****************************************************************************
 DATA DEFINITION LANGUAGE COMMANDS
*****************************************************************************/

/*create new table, defaults to NULL possible for field*/
CREATE TABLE MyTable(MyCol1 int NOT NULL, MyCol2 varchar(255)); 

DROP DATABASE MyDatabase                   /*delete the database*/  
DROP TABLE MyTable                         /*delete the table*/  
TRUNCATE TABLE MyTable                     /*remove all records from within a table*/
ALTER TABLE MyTable DROP COLUMN MyCol      /*delete column in table*/
ALTER TABLE MyTable ADD MyCol int          /*add column to table*/
ALTER TABLE MyTable ALTER COLUMN MyCol int /*change datatype of column*/

/*////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS AND PROCEDURES
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

/*****************************************************************************
AGGREGATE FUNCTIONS: Return a single value
*****************************************************************************/

AVG(MyCol)             /*returns average in value column*/
AVG(DISTINCT MyCol)    /*only use unique values for function*/
COUNT(MyCol)           /*number of rows in a column, null values not counted*/
COUNT(*)               /*number of rows in table*/
MAX(MyCol)             /*return highest number in column*/
MIN(MyCol)             /*return lowest number in column*/
SUM(MyCol)             /*sums values in a column*/

/*****************************************************************************
ARITHMATIC FUNCTIONS: Manipulate numeric data
*****************************************************************************/

EXP(x)     /*returns e^x*/
MOD(x/y)   /*returns x % y*/
SQRT(x)    /*returns Square root of x*/

/*****************************************************************************
DATE TIME FUNCTIONS
*****************************************************************************/

DATEPART('yyyy', MyCol) /*returns a numeric date of year, uses date datatype*/
GETDATE()               /*Returns the date set on the computer*/

/*****************************************************************************
CHARACTER FUNCTIONS
*****************************************************************************/

LTRIM(MyCol) /*removes white spaces from left of value or column name*/
RTRIM(MyCol) /*removes white spaces from right of value or column name*/
REPLACE()
LEN()       /*Returns the length of a string*/

/*****************************************************************************
CONVERSION FUNCTIONS
*****************************************************************************/

CAST(MyColumn AS nvarchar(5));

/*****************************************************************************
 PROCEDURES
*****************************************************************************/

/*Inserting Procedure*/
CREATE PROCEDURE dbo.InsertValues(@Name nvarchar(255), @DueDate datetime, @IsEnabled bit = 1)
AS BEGIN
INSERT MyTable([Name], DueDate, Notes, IsEnabled) VALUES (@Name, @DueDate, @Notes, @IsEnabled)
END

/*Updating Procedure*/
CREATE PROCEDURE dbo.UpdateValues(@EntryID int, @Name nvarchar(255), @IsEnabled)
AS BEGIN
UPDATE MyTable SET [Name] = @Name, IsEnabled = @IsEnabled WHERE EntryID = @EntryID
END

/*Getting Procedure*/
CREATE PROCEDURE dbo.GetValues
AS BEGIN
SELECT * FROM  MyTable
RETURN
END

/*Modifying Procedure*/
ALTER PROCEDURE dbo.MyProcedure(@EntryID int)
AS BEGIN
UPDATE MyTable SET * WHERE EntryID = @EntryID
END

/*Executing Procedure in SQL*/
EXECUTE MyProcedure 10.0 'MyString'