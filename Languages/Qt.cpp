/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FRAMEWORK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
Source: https://code.woboq.org/qt5/
QtCore               Core non-graphical classes used by other modules
QtGUI                Base classes for graphical user interface (GUI) components. Includes OpenGL
QtMultimedia         Classes for audio, video, radio and camera functionality
QtMultimediaWidgets  Widget-based classes for implementing multimedia functionality
QtQML                Classes for QML and JavaScript languages
QtQuick              A declarative framework for building highly dynamic applications with custom UI
QtQuickControls      Reusable Qt Quick based UI controls to create classic desktop-style user interfaces
QtQuickDialogs       Types for creating and interacting with system dialogs from a Qt Quick application
QtQuickLayouts       Layouts are items that are used to arrange Qt Quick 2 based items in the UI
QtTest               Classes for unit testing Qt applications and libraries
QtWidgets            Classes to extend Qt GUI with C++ widgets

IMPLICIT SHARING (COPY-ON-WRITE)
• QObjects do not use it as they cannot be copied
• All containers except: QVarLengthArray, QMimeData, QQmlListProperty, QQmlPropertyMap, QJSValue
• QByteArray uses it but does not detach with [] as it returns QByteRef
• All copy-able components: QBrush, QImage, QDateTime, QDir, QFileInfo, QLocale, QUrl etc.
**************************************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
• Meta Object Compilier code generator uses Q_OBJECT macro to generate moc cpp file
• Ability to use qobject_cast, signals, slots, property system

QOBJECT LIMITATIONS:
• Doesn't have a copy constructor or assignment operator
• Can't be created before QApplication (undefined behaviour)
• All MOC/Signal/Slot limitations

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

PROPERTY SYSTEM:
• To create dynamic QML properties use QQmlPropertyMap (Qt Containers)
• To create dynamic C++ properties use QObject::setProperty
MEMBER    [var]   Required if READ not used, implicitly creates getter/setter with emitting signal
READ      [fn]    Required if MEMBER not used, must be 'arg fn()'
WRITE     [fn]    Optional, can be used with either READ or MEMBER, must be 'void fn(arg)'
NOTIFY    [fn]    Optional, takes signal with one or no arguments, 'fn(arg)' or 'fn()'
RESET     [fn]    Optional, called when assigned 'undefined' in qml, must be 'void fn()'
STORED    [bool]  Optionals, default true, whether property value must be saved when storing object's state
REVISION  [int]   Optional, which qml import is supported, defaults all/0
BINDING   [fn]    Optional, 6.0+ function to return the Bindable<T> of the property
CONSTANT          Optional, makes readonly
FINAL             Optional, can enable optimizations, indicates shouldn't override though not enforced by moc
REQUIRED          Optional, enforces that property must be set in qml otherwise error
**************************************************************************************************************/

namespace N
{
    Q_NAMESPACE
    class MyClass : public QObject
    {
        Q_OBJECT // required for all moc provided features
        Q_CLASSINFO("Author", "Name") // attach additional name/value pairs to the class's meta-object
        Q_DISABLE_COPY(MyClass) // Required for singleton classes
        Q_CLASSINFO("DefaultProperty", "children")
        
        Q_PROPERTY(MyValue value MEMBER m_value)
        Q_PROPERTY(MyValue value READ getValue WRITE setValue NOTIFY mySignal)
        Q_PROPERTY(MyClass obj MEMBER m_obj) // Requires registration for QML use
        Q_PROPERTY(N::MyClass obj MEMBER m_obj) // If forward declared type, must use full namespace
        Q_PROPERTY(QQmlListProperty<QObject> children READ children)
        
        // Bindable properties (6.0+)
        Q_PROPERTY(MyValue value READ getValue WRITE setValue BINDABLE bindableValue)
        Q_OBJECT_BINDABLE_PROPERTY(MyClass, MyValue, m_value)

    public:
        explicit MyClass(QObject* parent = nullptr) : QObject(parent) {}   

        enum class MyEnum { ONE, TWO, THREE };
        Q_ENUM(MyEnum)
        enum MyFlag { One=0x01, Two=0x02, Three=0x04 };
        Q_DECLARE_FLAGS(MyFlags, MyFlag) // Creates type 'MyFlags'
        Q_FLAG(MyFlag)
        Q_FLAGS(MyFlags)
        
        // Bindable properties (6.0+)
        QBindable<MyValue> bindableValue() { return &m_value }

        // Can be overloaded, virtual, pure virtual, with defaults
        const MyValue& getValue() const { return m_value; }
        void setValue(const MyValue& value) { m_value = value; }
        Q_INVOKABLE void myFn() { }
    };

    // GADGETS
    struct MyGadget
    {
        Q_GADGET // Value-type used with variant, doesn't increase class size
        Q_PROPERTY(QString name MEMBER m_name)

    public:
        Q_INVOKABLE void myFn() { }
        bool operator==(const Gadget& g) const { ... }
        bool operator!=(const Gadget& g) const { ... }
    };
    Q_DECLARE_METATYPE(MyGadget) 
     
