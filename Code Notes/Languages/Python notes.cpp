//////////////////////////////////////////////////////////////////////////////
//PYTHON
//////////////////////////////////////////////////////////////////////////////

+   Addition 
-   Subtraction
*   Multiplication
/   Division 
%   Remainder
**  Exponent
#   Comment
0x  Hexadecimal
0b  Binary
0o  Octal 

x / y              //division that always produces float or complex if one is complex
x / / y            //division that always produces int result
x * * y            //x to power of y
bin(i)             //returns binary of i as a string
hex(i)             //returns hex of i as a string
oct(i)             //returns octal of i as a string
pow(x,y)           //x to power of y
pow(x,y,z)         //(x ** y) % z
divmod(x,y)        //returns turple of two ints with amount divided into and remainder
abs(x)             //absolute value
isinstance(o,MyCl) //returns true if object is instance/subclass of custom class 'class MyCl'
type(myInt)        //returns type of the variable (type(myInt) is int == true)
round(x,n)         //return value is same type as x
round(1.246,2)     //if n is positive, round to n decimal places, outputs 1.25
round(34.8,-1)     //if n is negative, round to n integral places, outputs 30.0
min(a,b)
max(a,b)

//PRINTING
print("str")
print "A string" + testString
print "The total is: ", add1 + add2 

//MULTILINE
//containers don't need to use
total = item_one + \
        item_two + \
        item_three

//////////////////////////////////////////////////////////////////////////////
//VARIABLES
//////////////////////////////////////////////////////////////////////////////

myInt = 1      /*or*/   myInt = int(1)
myFloat = 1.0  /*or*/   myFloat = float(1.0)
myBool = True 

//ASSIGNING 
a = b = c = 1 
a,b = (c,d) //does a = c, b = d, brackets optional
myVar = None //null variable

//IMMUTABLE
• Objects whose values cannot change once created (const)
• String, int, float, tuple

//MUTABLE
• Ojbects whose values can change once created
• Classes, Dictionary, Lists

//CONVERSIONS
int(x)   //converts x to integer
int(s)   //converts string to integer
float(x) //converts x to float
myFloat.is_integer() //Returns true if float has no fractional part
(123.0).is_integer() //Calling on literal number

//////////////////////////////////////////////////////////////////////////////
//ENUMS
//////////////////////////////////////////////////////////////////////////////

myEnum = StringEnum(Apple="Red")
apple = myEnum.Apple //gives "Red"

//##
//# Enum helper method
//# @return in form of keyword=value
def StringEnum(self,**enums):
    return type("StringEnum", (), enums)

//////////////////////////////////////////////////////////////////////////////
//COMPLEX NUMBERS
//////////////////////////////////////////////////////////////////////////////

myComplex = 1.0 + 2.0j
myComplex = Complex(1.0,2.0)
myComplex = Complex() //no arguments returns 0j
myComplex.conjugate() //Get conjugate of complex number
myComplex.real        //returns 1.0 (real part)
myComplex.imag        //returns 2.0 (imaginary part)


//////////////////////////////////////////////////////////////////////////////
//BIT MANIPULATION
//////////////////////////////////////////////////////////////////////////////

x | y   //Bitwise OR
x ^ y   //Bitwise XOR
x & y   //Bitwise &
x << y  //Shifts x left by y bits
x >> y  //Shifts x right by y bits
~x      //Bit invert    

//////////////////////////////////////////////////////////////////////////////
//LOOPING/LOGIC
//////////////////////////////////////////////////////////////////////////////
//Logical operators: and, or, not
//Logic: continue, break

//WHILE LOOP
a = 0
while a < 10:
    a = a + 1
    break
else:
    //done if loop finishes not done if 
    //exception thrown, break or return used

//BRANCHING IF STATEMENT
if (y == 1) and (x != 3):
    print "Test1"
elif (y < 7):
    print "Test2"
elif y or x:
    print "Test3"
elif not x:
    print "Test4"
else:
    print "Test5"
        
//FOR LOOP
for i in range(0,10):
    //from 0 to 9, 10 exits loop
else:
    //executed only when loop ends

//FOR CONTAINER LOOPS
for i in myList:
    print i

for i in range(len(L)):
    L[i] = process(L[i])

for x, y in ((1, 1), (2, 4), (3, 9)):
    print(x, y)

