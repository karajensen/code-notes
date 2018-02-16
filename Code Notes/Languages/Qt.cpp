////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT MODULES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QtCore               Core non-graphical classes used by other modules
QtGUI                Base classes for graphical user interface (GUI) components. Includes OpenGL
QtMultimedia         Classes for audio, video, radio and camera functionality
QtMultimediaWidgets  Widget-based classes for implementing multimedia functionality
QtNetwork            Classes to make network programming easier and more portable
QtQML                Classes for QML and JavaScript languages
QtQuick              A declarative framework for building highly dynamic applications with custom UI
QtQuickControls      Reusable Qt Quick based UI controls to create classic desktop-style user interfaces
QtQuickDialogs       Types for creating and interacting with system dialogs from a Qt Quick application
QtQuickLayouts       Layouts are items that are used to arrange Qt Quick 2 based items in the UI
QtSQL                Classes for database integration using SQL
QtTest               Classes for unit testing Qt applications and libraries
QtWidgets            Classes to extend Qt GUI with C++ widgets

LIBRARY: Set of functions, organized in classes, that does some work and then returns control to the client
FRAMEWORK: An abstract design that you need to insert into, through inheritance or callbacks, that the framework then calls
TOOLKIT: More focused library, used almost exclusively for graphical widgets, and GUI components
**************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT LICENSING
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
**************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT COMPONENTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.exec(); // Start the event loop
}

// QString
QString str = "str";
str.split(" "); // Returns QStringList of string split by spaces

// QStringList
QStringList lst; // Inherits from QList<QString>, specifically for strings
lst.join(" ")    // Returns a combined string seperated by spaces
lst.append(lst2) // Adds a new string list to the end

// QList
QList<int> lst; // Fast index-based access, insertions and removals
lst << 1 << 2;  // Allows streaming into container

// QListIterator
QListIterator<int> iter(myList);
while(iter.hasNext()) { iter.next(); }

//===================================================================================================
//WIDGETS
//===================================================================================================

// QWidget
QWidget widget; // Root widget used as a window
widget.setWindowTitle("Title");
widget.show();
widget.setLayout(layout); // Add a layout to the window, automatically parents

// QLabel
QLabel lbl("Message"); // Allows use of html tags to customise text

// QPushButton
QPushButton btn("Text");
QObject::connect(button, SIGNAL(clicked()), &app, SLOT(myFn()));  // Connect to button's click event

