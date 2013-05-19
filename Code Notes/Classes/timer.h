/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com)
* FPS class for determining frame rate and delta time
*****************************************************************/
#pragma once

#include <Windows.h>

class Timer
{
public:

    Timer();

    /**
    * Starts the initial ticking of the timer
    */
    void StartTimer();

    /**
    * Stops/Starts the timer to determine delta-time and fps
    * Renders both if running in debug
    * @return the time passed between frames (seconds)
    */
    double UpdateTimer();

private:

    double m_frequency;
    LARGE_INTEGER m_timer;
    double m_previousTime;

    double m_deltaTime;         ///< Timestep in secs between frames
    double m_deltaTimeCounter;  ///< Combined timestep between frames up to 1 second
    unsigned int m_fps;         ///< Amount of frames rendered in 1 second
    unsigned int m_fpsCounter;  ///< Amount of frames rendered since delta time counter began
};

