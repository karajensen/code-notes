////////////////////////////////////////////////////////////////////////////////////////////////////
//QML
////////////////////////////////////////////////////////////////////////////////////////////////////

//• Model: Contains C++ data for a control, can have multiple views for the same data
//• View : Displays the C++ data in Qt / QML in some way(eg.list, slider)
//• QML uses javascript

import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

//--------------------------------------------------------------------------------------------
// SHARED PROPERTIES
//--------------------------------------------------------------------------------------------
id: nameOfControl
objectName: "UserName"                  // user defined name
anchors.left: parent.left               // don't use with RowLayout, use Layout.fillWidth
anchors.right: parent.right             // don't use with RowLayout, use Layout.fillWidth
anchors.left: parent.left               // don't use with ColumnLayout, use Layout.fillHeight
anchors.right: parent.right             // don't use with ColumnLayout, use Layout.fillHeight
anchors.fill: parent                    // completely fills to parent
anchors.margins: 1                      // adds margins between the anchor
heigh : 30                              // avoid as easily ovewritten
width: 30                               // avoid as easily ovewritten
visible: true                           // whether control is visible

/* Called when the object has been instantiated */
Component.onCompleted:
{
}

/* Called when the object is destroyed */
Component.onDestruction :
{
}

/* Called when the property 'color' has changed */
onColorChanged:
{
}

//--------------------------------------------------------------------------------------------
// USER-DEFINED PROPERTIES
//--------------------------------------------------------------------------------------------
property var myProperty: true           // custom property
property alias myProperty2: myProperty; // alias for property

/* Callable function in QML */
function myFunction(x, y)
{
    return x + y;
}

//--------------------------------------------------------------------------------------------
// QML Components
//--------------------------------------------------------------------------------------------

/* Aligns elements after each other in a single row */
RowLayout
{
    spacing: 5
}

/* Aligns elements after each other in a single column */
ColumnLayout
{
    spacing: 5
}

/* Aligns elements in a grid with n columns */
GridLayout
{
    columns: 3
    spacing: 5
}

/* Interactable area */
MouseArea
{
    acceptedButtons: Qt.AllButtons
    onPressed: {}
    onRelease: {}
    onClicked:
    {
        var clickX = mouse.x;
        var clickY = mouse.y;
    }
}

/* Invisible Rectangle */
Item
{
}

/* Visible Rectangle */
Rectangle
{
    color: "red"
}