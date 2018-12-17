#include "SampleModel.h"
#include "SampleItem.h"
#include <qqml.h>
#include <qqmlengine.h>
#include <qvariant.h>

SampleModel::~SampleModel() = default;
SampleModel::SampleModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    fillTestItems();
}

void SampleModel::qmlRegisterTypes()
{
    // Register to allow SampleItemState enum in QML
    qmlRegisterType<SampleItem>("SampleModel", 1, 0, "SampleItemState");

    // Register to allow TestObject {} in QML
    qmlRegisterType<Test::Object>("SampleModel", 1, 0, "TestObject");

    // Allow gadget value-type to be used with variant/property system/QML
    qRegisterMetaType<Test::Gadget>();

    // Allow Test::Object::Enum to be used in QML
    qmlRegisterType<Test::Object>("SampleModel", 1, 0, "ObjectEnum");

    // Allow Test::Enum to be used in QML
    qmlRegisterUncreatableMetaObject(Test::staticMetaObject, "SampleModel", 1, 0,
        "Test", "Error msg if try to create MyEnum object");
}

//===========================================================================================================
// Test Methods
//===========================================================================================================

QObject* SampleModel::returnObject()
{
    return new Test::Object();
}

QList<QObject*> SampleModel::returnObjectList()
{
    QList<QObject*> list = { new Test::Object() };
    QQmlEngine::setObjectOwnership(list.back(), QQmlEngine::JavaScriptOwnership);
    return list;
}

void SampleModel::fillTestItems()
{
    for (int i = 0; i < 3; ++i)
    {
        m_intListTest.append(i);
        m_colorListTest.append(QColor(i, i, i));
        m_objectListTest.append(new Test::Object(i));
    }
}

//===========================================================================================================
// Required QAbstractItemModel 
//===========================================================================================================

int SampleModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_items.size());
}

int SampleModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : 1;
}

QModelIndex SampleModel::index(int row, int column, const QModelIndex& parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QModelIndex SampleModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

QVariant SampleModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= 0 && index.row() < static_cast<int>(m_items.size()))
    {
        const auto& item = m_items[index.row()];
        if (role == NameRole)
        {
            return item->getName();
        }
        else if (role == StateDescRole)
        {
            return item->getStateAsString();
        }
        else if (role == StateValueRole)
        {
            return item->getState();
        }
        else if (role == StepRole)
        {
            return item->getStep();
        }
        else if (role == MaxStepRole)
        {
            return item->getMaxSteps();
        }
    }
    return QVariant();
}

//===========================================================================================================
// Optional QAbstractItemModel 
//===========================================================================================================

QHash<int, QByteArray> SampleModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "role_name";
    roles[StateDescRole] = "role_state_desc";
    roles[StateValueRole] = "role_state_value";
    roles[StepRole] = "role_step";
    roles[MaxStepRole] = "role_maxstep";
    return roles;
}

bool SampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < static_cast<int>(m_items.size()))
    {
        const auto& item = m_items[index.row()];
        if (role == NameRole)
        {
            item->setName(value.toString());
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

//===========================================================================================================
// Drag and Drop
//===========================================================================================================

// Default checks if data has at least one format in the list of mimeTypes() 
// and if action is in supportedDropActions(), only re-implement if needing custom checking
bool SampleModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
    return QAbstractItemModel::canDropMimeData(data, action, row, column, parent);
}

// Default returns Qt::CopyAction, Drop Action Flags
Qt::DropActions SampleModel::supportedDropActions() const
{
    return QAbstractItemModel::supportedDropActions();
}

// Default returns supportedDropActions()
Qt::DropActions SampleModel::supportedDragActions() const
{
    return QAbstractItemModel::supportedDragActions();
}

// Serializes the items at indexes to MimeData
// Default uses mime type "application/x-qabstractitemmodeldatalist"
QMimeData* SampleModel::mimeData(const QModelIndexList& indexes) const
{
    return QAbstractItemModel::mimeData(indexes);
}

// Returns the supported Mime types
// Default returns mime type "application/x-qabstractitemmodeldatalist"
QStringList SampleModel::mimeTypes() const
{
    QStringList result = QAbstractItemModel::mimeTypes();
    result.push_back(MimeKey);
    return result;
}

// Default tries to insert the items of data either as siblings or children of an item
// Returns true if the data and action were handled by the model; otherwise returns false
bool SampleModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    return QAbstractItemModel::dropMimeData(data, action, row, column, parent);

    // Using Default Encoding of MimeData
    QByteArray encoded = data->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    while (!stream.atEnd())
    {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;
    }
    // Using Custom Encoding of MimeData
}

//===========================================================================================================
// Custom Methods
//===========================================================================================================

void SampleModel::moveItems(int oldIndex, int newIndex)
{
    if (oldIndex >= 0 && newIndex >= 0 && oldIndex != newIndex)
    {
        beginRemoveRows({}, oldIndex, oldIndex);
        const auto item = m_items.takeAt(oldIndex);
        endRemoveRows();

        beginInsertRows({}, newIndex, newIndex);
        m_items.insert(newIndex, item);
        endInsertRows();
    }
}

int SampleModel::itemToRow(const SampleItem* item) const
{
    const auto itr = std::find_if(m_items.begin(), m_items.end(),
        [item](const auto itemPtr) { return itemPtr == item; });
    return itr != m_items.end() ? std::distance(m_items.begin(), itr) : -1;
}

SampleItem* SampleModel::rowToItem(int row) const
{
    return row >= 0 && row < static_cast<int>(m_items.size())
        ? m_items[row] : nullptr;
}

void SampleModel::tick()
{
    for (auto& item : m_items)
    {
        item->tick();
    }
}

void SampleModel::createItem(const QString& name)
{
    auto onDataChanged = [this](const SampleItem* item)
    {
        const int row = itemToRow(item);
        if (row >= 0 && row < static_cast<int>(m_items.size()))
        {
            const auto& modelIndex = index(row);
            emit dataChanged(modelIndex, modelIndex);
        }
    };

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items.push_back(new SampleItem(name, onDataChanged, this));
    endInsertRows();
}

void SampleModel::deleteItem(int row)
{
    if (row >= 0 && row < static_cast<int>(m_items.size()))
    {
        beginRemoveRows(QModelIndex(), row, row);
        auto item = m_items.takeAt(row);
        item->deleteLater();
        endRemoveRows();
    }
}

void SampleModel::startItemProgress(int row)
{
    if (auto item = rowToItem(row))
    {
        item->start();
        const auto& modelIndex = index(row);
        emit dataChanged(modelIndex, modelIndex);
    }
}

void SampleModel::stopItemProgress(int row)
{
    if (auto item = rowToItem(row))
    {
        item->stop();
        const auto& modelIndex = index(row);
        emit dataChanged(modelIndex, modelIndex);
    }
}

void SampleModel::pauseItemProgress(int row)
{
    if (auto item = rowToItem(row))
    {
        item->pause();
        const auto& modelIndex = index(row);
        emit dataChanged(modelIndex, modelIndex);
    }
}