/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Unicode, 16-bit QChars, for characters with code > 65535, two consecutive QChars are used
• QStringRef avoids the memory allocation and reference counting overhead of a standard QString 

QSTRINGBUILDER
• Faster than + as multiple substring concatenations will be postponed until the final result
• At final result, amount of memory required is known and allocated only once
• Using QT_USE_QSTRINGBUILDER will auto convert all + to %

QT_NO_CAST_FROM_ASCII                 Disables auto conversion from C strings to QString
QT_RESTRICTED_CAST_FROM_ASCII         Allows auto conversion from char/char arrays, disables rest
QT_NO_CAST_TO_ASCII                   Disables automatic conversion from QString to C strings
QT_USE_QSTRINGBUILDER                 Auto converts all QString + to use QStringBuilder %
**************************************************************************************************************/

QChar::Null // null terminator character \0

// QString
// Most overload using QChar, QRegularExpression, QRegExp
QString str("str")
QString str() / QString str('\0') // Creates a null string
QString str(QStringLiteral("str")) // Internal data will be generated at compile time
str[i] // Returns QCharRef (QChar&) or const QCharRef, assigning to it will COW detach
str.append("str", n) // Adds n characters to the end of the string, returns QString& for chaining
str.append("str") / str.push_back("str") // Adds to the end of the string, returns QString& for chaining
str.arg(value) // Returns QString copy with %n replaced with value (eg. %1, %2...), printf with %n
str.at(i) // Returns QChar at index
str.back() // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.capacity() // Returns maximum number of characters that can be stored without forcing a reallocation
str.chop(n) // Removes n chars from end of the string, if n >= size, string becomes empty
str.chopped(n) // Removes n chars from end of the string and returns QString copy, n >= size is undefined
str.clear() // Makes string empty
str.compare("str", caseFlag) // Returns 0 if they match 
str.contains("str", caseFlag) // Returns true if contains substring str
str.count("str", caseFlag) // Returns count of substring, will count overlaps
str.count() / str.length() / str.size() // Amount of characters minus \0
str.data() // Returns QChar* or const QChar*
str.endsWith("str", caseFlag) // Returns true if ends with str
str.fill('c', n) // Resizes string to n and fills with character, without n will fill to current size
str.front() // Returns QChar (const version) or QCharRef at back, undefined on empty string
str.indexOf("str", i) // Searches for str from index i, returns index, or -1 if not found
str.insert(n, "str") // Inserts str at index n, returns QString&, auto resizes if n >= size
str.isEmpty() // Returns true if has no characters
str.isNull() // Returns true if null (default constructor)
str.isRightToLeft() // Returns true if string is to be read right to left
str.lastIndexOf("str", i) // Searches for str backwards from index i, returns index, or -1 if not found
str.left(n) // Returns QString with only n characters starting from left
str.leftJustified(n, 'c') // Returns QString of n width, any extra chars padded with fill 'c'
str.leftRef(n) // Returns QStringRef of n left most characters
str.mid(i, n) // Returns QString starting at index i for n optional characters
str.midRef(i, n) // Returns QStringRef starting at index i for n optional characters    
str.prepend("str") / str.push_front("str") // Adds to start of str and returns QString&
str.remove(i, n) // Removes n characters from index i, returns QString&, if i+n >= size will truncate
str.remove("str", caseFlag) // Removes every occurance of str and returns QString&
str.repeated(n) // Returns QString repeated n times
str.replace(i, n, "str") // Replaces from index i over n characters with str and returns QString& 
str.replace("a", "b", caseFlag) // Replaces all instances of "a" with "b"
str.reserve(n) // Reserve capacity for n characters
str.resize(n) // Sets size of string to n characters, new characters are uninitialized
str.resize(n, 'c') // Sets size of string to n characters, new characters use 'c'
str.right(n) // Returns QString with only n characters starting from right
str.rightJustified(n, 'c') // Returns QString of n width from end, any extra chars padded with fill 'c'
str.rightRef(n) // Returns QStringRef of n right most characters
str.section(',', s1, s2, sectionFlag) // For string ",,a,b,," will take section s1 to s2 where a=1, b=2 etc
str.setNum(integer) // Converts integer to QString
str.setNum(double, format, precision) // Converts floating point number to QString, Format Characters
str.setRawData(qchar, n) // Takes const QChar*, does not copy, qchar must stay alive, n = size
str.shrink_to_fit() / str.squeeze() // Removes unused capacity
str.simplified() // Returns QString with no start/end whitespace, any \t\n\v\f\r all replaced with single space
str.split(" ", splitFlag, caseFlag) // Returns QStringList split by delim, default keeps empty entries
str.splitRef(" ", splitFlag, caseFlag) // Same as split, but returns QVector<QStringRef>, requires str alive
str.startsWith("str", caseFlag) // Returns true if starts with str
str.toLower() / str.toCaseFolded() // Returns lower case QString
str.toUpper() // Returns upper case QString
str.toHtmlEscaped() // Converts a string for use in HTML with metacharacters < > & " replaced
str.toDouble(&ok) // Converts to double or 0.0 if fails, can include characters + - g e .
str.toFloat(&ok) // Converts to float or 0.0 if fails, can include characters + - g e .
str.toInt(&ok, base = 10) // Converts to int or 0, 0x in str will use hexadecimal base
str.toLong(&ok, base = 10) // Converts to long or 0, 0x in str will use hexadecimal base
str.toLongLong(&ok, base = 10) // Converts to long long or 0, 0x in str will use hexadecimal base
str.toShort(&ok, base = 10) // Converts to short or 0, 0x in str will use hexadecimal base
str.toUInt(&ok, base = 10) // Converts to unsigned int or 0, 0x in str will use hexadecimal base 
str.toULong(&ok, base = 10) // Converts to unsigned long or 0, 0x in str will use hexadecimal base
str.toULongLong(&ok, base = 10) // Converts to unsigned long long or 0, 0x in str will use hexadecimal base
str.toUShort(&ok, base = 10) // Converts to unsigned short or 0, 0x in str will use hexadecimal base
str.toLocal8Bit().constData() // Convert to ANSI const char*, null string returns \0
str.toUtf8().constData() // Convert to Utf8 const char*, null string returns \0
str.toWCharArray(arr) // Fills wchar_t*, arr must be preallocated, returns length of arr, does not add \0
str.toStdWString() // Returns std::wstring
str.toStdString() // Returns std::string using toUtf8()
str.trimmed() // Returns QString with no pre/post whitespaces
str.truncate(i) // Removes all characters from index i onwards
str.begin() / str.end() // iterator or const_iterator
str.rBegin() / str.rEnd() // reverse_iterator or const_reverse_iterator
str.cbegin() / str.cend() // const_iterator
str.constBegin() / str.constEnd() // const_iterator
str.crbegin() / str.crEnd() // const_reverse_iterator    
QString::asprintf("%i", n) // QString version of printf, uses same modifiers
QString::compare(str1, str2, caseFlag) // Returns 0 if they match, comparing char codes
QString::localeAwareCompare(str1, str2) // Returns 0 if they match, comparing actual words
QString::number(integer) // Converts integer to QString
QString::number(double, format, precision) // Converts floating point number to QString, Format Characters
QString::fromWCharArray(str, size) // Copies const wchar_t* to QString
QString::fromLocal8Bit(str, size) // Copies ANSI const char* to QString
QString::fromUtf8(str, size) // Copies Utf8 const char* to QString
QString::fromStdString(str) // Copies std::string using fromUtf8 to QString
QString::fromStdWString(str) // Copies std::wstring to QString
    
