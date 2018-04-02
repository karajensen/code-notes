/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FRAMEWORK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QtCore               Core non-graphical classes used by other modules
QtGUI                Base classes for graphical user interface (GUI) components. Includes OpenGL
QtMultimedia         Classes for audio, video, radio and camera functionality
QtMultimediaWidgets  Widget-based classes for implementing multimedia functionality
QtNetwork            Classes to make network programming easier and more portable
QtQML                Classes for QML and JavaScript languages
QtQuick              A declarative framework for building highly dynamic applications with custom UI
QtQuickControls      Reusable Qt Quick based UI controls to create classic desktop-style user interfaces
QtQuickDialogs       Types for creating and interacting with system dialogs from a Qt Quick application
QtQuickLayouts       Layouts are items that are used to arrange Qt Quick 2 based items in the UI
QtSQL                Classes for database integration using SQL
QtTest               Classes for unit testing Qt applications and libraries
QtWidgets            Classes to extend Qt GUI with C++ widgets
**************************************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTimer timer;
    timer.setInterval(10);
    QObject::connect(&timer, &QTimer::timeout, []() { /*tick*/ });
    timer.start();
    app.exec(); // Start the event loop
}

forever { break; }
qDebug() << "Message\n"; // Prints to stderr output
qobject_cast<MyQObject*>(qObj); // dynamic_cast without requiring RTTI
Q_ASSERT(expression);
Q_ASSERT_X(expression, "divide", "division by zero");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QPair<T1, T2>
auto pair = qMakePair(v1, v2);
pair.first;
pair.second;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QString
// Most also overload using a char, QRegularExpression, QRegExp
QString str("str")
str.append("str", n) // Adds n characters to the end of the string, returns QString& for chaining
str.append("str") / str.push_back("str") // Adds to the end of the string, returns QString& for chaining
str.arg(value) // Returns QString copy with %n replaced with value (eg. %1, %2...), printf with %n
str.at(n) // Returns QChar at index
str.back() // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.capacity() // Returns maximum number of characters that can be stored without forcing a reallocation
str.chop(n) // Removes n chars from end of the string, if n >= size, string becomes empty
str.chopped(n) // Removes n chars from end of the string and returns QString copy, n >= size is undefined
str.clear() // Makes string empty
str.compare("str", Qt::CaseInsensitive) // Returns 0 if they match 
str.contains("a", Qt::CaseInsensitive) // Returns true if contains substring 'a'
str.count("a", Qt::CaseInsensitive) // Returns count of substring, will count overlaps
str.endsWith("a", Qt::CaseInsensitive) // Returns true if ends with 'a'
str.fill('c', n) // Resizes string to n and fills with character, without n will fill to current size
str.front() // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.indexOf("a", i) // Searches for 'a' from index i, returns index, or -1 if not found
str.insert(n, "a") // Inserts 'a' at index n, returns QString&, auto resizes if n >= size
str.empty() // Returns true if has no characters
str.isNull() // Returns true if null (default constructor)
str.isRightToLeft() // Returns true if string is to be read right to left
str.lastIndexOf("a", i) // Searches for 'a' backwards from index i, returns index, or -1 if not found
str.left(n) // Returns QString with only n characters starting from left
str.leftJustified(n, 'c') // Returns QString of n width, any extra chars padded with fill 'c'
str.leftRef(n) // Returns QStringRef of n left most characters
str.length() / str.size() // Amount of characters
str.mid(i, n) // Returns QString starting at index i for n optional characters
str.midRef(i, n) // Returns QStringRef starting at index i for n optional characters    
str.prepend("a") / str.push_front("a") // Adds to start of str and returns QString&
str.remove(i, n) // Removes n characters from index i, returns QString&, if i+n >= size will truncate
str.remove("a", Qt::CaseInsensitive) // Removes every occurance of "a" and returns QString&
str.repeated(n) // Returns QString repeated n times
str.replace(i, n, "a") // Replaces from index i over n characters with "a" and returns QString& 
str.replace("a", "b", Qt::CaseInsensitive) // Replaces all instances of "a" with "b"
str.reserve(n) // Reserve capacity for n characters
str.resize(n) // Sets size of string to n characters, new characters are uninitialized
str.resize(n, 'c') // Sets size of string to n characters, new characters use 'c'
str.right(n) // Returns QString with only n characters starting from right
str.rightJustified(n, 'c') // Returns QString of n width from end, any extra chars padded with fill 'c'
str.rightRef(n) // Returns QStringRef of n right most characters
str.split(" ") // Returns QStringList of string split by spaces
str.toUtf8().constData() // Convert to const char*
str.begin() / str.end() // iterator or const_iterator
str.rBegin() / str.rEnd() // reverse_iterator or const_reverse_iterator
str.cbegin() / str.cend() // const_iterator
str.constBegin() / str.constEnd() // const_iterator
str.crbegin() / str.crEnd() // const_reverse_iterator    
QString::asprintf("%i", n) // QString version of printf, uses same modifiers
QString::compare(str1, str2, Qt::CaseInsensitive) // Returns 0 if they match
QString::number(integer) // Converts integer to QString
QString::number(double, 'g', precision) // Converts floating point number to QString
 
// QTextStream
QTextStream(&str) << "str" << value; // QString streamstream

