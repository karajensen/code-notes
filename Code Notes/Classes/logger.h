/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 2012
* Static class for logging
*****************************************************************/
#pragma once

#include <fstream>
#include <boost/scoped_ptr.hpp>

class Logger
{
public:

    Logger();
    Logger::~Logger();

    /**
    * Initialises logging for the application
    */
    static void Initialise();

    /**
    * Logs to a file and debug output window if windows
    * Info prepends INFO to message, Error prepends ERROR
    */
    static void LogInfo(const std::string& info);
    static void LogError(const std::string& error);

private:

    std::fstream m_logfile;
    static boost::scoped_ptr<Logger> sm_logger;
};