///////////////////////////////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////

assert(x == 0);
throw("Message goes here");
exit(EXIT_FAILURE);

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <exception>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//=====================================================================================
//BASIC EXCEPTION
//=====================================================================================

//Try-Catch block
try 
{ 
    testfunction() 
} 
catch (const char * s) // start of exception handler
{
    cout << s << endl;
}
catch (double x) 
{
    cout << x << endl;
}
catch (...) //catches ANYTHING
{
    cout << "caught!" << endl;
}

//Exception Function
void testfunction()
{
if (something happens)
    throw "error message!";
else
    throw 1;
}

//TYPES OF EXCEPTION FUNCTIONS
void testfunction(); //can throw anything
void testfunction() throw(const char *, double); //can throw string or double exception
void testfunction() throw(); //DOESN'T THROW EXCEPTION

//IOS_BASE EXCEPTIONS
cin.exceptions(ios_base::failbit);
bool okay = false;

while (!okay)
{
    try
    {
        cout << "Enter: ";
        int x;
        cin >> x;
        okay = true; //this line only happens if everything is okay
    }
    catch (ios_base::failure & e)
    {
        cout << e.what() << endl;
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }
}
//=====================================================================================
//DERIVING EXCEPTIONS
//=====================================================================================

//DERIVING OWN FROM EXCEPTION BASE CLASS
class myClass: public std::exception
{
public:
    virtual const char * what() const { return "bad arguments"; } //overload what()
};

try 
{
    throw myClas();
}
catch(std::exception & e)
{
    cout << e.what() << endl;
}

//UNEXPECTED EXPECTION: 
//Occurs when exception thrown that function doesn't expect to be thrown
//calls unexpected() -> terminate() -> abort()
try 
{
}
catch(std::bad_exception & e) //catch the bad_exception thrown
{
    cout << e.what() << endl;
}

set_unexpected(myUnexpeced);
void myUnexpected()
{
    throw; //original exception is thrown again
    throw std::bad_exception(); //bad_exception is thrown
}


//UNCAUGHT EXCEPTION: Occurs when no matching
//calls terminate() -> abort()
set_terminate(myQuit);
void myQuit()
{
    cout << "Terminating due to uncaught exception\n";
    exit(5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Logic/Runtime error families derived publically from Exception class

//LOGIC ERROR FAMILY
domain_error
invalid_argument
length_error
out_of_bounds

//RUNTIME ERROR FAMILY
range_error
overflow_error
underflow_error

try
{
}
catch(out_of_bounds & oe) // catch out_of_bounds error
{cout << e.what() << endl;}
catch(logic_error & oe) // catch remaining logic_error family
{cout << e.what() << endl;}
catch(exception & oe) // catch runtime_error, exception objects
{cout << e.what() << endl;}