    // ENUMS
    enum class MyEnum { One, Two, Three };
    Q_ENUM_NS(MyEnum) 

    // FLAGS
    enum MyFlag { One=0x01, Two=0x02, Three=0x04 };
    Q_FLAG_NS(MyFlag) 
    Q_DECLARE_FLAGS(MyFlags, MyFlag) // Creates type 'Flags'
}
Q_DECLARE_OPERATORS_FOR_FLAGS(N::MyFlags) // Allows operator use, must be outside namespace
Q_DECLARE_OPERATORS_FOR_FLAGS(MyClass::MyFlags) // Allows operator use, must be outside namespace
Q_DECLARE_METATYPE(MyClass::MyFlags) // Must be outside namespace

// QObject
obj.objectName // Property; User-defined name of object instance, blank as default
obj.setProperty("value", v); // Auto creates if doesn't exist, fires signal if set on qml object
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
obj.setParent(obj2) // Sets parent, must have same thread as parent
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
QMetaObject::invokeMethod(myObj, []{}, connection); // Connection default arg is AutoConnection

// QMetaEnum
QMetaEnum metaEnum(QMetaEnum::fromType<N::MyEnum>());
metaEnum.valueToKey(N::MyEnum::ONE) // Returns const char* or null if not found
metaEnum.keyToValue("ONE", &isValid) // Returns int or -1 if not found, optional bool
metaEnum.keyCount() // Returns number of keys/values
metaEnum.key(index) // Returns const char* key from int index, or null if doesn't exist
metaEnum.value(index) // Returns int value with the given index, or returns -1 if none found
 
// QFlags
// Requires Q_DECLARE_FLAGS and Q_DECLARE_OPERATORS_FOR_FLAGS, can implicity convert to unsigned int
// Requires Q_DECLARE_METATYPE if wanting to use it with property system
N::MyFlags flags = N::ONE | N::TWO
flags.testFlag(a::ONE) // returns true if flags includes ONE
flags ^= N::TWO // add TWO

// QBindable (6.0+)
myObject->bindableValue().setBinding([obj2](){ return obj2->x() });

// Registering with QMetaType
// Used to pass non-QObject types with QVariant and the property system (queued connections, Q_PROPERTY, Q_INVOKABLE)
// Register Macros must be placed after class in .h
// Type registered must be copy-constructable and have default constructor
// Containers don't need to be registered for variant, but undefined if used in QML; Use QVariantList instead
Q_DECLARE_METATYPE(MyGadget) // Allows use with variant: myVariant.value<N::MyGadget>()
qRegisterMetaType<N::MyGadget>(); // Allows use with property system (eg. queued connections, Q_PROPERTY, Q_INVOKABLE)
qRegisterMetaType<std::string>("std::string");
qRegisterMetaType<std::unordered_map<std::string, std::string>>("std::unordered_map<std::string, std::string>");
qRegisterMetaType<MyClass::MyFlags>(); // Required as Q_FLAGS doesn't register
Q_ENUM(MyEnum) // Registers with variant and property system, _NS version for Q_NAMESPACE
Q_FLAG(MyFlag) // Registers with variant and property system, _NS version for Q_NAMESPACE

// Registering with Streaming
// Allows use with drag/drop systems
qRegisterMetaTypeStreamOperators<N::MyClass>("MyClass");
QDataStream& operator<<(QDataStream& out, const MyClass& obj);
QDataStream& operator>>(QDataStream& in, MyClass& obj);

// Type Info
// Macro must placed after class in .h
// Q_PRIMITIVE_TYPE leaves obj memory unitialised, means trivally copyable
// Q_MOVABLE_TYPE uses std::memcpy rather than copy ctor to move obs around, means trivally relocatable
// Q_MOVABLE_TYPE does shallow move; don't use for types that self refer (pimpl with ptr back to parent)
Q_DECLARE_TYPEINFO(N::MyClass, Q_COMPLEX_TYPE) // Default
Q_DECLARE_TYPEINFO(N::MyEnum, Q_PRIMITIVE_TYPE)
Q_DECLARE_TYPEINFO(N::MyGadget, Q_MOVABLE_TYPE)
QTypeInfoQuery<N::MyClass>::isRelocatable // Query type info

// QObjects Deletion
obj.deleteLater() /*or*/ delete obj /*or*/ qDeleteAll(objs) /*or*/ { obj }
emit destroyed() // Emitted just before obj deleted, children deleted after signal

// QObject Reflection
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

