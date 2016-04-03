
#define EXPORTCLASS
#include "nativewrapper.h"
#include "wrapper.h"
#include <vcclr.h>

namespace Wrapper
{
    MyNativeClass::MyNativeClass() :
        m_myclass(nullptr)
    {
        //gcroot provides handle to address of the object on the managed heap
        //it will update as the object is moved by the GC
        MyClass^ myClass = gcnew MyClass();
        gcroot<MyClass^>* pointer = new gcroot<MyClass^>(myClass);
        m_myclass = (void*)pointer;
    }

    void MyNativeClass::LogCaller(const std::string& caller)
    {
        if(m_myclass)
        {
            gcroot<MyClass^>* pointer = reinterpret_cast<gcroot<MyClass^>*>(m_myclass);
            ((MyClass^)*pointer)->LogCaller(caller);
        }
    }

    MyNativeClass::~MyNativeClass()
    {
       if (m_myclass)
       {
          gcroot<MyClass^>* pointer = reinterpret_cast<gcroot<MyClass^>*>(m_myclass);
          m_myclass = nullptr;
          delete pointer; //deleting the gcroot wrapper releases managed MyClass
       }
    }
}
