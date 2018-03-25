/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODULES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QtCore               Core non-graphical classes used by other modules
QtGUI                Base classes for graphical user interface (GUI) components. Includes OpenGL
QtMultimedia         Classes for audio, video, radio and camera functionality
QtMultimediaWidgets  Widget-based classes for implementing multimedia functionality
QtNetwork            Classes to make network programming easier and more portable
QtQML                Classes for QML and JavaScript languages
QtQuick              A declarative framework for building highly dynamic applications with custom UI
QtQuickControls      Reusable Qt Quick based UI controls to create classic desktop-style user interfaces
QtQuickDialogs       Types for creating and interacting with system dialogs from a Qt Quick application
QtQuickLayouts       Layouts are items that are used to arrange Qt Quick 2 based items in the UI
QtSQL                Classes for database integration using SQL
QtTest               Classes for unit testing Qt applications and libraries
QtWidgets            Classes to extend Qt GUI with C++ widgets

LIBRARY: Set of functions, organized in classes, that does some work and then returns control to the client
FRAMEWORK: An abstract design that you need to insert into, through inheritance or callbacks, that the framework then calls
TOOLKIT: More focused library, used almost exclusively for graphical widgets, and GUI components
**************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LICENSING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
COMMERCIAL:
• Official Qt Support Helpdesk
• Keep your application private
• Full rights to proprietary Qt source code modifications

GENERAL PUBLIC LICENSE (GPL):
• Requires releasing the source code of your application if distributing the open source software 
• All portions of the project must be under GPL as well
• Can use static linking
• Needs to include qt source code or instructions on how to access it

LESSER GENERAL PUBLIC LICENSE (LGPL):
• Allows distributing the open source software with your application without releasing the application source
• LGPL open source software must be re-distributed as LGPU, other portions of project may have different licences
• Possible to keep your application private with dynamic linking
• Needs to include qt source code or instructions on how to access it

QT FOR APPLICATION DEVELOPMENT: 
• Cross platform development for desktop and mobile
• Can be licensed under commercial and open source licenses (GPU / LGPU)
• Some modules GPU only: QtDataVisualization / QtCharts / Tooling (if modifications are done)
  
QT FOR DEVICE CREATION: 
• Used with embedded devices
• Only under commercial licence to allow integration with proprietary code 
  
GPLv2 vs. GPLv3
• GPLv3 added compatibility regulations that make it easier to combine GPL code and code under different licenses
• GPLv3 adds regulations for digital rights management were added to keep GPL software from being changed at will
• GPLv3 adds an explicit patent license/copyright so that no one can profit from them
  
LGPLv2.1 vs. LGPLv3
• LGPLv3 closes loophole of locked-down consumer devices preventing users from installing
  modified versions of the library on the device
**************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FRAMEWORK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTimer timer;
    timer.setInterval(10);
    QObject::connect(&timer, &QTimer::timeout, []() { /*tick*/ });
    timer.start();
    app.exec(); // Start the event loop
}

qDebug() << "Message\n"; // Prints to stderr output
Q_ASSERT(expression);
Q_ASSERT_X(expression, "divide", "division by zero");

qobject_cast<MyQObject*>(qObj); // dynamic_cast without requiring RTTI

forever { break; }

//===============================================================================================================
// QT COMPONENTS
//===============================================================================================================

// QString
// Most also overload using a char, regex etc
QString str("str");
str.split(" "); // Returns QStringList of string split by spaces
str.append("str", n); // Adds n characters to the end of the string, returns QString& for chaining
str.append("str"); // Adds to the end of the string, returns QString& for chaining
str.arg(value); // Returns QString copy with %n replaced with value (eg. %1, %2...), printf with %n
str.at(n); // Returns QChar at index
str.back(); // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.begin(); // Returns iterator or const_iterator
str.capacity(); // Returns maximum number of characters that can be stored without forcing a reallocation
str.chop(n); // Removes n chars from end of the string, if n >= size, string becomes empty
str.chopped(n); // Removes n chars from end of the string and returns QString copy, n >= size is undefined
str.clear(); // Makes string empty
str.compare("str", Qt::CaseInsensitive); // Returns 0 if they match 
str.toUtf8().constData(); // Convert to const char*
str.contains("str", Qt::CaseInsensitive); // Returns true if contains substring 'str'
str.count("str", Qt::CaseInsensitive); // Returns count of substring, will count overlaps
str.end(); // Returns iterator or const_iterator
str.endsWith("str", Qt::CaseInsensitive); // Returns true if ends with 'str'
str.fill('c', n); // Resizes string to n and fills with character, without n will fill to current size
str.font(); // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.indexOf("str", n); // Searches for 'str' from index n, returns index, or -1 if not found
str.insert(n, "str"); // Inserts 'str' at index n, returns QString&, auto resizes if n >= size
QString::asprintf("%i", n); // QString version of printf, uses same modifiers
QString::compare(str1, str2, Qt::CaseInsensitive); // Returns 0 if they match
 