// QObject Iterate Properties
auto metaObject = myObject->metaObject();
for (int i = 0; i < metaObject->propertyCount(); ++i)
{
    const auto metaProperty = metaObject->property(i);
    const auto variant = myObject->property(metaProperty.name());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIGNALS / SLOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Can only be used by Q_OBJECT, not Q_GADGET, due to moc requirements
• On signal emit, all slots in order of connection are immediately notified, can't be async
• Slots can be virtual/pure virtual
• Default argument type must match between signals/slots, don't have to both have default
• Good design to not have return values for signals/slots but not disallowed

SIGNAL LIMITATIONS:
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
• QueuedConnection requires types requirested with qRegisterMetaType
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

// SIGNAL SPY
// Requires Qt5::Test
QSignalSpy spy(sender, &Sender::mySignal)
spy.isValid() // Returns true if setup correctly
spy.wait(timeoutMs) // Starts an event loop until signal or timed out (returns false if timed out)
    
// SIGNAL BLOCKER
// Blocks signals from obj in scope, same as turning on/off obj->blockSignals
const QSignalBlocker blocker(obj);

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
const auto button = Qt::MouseButton::LeftButton; // QML Qt.LeftButton
QCoreApplication::postEvent(object, 
    new QMouseEvent(QEvent::MouseButtonPress, QPointF(0, 0), button, button, Qt::KeyboardModifier::NoModifier), 
    Qt::NormalEventPriority);

const auto key = Qt::Key::Key_Control; // QML Qt.Key_Control, Qt::CTRL is an alternative for modifiers
const auto key = Qt::Key::Key_Escape; // QML Qt.Key_Escape
QCoreApplication::postEvent(object,
    new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, QKeySequence(key).toString()),
    Qt::HighEventPriority);

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

// QTimer
// Inherits QObject
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

// QUuid
// 128-bit unique number
QUuid id // Null ("{00000000-0000-0000-0000-000000000000}") by default
QUuid id(str) // Format "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}", {} optional, if fails will be null
id.isNull() // Returns if null id
id.toString(QUuid::StringFormat::WithBraces) // Default, QUuid::WithoutBraces also possible
QUuid::createUuid() // Generate a new unique QUuid
QUuid::fromString(str) // Format "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}", {} optional, if fails will be null

// QDateTime
// Combines a QDate and QTime
QDateTime dateTime
QDateTime::currentDateTime() // Returns QDateTime
QDateTime::fromString("2019-01-01", Qt::ISODate) // Takes QString and returns QDateTime
dateTime.toString(Qt::ISODate) // Returns QString
dateTime.toString("yyyy-MM-ddThh:mm:ss") // XML datetime format
dateTime.toUTC() // Used for comparing date times with < and >
dateTime.addSecs(1) // Add seconds to the date time
dateTime.addMins(1) // Add minutes to the date time
dateTime.addHours(1) // Add hours to the date time
dateTime.addDays(1) // Add days to the date time
dateTime.addYears(1) // Add years to the date time

// QDate
QDate date
QDate::currentDate() // Returns QDate
date.toString("yyyy-MM-dd") // XML date format

// QTime
QTime time
QTime::currentTime() // Returns QTime
time.secsTo(time2) // Difference in time in seconds
time.toString("hh:mm:ss") // XML time format

// QSettings
// Persistent platform-independent application settings
QSettings settings
settings.setValue("key", value);
settings.value("key", defaultValue) // Returns value or QVariant default value if doesn't exist
settings.sync() // Writes to registry, auto called by QSettings destructor
settings.status() // Returns QSettings::Status, call sync first to ensure up to date value
settings.remove("key")
settings.contains("key") 
settings.clear()
settings.allKeys() // Returns QStringList
    
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
// Weak pointer for QObject* that may have a parent
QPointer<T> ptr(new T(parent));
ptr.clear();             // Clears pointer and decrements ref count
ptr.isNull();            // Returns if null
ptr.data();              // Returns T*

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT APPLICATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QCoreApplication
// Singleton
app.organizationName
app.applicationName
app.applicationVersion
app.organizationDomain
app.installNativeEventFilter(filter) // Takes QAbstractNativeEventFilter
app.removeNativeEventFilter(filter) // Takes QAbstractNativeEventFilter
app.notify(receiver, event)
app.quit()
app.aboutToQuit() // Signal
QCoreApplication::instance()
QCoreApplication::applicationDirPath()
QCoreApplication::applicationFilePath()
QCoreApplication::applicationName()
QCoreApplication::applicationVersion()
QCoreApplication::organizationName()
QCoreApplication::setApplicationName(str) // Required for QSettings
QCoreApplication::setApplicationVersion(str)
QCoreApplication::setOrganizationName(str) // Required for QSettings
QCoreApplication::arguments()
QCoreApplication::eventDispatcher() // Returns QAbstractEventDispatcher*
QCoreApplication::setEventDispatcher(dispatcher) // Takes QAbstractEventDispatcher
QCoreApplication::exit(code) // Code defaults 0, 
QCoreApplication::installTranslator() // Takes QTranslator
QCoreApplication::removeTranslator() // Takes QTranslator
QCoreApplication::libraryPaths() // Returns QStringList
QCoreApplication::addLibraryPath(path)
QCoreApplication::removeLibraryPath(path)
QCoreApplication::setLibraryPaths(paths)    
QCoreApplication::postEvent(receiver, event)
QCoreApplication::postEvent(receiver, event, priority)
QCoreApplication::processEvents()
QCoreApplication::processEvents(flags)
QCoreApplication::processEvents(flags, ms)
QCoreApplication::removePostedEvents(receiver)
QCoreApplication::removePostedEvents(receiver, eventType)
QCoreApplication::sendEvent(receiver, event)
QCoreApplication::sendPostedEvents()
QCoreApplication::sendPostedEvents(receiver)
QCoreApplication::sendPostedEvents(receiver, eventType)
QCoreApplication::setAttribute(attribute, on) // Qt::ApplicationAttribute, on defaults to true
QCoreApplication::testAttribute(attribute) // Qt::ApplicationAttribute
QCoreApplication::translate("context", "text") // Translate text directly instead of using QObject::tr

