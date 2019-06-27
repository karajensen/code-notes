/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FRAMEWORK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
Source: https://code.woboq.org/qt5/
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
**************************************************************************************************************/

QT_FORWARD_DECLARE_CLASS(QQuickItem)

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QOBJECTS:
• Base class of all Qt objects, organised in an object tree
• Doesn't have a copy constructor or assignment operator
• Meta Object Compilier code generator uses Q_OBJECT macro to generate moc cpp file
• Ability to use qobject_cast, signals, slots, property system

MOC QOBJECT LIMITATIONS:
• Multiple Inheritance requires QObject to be first
• Moc doesn't support virtual inheritance
• Moc doesn't support templates with Q_OBJECT
• Moc doesn't support OS #defines, must use Q_MOC_RUN if moc is skipping because of them

DELETING QOBJECTS:
• Root parent needs to be explicitly deleted, either by delete (deleteLater, qDeleteAll) or stack scope
• Children deleted by parent automatically, if child is deleted first, parent is notified
• Children should not be created on the stack unless deleted first, as parent assumes children are on heap
• qDeleteAll used for containers of QObject* and calls 'delete' on all items

DELETE LATER:
• Calls 'delete' on object when control returns to the event loop
• If called before main loop, will be deleted when it starts. If called after, will not be deleted
• Safe to call multiple times
• Should be used unless you can ensure:
    - Object isn't used in any pending events or callbacks (eg. QTimer)
    - Object isn't the signaller if being deleted in a slot

IMPLICIT SHARING (COPY-ON-WRITE):
• Objects share the same memory in a 'shared block' if have the same values
• Automatically detaches the object from a shared block when object changes and ref count is > 1
• Qt classes use it internally, doesn't require a shared data pointer for it to happen
• Can be dangerous for iterators when container detaches from shared block:

PROPERTY SYSTEM:
• To create dynamic properties use QQmlPropertyMap (see Qt Containers)
MEMBER     Required if READ not used, implicitly creates getter/setter with emitting signal
READ       Required if MEMBER not used
WRITE      Optional, can be used with either READ or MEMBER
NOTIFY     Optional, takes signal with one or no arguments
STORED     Default true, indicates whether property value must be saved when storing the object's state
CONSTANT   Optional, makes readonly
FINAL      Optional, can enable optimizations, indicates shouldn't override though not enforced by moc
**************************************************************************************************************/

// OBJECTS/GADGETS
namespace N
{
    Q_NAMESPACE
    
    class MyClass : public QObject
    {
        Q_OBJECT // required for all moc provided features
        Q_CLASSINFO("Author", "Name") // attach additional name/value pairs to the class's meta-object
        Q_DISABLE_COPY(MyClass) // Required for singleton classes

    public:
        MyClass(QObject *parent = 0) { }
        Q_PROPERTY(MyValue value MEMBER m_value NOTIFY myValueSignal)
        Q_PROPERTY(MyValue value READ getValue WRITE setValue NOTIFY mySignal)

        enum class MyClassEnum { ONE, TWO, THREE };
        Q_ENUM(MyClassEnum)

        enum MyClassFlag { One=0x01, Two=0x02, Three=0x04 };
        Q_FLAG(MyClassFlag)

        // Can be overloaded, virtual, pure virtual, with defaults
        const MyValue& getValue() const { return m_value; }
        void setValue(const MyValue& value) { m_value = value; }
        Q_INVOKABLE void myFn() { }
    };
    
    // Value-type used with variant, doesn't increase class size
    struct MyGadget
    {
        Q_GADGET

    public:
        Q_PROPERTY(QString name MEMBER m_name)
        Q_INVOKABLE void myFn() { }
        bool operator==(const Gadget& g) const { ... }
        bool operator!=(const Gadget& g) const { ... }
    };
    Q_DECLARE_METATYPE(MyGadget) 
}

// ENUMS/FLAGS
// Must start with capital letter
namespace N
{
    Q_NAMESPACE
    
    enum class MyEnum { ONE, TWO, THREE };
    Q_ENUM_NS(MyEnum) 

    enum MyFlag { One=0x01, Two=0x02, Three=0x04 };
    Q_FLAG_NS(MyFlag) 
    Q_DECLARE_FLAGS(MyFlags, MyFlag) // Creates type 'Flags'
}
Q_DECLARE_OPERATORS_FOR_FLAGS(N::MyFlags) // Allows operator use, must be outside namespace

// QObject
obj.objectName // Property; User-defined name of object instance, blank as default
obj.setProperty("value", v); // Return true if existed and set, auto creates if doesn't exist only for obj
obj.property("value") // Returns QVariant, invalid if doesn't exist
obj.metaObject() // Returns const QMetaObject*
obj.blockSignals(true) // Prevents any signals from calling slots, doesnt block destroyed() signal
obj.signalsBlocked() // Whether signals blocked
obj.event(evt) // Internally called method that can be overridden to catch QEvents, return true if caught
obj.children() // Returns const QList<QObject*>& for children, order changes when child raised/lowered
obj.dumpObjectInfo() // Outputs to debug log
obj.dumpObjectTree() // Outputs to debug log
obj.dynamicPropertyNames() // Returns QList<QByteArray> for all dynamic properties, not in QML
obj.findChild<T*>("objectName") // Optional objectName, returns T* or null
obj.findChild<T*>("objectName", Qt::FindDirectChildrenOnly) // Non recursive version
obj.findChildren<T*>("objectName") // Optional objectName, returns QList<T*> =
obj.findChildren<T*>("objectName", Qt::FindDirectChildrenOnly) // Non recursive version
obj.installEventFilter(&obj2) // obj2's eventFilter() called before obj's event() for obj's events
obj.removeEventFilter(&obj2) // Remove obj2 as an event filter
obj.isWidgetType() // Whether obj inherits QWidget
obj.isWindowType() // Whether obj inherits QWindow
obj.parent() // Returns QObject*
obj.setParent(obj2) // Sets parent
obj.thread() // Returns QThread* where the object lives
obj.startTimer(interval, timerType) // Returns ID, takes ms, Qt::TimerType
obj.killTimer(id) // Stop timer with ID
obj.timerEvent(event) // QTimerEvent when timer interval is hit, QTimerEvent gives timerId() 
qobject_cast<N::MyClass*>(obj); // dynamic_cast without requiring RTTI
N::MyClass::staticMetaObject // QMetaObject for class
    
// QMetaObject
metaObj.propertyCount() // Number of properties, not including dynamic properties
metaObj.className() // Returns class name as const char*
metaObj.methodCount() // Number of methods including inherited, signals, slots
metaObj.enumeratorCount() // Number of enums including inherited
metaObj.enumerator(index) // Get QMetaEnum from index
metaObj.indexOfEnumerator(name) // Get index of enum from name, or -1 if not found
QMetaObject::invokeMethod(myObj, []{}); // Calls with Auto Connection (see Signals connection types)

// QMetaEnum
QMetaEnum metaEnum(QMetaEnum::fromType<N::MyEnum>());
metaEnum.valueToKey(N::MyEnum::ONE) // Returns const char* or null if not found
metaEnum.keyToValue("ONE", &isValid) // Returns int or -1 if not found, optional bool
metaEnum.keyCount() // Returns number of keys/values
metaEnum.key(index) // Returns const char* key from int index, or null if doesn't exist
metaEnum.value(index) // Returns int value with the given index, or returns -1 if none found
    
// QFlags
// Requires Q_DECLARE_FLAGS and Q_DECLARE_OPERATORS_FOR_FLAGS, can implicity convert to unsigned int
N::MyFlags flags = N::ONE | N::TWO
flags.testFlag(a::ONE) // returns true if flags includes ONE
flags ^= N::TWO // add TWO

