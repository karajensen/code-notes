import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import SampleModel 1.0

Rectangle {
    id: root
    width: 560
    height: 260

    /** Style properties */
    property int buttonHeight: 30
    property int rowHeight: 30
    property color darkShade: "#DDDDDD"
    property color midShade: "#DFDFDF"
    property color lightAltShade: "#F5F5F5"
    property color lightShade: "white"
    property color darkHighlight: "#8EACFF"
    property color midHighlight: "#B2C6FF"
    property color lightHighlight: "#E0E8FF"
    property int smallFont: 10
    property int largeFont: 14
    property int marginSize: 4
    property int iconsSize: 16

    Rectangle {
        anchors.fill: parent
        color: darkShade

        Rectangle {
            anchors.margins: marginSize
            anchors.fill: parent
            color: lightShade

            ColumnLayout {
                anchors.fill: parent
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ListView {
                        id: listView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: context_model
                        clip: true
                        currentIndex: 0
                        focus: true

                        Menu {
                            id: contextMenu
                            visible: false
                            MenuItem {
                                text: "Start"
                                iconSource: "qrc:///start.png"
                                enabled: {
                                    return listView.currentItem != null && listView.currentItem.canStart()
                                }
                                onTriggered: {
                                    context_model.startItemProgress(listView.currentIndex);
                                }
                            }
                            MenuItem {
                                text: "Pause"
                                iconSource: "qrc:///pause.png"
                                enabled: {
                                    return listView.currentItem != null && listView.currentItem.canPause()
                                }
                                onTriggered: {
                                    context_model.pauseItemProgress(listView.currentIndex);
                                }
                            }
                            MenuItem {
                                text: "Stop"
                                iconSource: "qrc:///stop.png"
                                enabled: {
                                    return listView.currentItem != null && listView.currentItem.canStop()
                                }
                                onTriggered: {
                                    context_model.stopItemProgress(listView.currentIndex);
                                }
                            }
                            MenuItem {
                                text: "Delete"
                                iconSource: "qrc:///trashbin.png"
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
                                    anchors.margins: marginSize
                                    Text {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                        Layout.alignment: Qt.AlignVCenter
                                        text: role_name
                                        font.bold: true
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: smallFont
                                    }
                                    Text {
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        Layout.fillHeight: true
                                        width: 100
                                        text: role_state_desc
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: smallFont
                                    }
                                    ProgressBar {
                                        id: progressBar
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        height: 20
                                        width: 100
                                        maximumValue: role_maxstep
                                        minimumValue: 0
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
                                        
                                        style: ProgressBarStyle {
                                            id: style
                                            background: Rectangle {
                                                radius: 2
                                                color: midShade
                                                border.color: darkShade
                                                border.width: 1
                                                implicitWidth: 100
                                                implicitHeight: 20
                                            }
                                            progress: Rectangle {
                                                color: midHighlight
                                                border.color: darkHighlight
                                            }
                                        }
                                    }
                                    Button {
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        Layout.fillHeight: true
                                        iconSource: "qrc:///start.png"
                                        width: iconsSize
                                        height: iconsSize
                                        enabled: canStart()
                                        onClicked: {
                                            context_model.startItemProgress(index)
                                        }
                                    }
                                    Button {
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        iconSource: "qrc:///pause.png"
                                        width: iconsSize
                                        height: iconsSize
                                        enabled: canPause()
                                        onClicked: {
                                            context_model.pauseItemProgress(index)
                                        }
                                    }
                                    Button {
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        iconSource: "qrc:///stop.png"
                                        width: iconsSize
                                        height: iconsSize
                                        enabled: canStop()
                                        onClicked: {
                                            context_model.stopItemProgress(index)
                                        }
                                    }
                                    Button {
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        iconSource: "qrc:///delete.png"
                                        width: iconsSize
                                        height: iconsSize
                                        onClicked: {
                                            context_model.deleteItem(index)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Dialog {
                    id: createDialog
                    visible: false
                    title: "Create New Sample Item"
                    width: 300
                    height: 80

                    onVisibleChanged: {
                        textInput.text = "";
                        if(visible) {
                            textInput.focus = true;
                        }
                        else {
                            listView.focus = true;
                        }
                    }

                    contentItem: Rectangle {
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
                                            createDialog.visible = false;
                                            listView.positionViewAtEnd()
                                        }
                                    }
                                    Button {
                                        Layout.preferredHeight: root.buttonHeight
                                        Layout.fillWidth: true
                                        text: "Cancel"
                                        onClicked: {
                                            createDialog.visible = false;
                                        }
                                    }
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
                            createDialog.visible = true;
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
}