// QGuiApplication
// Inherits QCoreApplication, Singleton
app.applicationDisplayName
app.desktopFileName
app.primaryScreen // Returns QScreen* const
app.platformName // Readonly 
app.layoutDirection // Qt::LayoutDirection
app.windowIcon // QIcon
app.devicePixelRatio()
app.sessionId()
app.sessionKey()
app.focusObjectChanged(focusObject) // Signal when focus object changes, QObject*
QGuiApplication::allWindows() // QWindowList
QGuiApplication::applicationState() // Qt::ApplicationState
QGuiApplication::clipboard() // Returns QClipboard*
QGuiApplication::focusObject() // Returns QObject*
QGuiApplication::focusWindow() // Returns QWindow*
QGuiApplication::highDpiScaleFactorRoundingPolicy() // Returns Qt::HighDpiScaleFactorRoundingPolicy
QGuiApplication::inputMethod() // Returns QInputMethod*
QGuiApplication::keyboardModifiers() // Returns Qt::KeyboardModifiers
QGuiApplication::modalWindow() // Returns QWindow*
QGuiApplication::mouseButtons() // Returns Qt::MouseButtons
QGuiApplication::palette() // Returns QPalette
QGuiApplication::platformNativeInterface() // Returns QPlatformNativeInterface*
QGuiApplication::primaryScreen() // Returns QScreen*
QGuiApplication::screenAt(point) // Returns QScreen*, takes QPoint
QGuiApplication::screens() // Returns QList<QScreen*>
QGuiApplication::setHighDpiScaleFactorRoundingPolicy(policy) // Qt::HighDpiScaleFactorRoundingPolicy
QGuiApplication::setPalette(palette) // QPalette
QGuiApplication::styleHints() // Returns QStyleHints*
QGuiApplication::topLevelAt(point) // Returns QWindow*, takes QPoint
QGuiApplication::topLevelWindows() // Returns QWindowList
    
// QApplication
// Inherits QGuiApplication, Singleton
// Handles QWidget specific initialization, finalization
app.doubleClickInterval
app.keyboardInputInterval
app.startDragDistance
app.startDragTime
app.styleSheet
app.wheelScrollLines
app.windowIcon
app.closeAllWindows()
app.focusChanged(old, now) // Signal, QWidget* for both
QApplication::activeModalWidget() // Returns QWidget*
QApplication::activePopupWidget() // Returns QWidget*
QApplication::activeWindow() // Returns QWidget*
QApplication::allWidgets() // Returns QWidgetList
QApplication::desktop() // Returns QDesktopWidget*
QApplication::focusWidget() // Returns QWidget*
QApplication::palette(widget) // Takes const QWidget*
QApplication::palette("className") // Returns QPalette
QApplication::setActiveWindow(widget) // Takes QWidget*
QApplication::setPalette(palette, "className") // Takes const QPalette&
QApplication::setStyle(style) // Takes QStyle*
QApplication::setStyle(styleStr) // Takes str, returns QStyle*
QApplication::style() // Returns QStyle*
QApplication::topLevelAt(point) // Returns QWidget*, takes QPoint
QApplication::topLevelAt(x, y) // Returns QWidget*, takes int
QApplication::topLevelWidgets() // Returns QWidgetList
QApplication::widgetAt(const QPoint &point) // Returns QWidget*, takes QPoint
QApplication::widgetAt(x, y) // Returns QWidget*, takes int
    
