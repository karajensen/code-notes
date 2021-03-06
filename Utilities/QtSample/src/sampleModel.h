#pragma once

#include "testClasses.h"
#include <qabstractitemmodel.h>
#include <memory>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qmimedata.h>
#include <qcolor.h>
#include <qvector.h>

class SampleItem;

class SampleModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(QList<int> intListTest MEMBER m_intListTest)
    Q_PROPERTY(QVariantList colorListTest MEMBER m_colorListTest)
    Q_PROPERTY(QList<QObject*> objectListTest MEMBER m_objectListTest)
    Q_PROPERTY(Test::Gadget gadgetTest MEMBER m_gadgetTest)

public:
    SampleModel(QObject* parent = nullptr);
    virtual ~SampleModel();
    static void qmlRegisterTypes();

    enum ModelRoles
    {
        NameRole = Qt::UserRole + 1,
        StateDescRole,
        StateValueRole,
        StepRole,
        MaxStepRole,
    };

    /** 
    * Required QAbstractItemModel 
    */
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;

    /**
    * Optional QAbstractItemModel
    */
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

    /**
    * Drag and Drop
    */
    static constexpr const char* MimeKey = "application/sample-model-item";
    virtual QStringList mimeTypes() const override;
    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;
    virtual bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const override;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const override;
    virtual Qt::DropActions supportedDropActions() const override;
    virtual Qt::DropActions supportedDragActions() const override;

    /**
    * Custom Methods
    */
    Q_INVOKABLE void createItem(const QString& name);
    Q_INVOKABLE void deleteItem(int row);
    Q_INVOKABLE void startItemProgress(int row);
    Q_INVOKABLE void stopItemProgress(int row);
    Q_INVOKABLE void pauseItemProgress(int row);
    Q_INVOKABLE void moveItems(int oldIndex, int newIndex);
    SampleItem* rowToItem(int row) const;
    int itemToRow(const SampleItem* item) const;
    void tick();

    /**
    * Test Methods
    */
    void fillTestItems();
    Q_INVOKABLE QObject* returnObject();
    Q_INVOKABLE QList<QObject*> returnObjectList();

private:
    QVector<SampleItem*> m_items;
    Test::Gadget m_gadgetTest;
    QList<int> m_intListTest;
    QVariantList m_colorListTest;
    QList<QObject*> m_objectListTest;
};