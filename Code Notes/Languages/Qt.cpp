////////////////////////////////////////////////////////////////////////////////////////////////////
//QT
////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************************************

QT MODULES
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

***************************************************************************************************

QT LICENSING
Qt for Application Development: 
  • Cross platform development for desktop and mobile
  • Can be licensed under commercial and open source licenses (GPU / LGPU)
  • Static linking requires GPU licence and all project code public
  • Dynamic linking can use LGPU licence to keep parts of it private
  • Some modules GPU only: Qt Data Visualization / Qt Charts / Tooling (if modifications are done)
Qt for Device Creation: 
  • Used with embedded devices
  • Only under commercial licence to allow integration with proprietary code 
  
**************************************************************************************************/

//===================================================================================================
// Qt Components
//===================================================================================================

// QString
QString str = "str";
str.split(" ");                         // Returns QStringList of string split by spaces

// QStringList
QStringList lst;                        // Inherits from QList<QString>, specifically for strings
lst.join(" ")                           // Returns a combined string seperated by spaces
lst.append(lst2)                        // Adds a new string list to the end

// QList
QList<int> lst;                         // Fast index-based access, insertions and removals
lst << 1 << 2;                          // Allows streaming into container

// QListIterator
QListIterator<int> iter(myList);
while(iter.hasNext()) { iter.next(); }

//===================================================================================================
// Qt Modeling Language (QML)
//===================================================================================================
//• QML: Markup language for user interfaces made up of elements, uses Javascript for scripting

import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Qt.quit()  // Quits the application

//--------------------------------------------------------------------------------------------------
// QML PROPERTIES
//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
// QML ELEMENTS
//--------------------------------------------------------------------------------------------------

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

//===================================================================================================
// MODELS / VIEWS
//===================================================================================================
//• Model: Contains the data and its structure
//• View: A container that displays the data. The view might display the data in a list or a grid.
//• Delegate: Determines how each element of data should appear in the view. Can also access each element.
//• Role: Used to access different attributes of a data element in the model

//===================================================================================================
// FILE SYSTEM
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
