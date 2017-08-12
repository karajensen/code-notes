//////////////////////////////////////////////////////////////////////////////
//PYTHON CONTAINERS
//////////////////////////////////////////////////////////////////////////////

//TYPES OF CONTAINERS
STRINGS:    Immutable, Sequence
TUPLE:      Immutable, Sequence
LIST:       Mutable, Sequence
DICTIONARY: Mutable, Mapping

//CONTAINER METHODS
v in a     //returns true if value (or key if dictionary) is in a
v not in a //returns true if value (or key if dictionary) is not in a
len(a)     //number of members in container
cmp(a,b)   //Compares elements of both containers
max(a)     //Returns item with max value
min(a)     //Returns item with min value
any(a)     //Returns true if any value in a == true
all(a)     //Returns true if all values in a == true

//Returns sorted container
//Sort function option, reverse false by default
sorted(a, key=sortFn, reverse=true) 
 
//==============================================================================
//MAPPING TYPES: DICTIONARIES
//==============================================================================

//MAPPING UNPACKING (**)
//key must match function argument name or TypeError is raised
def myFun(a,b,c)
MyDict = dict(a="AA",d="DD",c="CC",b="DD")
MyFun(**MyDict) //unpacks to a="AA",b="BB",c="CC"

//==============================================================================
//SEQUENCE TYPES: STRING,LIST,TURPLE
//==============================================================================

a + b //Returns container combined with both containers
a * n //Returns container times by n

//STARRED EXPRESSIONS
a, *b = [9, 2, -4] //stores a=9, b=[2,-4]
a, *b, c = [9, 2, 5, -4] //stores a=9, b=[2,5], c=-4

//SEQUENCE UNPACKING (*)
def MyFun(a,b,c)
mySeq = [1,2,3,4,5,6]
MyFun(*mySeq) //unpacks to a=mySeq[0],b=mySeq[1],c=mySeq[2]

mySeq[0]   //0-based array
mySeq[-1]  //gives last member
mySeq[-2]  //gives second last member

mySeq[:] /*or*/ mySeq[0:len(mySeq)] //return the whole container
mySeq[1:3]   //returns members at index 1-2
mySeq[:7]    //returns 0-6
mySeq[7:]    //returns 7-end
mySeq[::2]   //return every 2nd from whole container, start defaults to 0, end to len(mySeq)
mySeq[::-2]  //returns every 2nd from whole container, start defaults to -1, end to 0
mySeq[::-1]  //reverse container
mySeq[1:3] = [1,3,4]

//////////////////////////////////////////////////////////////////////////////
//STRINGS
//////////////////////////////////////////////////////////////////////////////

str = Str() //empty string
str = "A string"
str = """A 'triple' string""" //can contain "" and '' anywhere easily
str = ("This is a string"
       "And another string")

\\ Backslash
\' Single quote
\" Double quote
\r Return
\t Tab
\s Space
\n Newline

str1 == str2 //case-sensitive????
str1 = "a"*5 //returns aaaaa
str1 *= 2    //multiples contents of st1 by 2

//===========================================================================
//STRING METHODS
//===========================================================================
//(b,e = begin,end and are optional)

s.rpartition("/")    //returns a Turple with three parts; before the /, the / and after the /
s.capitalize()       //Capitalizes first letter
s.center(n,c)        //Returns s centered in string of n padded with character c
s.ljust(n,c)         //Returns s left aligned in string of n padded with character c
s.rjust(n,c)         //Returns s right aligned in string of n padded with character c
s.count(s2,b,e)      //Returns number of times s2 is in s
s.endswith(s2,b,e)   //Returns true if s ends with s2
s.endswith(t,b,e)    //Returns true if s ends with any strings in turple t
s.startswith(s2,b,e) //Returns true if s starts with s2
s.startswith(t,b,e)  //Returns true if s starts with any strings in turple t
s.expandtabs(n)      //Returns s with each tab replaced by n spaces
s.find(s2,b,e)       //Returns leftmost position of s2 in s or -1 if not found
s.rfind(s2,b,e)      //Returns rightmost position of s2 in s or -1 if not found
s.isalnum()          //Returns True if len(s)>0 and every character in s is alphanumeric
s.isalpha()          //Returns True if len(s)>0 and every character in s is alphabetic
s.islower()          //Returns True if s >= one letter and they are all lowercase
s.isupper()          //Returns True if s >= one letter and they are all uppercase
s.isnumeric()        //Returns True if len(s)>0 and every character in s is a number
s.isspace()          //Returns True if len(s)>0 and every character in s is a whitespace character
s.lower()            //Returns lowercased s
s.upper()            //Returns uppercased s
s.replace(s2,s3,n)   //Returns s with every s2 replaced with s3 or maximum of n times of specified
s.splitlines(false)  //Returns s split on every newline, removing the newline if false or keeping if true
s.strip(chars)       //Returns s with leading/trailing whitespace (or chars if specified) removed
s.lstring(chars)     //Returns s with leading whitespace (or chars if specified) removed
s.rstring(chars)     //Returns s with trailing whitespace (or chars if specified) removed
s.swapcase()         //Returns s with swapped uppercase with lowercase characters
s.zfill(size)        //Returns s if shorter than size is padded with leading zeros to make it size