if value not in myContainer:
    print(value)

myContainer = [y for y in range(0, 10)]

//Ternary operator
c = a if condition else b

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//BYVAL-BYREF
//References to variables are passed in byval
//Eg. Container passed in can change individual members of what it holds
//If changing what container myCon references is byval
def myFunction(x, y):   
    a = x+y
    return a

def myFunction(myList):
    myList[0] = "can change byref"
    myList = ["changes","byval"]
    return //void

//DEFAULT VALUES
def myFunction(name="name")

//DEFAULT VALUES FOR MUTABLE CONTAINERS
def myFunction(myList=[]) //Creates a static container
def myFunction(myList=None) //Create a new container inside function each time called
    if myList == None
        myList = []

//KEYWORD ARGUMENTS
//allows any ordering of arguments
def myFunction(name, age)
myFunction(age=50, name="name")

//PREVENT POSITIONAL ARGUMENTS
def myFunction(a,b,*,c,d) //Only allows keyword arguments after *
def myFunction(*,a,b,c,d) //Only allow keyword arguments
myFunction(1,2,c=5,d=2)
myFunction(a=1,b=2,c=5,d=2)

//VARIADIC FUNCTIONS
//allows any number of arguments
def myFunction(*vartuple):
   for var in vartuple:
      print var
   return
myFunction(10,23,45,12,23) 
myFunction(*myList) //unpack whole container

//VARIADIC DICTIONARIES
def myFunction(**varDict)
    for key in varDict
        print varDict[key]
    return

//LAMBDA FUNCTIONS
//can only contain one return expression
MyFunction = lambda a, b: a + b;
MyFunction(10, 20)

MyFunction = lambda: myOtherFunction("hello")
MyFunction() //calls myOtherFunction("hello")

//FUNCTION REFERENCES
myObjFn = obj.myFunction
        
//////////////////////////////////////////////////////////////////////////////
//CLASSES
//////////////////////////////////////////////////////////////////////////////

class MyClass(object): //if no custom base class, use object
    'Optional class documentation string'
    myStaticVar
    __myPrivateStaticVar

    //CONTRUCTOR
    //defining in the contructor creates the member vars
    def __init__(self,x,y):
        super(MyClass,self).__init() //Call the base class constructor
        self.x = x
        self.y = y //member var
        self.__privateVar = 0.0  //private member var
        MyClass.myStaticVar = 0.0 //static var
        MyClass.__myPrivateStaticVar = 0.0 //private static var

    //DESTRUCTOR
    def __del__(self):
        print __name__

    //EQUALITY TEST
    //called when obj1 == obj2
    //If specified, no longer hashable- can't be used as keys or stored in sets
    //Inequality version auto generated if equality is specified
    def __eq__ (self, o)
        if not isinstance(o, MyClass): //only allow comparion between same object types
            return NotImplemented
        return (self == x)

    //OVERLOADING +
    //called when obj1+obj2
    def __add__(self, o):
        return self.x+o.x

    //GETTER METHOD
    @property
    def privateVar(self):
        return self.__privateVar

    //SETTER METHOD
    @privateVar.setter
    def privateVar(self, x):
        self.__privateVar = x

    //CLASS METHOD WITHOUT SELF
    @staticmethod
    def myStaticFunction(x)
        return x

    //CLASS METHOD
    def myFunction(self, z):
        return self.x + self.y + z

//=========================================================================
//OPTIMISED CLASSES
//=========================================================================
//Can't add/remove members dynamically
//Normal classes contain members in a private dictionary, slots removes this
//Consumes less memory and faster than normal classes
//Inherit from Object, any derived from myOpClass must define __slots__
//If no members, use __slots__ = ()
class myOpClass(Object):

    __slots__ = ("x","y") //list of member variables

    def __init__(self, x=0):
        self.x = x
        self.y = 10

//=========================================================================
//CLASS OBJECTS
//=========================================================================
//calling any function before the constructor will automatically 
//call __new__ and then __init__ on the object
obj = MyClass(100,45)
obj.myFunction(40)
obj.x

//=========================================================================
//BUILT IN CLASS ATTRIBUTES
//=========================================================================
__dict__   //Dictionary containing the class's namespace.
__doc__    //Class documentation string, or None if undefined.
__name__   //Class name.
__module__ //Module name in which the class is defined
__bases__  //Tuple with the base classes in the order of their 
           //occurrence in the base list, empty if none