// QTextStream
QTextStream(&str) << "str" << value; // QString streamstream

//===============================================================================================================
// QT CONTAINERS
//===============================================================================================================
/*************************************************************************************************************
• Type T must provide default constructor, copy constructor, assignment operator, else use T*
• If container uses Key, type T must provide operator<
• Iterators can become invalid after insertion/removal, due to changing internals and implicit sharing
 
----------------------------------------------------------------------
CONTAINER          Access       Insertion  Prepending  Appending
----------------------------------------------------------------------
QLinkedList<T>     O(n)         O(1)       O(1)        O(1)
QList<T>           O(1)         O(n)       O(1)        O(1)
QVector<T>         O(1)         O(n)       O(n)        O(1)
QMap<Key, T>       O(log n)     O(logn)    -           -
QMultiMap<Key, T>  O(log n)     O(logn)    -           -
QHash<Key, T>      O(1) O(n)    O(n)       -           -
QSet<Key>          O(1) O(n)    O(n)       -           -
**************************************************************************************************************/

// CONTAINER FOREACH
// Auto takes copy of container at start of loop
// Modifying container during loop won't affect it due to implicit sharing
foreach (const auto& value, container) {}
foreach (const auto& value, map) {}
foreach (const auto& key, map.keys()) {}
foreach (const auto& key, multimap.uniqueKeys()) { foreach (const auto& value, multimap.values(key)) {} }

// QList<T>
// Pre-allocates memory both at start and end, fast index access, insertions and removals
// Array of T if sizeof(T) <= sizeof(void*) and T is Q_PRIMITIVE_TYPE or Q_MOVABLE_TYPE, else array of T* on heap
QList<T> lst;
lst << 1 << 2;  // Allows streaming into container

// QStringList
// Inherits from QList<QString>
QStringList lst;
lst.join(" ")    // Returns a combined string seperated by spaces
lst.append(lst2) // Adds a new string list to the end

// QLinkedList<T>
// Uses iterators to access members, segmented allocations
// Better performance than QList when inserting in the middle of a huge list

// QVector<T>
// Continuous memory allocation, reallocates whole block when resizing
// Fast index access and add/remove from back, slow insert and add/remove from front

// QStack<T>
// Inherits QVector<T>

// QQueue<T>
// Inherits QList<T>

// QMap<Key, T>
// Dictionary, auto stores its data in Key order

// QMultiMap<Key, T>
// Inherits QMap<Key, T>

// QHash<Key, T>
// Hash map, no auto sorting
// Uses hash key qHash(key) % QHash::capacity() (number of buckets)

// QMultiHash<Key, T>
// Inherits QHash<Key, T>

// QSet<T>
// Uses hash key qHash(key) % QHash::capacity() (number of buckets)

// QCache<Key, T>
// Uses hash key qHash(key) % QHash::capacity() (number of buckets)

// QContiguousCache<Key, T>

//===============================================================================================================
// QT ITERATORS
//===============================================================================================================
/*************************************************************************************************************
CONTAINER           JAVA-STYLE READ-ONLY    JAVA-STYLE MUTABLE               STL-STYLE ITERATORS
QList<T>            QListIterator<T>        QMutableListIterator<T>          QList<T>::iterator   
QQueue<T>           QListIterator<T>        QMutableListIterator<T>          QQueue<T>::iterator     
QLinkedList<T>      QLinkedListIterator<T>  QMutableLinkedListIterator<T>    QLinkedList<T>::iterator   
QVector<T>          QVectorIterator<T>      QMutableVectorIterator<T>        QVector<T>::iterator    
QStack<T>           QVectorIterator<T>      QMutableVectorIterator<T>        QStack<T>::iterator     
QSet<T>             QSetIterator<T>         QMutableSetIterator<T>           QSet<T>::iterator   
QMap<Key, T>        QMapIterator<Key, T>    QMutableMapIterator<Key, T>      QMap<Key, T>::iterator   
QMultiMap<Key, T>   QMapIterator<Key, T>    QMutableMapIterator<Key, T>      QMultiMap<Key, T>::iterator   
QHash<Key, T>       QHashIterator<Key, T>   QMutableHashIterator<Key, T>     QHash<Key, T>::iterator    
QMultiHash<Key, T>  QHashIterator<Key, T>   QMutableHashIterator<Key, T>     QMultiHash<Key, T>::iterator   
**************************************************************************************************************/