// TYPE INFO
// Macro must placed after class in .h
// Q_PRIMITIVE_TYPE leaves obj memory unitialised, means trivally copyable
// Q_MOVABLE_TYPE uses std::memcpy rather than copy ctor to move obs around, means trivally relocatable
// Q_MOVABLE_TYPE does shallow move; don't use for types that self refer (pimpl with ptr back to parent)
Q_DECLARE_TYPEINFO(N::MyClass, Q_COMPLEX_TYPE) // Default
Q_DECLARE_TYPEINFO(N::MyEnum, Q_PRIMITIVE_TYPE)
Q_DECLARE_TYPEINFO(N::MyGadget, Q_MOVABLE_TYPE)
QTypeInfoQuery<N::MyClass>::isRelocatable // Query type info

// REGISTERING WITH VARIANT
// Macros must be placed after class in .h
// QObject classes can only register MyClass*, not MyClass as must be copy-constructable
// Container don't need to be registered for variant, but undefined if used in QML; Use QVariantList instead
Q_DECLARE_METATYPE(MyGadget) // Allows use with variant: myVariant.value<N::MyGadget>()
qRegisterMetaType<N::MyGadget>(); // Allows use with property system
Q_ENUM(MyEnum) // Registers with variant and property system, _NS version for Q_NAMESPACE
Q_FLAG(MyFlag) // Registers with variant and property system, _NS version for Q_NAMESPACE

// REGISTERING FOR STREAMING
// Allows use with drag/drop systems
qRegisterMetaTypeStreamOperators<N::MyClass>("MyClass");
QDataStream& operator<<(QDataStream& out, const MyClass& obj);
QDataStream& operator>>(QDataStream& in, MyClass& obj);

// DELETING AN OBJECT
obj.deleteLater() /*or*/ delete obj /*or*/ qDeleteAll(objs) /*or*/ { obj }
emit destroyed() // Emitted just before obj deleted, children deleted after signal

// INVOKING A METHOD FROM QOBJECT
auto metaObject = myObj->metaObject();
auto methodIndex = metaObject->indexOfMethod("myFn(QVariant,bool)");
if (methodIndex != -1)
{
    QMetaMethod method = metaObject->method(methodIndex);
    if(method.isValid())
    {
        QVariant variant;
        if (method.invoke(myObj, Q_RETURN_ARG(QVariant, variant), 
            Q_ARG(QVariant, QVariant::fromValue(true)), Q_ARG(bool, false)))
        {
            return variant.value<bool>();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIGNALS / SLOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Can only be used by Q_OBJECT, not Q_GADGET, due to moc requirements
• On signal emit, all slots in order of connection are immediately notified, can't be async
• No return values, slots can be virtual/pure virtual
• Default argument type must match between signals/slots, don't have to both have default

MOC SIGNAL LIMITATIONS:
• Only signals and slots can live in the signals and slots sections
• Moc doesn't support templates with signals/slots
• Moc doesn't expand #define: cannot use a macro to declare a signal/slot or used as a signal/slot parameter
• Function Pointers cannot be direct signal/slot Parameters, work-around is to typedef it
• Enums/typedefs cannot be forward decl for signal/slot parameters
• Nested Classes cannot have signals or slots

CONNECTIONS:
• Returns QMetaObject::Connection or can call QObject::disconnect with same signature
• QObject destruction auto disconnects signals/slots
• Can duplicate connections, multiple signals are then emitted, all are broken with single disconnect call 
• Slot must have <= arguments of signal: can ignore values but cannot have more or different types to signal
• SIGNAL/SLOT macros give runtime error, functions give compile error if signal/slot incompatible
• Use normalised form from moc cpp for SIGNAL/SLOT macros, otherwise performance hit
• QueuedConnection auto copies values, DirectConnection/BlockedConnection doesn't
• BlockingQueuedConnection dangerous if connecting two objects with same thread affinity
**************************************************************************************************************/

Class MyClass : QObject
{
    Q_OBJECT
    void setValue(int value);
    
signals: // is only public, use QPrivateSignal to make private
    void mySignal();
    void mySignal(int value);
    void mySignal(int value, QPrivateSignal);

public slots: // can be protected/private
    void mySlot();
    void mySlot(int value);
    void mySlot(int value, QPrivateSignal);
    
    void mySlot(void (*fn)(void *)); // Cannot do
    void mySlot(MyFn fn);            // Can do
};

void MyClass::setValue(int value)
{
    if (value != m_value) 
    {
        // Emit a signal, need to call emit whenever Q_PROPERTY changes to update QML
        m_value = value;
        emit valueChanged(value);
    }
}

// CONNECTION
QObject::connect(sender, &Sender::mySignal, reciever, &Receiver::mySlot, type);
QObject::connect(sender, &Sender::mySignal, reciever, [](){}, type);
QObject::connect(sender, &Sender::mySignal, [](){}, type);
QObject::connect(sender, SIGNAL(mySignal()), reciever, SLOT(mySlot()), type);
QObject::connect(sender, SIGNAL(mySignalArgs(int,float)), reciever, SLOT(mySlotArgs(int,float)), type);
QObject::disconnect(sender, &Sender::mySignal, reciever, &Receiver::mySlot);
QObject::disconnect(connection);
QObject::disconnect(); // Disconnect all signals

// CONNECTION TYPE FLAGS
// Optional, AutoConnection is default
Qt::AutoConnection           // Objects with same thread affinity use DirectConnection, else QueuedConnection
Qt::DirectConnection         // Slot invoked immediately when signal emitted and executed in signaller's thread     
Qt::QueuedConnection         // Slot invoked in event loop of receiver's thread and executed in reciever's thread
Qt::BlockingQueuedConnection // QueuedConnection except signalling thread blocks until the slot returns
Qt::UniqueConnection         // Connect will fail if same connection already exists, can combine with other flags

// OVERLOADING SIGNALS/SLOTS
// Cannot use qOverload for Windows: https://bugreports.qt.io/browse/QTBUG-61667
void(MyClass1::*signal)(int) = &MyClass1::mySignal;
void(MyClass2::*slot)(int) = &MyClass2::mySlot;
QObject::connect(obj1, signal, obj2, slot);

// AUTO DISCONNECT SLOT FROM SIGNAL AFTER USE
auto connection = std::make_shared<QMetaObject::Connection>();
*connection = QObject::connect(sender, &Sender::mySignal, [this, connection]()
{
    QObject::disconnect(*connection);
});

// SIGNAL MAPPER
// Deprecated, used to combine multiple signals into one, and/or signal with different arguments
QSignalMapper signalMapper;
connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
signalMapper->setMapping(button, button);
connect(signalMapper, SIGNAL(mapped(QObject)), this, SIGNAL(clicked(QObject)));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT SMART POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT EVENT SYSTEM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Events can be async while signals/slots cannot
• All events derive from QEvent

SPONTANEOUS EVENTS: Generated by the os, Put in a system queue and processed sequentially by main loop
POSTED EVENTS: Generated from postEvent call, Put in queue in priority order and processed by main loop
SENT EVENTS: Generated from sendEvent call, Sent directly to target object
SYNTHETIC EVENTS: Posted/Sent events generated by application

EVENT LOOP:
• Allows merging/compressing of paint, move, resize, layout hint and language change events
• QApplication::sendPostedEvents forces processing of posted events
• QApplication::exec event loop: 
    1) Processes any posted events until queue is empty
    2) Processes any spontaneous events
    3) Processed any posted events generated during spontaneous events
**************************************************************************************************************/

