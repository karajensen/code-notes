//////////////////////////////////////////////////////////////////////////////
//PYTHON MODULES
//////////////////////////////////////////////////////////////////////////////

//IMPORTING MODULES
//only ever imports once
import TestMod                  //import general
import TestMod as tm            //import with new alias
from TestMod import *           //import everything
from TestMod import TestFunct   //import specific

//////////////////////////////////////////////////////////////////////////////
//import sys
//////////////////////////////////////////////////////////////////////////////

sys.executable  //Name of the project executable
sys.argv        //List of strings of command line arguments
sys.argv[0]     //Name of the script (implicit)


//////////////////////////////////////////////////////////////////////////////
//import math
//////////////////////////////////////////////////////////////////////////////

math.acos(x)       //Returns the arc cosine of x in radians
math.acosh(x)      //Returns the arc hyperbolic cosine of x in radians
math.asin(x)       //Returns the arc sine of x in radians
math.asinh(x)      //Returns the arc hyperbolic sine of x in radians
math.atan(x)       //Returns the arc tangent of x in radians
math.atan2(y, x)   //Returns the arc tangent of y / x in radians
math.atanh(x)      //Returns the arc hyperbolic tangent of x in radians
math.ceil(x)       //Returns the smallest integer >= x as an int
math.copysign(x,y) //Returns x with y’s sign
math.cos(x)        //Returns the cosine of x in radians
math.cosh(x)       //Returns the hyperbolic cosine of x in radians
math.degrees(r)    //Converts from radians to degrees
math.e             //The constant e; approximately 2.7182818284590451
math.exp(x)        //Returns math.e ** x
math.fabs(x)       //Absolute float value
math.factorial(x)  //Returns x!
math.floor(x)      //Returns the largest integer <= x as an int
math.fmod(x, y)    //returns remainder of dividing x by y (use for floats instead of %)
math.fsum(i)       //Returns the sum of the values in iterable i as a float
math.hypot(x, y)   //Returns √(x² + y²)
math.isinf(x)      //Returns True if float x is ± inf (± ∞)
math.isnan(x)      //Returns True if float x is not a number
math.log(x, a)     //Returns logₐx; a is optional and defaults to math.e
math.log₁₀(x)      //Returns log₁₀x
math.modf(x)       //Returns x’s fractional and whole parts as two floats
math.pi            //The constant π; approximately 3.1415926535897931
math.pow(x, y)     //Returns xy as a float
math.radians(d)    //Converts from degrees to radians
math.sin(x)        //Returns the sine of x in radians
math.sinh(x)       //Returns the hyperbolic sine of x in radians
math.sqrt(x)       //Returns √x
math.tan(x)        //Returns the tangent of x in radians
math.tanh(x)       //Returns the hyperbolic tangent of x in radians
math.trunc(x)      //Truncates x; same as int(x)

//////////////////////////////////////////////////////////////////////////////
//import cmath
//////////////////////////////////////////////////////////////////////////////
//Math library for Complex Numbers

cmath.polar()
cmath.e        //The constant e; approximately 2.7182818284590451
cmath.pi       //The constant π; approximately 3.1415926535897931
               
//////////////////////////////////////////////////////////////////////////////
//import decimal
//////////////////////////////////////////////////////////////////////////////
//Constructors can take int or string as argument but not float
//Can't use the Math Modules
//Can be used with default operators/methods with exceptions:
//Decimal ** Int okay, Decimal ** Decimal not okay
//pow(Decimal,Int) okay, pow(Decimal,Decimal) not okay

myDecimal = decimal.Decimal(12234)
myDecimal = decimal.Decimal("234.0")
myDecimal = deciaml.Decimal.from_float(34.0)

myDecimal.exp()    //Returns math.e ** myDecimal
myDecimal.ln()     //Returns logₑmyDecimal
myDecimal.log10()  //Returns log₁₀myDecimal
myDecimal.sqrt()