// QStringList
// Inherits from QList<QString>
// Most also overload using a char, QRegularExpression, QRegExp
QStringList<T> lst = { value }
QStringList<T> lst("str")
lst.join("delim") // Returns a combined string seperated by delim
lst.split("delim") // Returns 
lst.contains("str", Qt::CaseInsensitive) // True if list contains string
lst.filter(regex) // Returns QStringList filtered by regex
lst.indexOf(regex, i) // Returns index of first match from regex starting from optional i, else -1
lst.lastIndexOf(regex, i) // Returns index of last match from regex backwards from optional i, else -1
lst.removeDuplicates() // Removes all duplicate strings, doesn't require sorting
lst.replaceInStrings("str1", "str2", Qt::CaseInsensitive) // Replace 'str1' with 'str2' in all strings
lst.sort(Qt::CaseInsensitive) // Sort all strings using std::sort

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT CONTAINERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Type T must provide default constructor, copy constructor, assignment operator, else use T*
• Iterators can become invalid after insertion/removal, due to changing internals and implicit sharing (COW)
• Using mutable operator[] will COW detach, except for QByteArray which uses QByteRef
• Using mutable iterators will COW detach, use constBegin/constEnd for read-only
• Can disable implicit conversion of begin() to constBegin() using QT_STRICT_ITERATORS

QList<T>
• Pre-allocates array of void*, with extra space before/after, fast index access, insertions and removals
• void* becomes T if sizeof(T) <= sizeof(void*) and T is Q_PRIMITIVE_TYPE or Q_MOVABLE_TYPE
  else void* becomes T*, copy-constructed into the heap using new
• Wastes memory if sizeof(T) < sizeof(void*) or if allocated on heap due to extra T*

QVector<T>
• Continuous memory allocation, reallocates whole block when resizing
• Fast index access and add/remove from back, slow insert and add/remove from front

QVarLengthArray<T, n>
• Stack allocated array, n must be constant, if resizing will move to heap
• No implicit sharing, no auto-init for basic types

QLinkedList<T>
• Uses iterators to access members, segmented allocations
• Better performance than QList when inserting in the middle of a huge list

QMap<Key, T>
• Dictionary, auto stores its data in Key order
• Key must provide operator<()

QHash<Key, T>
• Provides average faster lookups than QMap, no auto sorting, has auto resizing
• Key must provide operator==() and a global uint qHash(const K &key) function
• Uses hash key qHash(key) % QHash::capacity() (number of buckets)

QSet<T>
• Underlying type based on QHash
• Provides average faster lookups than QMap, no auto sorting

QCache<Key, T>
• Auto takes ownership of items inserted
• Uses score to determine what to keep/remove from cache
• If full, least accessed item is removed

QContiguousCache<Key, T>
• Items must be contiguous (adjacent)
• Consumes less memory and processor cycles than QCache
• Uses capacity to determine what the keep/remove from cache
• If full, item at opposite end of the cache from prepend/append is removed

-------------------------------------------------------------------------------------------------
CONTAINER      ACCESS     INSERT     PREPEND   APPEND   EQUIVALENT
-------------------------------------------------------------------------------------------------
QLinkedList    O(n)       O(1)       O(1)      O(1)     std::list   
QList          O(1)       O(n)       O(1)      O(1)     -
QVector        O(1)       O(n)       O(n)      O(1)     std::vector  
QMap           O(logn)    O(logn)    -         -        std::map 
QMultiMap      O(logn)    O(logn)    -         -        std::multimap
QHash          O(1)       O(n)       -         -        std::unordered_map       
QMultiHash                                              std::unordered_multimap    
QSet           O(1)       O(n)       -         -        std::unordered_set
-------------------------------------------------------------------------------------------------
CONTAINER         JAVA-STYLE READ-ONLY   JAVA-STYLE MUTABLE            STL-STYLE ITERATORS
-------------------------------------------------------------------------------------------------
QList             QListIterator          QMutableListIterator          QList::iterator
QQueue            QListIterator          QMutableListIterator          QQueue::iterator     
QLinkedList       QLinkedListIterator    QMutableLinkedListIterator    QLinkedList::iterator   
QVector           QVectorIterator        QMutableVectorIterator        QVector::iterator    
QStack            QVectorIterator        QMutableVectorIterator        QStack::iterator     
QSet              QSetIterator           QMutableSetIterator           QSet::iterator   
QMap              QMapIterator           QMutableMapIterator           QMap::iterator   
QMultiMap         QMapIterator           QMutableMapIterator           QMultiMap::iterator   
QHash             QHashIterator          QMutableHashIterator          QHash::iterator    
QMultiHash        QHashIterator          QMutableHashIterator          QMultiHash::iterator 
**************************************************************************************************************/