// RECEIVE EVENTS
// Recieve events only for the object
bool MyObject::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::KeyPress:
        QKeyEvent* evt = static_cast<QKeyEvent*>(event);
        evt->key(); // Get the key enum type 
        break;
    case QEvent::Close:
        break;
    case QEvent::Show:
        break;
    case QEvent::FocusIn:
        break;
    case QEvent::FocusOut:
        break;
    }        
    return true; // Prevent the event from being passed on
    return QObject::event(event);
}

// EVENT FILTERS
// Recieve an event from one object in another, can install multiple filters
// myObj2 eventFilter() called before myObj event()
myObj->installEventFilter(&myObj2);
myObj->removeEventFilter(&myObj2);
bool MyObject2::eventFilter(QObject* object, QEvent* event)
{
    if (object == myObj)
    {
        // Do something with object
    }
    return QObject::eventFilter(object, event);
}

// SEND EVENTS
// Sends directly to myObject, returns value returned from MyObject::event
// Doesn't take ownership of event
QMouseEvent event(QEvent::MouseButtonPress, pos, 0, 0, 0);
QApplication::sendEvent(myObject, &event);

// POST EVENTS
// Adds the event to an event queue run from the main loop and returns immediately
// Takes ownership of event- not safe to access after post call
QApplication::postEvent(myObject, 
    new QMouseEvent(QEvent::MouseButtonPress, pos, 0, 0, 0), 
    Qt::NormalEventPriority);

// CUSTOM EVENTS
class MyCustomEvent : public QEvent
{
public:
    MyCustomEvent() : QEvent(CustomEventType) {}
    virtual ~QCustomEvent() {}
    static QEvent::Type CustomEventType;
};
QEvent::Type MyCustomEvent::CustomEventType = static_cast<QEvent::Type>(QEvent::registerEventType());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT BASIC TYPES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qint8        // signed char, guaranteed to be 8-bit
qint16       // signed short, guaranteed to be 16-bit
qint32       // signed int, guaranteed to be 32-bit
qint64       // signed long long int (__int64 on Windows), guaranteed to be 64-bit, use Q_INT64_C to create
qintptr      // signed integral type for representing pointers
qlonglong    // same as qint64
qptrdiff     // signed integral type for representing pointer differences.
qreal        // double unless Qt is configured with the -qreal float
qsizetype    // size_t
quint8       // unsigned char, guaranteed to be 8-bit
quint16      // unsigned short, guaranteed to be 16-bit
quint32      // unsigned int, guaranteed to be 32-bit
quint64      // unsigned long long int (__int64 on Windows), guaranteed to be 64-bit, use Q_UINT64_C to create
quintptr     // unsigned integral type for representing pointers
qulonglong   // same as quint64
uchar        // generic typedef for unsigned char
uint         // generic typedef for unsigned int
ulong        // generic typedef for unsigned long
ushort       // generic typedef for unsigned short

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QPair<T1, T2>
auto pair = qMakePair(v1, v2);
pair.first;
pair.second;

// QSettings
// Provides persistent platform-independent application settings

// QTimer
// Provides repetitive and single-shot timers, takes milliseconds
// Interval of 0 will time out as soon as all events in the event queue have been processed
QTimer timer;
timer.isActive(); // Whether timer is currently running
timer.interval(); // Get int interval time in ms
timer.setInterval(ms); // Set int interval time in ms
timer.remainingTime(); // Returns int time left in ms
timer.isSingleShot(); // Get whether only ticks once and turns itself off
timer.setSingleShot(true); // Set whether only ticks once and turns itself off 
timer.timerType(); // Returns TimerType Enum
timer.setTimerType(type); // Sets TimerType Enum
timer.intervalAsDuration(); // Returns std::chrono::milliseconds for interval
timer.remainingTimeAsDuration(); // Returns std::chrono::milliseconds for time left 
timer.start(ms); // Starts or restarts the timer with a timeout interval of optional ms
timer.stop(); // Stops the timer
QTimer::singleShot(ms, fn); // Internally creates timer which calls slot when done
QTimer::singleShot(ms, type, fn); // Internally creates timer which calls slot when done for TimerType Enum
QTimer::singleShot(ms, receiver, SLOT(mySlot())); // Internally creates timer which calls slot when done
connect(timer, SIGNAL(timeout()), fn); // timeout signal called when interval reached
                                  
// QTimer TimerType Enum
Qt::PreciseTimer        // Try to keep millisecond accuracy
Qt::CoarseTimer         // Try to keep accuracy within 5% of the desired interval
Qt::VeryCoarseTimer     // Only keep full second accuracy
                               
// QUrl
// Interface for working with URLs with prefix qrc:/, file:/// etc.
// Structure is scheme:path or scheme://useinfo@host:port/path/query
// If path passed in has no scheme, considered relative even if absolute path
QUrl url(str) // Set the path directly, does not auto add any scheme
url.clear(); // clears the URL
url.setUrl(str); // Sets the URL
url.isValid(); // Returns true if non-empty and conforms to encoding tests
url.isRelative(); // Returns true if scheme is undefined (same as scheme().isEmpty())
url.toLocalFile() // Convert QUrl to local file path without prefix, normalizes seperators to /
url.toString() // Returns path with prefix file:///, qrc with qrc:/
url.setScheme(str) // Sets type (or protocol) component
url.setPath(str) // Sets path component
QUrl::fromLocalFile(str) // Convert a local file path to QUrl; adds file:/// in front

// QUuid
// 128-bit unique number
QUuid id // Null ("{00000000-0000-0000-0000-000000000000}") by default
QUuid id(str) // Format "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}", {} optional, if fails will be null
id.isNull() // Returns if null id
id.toString(QUuid::StringFormat::WithBraces) // Default, QUuid::WithoutBraces also possible
QUuid::createUuid() // Generate a new unique QUuid
QUuid::fromString(str) // Format "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}", {} optional, if fails will be null

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
/*************************************************************************************************************
• QWidget <- QMainWindow
• QWidget <- QQuickWidget
• QWindow <- QQuickWindow <- QQuickView
• Properties have accessors item.property() or item.isProperty() or item.hasProperty() and item.setProperty()
**************************************************************************************************************/