//=========================================================================
//ATTRIBUTES (MEMBERS)
//=========================================================================

//Makes use of the private dictionary
//Throws error if __slots__ is enabled
//Throws AttributeError if member does not exist
__delattr__(self,x)       //Use: del obj.x Deletes member x from obj
__dir__(self)             //Use: dir(obj) Returns a list of objs attribute names
__getattr__(self,x)       //Use v = obj.x Returns the value of member x 
__setattr__(self,x,value) //Use: obj.x = value Sets member x to value

//ADDING NEW ATTRIBUTES
myObj.newAttribute = 100 // if newAttribute doesn't exist, creates newAttribute just for myObj


//=========================================================================
//CLASS IMPLICIT FUNCTIONS
//=========================================================================
__init__()             //constructor
__del__(self)          //destrutor
__eq__ (self, other)   //use: x == y

//=========================================================================
//CLASS OVERLOADS
//=========================================================================
__abs__(self)               //use: abs(x) 
__complex__(self)           //use: complex(x)
__float__(self)             //use: float(x) 
__int__(self)               //use: int(x)
__index__(self)             //use: bin(x) oct(x) hex(x)
__round__(self, digits)     //use: round(x, digits)
__lt__(self, other)         //use: x < y
__le__(self, other)         //use: x <= y 
__eq__(self, other)         //use: x == y 
__ne__(self, other)         //use: x != y 
__ge__(self, other)         //use: x >= y 
__gt__(self, other)         //use: x > y
__pos__(self)               //use: +x 
__neg__(self)               //use: -x
__add__(self, other)        //use: x + y 
__sub__(self, other)        //use: x - y
__iadd__(self, other)       //use: x += y 
__isub__(self, other)       //use: x -= y
__radd__(self, other)       //use: y + x 
__rsub__(self, other)       //use: y - x
__mul__(self, other)        //use: x * y 
__mod__(self, other)        //use: x % y
__imul__(self, other)       //use: x *= y 
__imod__(self, other)       //use: x %= y
__rmul__(self, other)       //use: y * x 
__rmod__(self, other)       //use: y % x
__floordiv__(self, other)   //use: x // y 
__truediv__(self, other)    //use: x / y
__ifloordiv__(self, other)  //use: x //= y 
__itruediv__(self, other)   //use: x /= y
__rfloordiv__(self, other)  //use: y // x 
__rtruediv__(self, other)   //use: y / x
__divmod__(self, other)     //use: divmod(x, y) 
__rdivmod__(self, other)    //use: divmod(y, x)
__pow__(self, other)        //use: x ** y 
__and__(self, other)        //use: x & y
__ipow__(self, other)       //use: x **= y 
__iand__(self, other)       //use: x &= y
__rpow__(self, other)       //use: y ** x 
__rand__(self, other)       //use: y & x
__xor__(self, other)        //use: x ^ y 
__or__(self, other)         //use: x | y
__ixor__(self, other)       //use: x ^= y 
__ior__(self, other)        //use: x |= y
__rxor__(self, other)       //use: y ^ x 
__ror__(self, other)        //use: y | x
__lshift__(self, other)     //use: x << y 
__rshift__(self, other)     //use: x >> y
__ilshift__(self, other)    //use: x <<= y 
__irshift__(self, other)    //use: x >>= y
__rlshift__(self, other)    //use: y << x 
__rrshift__(self, other)    //use: y >> x
__invert__(self)            //use: ~x
__str__(self)               //use: str(x)
__bool__(self)              //use: bool(x)
__hash__(self)              //use: hash(x) converts to a dict key or set member


//////////////////////////////////////////////////////////////////////////////
//INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//Supports multiple inheritance, all class methods are inheritly virtual
//Default inherits class Object if no inheritance used
//Slots must be inherited from base
//If diamond MI, uses shared base class from first declared (BaseA)

//BASE CLASS
class BaseA: //default inherits Object, best to explicitly use it though

    def __init__(self,x):

    def method(self):   //Base method overidden

//DERIVED CLASS
class Deri(BaseA, BaseB):

    def __init__(self,x):
        super(Deri,self).__init(x) //Call the base class constructor

    def method(self):     //Derived method will override
        BaseA.method()    //Explicitly call base class method
      
