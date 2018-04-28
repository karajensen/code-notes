#pragma once
#include <qabstractitemmodel.h>
#include <memory>

#include <qbytearray.h>
#include <qdatastream.h>
#include <qmimedata.h>

class SampleItem;

class SampleModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SampleModel(QObject* parent = nullptr);
    virtual ~SampleModel();

    enum ModelRoles
    {
        NameRole = Qt::UserRole + 1,
        StateDescRole,
        StateValueRole,
        StepRole,
        MaxStepRole,
    };

    /**
    * Register this type with QML
    */
    static void qmlRegisterTypes();

    /** 
    * Ticks the model to allow step values
    */
    void tick();

    /**
    * QML invokable functions to be used on sample items
    */
    Q_INVOKABLE void createItem(const QString& name);
    Q_INVOKABLE void deleteItem(int row);
    Q_INVOKABLE void startItemProgress(int row);
    Q_INVOKABLE void stopItemProgress(int row);
    Q_INVOKABLE void pauseItemProgress(int row);

    /** 
    * @see QAbstractItemModel 
    */
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;

    /**
    * Drag and drop
    */
    static constexpr const char* MimeKey = "application/sample-model-item";
    virtual QStringList mimeTypes() const override;
    //virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;
    //virtual bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const override;
    //virtual QMimeData* mimeData(const QModelIndexList& indexes) const override;

private:
    SampleItem* rowToItem(int row) const;
    int itemToRow(const SampleItem* item) const;

    std::vector<std::unique_ptr<SampleItem>> m_items;
};