// QWindow
// Window for non-widgets based applications (eg. QML)
// If has a parent, becomes a native child window of their parent window
// Inherits QOBject and QSurface, inherited by QPaintDeviceWindow and QVulkanWindow
QWindow window;
window.active // Whether window is active
window.contentOrientation // Qt::ScreenOrientation, orientation of the window's contents, used for popups etc.
window.flags // Qt::WindowFlags, setFlags will modify any invalid flags out
window.height // Height of window
window.maximumHeight // Maximum height of window
window.maximumWidth // Maximum width of window
window.minimumHeight // Minimum height of window
window.minimumWidth // Minimum width of window
window.modality // Qt::WindowModality, prevents other windows from receiving input events
window.opacity // Window transparency [0.0, 1.0]
window.title // QString title of window
window.visibility // QWindow::Visibility enum
window.visible // Whether window is visible
window.width // Width of the window
window.x / window.y // Position of the window
window.baseSize() / window.setBaseSize(size) // QSize
window.cursor() / window.setCursor(cursor) // QCursor
window.unsetCursor() // Restore default cursor
window.devicePixelRatio() // Ratio between physical pixels and device-independent pixels for the window
window.filePath() / window.setFilePath() // the file name this window is representing
window.focusObject() // Object in focus in the window, has focusObjectChanged signal
window.format() / window.setFormat(format) // QSurfaceFormat, setFormat may not set invalid options
window.frameGeometry() // QRect geometry of the window including its window frame
window.frameMargins() // QMargins margin size of window
window.geometry() / window.setGeometry(rect) // QRect geometry of the window excluding its window frame
window.setGeometry(x, y, w, h) // geometry of the window excluding its window frame
window.hide() // Hides the window
window.show() // Shows the window
window.showFullScreen() // Shows the window as fullscreen
window.showMaximized() // Shows the window as maximised
window.showMinimized() // Shows the window as minimised
window.showNormal() // Shows the window as default state based on platform
window.icon() / window.setIcon(icon) // QIcon
window.isModal() // Whether window is receiving any input
window.isTopLevel() // Whether window has no parent window
window.isAncestorOf(window2) // Whether window2 is a parent of window
window.lower() // Lower the window below other windows
window.raise() // Raise the window above other windows
window.mapFromGlobal(pos) // Global QPoint screen coord to window QPoint coord
window.mapToGlobal(pos) // Window QPoint coord to Global QPoint screen coord
window.parent() / window.setParent(window) // QWindow*, null means top-most window
window.position() / window.setPosition(pos) // QPoint of window excluding any window frame
window.resize(size) // Change the QSize of the window, excluding any window frame
window.resize(w, h) // Change width/height, excluding any window frame
window.screen() // QScreen*, For child windows, this returns the screen of top level window
window.setFlag(flag, on) // Sets Qt::WindowType flag to on/off
window.setKeyboardGrabEnabled(enabled) // Sets whether keyboard events all forced to window
window.setMouseGrabEnabled(enabled) // Sets whether mouse events all forced to window
window.sizeIncrement() / window.setSizeIncrement(size) // QSize increase when user resizes the window
window.windowState() / window.setWindowState(state) // Qt::WindowState
window.windowStates() / window.setWindowStates(state) // Qt::WindowStates
window.size() // QSize size of the window excluding any window frame
window.transientParent() // Parent for dialogs/popups
window.type() // Qt::WindowType
window.id() // window's WId platform id
    
// QQuickWindow
// Inherits QWindow, window for QML applications

// QQuickView 
// Inherits QQuickWindow, automatically load and display a QML scene from an url
QQuickView view;
view.rootContext(); // Returns QQmlContext*
view.setSource(QUrl("qrc:/main.qml"));
view.setTitle("title");
view.setResizeMode(QQuickView::SizeRootObjectToView);
view.show();

// QWidget
// If no parent, window for widgets based applications (non-QML), else base class for widgets
// Inherits QObject and QPaintDevice, inherited by QOpenGLWidget and QWidget components (eg. QLabel)
// 'Native' Widgets are a toplevel window, QGLWidget, or has had winId() called to create a WId
QWidget widget;
widget.acceptDrops // Whether dropping is enabled
widget.baseSize // QSize
widget.childrenRect // QRect of the children (excluding hidden)
widget.childrenRegion // QRegion of the children (excluding hidden)
widget.contextMenuPolicy // Qt::ContextMenuPolicy, how the widget shows a context menu
widget.cursor // QCursor
widget.enabled
widget.focus // readonly
widget.focusPolicy // Qt::FocusPolicy
widget.font // QFont
widget.frameGeometry // QRect geometry of the window including its window frame
widget.frameSize // QSize geometry of window including parents including window frame
widget.fullScreen // Whether fullscreen window mode
widget.geometry // QRect geometry of window excluding window frame
widget.height / widget.width
widget.inputMethodHints // Qt::InputMethodHints
widget.isActiveWindow // Whether this widget's window is the active window
widget.layoutDirection // Qt::LayoutDirection
widget.locale // QLocale, if not set will use parents or default locale
widget.maximized // Whether maximised window mode
widget.minimized // Whether minimized window mode
widget.maximumHeight / widget.minimumHeight
widget.maximumWidth / widget.minimumWidth
widget.maximumSize / widget.minimumSize // QSize
widget.minimumSizeHint // QSize recommended minimum size for the widget
widget.modal // whether the widget is a modal widget
widget.mouseTracking // default false, same as hoverEnabled
widget.normalGeometry // QRect used when not maximized or full screen, empty for child widgets
widget.palette // QPalette
widget.pos // QPoint
widget.rect // QRect without window frame
widget.size // QSize without window frame
widget.sizeHint // QSize recommended size for the widget
widget.sizeIncrement // QSize to increment window when resizing
widget.sizePolicy // QSizePolicy
widget.statusTip // QString
widget.styleSheet // QString
widget.toolTip // QString
widget.toolTipDuration // ms display time, -1 (default) auto calculates based on length
widget.updatesEnabled // Whether to prevent update/repaint calls, to help prevent flickering when resizing
widget.visible
widget.whatsThis // QString What's This help text
widget.filePath // the file name this window is representing
widget.windowFlags // Qt::WindowFlags
widget.windowIcon // QIcon
widget.windowModality // Qt::WindowModality
widget.windowModified // Whether the document shown in the window has unsaved changes
widget.windowOpacity // [0.0, 1.0]
widget.windowTitle // QString
widget.x / widget.y
widget.adjustSize() // Adjusts the size of the widget to fit its contents
widget.backgroundRole() / widget.setBackgroundRole() // QPalette::ColorRole
widget.forgroundRole() / widget.setForegroundRole() // QPalette::ColorRole
widget.backingStore() // Returns the QBackingStore* this widget will be drawn into
widget.childAt(x, y) // Returns QWidget*
widget.childAt(point) // Returns QWidget*, QPoint 
widget.clearFocus() // Takes keyboard input focus from the widget
widget.contentsMargins() // QMargins
widget.contentsRect() // QRect area inside the widget's margins
widget.ensurePolished() // Force update widget
widget.find(id) // Returns QWidget*, takes WId
widget.focusNextChild() // Force focus onto next in tab chain
widget.focusNextPrevChild() // Force focus onto previous in tab chain
widget.nextInFocusChain() // QWidget*
widget.previousInFocusChain() // QWidget*
widget.focusWidget() // QWidget* in focus
widget.fontInfo() // Returns QFontInfo for widget
widget.fontMetrics() // Returns QFontMetrics for widget
widget.getContentsMargins(left, top, right, bottom) // Takes int*
widget.grab(rect, size) // Render widget and children into optional rect/size, returns QPixmap
widget.grabKeyboard() / widget.releaseKeyboard() // Sets whether keyboard events all forced to window
widget.grabMouse() / widget.releaseMouse() // Sets whether mouse events all forced to window
widget.isAncestorOf(child) // Whether a parent of QWidget* child
widget.isEnabledTo(ancestor) // if this widget would become enabled if ancestor is enabled
widget.isHidden() // Not the same as !isVisible(), can be hidden if parent is hidden etc.
widget.isEnabledTo(ancestor) // if this widget would become enabled if ancestor is enabled
widget.isVisibleTo(ancestor) // if this widget would become visible if ancestor is shown
widget.isWindow() // Returns true if the widget is an independent window
widget.layout() // Returns QLayout*
widget.lower() // Lower the window below other windows
widget.raise() // Raise the window above other windows
widget.mapFromGlobal(pos) // Global QPoint screen coord to window QPoint coord
widget.mapFrom(parent, pos) // QPoint pos in QWidget parent coord to window QPoint coord, must be a parent
widget.mapFromParent(pos) // QPoint pos in QWidget parent coord to window QPoint coord
widget.mapTo(parent, pos) // Window QPoint coord to QWidget parent coord, must be a parent
widget.mapToParent(pos) // Window QPoint coord to QWidget parent coord
widget.mapToGlobal(pos) // Window QPoint coord to Global QPoint screen coord
widget.parentWidget() // Returns QWidget*
widget.repaint() // Force render the widget
widget.resize(w, h) // Resize the widget
widget.actions() // QList<QAction*> of actions0assigned to this widget
widget.addAction(action) // Assign QAction* to this widget, ownership not transferred
widget.addActions(actions) // Assign QList<QAction*> to this widget, ownership not transferred    
widget.insertAction(before, action) // Insert QAction* before QAction*
widget.insertActions(before, actions) // Insert QList<QAction*> before QAction*
widget.removeAction(action) // QAction*
widget.restoreGeometry(geometry) // QByteArray
widget.saveGeometry() // QByteArray
widget.scroll(dx, dy) // Scrolls widget including children, can be negative values
widget.setFocus(reason) // Qt::FocusReason optional
widget.setHidden(hidden) // setVisible(!hidden)
widget.setLayout(layout) // QLayout*, will take ownership
widget.setWindowFlag(flag, on) // Sets Qt::WindowType flag to on/off
widget.windowState() / widget.setWindowState(state) // Qt::WindowState
widget.hide() // Hides the window
widget.show() // Shows the window
widget.showFullScreen() // Shows the window as fullscreen
widget.showMaximized() // Shows the window as maximised
widget.showMinimized() // Shows the window as minimised
widget.showNormal() // Shows the window as default state based on platform
widget.close()
widget.stackUnder(widget) // Places under widget in parent's stack. Must be siblings
widget.underMouse() // Whether mouse hovered
widget.effectiveWinId() // WId platform id of first native widget, may change
widget.id() // WId platform id, may change, if non-native widget, will create an id
widget.window() // Returns QWidget* for widget's window (or itself if a window)
widget.windowHandle() // Returns QWindow* if a toplevel window, QGLWidget, or has had winId called
QWidget::setTabOrder(first, second) // QWidget*, QWidget*