// STL-STYLED ITERATORS
// Point to actual values
// Support reverse_iterator, const_iterator and iterator maths
*itr                    // Return value
++i / --i               // Increment/decrement
itr.begin()             // Start of container
itr.end()               // One after end of container
itr.key()               // Key-based only, returns const Key&
  
// JAVA-STYLED ITERATORS
// Point to position between values
itr.toFront()           // Sets iterator as begin
itr.toBack()            // Sets iterator as end
itr.hasNext()           // Returns true if the iterator isn't at the back of the list
itr.next()              // Returns the next item and advances the iterator by one position
itr.peekNext()          // Returns the next item without moving the iterator
itr.hasPrevious()       // Returns true if the iterator isn't at the front of the list
itr.previous()          // Returns the previous item and moves the iterator back by one position
itr.peekPrevious()      // Returns the previous item without moving the iterator
itr.value()             // Mutable or key-based only, Returns T& or const T&
itr.setValue(value)     // Mutable only, Takes in const T&
itr.insert(value)       // Mutable, non-key based only, Takes in const T&, inserts one after itr
itr.findNext(value)     // Mutable or key-based only, from itr, searches forward for value, returns if found
itr.findPrevious(value) // Mutable or key-based only, from itr, searches backwards for value, returns if found
itr.remove()            // Mutable only, Removes the value, does not invalidate itr
itr.key()               // Key-based only, Returns const Key&

//===============================================================================================================
// QT SMART POINTERS
//===============================================================================================================
 
// QSharedDataPointer
// Requires T to be derived from QSharedData
// Thread-safe reference counting pointer to an implicitly shared object
// Calling non-const class methods auto detaches ptr from shared block
QSharedDataPointer<T> ptr(new T());
QSharedDataPointer<T> ptr2(ptr); // Implicity shares data with ptr
ptr.constData();         // Returns const T*
ptr.data();              // Returns T* or const T*
ptr.detach();            // Detaches object from shared data

// QExplicitlySharedDataPointer
// Requires T to be derived from QSharedData
// Thread-safe reference counting pointer to an implicitly shared object
// Calling non-const class methods DOES NOT auto detach ptr from shared block
QExplicitlySharedDataPointer<T> ptr(new T());
QExplicitlySharedDataPointer<T> ptr2(ptr); // Implicity shares data with ptr
ptr.constData();         // Returns const T*
ptr.data();              // Returns T* or const T*
ptr.detach();            // Detaches object from shared data

// QSharedPointer  
// Thread-safe reference counting shared pointer with control block
QSharedPointer<T> ptr(new T());
QSharedPointer<T> ptr(new T(), [](T* data){}); // With custom deleter
auto ptr = QSharedPointer<T>::create(); // Allocates control block and memory together
ptr.clear();             // Clears pointer and decrements ref count
ptr.constCast();         // Returns QSharedPointer<T> with T stripped of const
ptr.objectCast<T2>();    // Returns QSharedPointer<T2> by doing a qobject_cast
ptr.dynamicCast<T2>();   // Returns QSharedPointer<T2>
ptr.staticCast<T2>();    // Returns QSharedPointer<T2>
ptr.toWeakRef();         // Returns QWeakPointer<T>
ptr.isNull();            // Returns if null
ptr.data();              // Returns T*
ptr.reset();
ptr.reset(new T());

// QWeakPointer
// Holds a weak reference to a QSharedPointer
QWeakPointer<T> ptr(mySharedPtr->toWeakRef());
ptr.clear();             // Clears pointer
ptr.data();              // Returns T*, does not cast to QSharedPointer<T> or check if valid
ptr.isNull();            // Returns if null
ptr.lock();              // Returns QSharedPointer<T>, same as toStrongRef
ptr.toStrongRef();       // Returns QSharedPointer<T>, same as lock

// QScopedPointer
QScopedPointer<T> ptr(new T());
ptr.take();             // Returns T* and sets pointer to null
ptr.data();             // Returns T*
ptr.isNull();           // Returns if null
ptr.reset();
ptr.reset(new T());

