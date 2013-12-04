////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - logger.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <fstream>
#include <boost/scoped_ptr.hpp>

/**
* Static class for logging application issues
*/
class Logger
{
public:

    /**
    * Destructor
    */
    ~Logger();

    /**
    * Initialises logging for the application
    */
    static void Initialise();

    /**
    * Logs info to a file and debug output window if windows
    * @param info The information to log
    */
    static void LogInfo(const std::string& info);

    /**
    * Logs an error to a file and debug output window if windows
    * @param error The error to log
    */
    static void LogError(const std::string& error);

private:

    /**
    * Constructor
    */
    Logger();

    std::fstream m_logfile; ///< filestream for the logfile
    static boost::scoped_ptr<Logger> sm_logger;
};