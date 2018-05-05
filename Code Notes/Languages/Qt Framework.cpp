/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FRAMEWORK
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
**************************************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTimer timer;
    timer.setInterval(10);
    QObject::connect(&timer, &QTimer::timeout, []() { /*tick*/ });
    timer.start();
    app.exec(); // Start the event loop
}

forever { break; }
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
• Meta Object Compilier (moc) uses Q_OBJECT macro to generate extra data
• Ability to use qobject_cast, signals, slots, property system

QOBJECT LIMITATIONS:
• Only signals and slots can live in the signals and slots sections
• Multiple Inheritance requires QObject to be first
• Moc doesn't support virtual inheritance
• Moc doesn't support templates with Q_OBJECT/signals/slots
• Moc doesn't expand #define: cannot use a macro to declare a signal/slot or used as a signal/slot parameter
• Function Pointers cannot be direct signal/slot Parameters, work-around is to typedef it
• Enums/typedefs cannot be forward decl for signal/slot parameters
• Nested Classes cannot have signals or slots

PARENT-CHILD RELATIONSHIP:
• Parent needs to be explicitly deleted, either by delete or stack scope
• Children deleted by parent automatically, if child is deleted first, parent is notified
• Children should not be created on the stack unless deleted first, as parent assumes children are on heap

IMPLICIT SHARING (COPY-ON-WRITE):
• Objects share the same memory in a 'shared block' if have the same values
• Automatically detaches the object from a shared block when object changes and ref count is > 1
• Qt classes use it internally, doesn't require a shared data pointer for it to happen
• Can be dangerous for iterators when container detaches from shared block:

SIGNALS/SLOTS:
• On signal emit, all slots in order of connection are immediately notified, can't be async
• Type safe: The signature of a signal must match the signature of the receiving slot
• No return values, slots can be virtual/pure virtual

PROPERTY SYSTEM:
MEMBER     Required if READ not used
READ       Required if MEMBER not used
WRITE      Optional, can be used with either READ or MEMBER
NOTIFY     Optional, takes signal with one or no arguments
STORED     Default true, indicates whether property value must be saved when storing the object's state
CONSTANT   Optional, makes readonly
FINAL      Optional, can enable optimizations, indicates shouldn't override though not enforced by moc
**************************************************************************************************************/

class MyClass : public QObject
{
    Q_OBJECT // required for all moc provided features
    Q_CLASSINFO("Author", "Name") // attach additional name/value pairs to the class's meta-object

public:
    MyClass(QObject *parent = 0) { }
    
    Q_INVOKABLE void myFn() { }
    Q_PROPERTY(MyValue value MEMBER m_value NOTIFY myValueSignal)
    Q_PROPERTY(MyValue value READ getValue WRITE setValue NOTIFY mySignal)
    
    // Can be inherited/virtual
    const MyValue& getValue() const { return m_value; }
    void setValue(const MyValue& value) { m_value = value; }
    
    // Enums must start with capital letter
    enum MyEnum { ONE, TWO, THREE };
    enum MyFlag { One=0x01, Two=0x02, Three=0x04 };
    
signals:
    void mySignal();
    void myValueSignal(const MyValue& value);

public slots: // can be protected/private
    void mySlot();
    void mySlot(void (*fn)(void *)); // Cannot do
    void mySlot(MyFn fn);            // Can do
};

obj.objectName // Property; User-defined name of object instance, blank as default
obj.setProperty("value", v); // Return true if existed and set, auto creates if doesn't exist only for obj
obj.property("value") // Returns QVariant, invalid if doesn't exist
obj.metaObject() // Returns const QMetaObject*
obj.blockSignals(true) // Prevents any signals from calling slots, doesnt block destroyed() signal
obj.signalsBlocked() // Whether signals blocked
obj.children() // Returns const QList<QObject*>& for children, order changes when child raised/lowered
obj.dumpObjectInfo() // Outputs to debug log
obj.dumpObjectTree() // Outputs to debug log
obj.dynamicPropertyNames() // Returns QList<QByteArray> for all dynamic properties
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
qobject_cast<MyClass*>(obj); // dynamic_cast without requiring RTTI
emit obj.mySignal() // Emit a signal, need to call emit whenever Q_PROPERTY changes to update QML
MyClass::staticMetaObject // QMetaObject for class
    
// QMetaObject
metaObj.propertyCount() // Number of properties, not including dynamic properties
metaObj.className() // Returns class name as const char*
metaObj.methodCount() // Number of methods including inherited, signals, slots
metaObj.enumeratorCount() // Number of enums including inherited
metaObj.enumerator(index) // Get QMetaEnum from index
metaObj.indexOfEnumerator(name) // Get index of enum from name, or -1 if not found