// QList<T>
QList<T> lst = { value }
lst[index]; // Returns const T& or T&, asserts out-of-range
lst << value; // Allows streaming into container
lst.append(value)  / lst.push_back(value) // Appends to end of list
lst.prepend(value) / lst.push_back(value) // Prepends to start of list
lst.removeLast()   / lst.pop_back() // Remove item at end
lst.removeFirst()  / lst.pop_front() // Remove item at start
lst.first() / lst.front() // Returns const T& or T& for first item
lst.last()  / lst.back() // Returns const T& or T& for last item
lst.constFirst() // Returns const T& for first item
lst.constLast() // Returns const T& for last item
lst.at(i) // Returns const T&, will not COW detach, asserts out-of-range
lst.clear() // Clears the container
lst.contains(value) // Returns true if item is in list
lst.count(value) // Returns number of times item is in list
lst.count() / lst.length() / lst.size() // Returns number of items in list
lst.empty() / lst.isEmpty() // Whether the list is empty
lst.endsWith(value) // Whether list is not empty and last item is value
lst.startsWith(value) // Whether list is not empty and first item is value
lst.erase(itr) // Removes item at iterator, returns itr to next item
lst.erase(itr1, itr2) // Removes range, returns itr to the same item that itr2 used to be at
lst.indexOf(value, i) // Returns index of first value, starting from optional i, or -1 if not found
lst.insert(i, value) // Insert at index, i <= 0 uses preprend, i >= size uses append
lst.insert(itr, value) // Inserts value before itr, returns iterator at new item, invalidates itr
lst.lastIndexOf(value, i) // Returns index of last value, backwards from optional i, or -1 if not found
lst.mid(i, n) // Returns QList<T> from index i over n items, use -1 for all to the end
lst.move(i1, i2) // Moves item at i1 to i2, shifts other elements as needed
lst.removeAll(value) // Remove all items with value, returns amount removed
lst.removeAt(i) // Remove at index i
lst.removeOne(value) // Removes first occurance of value, returns true if removed
lst.replace(i, value) // Replaces at index i with the value
lst.reserve(n) // Reserve capacity for n items, only reserves space for the void*
lst.swap(i1, i1) // Swap values at i1 and i2    
lst.takeAt(i) // Removes item at index i and returns T, removeAt more effecient if not using T
lst.takeFirst() // Removes first item and returns T, removeFirst more effecient if not using T
lst.takeLast() // Removes last item and returns T, removeLast more effecient if not using T
lst.toSet() // Returns QSet<T> from list
lst.toStdList() // Returns std::list<T> from list
lst.toVector() // Returns QVector<T> from list
lst.value(i) // Returns T at index i, if i is out of bounds, returns default constructed T
lst.value(i, default) // Returns T at index i, if i is out of bounds, returns default
QList<T>::fromSet(set); // Returns QList<T> converted from a QSet<T>
QList<T>::fromStdList(lst); // Returns QList<T> converted from a std::list<T>
QList<T>::fromVector(vec); // Returns QList<T> converted from a QVector<T>
    
// QQueue<T>
// Inherits QList<T>
QQueue<T> queue = { value }
queue.dequeue() // Removes from front of queue and returns T
queue.enqueue(value) // Adds to back of queue
queue.head() // Returns T& or const T& from front of queue

// QVector<T>
QVector<T> vec = { value }
QVector<T> vec(n) // Initialise all with default constructor
QVector<T> vec(value) // Initialise all with value
vec[index]; // Returns const T& or T&, asserts out-of-range
vec.append(value)  / vec.push_back(value) // Appends to end of vector
vec.prepend(value) / vec.push_back(value) // Prepends to start of vector
vec.removeLast()   / vec.pop_back() // Remove item at end
vec.removeFirst()  / vec.pop_front() // Remove item at start
vec.first() / vec.front() // Returns const T& or T& for first item
vec.last()  / vec.back() // Returns const T& or T& for last item
vec.constFirst() // Returns const T& for first item
vec.constLast() // Returns const T& for last item
vec.at(i) // Returns const T&, will not COW detach, asserts out-of-range
vec.clear() // Clears the container
vec.capacity() // Returns maximum items before forcing a reallocation
vec.constData() // Returns const T* of the first item
vec.contains(value) // Returns true if item is in vector
vec.count(value) // Returns number of times item is in vector
vec.count() / vec.length() / vec.size() // Returns number of items in vector
vec.data() // Returns T* or const T* of the first item
vec.empty() / vec.isEmpty() // Whether the vector is empty
vec.endsWith(value) // Whether vector is not empty and last item is value
vec.startsWith(value) // Whether vector is not empty and first item is value
vec.erase(itr) // Removes item at iterator, returns itr to next item
vec.erase(itr1, itr2) // Removes range, returns itr to the same item that itr2 used to be at
vec.fill(value, n) // Resizes to n, fills whole vector with value
vec.indexOf(value, i) // Returns index of first value, starting from optional i, or -1 if not found
vec.insert(i, value) // Insert at index, i <= 0 uses preprend, i >= size uses append
vec.insert(itr, value) // Inserts value before itr, returns iterator at new item, invalidates itr
vec.lastIndexOf(value, i) // Returns index of last value, backwards from optional i, or -1 if not found
vec.mid(i, n) // Returns QVector<T> from index i over n items, use -1 for all to the end
vec.move(i1, i2) // Moves item at i1 to i2, shifts other elements as needed
vec.remove(i, n) // Remove n items from index i
vec.removeAll(value) // Remove all items with value, returns amount removed
vec.removeAt(i) / vec.remove(i) // Remove at index i
vec.removeOne(value) // Removes first occurance of value, returns true if removed
vec.replace(i, value) // Replaces at index i with the value
vec.reserve(n) // Reserve capacity for n items
vec.resize(n) // Resizes vector to n items
vec.shrink_to_fit() / vec.squeeze() // Removes unused capacity
vec.swap(i1, i1) // Swap values at i1 and i2    
vec.takeAt(i) // Removes item at index i and returns T, removeAt more effecient if not using T
vec.takeFirst() // Removes first item and returns T, removeFirst more effecient if not using T
vec.takeLast() // Removes last item and returns T, removeLast more effecient if not using T
vec.toStdVector() // Returns std::vector<T> from vector
vec.toList() // Returns QList<T> from vector
vec.value(i) // Returns T at index i, if i is out of bounds, returns default constructed T
vec.value(i, default) // Returns T at index i, if i is out of bounds, returns default
QVector<T>::fromStdVector(vec); // Returns QVector<T> converted from a std::vector<T>
QVector<T>::fromList(lst); // Returns QVector<T> converted from a QList<T>

// QStack<T>
// Inherits QVector<T>
QStack<T> stack = { value }
stack.pop() // Removes from top and returns T
stack.push(value) // Adds to top of stack
stack.top() // Returns T& or const T& from top of stack
    