// QScopedArrayPointer
QScopedArrayPointer<T> ptr(new T[n]);
ptr[index];             // Returns T& at index
ptr.take();             // Returns T* and sets pointer to null
ptr.data();             // Returns T*
ptr.isNull();           // Returns if null
ptr.reset();
ptr.reset(new T[n]);

// QPointer
// Same as QScopedPointer, kept for legacy support
QPointer<T> ptr(new T());
ptr.clear();             // Clears pointer and decrements ref count
ptr.isNull();            // Returns if null
ptr.data();              // Returns T*

//===============================================================================================================
// QT WIDGETS
//===============================================================================================================

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

//===============================================================================================================
// QT LAYOUTS
//===============================================================================================================

// QHBoxLayout: lays out widgets horizontally from left to right
QHBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout: lays out widgets vertically from top to bottom
QVBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QGridLayout: lays out widgets in a grid.
QGridLayout layout;
layout.addWidget(spinBox, r, c); // Add a widget to the layout, automatically parents and resizes

//===============================================================================================================
// IMPLICIT SHARING (COPY-ON-WRITE)
//===============================================================================================================

// • Objects share the same memory in a 'shared block' if have the same values
// • Automatically detaches the object from a shared block when object changes and ref count is > 1
// • Qt classes use it internally, doesn't require a shared data pointer for it to happen
// • Can be dangerous for iterators when container detaches from shared block:
QVector<int> a, b;
QVector<int>::iterator i = a.begin();
b = a;    // Make both implicity share
*i = 10;  // Iterator points to share block, will modify both a and b
a[0] = 5; // Detach a by modifying only it, i still points to b though

//===============================================================================================================
// FILE SYSTEM
//===============================================================================================================

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELING LANGUAGE (QML)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

Qt.quit() // Quits the application
console.log("Message")

//===============================================================================================================
// QML PROPERTIES
//===============================================================================================================

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
property alias myProperty2: myProperty    // alias for property
    
/* Called when the element has been instantiated */
Component.onCompleted: {}

/* Called when the element is destroyed */
Component.onDestruction: {}

/* Called when the property 'color' has changed */
onColorChanged: {}

/* Javascript custom function */
function myFunction(x, y) {
    return x + y;
}

//===============================================================================================================
// QML COMPONENTS
//===============================================================================================================

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

//===============================================================================================================
// QML LAYOUTS
//===============================================================================================================

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

//===============================================================================================================
// QML WIDGETS
//===============================================================================================================

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
// QT OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QOBJECTS:
• Base class of all Qt objects, organised in an object tree
• Doesn't have a copy constructor or assignment operator
• Meta Object Compilier (moc) uses Q_OBJECT macro to generate extra data/features to use in framework:
    - Ability to use qobject_cast, signals and slots
    - QObject::metaObject returns the associated meta-object for the class
    - QMetaObject::className returns the class name as a string (without using RTTI)
    - QObject::inherits returns whether an instance of another QObject class
    - QObject::setProperty / QObject::property dynamically set and get properties by name
    - QMetaObject::newInstance constructs a new instance of the class

QOBJECT LIMITATIONS:
• Only signals and slots can live in the signals and slots sections
• Class templates cannot have signals or slots
• Signal/Slot return types cannot be references
• Multiple Inheritance requires QObject to be first
• Virtual inheritance with QObject is not supported
• Moc doesn't expand #define: cannot use a macro to declare a signal/slot or used as a signal/slot parameter
• Function Pointers cannot be direct signal/slot Parameters, work-around is to typedef it
• Enums/typedefs cannot be forward decl for signal/slot parameters
• Nested Classes cannot have signals or slots

PARENT-CHILD RELATIONSHIP:
• Parent needs to be explicitly deleted, either by delete or stack scope
• Children deleted by parent automatically, if child is deleted first, parent is notified
• Children should not be created on the stack unless deleted first, as parent assumes children are on heap
**************************************************************************************************************/

class MyClass : public QObject
{
    Q_OBJECT // required for all moc provided features
    Q_CLASSINFO("Author", "Name") // attach additional name/value pairs to the class's meta-object

public:
    MyClass(QObject *parent = 0);
    ~MyClass();
    
    // Enums must start with capital letter
    enum MyEnum { ONE, TWO, THREE };
    Q_ENUMS(MyEnum)
    
