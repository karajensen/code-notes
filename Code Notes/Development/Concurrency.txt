///////////////////////////////////////////////////////////////////////////////////////////////////
//MULTITHREADING
///////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//RACE CONDITIONS
///////////////////////////////////////////////////////////////////////////////////////////////////