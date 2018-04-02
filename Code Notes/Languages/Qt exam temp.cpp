/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT HELP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Includes tools for generating and viewing Qt help files
• Provides framework for accessing help contents / integrating online help programmatically
• Can view help files through Qt Assistant browser or linking to QHelpEngine API
• 4 files involved with generating help documentation:
-------------------------------------------------------------------------------------------------------
Qt Help Project    | .qhp  | The input file for the help generator consisting of the table of contents, 
                   |       | indices, and references to the actual documentation files (*.html). 
                   |       | It also defines a unique namespace for the documentation. Generates .qch
                   |       | when calling qhelpgenerator doc.qhp -o doc.qch
                   |       | 
Qt Compressed Help | .qch  | The output file of the help generator. This binary file contains all the 
                   |       | information specified in the help project file along with all the 
                   |       | compressed documentation files.
                   |       | 
Qt Help Collection | .qhcp | The input file for the help collection generator. It contains references 
Project            |       | to the compressed help files that should be included in the collection; 
                   |       | it also may contain other information for customizing Qt Assistant. 
                   |       | Generates a .qhc file by calling:
                   |       | qcollectiongenerator mycollection.qhcp -o mycollection.qhc              
                   |       | 
Qt Help Collection | .qhc  | The output of the help collection generator. This is the file QHelpEngine 
                   |       | operates on. It contains references to any number of compressed help files 
                   |       | as well as additional information, such as custom filters.
-------------------------------------------------------------------------------------------------------
**************************************************************************************************************/

// ACCESSING HELP FILES
QHelpEngineCore helpEngine("help.qhc");
QMap<QString, QUrl> links = helpEngine.linksForIdentifier("keyword"));
// If help is available for this keyword, get the help data
if (links.count()) 
{
    QByteArray helpData = helpEngine->fileData(links.constBegin().value());
    if (!helpData.isEmpty())
    {
        displayHelp(helpData);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LINGUIST
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
LUPDATE
• Tool to synchronize source code and translations
• Finds translatable strings from files specified in .pro and creates/updates .ts translation files
• Run using: lupdate myproject.pro

LRELEASE
• Tool to create run-time translation files for use by the released application
• Creates binary QM files out of TS files
• Run using: lrelease myproject.pro

QT LINGUIST TOOL
• Translate text in applications using TS files, can save out QM files
• Includes phrase book
**************************************************************************************************************/

// PROJECT FILE
// Each language required needs to be specified
TRANSLATIONS    = superapp_dk.ts \
                  superapp_fi.ts \
                  superapp_no.ts \
                  superapp_se.ts
                  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LICENSING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
COMMERCIAL:
• Official Qt Support Helpdesk
• Keep your application private
• Full rights to proprietary Qt source code modifications

GENERAL PUBLIC LICENSE (GPL):
• Requires releasing the source code of your application if distributing the open source software 
• All portions of the project must be under GPL as well
• Can use static linking
• Needs to include qt source code or instructions on how to access it

LESSER GENERAL PUBLIC LICENSE (LGPL):
• Allows distributing the open source software with your application without releasing the application source
• LGPL open source software must be re-distributed as LGPU, other portions of project may have different licences
• Possible to keep your application private with dynamic linking
• Needs to include qt source code or instructions on how to access it

QT FOR APPLICATION DEVELOPMENT: 
• Cross platform development for desktop and mobile
• Can be licensed under commercial and open source licenses (GPU / LGPU)
• Some modules GPU only: QtDataVisualization / QtCharts / Tooling (if modifications are done)
  
QT FOR DEVICE CREATION: 
• Used with embedded devices
• Only under commercial licence to allow integration with proprietary code 
  
GPLv2 vs. GPLv3
• GPLv3 added compatibility regulations that make it easier to combine GPL code and code under different licenses
• GPLv3 adds regulations for digital rights management were added to keep GPL software from being changed at will
• GPLv3 adds an explicit patent license/copyright so that no one can profit from them
  
LGPLv2.1 vs. LGPLv3
• LGPLv3 closes loophole of locked-down consumer devices preventing users from installing
  modified versions of the library on the device

LIBRARY: Set of functions, organized in classes, that does some work and then returns control to the client
FRAMEWORK: An abstract design that you need to insert into, through inheritance or callbacks, that the framework then calls
TOOLKIT: More focused library, used almost exclusively for graphical widgets, and GUI components  
**************************************************************************************************************/