// QVarLengthArray<T, n>
QVarLengthArray<T, n> arr = { value }
QVarLengthArray<T, n> arr(n2) // n capacity, n2 items
arr[index]; // Returns const T& or T&, asserts out-of-range
arr.append(value)  / arr.push_back(value) // Appends to end of array
arr.prepend(value) / arr.push_back(value) // Prepends to start of array
arr.removeLast()   / arr.pop_back() // Remove item at end
arr.removeFirst()  / arr.pop_front() // Remove item at start
arr.first() / arr.front() // Returns const T& or T& for first item
arr.last()  / arr.back() // Returns const T& or T& for last item
arr.constFirst() // Returns const T& for first item
arr.constLast() // Returns const T& for last item
arr.at(i) // Returns const T&, will not COW detach, asserts out-of-range
arr.clear() // Clears the container
arr.capacity() // Returns maximum items before forcing a reallocation
arr.constData() // Returns const T* of the first item
arr.contains(value) // Returns true if item is in array
arr.count() / arr.length() / arr.size() // Returns number of items in array
arr.data() // Returns T* or const T* of the first item
arr.empty() / arr.isEmpty() // Whether the array is empty
arr.erase(itr) // Removes item at iterator, returns itr to next item
arr.erase(itr1, itr2) // Removes range, returns itr to the same item that itr2 used to be at
arr.indexOf(value, i) // Returns index of first value, starting from optional i, or -1 if not found
arr.insert(i, value) // Insert at index, i <= 0 uses preprend, i >= size uses append
arr.insert(itr, value) // Inserts value before itr, returns iterator at new item, invalidates itr
arr.lastIndexOf(value, i) // Returns index of last value, backwards from optional i, or -1 if not found
arr.remove(i, n) // Remove n items from index i
arr.remove(i) // Remove at index i
arr.replace(i, value) // Replaces at index i with the value
arr.reserve(n) // Reserve capacity for n items
arr.resize(n) // Resizes vector to n items
arr.shrink_to_fit() / arr.squeeze() // Removes unused capacity
arr.value(i) // Returns T at index i, if i is out of bounds, returns default constructed T
arr.value(i, default) // Returns T at index i, if i is out of bounds, returns default

// QLinkedList<T>
QLinkedList<T> lst = { value }
lst << value; // Allows streaming into container
lst.append(value)  / lst.push_back(value) // Appends to end of list
lst.prepend(value) / lst.push_back(value) // Prepends to start of list
lst.removeLast()   / lst.pop_back() // Remove item at end
lst.removeFirst()  / lst.pop_front() // Remove item at start
lst.first() / lst.front() // Returns const T& or T& for first item
lst.last()  / lst.back() // Returns const T& or T& for last item
lst.constFirst() // Returns const T& for first item
lst.constLast() // Returns const T& for last item
lst.clear() // Clears the container
lst.contains(value) // Returns true if item is in list
lst.count(value) // Returns number of times item is in list
lst.count() / lst.length() / lst.size() // Returns number of items in list
lst.empty() / lst.isEmpty() // Whether the list is empty
lst.endsWith(value) // Whether list is not empty and last item is value
lst.startsWith(value) // Whether list is not empty and first item is value
lst.erase(itr) // Removes item at iterator, returns itr to next item
lst.erase(itr1, itr2) // Removes range, returns itr to the same item that itr2 used to be at
lst.insert(itr, value) // Inserts value before itr, returns iterator at new item, invalidates itr
lst.lastIndexOf(value, i) // Returns index of last value, starting from optional i, or -1 if not found
lst.removeAll(value) // Remove all items with value, returns amount removed
lst.removeOne(value) // Removes first occurance of value, returns true if removed
lst.takeFirst() // Removes first item and returns T, removeFirst more effecient if not using T
lst.takeLast() // Removes last item and returns T, removeLast more effecient if not using T
lst.toStdList() // Returns std::list<T> from list
QLinkedList<T>::fromStdList(lst); // Returns QList<T> converted from a std::list<T>

// QMap<Key, T>
// Can hold multiple values per key- will work on most recent added key value unless specified
QMap<Key, T> map = { std::make_pair(key, value) }
map[key] // Inserts into map if key doesn't exist for non-const maps
map.clear() // Clears the container
map.constFind(key) // Returns const_iterator or constEnd() if not found
map.contains(key) // Return true if map contains key
map.count(key) // number of items associated with key
map.count() / map.size() // number of items in map
map.empty() / map.isEmpty() // Whether map has items
map.equal_range(key) // Returns QPair<itr, itr> for range of values [first, second) in key, has const overload
map.erase(itr) // Removes item, returns itr for next item
map.find(key) // Returns itr or end(), has const overload
map.first() // Returns T& or const T& of the value to the smallest key in map
map.firstKey() // Returns const Key& to the smallest key in map
map.insert(key, value) // Inserts into map, returns itr to new item, for multi overrides most recent value
map.insertMulti(key, value) // Inserts into map, returns itr to new item, for multi appends to key values
map.key(value, default) // Returns first key using value or default if not found, slow
map.keys() // Returns QList<Key> of all keys, for multi has multiple same key entries, order same as values()
map.last() // Returns T& or const T& of the value to the largest key in map
map.lastKey() // Returns const Key& to the largest key in map    
map.lowerBound(key) // Returns itr/const itr to first item with key or nearest item with greater key
map.remove(key) // Removes all items with key, return number of items removed
map.take(key) // Removes item with key and returns T or default constructed value
map.toStdMap() // Returns std::map<Key, T>
map.uniqueKeys() // Returns all unique keys in ascending order
map.unite(map2) // Adds map2 to map, if sharing keys will append values to key
map.upperBound(key) // Returns itr/const itr to one after first item with key or nearest item with greater key
map.value(key, default) // Returns value of key or optional default value if doesn't exist
map.values() // Returns QList<T> in same order/count as keys()
map.values(key) // Returns QList<T> of all values under key
    