// QStringRef
// Most overload using QChar, QRegularExpression, QRegExp
QStringRef ref(&str)
QStringRef ref(&str, i, n) // Reference str from index i for n characters
ref[i] // Returns QChar
ref.appendTo(&str) // Adds ref to str, returns QStringRef for the new combination
ref.at(i) // Returns QChar at index
ref.back() // Returns QChar at back, undefined on empty string
ref.chop(n) // Removes n chars from end of the string, if n >= size, string becomes empty
ref.chopped(n) // Removes n chars from end of the string and returns QStringRef, n >= size is undefined
ref.clear() // Makes reference empty
ref.compare("str", caseFlag) // Returns 0 if they match 
ref.contains("str", caseFlag) // Returns true if contains substring str
ref.count("str", caseFlag) // Returns count of substring, will count overlaps
ref.count() / ref.length() / ref.size() // Amount of characters minus \0
ref.data() // Returns const QChar*
ref.endsWith("str", caseFlag) // Returns true if ends with str
ref.front() // Returns QChar at front, undefined on empty string
ref.indexOf("str", i) // Searches for str from index i, returns index, or -1 if not found
ref.isEmpty() // Returns true if has no characters
ref.isNull() // Returns true if null (default constructor)
ref.isRightToLeft() // Returns true if string is to be read right to left
ref.lastIndexOf("str", i) // Searches for str backwards from index i, returns index, or -1 if not found
ref.left(n) // Returns QStringRef with only n characters starting from left
ref.mid(i, n) // Returns QStringRef starting at index i for n optional characters
ref.position() // Returns index the ref starts in the actual string
ref.right(n) // Returns QStringRef with only n characters starting from right
ref.split(" ", splitFlag, caseFlag) // Returns QVector<QStringRef> split by delim, default keeps empty entries
ref.startsWith("str", caseFlag) // Returns true if starts with str
ref.string() // Returns full const QString* or 0 if doesn't reference anything
ref.toDouble(&ok) // Converts to double or 0.0 if fails, can include characters + - g e .
ref.toFloat(&ok) // Converts to float or 0.0 if fails, can include characters + - g e .
ref.toInt(&ok, base = 10) // Converts to int or 0, 0x in str will use hexadecimal base
ref.toLong(&ok, base = 10) // Converts to long or 0, 0x in str will use hexadecimal base
ref.toLongLong(&ok, base = 10) // Converts to long long or 0, 0x in str will use hexadecimal base
ref.toShort(&ok, base = 10) // Converts to short or 0, 0x in str will use hexadecimal base
ref.toUInt(&ok, base = 10) // Converts to unsigned int or 0, 0x in str will use hexadecimal base 
ref.toULong(&ok, base = 10) // Converts to unsigned long or 0, 0x in str will use hexadecimal base
ref.toULongLong(&ok, base = 10) // Converts to unsigned long long or 0, 0x in str will use hexadecimal base
ref.toUShort(&ok, base = 10) // Converts to unsigned short or 0, 0x in str will use hexadecimal base
ref.toLocal8Bit().constData() // Convert to const char* using system's local encoding, null string returns \0
ref.toUtf8().constData() // Convert to const char* using UTF-8 encoding, null string returns \0
ref.trimmed() // Returns QStringRef with no pre/post whitespaces
ref.truncate(i) // Removes all characters from index i onwards
ref.begin() / ref.end() // iterator or const_iterator
ref.rBegin() / ref.rEnd() // reverse_iterator or const_reverse_iterator
ref.cbegin() / ref.cend() // const_iterator
ref.constBegin() / ref.constEnd() // const_iterator
ref.crbegin() / ref.crEnd() // const_reverse_iterator
  
