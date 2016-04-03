
#include "wrapper.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>

namespace Wrapper
{
    class Logger
    {
    public:

        Logger::Logger()
        {
            m_logfile.open("logfile.txt",std::ios_base::out);
        }

        Logger::~Logger()
        {
            if(m_logfile.is_open())
            {
                m_logfile.close();
            }
        }

        void Logger::LogInfo(const char* info)
        {
            m_logfile << info << std::endl;
        }

    private:
        std::fstream m_logfile;
    };

    MyClass::MyClass()
    {
        log = new Logger();
        log->LogInfo("inside constructor");
    }

    void MyClass::Release()
    {
        if(log)
        {
            delete log;
            log = nullptr;
        }
    }

    void MyClass::LogCaller(const std::string& caller)
    {
        log->LogInfo(caller.c_str());
    }

    void MyClass::LogCaller(System::String^ caller)
    {
        msclr::interop::marshal_context context;
        std::string stdCaller = context.marshal_as<std::string>(caller);
        log->LogInfo(stdCaller.c_str());
    }

    MyClass::!MyClass()
    {
        log->LogInfo("inside finaliser");
        Release();
    }

    MyClass::~MyClass()
    {
        //will suppress finalisation if managed
        log->LogInfo("inside destructor");
        Release();
    }
}
