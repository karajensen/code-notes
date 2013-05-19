#include "event_receiver.h"

bool EventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        if(m_keys.find(static_cast<unsigned int>(event.KeyInput.Key)) != m_keys.end())
        {
            if(event.KeyInput.PressedDown)
            {
                // Turn on KEY_DOWN
                m_keys[event.KeyInput.Key].state |= KEY_DOWN;
            }
            else
            {
                // Turn off KEY_DOWN
                m_keys[event.KeyInput.Key].state &= ~KEY_DOWN;
            }
        }
    }
    else if(event.EventType == irr::EET_LOG_TEXT_EVENT)
    {
        Logger::LogInfo(event.LogEvent.Text);
        return true;
    }
    return false;
}

bool EventReceiver::IsKeyDownContinous(unsigned int& state)
{
    return (state & KEY_DOWN) == KEY_DOWN;
}

bool EventReceiver::IsKeyDown(unsigned int& state)
{
    if(((state & KEY_DOWN) == KEY_DOWN) &&
       ((state & KEY_QUERIED) != KEY_QUERIED))
    {
        // Add user has queried for key to prevent constant queries
        state |= KEY_QUERIED;
        return true;
    }
    else if((state & KEY_DOWN) != KEY_DOWN)
    {
        // Key is lifted, allow user to query again
        state &= ~KEY_QUERIED;
    }
    return false;
}

void EventReceiver::Update()
{
    for(KeyMap::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
    {
        if(it->second.continuous ? IsKeyDownContinous(it->second.state) : IsKeyDown(it->second.state))
        {
            it->second.onKeyFn();
        }
    }
}

void EventReceiver::SetKeyCallback(unsigned int key, bool onContinous, KeyFn keyFn)
{
    m_keys[key] = Key();
    m_keys[key].state = 0x00;
    m_keys[key].continuous = onContinous;
    m_keys[key].onKeyFn = keyFn;
}
