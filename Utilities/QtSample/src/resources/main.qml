import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQml.Models 2.1
import SampleModel 1.0

Rectangle {
    id: root
    width: 560
    height: 260

    /** Style properties */
    readonly property int buttonHeight: 30
    readonly property int rowHeight: 25
    readonly property color darkShade: "#DDDDDD"
    readonly property color midShade: "#DFDFDF"
    readonly property color lightAltShade: "#F5F5F5"
    readonly property color lightShade: "white"
    readonly property color dragHighlight: "red"
    readonly property color darkHighlight: "#8EACFF"
    readonly property color midHighlight: "#B2C6FF"
    readonly property color lightHighlight: "#E0E8FF"
    readonly property int smallFont: 8
    readonly property int largeFont: 10
    readonly property int marginSize: 4
    readonly property int iconsSize: 16

    /** Test some model properties */
    property var sampleModel: context_model
    onSampleModelChanged: {
        if (sampleModel) {
            console.log("----------------------------------")
            console.log(Test.Enum.ONE + " " + Test.Enum.TWO + " " + Test.Enum.THREE);
            console.log(ObjectEnum.ONE + " " + ObjectEnum.TWO + " " + ObjectEnum.THREE);

            for(var i = 0; i < 3; i++) {
                console.log(sampleModel.intListTest[i] + " " + typeof(sampleModel.intListTest[i]));
                console.log(sampleModel.colorListTest[i] + " " + typeof(sampleModel.colorListTest[i]));
                console.log(sampleModel.objectListTest[i].id + " " + typeof(sampleModel.objectListTest[i]));
            }
            var test = sampleModel.returnObjectList();
            console.log("----------------------------------")
        }
    }

    /** Delegate model allows for drag/drop behaviour */
    DelegateModel {
        id: delegateModel
        model: sampleModel

        delegate: Item {
            id: control
            readonly property int delegateIndex: DelegateModel.itemsIndex
            readonly property bool isHighlighted: dragArea.containsMouse || progressBar.containsMouse
            readonly property bool isSelected: listView.currentIndex == index
            width: listView.width
            height: root.rowHeight

            /** Anything here can also be seen by the ListView delegate */
            readonly property bool canStart: role_state_value != SampleItemState.STEPPING
            readonly property bool canPause: role_state_value == SampleItemState.STEPPING
            readonly property bool canStop: role_state_value == SampleItemState.STEPPING ||
                role_state_value == SampleItemState.PAUSED
            
            /** Everything needs to be wrapped in a MouseArea */
            MouseArea {
                id: dragArea
                anchors.fill: parent
                pressAndHoldInterval: 250
                hoverEnabled: true
                acceptedButtons: Qt.RightButton | Qt.LeftButton

                readonly property alias delegateIndex: control.delegateIndex
                property int previousDelegateIndex: -1
                property bool dragging: false

                drag.target: dragging ? content : undefined
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: listView.height - parent.height

                onPressed: {
                    listView.currentIndex = index;
                }
                
                onPressAndHold: {
                    previousDelegateIndex = delegateIndex;
                    dragging = true
                }
                
                onReleased: {
                    dragging = false
                    if (previousDelegateIndex != delegateIndex) {
                        context_model.moveItems(previousDelegateIndex, delegateIndex);
                    }

                    listView.currentIndex = index;
                    if(mouse.button == Qt.RightButton) {
                        contextMenu.popup()
                    }
                }
     
                /** The visible elements that will drag */
                Rectangle {
                    id: content
                    width: listView.width
                    height: root.rowHeight

                    Drag.active: dragArea.dragging
                    Drag.source: dragArea
                    Drag.hotSpot.x: width / 2
                    Drag.hotSpot.y: height / 2

                    states: State  {
                        when: dragArea.dragging
                        ParentChange { 
                            target: content; 
                            parent: listView
                        }
                        AnchorChanges {
                            target: content
                            anchors { horizontalCenter: undefined; verticalCenter: undefined }
                        }
                    }

                    color: {
                        if(dragArea.dragging) {
                            return dragHighlight
                        }
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
                            enabled: control.canStart
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
                            enabled: control.canPause
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
                            enabled: control.canStop
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

                DropArea {
                    anchors.fill: parent
                    anchors.margins: 10
                    onEntered: {
                        delegateModel.items.move(
                            drag.source.delegateIndex, 
                            dragArea.delegateIndex);
                    }
                }
            }
        }
    }

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
                    model: delegateModel
                    clip: true
                    currentIndex: 0
                    focus: true

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
                            enabled: listView.currentItem != null && listView.currentItem.canStart
                            onTriggered: {
                                context_model.startItemProgress(listView.currentIndex);
                            }
                        }
                        MenuItem {
                            text: "Pause"
                            icon.source: "qrc:///pause.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            enabled: listView.currentItem != null && listView.currentItem.canPause
                            onTriggered: {
                                context_model.pauseItemProgress(listView.currentIndex);
                            }
                        }
                        MenuItem {
                            text: "Stop"
                            icon.source: "qrc:///stop.png"
                            icon.width: iconsSize
                            icon.height: iconsSize
                            enabled: listView.currentItem != null && listView.currentItem.canStop
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