// QMultiMap<Key, T>
// Inherits QMap<Key, T>
map.constFind(key, value) // Returns const_iterator or constEnd() if not found
map.contains(key, value) // Return true if map contains key/value
map.count(key, value) // number of items associated with key/value
map.find(key, value) // Returns itr or end(), has const overload
map.insert(key, value) // Inserts into map, returns itr to new item, appends to key values
map.remove(key, value) // Removes all items with key/value, return number of items removed
map.replace(key, value) // Inserts into map, returns itr to new item, overrides most recent value
    
// QHash<Key, T>
// Can hold multiple values per key- will work on most recent added key value unless specified
QHash<Key, T> hash = { std::make_pair(key, value) }
hash[key] // Inserts into hash if key doesn't exist for non-const hashs
hash.capacity() // Returns maximum items before forcing a reallocation 
hash.clear() // Clears the container
hash.constFind(key) // Returns const_iterator or constEnd() if not found
hash.contains(key) // Return true if hash contains key
hash.count(key) // number of items associated with key
hash.count() / hash.size() // number of items in hash
hash.empty() / hash.isEmpty() // Whether hash has items
hash.equal_range(key) // Returns QPair<itr, itr> for range of values [first, second) in key, has const overload
hash.erase(itr) // Removes item, returns itr for next item
hash.find(key) // Returns itr or end(), has const overload
hash.insert(key, value) // Inserts into hash, returns itr to new item, for multi overrides most recent value
hash.insertMulti(key, value) // Inserts into hash, returns itr to new item, for multi appends to key values
hash.key(value, default) // Returns first key using value or default if not found, slow
hash.keys() // Returns QList<Key> of all keys, for multi has multiple same key entries, order same as values()
hash.remove(key) // Removes all items with key, return number of items removed
hash.reserve() // Reserve capacity for n items
hash.squeeze() // Removes unused capacity
hash.take(key) // Removes item with key and returns T or default constructed value
hash.uniqueKeys() // Returns all unique keys in ascending order
hash.unite(hash2) // Adds hash2 to hash, if sharing keys will append values to key
hash.value(key, default) // Returns value of key or optional default value if doesn't exist
hash.values() // Returns QList<T> in same order/count as keys()
hash.values(key) // Returns QList<T> of all values under key

// QMultiHash<Key, T>
// Inherits QHash<Key, T>
hash.constFind(key, value) // Returns const_iterator or constEnd() if not found
hash.contains(key, value) // Return true if map contains key/value
hash.count(key, value) // number of items associated with key/value
hash.find(key, value) // Returns itr or end(), has const overload
hash.insert(key, value) // Inserts into hash, returns itr to new item, appends to key values
hash.remove(key, value) // Removes all items with key/value, return number of items removed
hash.replace(key, value) // Inserts into hash, returns itr to new item, overrides most recent value    

// QSet<T>
QSet<T> set = { value }
set[value] // Inserts into set if value doesn't exist for non-const sets
set.capacity() // Returns maximum items before forcing a reallocation 
set.clear() // Clears the container
set.constFind(value) // Returns const_iterator or constEnd() if not found
set.contains(value) // Return true if set contains value
set.count() / set.size() // number of items in set
set.empty() / set.isEmpty() // Whether set has items
set.erase(itr) // Removes item, returns itr for next item
set.find(value) // Returns itr or end(), has const overload
set.insert(value) // Inserts into set, returns itr to new item
set.remove(value) // Removes item with value, return if item removed
set.reserve() // Reserve capacity for n items
set.subtract(set2) // Removes all items from set that are contained in set2
set.squeeze() // Removes unused capacity
set.unite(set2) // Adds set2 to set, if sharing keys will append values to key
set.values() / set.toList() // Returns QList<T> with undefined order

// QCache<Key, T>
QCache<Key, T> cache(n) // Optional max cost
cache[key] // Returns T*, or 0 if doesn't exist
cache.clear() // Clears the container
cache.contains(key) // Return true if cache contains key
cache.count() / cache.size() // number of items in cache
cache.insert(key, value, cost) // adds/overwrites item with key at cost, returns true if inserted
cache.isEmpty() // Returns true if cache has no objects
cache.keys() // Returns QList<Key> of keys
cache.maxCost() // Returns max cost which determines how much cache holds before deleting
cache.object(key) // Returns T*
cache.remove(key) // Returns true if object is in cache and was deleted
cache.setMaxCost(n) // Sets the max cost
cache.take(key) // Removes T* from the cache without deleting it and returns T*
cache.totalCost() // Returns combined cost of all objects in cache, can be > maxCost with COW
    
