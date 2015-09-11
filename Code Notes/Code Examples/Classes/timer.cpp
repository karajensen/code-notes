////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - timer.cpp
////////////////////////////////////////////////////////////////////////////////////////

#include "timer.h"
#include <string>

void Timer::StartTimer()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&m_timer);

    m_frequency = static_cast<double>(frequency.QuadPart);
    m_previousTime = static_cast<double>(m_timer.QuadPart);
}

void Timer::UpdateTimer()
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

    m_totalTime += m_deltaTime;
    m_totalTime = _finite(m_totalTime) ? m_totalTime : 0.0f;
    
    ++m_fpsCounter; 
    m_previousTime = currentTime;
}

float Timer::GetTotalTime() const
{
    return static_cast<float>(m_totalTime);
}

float Timer::GetDeltaTime() const 
{ 
    return static_cast<float>(m_deltaTime);
}

int Timer::GetFPS() const
{
    return static_cast<int>(m_fps);
}

int Timer::GetCappedFPS() const
{
    return min(static_cast<int>(m_fps), 60);
}