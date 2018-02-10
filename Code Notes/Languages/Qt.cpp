////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT PROJECT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QMAKE
• Run from top level directory of the project  
• Generates Makefiles from a project files (.pro)
• Includes build rules for moc and uic

PROJECT FILES (.pro)
• List of source/header files, libraries, include paths, configuration info
**************************************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.exec(); // Start the event loop
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT COMPONENTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QString
QString str = "str";
str.split(" "); // Returns QStringList of string split by spaces

// QStringList
QStringList lst; // Inherits from QList<QString>, specifically for strings
lst.join(" ")    // Returns a combined string seperated by spaces
lst.append(lst2) // Adds a new string list to the end

// QList
QList<int> lst; // Fast index-based access, insertions and removals
lst << 1 << 2;  // Allows streaming into container

// QListIterator
QListIterator<int> iter(myList);
while(iter.hasNext()) { iter.next(); }

//==========================================================================================================
//WIDGETS
//==========================================================================================================

// QWidget
QWidget widget; // Root widget used as a window
widget.setWindowTitle("Title");
widget.show();
widget.setLayout(layout); // Add a layout to the window, automatically parents

// QLabel
QLabel lbl("Message"); // Allows use of html tags to customise text

// QPushButton
QPushButton btn("Text");
QObject::connect(button, SIGNAL(clicked()), &app, SLOT(myFn()));  // Connect to button's click event

// QSpinBox
QSpinBox spinbox;
spinbox.setRange(min, max);
spinBox.setValue(value);
QObject::connect(spinBox, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

// QSlider 
QSlider slider(Qt::Horizontal);
slider.setRange(min, max);
slider.setValue(value);
QObject::connect(slider, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

//==========================================================================================================
//LAYOUTS
//==========================================================================================================

// QHBoxLayout: lays out widgets horizontally from left to right
QHBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout: lays out widgets vertically from top to bottom

// QGridLayout: lays out widgets in a grid.

//==========================================================================================================
//FILE SYSTEM
//==========================================================================================================

// Read from a file, no need to close it
QFile file("myFile.txt");
if(file.open(QIODevice::ReadOnly))
{
    QTextStream stream(&file);
    QString line = stream.readLine(); // read the next line
    while(!line.isNull())
    {
        line = stream.readLine();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT OBJECTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT MODELING LANGUAGE (QML)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//• QML: Markup language for user interfaces made up of elements, uses Javascript for scripting

import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Qt.quit()  // Quits the application

//==========================================================================================================
//QML PROPERTIES
//==========================================================================================================
id: nameOfControl                         // unique id of element, can be used to access it
objectName: "UserName"                    // user defined name
anchors.left: parent.left                 // don't use with RowLayout, use Layout.fillWidth
anchors.right: parent.right               // don't use with RowLayout, use Layout.fillWidth
anchors.left: parent.left                 // don't use with ColumnLayout, use Layout.fillHeight
anchors.right: parent.right               // don't use with ColumnLayout, use Layout.fillHeight
anchors.fill: parent                      // completely fills to parent
anchors.margins: 1                        // adds margins between the anchor
heigh: 30                                 // avoid as easily ovewritten
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

//==========================================================================================================
//QML ELEMENTS
//==========================================================================================================

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QT MODELS / VIEWS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
**************************************************************************************************************/