// QSpinBox
QSpinBox spinbox;
spinbox.setRange(min, max);
spinBox.setValue(value);
QObject::connect(spinBox, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

// QSlider 
QSlider slider(Qt::Horizontal);
slider.setRange(min, max);
slider.setValue(value);
QObject::connect(slider, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

//===================================================================================================
//LAYOUTS
//===================================================================================================

// QHBoxLayout: lays out widgets horizontally from left to right
QHBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout: lays out widgets vertically from top to bottom

// QGridLayout: lays out widgets in a grid.

//===================================================================================================
//FILE SYSTEM
//===================================================================================================

// Read from a file, no need to close it
QFile file("myFile.txt");
if(file.open(QIODevice::ReadOnly))
{
    QTextStream stream(&file);
    QString line = stream.readLine(); // read the next line
    while(!line.isNull())
    {
        line = stream.readLine();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT OBJECTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT MODELING LANGUAGE (QML)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//• QML: Markup language for user interfaces made up of elements, uses Javascript for scripting

import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Qt.quit()  // Quits the application

//===================================================================================================
//QML PROPERTIES
//===================================================================================================
id: nameOfControl                         // unique id of element, can be used to access it
objectName: "UserName"                    // user defined name
anchors.left: parent.left                 // don't use with RowLayout, use Layout.fillWidth
anchors.right: parent.right               // don't use with RowLayout, use Layout.fillWidth
anchors.left: parent.left                 // don't use with ColumnLayout, use Layout.fillHeight
anchors.right: parent.right               // don't use with ColumnLayout, use Layout.fillHeight
anchors.fill: parent                      // completely fills to parent
anchors.margins: 1                        // adds margins between the anchor
heigh: 30                                 // avoid as easily ovewritten
width: 30                                 // avoid as easily ovewritten
visible: true                             // whether control is visible
property var myProperty: true             // custom property
property alias myProperty2: myProperty;   // alias for property
    
/* Called when the element has been instantiated */
Component.onCompleted: {
}

/* Called when the element is destroyed */
Component.onDestruction: {
}

/* Called when the property 'color' has changed */
onColorChanged: {
}

/* Javascript custom function */
function myFunction(x, y) {
    return x + y;
}

//===================================================================================================
//QML ELEMENTS
//===================================================================================================

/* Aligns elements after each other in a single row */
RowLayout {
    spacing: 5
}

/* Aligns elements after each other in a single column */
ColumnLayout {
    spacing: 5
}

/* Aligns elements in a grid with n columns */
GridLayout {
    columns: 3
    spacing: 5
}

/* Interactable area */
MouseArea {
    acceptedButtons: Qt.AllButtons
    onPressed: {}
    onRelease: {}
    onClicked: {
        var clickX = mouse.x;
        var clickY = mouse.y;
    }
}

/* Invisible Rectangle */
Item {
}

/* Visible Rectangle */
Rectangle {
    color: "red"
}

/* Visible Text */
Text {
    text: "text"
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT MODELS / VIEWS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
**************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QMAKE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Run from top level directory of the project  
• Generates Makefiles from a project files (.pro) and includes build rules for moc and uic
• Project files include a list of source/header files, libraries, include paths, configuration info
• Project files can be auto-generated from Qt Creator wizard and qmake
**************************************************************************************************************/

//===================================================================================================
//RUNNING QMAKE
//===================================================================================================
qmake -makefile [options] file1.pro file2.pro // output will be Makefiles (default)
qmake -project  [options] file.pro MyDir      // output will be a project (*.pro) file, accepts dirs
make /*or*/ nmake                             // generates exe from Makefiles

//GENERAL OPTIONS
-help               // output help information
-o [outputname]     // change the name of the output file
-d                  // output debug information
-t [template]       // change the template used in the project file (only after it's processed)
-Wall               // output all warnings
-Wnone              // output no warnings
-Wparser            // output only parser warnings
-Wlogic             // output warnings for problems in project file
-spec macx-g++      // change the platform to mac

//MAKEFILE MODE OPTIONS
"CONFIG+=test"           // pass extra assignments, processed before .pro file
"CONFIG+=test" -after    // extra assignments processed after .pro file
-nocache                 // .qmake.cache file ignored
-nodepend                // don't generate dependency information	

//PROJECT MODE OPTIONS
-r                       // look through supplied directories excursively
-nopwd                   // only use supplied files, do not use current working directory

//===================================================================================================
//PROJECT CONFIGURATION
//===================================================================================================
TARGET = hello                 // name of the executable
VERSION = 1.2.3                
LANGUAGE  = C++
DESTDIR = "c:/MyPath"          // The directory to output the target executable
CONFIG += debug                // add configuration information to project
TEMPLATE = app                 // sets what type of project to build, overrides previously set
PRECOMPILED_HEADER = stdafx.h  
HEADERS += hello.h             	
FORMS = hello.ui               
SOURCES = hello.cpp main.cpp   // Can also just list instead of +=, use \ for newlines      
INCLUDEPATH += "c:/MyPath"     
MOC_DIR = "c:/MyPath"          // Where intermediate moc files are placed
OBJECTS_DIR = "c:/MyPath"      // Where intermediate objects are placed
DEFINES += MY_DEFINE           // Add a new #define MY_DEFINE, can be removed with -=
QT += xml                      // Add qt libraries to link against, core and gui already there by default
QT += widgets designer         // Requires lib template, builds a qt designer plugin

//OPERATORS
# This is a comment       // use &&LITERAL_HASH for actual #
$$value                   // Get contents of variable
$${value}                 // Same as $$value but allows adding to string values (eg. DEFINES = name_$${value})
$$[qmake_property]        // Get contents of qmake property
$$(env_variable)          // Get contents of environment variable when qmake is run
$(env_variable)           // Get contents of environment variable when makefiles are processed
$$replace_fn()            // Get return of a replace function
= value                   // Replace the value	
-= value                  // Subtract the value
+= value                  // Add the value
*= value                  // Only add if it hasn't already been added
~= expression             // Replaces any values that match a regular expression
MY_VAR = 0                // Create a new variable
MY_VAR = one two three    // Create a new list with strings

//CONFIG OPTIONS
qt                        // Link against qt library
release                   // Build project in release, if 'debug' is also used, last one is only used
debug                     // Build project in debug, if 'release' is also used, last one is only used
debug_and_release         // The project is prepared to be built in both debug and release modes
debug_and_release_target  // Put debug/release builds in seperate directories (default)
build_all                 // Used with debug_and_release to build both debug and release
autogen_precompile_source // Automatically generates precompiled header files specified in .pro file
ordered                   // Used with subdirs template, directories should be processed in a given order
precompile_header         // Enables precompiled headers support
warn_on                   // Increase warning level from default
warn_off                  // Decrease warning level from default
exceptions                // Exception support enabled (default)
exceptions_off            // Exception support disabled
rtti                      // RTTI support enabled (by default, compiler default is used)
rtti_off                  // RTTI support disabled (by default, compiler default is used)
stl                       // STL support enabled (by default, compiler default is used)
stl_off                   // STL support disabled (by default, compiler default is used)
thread                    // Thread support is enabled (enabled by default)
c++11                     // C++11 support enabled, by default is disabled
c++14                     // C++14 support enabled, by default is disabled
opengl                    // Includes opengl support
windows                   // app Template only, Target is a Windows GUID application
console                   // app Template only, Target is a Win32 console application
testcase                  // app Template only, Target is an automated test
dll                       // lib Template only, The library is a shared library (dll).
staticlib                 // lib Template only, The library is a static library.
plugin                    // lib Template only, The library is a plugin.

//TEMPLATE OPTIONS
app                           // creates Makefile to build an application (default)
lib                           // creates Makefile to build a library
aux                           // creates Makefile to build nothing, used fo interpreted languages
subdirs                       // creates Makefile to use project files in each subdirectory
vcapp                         // creates Visual Studio Project file to build an application
vclib                         // creates Visual Studio Project file to build a library
vcsubdirs                     // creates Visual Studio Solution file to build projects in sub-directories 
                              
//CONDITIONAL SCOPE                  
debug {}                      // do if debug configuration, can use any config options
!debug {}                     // do if not debug configuration
win32 {}                      // do if windows configuration
win32:debug {}                // can combine nested scopes
win32|macx {}                 // do if either is true
win32:DEFINES += TEST         // add only if win32
CONFIG(opengl) {}             // alternative to scope
win32 {} else:macx {} else {}

// FUNCTIONS
exists(main.cpp) {}           // do code inside if file exists, !exists(){} for negative
error("error")                // print an error
message("message")            // print a message
include(other.pro)            // include another project file

//REPLACE FUNCTIONS
absolute_path("file.txt")
basename("MyPath/file.txt")      // Returns file name
cat("file.txt")                  // Returns contents of file
clean_path("MyPath/file.txt")    // Returns normalized path, converts to / and removes .
dirname("MyPath/file.txt")       // Returns directory of file	
enumerate_vars()                 // Returns list of all defined variable names
find(MY_VAR, expression)         // Returns all the values in MY_VAR that match the regex
files(expression, true)          // Returns list of files using regex from working dir, true for recursion
first(MY_VAR)                    // Returns first of MY_VAR if a list
getenv(MY_ENV_VAR)               // Returns value of env var, supports var names with () in them
join(MY_VAR, , prefix, suffix)   // Returns MY_VAR with suffix and prefix (both optional)

//REPLACE FORMAT FUNCTIONS
//Floating-point numbers are currently not supported
format_number(value, obase=16)   // Returns decimal number in hex
format_number(value, ibase=16)   // Returns hex number in decimal
format_number(value, width=n)    // Sets the min width of the output, if output shorter, pads with spaces
format_number(value, zeropad)    // Pads the output with 0 instead of spaces
format_number(value, padsign)    // Prepends a space to positive values in the output
format_number(value, alwayssign) // Repends a plus sign to positive values in the output
format_number(value, leftalign)  // Places the padding to the right of the value in the output

//===================================================================================================
//QMAKE PROPERTIES
//===================================================================================================
qmake -set "QT_VERSION" value    // set the property
qmake -query "QT_VERSION"        // query the property
qmake -query                     // queries all property/value pairs
$$[QMAKE_VERSION]                // query the property in a project file

QMAKE_VERSION             // the current version of qmake
QT_INSTALL_ARCHDATA       // location of general architecture-dependent Qt data
QT_INSTALL_BINS           // location of Qt binaries (tools and applications)
QT_INSTALL_CONFIGURATION  // location for Qt settings. Not applicable on Windows
QT_INSTALL_DATA           // location of general architecture-independent Qt data
QT_INSTALL_DOCS           // location of documentation
QT_INSTALL_EXAMPLES       // location of examples
QT_INSTALL_HEADERS        // location for all header files
QT_INSTALL_IMPORTS        // location of QML 1.x extensions
QT_INSTALL_LIBEXECS       // location of executables required by libraries at runtime
QT_INSTALL_LIBS           // location of libraries
QT_INSTALL_PLUGINS        // location of Qt plugins
QT_INSTALL_PREFIX         // default prefix for all paths
QT_INSTALL_QML            // location of QML 2.x extensions
QT_INSTALL_TESTS          // location of Qt test cases
QT_INSTALL_TRANSLATIONS   // location of translation information for Qt strings
QT_SYSROOT                // the sysroot used by the target build environment
QT_VERSION                // the Qt version