//////////////////////////////////////////////////////////////////////////////
//import random
//////////////////////////////////////////////////////////////////////////////
    
random.uniform(-1.0,1.0)  //random float from -1.0 to 1.0
random.uniform(-1,1)      //random int from -1 to 1
random.choice(container)  //random member from container
random.shuffle(container) //randomnizes objects in container in place

//////////////////////////////////////////////////////////////////////////////
//import time
//////////////////////////////////////////////////////////////////////////////

//Get current CPU time (seconds) as float
time.clock()

//Suspends the calling thread for secs seconds.
time.sleep(secs)

//Get time as turple
time.localtime(time.time())
MyTime[0]   Year
MyTime[1]   Month
MyTime[2]   Day
MyTime[3]   Hour
MyTime[4]   Minute
MyTime[5]   Second
MyTime[6]   Day of Week	0 to 6 (0 is Monday)
MyTime[7]   Day of year	1 to 366
MyTime[8]   Daylight savings

//Get time as formatted Weekday Month Day Time Year
time.asctime(time.localtime(time.time()))

//Get time as formatted string
time.strftime("%m-%d-%Y", time.localtime())
%S = second
%M = minute
%H = hour
&d = day
%m = month
%Y = year

//////////////////////////////////////////////////////////////////////////////
//import calendar
//////////////////////////////////////////////////////////////////////////////

/*PRINTS
    January 2008
Mo Tu We Th Fr Sa Su
    1  2  3  4  5  6
 7  8  9 10 11 12 13
14 15 16 17 18 19 20
21 22 23 24 25 26 27
28 29 30 31*/
calendar.month(2008, 1)

//Returns if leap year or not
calendar.isleap(year)

//////////////////////////////////////////////////////////////////////////////
//import shutil
//////////////////////////////////////////////////////////////////////////////

shutil.copytree("folder1","folder2")    //copy folder1 to folder2, folder 2 cannot exist


//////////////////////////////////////////////////////////////////////////////
//import collections
//////////////////////////////////////////////////////////////////////////////

//NAMED TUPLES
myTuple = collections.namedtuple("MyTuple","one two three") //tuple members seperated by spaces
myTupleObj = MyTuple(1,2,3) //can use it like a class

//DEFAULT DICTIONARIES
myDict = collections.defaultdict(int) //default value created is from int()     
myDict[3] += "hello" //if key doesn't exist, creates value/key with default value


//////////////////////////////////////////////////////////////////////////////
//import os
//////////////////////////////////////////////////////////////////////////////
//Relative paths use current directory

os.rename("file1.txt","file2.txt") //rename a file
os.remove("file1.txt")             //delete the file
os.chdir("/myFolder")              //change the working directory
os.getcwd()                        //get current working directory
os.rmdir("/myFolder")              //remove a directory (must delete contents first) 
os.tmpnam()                        //returns file path to create temporary file
os.path.exists("Mypath.txt")       //true if the path exists
os.path.join("Folderpath","MyFile.txt")
os.path.isfile("filepath")         //true if not a folder
os.path.dirname(__file__)          //directory script is in
os.makedirs("MyFolderpath")        //creates the directory
os.listdir("MyFolderpath")         //returns a list of what's in the director
os.path.isfile("MyFile")           //returns true/false depending if folder or file

myFilePath.split(os.path.dirname(myFilePath)+"/",1) //splits directory and name into [dir, name]

//////////////////////////////////////////////////////////////////////////////
//import logging
//////////////////////////////////////////////////////////////////////////////

//LOGGING LEVELS
//Level determines what shows in the logging
//DEBUG: Diagnostic information
//INFO: Confirmation of events happening
//WARNING: Unexpected happening
//ERROR: Problem happening
//CRITICAL: Serious errors