// QByteArray
// Used to store both raw bytes (including '\0's) and traditional 8-bit '\0'-terminated strings
// Most overload using char, string literal/cstring
QByteArray arr("str")
QByteArray arr(data) // Does deep copy of const char* and adds on a \0
QByteArray arr(n, 'c') // Fills n size with character c
arr.append(arr2) / arr.push_back(arr2) // If non-empty, makes deep copy of arr2 and adds to arr
arr.append(n, 'c') // Adds n size with character c to end
arr.at(index) // Returns char at index position i
arr.back() // Returns char if const, QByteRef if non-const
arr.capacity() // Returns maximum items before forcing a reallocation
arr.chop(n) // Removes n bytes from the end of the byte array, if n > size, becomes empty
arr.chopped(n) // Returns QByteArray with size-n bytes copied, if n > size, undefined
arr.clear() // Clears the contents of the byte array and makes it null
arr.contains(arr2) // Whether arr contains arr2
arr.count(arr2) // Returns number of potentially overlapping occurrences of arr2 in arr
arr.count() / arr.length() / arr.size() // Amount of characters minus \0
arr.data() // Non-const returns char*, const returns const char*, includes \0
arr.endsWith(arr2) // Whether arr ends with arr2
arr.fill('c', n) // Resizes string to n and fills with character, without n will fill to current size
arr.front() // Returns char if const, QByteRef if non-const
arr.indexOf(arr2, i) // Searches for arr2 from index i, returns index, or -1 if not found
arr.insert(n, arr2) // Inserts arr2 at index n, returns QByteArray&, auto resizes if n >= size
arr.isEmpty() // Returns true if has no items
arr.isNull() // Returns true if null (default constructor)
arr.lastIndexOf(arr2, i) // Searches for arr2 backwards from index i, returns index, or -1 if not found
arr.left(n) // Returns QByteArray with only n characters starting from left
arr.leftJustified(n, 'c') // Returns QByteArray of n width, any extra chars padded with fill 'c'
arr.mid(i, n) // Returns QByteArray starting at index i for n optional characters
arr.number(n) // Converts number to QByteArray
arr.number(double, format, precision) // Converts floating point number to QByteArray, Format Characters
arr.prepend(arr2) / str.push_front(arr2) // Adds to start of arr
arr.remove(i, n) // Removes n bytes from index i, returns QByteArray&, if i+n >= size will truncate
arr.repeated(n) // Returns QByteArray repeated n times
arr.replace(i, n, arr2) // Replaces from index i over n characters with arr2 and returns QByteArray& 
arr.replace("a", "b") // Replaces all instances of "a" or 'a' with "b" or 'b'
arr.reserve(n) // Reserve capacity for n characters
arr.resize(n) // Sets size to n characters, new characters are uninitialized
arr.right(n) // Returns QByteArray with only n characters starting from right
arr.rightJustified(n, 'c') // Returns QByteArray of n width from end, any extra chars padded with fill 'c'
arr.setNum(integer) // Converts integer to QString
arr.setNum(double, format, precision) // Converts floating point number to QByteArray, Format Characters
arr.setRawData(cstr, n) // Takes const char*, does not copy, cstr must stay alive, n = size
arr.shrink_to_fit() / arr.squeeze() // Removes unused capacity
arr.simplified() // Returns QByteArray with no start/end whitespace, any \t\n\v\f\r all replaced with single space
arr.split(" ") // Returns QList<QByteArray> split by delim
arr.startsWith(arr2) // Returns true if starts with arr2
arr.toBase64(options) // Returns QByteArray copy encoded, QByteArray Base64 Options Enum optional
arr.toHex() // Returns QByteArray copy encoded
arr.toDouble(&ok) // Converts to double or 0.0 if fails, can include characters + - g e .
arr.toFloat(&ok) // Converts to float or 0.0 if fails, can include characters + - g e .
arr.toInt(&ok, base = 10) // Converts to int or 0, 0x in str will use hexadecimal base
arr.toLong(&ok, base = 10) // Converts to long or 0, 0x in str will use hexadecimal base
arr.toLongLong(&ok, base = 10) // Converts to long long or 0, 0x in str will use hexadecimal base
arr.toShort(&ok, base = 10) // Converts to short or 0, 0x in str will use hexadecimal base
arr.toUInt(&ok, base = 10) // Converts to unsigned int or 0, 0x in str will use hexadecimal base 
arr.toULong(&ok, base = 10) // Converts to unsigned long or 0, 0x in str will use hexadecimal base
arr.toULongLong(&ok, base = 10) // Converts to unsigned long long or 0, 0x in str will use hexadecimal base
arr.toUShort(&ok, base = 10) // Converts to unsigned short or 0, 0x in str will use he
arr.toLower() // Returns lower case QByteArray
arr.toUpper() // Returns upper case QByteArray
arr.trimmed() // Returns QByteArray with no pre/post whitespaces
arr.truncate(i) // Removes all characters from index i onwards
arr.begin() / arr.end() // iterator or const_iterator
arr.rBegin() / arr.rEnd() // reverse_iterator or const_reverse_iterator
arr.cbegin() / arr.cend() // const_iterator
arr.constBegin() / arr.constEnd() // const_iterator
arr.crbegin() / arr.crEnd() // const_reverse_iterator
QByteArray::fromBase64(arr, options) // Returns Base64 decoded copy, QByteArray Base64 Options Enum optional
QByteArray::fromHex(arr) // Returns Hex decoded copy
QByteArray::fromRawData(data) // Returns QByteArray with data without any deep copy
  