// QContiguousCache<Key, T>
QContiguousCache<T> cache(n) // Capacity must be set as has default of 0
cache[i] // Returns T& or const T&, will auto add value to non-const cache if doesn't exist    
cache.append(value) // Inserts value at end of cache, will remove items from front if full
cache.areIndexesValid() // True if no indexes are > INT_MAX or < 0
cache.at(i) // Returns const T& at index
cache.available() // Returns number of items that can be added before cache is full
cache.capacity() // Returns number of items the cache can hold
cache.clear() // Remove all items from cache
cache.containsIndex(i) // Return true if index is valid
cache.count() / cache.size() // Returns number of items in cache
cache.first() // Returns T& or const T& from front of cache
cache.firstIndex() // Returns first valid index in the cache, will be invalid if empty
cache.insert(i, value) // Inserts into cache, replaces if already exist, invalid i will clear cache first
cache.isEmpty() // Returns true if nothing in cache
cache.isFull() // Returns true if max capacity has been reached
cache.last() // Returns T& or const T& from back of cache
cache.lastIndex() // Returns last valid index in the cache, will be invalid if empty
cache.normalizeIndexes() // Ensures all indexes in cache are valid, does not reorder values
cache.prepend(value) // Inserts value at start of cache, will remove items from back if full
cache.removeFirst() // Removes first item from cache, cache must not be empty
cache.removeLast() // Removes last item from cache, cache must not be empty
cache.setCapacity(n) // Set amount of items cache can hold before considered full
cache.takeFirst() // Removes first item from cache and returns T, cache must not be empty
cache.takeLast() // Removes last item from cache and returns T, cache must not be empty
    
// QBitArray
QBitArray arr; // Null bit array
QBitArray arr(n, isOn) // Number of bits, if n == 0, considered empty bit array, optional bool isOn
arr |= arr2 // OR, result has the length of the longest of the two
arr ^= arr2 // XOR, result has the length of the longest of the two
arr &= arr2 // AND, result has the length of the longest of the two
~arr // Returns QBitArray copy inverted
arr[i] // Returns QBitRef (non-const) or bool (const), 0-based index
arr.at(i) // Returns bool, 0-based index
arr.clear() // Makes array empty
arr.clearBit(i) // Sets bit to false
arr.count() / arr.size() // Number of bits
arr.count(isOn) // if isOn == true, count of bits on, else count of bits off
arr.fill(isOn, n) // Optional n resizes array, then sets all bits to isOn
arr.fill(isOn, i1, i2) // Fills array from [i1, i2)
arr.isEmpty() // Returns true if size of array is 0
arr.isNull() // Returns true if considered null (default constructor initialised)
arr.resize() // Changes size of array, any new bits auto init to false
arr.setBit(i, isOn) // Sets bit at index i
arr.testBit(i) // Returns true if bit at index i is on
arr.toggleBit(i) // Toggles bit at index i, returning previous value of bit
arr.truncate(i) // Truncates array to index i

// CONTAINER FOREACH
// Readonly loop, Auto takes copy of container at start of loop
// Modifying container during loop won't affect it due to implicit sharing
// Q_FOREACH if QT_NO_KETYWORDS is defined
foreach (const auto& value, container) {}
foreach (const auto& value, map) {}
foreach (const auto& key, map.keys()) {}
foreach (const auto& key, multimap.uniqueKeys()) { foreach (const auto& value, multimap.values(key)) {} }

// STL-STYLED ITERATORS
// Point to actual values, support reverse_iterator, const_iterator and iterator maths
// Getting a mutable iterator from a container will auto COW detach
begin()              end()              // iterator or const_iterator
rBegin()             rEnd()             // reverse_iterator or const_reverse_iterator
cbegin()             cend()             // const_iterator
constBegin()         constEnd()         // const_iterator
crbegin()            crEnd()            // const_reverse_iterator
keyBegin()           keyEnd()           // key_iterator
keyValueBegin()      keyValueEnd()      // key_value_iterator or const_key_value_iterator
constKeyValueBegin() constKeyValueEnd() // const_key_value_iterator
*itr                 // Return value
++i / --i            // Increment/decrement
itr.key()            // Key-based only, returns const Key&
    
// JAVA-STYLED ITERATORS
// Point to position between values
QListIterator<T> itr(lst);
itr.toFront()              // Sets iterator as begin
itr.toBack()               // Sets iterator as end
itr.hasNext()              // Returns true if the iterator isn't at the back of the list
itr.next()                 // Returns the next item and advances the iterator by one position
itr.peekNext()             // Returns the next item without moving the iterator
itr.hasPrevious()          // Returns true if the iterator isn't at the front of the list
itr.previous()             // Returns the previous item and moves the iterator back by one position
itr.peekPrevious()         // Returns the previous item without moving the iterator
itr.value()                // Mutable or key-based only, Returns T& or const T&
itr.setValue(value)        // Mutable only, Takes in const T&
itr.insert(value)          // Mutable, non-key based only, Takes in const T&, inserts one after itr
itr.findNext(value)        // Mutable or key-based only, from itr, searches forward for value, returns if found
itr.findPrevious(value)    // Mutable or key-based only, from itr, searches backwards for value, returns if found
itr.remove()               // Mutable only, Removes the value, does not invalidate itr
itr.key()                  // Key-based only, Returns const Key&
  
// ITERATOR IMPLICIT SHARING PITFALL
// Can be dangerous for iterators when container detaches from shared block:
QVector<int> a, b;
QVector<int>::iterator i = a.begin();
b = a;    // Make both implicity share
*i = 10;  // Iterator points to share block, will modify both a and b
a[0] = 5; // Detach a by modifying only it, i still points to b though  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT SMART POINTERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// QSharedDataPointer
// Requires T to be derived from QSharedData
// Thread-safe reference counting pointer to an implicitly shared object
// Calling non-const class methods auto detaches ptr from shared block
QSharedDataPointer<T> ptr(new T());
QSharedDataPointer<T> ptr2(ptr); // Implicity shares data with ptr
ptr.constData();         // Returns const T*
ptr.data();              // Returns T* or const T*
ptr.detach();            // Detaches object from shared data