//////////////////////////////////////////////////////////////////////////////
//DECORATORS
//////////////////////////////////////////////////////////////////////////////

//myFunction() is compiled and passed to the myDecorator code for editing
//Decorate passes back a new function object to be used in place of function
@myDecorator
def myFunction()
    x = int()

//CLASSES AS DECORATORS
class myDecorator(object):

    //Constructor passes in myFunction
    def __init__(self, func):
        self.func = func

    //Call override calls myFunction and anything else that needs to be done
    def __call__(self):
        self.func()

//FUNCTIONS AS DECORATORS
def myDecorater(func):
    def new_func():
        func()
    return new_func //return new function

//DECORATORS FOR ERROR CHECKING / UNIT TESTS
def positive_result(funct):
    @functools.wraps(funct) //ensures new_funct has origin functions name/documentation
    def new_funct(*args, **kwargs): //take in variable arguments
        result = funct(*args, **kwargs)
        assert result >= 0, function.__name__ + "() result isn't >= 0"
        return result
    return new_funct //return new function

def boxIsChecked(func):
    def new_func(self,attribute,obj):
        if attribute[VALUE][1].isChecked():
            return func(self,attribute,obj)
        return ""
    return new_func

@positive_result
def GetValue(a, b, c):
    return a*b*c

//DECORATORS WITH MULTIPLE ARGUMENTS
def myDecWrapper(a,b)
    def myDecorator(funct)
        @functools.wraps(funct)
        def new_funct(*args, **kwargs):
            result = funct(*args, **kwargs)
            if result == a
                return a
            return b
        return new_funct
    return myDecorator

@myDecWrapper(0,200)
def myFunction(x,y)
    return x*y

//////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
//////////////////////////////////////////////////////////////////////////////

                             Exception
                                 | 
       -------------------------------------------------------
      |                 |             |           |           |
ArithmaticError  EnvironmentError  EOFError  LookupError  ValueError
                        |                         |
                     -------                  ----------
                    |       |                |          |
                 IOError  OSError        IndexError  KeyError


//EXCEPTION TYPES
IOError        //Can't read/write data to file
ValueError     //Value not found for lists/tuples
KeyError       //Value not found for dictionaries/sets
EOFError       //when file reaches end
AttributeError //class method could not be found

//TRY-CATCH BLOCK
try:
except (LookupError, IOError) as err:
    print err
except ValueError as err:
    print err.args
    print "ValueError({0}):{1}".format(err.errno, err.strerror)
else: //for no exception

try:
except Exception, reason: //for any exception
    print reason
except: //for any exception
    print "Unexpected error:", sys.exc_info()[0]
else: //for no exception
finally: //do whether exception was raised or not

//RAISING EXCEPTIONS
raise RuntimeError("Message")

//USER DEFINED EXCEPTIONS
class MyError(RuntimeError):
   def __init__(self, arg):
      self.args = arg
try:
   raise MyError("An Error")
except MyError e:
   print e.args

//ASSERTIONS
assert x < 0, "My Assertion String message if false (x >= 0)"

//////////////////////////////////////////////////////////////////////////////
//FILE INPUT/OUTPUT
//////////////////////////////////////////////////////////////////////////////

//ACCESS MODES
r	//Reading: File pointer at beginning
w	//Writing: Overwrites the file if file exists otherwise creates new
w+	//Writing/Reading: Overwrites the file if file exists otherwise creates new
a	//Writing(Appending): File pointer at end of file if file exists otherwise creates new
a+	//Writing(Appending)/Reading: File pointer at end of file if file exists otherwise creates new
    
//OPENING FILE
openfile = open('filename', 'r')
openfile.closed //true if closed
openfile.mode //returns access mode
openfile.name //returns file name

//CLOSING FILE
openfile.close()

//MOVING CURSOR IN TEXT FILE 
//0 = start, 1 = current position, 2 = end
//need to make sure cursor is at correct position
openfile.tell()      //returns where cursor currently is
openfile.seek(45,0)  //move the cursor to 45 bytes/letters after the beginning of the file.
openfile.seek(10,1)  //move the cursor to 10 bytes/letters after the current cursor position.
openfile.seek(-77,2) //move the cursor to 77 bytes/letters before the end of the file