//PARTITIONING
//Returns tuple of three strings from s; before s2, s2 and after s2
//If s2 isn't in s, returns s and two empty strings
s.partition(s2)  //looks leftmost for s2
s.rpartition(s2) //looks rightmost for s2

//SPLITTING
//Returns list of strings splitting at most n times on string s2
//If n not given, splits as many times as possible
//If s2 not given, splits on whitespace
s.split(s2,n)  //searches leftmost for s2
s.rsplit(s2,n) //searches rightmost for s2

//JOINING
myJoiner = "-"
myList = ["one", "two", "three"] //can use list or turple
myJoiner.join(myList) //returns one-two-three using joiner

//===========================================================================
//STRING FORMATTING
//===========================================================================

str = Str(myInt)
str = Str(myFloat)
str = "hello %i" myInt     
str = "hello %f" % myFloat
str = "hello %c" % myCharacter     
str = "hello %s" % myString

//Outputs a c b 15
("a {0} b {1}").format("c",15)

//Outputs a b c
("{} {} {}").format("a","b","c")

//Outputs a c b 15
//{n} always comes first; user defined becomes {n+1}; ac would = 1
("a {ac} b {0}").format(15,ac="c")

//---------------------------------------------------------------------
//USING LISTS/TUPLES
//---------------------------------------------------------------------
//Outputs: a one b three
//myList (or tuple) is element 0 and [1] chooses which in list
myList = ["one", "two", "three"]
("a {0[0]} b {0[2]}").format(myList)

//---------------------------------------------------------------------
//USING DICTIONARIES
//---------------------------------------------------------------------
//Outputs: a 1 b two
myDict = dict(one=1, two="two")
("a {0[one]} b {0[two]}").format(myDict)

//has effect of one=myDict.one etc
//only keys in string are unpacked
("a {one} b {two}").format(**myDict) 

//---------------------------------------------------------------------
//USING MODULES
//---------------------------------------------------------------------
("pi is {0.pi} and cmath e is {1.e}").format(math,cmath)

