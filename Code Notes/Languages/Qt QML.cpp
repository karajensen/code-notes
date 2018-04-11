/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELING LANGUAGE (QML)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************

AVOID WHEN PROPERTY BINDING:
• Declaring intermediate JavaScript variables
• Accessing "var" properties
• Calling JavaScript functions
• Constructing closures or defining functions within the binding expression
• Accessing properties outside of the immediate evaluation scope (non-component properties)
• Writing to other properties as side effects
• Using var unless type is QVariantMap/variant

**************************************************************************************************************/

import QtQuick 2.6
import QtQuick.Controls 1.4
import MyEnums 1.0

id: nameOfControl                      // unique id of element, can be used to access it
objectName: "UserName"                 // user defined name
anchors.left: parent.left              // don't use with RowLayout, use Layout.fillWidth
anchors.right: parent.right            // don't use with RowLayout, use Layout.fillWidth
anchors.left: parent.left              // don't use with ColumnLayout, use Layout.fillHeight
anchors.right: parent.right            // don't use with ColumnLayout, use Layout.fillHeight
anchors.fill: parent                   // completely fills to parent
anchors.margins: 1                     // adds margins between the anchor
property bool myProperty: true         // custom property
property int myEnum: MyEnum.ONE        // enum property
property int myProperty: myFunction    // if property used in function changes, re-evaluates property
property alias myAlias: myProperty     // reference for property
    
/* Called when the element has been instantiated */
Component.onCompleted: {}

/* Called when the element is destroyed */
Component.onDestruction: {}

/* Called when the property has changed */
onMyPropertyChanged: {}

/* Javascript custom function */
function myFunction(x, y) {
    return x + y;
}

Qt.quit() // Quits the application
console.log("Message")

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Item {
}

MouseArea {
    hoverEnabled: true
    acceptedButtons: Qt.RightButton | Qt.LeftButton | Qt.AllButtons
    onPressed: {}
    onRelease: {}
    onClicked: {
        var clickX = mouse.x;
        var clickY = mouse.y;
        var button = mouse.button;
    }
}

// Call using id.popup() to show at mouse position
Menu {
    visible: false
    MenuItem {
        text: "Item"
        iconSource: "qrc:///icon.png"
        enabled: true
        onTriggered: {}
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
Layout.fillHeight: true
Layout.fillWidth: true
Layout.preferredHeight: 30
Layout.preferredWidth: 30

// Aligns elements after each other in a single row
RowLayout {
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

// Aligns elements after each other in a single column
ColumnLayout {
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

// Aligns elements in a grid with n columns
GridLayout {
    columns: 3
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Rectangle {
    color: "#8EACFF"
    radius: 2
    border.color: "red"
    border.width: 1      
}

Text {
    text: "text"
    verticalAlignment: Text.AlignVCenter
    font.pointSize: 14
    font.bold: true
}

Button {
    iconSource: "qrc:///icon.png"
    enabled: true
    onClicked: {}
}

ProgressBar {
    maximumValue: 20
    minimumValue: 0
    style: ProgressBarStyle {
        background: Rectangle {
            radius: 2
            color: "grey"
            implicitWidth: 100
            implicitHeight: 20
        }
        progress: Rectangle {
            color: "blue"
        }
    }
}

Dialog {
    visible: false // Turning on/off will show dialog window
    title: "Title"
    width: 300
    height: 80
    contentItem: Rectangle {
        anchors.fill: parent
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScrollView {
    Layout.fillWidth: true
    Layout.fillHeight: true
    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: context_model // Set through C++

        onCurrentIndexChanged: {
            console.log("Selected " + currentIndex);
        }          
        onCurrentItemChanged: {
            console.log("Selected " + currentItem);
        }
        
        // Each item of the model is instantiated with the delegate
        delegate: Item {
            property bool isHighlighted: mouseArea.containsMouse
            property bool isSelected: listView.currentIndex == index
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onPressed: { listView.currentIndex = index; }
                onClicked: { listView.currentIndex = index; }
            }                   
            Text {
                width: listView.width
                height: 30
                text: role_name // Set through C++
            }
        }
    }
}