// Qt::ApplicationAttribute Enum
AA_NativeWindows // Ensures that widgets have native windows
AA_DontCreateNativeWidgetSiblings // Siblings of native widgets stay non-native
AA_PluginApplication // Application is a Qt plugin, suppressing some initalization
AA_DontUseNativeMenuBar // Suppress native menu bars
AA_UseHighDpiPixmaps // Scales pixmaps, should divide by devicePixelRatio if this is on
AA_SetPalette // Indicates whether a palette was explicitly set on the QGuiApplication
AA_EnableHighDpiScaling // Enables high-DPI scaling, must be set before QGuiApplication is created
AA_UseStyleSheetPropagationInWidgetStyles // Allow QWidget stylesheet palette and font propagation
AA_DontUseNativeDialogs // Don't use native dialogs provided by the platform
AA_DisableShaderDiskCache // Disables caching of shader program binaries on disk
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT QUICK WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
// Has a single invisible root item
// Has its own scene graph which is invalidated when window is hidden
QQuickWindow window;
window.color // QColor used to clear the back buffer, default white
window.activeFocusItem // readonly property QQuickItem* const which has active focus or null
window.contentItem // readonly property QQuickItem* const for inivisble root item
window.releaseResources() // Release redundant resources currently held
window.sceneGraphError(error, message) // Signal emitted when error occurs
window.update() // Schedules the window to render another frame
window.effectiveDevicePixelRatio() // Returns the device pixel ratio for this window
window.grabWindow() // Returns QImage of window contents
    
// QQuickView 
// Inherits QQuickWindow, automatically load and display a QML scene from an url
// Best to also listen to the Qt message handler for errors / warnings when using
QQuickView view
view.source // QUrl
view.rootContext() // Returns QQmlContext*
view.rootObject() // Returns QQuickItem*
view.setSource(QUrl("qrc:/main.qml"))
view.setTitle("title")
view.show()
view.engine() // Returns QQmlEngine*
view.errors() // Returns QList<QQmlError>
    
// QQuickWidget
// Inherits QWidget, wrapper for QQuickWindow, allows integrating QML with QWidgets UI
// Less stacking order restrictions, though slower compared to QQuickWindow/QQuickView
// Disables the threaded render loop on all platforms
// Avoid calling winId; triggers creation of a native window, resulting in reduced performance
QQuickWidget widget
widget.source // QUrl
widget.rootContext() // Returns QQmlContext*
widget.rootObject() // Returns QQuickItem*
widget.setSource(QUrl("qrc:/main.qml"))
widget.engine() // Returns QQmlEngine*
widget.errors() // Returns QList<QQmlError>
widget.show()

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
// QT QUICK / QML
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************************
CONVERTING BETWEEN C++/QML
• Data passed via Q_PROPERTY, Q_INVOKABLE/slots, setContextProperty or setRootContext
• Unsupported types can be passed to/from QML without registering, but cannot be used unless registered
• QObject* derived types don't require registering and can be fully used, except if MyClass* is used
• QJSValue/QQmlPropertyMap can be used to pass dynamic objects/functions to/from QML
• quint64 looses precision when passed to QML as Javascript Number doesn't have enough precision

CONVERTING CONTAINERS BETWEEN C++/QML
• If unsupported Container<T>, must use QVariantList, even if T is supported
• Converted Javascript arrays have a few differences from native Javascript arrays:
   - delete myArray[i] sets element as default constructed instead of undefined
   - resizing larger will default construct elements instead of be undefined
   - Using index > INT_MAX will fail as Qt container class indexing is signed, not unsigned
• Avoid std::vectors as they are copied each access whether Q_PROPERTY or Q_INVOKABLE
• Q_PROPERTY container more expensive to read/write than Q_INVOKABLE returned container

QML SUPPORTED TYPES
CPP                                       QML              JAVASCRIPT
bool                                      bool             Boolean 
unsigned int/int                          int              Number
double                                    double           Number
float/qreal                               real             Number
QString                                   string           String
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
QObject*                                  var              Object
QMap<QString, QVariant> (QVariantMap)     var              Object
QQmlPropertyMap                           var              Object
QByteArray                                var              ArrayBuffer
QList<QVariant> (QVariantList)            var/list         Array (with differences)
QList/QVector/std::vector<int>            var/list         Array (with differences)
QList/QVector/std::vector<bool>           var/list         Array (with differences)
QList/QVector/std::vector<qreal>          var/list         Array (with differences)
QList/QVector/std::vector<QUrl>           var/list         Array (with differences)
QList/QVector/std::vector<QString>        var/list         Array (with differences)
QStringList                               var/list         Array (with differences)
QList<QObject*>                           var/list         Array (with differences)
QJSValue                                  any              Any

FOUR WAYS TO CREATE QML ITEMS
• QObject: Not graphical
• QQuickItem: graphical with Scene Graph Nodes (QQuickItem::updatePaintNode)
• QQuickPaintedItem: graphical with QPainter (QQuickPaintedItem::paint), slow
• QQuickFramebufferObject: requires QQuickFramebufferObject::Renderer, uses render targets
**************************************************************************************************************/

// OWNERSHIP WITH QML
// Best to set CppOwnership for all parentless QObjects passed to QML
// Officially only Q_INVOKABLE will automatically take ownership of parentless QObjects unless CppOwnership
Q_PROPERTY(QObject* obj MEMBER m_obj) // Has cpp owernship
Q_INVOKABLE QObject* myFn() {...} // Returning parentless QObject* has qml ownership
Q_INVOKABLE QList<QObject*> myFn()  {...} // Returning parentless QList<QObject*> has cpp ownership
QQmlEngine::setObjectOwnership(myObj, QQmlEngine::CppOwnership); // Force cpp ownership
QQmlEngine::setObjectOwnership(myObj, QQmlEngine::JavaScriptOwnership); // Force QML ownership

