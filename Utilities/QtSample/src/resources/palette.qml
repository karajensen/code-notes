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
        readonly property color one: "red"
        readonly property color two: "green"
        readonly property color three: "blue"
        readonly property color four: "yellow"
        readonly property color five: "orange"
        readonly property color six: "purple"
        readonly property color seven: "blue"
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
    
    GridView {
        id: gridView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: nameRect.top
        model: colorData.values.length
        cellHeight: 100
        cellWidth: 100
        currentIndex: -1

        delegate: Rectangle {
            width: gridView.cellWidth
            height: gridView.cellHeight
            color: colorData.values[index]
            border.width: gridView.currentIndex == index ? 2 : 0
            border.color: "white"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    gridView.currentIndex = gridView.currentIndex == index ? -1 : index;
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