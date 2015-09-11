////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - timer.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>

/**
* FPS class for determining frame rate and delta time
*/
class Timer
{
public:

    /**
    * Starts the initial ticking of the timer
    */
    void StartTimer();

    /**
    * Stops/Starts the timer to determine delta-time and fps
    */
    void UpdateTimer();

    /**
    * @return The time passed since last frame in seconds
    */
    float GetDeltaTime() const;

    /**
    * @return the total time passed since starting the simulation
    */
    float GetTotalTime() const;

    /**
    * @return the frames per second
    */
    int GetFPS() const;

    /**
    * @return the capped frames per second
    */
    int GetCappedFPS() const;

private:

    double m_frequency = 0.0;         ///< The frequency of the high-resolution performance counter
    LARGE_INTEGER m_timer;            ///< The current time queried
    double m_previousTime = 0.0;      ///< The previous time queried
    double m_deltaTime = 0.0;         ///< The time passed since last frame in seconds
    double m_deltaTimeCounter = 0.0;  ///< Combined timestep between frames up to 1 second
    double m_totalTime = 0.0;         ///< The time passed since start of the timer
    unsigned int m_fps = 0;           ///< Amount of frames rendered in 1 second
    unsigned int m_fpsCounter = 0;    ///< Amount of frames rendered since delta time counter began
};

