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
//TRIGGERING QMAKE
//===================================================================================================
qmake -o Makefile hello.pro   // generate Makefiles
qmake -tp vc hello.pro        // generate visual studio project
make /*or*/ nmake             // generates exe from Makefiles

//===================================================================================================
//PROJECT CONFIGURATION
//===================================================================================================
TARGET = hello                // name of the executable
CONFIG += debug               // add configuration information to project
TEMPLATE = app                // sets what type of project to build, overrides previously set
HEADERS += hello.h            
SOURCES = hello.cpp main.cpp  // Can also just list instead of +=, use \ for newlines      
INCLUDEPATH += "c:/MyPath"
DEFINES += MY_DEFINE          // Add a new #define MY_DEFINE, can be removed with -=
QT += xml                     // Add qt libraries to link against, core and gui already there by default

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
depend_includepath        // Appending the value of INCLUDEPATH to DEPENDPATH is enabled (default)
opengl                    // Includes opengl support
console                   // Target is a Win32 console application

//TEMPLATE OPTIONS
app                       // creates Makefile to build an application (default)
lib                       // creates Makefile to build a library
aux                       // creates Makefile to build nothing, used fo interpreted languages
subdirs                   // creates Makefile to use project files in each subdirectory
vcapp                     // creates Visual Studio Project file to build an application
vclib                     // creates Visual Studio Project file to build a library
vcsubdirs                 // creates Visual Studio Solution file to build projects in sub-directories 

//===================================================================================================
//SCOPES
//===================================================================================================
debug {}                  // do if debug configuration
win32 {}                  // do if windows configuration
win32:debug {}            // can combine nested scopes
win32:INCLUDEPATH {}      // include only if win32
CONFIG(opengl) {}         // do if configuration value is set

//===================================================================================================
//FUNCTIONS
//===================================================================================================
exists(main.cpp) {}       // do code inside if file exists, !exists(){} for negative
error("error")            // print an error
message("message")        // print a message
include(other.pro)        // include another project file

//===================================================================================================
//VARIABLES
//===================================================================================================
# This is a comment       // use &&LITERAL_HASH for actual #
MYVAR = $$MYVAR2          // assign contents of variable to another