// REGISTERING OBJECTS WITH QML
// To create QML Component, must be QObject derived
// use 'import MyInclude 1.0' / MyClass {}
qmlRegisterType<N::MyClass>("MyInclude", 1, 0, "MyClass"); // Allows it to be used as MyClass {}
qmlRegisterUncreatableType<N::MyClass>("MyInclude", 1, 0, "MyClass", "Cannot be instantiated in QML");

// REGISTERING ENUMS WITH QML
// Requires Q_ENUM_NS / Q_ENUM registration with Variant
// use 'import MyInclude 1.0' / 'N.MyEnum.ONE'
// any extra namespaces requires args to be in full eg. Q_INVOKABLE void fn(n::N::MyEnum e)
qRegisterMetaType<MyClass::MyEnum>();
qmlRegisterUncreatableMetaObject(N::staticMetaObject, "MyInclude", 1, 0,
    "N", "Error msg if try to create MyEnum object"); // For namespace enums only

// REGISTERING SINGLETONS WITH QML
// Will be owned by QML, use 'import MyInclude 1.0' and 'MySingleton.Member'
qmlRegisterSingletonType(QUrl("qrc:///MyGlobal.qml"), "MyInclude", 1, 0, "MySingleton")
qmlRegisterSingletonType("MyInclude", 1, 0, "MySingleton", 
    [](QQmlEngine*, QJSEngine*)->QObject* { return new MySingleton(); });

// REGISTERING GLOBAL FUNCTIONS WIH QML
// Requires QQmlEngine which inherits QJSEngine
// Call using 'globalFn(10, "str")' without namespaces
class GlobalFnHolder : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool globalFn(int myInt, QString myString);
};
m_globalFnHolder = new GlobalFnHolder(this);
m_globalFnObject = qmlEngine.newQObject(m_globalFnHolder); // QJSValue
qmlEngine.globalObject().setProperty(QLatin1String("globalFn"), 
    m_globalFnObject.property(QLatin1String("globalFn")));

// USING QML OBJECTS/FUNCTIONS IN C++
// See QJSValue for more details, dangerous to store object but can be used as context object
Q_INVOKABLE void myFunction(QObject* object, QJsValue fn) {
    QMetaObject::invokeMethod(object, [fn]() mutable { fn.call(); }, Qt::ConnectionType::QueuedConnection);
    QMetaObject::invokeMethod(object, "myFn", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg));
}

// LOADING QML FILES
qmlEngine->load(QUrl("qrc:/Main.qml"));
/*OR*/
QQuickView view;
view.setResizeMode(QQuickView::SizeRootObjectToView);
QQmlContext* context = view.rootContext();
context->setContextProperty("_model", &model);
view.setSource(QUrl("qrc:/Main.qml"));
view.show();

// LOADING QML FILES WITH QQMLCOMPONENT
context = new QQmlContext(&qmlEngine, &qmlEngine);
context->setContextProperty("_model", &model);
component = new QQmlComponent(&qmlEngine, QUrl("qrc:/Main.qml"));
auto onLoaded = [this]()
{
    auto myObject = std::make_unique<QObject>(component->create(&context));
    if (!myObject || component->isError())
    {
        for (const auto& error : component->errors())
        {
            qDebug() << error.toString();
        }
    }
};
!component->isLoading() ? onLoaded() :
    connectOnce(component, &QQmlComponent::statusChanged, this, onLoaded);

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
// Must derive from it and implement paint(QPainter *painter)
QQuickPaintedItem item
item.fillColor // QColor
item.renderTarget // QQuickPaintedItem::RenderTarget
item.textureSize // QSize
item.setAntialiasing(enable)
item.antialiasing()
item.setMipmap(enable)
item.mipmap() const
item.setOpaquePainting(enable)
item.opaquePainting() const
item.setPerformanceHint(hint, enabled)
item.performanceHints() // Returns QQuickPaintedItem::PerformanceHints
item.setPerformanceHints(hints)
    
// QQmlComponent
// Inherits QObject, instantiated by Component
QQmlComponent component(&qmlEngine, QUrl("qrc:/Main.qml"));
component.progress // [0.0, 1.0] for loading progress, readonly property
component.status // QQmlComponent Status Enum, readonly property
component.url // QUrl, reonly property
component.loadUrl(url, mode) // QQmlComponent Compilation Mode Enum, loads the url
component.isLoading() // status() == QQmlComponent::Loading
component.isError() // status() == QQmlComponent::Error
component.isNull() // status() == QQmlComponent::Null
component.isReady() // status() == QQmlComponent::Ready
component.create(&context) // Takes QQmlContext, returns QObject*, caller takes ownership
component.errors() // Returns QList<QQmlError>, empty if no errors
component.engine() // Returns QML engine used

