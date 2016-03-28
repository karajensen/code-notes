///////////////////////////////////////////////////////////////////////////////////////////////////
//MULTITHREADING
///////////////////////////////////////////////////////////////////////////////////////////////////
/*

• Threads within a program share same data space/information with main thread
• Thread has instruction pointer- keeps track of where its currently running
• Threads can be interrupted and put to sleep while other threads are running

HARDWARE THREADS
• Actually perform computation: one or more per CPU core

SOFTWARE/SYSTEM THREADS
• Operating system manages these across all processes for execution on hardware threads
• Throw exception if trying to create more than system can provide

AMDAHLS LAW
• Used to find the maximum expected improvement to an overall system when part of the system is improved
• Used in parallel computing to predict the maximum speed increase using multiple processors

OVERSUBSCRIPTION
• Not enough hardware threads for the software threads to use
• Thread schedular requires greater management costs when this happens

RACE CONDITION
• When multiple threads access the same variable concurrently with one of them writing to it
• Does not apply to multiple threads only reading or variables with internal synchronization (mutexes)
• Variable protected via mutex or making it atomic in low-lock or lockless code
• Without protection, may read before or after result of variable or have undefined behaviour

DEADLOCK
• Two threads hold a lock the other needs and block each other
• Reduced by only holding a single lock at a time

LIVELOCK
• Two threads compete for the same set of resources
• Can arise when threads detect a deadlock and try to step aside for each other
• Reduced by using a lock heirarchy

ATOMIC OPERATIONS: Non-blocking, work on simple data types
LOCKING: Blocking, for critical parts where only one thread is allowed access

SEMAPHORE:
• Can be locked by a set number of lockers concurrently
• Semaphore allowing only 1 locker is a Binary Semphore similar to a mutex
• Used as a signaling mechanism between processes

MUTEX: Provides mutual exclusion to a variable/section of code
MONITOR: Provides mutual exclusion to an object
RECURSIVE LOCK: Allows one thread to lock multiple times, requires releasing same number of times
SPIN LOCK: A spin lock polls its lock condition repeatedly rather than block

*/
///////////////////////////////////////////////////////////////////////////////////////////////////
//RACE CONDITIONS
///////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************
SIMPLE RACE
Multiple threads accessing/writing to the same variable with no synchronization
************************************************************************************************/
void Thread1() 
{
    myVar++;
}
void Thread2() 
{
    myVar++;
}

/************************************************************************************************
THREAD-HOSTILE REFERENCE COUNTING
Simple race with reference counting that can lead to memory leaks or double deleting
************************************************************************************************/
class RefCountedObject 
{
public:
    void Ref() 
    {
        m_ref++;
    }
    void Unref() 
    {
        if (--m_ref == 0)  // Need to use atomic decrement
            delete this;
    }
private:
    int m_ref;
};

/************************************************************************************************
RACE ON A COMPLEX OBJECT
Multiple threads access a thread unsafe object (eg. STL container) without synchronization 
************************************************************************************************/
void Thread1() 
{
    myMap[123] = 1;
}
void Thread2() 
{
    myMap[345] = 0;
}

/************************************************************************************************
NOTIFICATION
Incorrect synchronization between threads can cause issues if variable is cached
************************************************************************************************/
void Thread1() 
{
    while (!done) 
    {
        DoSomething();
    }
}
void Thread2() 
{
    DoSomethingElse();
    done = true;
}

/************************************************************************************************
INITIALIZING OBJECTS WITHOUT SYNCHRONIZATION
Construction done by multiple threads without synchronization can cause memory leaks
************************************************************************************************/
void InitObj() 
{
    if (!m_pointer)
        m_pointer = new MyObj();
}
void Thread1() 
{
    InitObj();
}
void Thread2() 
{
    InitObj();
}

/************************************************************************************************
RACE ON BIT FIELD
Race condition if x is of type struct BitField{ int a : 4, b : 4; }
************************************************************************************************/
void Thread1() 
{
    x.a++;
}
void Thread2() 
{
    x.b++;
}

/************************************************************************************************
DOUBLE-CHECKED LOCKING
Creation of Singleton happens as:
  1) Allocate memory to hold a Singleton object
  2) Construct a Singleton object in the allocated memory
  3) Make m_instance point to the allocated memory
Step 2-3 can be swapped by compiler which may cause the initial check to think its created
************************************************************************************************/
Singleton& Singleton::GetInstance() 
{
    if (m_instance == nullptr) 
    {
        Lock lock;
        if (m_instance = nullptr)
        {
            m_instance = new Singleton();
        }
    }
    return *m_instance;
}

/************************************************************************************************
RACE DURING DESTRUCTION
Object is created on stack, passed to thread 2 and goes out of scope before thread 2 finished
************************************************************************************************/
void Thread1()
{
    MyClass object;
    ExecuteCallbackInThread2(SomeCallback, &object);
    // object is destroyed when leaving its scope.
}

/************************************************************************************************
DATA RACE ON VPTR
************************************************************************************************/

/************************************************************************************************
DATA RACE ON VPTR DURING CONSTRUCTION
************************************************************************************************/   

/************************************************************************************************
RACE ON FREE
************************************************************************************************/

/************************************************************************************************
RACE DURING EXIT
************************************************************************************************/

/************************************************************************************************
RACE ON A MUTEX
************************************************************************************************/