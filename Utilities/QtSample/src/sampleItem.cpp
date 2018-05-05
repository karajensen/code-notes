#include "SampleItem.h"
#include <assert.h>

const int MAX_STEPS = 100;

SampleItem::~SampleItem() = default;
SampleItem::SampleItem(const QString& name, onDataChangedFn changedFn, QObject* parent)
    : SampleItem(parent)
{
    m_name = name;
    m_changedFn = changedFn;
}

SampleItem::SampleItem(QObject* parent)
    : QObject(parent)
    , m_step(0)
    , m_state(NONE)
    , m_stateEnum(QMetaEnum::fromType<State>())
{
}

void SampleItem::tick()
{
    if (m_state == STEPPING)
    {
        ++m_step;
        if (m_step >= MAX_STEPS)
        {
            m_step = MAX_STEPS;
            m_state = COMPLETE;
        }

        if (m_changedFn)
        {
            m_changedFn(this);
        }
    }
}

const QString& SampleItem::getName() const
{
    return m_name;
}

QString SampleItem::getStateAsString() const
{
    return m_stateEnum.valueToKey(m_state);
}

SampleItem::State SampleItem::getState() const
{
    return m_state;
}

int SampleItem::getStep() const
{
    return m_step;
}

int SampleItem::getMaxSteps() const
{
    return MAX_STEPS;
}

void SampleItem::start()
{
    setState(STEPPING);
}

void SampleItem::stop()
{
    setState(STOPPED);
}

void SampleItem::pause()
{
    setState(PAUSED);
}

void SampleItem::setState(State state)
{
    if (state != m_state)
    {
        m_state = state;

        if (m_changedFn)
        {
            m_changedFn(this);
        }
    }
}

void SampleItem::setName(const QString& name)
{
    m_name = name;
}