// QTextStream
QTextStream(&str) << "str" << value; // QString streamstream
stream.setCodec("UTF-8") // Required for windows reading non-ANSI characters

// QStringList
// Inherits from QList<QString>
// Most also overload using a char, QRegularExpression, QRegExp
QStringList<T> lst = { value }
QStringList<T> lst("str")
lst.join("delim") // Returns a combined string seperated by delim
lst.split("delim") // Returns 
lst.contains("str", caseFlag) // True if list contains string
lst.filter(regex) // Returns QStringList filtered by regex
lst.indexOf(regex, i) // Returns index of first match from regex starting from optional i, else -1
lst.lastIndexOf(regex, i) // Returns index of last match from regex backwards from optional i, else -1
lst.removeDuplicates() // Removes all duplicate strings, doesn't require sorting
lst.replaceInStrings("str1", "str2", caseFlag) // Replace 'str1' with 'str2' in all strings
lst.sort(case) // Sort all strings using std::sort
  
// QRegularExpression
// Provides pattern matching using regular expressions
  
// QRegExp
// Provides pattern matching using regular expressions
  
// QString / QByteArray Format Characters
e   // format as [-]9.9e[+|-]999
E   // format as [-]9.9E[+|-]999
f   // format as [-]9.9
g   // use e or f format, whichever is the most concise
G   // use E or f format, whichever is the most concise 

