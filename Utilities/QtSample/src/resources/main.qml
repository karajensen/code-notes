import QtQuick 2.6
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SampleModel 1.0

Rectangle {
    id: root
    width: 560
    height: 260

    /** Style properties */
    property int buttonHeight: 30
    property int rowHeight: 25
    property color darkShade: "#DDDDDD"
    property color midShade: "#DFDFDF"
    property color lightAltShade: "#F5F5F5"
    property color lightShade: "white"
    property color darkHighlight: "#8EACFF"
    property color midHighlight: "#B2C6FF"
    property color lightHighlight: "#E0E8FF"
    property int smallFont: 8
    property int largeFont: 10
    property int marginSize: 4
    property int iconsSize: 16

    Rectangle {
        anchors.fill: parent
        color: darkShade

        Rectangle {
            anchors.margins: marginSize
            anchors.fill: parent
            color: lightShade

            TestObject {
                Component.onCompleted: {
                    console.log("Created Custom Test Object")
                }
            }

            ColumnLayout {
                anchors.fill: parent
                ListView {
                    id: listView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: context_model
                    clip: true
                    currentIndex: 0
                    focus: true

                    onModelChanged: {
                        if(model) {
                            console.log(model.gadgetTest.id + " " + typeof(model.gadgetTest));
                            console.log(Test.Enum.ONE + " " + Test.Enum.TWO + " " + Test.Enum.THREE);
                            console.log(ObjectEnum.ONE + " " + ObjectEnum.TWO + " " + ObjectEnum.THREE);

                            for(var i = 0; i < 3; i++) {
                                console.log(model.intListTest[i] + " " + typeof(model.intListTest[i]));
                                console.log(model.colorListTest[i] + " " + typeof(model.colorListTest[i]));
                                console.log(model.objectListTest[i].id + " " + typeof(model.objectListTest[i]));
                            }
                            var test = model.returnObjectList();
                        }
                    }

                    ScrollBar.vertical: ScrollBar {
                        contentItem.opacity: 1
                    }

                    Menu {
                        id: contextMenu
                        visible: false
                        MenuItem {
                            text: "Start"
                            icon.source: "qrc:///start.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            enabled: {
                                return listView.currentItem != null && listView.currentItem.canStart()
                            }
                            onTriggered: {
                                context_model.startItemProgress(listView.currentIndex);
                            }
                        }
                        MenuItem {
                            text: "Pause"
                            icon.source: "qrc:///pause.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            enabled: {
                                return listView.currentItem != null && listView.currentItem.canPause()
                            }
                            onTriggered: {
                                context_model.pauseItemProgress(listView.currentIndex);
                            }
                        }
                        MenuItem {
                            text: "Stop"
                            icon.source: "qrc:///stop.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            enabled: {
                                return listView.currentItem != null && listView.currentItem.canStop()
                            }
                            onTriggered: {
                                context_model.stopItemProgress(listView.currentIndex);
                            }
                        }
                        MenuItem {
                            text: "Delete"
                            icon.source: "qrc:///delete.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            onTriggered: {
                                context_model.deleteItem(listView.currentIndex);
                            }
                        }
                    }

                    delegate: Item {
                        id: listDelegate
                        property bool isHighlighted: mouseArea.containsMouse || progressBar.containsMouse
                        property bool isSelected: listView.currentIndex == index
                        width: listView.width
                        height: root.rowHeight

                        function canStart() {
                            return role_state_value != SampleItemState.STEPPING;
                        }
                        function canPause() {
                            return role_state_value == SampleItemState.STEPPING;
                        }
                        function canStop() {
                            return role_state_value == SampleItemState.STEPPING ||
                                role_state_value == SampleItemState.PAUSED;
                        }
                        function onMousePress() {
                            listView.currentIndex = index;
                        }
                        function onMouseClick(mouse) {
                            listView.currentIndex = index;
                            if(mouse.button == Qt.RightButton) {
                                contextMenu.popup()
                            }
                        }                           
                            
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.RightButton | Qt.LeftButton
                            onPressed: { onMousePress(); }
                            onClicked: { onMouseClick(mouse); }
                        }                           

                        Rectangle {
                            anchors.fill: parent

                            color: {
                                if(isSelected) {
                                    return darkHighlight
                                }
                                if(isHighlighted) {
                                    return lightHighlight
                                }
                                return (index & 1) ? lightShade : lightAltShade;
                            }

                            RowLayout {
                                anchors.fill: parent

                                Text {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.margins: marginSize
                                    text: role_name
                                    font.bold: true
                                    font.pointSize: smallFont
                                }
                                Text {
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.fillHeight: true
                                    Layout.margins: marginSize
                                    width: 100
                                    text: role_state_desc
                                    font.pointSize: smallFont
                                }
                                ProgressBar {
                                    id: progressBar
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.fillHeight: true
                                    Layout.margins: marginSize
                                    width: 100
                                    from: 0
                                    to: role_maxstep
                                    property alias containsMouse: mouseAreaBar.containsMouse
                                        
                                    property var roleStep: role_step
                                    onRoleStepChanged: {
                                        value = roleStep;
                                    }                                       
                                        
                                    MouseArea {
                                        id: mouseAreaBar
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        acceptedButtons: Qt.RightButton | Qt.LeftButton
                                        onPressed: { onMousePress(); }
                                        onClicked: { onMouseClick(mouse); }
                                    }                                       
                                }
                                Button {
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.preferredHeight: iconsSize
                                    Layout.preferredWidth: iconsSize
                                    padding: 0
                                    icon.source: "qrc:///start.png"
                                    enabled: canStart()
                                    onClicked: {
                                        context_model.startItemProgress(index)
                                    }
                                }
                                Button {
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.preferredHeight: iconsSize
                                    Layout.preferredWidth: iconsSize
                                    padding: 0
                                    icon.source: "qrc:///pause.png"
                                    enabled: canPause()
                                    onClicked: {
                                        context_model.pauseItemProgress(index)
                                    }
                                }
                                Button {
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.preferredHeight: iconsSize
                                    Layout.preferredWidth: iconsSize
                                    padding: 0
                                    icon.source: "qrc:///stop.png"
                                    enabled: canStop()
                                    onClicked: {
                                        context_model.stopItemProgress(index)
                                    }
                                }
                                Button {
                                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                    Layout.preferredHeight: iconsSize
                                    Layout.preferredWidth: iconsSize
                                    Layout.margins: marginSize
                                    padding: 0
                                    icon.source: "qrc:///delete.png"
                                    onClicked: {
                                        context_model.deleteItem(index)
                                    }
                                }
                                Item {
                                    Layout.margins: marginSize
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Button {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.buttonHeight
                        text: "Create Item"
                        onClicked: {
                            createWindow.visible = true;
                        }
                    }
                    Button {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.buttonHeight
                        text: "Delete Item"
                        onClicked: {
                            context_model.deleteItem(listView.currentIndex)
                        }
                    }
                }
            }
        }
    }

    ApplicationWindow {
        id: createWindow
        width: 300
        height: 80
        title: "Create Item"
        visible: false

        onVisibleChanged: {
            textInput.text = "";
            if(visible) {
                textInput.focus = true;
            }
            else {
                listView.focus = true;
            }
        }

        Rectangle {
            anchors.fill: parent
            color: darkShade
            Rectangle {
                anchors.margins: marginSize
                anchors.fill: parent
                color: lightShade
                ColumnLayout {
                    anchors.fill: parent
                    TextInput {
                        id: textInput
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        font.pointSize: largeFont
                        padding: marginSize
                        maximumLength: 25
                        selectionColor: darkHighlight
                        selectByMouse: true
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        Button {
                            Layout.preferredHeight: root.buttonHeight
                            Layout.fillWidth: true
                            text: "Create"
                            onClicked: {
                                context_model.createItem(textInput.displayText)
                                createWindow.visible = false;
                                listView.positionViewAtEnd()
                            }
                        }
                        Button {
                            Layout.preferredHeight: root.buttonHeight
                            Layout.fillWidth: true
                            text: "Cancel"
                            onClicked: {
                                createWindow.visible = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