// QMetaEnum
QMetaEnum metaEnum(QMetaEnum::fromType<MyClass::MyEnum>());
metaEnum.valueToKey(MyClass::ONE)
metaEnum.keyToValue("ONE")

// OBJECT TYPE INFO
// Macro must be outside all namespaces
// Q_PRIMITIVE_TYPE leaves obj memory unitialised, means trivally copyable
// Q_MOVABLE_TYPE uses std::memcpy rather than copy ctor to move obs around, means trivally relocatable
// Q_MOVABLE_TYPE does shallow move; don't use for types that self refer (pimpl with ptr back to parent)
Q_DECLARE_TYPEINFO(MyClass, Q_COMPLEX_TYPE) // Default
Q_DECLARE_TYPEINFO(MyClass::MyEnum, Q_PRIMITIVE_TYPE)
Q_DECLARE_TYPEINFO(MyClass, Q_MOVABLE_TYPE)
QTypeInfoQuery<MyClass>::isRelocatable // Query type info

// REGISTERING OBJECT WITH VARIANT
// Macro must be outside all namespaces
// Allows use with variant: myVariant.value<MyClass>()
// Not needed for: MyClass*, qt smart pointers/container with MyClass, if using Q_ENUM/Q_FLAG/Q_GADGET
Q_DECLARE_METATYPE(MyClass)

// REGISTERING OBJECT WITH PROPERTY SYSTEM
// Allows use with signals/slots/property system
qRegisterMetaType<MyClass>();

// REGISTERING OBJECT FOR STREAMING
// Allows use with drag/drop systems
qRegisterMetaTypeStreamOperatorss<MyClass>("MyClass");
QDataStream& operator<<(QDataStream& out, const MyClass& obj);
QDataStream& operator>>(QDataStream& in, MyClass& obj);

// REGISTERING ENUMS
// Macro must be outside all namespaces
// QML use 'import MyEnums 1.0' and 'MyEnum.ONE'
Q_ENUM(MyClass::MyEnum)
qmlRegisterType<MyClass>("MyEnums", 1, 0, "MyEnum");

// CONNECT SIGNALS/SLOTS
// Returns QMetaObject::Connection for disconnecting, or can call QObject::disconnect with same signature
// Can duplicate connections, multiple signals are then emitted, all are broken with single disconnect call 
// Signatures must match: SIGNAL/SLOT macros give runtime error, functions give compile error
// Use normalised form from moc cpp for SIGNAL/SLOT macros, otherwise performance hit
QObject::connect(sender, &Sender::mySignal, reciever, &Receiver::mySlot);
QObject::connect(sender, &Sender::mySignal, reciever, [](){});
QObject::connect(sender, SIGNAL(mySignal()), reciever, SLOT(mySlot()));
QObject::connect(sender, SIGNAL(mySignalArgs(int,float)), reciever, SLOT(mySlotArgs(int,float)));

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
// QT COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QWindow
// Window for non-widgets based applications (QML)
// If has a parent, becomes a native child window of their parent window
// Uses QBackingStore for rendering with QPainter using QSurface::RasterSurface
// Or can use QOpenGLContext for rendering with OpenGL using QSurface::OpenGLSurface

// QPair<T1, T2>
auto pair = qMakePair(v1, v2);
pair.first;
pair.second;

// QSettings
// Provides persistent platform-independent application settings

// QTimer
// Provides repetitive and single-shot timers

// QUrl
// Interface for working with URLs

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELS / VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
• MimeData: MIME-encoded data for the Model's items, used for drag-drop
**************************************************************************************************************/

class MyModel : public QAbstractItemModel // QAbstractListModel
{
    Q_OBJECT
public:
    virtual ~MyModel() = default;
    MyModel(QObject* parent = nullptr)
        : QAbstractListModel(parent)
    {
        // Batch create all new items here
    }

    enum ModelRoles
    {
        MyRole1 = Qt::UserRole + 1,
        MyRole2
    };
    