    // Use Enum with QML
    // Use 'import MyEnums 1.0' and 'MyEnum.ONE'
    static registerEnum() { qmlRegisterType<MyClass>("MyEnums", 1, 0, "MyEnum"); }
    
    // Use Enum with signals/slots
    Q_PROPERTY(MyEnum m_enum READ getEnum WRITE setEnum)
    void setEnum(MyEnum value) { m_enum = value; }
    MyEnum getEnum() const { return m_enum; }

signals:
    void mySignal();

public slots:
    void mySlot();
    void mySlot(void (*fn)(void *)); // Cannot do
    void mySlot(MyFn fn);            // Can do
    
private:
    MyEnum m_enum;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELS / VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
**************************************************************************************************************/

// CREATING CUSTOM MODEL
class MyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    virtual ~MyModel() = default;
    MyModel(QObject* parent = nullptr)
        : QAbstractListModel(parent)
    {
    }

    enum ModelRoles
    {
        MyRole1 = Qt::UserRole + 1,
        MyRole2
    };

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent);
        return static_cast<int>(m_items.size());    
    }
    
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (index.row() >= 0 && index.row() < static_cast<int>(m_items.size()))
        {
            const auto& item = m_items[index.row()];
            if (role == Role1)
            {
                return item->getRole1();
            }
            else if (role == Role2)
            {
                return item->getRole2();
            }
        }
        return QVariant();    
    }
    
    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[MyRole1] = "role_one";
        roles[MyRole2] = "role_two";
        return roles;    
    }
    
    MyItem* rowToItem(int row) const
    {
        return row >= 0 && row < static_cast<int>(m_items.size())
            ? m_items[row].get() : nullptr;
    }
    
    Q_INVOKABLE void qmlFunction(int row)
    {
        if (auto item = rowToItem(row))
        {
            item->doSomethingToChangeData();
            const auto& modelIndex = index(row);
            emit dataChanged(modelIndex, modelIndex);
        }
    }
    
    void createItem()
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items.push_back(std::make_unique<MyItem>());
        endInsertRows();
    }

    void deleteItem(int row)
    {
        if (row >= 0 && row < static_cast<int>(m_items.size()))
        {
            beginRemoveRows(QModelIndex(), row, row);
            auto itr = m_items.begin();
            std::advance(itr, row);
            m_items.erase(itr);
            endRemoveRows();
        }
    }    

private:
    std::vector<MyItem> m_items;
};

// USING MODEL IN QML
ScrollView {
    Layout.fillWidth: true
    Layout.fillHeight: true
    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: context_model

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
                text: role_name
            }
        }
    }
}

// ATTACHING MODEL TO QML VIEW
QQuickView view;
view.rootContext()->setContextProperty("context_model", &model);
view.setSource(QUrl("qrc:/main.qml"));
view.show();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESOURCES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Allows storing resource files as binary in executable
• To add to exe, add RESOURCES = myResources.qrc to .pro file
• Access using qrc:///file.ext, paths relative to .qrc file
**************************************************************************************************************/

<RCC>
    <qresource prefix="/MyResources"> // Prefix optional
        <file>file.ext</file>
        <file alias="file.ext">path/file.ext</file>
    </qresource>
    <qresource prefix="/MyResources" lang="fr">
        <file>file.ext</file> // Will use instead if language matches
    </qresource>    
</RCC>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMAKE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Run from top level directory of the project  
• Generates Makefiles from a project files (.pro) and includes build rules for moc and uic
• Project files include a list of source/header files, libraries, include paths, configuration info
• Project files can be auto-generated from Qt Creator wizard and qmake
• Should only use directory separator / regardless of platform

META-OBJECT COMPILER (MOC):
• Reads a .h file for classes with Q_OBJECT inheriting QObject
• Creates a .cpp file with meta-object code required for signals/slots, RTTI and dynamic properties
• Must be compiled and linked with the class

USER INTERFACE COMPILER (UIC):
• Reads a .ui file as generated by Qt Designer and creates a .h file
**************************************************************************************************************/

//===============================================================================================================
// RUNNING QMAKE
//===============================================================================================================

qmake -makefile [options] file1.pro file2.pro // output will be Makefiles (default)
qmake -project  [options] file.pro MyDir      // output will be a project (*.pro) file, accepts dirs
make /*or*/ nmake                             // generates exe from Makefiles

