#pragma once
#include <qstring.h>
#include <qobject.h>
#include <qmetaobject.h>
#include <memory>
#include <functional>

class SampleItem : public QObject
{
    Q_OBJECT

public:
    typedef std::function<void(const SampleItem* item)> onDataChangedFn;
    SampleItem(const QString& name, onDataChangedFn changedFn, QObject* parent = nullptr);
    SampleItem(QObject* parent = nullptr);
    ~SampleItem();

    enum State
    {
        NONE = 0,
        STEPPING,
        PAUSED,
        COMPLETE,
        STOPPED
    };
    Q_ENUM(State)

    void tick();
    void start();
    void stop();
    void pause();

    void setName(const QString& name);
    const QString& getName() const;
    QString getStateAsString() const;
    State getState() const;
    int getStep() const;
    int getMaxSteps() const;

private:
    void setState(State state);

    QMetaEnum m_stateEnum;
    QString m_name;
    State m_state;
    int m_step = 0;
    onDataChangedFn m_changedFn = nullptr;
};