// QString Section Flags
QString::SectionSkipEmpty             // Ignore empty sections; don't include in section count
QString::SectionIncludeLeadingSep     // Include any leading delims in the result string
QString::SectionIncludeTrailingSep    // Include any trailing delims in the result string
QString::SectionCaseInsensitiveSeps   // Compare the delims case-insensitively
QString::SectionDefault               // Empty sections counted, pre/post delims not included and case sensitive

// QString Split Flags                           
QString::KeepEmptyParts	         // If a field is empty, keep it in the result
QString::SkipEmptyParts	         // If a field is empty, don't include it in the result                          
  
// QString Case Flags
Qt::CaseInsensitive              // Lower and upper characters treated the same
Qt::CaseSensitive                // Lower and upper characters not treated the same

// QByteArray Base64 Options Enum
QByteArray::Base64Encoding       // The regular Base64 alphabet
QByteArray::Base64UrlEncoding    // An alternate alphabet which replaces two characters to be URL friendly
QByteArray::KeepTrailingEquals   // Make data always a size multiple of four by keeping trailing equal characters
QByteArray::OmitTrailingEquals   // Omits adding the padding equal signs at the end of the encoded data

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT VARIANT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Holds a single value of a type, need to register type to use it
• For Q_PRIMITIVE_TYPE objects doesn't call constructor/destructor
• To use custom types, must be registered with Q_DECLARE_METATYPE
• QVariantList is typedef for QList<QVariant>, QVariantMap is typedef for QMap<QString, QVariant>
• See http://doc.qt.io/qt-5/qvariant-obsolete.html#Type-enum for Variant Type Enum
**************************************************************************************************************/

