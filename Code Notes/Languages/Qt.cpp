////////////////////////////////////////////////////////////////////////////////////////////////////
//QT
////////////////////////////////////////////////////////////////////////////////////////////////////

// QString
QString myStr = "str";
myStr.split(" ");                       // Returns QStringList of string split by spaces

// QStringList
QStringList myList;                     // Inherits from QList<QString>, specifically for strings
myList.join(" ")                        // Returns a combined string seperated by spaces

// QList
QList<int> myList;                      // Fast index-based access, insertions and removals
myList << 1 << 2;                       // Allows streaming into container

// QListIterator
QListIterator<int> iter(myList);
while(iter.hasNext()) { iter.next(); }

//===================================================================================================
// QML
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
heigh : 30                                // avoid as easily ovewritten
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