// QMainWindow
// Inherits QWidget, must have a central widget set
QMainWindow window;
window.animated // Whether docking/tool bars are animated
window.dockOptions // QMainWindow::DockOption / QMainWindow::DockOptions
window.documentMode // Whether tab bar for tabbed dockwidgets is set to document mode
window.iconSize // QSize
window.tabShape // QTabWidget::TabShape
window.toolButtonStyle // Qt::ToolButtonStyle
window.addDockWidget(area, widget, orientation) // Qt::DockWidgetArea, QDockWidget*, Qt::Orientation
window.addToolBar(area, toolbar) // Qt::ToolBarArea, QToolBar*
window.addToolBar(title) // returns QToolBar* parented to window
window.centralWidget() // returns QWidget*
window.corner(corner) // returns Qt::DockWidgetArea for Qt::Corner
window.createPopupMenu() // returns QMenu*, ownership transfers to caller
window.dockWidgetArea(widget) // returns Qt::DockWidgetArea for QDockWidget*
window.insertToolBar(before, toolbar) // QToolBar*
window.menuBar() // returns main QMenuBar*, creates and returns if does not exist
window.menuWidget() // returns main QWidget*, returns null if does not exist
window.removeDockWidget(widget) // remove QDockWidget*
window.removeToolBar(toolbar) // remove QToolBar*
window.resizeDocks(docks, sizes, orientation) // QList<QDockWidget*>, QList<int>, Qt::Orientation
window.restoreState(state) // const QByteArray&
window.saveState() // QByteArray
window.setCentralWidget(widget) // QWidget*, takes ownership
window.setCorner(corner, area) // Qt::Corner, Qt::DockWidgetArea
window.setMenuBar(menuBar) // QMenuBar*, takes ownership
window.setMenuWidget(menuBar) // QWidget*, takes ownership
window.setStatusBar(statusbar) // QStatusBar*, takes ownership
window.setTabPosition(areas, tabPosition) // Qt::DockWidgetAreas, QTabWidget::TabPosition
window.statusBar() // returns QStatusBar*, creates and returns if does not exist
window.tabPosition(area) // returns QTabWidget::TabPosition, takes Qt::DockWidgetArea
window.takeCentralWidget() // removes and returns QWidget*, transfers ownership to caller
window.toolBarArea(toolbar) // Returns Qt::ToolBarArea, takes QToolBar*
    
// QQuickWidget
// Inherits QWidget, wrapper for QQuickWindow, allows integrating QML with QWidgets UI
// Less stacking order restrictions, though slower compared to QQuickWindow/QQuickView
// Disables the threaded render loop on all platforms
// Avoid calling winId; triggers creation of a native window, resulting in reduced performance

// QWindow::Visibility
QWindow::Windowed             // Window allowed to be resized/moved to part of screen
QWindow::Minimized            // Window minimized to dock, start bar etc.
QWindow::Maximized            // Window full screen but with status bar
QWindow::FullScreen           // Window full screen, is not resizable, no titlebar
QWindow::AutomaticVisibility  // Default visible state based on platform
QWindow::Hidden               // Window not visible in any way

// Qt::WindowState / Qt::WindowStates
Qt::WindowNoState             // Normal state
Qt::WindowMinimized           // Minimised
Qt::WindowMaximized           // Maximised
Qt::WindowFullScreen          // Fullscreen
Qt::WindowActive              // Has focus
    
// Qt::ScreenOrientation
Qt::PrimaryOrientation             // The display's primary orientation
Qt::LandscapeOrientation           // Width > height
Qt::PortraitOrientation            // Height > width, rotated 90 degree clockwise relative to landscape
Qt::InvertedLandscapeOrientation   // Inverted landscape orientation, rotated 180 degrees relative to landscape
Qt::InvertedPortraitOrientation    // Inverted portrait orientation, rotated 180 degrees relative to portrait

// Qt::WindowModality
Qt::NonModal           // Does not block input to other windows
Qt::WindowModal        // Blocks input to all parents and their siblings windows
Qt::ApplicationModal   // Blocks input to all windows
    
// Qt::WindowFlags /  Qt::WindowType
Qt::Widget           // Default type for QWidget
Qt::Window           // Indicates window
Qt::SubWindow        // Indicates subwindow
Qt::Dialog           // value|Window, Indicates is a dialog window
Qt::Popup            // value|Window, Indicates is popup menu window
Qt::Sheet            // value|Window, Indicates modal osx window
Qt::Desktop          // value|Window, Default type for QDesktopWidget
Qt::CoverWindow      // value|Window, Indicates is a cover window (shown when app minimised)
Qt::ForeignWindow    // value|Window, Handle of a native platform window created by another process/native code
Qt::Tool             // Popup|Dialog, Indicates tool window always on top of parent
Qt::ToolTip          // Popup|Sheet, Indicates tooltip window
Qt::SplashScreen     // Dialog|ToolTip, Default type for QSplashScreen
Qt::CustomizeWindowHint           // Required for most window hints
Qt::FramelessWindowHint           // Make window without a border
Qt::NoDropShadowWindowHint        // Disables window drop shadow on supporting platforms
Qt::WindowTitleHint               // Gives the window a title bar
Qt::WindowSystemMenuHint          // Adds a window system menu and a close button on some systems
Qt::WindowMinimizeButtonHint      // Adds a minimize button, may require WindowSystemMenuHint
Qt::WindowMaximizeButtonHint      // Adds a maximize button, may require WindowSystemMenuHint
Qt::WindowMinMaxButtonsHint       // WindowMaximizeButtonHint|WindowMaximizeButtonHint
Qt::WindowCloseButtonHint         // Adds a close button, may require WindowSystemMenuHint
Qt::WindowContextHelpButtonHint   // Adds a context help button to dialog, may require WindowSystemMenuHint
Qt::WindowStaysOnTopHint          // Window should always be on top
Qt::WindowStaysOnBottomHint       // Window should always be on bottom

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
// QOpenGLWidget
// Inherits QWidget but uses QOpenGLContext for rendering with OpenGL into a framebuffer object
QOpenGLWidget widget
widget.context() // returns QOpenGLContext*
widget.initializeGL() // Reimplement this to initialize any needed resources
widget.paintGL() // Reimplement this for when the widget needs to be rendered
widget.resizeGL(w, h) // Reimplement this for when the widget needs to be resized   

