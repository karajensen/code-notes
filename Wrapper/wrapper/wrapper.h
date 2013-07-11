#pragma once

#include <string>

namespace Wrapper
{
    class Logger;

    public ref class MyClass
    {
    public:

        MyClass();
        ~MyClass();
        !MyClass();
        void LogCaller(System::String^ caller);
        void LogCaller(const std::string& caller);

    private:

        void Release();
        Logger* log;
    };
}