//GENERAL OPTIONS
-help               // output help information
-o [outputname]     // change the name of the output file
-d                  // output debug information
-t [template]       // change the template used in the project file (only after it's processed)
-Wall               // output all warnings
-Wnone              // output no warnings
-Wparser            // output only parser warnings
-Wlogic             // output warnings for problems in project file
-spec macx-g++      // change the platform to mac
-E                  // preprocess only; do not generate meta-object code

//MAKEFILE MODE OPTIONS
"CONFIG+=test"           // pass extra assignments, processed before .pro file
"CONFIG+=test" -after    // extra assignments processed after .pro file
-nocache                 // .qmake.cache file ignored
-nodepend                // don't generate dependency information	

//PROJECT MODE OPTIONS
-r                       // look through supplied directories excursively
-nopwd                   // only use supplied files, do not use current working directory

//===============================================================================================================
// PROJECT CONFIGURATION
//===============================================================================================================

TARGET = hello                 // name of the executable
VERSION = 1.2.3                
LANGUAGE  = C++
DESTDIR = "c:/MyPath"          // The directory to output the target executable
CONFIG += debug                // add configuration information to project
TEMPLATE = app                 // sets what type of project to build, overrides previously set
PRECOMPILED_HEADER = stdafx.h  
HEADERS += hello.h             	
FORMS = hello.ui               
SOURCES = hello.cpp main.cpp   // Can also just list instead of +=, use \ for newlines      
INCLUDEPATH += "c:/MyPath"     
MOC_DIR = "c:/MyPath"          // Where intermediate moc files are placed
OBJECTS_DIR = "c:/MyPath"      // Where intermediate objects are placed
DEFINES += MY_DEFINE           // Add a new #define MY_DEFINE, can be removed with -=
QT += xml                      // Add qt libraries to link against, core and gui already there by default
QT += widgets designer         // Requires lib template, builds a qt designer plugin

//OPERATORS
# This is a comment       // use &&LITERAL_HASH for actual #
$$value                   // Get contents of variable
$${value}                 // Same as $$value but allows adding to string values (eg. DEFINES = name_$${value})
$$[qmake_property]        // Get contents of qmake property
$$(env_variable)          // Get contents of environment variable when qmake is run
$(env_variable)           // Get contents of environment variable when makefiles are processed
$$replace_fn()            // Get return of a replace function
= value                   // Replace the value	
-= value                  // Subtract the value
+= value                  // Add the value
*= value                  // Only add if it hasn't already been added
~= expression             // Replaces any values that match a regular expression
MY_VAR = 0                // Create a new variable, all are lists by default even if one item assigned
MY_VAR = one two three    // Create a new variable with strings

//CONFIG OPTIONS
qt                        // Link against qt library
release                   // Build project in release, if 'debug' is also used, last one is only used
debug                     // Build project in debug, if 'release' is also used, last one is only used
debug_and_release         // The project is prepared to be built in both debug and release modes
debug_and_release_target  // Put debug/release builds in seperate directories (default)
build_all                 // Used with debug_and_release to build both debug and release
autogen_precompile_source // Automatically generates precompiled header files specified in .pro file
ordered                   // Used with subdirs template, directories should be processed in a given order
precompile_header         // Enables precompiled headers support
warn_on                   // Increase warning level from default
warn_off                  // Decrease warning level from default
exceptions                // Exception support enabled (default)
exceptions_off            // Exception support disabled
rtti                      // RTTI support enabled (by default, compiler default is used)
rtti_off                  // RTTI support disabled (by default, compiler default is used)
stl                       // STL support enabled (by default, compiler default is used)
stl_off                   // STL support disabled (by default, compiler default is used)
thread                    // Thread support is enabled (enabled by default)
c++11                     // C++11 support enabled, by default is disabled
c++14                     // C++14 support enabled, by default is disabled
opengl                    // Includes opengl support
windows                   // app Template only, Target is a Windows GUID application
console                   // app Template only, Target is a Win32 console application
testcase                  // app Template only, Target is an automated test
dll                       // lib Template only, The library is a shared library (dll).
staticlib                 // lib Template only, The library is a static library.
plugin                    // lib Template only, The library is a plugin.

//TEMPLATE OPTIONS
app                           // creates Makefile to build an application (default)
lib                           // creates Makefile to build a library
aux                           // creates Makefile to build nothing, used fo interpreted languages
subdirs                       // creates Makefile to use project files in each subdirectory
vcapp                         // creates Visual Studio Project file to build an application
vclib                         // creates Visual Studio Project file to build a library
vcsubdirs                     // creates Visual Studio Solution file to build projects in sub-directories 
                              