// QLabel
QLabel lbl("Message") // Allows use of html tags to customise text

// QPushButton
QPushButton btn("Text")
QObject::connect(button, SIGNAL(clicked()), fn)  // Connect to button's click event

// QSpinBox
QSpinBox spinbox
spinbox.setRange(min, max)
spinBox.setValue(value)
QObject::connect(spinBox, SIGNAL(valueChanged(int)), fn)

// QSlider 
QSlider slider(Qt::Horizontal)
slider.setRange(min, max)
slider.setValue(value)
QObject::connect(slider, SIGNAL(valueChanged(int)), fn)

// QHBoxLayout
// Lays out widgets horizontally from left to right
QHBoxLayout layout
layout.addWidget(spinBox) // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout
// Lays out widgets vertically from top to bottom
QVBoxLayout layout
layout.addWidget(spinBox) // Add a widget to the layout, automatically parents and resizes

// QGridLayout
// Lays out widgets in a grid.
QGridLayout layout
layout.addWidget(spinBox, r, c) // Add a widget to the layout, automatically parents and resizes

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT QUICK / QML
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QQuickItem
// Inherits QObject, instantiated by Item
// Properties have accessors item.property() or item.isProperty() and item.setProperty()
item.activeFocus // Read only, whether item has active focus
item.activeFocusOnTab // Whether included in active focus on tab, default false
item.antialiasing // Whether antialiasing enable, default false
item.baselineOffset // Position offset, default 0, used for text
item.childrenRect // Read only, QRectF collective position and size of the item's children
item.clip // Whether clipping enabled, default false, hides part of item/children, performance hit
item.enabled // Recursive, whether the item receives mouse and keyboard events
item.focus // Whether item has input focus
item.height // Actual height of item
item.width // Actual width of item
item.implicitHeight // Default height of the Item if no height is specified
item.implicitWidth // Default width of the Item if no width is specified
item.opacity // Alpha of item, values outside [0,1] clamped
item.objectName // Inherited from QObject
item.parent // QQuickItem*, visual parent of the item
item.rotation // rotation of the item in degrees clockwise around its transformOrigin, default 0
item.scale // size of item, negative mirror's item, default 1
item.smooth // Image interpolation, true is linear, false is nearest neighbour, default true
item.state // QString state name, default empty
item.transformOrigin // TransformOrigin type which scale/rotate use
item.visible // Recursive, whether item is rendered
item.x / item.y / item.z // Position and stacking depth of item, negative z draws under parent
item.childAt(x, y) // Returns first visible QQuickItem* child found at point within item coord system
item.childItems() // Returns QList<QQuickItem*>
item.componentComplete() // Called when the item has been instantiated
item.contains(point) // If item contains QPointF (in local coordinates)
item.cursor() // Returns QCursor enum for cursor type when mouse over item, default Qt::ArrowCursor
item.flag() // Returns Flags enum value
item.forceActiveFocus(reason) // Focuses item and any parent FocusScopes, reason optional
item.grabMouse() // Item will receive all mouse events until ungrabMouse is called
item.isComponentComplete() // If construction of the QML component is complete
item.isFocusScope() // If item is a FocusScope
item.keepMouseGrab() // Whether mouse input should exclusively remain with this item
item.mapFromGlobal(point) // Converts global coords into item local coords, returns QPointF
item.mapFromItem(item2, point) // Converts item2 local coords into item local coords, returns QPointF
item.mapFromScene(point) // Converts scene coords into item local coords, returns QPointF
item.mapRectFromItem(item2, rect) // Converts item2 local coords into item local coords, returns QRectF
item.mapRectFromScene(rect) // Converts scene coords into item local coords, returns QRectF
item.mapRectToItem(item2, rect) // Converts item local coords into item2 local coords, returns QRectF
item.mapRectToScene(rect) // Converts item local coords into scene coords, returns QRectF
item.mapToGlobal(point) // Converts item local coords into global coords, returns QPointF
item.mapToItem(item2, point) // Converts item local coords into item2 local coords, returns QPointF
item.mapToScene(point) // Converts item local coords into scene coords, returns QPointF
item.nextItemInFocusChain(forward) // Returns next QQuickItem* in the focus chain, whether to move forward
item.scopedFocusItem() // If item is a FocusScope, returns the item in its focus chain with current focus
item.setCursor(cursor) // Sets the cursor shape for this item
item.setFlags(flags) // Enables the specified flags for this item
item.stackAfter(sibling) // Moves sibling QQuickItem* to the index after item in the list of children
item.stackAfter(sibling) // Moves sibling QQuickItem* to the index before item in the list of children
item.ungrabMouse() // Releases the mouse grab following a call to grabMouse
item.unsetCursor() // Clears the cursor shape for this item
item.update() // Schedules a call to updatePaintNode
item.updatePaintNode(oldNode, nodeData) // Called on render thread to sync the item with scene graph
item.updatePolish() // Called to do item layout before rendering the next frame
item.widthValid() // whether the width property has been set explicitly
item.heightValid() //whether the height property has been set explicitly
item.window() // Return QQuickWindow* in which this item is rendered
 
// QQuickPaintedItem
// Inherits QQuickItem, allows rendering content using QPainter
    
// QQmlComponent
// Inherits QObject, instantiated by Component
                               
// QQmlContext
context.setContextProperty("context_model", model); // Sends to QML, does not update if QML already loaded

// QQmlEngine
QQmlEngine::setObjectOwnership(myObj, QQmlEngine::CppOwnership) // Must be used on cpp QObjects without parents

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT QUICK / QML COMMUNICATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
/************************************************************************************************************
CPP                                       QML              JAVASCRIPT
------------------------------------------------------------------------------------------------------------
bool                                      bool             boolean 
unsigned int/int                          int              number
double                                    double           number
float/qreal                               real             number
QString                                   string           string
QUrl                                      url
QColor                                    color
QFont                                     font
QDate                                     date             Date
QTime                                     var              Date
QPoint/QPointF                            point
QSize/QSizeF                              size
QRect/QRectF                              rect
QMatrix4x4                                matrix4x4
QQuaternion                               quaternion
QVector2D                                 vector2d
QVector3D                                 vector3d
QVector4D                                 vector4d
QVariant                                  var
QObject*                                  var              object
QMap<QString, QVariant> (QVariantMap)     var              object
QByteArray                                var              ArrayBuffer
QList<QVariant> (QVariantList)            var/list         Array (with differences)
QList/QVector/std::vector<int>            var/list         Array (with differences)
QList/QVector/std::vector<bool>           var/list         Array (with differences)
QList/QVector/std::vector<qreal>          var/list         Array (with differences)
QList/QVector/std::vector<QUrl>           var/list         Array (with differences)
QList/QVector/std::vector<QString>        var/list         Array (with differences)
QStringList                               var/list         Array (with differences)
QList<QObject*>                           var/list         Array (with differences)

• Non-registered types convert to/from QVariant using 'var'
• Non-registered container with type convert to/from QVariantList, even if type is registered
• Converted Javascript arrays have a few differences from native Javascript arrays:
   - delete myArray[i] sets element as default constructed instead of undefined
   - resizing larger will default construct elements instead of be undefined
   - Using index > INT_MAX will fail as Qt container class indexing is signed, not unsigned
• Avoid std::vectors as they are copied each access whether Q_PROPERTY or Q_INVOKABLE
• Q_PROPERTY container more expensive to read/write than Q_INVOKABLE returned container
**************************************************************************************************************/

