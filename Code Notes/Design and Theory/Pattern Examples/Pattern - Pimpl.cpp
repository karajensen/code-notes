//////////////////////////////////////////////////////////////////////////////  
//PIMPL PATTERN
//////////////////////////////////////////////////////////////////////////////  
/*--------------------------------------------------------------------------
TYPE: Structural
USE: Allows changing of a class's private variable implementation without 
     editing the .h that contains its interface
--------------------------------------------------------------------------*/


//MYCLASS.H
class MyClass
{
public:
   MyClass();
   ~MyClass();
 
   MyClass(const MyClass &rhs);  
   MyClass& operator=(MyClass);
 
   void Public_Method();
 
private:

   class MyClassPimpl; 
   MyClassPimpl *pimpl_;
};


//MYCLASS.CPP
#include "MyClass.h"

class MyClass::MyClassPimpl
{
public:
   void   Private_Method()  {}  // dummy private function
   int    private_var_;         // a private variable
};
 
MyClass::MyClass():  
    pimpl_(new MyClassPimpl())
{
}
 
MyClass::~MyClass()
{
   delete  pimpl_;
}
 
void   MyClass::Public_Method()
{
   pimpl_->Private_Method();
   pimpl_->private_var_  = 3;
}


