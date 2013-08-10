////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com
////////////////////////////////////////////////////////////////////////////////////////

#include "input.h"
#include <algorithm>

namespace 
{
    const int MOUSE_LEFT = 0;           ///< Index into directX mouse input array
    const int BLANK_KEY = 0x00;         ///< Key state initialiser
    const int KEY_BUFFER_SIZE = 256;    ///< Max buffer size allowable for keys
}

Input::Input(HINSTANCE hInstance, HWND hWnd) :
    m_hWnd(hWnd),
    m_mouseClicked(false),
    m_mouse(0),
    m_x(-1),
    m_y(-1),
    m_mouseDirection(0.0f, 0.0f),
    m_directInput(nullptr),
    m_keyboardInput(nullptr),
    m_mouseInput(nullptr)
{
    DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr);

    m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboardInput, NULL);
    m_directInput->CreateDevice(GUID_SysMouse, &m_mouseInput, NULL);

    m_keyboardInput->SetDataFormat(&c_dfDIKeyboard);
    m_mouseInput->SetDataFormat(&c_dfDIMouse);

    m_keyboardInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    m_mouseInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

    m_mouseInput->Acquire();
    m_keyboardInput->Acquire();
}

void Input::GetKeys(BYTE* keyState)
{
    m_keyboardInput->GetDeviceState(KEY_BUFFER_SIZE, (LPVOID)keyState);

    for(int Index = 0; Index < KEY_BUFFER_SIZE; ++Index)
    {
        *(keyState + Index) &= 0x80;
    }
}

void Input::GetMouse(DIMOUSESTATE* mouseState)
{
    m_mouseInput->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);
    mouseState->rgbButtons[0] &= 0x80;
    mouseState->rgbButtons[1] &= 0x80;
    mouseState->rgbButtons[2] &= 0x80;
    mouseState->rgbButtons[3] &= 0x80;
}

Input::~Input()
{
    if(m_keyboardInput)
    {
        m_keyboardInput->Unacquire();
    }
    if(m_mouseInput)
    {
        m_mouseInput->Unacquire();
    }
    if(m_directInput)
    {
        m_directInput->Release();
    }
}

void Input::UpdateInput()
{
    POINT cursor;
    DIMOUSESTATE mouse;
    BYTE keys[KEY_BUFFER_SIZE];
    GetMouse(&mouse);
    GetKeys(keys);

    // Update mouse position
    GetCursorPos(&cursor);
    ScreenToClient(m_hWnd, &cursor); 
    SetMouseCoord(static_cast<int>(cursor.x),static_cast<int>(cursor.y));

    // Update all keys
    for(KeyMap::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
    {
        UpdateKey(keys[it->first], it->second.state);

        bool keyDown = it->second.continuous ? 
            IsKeyDownContinous(it->second.state) : 
            IsKeyDown(it->second.state);

        KeyFn keyFn = keyDown ? 
            it->second.onKeyFn : 
            it->second.offKeyFn;

        if(keyFn != nullptr)
        {
            keyFn();
        }
    }

    // Update mouse
    UpdateKey(mouse.rgbButtons[MOUSE_LEFT], m_mouse);
    m_mouseClicked = IsKeyDown(m_mouse);

    std::for_each(m_clickPreventionKeys.begin(), m_clickPreventionKeys.end(),
        [&](const unsigned int& key){ if(IsKeyDownContinous(m_keys[key].state)){ m_mouseClicked = false; }});

    if(Diagnostic::AllowText())
    {
        Diagnostic::UpdateText("MouseDirection", Diagnostic::WHITE, 
            StringCast(m_mouseDirection.x)+", "+StringCast(m_mouseDirection.y));

        Diagnostic::UpdateText("MousePosition", Diagnostic::WHITE, StringCast(m_x)+", "+StringCast(m_y));
        Diagnostic::UpdateText("MousePress", Diagnostic::WHITE, StringCast(IsMousePressed()));
        Diagnostic::UpdateText("MouseClick", Diagnostic::WHITE, StringCast(IsMouseClicked()));
    }

    m_mouseDirection.x = 0.0f;
    m_mouseDirection.y = 0.0f;
}

bool Input::IsMousePressed() 
{
    return IsKeyDownContinous(m_mouse);
}

bool Input::IsMouseClicked() const
{
    return m_mouseClicked;
}

void Input::UpdateKey(BYTE pressed, unsigned int& state)
{
    if(pressed && (state & KEY_DOWN) != KEY_DOWN)
    {
        //save key as pressed
        state |= KEY_DOWN;
    }
    else if(!pressed && (state & KEY_DOWN) == KEY_DOWN)
    {
        //save key as not pressed
        state &= ~KEY_DOWN;
    }
}

bool Input::IsKeyDownContinous(unsigned int& state)
{
    return (state & KEY_DOWN) == KEY_DOWN;
}

bool Input::IsKeyDown(unsigned int& state)
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

void Input::SetMouseCoord(int x, int y)
{
    m_mouseDirection.x = static_cast<float>(m_x) - x;
    m_mouseDirection.y = static_cast<float>(m_y) - y;

    float length = std::sqrt((m_mouseDirection.x*m_mouseDirection.x) + 
        (m_mouseDirection.y*m_mouseDirection.y));

    if(length != 0.0f)
    {
        m_mouseDirection /= length;
    }

    m_x = x;
    m_y = y;
}

void Input::SetKeyCallback(unsigned int key, bool onContinous, KeyFn onKeyFn, KeyFn offKeyFn)
{
    m_keys[key] = Key();
    m_keys[key].state = BLANK_KEY;
    m_keys[key].continuous = onContinous;
    m_keys[key].onKeyFn = onKeyFn;
    m_keys[key].offKeyFn = offKeyFn;
}

void Input::UpdatePicking(Transform& projection, Transform& view)
{
    m_picking.UpdatePicking(projection, view, m_x, m_y);
}

void Input::SolvePicking()
{
    m_picking.SolvePicking();
}

void Input::AddClickPreventionKey(unsigned int key)
{
    if(m_keys.find(key) != m_keys.end())
    {
        m_clickPreventionKeys.push_back(key);
    }
}