    /* @return the supported roles for this model */
    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[MyRole1] = "role_one";
        roles[MyRole2] = "role_two";
        return roles;    
    }
    
    /* Sets data for an item at index using the given role */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
    {
        if (index.row() >= 0 && index.row() < static_cast<int>(m_items.size()))
        {
            const auto& item = m_items[index.row()];
            if (role == Role1)
            {
                item->setRole1(value);
                emit dataChanged(index, index);
                return true;
            }
            else if (role == Role2)
            {
                item->setRole2(value);
                emit dataChanged(index, index);
                return true;
            }
        }
        return false;
    }
   
    /* @return data for an item at index using the given role */
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

    /* @return the amount of rows in the model */
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent);
        return static_cast<int>(m_items.size());    
    }
    
    /* Not needed if using QAbstractListModel, Return the amount of columns in the model*/
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : 1;
    }
    
    /* Not needed for QAbstractListModel, Default column = 0 if not using it */
    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override
    {
        return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
    }

    /* Not needed for QAbstractListModel */
    virtual QModelIndex parent(const QModelIndex& child = QModelIndex()) const override
    {
        return QModelIndex();
    }    
    
    /* @return row index converted to an item */
    MyItem* rowToItem(int row) const
    {
        return row >= 0 && row < static_cast<int>(m_items.size())
            ? m_items[row].get() : nullptr;
    }
    
    /* @return item converted to row index */
    int itemToRow(const WorkerItem* item) const
    {
        const auto itr = std::find_if(m_items.begin(), m_items.end(), 
            [item](const auto& itemPtr) { return itemPtr.get() == item; });
        return itr != m_items.end() ? std::distance(m_items.begin(), itr) : -1;
    }
    
    /* A function invokable from QML that modifies data from the model */
    Q_INVOKABLE void qmlFunction(int row)
    {
        if (auto item = rowToItem(row))
        {
            item->doSomethingToChangeData();
            const auto& modelIndex = index(row);
            emit dataChanged(modelIndex, modelIndex);
        }
    }
    
    /* A function that creates a new item */
    void createItem()
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items.push_back(std::make_unique<MyItem>());
        endInsertRows();
    }

    /* A function that deletes an item */
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

//===========================================================================================================
// QT MODELS
//===========================================================================================================

// QModelIndex
// Created/obtained from QAbstractItemModel::createIndex / QAbstractItemModel::index
// Should be used immediately and then discarded
QModelIndex index; // Create an invalid index
index.column() // Column of the index
index.data(role) // Default role Qt::DisplayRole, returns QVariant of item at index
index.flags() // Returns Qt::ItemFlags for the item at index
index.internalId() // Returns quintptr used by model to associate the index with the internal data
index.internalPointer() // Returns void* used by model to associate the index with the internal data
index.isValid() // Valid index belongs to a model, and has non-negative row and column numbers
index.model() // Returns const QAbstractItemModel*, do not const_cast
index.parent() // Returns QModelIndex
index.row() // Row of the index
index.sibling(row, column) // Returns QModelIndex

// QPersistentModelIndex
// Can be safely stored, model will auto update all saved if index invalidation change occurs
QPersistentModelIndex pindex(index); 
pindex.column() // Column of the index
pindex.data(role) // Default role Qt::DisplayRole, returns QVariant of item at index
pindex.flags() // Returns Qt::ItemFlags for the item at index
pindex.isValid() // Valid index belongs to a model, and has non-negative row and column numbers
pindex.model() // Returns const QAbstractItemModel*, do not const_cast
pindex.parent() // Returns QModelIndex
pindex.row() // Row of the index
pindex.sibling(row, column) // Returns QModelIndex

