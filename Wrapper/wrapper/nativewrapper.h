#pragma once

#include <string>

#ifdef EXPORTCLASS
#define MYCLASSAPI __declspec(dllexport)
#else
#define MYCLASSAPI __declspec(dllimport)
#endif

namespace Wrapper
{
    class MYCLASSAPI MyNativeClass
    {
    public:

        MyNativeClass();
        ~MyNativeClass();
        void LogCaller(const std::string& caller);

    private:

        void* m_myclass;
    };
}