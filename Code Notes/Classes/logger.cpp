#include "logger.h"
#include <string>

#ifdef _IRR_WINDOWS_
#include <Windows.h>
#endif

boost::scoped_ptr<Logger> Logger::sm_logger;

Logger::Logger()
{
    m_logfile.open("logfile.txt",std::ios_base::out);
}

Logger::~Logger()
{
    if(m_logfile.is_open())
    {
        m_logfile << std::endl;
        m_logfile.close();
    }
}

void Logger::Initialise()
{
    sm_logger.reset(new Logger());
}

void Logger::LogInfo(const std::string& info)
{
    sm_logger->m_logfile << "INFO: \t" << info << std::endl;


#ifdef _IRR_WINDOWS_
    OutputDebugString((info+"\n").c_str());
#endif
}

void Logger::LogError(const std::string& error)
{
    sm_logger->m_logfile << "ERROR: \t" <<  error << std::endl;

#ifdef _IRR_WINDOWS_
    OutputDebugString((error+"\n").c_str());
#endif
}