// QAbstractItemModel
// Inherits QObject, Abstract interface for item model classes
// Parent/index is always const QModelIndex&
// Drag-drop methods in Model Drag / Drop section
model.beginInsertColumns(parent, first, last) // Insert new columns between first to last
model.beginInsertRows(parent, first, last) // Insert new rows between first to last
model.beginMoveColumns(srcParent, srcFirst, srcLast, dstParent, dstChild) // Move srcFirst-srcLast to dstChild
model.beginMoveRows(srcParent, srcFirst, srcLast, dstParent, dstChild) // Move srcFirst-srcLast to dstChild
model.beginRemoveColumns(parent, first, last) // Remove columns between first to last
model.beginRemoveRows(parent, first, last) // Remove rows between first to last
model.beginResetModel()
model.buddy(index) // Returns QModelIndex for item to edit instead of selected one. Auto called?
model.canFetchMore(parent)
model.changePersistentIndex(from, to)
model.changePersistentIndexList(from, to)
model.createIndex(row, column, ptr) // Returns QModelIndex, ptr optional
model.createIndex(row, column, id) // Returns QModelIndex
model.columnCount(parent) // parent optional
model.data(index, role) // Default role Qt::DisplayRole, returns QVariant
model.endInsertColumns()
model.endInsertRows()
model.endMoveColumns()
model.endMoveRows()
model.endRemoveColumns()
model.endRemoveRows()
model.endResetModel()
model.fetchMore(parent)
model.flags(index) // Returns Qt::ItemFlags
model.hasChildren(parent) // parent optional
model.hasIndex(row, column, parent) // parent optional
model.headerData(section, orientation, role) // Default role Qt::DisplayRole
model.index(row, column, parent) // parent optional, returns QModelIndex
model.insertColumn(column, parent) // parent optional, calls insertColumns
model.insertColumns(column, count, parent) // parent optional
model.insertRow(row, parent) // parent optional, calls insertRows
model.insertRows(row, count, parent) // parent optional
model.itemData(index) // Returns QMap<int, QVariant>
model.match(start, role, value, hits, matchflags) // Returns QModelIndexList, hits/matchFlags optional
model.moveColumn(srcParent, srcColumn, dstParent, dstChild) // calls moveColumns
model.moveColumns(srcParent, srcColumn, count, dstParent, dstChild)
model.moveRow(srcParent, srcRow, dstParent, dstChild) // calls moveRows
model.moveRows(srceParent, srcRow, count, dstParent, dstChild)
model.parent(index) // Returns QModelIndex
model.persistentIndexList() // Returns QModelIndexList
model.removeColumn(column, parent) // parent optional, calls removeColumns
model.removeColumns(column, count, parent) // parent optional
model.removeRow(row, parent) // parent optional, calls removeRows
model.removeRows(row, count, parent) // parent optional
model.roleNames() const // Returns QHash<int, QByteArray>
model.rowCount(parent) // parent optional
model.setData(index, value, role) // Default role Qt::EditRole
model.setHeaderData(section, orientation, value, role) // Default role Qt::EditRole
model.setItemData(index, roles)
model.sibling(row, column, index) // Returns QModelIndex
model.sort(column, order) // Order default Qt::AscendingOrder
model.span(index) // Returns QSize
emit dataChanged(topLeft, botRight, roles) // Roles optional, Emitted by setData
emit headerDataChanged(orientation, first, last) // Emitted by setHeaderData
emit columnsAboutToBeInserted(parent, first, last) // Emitted by beginInsertColumns
emit columnsInserted(parent, first, last) // Emitted by endInsertColumns
emit columnsAboutToBeMoved(srcParent, srcFirst, srcLast, dstParent, dstChild) // Emitted by beginMoveColumns
emit columnsMoved(srcParent, srcFirst, srcLast, dstParent, dstChild) // Emitted by endMoveColumns
emit columnsAboutToBeRemoved(parent, first, last) // Emitted by beginRemoveColumns
emit columnsRemoved(parent, first, last) // Emitted by endRemoveColumns
emit rowsAboutToBeInserted(parent, first, last) // Emitted by beginInsertRows
emit rowsInserted(parent, first, last) // Emitted by endInsertRows
emit rowsAboutToBeMoved(srcParent, srcFirst, srcLast, dstParent, dstChild) // Emitted by beginMoveRows
emit rowsMoved(srcParent, srcFirst, srcLast, dstParent, dstChild) // Emitted by endMoveRows
emit rowsAboutToBeRemoved(parent, first, last) // Emitted by beginRemoveRows
emit rowsRemoved(parent, first, last) // Emitted by endRemoveRows
emit layoutAboutToBeChanged(parents, hint) // Both optional
emit layoutChanged(parents, hint) // Both optional
emit modelAboutToBeReset() // Emitted by beginResetModel
emit modelReset() // Emitted by endResetModel
    
// QAbstractItemModel Default Roles
Qt::DisplayRole         // display
Qt::DecorationRole      // decoration
Qt::EditRole            // edit
Qt::ToolTipRole         // toolTip
Qt::StatusTipRole       // statusTip
Qt::WhatsThisRole       // whatsThis

// QAbstractTableModel
// Inherits QAbstractItemModel, Can be subclassed to create table models
// Re-implements: dropMimeData, flags, index, sibling
QAbstractTableModel model;
    
// QAbstractListModel
// Inherits QAbstractItemModel, Can be subclassed to create one-dimensional list models
// Re-implements: dropMimeData, flags, index, sibling
QAbstractListModel model;
    
// QStringListModel
// Inherits QAbstractListModel, Model that supplies strings to views

// QItemSelectionModel
// Instantiated By ItemSelectionModel, Inherits QObject, keeps track of a view's selected items

//===========================================================================================================
// QT PROXY MODELS
//===========================================================================================================

// QAbstractProxyModel
// Inherits QAbstractItemModel, Base class for proxy item models that can do sorting, filtering etc