//CONDITIONAL SCOPE                  
debug {}                      // do if debug configuration, can use any config options
!debug {}                     // do if not debug configuration
win32 {}                      // do if windows configuration
win32:debug {}                // can combine nested scopes
win32|macx {}                 // do if either is true
win32:DEFINES += TEST         // add only if win32
for(var, $$MY_LIST) {}        // takes a list variable eg. list(one two three)
if(expression) {} else {}
win32 {} else:macx {} else {}

//FUNCTIONS
include(other.pro)               // Include another project file
log("Message")                   // Same as message() but without line break
error("String")                  // Print an error and exits
message("String")                // Prints a message
warning("String")                // Prints a warning
prompt("String")                 // Shows a dialog prompt and returns answer
mkpath("c:/MyPath")              // Creates a new path
requires(expression)             // Evaluates expression, if false, qmake skips file
system("cd Folder")              // Execute using the command line
unset(MY_VAR)                    // Undefines variable

//TEST FUNCTIONS
//Return bool, can be used as fn(){}, putting ! in front negates
CONFIG(option)                     // Succeeds if config option is on
contains(MY_VAR, value)            // Succeeds if MY_VAR contains value
count(MY_VAR, n)                   // Succeeds if contains a list with n values
debug(level, "String")             // Succeeds if qmake debug level is set, prints message if so
defined(MY_VAR)                    // Succeeds function or variable name is defined
equals(MY_VAR, value)              // Succeeds if MY_VAR equals value, can use isEqual()
eval(expression)                   // Succeeds if expression succeeds, same as if block
exists(main.cpp)                   // Succeeds if file exists
greaterThan(MY_VAR, value)         // Succeeds if MY_VAR > value
infile("file.txt", MY_VAR, value)  // Succeeds if file contains variable with name and optionally value
isEmpty(MY_VAR)                    // Succeeds if MY_VAR is empty or has no value

//REPLACE FUNCTIONS
//To use return value, put $$ in front
absolute_path("file.txt")        // Returns path as absolute
relative_path("c:/file.txt")     // Returns path as relative
basename("MyPath/file.txt")      // Returns file name
cat("file.txt")                  // Returns contents of file
clean_path("MyPath/file.txt")    // Returns normalized path, converts to / and removes .
dirname("MyPath/file.txt")       // Returns directory of file	
enumerate_vars()                 // Returns list of all defined variable names
find(MY_VAR, expression)         // Returns all the values in MY_VAR that match the regex
files(expression, true)          // Returns list of files using regex from working dir, true for recursion
first(MY_VAR)                    // Returns first of MY_VAR if a list
last(MY_VAR)                     // Returns last of MY_VAR if a list
getenv(MY_ENV_VAR)               // Returns value of env var, supports var names with () in them
join(MY_VAR, , prefix, suffix)   // Returns MY_VAR with suffix and prefix (both optional)
list(one two three)              // Returns a list of strings
lower(MY_VAR, MY_VAR2...)        // Takes n values and converts them to lower case
upper(MY_VAR, MY_VAR2...)        // Takes n values and converts them to upper case
member(MY_LIST, start, end)      // Returns slice of list between zero-based indices, use str_member() for strings
num_add(MY_VAR, MY_VAR2...)      // Takes n values and returns sum
re_escape("String")              // Returns string with regular expression characters escaped with a backslash
quote("String")                  // Adds " to a string
sprintf("String", MY_VAR...)     // Replaces %1-%9 in string with variables
reverse(MY_VAR)                  // Returns value of MY_VAR in reverse order
size(MY_VAR)                     // Returns number of values in MY_VAR, use str_size() for strings
sorted(MY_VAR)                   // Returns list of ascended sorted values in MY_VAR	
split(MY_VAR, delim)             // Returns a list of MY_VAR seperated by delim
take_first(MY_VAR)               // Returns the first item and pops it
take_last(MY_VAR)                // Returns the last item and pops it
unique(MY_VAR)                   // Returns MY_VAR with any duplicate items removed

//REPLACE FORMAT FUNCTIONS
//Floating-point numbers are currently not supported
format_number(value, obase=16)   // Returns decimal number in hex
format_number(value, ibase=16)   // Returns hex number in decimal
format_number(value, width=n)    // Sets the min width of the output, if output shorter, pads with spaces
format_number(value, zeropad)    // Pads the output with 0 instead of spaces
format_number(value, padsign)    // Prepends a space to positive values in the output
format_number(value, alwayssign) // Repends a plus sign to positive values in the output
format_number(value, leftalign)  // Places the padding to the right of the value in the output