//Create own logging file; use filemode from input/output
logging.basicConfig(filename="myFile.log", filemode='w', level=logging.DEBUG)
logging.basicConfig(format="%(asctime)s %(message)s", datefmt="%m/%d/%Y %I:%M:%S %p")

//Setup a logging object for each module logging is needed int
Logger = logging.getLogger(__name__) //where __name__ gives the modules name

//LOGGING METHODS
Logger.info("Message %i",myInt)
Logger.warning("Message %i",myInt)
Logger.error("Message %i",myInt)
Logger.exception("Message %i %f",myInt,myFloat)
Logger.critical("Message %i %s",myInt,myString)
log.exception("Message %i",myInt) //Also dumps stack trace

//////////////////////////////////////////////////////////////////////////////
//import traceback
//////////////////////////////////////////////////////////////////////////////

traceback.print_exc(file="myFile.txt") //print stack to file
traceback.format_exc() //return stack as tring


//////////////////////////////////////////////////////////////////////////////
//import xml.dom.minidom
//////////////////////////////////////////////////////////////////////////////

<root>
    <node name="node name">
       <type>30</type>
    </node>
</root>

//Create tree from file
DOMTree = xml.dom.minidom.parse("myfile.xml")
root = DOMTree.documentElement

//Get all nodes with same tag
nodes = root.getElementsByTagName("node")
for node in nodes:

    //Getting attributes
    if node.hasAttribute("name"):
        print "Name: %s" % node.getAttribute("name")

    //Getting child nodes
    type = movie.getElementsByTagName("type")[0]
    print "Type: %s" % type.childNodes[0].data

//Writing XML; text must be in xml form <root>...</root>
textAsXML = xml.dom.minidom.parseString(text).toxml()
with open(os.path.join(os.path.dirname(__file__),self.xmlFilename), "w") as fl:
    fl.write(textAsXML)

//////////////////////////////////////////////////////////////////////////////
//import queue
//////////////////////////////////////////////////////////////////////////////

myQueue.get()   //removes and returns an item from the queue.
myQueue.put()   //adds item to a queue.
myQueue.qsize() //returns the number of items that are currently in the queue.
myQueue.empty() //returns True if queue is empty; otherwise, False.
myQueue.full()  //returns True if queue is full; otherwise, False.

//////////////////////////////////////////////////////////////////////////////
//import thread
//////////////////////////////////////////////////////////////////////////////

//calls the passed in function in another thread
//terminates thread once function finished
//calls myFunction(a,b), empty turple used for no arguments
thread.start_new_thread(myFunction, turple("hello",2))

//////////////////////////////////////////////////////////////////////////////
//import threading
//////////////////////////////////////////////////////////////////////////////

threading.activeCount()   //Returns the number of thread objects that are active.
threading.currentThread() //Returns the number of thread objects in the caller's thread control.
threading.enumerate()     //Returns a list of all thread objects that are currently active.

myThread.run()      //entry point for a thread.
myThread.start()    //starts a thread by calling the run method.
myThread.join()     //waits for threads to terminate.
myThread.isAlive()  //checks whether a thread is still executing.
myThread.getName()  //returns the name of a thread.
myThread.setName()  //sets the name of a thread.

// Global var all threads can access
exitFlag = 0

// Inherit from threading base class
class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        self.threadID = threadID
        self.name = name
        self.counter = counter
        threading.Thread.__init__(self)
    def run(self):
        threadLock.acquire() //get lock to synchronize threads
        process_data(self.name, self.counter, 5)
        threadLock.release() //free lock to release next thread

// Process threads data
def process_data(threadName, delay, counter):
    while (exitFlag != 0):
        time.sleep(delay)
    else:
        thread.exit()

// Create new threads
threadLock = threading.Lock()
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

// Start new threads
thread1.start()
thread2.start()

// Add threads to a list
threads = []
threads.append(thread1)
threads.append(thread2)

//Wait for all threads to complete before leaving main thread
for t in threads:
    t.join()