// USING QOBJECTS WITH QML
// Data passed via Q_PROPERTY, Q_INVOKABLE, setContextProperty or setRootContext
// Best to set CppOwnership for all parentless QObjects passed to QML
// Officially, only Q_INVOKABLE will automatically take ownership of parentless QObjects unless CppOwnership
// QGadgets: to use, needs Q_GADGET registration with Variant/Property system and is passed by value
// QObjects: to use, doesn't need any registration and is passed as QObject*
Q_PROPERTY(QList<QObject*> objList MEMBER m_objList) // Has cpp owernship
Q_PROPERTY(QObject* obj MEMBER m_obj) // Has cpp owernship
Q_INVOKABLE QObject* myFn() { ... } // Returning parentless QObject* has qml ownership
Q_INVOKABLE QList<QObject*> myFn()  { ... } // Returning parentless QList<QObject*> has cpp ownership
QQmlEngine::setObjectOwnership(myObj, QQmlEngine::CppOwnership); // Force cpp ownership
QQmlEngine::setObjectOwnership(myObj, QQmlEngine::JavaScriptOwnership); // Force QML ownership

// REGISTERING COMPONENTS WITH QML
// To create QML Component, must be QObject derived
// use 'import MyInclude 1.0' / MyClass {}
qmlRegisterType<N::MyClass>("MyInclude", 1, 0, "MyClass");

// REGISTERING CLASS ENUMS WITH QML
// Requires Q_ENUM registration with Variant
// Does not need further registration to use for class property/signals
// Requires further registration to use named enums in QML
// use 'import MyInclude 1.0' / 'MyClassEnum.ONE'
qmlRegisterType<N::MyClass>("MyInclude", 1, 0, "MyClassEnum"); 

// REGISTERING Q_NAMESPACE ENUMS WITH QML
// Requires Q_ENUM_NS registration with Variant
// use 'import MyInclude 1.0' / 'N.MyEnum.ONE'
qmlRegisterUncreatableMetaObject(N::staticMetaObject, "MyInclude", 1, 0,
    "N", "Error msg if try to create MyEnum object");

// REGISTERING SINGLETONS WITH QML
// Will be owned by QML, use 'import MyInclude 1.0' and 'MySingleton.Member'
qmlRegisterSingletonType(QUrl("qrc:///MyGlobal.qml"), "MyInclude", 1, 0, "MySingleton")
qmlRegisterSingletonType("MyInclude", 1, 0, "MySingleton", 
    [](QQmlEngine*, QJSEngine*)->QObject* { return new MySingleton(); });

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FILE SYSTEM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                               
// QFileInfo
// If path is a directory, treat as filepath but without a name/extension
QFileInfo info(path)
info.absoluteDir() // Returns QDir using absolutePath()
info.absoluteFilePath() // Returns path as absolute QString, keeps dots/symlinks
info.absolutePath() // Returns path without the filename as absolute QString, keeps dots/symlinks
info.baseName() // Returns the filename without directory or extensions
info.birthTime() // Returns QDateTime of date and time when the file was created
info.canonicalFilePath() // Returns path QString, removes dots/symlinks, empty if doesn't exist 
info.canonicalPath() // Returns path without filename QString, removes dots/symlinks, empty if doesn't exist
info.completeBaseName() // Returns the filename as QString without directory or last extension
info.completeSuffix() // Returns all extensions as QString, does not start with '.'
info.dir() // Returns parent directory as QDir, even if info holds a directory         
info.exists() // Returns true if file exists
info.fileName() // Returns full file name as QString including all extensions
info.filePath() // Returns path (which may be absolute or relative)
info.isAbsolute() // Returns true if path is absolute
info.isDir() // Returns true if path is a directory
info.isExecutable() // Returns true if path is an executable
info.isFile() // Returns true if path is a file
info.isHidden() // Returns true if path is hidden
info.isNativePath() // Returns true if path can be used with the OS native file system, minus encoding requirements
info.isReadable() // Returns true if user can read the file
info.isRelative() // Returns true if path is relative
info.isSymLink() // Returns true if path is a symlink
info.isWritable() // Returns true if path is writable
info.lastModified() // Returns QDateTime when path was last modified
info.lastRead() // Returns QDateTime when path was last accessed
info.makeAbsolute() // Converts a relative path to absolute if needed
info.path() // Returns path without the filename (which may be absolute or relative)
info.size() // Returns qint64 of size in bytes
info.suffix() // Returns final extension of file, without the .
QFileInfo::exists(path) // Returns true if file exists, faster than QFileInfo(path).exists()

// QDir
// Can hold both directories and files
// All entryList calls return just the folder/filename, need to use absoluteFilePath
QDir dir(path) // Root directory
dir.absoluteFilePath(filename) // Use with entryList to make into absolute path
dir.absolutePath() // Returns path as absolute, may have symlink but no dots
dir.canonicalPath() // Returns path without symlinks and dots, empty if doesn't exist
dir.cd(path) // Cd to a path, can use . and ..
dir.cdUp() // Move up one directory
dir.count() // Returns uint total amount of files/folders in path
dir.dirName() // Returns name of directory
dir.entryList(nameFilters, filterFlags, sortFlags) // Search directory recursively, returns QStringList
dir.entryList(nameFilters) // Not using any args will use the stored filterFlags/sortFlags
dir.entryList(filterFlags, sortFlags) // Search directory recursively with filter flags, returns QStringList
dir.entryList() // Not using any args will use the stored filterFlags/sortFlags
dir.exists() // Whether path exists
dir.isAbsolute() // Whether path is absolute
dir.isEmpty(filters) // Optional filters, whether directory is empty
dir.isReadable() // Returns true if readable
dir.isRelative() // Returns true if path is relative
dir.isRoot() // Returns true if path is a system root directory
dir.makeAbsolute() // Makes the path absolute if needed
dir.mkdir(folder) // Make a folder under path, returns true if success
dir.mkpath(path) // Make a path under path, will create all folders if needed, returns true if success
dir.path() // Returns path, keeps symlinks but removes dots
dir.remove(filename) // Removes file in path, returns true if success
dir.removeRecursively() // Removes path including all children, returns true if success
dir.rename(oldFileName, newFileName) // Renames a file, returns true if success
dir.setNameFilters(QStringList("*.qml", "*.txt")) // Extension types to filter searches with
dir.setSorting(sortFlags) // Flags to use with entryList
QDir::cleanPath(path) // Returns normalized path; removes dots, seperators become single /, keeps symlinks
QDir::current() // Returns application's current directory as QString
QDir::currentPath() // Returns application's current path as QString                               
QDir::drives() // Returns QFileInfoList of all root drives in the system
QDir::home() // Returns user's home directory as QString
QDir::homePath() // Returns the absolute path of the user's home directory as QString
QDir::listSeparator() // Returns native path list seperator ; or :
QDir::root() // Returns root directory as QDir
QDir::rootPath() // Returns the absolute path of the root directory (eg. c:/)
QDir::separator() // Returns QChar native directory seperator
QDir::temp() // Returns folder for temp files as QDir
QDir::toNativeSeparators(path) // Converts seperators to native seperator
    
// QIODevice
// base interface class of all I/O devices

// QDataStream
// serialization of binary data to a QIODevice

