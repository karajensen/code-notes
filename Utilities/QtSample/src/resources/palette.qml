import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQml.Models 2.1

Rectangle {
    id: root
    width: 300
    height: 300
    color: "black"

    QtObject {
        id: colors
        readonly property color red: "red"
        readonly property color green: "green"
        readonly property color blue: "blue"
        readonly property color yellow: "yellow"
        readonly property color orange: "orange"
        readonly property color purple: "purple"
        readonly property color blueTwo: "blue"
    }

    function extractColorData(item) {
        var colorValues = new Array();
        var colorNames = new Array();

        for (var key in item) {
            const value = item[key];

            if (typeof(value.r) !== "undefined" && 
                typeof(value.g) !== "undefined" && 
                typeof(value.b) !== "undefined") {
                const index = colorValues.indexOf(value);
                if (index == -1) {
                    colorValues.push(value);
                    colorNames.push(key);
                }
                else {
                    colorNames[index] = colorNames[index] + "\n" + key;
                }
            }
        }

        return { values: colorValues, names : colorNames };
    }

    readonly property var colorData: extractColorData(colors)
    
    DelegateModel {
        id: delegateModel
        model: colorData.values.length

        delegate: Item {
            id: item

            readonly property int delegateIndex: DelegateModel.itemsIndex
            width: gridView.cellWidth
            height: gridView.cellHeight

            MouseArea {
                id: dragArea
                anchors.fill: parent

                pressAndHoldInterval: 150
                hoverEnabled: true

                readonly property alias delegateIndex: item.delegateIndex
                property bool dragging: false

                drag.target: dragging ? content : undefined
                drag.axis: Drag.XAndYAxis

                onClicked: {
                    gridView.currentIndex = gridView.currentIndex == index ? -1 : index;
                }

                onPressAndHold: {
                    gridView.currentIndex = -1;
                    dragging = true
                    content.opacity = 0.75;
                }
                
                onReleased: {
                    dragging = false
                    content.opacity = 1.0;
                }

                Rectangle {
                    id: content
                    width: gridView.cellWidth
                    height: gridView.cellHeight
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    color: colorData.values[index]
                    border.width: gridView.currentIndex == index ? 2 : 0
                    border.color: "white"

                    Drag.active: dragArea.dragging
                    Drag.source: dragArea
                    Drag.hotSpot.x: width / 2
                    Drag.hotSpot.y: height / 2

                    states: State  {
                        when: dragArea.dragging
                        ParentChange { 
                            target: content; 
                            parent: gridView
                        }
                        AnchorChanges {
                            target: content
                            anchors { horizontalCenter: undefined; verticalCenter: undefined }
                        }
                    }

                    Rectangle {
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        color: Qt.rgba(0.0, 0.0, 0.0, 0.3)
                        width: colorText.implicitWidth + 6
                        height: colorText.implicitHeight + 6

                        Text {
                            id: colorText
                            anchors.centerIn: parent
                            text: colorData.values[index].toString()
                            color: "white"
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

    GridView {
        id: gridView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: nameRect.top
        model: delegateModel
        cellHeight: 100
        cellWidth: 100
        currentIndex: -1
    }

    Rectangle {
        id: nameRect
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Qt.rgba(0.0, 0.0, 0.0, 0.85)
        height: visible ? nameText.implicitHeight + 6 : 0
        border.color: "white"
        border.width: 2
        visible: nameText.text.length > 0

        Text {
            id: nameText
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            text: gridView.currentIndex != -1 ? colorData.names[gridView.currentIndex] : ""
            color: "white"
        }
    }
}