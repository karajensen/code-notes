/****************************************************************
* Kara Jensen (mail@karajensen.com) 
* Derived class for overriding events in Irrlicht
*****************************************************************/
#pragma once

#include <irrlicht.h>
#include <functional>
#include <unordered_map>
#include "logger.h"
using namespace irr;

class EventReceiver : public IEventReceiver
{
public:

    typedef std::function<void(void)> KeyFn;

    /**
    * Irrlicht override
    * @return true if handled, false if irrlicht needs to also handle it
    */
    virtual bool OnEvent(const SEvent& event);

    /**
    * Set the function to call upon toggle of the input key
    * @param the DirectInput keyboard scan code
    * @param the function to call
    * @param whether to call on key press or key press continously
    */
    void SetKeyCallback(unsigned int key, bool onContinous, KeyFn keyFn);

    /**
    * Checks what keys are pressed and calls the relevent callbacks
    */
    void Update();

private:

    /**
    * Masks used for the key array
    */
    enum
    {
        KEY_DOWN = 1,
        KEY_QUERIED = 2
    };

    /**
    * Key object structure
    */
    struct Key
    {
        unsigned int state;     ///< Current state of the key
        KeyFn onKeyFn;          ///< Function to call if key is down
        bool continuous;        ///< Whether key should look at continous or not
    };

    /**
    * Whether a key is currently being pressed or not
    * @param the state of the key
    * @param whether the key is being pressed
    */
    bool IsKeyDownContinous(unsigned int& state);

    /**
    * Whether a key was pressed. Once queried will return false until key is released
    * @param the state of the key
    * @param whether the key was pressed
    */
    bool IsKeyDown(unsigned int& state);

    typedef std::unordered_map<unsigned int, Key> KeyMap;
    KeyMap m_keys; ///< Cached keys
};