// QFile
// Interface for reading from and writing to files

// QDir Filter Flags
QDir::NoFilter         // No filter flag used
QDir::Dirs             // Apply filters to directory names
QDir::AllDirs          // Don't apply the filters to directory names
QDir::Files            // List files
QDir::Drives           // List disk drives
QDir::NoSymLinks       // Do not list symbolic links
QDir::NoDotAndDotDot   // NoDot | NoDotDot
QDir::NoDot            // Do not list the special entry "."
QDir::NoDotDot         // Do not list the special entry ".."
QDir::AllEntries       // Dirs | Files | Drives
QDir::Readable         // List files which application has read access
QDir::Writable         // List files which application has write access
QDir::Executable       // List files which application has execute access
QDir::Modified         // Only list files that have been modified
QDir::Hidden           // List hidden files
QDir::System           // List system files
QDir::CaseSensitive    // The filter should be case sensitive
    
// QDir Sort Flags
QDir::NoSort           // No sorting
QDir::Name             // Sort by name
QDir::Time             // Sort by time (modification time)
QDir::Size             // Sort by file size
QDir::Type             // Sort by file type (extension)
QDir::Unsorted         // Do not sort
QDir::NoSort           // Not sorted by default
QDir::DirsFirst        // Put the directories first, then the files
QDir::DirsLast         // Put the files first, then the directories
QDir::Reversed         // Reverse the sort order
QDir::IgnoreCase       // Sort case-insensitively
QDir::LocaleAware      // Sort using the current locale settings

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT THREADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QOBJECTS
• Has thread affinity: lives on a specific thread, query using obj.thread()
• Must have same thread as parent, obj.setParent will fail if not
• Will recieve queued signals/event from same or other threads, slot is always called in own thread
• If no thread affinity or in thread without event loop, cannot process queued signals/events
• Can change with object.moveToThread(), must not have a parent, all children auto changed too
• Use deleteLater if object is accessed across multiple threads

SIGNALS / SLOTS
• Thread safe to connect, disconnect and emit signals
• Connection type default is AutoConnection, thread safe and auto copies arguments
• AutoConnection Becomes QueuedConnection if signal/slot objects have different thread affinity
• QueuedConnection signals will be sent to slot object's event queue and called synchronously

LIMITATIONS ON QTHREAD
• Cannot modify gui (QQuick, QWidgets etc.)
• Cannot call OpenGL unless QOpenGLContext::supportsThreadedOpenGL is true
• All QObjects must be destroyed before QThread is destroyed- can connect deleteLater to QThread::finished
**************************************************************************************************************/

class MyThread : public QThread
{
    Q_OBJECT
    void run() override {
        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);
};

MyThread* myThread = new MyThread(this);
connect(myThread, &MyThread::resultReady, this, &MyObject::handleResults);
connect(myThread, &MyThread::finished, myThread, &QObject::deleteLater);
workerThread->start();

QThread::sleep(3); //seconds
QThread::currentThreadId();
QThread::currentThread();
QtConcurrent::run([](){});

// ENFORCING THREAD AFFINITY
// Can either use signals/slots or QMetaObject::invokeMethod with an Auto Connection
QMetaObject::invokeMethod(myObj, [myObj]() {
    Q_ASSERT(myObj->thread() == QThread::currentThread());
});
QObject::connect(myObj, &MyClass::signal, [myObj]() {
    Q_ASSERT(myObj->thread() == QThread::currentThread());
});

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT ALGORITHMS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
// QtMath
qAcos(v) // Takes qreal radians, returns qreal
qAsin(v) // Takes qreal radians, returns qreal
qAtan2(y, x) // Takes qreal radians, returns qreal
qAtan(v) // Takes qreal radians, returns qreal
qCeil(v) // Takes qreal, returns int
qCos(v) // Takes qreal radians, returns qreal
qDegreesToRadians(v) // Takes float/double degrees, returns float/double radians
qExp(v) // Takes qreal, feturns qreal eᵛ
qFabs(v) // Takes qreal, returns absolute qreal value
qFloor(v) // Takes qreal, returns floored int
qLn(v) // Takes qreal, returns qreal natural log of v
qNextPowerOfTwo(v) // Takes/returns quint32/qint32/quint64/qint64, returns nearest power of two greater than v
qPow(x, y) // Takes qreal, returns xʸ
qRadiansToDegrees(v) // Takes float/double degrees, returns float/double degrees
qSin(v) // Takes qreal radians, returns qreal
qSqrt(v) // Takes qreal, returns square root qreal
qTan(v) // Takes qreal radians, returns qreal
M_PI // π
M_PI_2 // π / 2
M_PI_4 // π / 4
    
// QtGlobal
qAbs(v) // Templated, returns absolute value of v
qAsConst(v) // Templated, takes T& and returns const T&
qBound(min, v, max) // Templated, returns v clamped
qEnvironmentVariable(name) // Returns QString of env var with name
qEnvironmentVariable(name, default) // Returns QString of env var with name or default if doesn't exist
qEnvironmentVariableIntValue(name, &ok) // Returns int of env var with name, ok set to false if doesn't exist
qEnvironmentVariableIsEmpty(name) // Returns if env var with name is empty
qEnvironmentVariableIsSet(name) // Returns if env var with name is set
qgetenv(name) // Returns env var with name as QByteArray
qputenv(name, value) // Sets env var with value const QByteArray&, will create, returns false if failed
qunsetenv(name) // Deletes the env var, returns true if success
qFuzzyCompare(a, b) // Takes double/float, returns true if considered equal
qFuzzyIsNull(v) // Takes double/float, returns truen if absolute value of v is within 0.000000000001 of 0.0
qInf() // Returns the bit pattern for an infinite number as a double
qInstallMessageHandler(handler) // Install a new QtMessageHandler, returns the old one
qIsFinite(v) // Takes double/float, returns if v is a finite number
qIsInf(v) // Takes double/float, returns if v is an infinite number
qIsNaN(v) // Takes double/float, returns if v is not an number
qMax(a, b) // Templated, returns max of a and b
qMin(a, b) // Templated, returns min of a and b
qQNaN() // Returns the bit pattern of a quiet NaN as a double
qRound64(v) // Takes double/float, rounds (0.5 -> 1.0), returns qint64
qRound(v) // Takes double/float, rounds (0.5 -> 1.0), returns int
qPrintable(str) // Takes QString, does str.toLocal8Bit().constData()
qUtf8Printable(str) // Takes QString, does str.toUtf8().constData()
qSNaN() // Returns the bit pattern of a signalling NaN as a double
qVersion() // Returns the version number of Qt
qtTrId(id) // Finds and returns a translated QString
qConstOverload<Arg1, Arg2>(&MyClass::fn) // Converts address to const version
qNonConstOverload<Arg1, Arg2>(&MyClass::fn) // Converts address to non-const version
qOverload<Arg1, Arg2>(&MyClass::fn) // Converts address to an overloaded version
QOverload<Arg1, Arg2>::of(&MyClass::fn) // Alternate syntax
    
// QtAlgorithm
// STL algorithms should be used for Qt containers rather than deprecated QtAlgorithm
qCountLeadingZeroBits(v) // Takes all quints, returns uint of no. of consecutive zero bits
qCountTrailingZeroBits(v) // Takes all quints, returns uint of no. of consecutive zero bits
qDeleteAll(begin, end) // Takes container iterator with pointers, calls delete on pointers, doesn't clear
qDeleteAll(container) // Takes container with pointers, calls delete on pointers, doesn't clear
qPopulationCount(v) // Takes all quints, returns no. of bits set in v, or the 'Hamming Weight of v'