QVariant variant // Null variant
QVariant variant("str")
qvariant_cast<T>(variant) // Returns T, same as variant.value<T>()
variant.canConvert<T>() // Whether can cast, T doesn't have to be variant type
variant.convert<T>() // Cast variant to type, returns true if success
variant.clear() // Convert to type QMetaType::UnknownType and free up any resources
variant.fromValue(value) // Returns a QVariant containing a copy of value
variant.isNull() // Null if no value, nullptr or type that has an isNull method which returns true
variant.isValid() // Returns true if the storage type is not QMetaType::UnknownType
variant.setValue(value) // Stores a copy of value
variant.toBitArray() // QBitArray
variant.toBool() // bool
variant.toByteArray() //QByteArray
variant.toChar() // QChar
variant.toDate() // QDate
variant.toDateTime() // QDateTime
variant.toDouble(&ok) // double
variant.toEasingCurve() // QEasingCurve
variant.toFloat(&ok) // float
variant.toHash() // QHash<QString, QVariant>
variant.toInt(&ok) // int
variant.toJsonArray() // QJsonArray
variant.toJsonDocument() // QJsonDocument
variant.toJsonObject() // QJsonObject
variant.toJsonValue() // QJsonValue
variant.toLine() // QLine
variant.toLineF() // QLineF
variant.toList() // QList<QVariant>	
variant.toLocale() // QLocale
variant.toLongLong(&ok) // qlonglong
variant.toMap() // QMap<QString, QVariant>
variant.toModelIndex() // QModelIndex
variant.toPersistentModelIndex() // QPersistentModelIndex
variant.toPoint() // QPoint
variant.toPointF() // QPointF
variant.toReal(&ok) // qreal
variant.toRect() // QRect
variant.toRectF() // QRectF
variant.toRegExp() // QRegExp
variant.toRegularExpression() // QRegularExpression
variant.toSize() // QSize
variant.toSizeF() // QSizeF
variant.toString() // QString
variant.toStringList() // QStringList
variant.toTime() // QTime
variant.toUInt(&ok) // uint
variant.toULongLong(&ok) // qulonglong
variant.toUrl() // QUrl
variant.toUuid() // QUuid
variant.type() // Returns QVariant::Type
variant.typeName() // Returns const char* or 0 if invalid
variant.value<T>() // If the value cannot be converted a default-constructed value will be returned
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT CONTAINERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Type T must provide default constructor, copy constructor, assignment operator, else use T*
• Iterators can become invalid after insertion/removal, due to changing internals and implicit sharing (COW)
• Using mutable operator[] will COW detach, except for QByteArray which uses QByteRef
• Using mutable iterators will COW detach, use constBegin/constEnd for read-only
• Can disable implicit conversion of begin() to constBegin() using QT_STRICT_ITERATORS
• Q_MOVABLE_TYPE/Q_PRIMITIVE_TYPE can improve performance for some containers

QList<T>
• Pre-allocates array of void*, with extra space before/after, fast index access, insertions and removals
• void* becomes T if sizeof(T) <= sizeof(void*) and T is Q_PRIMITIVE_TYPE or Q_MOVABLE_TYPE
  else void* becomes T*, copy-constructed into the heap using new
• For Q_PRIMITIVE_TYPE objects doesn't call constructor/destructor
• Wastes memory if sizeof(T) < sizeof(void*) or if allocated on heap due to extra T*

QVector<T>
• Continuous memory allocation, reallocates whole block when resizing
• Fast index access and add/remove from back, slow insert and add/remove from front
• For Q_PRIMITIVE_TYPE objects doesn't call constructor/destructor
• For Q_MOVABLE_TYPE when moving objects uses realloc (faster)

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