//===============================================================================================================
// QMAKE PROPERTIES
//===============================================================================================================

qmake -set "QT_VERSION" value    // set the property
qmake -query "QT_VERSION"        // query the property
qmake -query                     // queries all property/value pairs
$$[QMAKE_VERSION]                // query the property in a project file

QMAKE_VERSION             // the current version of qmake
QT_INSTALL_ARCHDATA       // location of general architecture-dependent Qt data
QT_INSTALL_BINS           // location of Qt binaries (tools and applications)
QT_INSTALL_CONFIGURATION  // location for Qt settings. Not applicable on Windows
QT_INSTALL_DATA           // location of general architecture-independent Qt data
QT_INSTALL_DOCS           // location of documentation
QT_INSTALL_EXAMPLES       // location of examples
QT_INSTALL_HEADERS        // location for all header files
QT_INSTALL_IMPORTS        // location of QML 1.x extensions
QT_INSTALL_LIBEXECS       // location of executables required by libraries at runtime
QT_INSTALL_LIBS           // location of libraries
QT_INSTALL_PLUGINS        // location of Qt plugins
QT_INSTALL_PREFIX         // default prefix for all paths
QT_INSTALL_QML            // location of QML 2.x extensions
QT_INSTALL_TESTS          // location of Qt test cases
QT_INSTALL_TRANSLATIONS   // location of translation information for Qt strings
QT_SYSROOT                // the sysroot used by the target build environment
QT_VERSION                // the Qt version
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMAKE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
find_package(Qt5 COMPONENTS Core Widgets Quick)
qt5_add_resources(RESOURCES resources/myResources.qrc)
add_executable(exe_name ${SRC_LIST} ${RESOURCES})
qt5_use_modules(exe_name Core Widgets Quick)
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT HELP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Includes tools for generating and viewing Qt help files
• Provides framework for accessing help contents / integrating online help programmatically
• Can view help files through Qt Assistant browser or linking to QHelpEngine API
• 4 files involved with generating help documentation:
-------------------------------------------------------------------------------------------------------
Qt Help Project    | .qhp  | The input file for the help generator consisting of the table of contents, 
                   |       | indices, and references to the actual documentation files (*.html). 
                   |       | It also defines a unique namespace for the documentation. Generates .qch
                   |       | when calling qhelpgenerator doc.qhp -o doc.qch
                   |       | 
Qt Compressed Help | .qch  | The output file of the help generator. This binary file contains all the 
                   |       | information specified in the help project file along with all the 
                   |       | compressed documentation files.
                   |       | 
Qt Help Collection | .qhcp | The input file for the help collection generator. It contains references 
Project            |       | to the compressed help files that should be included in the collection; 
                   |       | it also may contain other information for customizing Qt Assistant. 
                   |       | Generates a .qhc file by calling:
                   |       | qcollectiongenerator mycollection.qhcp -o mycollection.qhc              
                   |       | 
Qt Help Collection | .qhc  | The output of the help collection generator. This is the file QHelpEngine 
                   |       | operates on. It contains references to any number of compressed help files 
                   |       | as well as additional information, such as custom filters.
-------------------------------------------------------------------------------------------------------
**************************************************************************************************************/

// ACCESSING HELP FILES
QHelpEngineCore helpEngine("help.qhc");
QMap<QString, QUrl> links = helpEngine.linksForIdentifier("keyword"));
// If help is available for this keyword, get the help data
if (links.count()) 
{
    QByteArray helpData = helpEngine->fileData(links.constBegin().value());
    if (!helpData.isEmpty())
    {
        displayHelp(helpData);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LINGUIST
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
LUPDATE
• Tool to synchronize source code and translations
• Finds translatable strings from files specified in .pro and creates/updates .ts translation files
• Run using: lupdate myproject.pro

LRELEASE
• Tool to create run-time translation files for use by the released application
• Creates binary QM files out of TS files
• Run using: lrelease myproject.pro

QT LINGUIST TOOL
• Translate text in applications using TS files, can save out QM files
• Includes phrase book
**************************************************************************************************************/

// PROJECT FILE
// Each language required needs to be specified
TRANSLATIONS    = superapp_dk.ts \
                  superapp_fi.ts \
                  superapp_no.ts \
                  superapp_se.ts
