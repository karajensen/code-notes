/////////////////////////////////////////////////////////////////////////////////////
//C++ Qt
/////////////////////////////////////////////////////////////////////////////////////

QApplication qA;    // Manages the main settings, one per exe even if multiple windows
qA.processEvents()  // Processes GUI events 
qA.exit()           // Exits the app

/////////////////////////////////////////////////////////////////////////////////////
//QML
/////////////////////////////////////////////////////////////////////////////////////

/**
* To view a QML file in Qt Creator:
* File -> New File or Project -> Applications -> Qt Quick UI
* Avoid using position properties
*/

import QtQuick 2.3           // Import basic QML data types
import QtQuick.Controls 1.2  // Import GUI control data types
import QtQuick.Window 2.2    // Import application window data type

// OBJECT HIERARCHY
Rectangle {
    width: 200
    Text {                    // Parent property automatically set to Rectangle
        text: "Example"
    }
}

//===============================================================================
// SHARED PROPERTIES / METHODS
//===============================================================================

parent                        // Allows access to all parent properties
anchors.centerIn: parent
anchors.horizontalCenter: parent.horizontalCenter
anchors.verticalCenter: parent.verticalCenter
width: 200
height: 100

console.log("Console");
Qt.quit();

//===============================================================================
// OBJECT PROPERTIES / METHODS
//===============================================================================

// APPLICATION
ApplicationWindow {
    title: "Example"
}

// BUTTON
Button {
    text: "Example"
    radius: 8       // rounded corners
}

// RECTANGLE
Rectangle {
    color: "red"
}

// TEXT
Text{
    text: "Example"
}

// MENU BAR
menuBar: MenuBar {
    Menu {
        title: "MyMenu"
        MenuItem {
            text: "Option1"
            onTriggered: console.log("Option1");
        }
        MenuItem {
            text: "Option2"
            onTriggered: console.log("Option2");
        }
    }
}

//===============================================================================
// INPUT
//===============================================================================

// Key Bindings
Qt.Key_Return

// Put inside object that has keyboard focus
focus: true
Keys.onPressed : {
    if (event.key == Qt.Key_Return) {
        // change properties of object
        event.accepted = true;
    }
}

MouseArea {
    anchors.fill: parent
    onClicked: // change properties of object
}

//===============================================================================
// LAYOUTS
//===============================================================================

// Stacks each object in a single column
Column {
    Rectangle {
        width: 100
    }
    Rectangle {
        width: 100
    }
}

//===============================================================================
// CUSTOM QML OBJECTS
//===============================================================================

// MyObject.qml
import QtQuick 2.3
Rectangle {
    width: 100
    color: "red"
}

// Application.qml
import QtQuick 2.3
MyObject {
    width: 200
}
MyObject {
    width: 200
    color: "blue"
}