// CONTAINER ITERATING
// Q_FOREACH takes const copy of container before iterating to prevent COW detach
// If Q_FOREACH original container detaches, doesn't affect Q_FOREACH looping container
// Do not use Q_FOREACH with STL containers or QVarLengthArray as they don't have COW
// STL for loop will COW detach if container itself is non-const, using const for item doesn't prevent
Q_FOREACH (const auto& value, container) {}
for (const auto& value : container) {} // COW detaches if container is mutable
for (const auto& value : std::as_const(container)) {} // Enforce const container, No COW detach
for (auto itr = container.begin(); itr != container.end(); ++itr) {} // COW detaches if container is mutable
for (auto itr = container.cbegin(); itr != container.cend(); ++itr) {} // No COW detach

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
// QT JSON
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QJsonObject
// Key is case sensitive string, value is QJsonValue
QJsonObject obj
QJsonObject obj = { {"key1", 1}, {"key2", 2} };
obj.constFind("key") // Returns QJsonObject::const_iterator or end()
obj.contains("key") // Returns true if key exists
obj.count() / obj.length() / obj.size() // Number of key-value pairs
obj.empty() / obj.isEmpty() // Whether the object is empty
obj.erase(itr) // Erases key-value pair at itr
obj.find("key") // Returns QJsonObject::iterator or end()
obj.insert("key", value) // Insert or replace, returns QJsonObject::iterator for entry
obj.insert("key", QJsonValue::Undefined) // Will remove 'key'
obj.keys() // Returns QStringList of all keys
obj.remove("key") // Removes 'key'
obj.take("key") // Removes 'key' and returns QJsonValue
obj.toVariantHash() // Returns QVariantHash
obj.toVariantMap() // Returns QVariantMap
obj.value("key") // Returns QJsonValue object
obj.begin() // QJsonObject::iterator or QJsonObject::const_iterator
obj.end() // QJsonObject::iterator or QJsonObject::const_iterator
obj.constBegin() // QJsonObject::const_iterator
obj.constEnd() // QJsonObject::const_iterator
QJsonObject::fromVariantHash(hash) // Converts from a QVariantHash
QJsonObject::fromVariantMap(map) // Converts from a QVariantMap

// QJsonValue
QJsonValue value
value.isArray() // Whether value holds a QJsonArray
value.isBool() // Whether value holds a boolean
value.isDouble() // Whether value holds a double
value.isNull() // Whether value is null
value.isObject() // Whether value holds a QJsonObject
value.isString() // Whether value holds a QString
value.isUndefined() // Whether value holds an array
value.toArray(default) // Default optional, returns default or QJsonArray() if failed
value.toBool(default) // Default optional, returns default or false if failed
value.toDouble(default) // Default optional, returns default or 0 if failed
value.toInt(default) // Default optional, returns default or 0 if failed
value.toObject(default) // Default optional, returns QJsonObject() if failed
value.toString(default) // Default optional, returns a null QString() if failed
value.toVariant(default) // See QJsonValue to QVariant Conversion
value.type() // Returns QJsonValue::Type
    
// QJsonValue to QVariant Conversion
Null       ->   QMetaType::Nullptr
Bool       ->   QMetaType::Bool
Double     ->   QMetaType::Double
String     ->   QString
Array      ->   QVariantList
Object     ->   QVariantMap
Undefined  ->   QVariant()
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT JAVASCRIPT OBJECT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
/*************************************************************************************************************
• Used to pass Javascript objects/functions to/from QML
• Can be stored in QVariant
• Has no comparison functions, cannot be used as Q_PROPERTY with MEMBER
**************************************************************************************************************/    

// Creating object in C++
QJSEngine myEngine;
QJSValue obj = myEngine.newObject();
obj.setProperty("key", "value");

// Calling QML Function in C++
Q_INVOKABLE void fn(const QJSValue& callback)
{
    if (callback.isCallable()) 
    {
        QJSValueList args;
        args << "one";
        args << 2;
        const QJSValue value = callback.call(args);
        const bool exception = value.isError(); // will be error if exception happened
        const bool undefined = value.isUndefined(); // will be undefined if callback isn't a function or no return
    }
}