// QExplicitlySharedDataPointer
// Requires T to be derived from QSharedData
// Thread-safe reference counting pointer to an implicitly shared object
// Calling non-const class methods DOES NOT auto detach ptr from shared block
QExplicitlySharedDataPointer<T> ptr(new T());
QExplicitlySharedDataPointer<T> ptr2(ptr); // Implicity shares data with ptr
ptr.constData();         // Returns const T*
ptr.data();              // Returns T* or const T*
ptr.detach();            // Detaches object from shared data

// QSharedPointer  
// Thread-safe reference counting shared pointer with control block
QSharedPointer<T> ptr(new T());
QSharedPointer<T> ptr(new T(), [](T* data){}); // With custom deleter
auto ptr = QSharedPointer<T>::create(); // Allocates control block and memory together
ptr.clear();             // Clears pointer and decrements ref count
ptr.constCast();         // Returns QSharedPointer<T> with T stripped of const
ptr.objectCast<T2>();    // Returns QSharedPointer<T2> by doing a qobject_cast
ptr.dynamicCast<T2>();   // Returns QSharedPointer<T2>
ptr.staticCast<T2>();    // Returns QSharedPointer<T2>
ptr.toWeakRef();         // Returns QWeakPointer<T>
ptr.isNull();            // Returns if null
ptr.data();              // Returns T*
ptr.reset();
ptr.reset(new T());

// QWeakPointer
// Holds a weak reference to a QSharedPointer
QWeakPointer<T> ptr(mySharedPtr->toWeakRef());
ptr.clear();             // Clears pointer
ptr.data();              // Returns T*, does not cast to QSharedPointer<T> or check if valid
ptr.isNull();            // Returns if null
ptr.lock();              // Returns QSharedPointer<T>, same as toStrongRef
ptr.toStrongRef();       // Returns QSharedPointer<T>, same as lock

// QScopedPointer
QScopedPointer<T> ptr(new T());
ptr.take();             // Returns T* and sets pointer to null
ptr.data();             // Returns T*
ptr.isNull();           // Returns if null
ptr.reset();
ptr.reset(new T());

// QScopedArrayPointer
QScopedArrayPointer<T> ptr(new T[n]);
ptr[index];             // Returns T& at index
ptr.take();             // Returns T* and sets pointer to null
ptr.data();             // Returns T*
ptr.isNull();           // Returns if null
ptr.reset();
ptr.reset(new T[n]);

// QPointer
// Same as QScopedPointer, kept for legacy support
QPointer<T> ptr(new T());
ptr.clear();             // Clears pointer and decrements ref count
ptr.isNull();            // Returns if null
ptr.data();              // Returns T*

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT TYPES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QTypeInfo Default
QTypeInfo<T>::isSpecialized = std::is_enum<T>::value
QTypeInfo<T>::isPointer = false
QTypeInfo<T>::isIntegral = std::is_integral<T>::value
QTypeInfo<T>::isComplex = !isIntegral && !std::is_enum<T>::value
QTypeInfo<T>::isStatic = true
QTypeInfo<T>::isRelocatable = std::is_enum<T>::value
QTypeInfo<T>::isLarge = sizeof(T) > sizeof(void*)
    
// QTypeInfo Pointer specialisation
QTypeInfo<T*>::isSpecialized = true
QTypeInfo<T*>::isPointer = true
QTypeInfo<T*>::isIntegral = false
QTypeInfo<T*>::isComplex = false
QTypeInfo<T*>::isStatic = false
QTypeInfo<T*>::isRelocatable = true
QTypeInfo<T*>::isLarge = false
    
// QTypeInfo void specialisation
QTypeInfo<void>::isSpecialized = true
QTypeInfo<void>::isPointer = false
QTypeInfo<void>::isIntegral = false
QTypeInfo<void>::isComplex = false
QTypeInfo<void>::isStatic = false
QTypeInfo<void>::isRelocatable = false
QTypeInfo<void>::isLarge = false
    
// QTypeInfo Qt Container specialisation
QTypeInfo<T>::isSpecialized = true
QTypeInfo<T>::isComplex = (((FLAGS) & Q_PRIMITIVE_TYPE) == 0)
QTypeInfo<T>::isStatic = (((FLAGS) & (Q_MOVABLE_TYPE | Q_PRIMITIVE_TYPE)) == 0)
QTypeInfo<T>::isRelocatable = !isStatic || ((FLAGS) & Q_RELOCATABLE_TYPE)
QTypeInfo<T>::isLarge = sizeof(T)  >sizeof(void*)
QTypeInfo<T>::isPointer = false
QTypeInfo<T>::isIntegral = std::is_integral<T>::value

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QHBoxLayout: lays out widgets horizontally from left to right
QHBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout: lays out widgets vertically from top to bottom
QVBoxLayout layout;
layout.addWidget(spinBox); // Add a widget to the layout, automatically parents and resizes

// QGridLayout: lays out widgets in a grid.
QGridLayout layout;
layout.addWidget(spinBox, r, c); // Add a widget to the layout, automatically parents and resizes

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QWidget
QWidget widget; // Root widget used as a window
widget.setWindowTitle("Title");
widget.show();
widget.setLayout(layout); // Add a layout to the window, automatically parents

// QLabel
QLabel lbl("Message"); // Allows use of html tags to customise text

// QPushButton
QPushButton btn("Text");
QObject::connect(button, SIGNAL(clicked()), &app, SLOT(myFn()));  // Connect to button's click event