//READING FROM TEXT FILE
openfile.next()       //reads next line from file each time function is called
openfile.read()       //shows /n character
openfile.readline()   //reads where cursor is till end of line /n, shows /n character
openfile.readline(4)  //reads where cursor is over 4 bytes/characters

TestList = openfile.readlines() //reads all lines from cursor onwards, returns a list 
TestList[0]  //gives first line in text file
TestList[1]  //gives second line in text file

//READ LOOPS
while True:
    try:
        //read some lines
    except EOFError:
        break

for line in open(filename, encoding="utf8"):
    process(line)

//WRITING TO TEXT FILE
//writes to file from where cursor is and overwrites text in front of it
openfile.write('TestString') 

//WRITING CONTAINERS
import pickle                           
TestList = ['one',2,'three','four',5]       
file = open('filename', 'w')                
pickle.dump(TestList,file)      
file.close()                                

//READING CONTAINERS
import pickle
file = open('filename','r')
TestList = pickle.load(file)
file.close()

//////////////////////////////////////////////////////////////////////////////
//C++ EXTENSIONS
//////////////////////////////////////////////////////////////////////////////
//Save methods in MyExt.c

#include <Python.h> //must be before any other includes

//FUNCTION WITH ARGUMENTS
static PyObject* MyFunction(PyObject* self, PyObject* args)
{
   int myInt;
   double myDouble;
   char* myString;

   //Possible values to parse are: i=int, d=double, s=char*, f=float, l=long, c=char
   if(!PyArg_ParseTuple(args, "ids", &myInt, &myDouble, &myString)) 
   {
      return Py_RETURN_NONE;
   }
    
   //Return an int(i) 
   return Py_BuildValue("i", myInt + static_cast<int>(myDouble));

   //Return two values (creates a list)
   return Py_BuildValue("is", myInt, "hello");
}

//FUNCTION WITHOUT ARGUMENTS
static PyObject* MyFunctionNoArgs(PyObject* self)
{
    Py_RETURN_NONE; //return void
}

//FUNCTION DOCUMENTATION
static char MyFunctionNoArgs_doc[] = "MyFunctionNoArgs(): Any message you want to put here!!\n";
static char MyFunction_doc[] = "MyFunction(): Any message you want to put here!!\n";

//FUNCTION OBJECT FOR PYTHON TO USE
static PyMethodDef MyExt_funcs[] = 
{
    {"MyFunctionNoArgs", (PyCFunction)MyFunctionNoArgs, METH_NOARGS, MyFunctionNoArgs_doc},
    {"MyFunction", (PyCFunction)MyFunction, METH_VARARGS, MyFunction_doc },
    {NULL, NULL, 0, NULL}
};

//INITILISATION FUNCTION
void initMyExt()
{
    Py_InitModule3("MyExt", MyExt_funcs, "Extension module example!");
}

//BUILDING THE EXTENSION
//Add to setup.py script and run command: python setup.py install
from distutils.core import setup, Extension
setup(name='MyExt', version='1.0', ext_modules=[Extension('MyExt', ['MyExt.c'])])

//IMPORTING THE EXTENSION
import MyExt
MyExt.MyFunctionNoArgs()

//////////////////////////////////////////////////////////////////////////////
//PYTHON ALGORITHMS
//////////////////////////////////////////////////////////////////////////////

//## 
//# Checks if extension matches supported image types
//# @param the filename of the image with the extension
//# @return whether image is valid or not
def isValidImage(self, filename):
    splitFile = filename.split(os.extsep, 1)
    if len(splitFile) > 1:
        extension = splitFile[1].lower()
        supportedImageTypes = ["png","jpg","jpeg","bmp"]
        for imageType in supportedImageTypes:
            if extension == imageType:
                return True
    return False

//## 
//# Checks if the filename has the given extension type
//# @param the filename of the image
//# @param the extension to check for
//# @return whether image is valid or not
def hasExtension(self, filename, ext):
    splitFile = filename.split(os.extsep, 1)
    if len(splitFile) > 1:
        if splitFile[1].lower() == ext:
            return True
    return False

//##
//# Checks if folder exists and creates if not
def checkFolderPath(self, pathname):
    if not os.path.exists(pathname):
        os.makedirs(pathname)