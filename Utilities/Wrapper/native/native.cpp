#include <iostream>
#include "../wrapper/nativeWrapper.h"

int main()
{
    Wrapper::MyNativeClass* myHeapObj = new Wrapper::MyNativeClass();
    myHeapObj->LogCaller("Hello from Native");
    delete myHeapObj;

    std::cin.get();
    return 0;
};