// QQmlContext
// Use with QQmlComponent or QQmlEngine::rootContext to set properties
QQmlContext context(&qmlEngine, &qmlEngine);
context.setContextProperty("key", value) // Sends to QML, does not update if QML already loaded
context.engine() // Returns QQmlEngine*
context.contextProperty("key") // Returns value as QVariant

// QQmlEngine
// Inherits QJsEngine/QObject
QQmlEngine engine
engine.addImageProvider(providerId, provider)
engine.imageProvider(providerId) // Return QQmlImageProviderBase*
engine.addImportPath(path)
engine.addPluginPath(path)
engine.importPathList() // Return QStringList
engine.pluginPathList() // Return QStringList
engine.setImportPathList(paths)
engine.clearComponentCache() // Reload for QML
engine.trimComponentCache()
engine.retranslate() // Reloads all translated text for qml
engine.rootContext() // Return QQmlContext*, used to set global context properties for qml
engine.warnings(warnings) // Signal with QList<QQmlError> when qml warnings occur
QQmlEngine::contextForObject(obj) // Takes QObject, returns QQmlContext*
QQmlEngine::objectOwnership(obj) // Takes QObject, returns QQmlEngine::ObjectOwnership
QQmlEngine::setObjectOwnership(obj, QQmlEngine::CppOwnership) // Must be used on cpp QObjects without parents
    
// QQmlComponent Status Enum
QQmlComponent::Null     // This QQmlComponent has no data
QQmlComponent::Ready    // This QQmlComponent is ready and create() may be called
QQmlComponent::Loading  // This QQmlComponent is loading network data
QQmlComponent::Error    // An error has occurred. Call errors() to retrieve a list of errors
    
// QQmlComponent Compilation Mode Enum
QQmlComponent::PreferSynchronous // Block the thread, except for remote URLs which always load asynchronously
QQmlComponent::Asynchronous      // Load async

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML ATTACHED PROPERTIES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ATTACHED PROPERTY (STAND-ALONE)
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int prop READ prop WRITE setProp)
public:
    static MyClass* qmlAttachedProperties(QObject* parent) { return new MyClass(parent); }        
};
QML_DECLARE_TYPEINFO(MyClass, QML_HAS_ATTACHED_PROPERTIES) // Requires #include <QtQml>
qmlRegisterType<MyClass>(); // Usage: Item { MyClass.prop: 0 }
 
// ATTACHED PROPERTY
class MyClassAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int prop READ prop WRITE setProp)
};
class MyClass : public QObject
{
public:
    static MyClassAttached* qmlAttachedProperties(QObject* parent)  { return new MyClassAttached(parent); }  
};
QML_DECLARE_TYPEINFO(MyClass, QML_HAS_ATTACHED_PROPERTIES) // Requires #include <QtQml>
qmlRegisterType<MyClassAttached>(); // Usage: MyClass { MyClass.prop: 0 }
qmlRegisterType<MyClass>(“MyImport”, 1, 0, “MyClass”);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT THREADING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
REENTRANCY/THREAD SAFETY
• Class is reentrant if members are threadsafe with different instances of class (eg. no static vars used)
• Class is threadsafe if members are threadsafe with same instance of class (eg. uses mutexes)
• Thread-safe is always reentrant, but reentrant is not always thread-safe
• QObject is reentrant, QWidget/GUI classes are not reentrant and can only be used in GUI thread

QOBJECTS
• Lives on a specific thread (thread affinity) query using obj.thread()
• Must have same thread as parent, obj.setParent will fail if not
• Can change with object.moveToThread(), must not have a parent, all children auto changed too
• Use deleteLater if object is accessed across multiple threads, using delete in wrong thread affinity unsafe
• Can recieve queued signals/events from same/other threads, slot is always called in own thread
• If thread without event loop or thread is destroyed, cannot process queued signals/events including deleteLater
• Creating QObject (including static QObjects) before QApplication is undefined behaviour

SIGNALS / SLOTS
• Threadsafe to connect, disconnect and emit signals, defaults to AutoConnection
• AutoConnection Becomes QueuedConnection when signal is fired from different thread to reciever
• QueuedConnection signals will be sent to slot object's event queue and called synchronously
• QueuedConnection will copy arguments, if slot object doesn't have an event queue, signal is lost

QTHREAD
• Cannot modify gui (QQuick, QWidgets etc.)
• Cannot call OpenGL unless QOpenGLContext::supportsThreadedOpenGL is true
• All QObjects must be destroyed before QThread is destroyed- can connect deleteLater to QThread::finished
• Has a parallel event loop, subclassing QThread gives control over when to start or use the loop
**************************************************************************************************************/

