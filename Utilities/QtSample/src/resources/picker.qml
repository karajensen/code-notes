import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Rectangle {
    id: root
    width: 400
    height: 400
    color: "grey"

    property color selectedColor: Qt.rgba(0, 1, 1, 1)

    property bool _stopColorLoop: false
    property color _hue

    Component.onCompleted: {
        root._setPickerFromColor()
    }

    onSelectedColorChanged: {
        root._setPickerFromColor()
        console.info(root.selectedColor.toString().toUpperCase())
    }

    function _setPickerFromColor() {
        if (root._stopColorLoop) {
            return
        }
        root._stopColorLoop = true
        const brightness = 1.0 - root.selectedColor.hsvValue
        const saturation = root.selectedColor.hsvSaturation
        pickerHandle.y = (picker.height * brightness) - (pickerHandle.height / 2)
        pickerHandle.x = (picker.width * saturation) - (pickerHandle.width / 2)
        slider.value = Math.max(0, root.selectedColor.hsvHue)
        root._hue = _getGradientColor(hueGradient, slider.value)
        root._stopColorLoop = false
    }

    function _setColorFromPicker() {
        if (root._stopColorLoop) {
            return
        }
        root._stopColorLoop = true
        root._hue = _getGradientColor(hueGradient, slider.value)
        const handleX = pickerHandle.x + (pickerHandle.width / 2.0)
        const handleY = pickerHandle.y + (pickerHandle.height / 2.0)
        const saturation = _getGradientColor(saturationGradient.gradient, (handleX / picker.width))
        const brightness = _getGradientColor(brightnessGradient.gradient, (handleY / picker.height))
        root.selectedColor = Qt.tint(saturation, brightness)
        root._stopColorLoop = false
    }

    function _getGradientColor(gradient, value) {
        for (var i = 0; i < gradient.stops.length - 1; ++i) {
            if (gradient.stops[i].position <= value && value <= gradient.stops[i + 1].position) {
                const start = gradient.stops[i].position
                const end = gradient.stops[i + 1].position
                const startColor = gradient.stops[i].color
                const endColor = gradient.stops[i + 1].color
                const factor = (value - start) / (end - start)
                const r = startColor.r + factor * (endColor.r - startColor.r)
                const g = startColor.g + factor * (endColor.g - startColor.g)
                const b = startColor.b + factor * (endColor.b - startColor.b)
                const a = startColor.a + factor * (endColor.a - startColor.a)
                return Qt.rgba(r, g, b, a)
            }
        }
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        anchors.margins: 20

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            color: root.selectedColor
        }

        MouseArea {
            id: picker
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            drag.threshold: 0
            drag.target: pickerHandle
            drag.minimumX: -pickerHandle.width / 2
            drag.maximumX: picker.width - (pickerHandle.width / 2)
            drag.minimumY: -pickerHandle.height / 2
            drag.maximumY: picker.height - (pickerHandle.height / 2)

            LinearGradient {
                id: saturationGradient
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(parent.width, 0)

                gradient: Gradient {
                    GradientStop { 
                        position: 0.0
                        color: Qt.rgba(1, 1, 1, 1) 
                    }
                    GradientStop { 
                        position: 1.0
                        color: root._hue 
                    }
                }
            }
            
            LinearGradient {
                id: brightnessGradient
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(0, parent.height)

                gradient: Gradient {
                    GradientStop { 
                        position: 0.0
                        color: Qt.rgba(0, 0, 0, 0) 
                    }
                    GradientStop { 
                        position: 1.0
                        color: Qt.rgba(0, 0, 0, 1) 
                    }
                }
            }

            Item {
                id: pickerHandle
                width: 24
                height: width

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 4
                    border.width: 2
                    border.color: "black"
                    radius: width / 2
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    drag.threshold: 0
                    drag.target: pickerHandle
                    drag.minimumX: -pickerHandle.width / 2
                    drag.maximumX: picker.width - (pickerHandle.width / 2)
                    drag.minimumY: -pickerHandle.height / 2
                    drag.maximumY: picker.height - (pickerHandle.height / 2)

                    onPressed: pickerHandle.forceActiveFocus()
                    onPositionChanged: root._setColorFromPicker()
                }
            }

            onPressed: {
                pickerHandle.forceActiveFocus()
                pickerHandle.x = mouse.x - (pickerHandle.width / 2)
                pickerHandle.y = mouse.y - (pickerHandle.height / 2)
                root._setColorFromPicker()
            }

            onPositionChanged: {
                if (drag.active) {
                    root._setColorFromPicker()
                }
            }
        }

        Slider {
            id: slider
            Layout.fillWidth: true
            Layout.preferredHeight: 16
            padding: 0
            value: 0
            from: 0
            to: 1.0
            stepSize: 0.01
            onValueChanged: root._setColorFromPicker()

            handle: Rectangle {
                id: sliderHandle
                x: slider.visualPosition * (slider.availableWidth - width)
                y: (slider.availableHeight / 2) - (height / 2)
                radius: width / 2
                width: 16
                height: width
                color: root._hue
                border.color: "black"
                border.width: 2
            }

            background: Rectangle {
                width: slider.availableWidth
                height: slider.availableHeight
                gradient: hueGradient
            }

            Gradient {
                id: hueGradient
                orientation: Qt.Horizontal
                GradientStop { 
                    position: 0.0
                    color: Qt.rgba(1, 0, 0, 1) 
                }
                GradientStop { 
                    position: 1.0 / 6.0
                    color: Qt.rgba(1, 1, 0, 1) 
                }
                GradientStop { 
                    position: 2.0 / 6.0
                    color: Qt.rgba(0, 1, 0, 1) 
                }
                GradientStop { 
                    position: 3.0 / 6.0;
                    color: Qt.rgba(0, 1, 1, 1) 
                }
                GradientStop { 
                    position: 4.0 / 6.0
                    color: Qt.rgba(0, 0, 1, 1) 
                }
                GradientStop { 
                    position: 5.0 / 6.0
                    color: Qt.rgba(1, 0, 1, 1) 
                }
                GradientStop { 
                    position: 1.0
                    color: Qt.rgba(1, 0, 0, 1) 
                }
            }
        }
    }
}