// QJSValue
QJSValue obj("value") / QJSValue obj(0) / QJSValue obj(0.0) / QJSValue obj(true)
obj.call(args) // See calling QML function in C++
obj.deleteProperty("key") // Returns true if deleted key or key doesn't exist
obj.equals(obj2) // Comparison using javascript == (compares values but not types)
obj.strictlyEquals(obj2) // Comparison using javascript === (compares values and types)
obj.errorType() // Returns QJSValue::ErrorType
obj.hasProperty("key")
obj.isArray() // Is javascript Array
obj.isBool() // Is javascript Boolean
obj.isUndefined() // Is javascript Undefined
obj.isCallable() // Can be called as a function
obj.isDate() // Is javacript Date
obj.isError() // Is an object of the Error class
obj.isNull() // Is javascript Null
obj.isNumber() // Is javascript Number
obj.isObject() // Is javascript Object
obj.isQObject() // Is a QObject
obj.isRegExp() // Is javascript RegExp
obj.isString() // Is javascript String
obj.isVariant() // Is a variant value
obj.property("key") // Returns QJSValue which is undefined if doesn't exist
obj.property(index)
obj.setProperty("key", "value") // Creates if doesn't exist, does nothing if not an Object
obj.setProperty(index, "value") 
obj.toBool() // Returns bool
obj.toDateTime() // Returns QDateTime
obj.toInt() // Returns qint32
obj.toNumber() // Returns double
obj.toQObject() // Returns QObject*
obj.toString() // Returns QString
obj.toUInt() // Returns quint32
obj.toVariant() // Returns QVariant, converts type if needed eg. Boolean -> QVariant(bool)
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT QML PROPERTY MAP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
/*************************************************************************************************************
• Used to create dynamic QObject properties for use in QML
**************************************************************************************************************/
    
QQmlPropertyMap map
map.insert("property", variant)
map.clear("property")
map.contains("property")
map.count() / map.size() 
map.isEmpty()
map.keys() // Returns QStringList of all property names
map.value("property") // Returns QVariant value at key or invalid QVariant if doesn't exist
map.valueChanged() // Signal emitted only when value is changed in QML

// ADDING TO QML
QQmlPropertyMap subMap(&map)
map.insert("property", QVariant::fromValue(0))
subMap.insert("property", QVariant::fromValue("test"))
map.insert("subMap", QVariant::fromValue(subMap))
context->setContextProperty("map", &map)
console.log(map.subMap.property)
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MIME DATA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
/*************************************************************************************************************
• Used to describe information that can be stored in clipboard / transferred via drag and drop mechanism
• To use custom types, must be registered with Q_DECLARE_METATYPE / qRegisterMetaTypeStreamOperators 
**************************************************************************************************************/

QMimeData data;
data.colorData() // Returns QVariant with QColor or null if can't return a color
data.data(mimeType) // Returns QByteArray from type
data.formats() // Returns QStringList of mimeTypes supported by the object
data.hasColor() // Returns true if object can return a color
data.hasFormat(mimeType) // Returns true if the object can return data for the MIME type specified by mimeType
data.hasHtml() // Returns true if the object can return HTML
data.hasImage() // Returns true if the object can return an image
data.hasText() // Returns true if the object can return plain text
data.hasUrls() // Returns true if the object can return a list of urls
data.html() // Returns QString if the data stored in the object is HTML, else empty
data.imageData() // Returns QVariant with QImage or null if can't return an image
data.removeFormat(mimeType) // Removes the data entry for mimeType in the object
data.retrieveData(mimeType, variantType) // Returns QVariant, see Variant section for Variant Type Enum
data.setColorData(color) // Takes QVariant with QColor
data.setData(mimeType, data) // Takes QByteArray, sets data for mime type
data.setHtml(html) // Takes QString
data.setImageData(image) // Takes QVariant with QImage
data.setText(text) // Takes QString
data.setUrls(urls) // Takes QList<QUrl>
data.text() // Returns QString or empty
data.urls() // Returns QList<QUrl> or empty
    
// Mime Types
"application/x-qabstractitemmodeldatalist"
"application/x-color"                          // QColor      
"text/uri-list"                                // QList<QUrl> 
"text/html"                                    // QString
"text/plain"                                   // QString
"image/ *"                                     // QImage      