// QIdentityProxyModel
// Inherits QAbstractProxyModel, Proxies its source model unmodified

// QSortFilterProxyModel
// Inherits QAbstractProxyModel, support for sorting/filtering data passed between another model and a view

//===========================================================================================================
// MODEL DRAG / DROP
//===========================================================================================================

// All are optional, re-implementing some require others to also be implemented
class MyModel : public QAbstractItemModel
{
    static constexpr const char* MimeKey = "application/my-model-item";

    // Default checks if data has at least one format in the list of mimeTypes() 
    // and if action is in supportedDropActions(), only re-implement if needing custom checking
    virtual bool canDropMimeData(const QMimeData* data, Qt::DropAction action, 
                                int row, int column, const QModelIndex& parent) const override
    {
    }
    
    // Default returns Qt::CopyAction, Returns the supported Drop Action Flags
    virtual Qt::DropActions supportedDropActions() const override
    {
    }
    
    // Serializes the items at indexes to MimeData
    // Default uses mime type "application/x-qabstractitemmodeldatalist"
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const override
    {
    }
    
    // Returns the supported Mime types
    // Default returns mime type "application/x-qabstractitemmodeldatalist"
    virtual QStringList mimeTypes() const override
    {
        QStringList result = QAbstractItemModel::mimeTypes();
        result.push_back(MimeKey); // Add custom key to supported types
        return result;    
    }    
     
    // Default tries to insert the items of data either as siblings or children of an item
    // Returns true if the data and action were handled by the model; otherwise returns false
    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, 
                              int row, int column, const QModelIndex& parent) override
    {
        // Using Default Encoding of MimeData
        QByteArray encoded = qMimeData->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encoded, QIODevice::ReadOnly);
        while (!stream.atEnd())
        {
            int row, col;
            QMap<int,  QVariant> roleDataMap;
            stream >> row >> col >> roleDataMap;
        }
        // Using Custom Encoding of MimeData
    }
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QWidget
// If no parent, window for widgets based applications (non-QML), else base class for widgets
// Uses QBackingStore for rendering with QPainter using QSurface::RasterSurface
QWidget widget;
widget.setWindowTitle("Title");
widget.show();
widget.setLayout(layout); // Add a layout to the window, automatically parents

// QOpenGLWidget
// Inherits QWidget but uses QOpenGLContext for rendering with OpenGL using QSurface::OpenGLSurface

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QHBoxLayout
// Lays out widgets horizontally from left to right
QHBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout
// Lays out widgets vertically from top to bottom
QVBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QGridLayout
// Lays out widgets in a grid.
QGridLayout layout;
layout.addWidget(spinBox, r, c); // Add a widget to the layout, automatically parents and resizes

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT QUICK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QQuickWindow
// Inherits QWindow, window for QML applications

// QQuickView 
// Wrapper for QQuickWindow to automatically load and display a QML scene from an url
QQuickView view;
view.rootContext()->setContextProperty("context_model", model); // Attach an QAbstractItemModel* to QML
view.setSource(QUrl("qrc:/main.qml"));
view.show();

// QQuickWidget
// Wrapper for QQuickWindow to automatically load and display a QML scene from an url
// Less stacking order restrictions, though slower compared to QQuickWindow/QQuickView
// Disables the threaded render loop on all platforms
// Avoid calling winId; triggers creation of a native window, resulting in reduced performance

// QQuickItem
// Inherits QObject, instantiated by Item
// Properties have accessors item.property() and item.setProperty()
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

// QQmlEngine
qmlRegisterSingletonType(QUrl("qrc:///MyGlobal.qml"), "MyGlobals", 1, 0, "MyGlobal")
qmlRegisterType<MyClass>("MyEnums", 1, 0, "MyEnum") // MyEnum must be in Q_OBJECT class

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

// QDir
// Provides access to directory structures and their contents
QDir dir("Folder/Folder") // Root directory
dir.exists() // Whether root directly exists
dir.setNameFilters(QStringList("*.qml", "*.txt")) // Extension types to filter searches with
dir.entryList(nameFilters, filterFlags, sortFlags) // Search directory recursively, returns QStringList
dir.entryList(nameFilters) // Not using any args will use the stored filterFlags/sortFlags
dir.entryList(filterFlags, sortFlags) // Search directory recursively with filter flags, returns QStringList
dir.entryList() // Not using any args will use the stored filterFlags/sortFlags

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
    
// QIODevice
// base interface class of all I/O devices

// QDataStream
// serialization of binary data to a QIODevice

// QFile
// Interface for reading from and writing to files
