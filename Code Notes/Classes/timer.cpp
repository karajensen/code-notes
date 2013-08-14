////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - timer.cpp
////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "timer.h"
#include "diagnostic.h"

Timer::Timer() :
    m_frequency(0.0),
    m_previousTime(0.0),
    m_deltaTime(0.0),
    m_deltaTimeCounter(0.0),
    m_fps(0),
    m_fpsCounter(0)
{
}

void Timer::StartTimer()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&m_timer);

    m_frequency = static_cast<double>(frequency.QuadPart);
    m_previousTime = static_cast<double>(m_timer.QuadPart);
}

double Timer::UpdateTimer()
{
    QueryPerformanceCounter(&m_timer);
    double currentTime = static_cast<double>(m_timer.QuadPart);

    m_deltaTime = (currentTime - m_previousTime) / m_frequency;
    m_deltaTimeCounter += m_deltaTime;
    if (m_deltaTimeCounter >= 1.0) //one second has passed
    {
        m_deltaTimeCounter = 0.0;
        m_fps = m_fpsCounter;
        m_fpsCounter = 0;
    }

    if(Diagnostic::AllowText())
    {
        Diagnostic::Get().UpdateText("FramePerSec", Diagnostic::WHITE, StringCast(m_fps));
        Diagnostic::Get().UpdateText("FramesCounter", Diagnostic::WHITE, StringCast(m_fpsCounter));
        Diagnostic::Get().UpdateText("DeltaTime", Diagnostic::WHITE, StringCast(m_deltaTime));
        Diagnostic::Get().UpdateText("DeltaTimeCounter", Diagnostic::WHITE, StringCast(m_deltaTimeCounter));
    }
    
    ++m_fpsCounter; //increment frame counter
    m_previousTime = currentTime;

    return m_deltaTime; 
}

    #ifdef _DEBUG
    Diagnostic::Get().UpdateText("FramePerSec", Diagnostic::WHITE, StringCast(m_fps));
    Diagnostic::Get().UpdateText("FramesCounter", Diagnostic::WHITE, StringCast(m_fpsCounter));
    Diagnostic::Get().UpdateText("DeltaTime", Diagnostic::WHITE, StringCast(m_deltaTime));
    Diagnostic::Get().UpdateText("DeltaTimeCounter", Diagnostic::WHITE, StringCast(m_deltaTimeCounter));
    #endif

    ++m_fpsCounter; //increment frame counter
    m_previousTime = currentTime;

    return m_deltaTime; 
}