// QSpinBox
QSpinBox spinbox;
spinbox.setRange(min, max);
spinBox.setValue(value);
QObject::connect(spinBox, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

// QSlider 
QSlider slider(Qt::Horizontal);
slider.setRange(min, max);
slider.setValue(value);
QObject::connect(slider, SIGNAL(valueChanged(int)), &app, SLOT(myFn(int)));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
QOBJECTS:
• Base class of all Qt objects, organised in an object tree
• Doesn't have a copy constructor or assignment operator
• Meta Object Compilier (moc) uses Q_OBJECT macro to generate extra data/features to use in framework:
    - Ability to use qobject_cast, signals and slots
    - QObject::metaObject returns the associated meta-object for the class
    - QMetaObject::className returns the class name as a string (without using RTTI)
    - QObject::inherits returns whether an instance of another QObject class
    - QObject::setProperty / QObject::property dynamically set and get properties by name
    - QMetaObject::newInstance constructs a new instance of the class

QOBJECT LIMITATIONS:
• Only signals and slots can live in the signals and slots sections
• Signal/Slot return types cannot be references
• Multiple Inheritance requires QObject to be first
• Moc doesn't support virtual inheritance
• Moc doesn't support templates with Q_OBJECT/signals/slots
• Moc doesn't expand #define: cannot use a macro to declare a signal/slot or used as a signal/slot parameter
• Function Pointers cannot be direct signal/slot Parameters, work-around is to typedef it
• Enums/typedefs cannot be forward decl for signal/slot parameters
• Nested Classes cannot have signals or slots

PARENT-CHILD RELATIONSHIP:
• Parent needs to be explicitly deleted, either by delete or stack scope
• Children deleted by parent automatically, if child is deleted first, parent is notified
• Children should not be created on the stack unless deleted first, as parent assumes children are on heap

IMPLICIT SHARING (COPY-ON-WRITE):
• Objects share the same memory in a 'shared block' if have the same values
• Automatically detaches the object from a shared block when object changes and ref count is > 1
• Qt classes use it internally, doesn't require a shared data pointer for it to happen
• Can be dangerous for iterators when container detaches from shared block:
**************************************************************************************************************/

class MyClass : public QObject
{
    Q_OBJECT // required for all moc provided features
    Q_CLASSINFO("Author", "Name") // attach additional name/value pairs to the class's meta-object

public:
    MyClass(QObject *parent = 0);
    ~MyClass();
    
    // Enums must start with capital letter
    enum MyEnum { ONE, TWO, THREE };
    Q_ENUMS(MyEnum)
    
    // Use Enum with QML
    // Use 'import MyEnums 1.0' and 'MyEnum.ONE'
    static registerEnum() { qmlRegisterType<MyClass>("MyEnums", 1, 0, "MyEnum"); }
    
    // Use Enum with signals/slots
    Q_PROPERTY(MyEnum m_enum READ getEnum WRITE setEnum)
    void setEnum(MyEnum value) { m_enum = value; }
    MyEnum getEnum() const { return m_enum; }

signals:
    void mySignal();

public slots:
    void mySlot();
    void mySlot(void (*fn)(void *)); // Cannot do
    void mySlot(MyFn fn);            // Can do
    
private:
    MyEnum m_enum;
};

// Leave memory unitialised, Q_COMPLEX_TYPE is default
Q_DECLARE_TYPEINFO(MyEnum, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(MyPOD, Q_PRIMITIVE_TYPE);

// std::memcpy() rather than copy constructor to move instances around
// Don't use this for any class that requires deep copying
Q_DECLARE_TYPEINFO(MyClass,  Q_MOVABLE_TYPE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELS / VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
**************************************************************************************************************/

// CREATING CUSTOM MODEL
class MyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    virtual ~MyModel() = default;
    MyModel(QObject* parent = nullptr)
        : QAbstractListModel(parent)
    {
    }

    enum ModelRoles
    {
        MyRole1 = Qt::UserRole + 1,
        MyRole2
    };

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent);
        return static_cast<int>(m_items.size());    
    }
    
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (index.row() >= 0 && index.row() < static_cast<int>(m_items.size()))
        {
            const auto& item = m_items[index.row()];
            if (role == Role1)
            {
                return item->getRole1();
            }
            else if (role == Role2)
            {
                return item->getRole2();
            }
        }
        return QVariant();    
    }
    
    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[MyRole1] = "role_one";
        roles[MyRole2] = "role_two";
        return roles;    
    }
    
    MyItem* rowToItem(int row) const
    {
        return row >= 0 && row < static_cast<int>(m_items.size())
            ? m_items[row].get() : nullptr;
    }
    
    Q_INVOKABLE void qmlFunction(int row)
    {
        if (auto item = rowToItem(row))
        {
            item->doSomethingToChangeData();
            const auto& modelIndex = index(row);
            emit dataChanged(modelIndex, modelIndex);
        }
    }
    
    void createItem()
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items.push_back(std::make_unique<MyItem>());
        endInsertRows();
    }

    void deleteItem(int row)
    {
        if (row >= 0 && row < static_cast<int>(m_items.size()))
        {
            beginRemoveRows(QModelIndex(), row, row);
            auto itr = m_items.begin();
            std::advance(itr, row);
            m_items.erase(itr);
            endRemoveRows();
        }
    }    

private:
    std::vector<MyItem> m_items;
};

// ATTACHING MODEL TO QML VIEW
QQuickView view;
view.rootContext()->setContextProperty("context_model", &model);
view.setSource(QUrl("qrc:/main.qml"));
view.show();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FILESYSTEM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read from a file, no need to close it
QFile file("myFile.txt");
if(file.open(QIODevice::ReadOnly))
{
    QTextStream stream(&file);
    QString line = stream.readLine(); // read the next line
    while(!line.isNull())
    {
        line = stream.readLine();
    }
}