class MyThread : public QThread
{
    Q_OBJECT
    void run() override { emit resultReady(result); }
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

QMutex mutex;
QMutexLocker lock(&mutex);
mutex.lock();
mutex.unlock();

// CHANGING THREAD AFFINITY
// Can only 'push' an object from its current thread to another thread
// Must do this before setting a parent with different affinity
myObj->moveToThread(myObj2->thread());

// ENFORCING THREAD AFFINITY
// Can either use signals/slots or QMetaObject::invokeMethod with an Auto Connection
QMetaObject::invokeMethod(myObj, [myObj]() {
    Q_ASSERT(myObj->thread() == QThread::currentThread());
});
QObject::connect(myObj, &MyClass::signal, [myObj]() {
    Q_ASSERT(myObj->thread() == QThread::currentThread());
});

// WAITING FOR ANOTHER THREAD
// If multiple threads are waiting on condition, order of waking is undefined, wakeOne will be random
QMutex mutex;
QWaitCondition waitCondition;
mutex.lock();
waitCondition.wait(&mutex, timeout); // Waits for a wakeOne or wakeAll call, or till optional timeout
waitCondition.wakeOne() /*or*/ waitCondition.wakeAll(); // Called on other thread
mutex.unlock();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT GLOBAL / ALGORITHMS
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
    
// QtAlgorithm
// STL algorithms should be used for Qt containers rather than deprecated QtAlgorithm
qCountLeadingZeroBits(v) // Takes all quints, returns uint of no. of consecutive zero bits
qCountTrailingZeroBits(v) // Takes all quints, returns uint of no. of consecutive zero bits
qDeleteAll(begin, end) // Takes container iterator with pointers, calls delete on pointers, doesn't clear
qDeleteAll(container) // Takes container with pointers, calls delete on pointers, doesn't clear
qPopulationCount(v) // Takes all quints, returns no. of bits set in v, or the 'Hamming Weight of v'
    
// QtGlobal
qAbs(v) // Templated, returns absolute value of v
qAsConst(v) // Templated, takes T& and returns const T&
qBound(min, v, max) // Templated, returns v clamped
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
    
// QtGlobal Macros
Q_UNREACHABLE()
Q_UNUSED(arg)
    
// QtGlobal Environment Variables
qEnvironmentVariable(name) // Returns QString of env var with name
qEnvironmentVariable(name, default) // Returns QString of env var with name or default if doesn't exist
qEnvironmentVariableIntValue(name, &ok) // Returns int of env var with name, ok set to false if doesn't exist
qEnvironmentVariableIsEmpty(name) // Returns if env var with name is empty
qEnvironmentVariableIsSet(name) // Returns if env var with name is set
qunsetenv(name) // Deletes the env var, returns true if success
qgetenv(name) // Returns env var with name as QByteArray
qputenv(name, value) // Sets env var with value const QByteArray&, will create, returns false if failed
qputenv("QML_DISABLE_DISK_CACHE", "1"); // Disables caching of qml files

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOCALISATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Run lupdate -recursive '.' -ts MyApp_en_US.ts
• All strings in application that use tr or qsTr are picked up by lupdate
• Resources can also be translated
• ts files are then translated by translator
• qm files are loaded by application and can be switched at runtime
• Avoid static strings as they are initialised before translator is set
• Avoid using tr in threads, if used in threads, must not switch translators at same time

TRANSLATION STRINGS:
• Ensure ',' and ' ' are translated as some languages (Japanese) use different characters
• Avoid translation word puzzles
• Use //: to provide translation notes

LUPDATE: Command line tool that looks through source code and creates ts file from strings
LRELEASE: Converts ts files to qm files 
LINGUIST: GUI app that edits ts files and can save qml files
**************************************************************************************************************/

// Can overload QTranslator::translate to provide custom/test translations
// Can have multiple translators installed, searched last to first, first translation found is used
QTranslator translator
translator.load("MyApp_en_US.qm", ":/qrc_path")
application.installTranslator(&translator)
application.removeTranslator(&translator)
application.qmlEngine()->retranslate() // Only for qml, look at QEvent::LanguageChange for C++
   
QLocale("invalid") // Fallback to c locale
QLocale() // System locale unless QLocale::setDefault called
QLocale::system() // System locale
QLocale("C") // C locale
QLocale::c() // C locale
QLocale::setDefault(locale) // Sets what QLocale() will default to
QLocale().groupSeparator() // comma for locales that use it
    
// Numeric form translations (qStr also supported)
tr("%L1 item%2").arg(count).arg(count == 1 ? "" : "s");
tr("%Ln item(s)", "", count);

// Number translations (qStr also supported)
tr(%L1 item).arg(count)
tr(%1 item).arg(count) // without locale
tr(%1 item).arg(QLocale().toString(count, 'f', precision))
qsTr(%1 item).arg(count.toLocaleString(Qt.locale(), 'f', precision))

// Translate with custom context
// context = grouping, disambiguation = for equal sourceText within context
// disambiguation and n optional
QCoreApplication::translate(context, sourceText, disambiguation, n)
Qt.qsTranslate(context, sourceText, disambiguation, n) // qml