//---------------------------------------------------------------------
//CONVERSION SPECIFIERS
//---------------------------------------------------------------------
//Outputs 12.3 Decimal('12.3')
//s = force string form, r = force representational form
("{0!s} {0!r}").format(decimal.Decimal("12.3") 

//---------------------------------------------------------------------
//FORMAT SPECIFIERS
//---------------------------------------------------------------------
//Order is   :[Fill][Align][Sign][Prefix][0Pad][Width][Precision][Type]
//FILL:      [any character] except }
//ALIGN:     [<] left, [>] right, [^] center [=] pad between sign/number
//SIGN:      [+] force sign, [-] sign only for negative numbers
//PREFIX:    [#] prefix ints with 0b,0o,0x
//0Pad:      [0] Pad numbers with 0
//WIDTH:     [any number] Minimum field width
//PRECISION: [.any number] Maximum field width for strings, number of deci places for floats

str = "a string"
("{0:10}").format(s) //Outputs: 'a string  '
("{0:>10}").format(s) //Outputs: '  a string' right aligned
("{0:-^10}").format(s) //Outputs '-a string-' centered with fill
("{0:.1}").format("23.13") //Outputs '23.1 where 1 is amount of decimal places
("{0:0=5}").format(-123) //Outputs '-00123' where 5 is minimum width
("{0:05}").format(123) //Outputs '00123' where 5 is minimum width
("{0:%}").format(0.1) //Outputs '10%' Multiplies number by 100 and adds %
("{0:f}").format("1234567890.1234567890.")  //Outputs number as is, without f does scientific notation
("{0:g}").format("1234567890.1234567890.")  //Outputs number as scientific notation (default)

//////////////////////////////////////////////////////////////////////////////
//LISTS
//////////////////////////////////////////////////////////////////////////////
//can be changed, can hold multiple data types

TestList = list()
TestList = []
TestList = ["One", "Two", "Three"]
del TestList[1] //delete member at index 1

L.append(x)     //Appends item x to the end of list L
L.count(x)      //Returns the number of times item x occurs in list L
L.extend(c)     //Appends all of c’s items to the end of list L
L += c          //Appends all of c’s items to the end of list L
L.index(x,s,e)  //Returns the index of the leftmost occurrence of s or throws ValueError
L.insert(i, x)  //Inserts item x into list L at index position int i
L.pop()         //Returns and removes the rightmost item of list L
L.pop(i)        //Returns and removes the item at index position int i in L
L.remove(x)     //Removes the leftmost occurrence of item x or raises a ValueError exception if not found
L.reverse()     //Reverses list L in-place
L.sort(MyFnc)   //Sorts list L in-place, uses comparsion function if given

//////////////////////////////////////////////////////////////////////////////
//TUPLES
//////////////////////////////////////////////////////////////////////////////
//cannot be changed, can hold multiple data types

TestTuple = ("One","Two","Three")
TestTuple.count("One") //number of times value is in
TestTuple.index("One") //get index of leftmost occurance of value or throw ValueError


//////////////////////////////////////////////////////////////////////////////
//DICTIONARIES
//////////////////////////////////////////////////////////////////////////////
//can be changed; uses string key to access; unordered
//keys can be strings or numbers

TestDict = dict(One=1,Two="two")
TestDict = {}
TestDict = {"One":8806336,
            "Two":6784346,
            "Three":1122345}

del TestDict["One"]
TestDict["One"] = 1234567

d.clear()          //Removes all items from dict d
d.copy()           //Returns a shallow copy of dict d Shallow
d.fromkeys(s, v)   //Returns a dict whose keys are s and whose values are v or none
d.get(k)           //Returns key k’s associated value, or None if k isn’t in dict d
d.get(k, v)        //Returns key k’s associated value, or v if k isn’t in dict d
d.pop(k)           //Returns and removes value at k, or throws KeyError if not in d
d.pop(k, v)        //Returns and removes value at k, or returns v if not in d
d.popitem()        //Returns and removes an arbitrary (key, value) pair or throws KeyError
d.setdefault(k, v) //Returns value at k or if no k, insert new item under k with None or v if specified
d.update(c)        //Combines dictionary,turple,list with dictionary d. Overwrites if value exists

//=========================================================================
//DICTIONARY VIEWS
//=========================================================================
//Read only iterable object that updates when dictionary updates
//Supports union, intersection, difference and symmetric difference
d.items()  //Returns a view of all the (key, value) pairs in dict d
d.keys()   //Returns a view of all the keys in dict d
d.values() //Returns a view of all the values in dict d

//=========================================================================
//DICTIONARY COMPREHENSION
//=========================================================================
d = {key: value for (key, value) in sequence}
d = {key: value for (key, value) in sequence if condition}
d = {apple: GetAppleType(apple) for apple in AppleList}
d = {apple: GetAppleType(apple) for apple in AppleList if apple != "red"}


//////////////////////////////////////////////////////////////////////////////
//SETS
//////////////////////////////////////////////////////////////////////////////
//Collection of hashable objects, no index positions 

set("four") | set("five") //UNION: 'fourive' 
set("four") & set("five") //INTERSECTION: 'f'
set("four") - set("five") //DIFFERENCE: 'our'
set("four") ^ set("five") //SYMMETRIC DIFFERENCE: 'ourive'

s.add(x)                  //Adds item x to set s if it is not already in s
s.clear()                 //Removes all the items from set s
s.copy()                  //Returns a shallow copy of set
s.difference(t)           //Returns s - t
s.difference_update(t)    //Returns s -= t
s.discard(x)              //Removes item x from set s if it is in s
s.intersection(t)         //Returns s & t
s.intersection_update(t)  //Returns s &= t
s.isdisjoint(t)           //Returns True if sets s and t have no items in
s.issubset(t)             //Returns True if set s is equal to or a subset of set t
s.issuperset(t)           //Returns True if set s is equal to or a superset of set t
s.pop()                   //Returns/removes a random item from set s; throws KeyError if empty
s.remove(x)               //Removes item x from set s; throws KeyError if x is not in s
s.symmetric_difference(t) //Returns s^t 
s.union(t)                //Returns s|t
s.update(t)               //Returns s|=t