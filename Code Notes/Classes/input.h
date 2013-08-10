////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#define DIRECTINPUT_VERSION 0x0800 //for direct input
#include "common.h"
#include "picking.h"
#include <dinput.h>
#include <unordered_map>

class Mesh;

/*
* Direct Input and mouse picking wrapper
* Note: Some keys do not work with continuous 
* keypress/mouse click combination (ie. Space/Tab)
*/
class Input
{
public:

    typedef std::function<void(void)> KeyFn;

    /**
    * Constructor
    * @param hInstance Handle to the instance of the application
    * @param hWnd Handle to the window of the application
    */
    Input(HINSTANCE hInstance, HWND hWnd);

    /**
    * Destroy directinput
    */
    ~Input();

    /**
    * Updates the input from directX
    */
    void UpdateInput();

    /**
    * @return whether the mouse has been clicked for this tick.
    */
    bool IsMouseClicked() const;

    /**
    * @return whether the mouse is being held down
    */
    bool IsMousePressed();

    /**
    * Adds key to a list that prevents mouse clicking when held
    * @param key The DirectInput keyboard scan code
    */
    void AddClickPreventionKey(unsigned int key);

    /**
    * Set the function to call upon toggle of the input key
    * @param key The DirectInput keyboard scan code
    * @param onContinous Whether to call on key press or key press continously
    * @param onKeyFn The function to call
    * @param offKeyFn An optional function to call if key is no longer pressed
    */
    void SetKeyCallback(unsigned int key, bool onContinous, KeyFn onKeyFn, KeyFn offKeyFn = nullptr);

    /**
    * @return mouse picking information
    */
    Picking& GetMousePicking() { return m_picking; }

    /**
    * Send a ray into the scene to determine if mouse clicked an object
    * @param projection The camera projection matrix
    * @param view The camera view matrix
    */
    void UpdatePicking(Transform& projection, Transform& view);

    /**
    * If a mesh was picked, call the associated picking function
    */
    void SolvePicking();

    /**
    * @return the mouse click X position
    */
    int GetMouseX() const { return m_x; }

    /**
    * @return the mouse click Y position
    */
    int GetMouseY() const { return m_y; }

    /**
    * @return the direction the mouse has moved since last tick
    */
    const D3DXVECTOR2& GetMouseDirection() const { return m_mouseDirection; }
    
private:

    /**
    * @param x/y the mouse coordinates to set
    */
    void SetMouseCoord(int x, int y);

    /**
    * Determines if a key is being pressed and held
    * @param state The state of the key
    * @return Whether a key is currently being pressed or not
    */
    bool IsKeyDownContinous(unsigned int& state);

    /**
    * Whether a key was pressed but not held
    * Once queried will return false until key is released
    * @param state The state of the key
    * @return Whether a key is currently being pressed or not
    */
    bool IsKeyDown(unsigned int& state);

    /**
    * Recieves states of keys from directInput
    * @param keyState The state of the keyboard
    */
    void GetKeys(BYTE* keyState);

    /**
    * Recieves state of mouse from directInput
    * @param mouseState The state of the mouse
    */
    void GetMouse(DIMOUSESTATE* mouseState);

    /**
    * Updates the cached key array from the direct input state
    * @param pressed Whether the key is currently being pressed
    * @param state The state of the key
    */
    void UpdateKey(BYTE pressed, unsigned int& state);

    /**
    * Prevent copying
    */
    Input(const Input&);
    Input& operator=(const Input&);

    /**
    * Masks for state of input key
    */
    enum InputMask
    {
        KEY_DOWN = 1,    ///< Whether the key is currently being pressed
        KEY_QUERIED = 2  ///< Whether the key has been queried since pressed
    };

    /**
    * Key object structure
    */
    struct Key
    {
        unsigned int state;     ///< Current state of the key
        KeyFn onKeyFn;          ///< Function to call if key is down
        KeyFn offKeyFn;         ///< Function to call if key is up
        bool continuous;        ///< Whether key should look at continous or not
    };

    typedef std::unordered_map<unsigned int, Key> KeyMap;
    typedef std::vector<unsigned int> KeyList;

    HWND m_hWnd;                           ///< Cached handle to the window
    KeyMap m_keys;                         ///< Cached keys
    KeyList m_clickPreventionKeys;         ///< Keys that will prevent clicking of the mouse
    bool m_mouseClicked;                   ///< Whether mouse was clicked this tick
    unsigned int m_mouse;                  ///< Cached mouse state
    int m_x, m_y;                          ///< Mouse clicked screen coordinates
    Picking m_picking;                     ///< Mouse picking
    D3DXVECTOR2 m_mouseDirection;          ///< Direction mouse has moved (normalized) between ticks
    LPDIRECTINPUT8 m_directInput;          ///< DirectX input
    LPDIRECTINPUTDEVICE8 m_keyboardInput;  ///< DirectX keyboard device
    LPDIRECTINPUTDEVICE8 m_mouseInput;     ///< DirectX mouse device
};