/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT FILE SYSTEM
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

// Iterate over all files in directory (non-recursive)
QDir dir(path);
for (const auto& fileName : dir.entryList(QStringList("*.qml")))
{
    qDebug() << (path + "/" + fileName); // absolute path
}

// Iterate over all files in directory (recursive)
QDirIterator it(path, QStringList() << "*.qml", QDir::Files, QDirIterator::Subdirectories); // files
QDirIterator itr(path, QStringList(), QDir::Dirs|QDir::NoDotAndDotDot, QDirIterator::Subdirectories); // dirs
while (it.hasNext())
{
    qDebug() << it.next(); // absolute path
}

// QUrl
// Interface for working with URLs with prefix qrc:/, file:/// etc.
// Structure is scheme:path or scheme://useinfo@host:port/path/query
// If path passed in has no scheme, considered relative even if absolute path
QUrl url(str) // Set the path directly, does not auto add any scheme
url.clear(); // clears the URL
url.setUrl(str); // Sets the URL
url.isValid(); // Returns true if non-empty and conforms to encoding tests
url.isRelative(); // Returns true if scheme is undefined (same as scheme().isEmpty())
url.toLocalFile() // Convert QUrl to local file path without prefix, normalizes seperators to /
url.toString() // Returns path with prefix file:///, qrc with qrc:/
url.setScheme(str) // Sets type (or protocol) component
url.setPath(str) // Sets path component
QUrl::fromLocalFile(str) // Convert a local file path to QUrl; adds file:/// in front

// QFileInfo
// If path is a directory, treat as filepath but without a name/extension
QFileInfo info(path)
info.absoluteDir() // Returns QDir using absolutePath()
info.absoluteFilePath() // Returns path as absolute QString, keeps dots/symlinks
info.absolutePath() // Returns path without the filename as absolute QString, keeps dots/symlinks
info.baseName() // Returns the filename without directory or extensions
info.birthTime() // Returns QDateTime of date and time when the file was created
info.canonicalFilePath() // Returns path QString, removes dots/symlinks, empty if doesn't exist 
info.canonicalPath() // Returns path without filename QString, removes dots/symlinks, empty if doesn't exist
info.completeBaseName() // Returns the filename as QString without directory or last extension
info.completeSuffix() // Returns all extensions as QString, does not start with '.'
info.dir() // Returns parent directory as QDir, even if info holds a directory         
info.exists() // Returns true if file exists
info.fileName() // Returns full file name as QString including all extensions
info.filePath() // Returns path (which may be absolute or relative)
info.isAbsolute() // Returns true if path is absolute
info.isDir() // Returns true if path is a directory
info.isExecutable() // Returns true if path is an executable
info.isFile() // Returns true if path is a file
info.isHidden() // Returns true if path is hidden
info.isNativePath() // Returns true if path can be used with the OS native file system, minus encoding requirements
info.isReadable() // Returns true if user can read the file
info.isRelative() // Returns true if path is relative
info.isSymLink() // Returns true if path is a symlink
info.isWritable() // Returns true if path is writable
info.lastModified() // Returns QDateTime when path was last modified
info.lastRead() // Returns QDateTime when path was last accessed
info.makeAbsolute() // Converts a relative path to absolute if needed
info.path() // Returns path without the filename (which may be absolute or relative)
info.size() // Returns qint64 of size in bytes
info.suffix() // Returns final extension of file, without the .
QFileInfo::exists(path) // Returns true if file exists, faster than QFileInfo(path).exists()

// QDir
// Can hold both directories and files
// All entryList calls return just the folder/filename, need to use absoluteFilePath
QDir dir(path) // Root directory
dir.absoluteFilePath(filename) // Use with entryList to make into absolute path
dir.absolutePath() // Returns path as absolute, may have symlink but no dots
dir.canonicalPath() // Returns path without symlinks and dots, empty if doesn't exist
dir.cd(path) // Cd to a path, can use . and ..
dir.cdUp() // Move up one directory
dir.count() // Returns uint total amount of files/folders in path
dir.dirName() // Returns name of directory
dir.entryList(nameFilters, filterFlags, sortFlags) // Search directory recursively, returns QStringList
dir.entryList(nameFilters) // Not using any args will use the stored filterFlags/sortFlags
dir.entryList(filterFlags, sortFlags) // Search directory recursively with filter flags, returns QStringList
dir.entryList() // Not using any args will use the stored filterFlags/sortFlags
dir.exists() // Whether path exists
dir.isAbsolute() // Whether path is absolute
dir.isEmpty(filters) // Optional filters, whether directory is empty
dir.isReadable() // Returns true if readable
dir.isRelative() // Returns true if path is relative
dir.isRoot() // Returns true if path is a system root directory
dir.makeAbsolute() // Makes the path absolute if needed
dir.mkdir(folder) // Make a folder under path, returns true if success
dir.mkpath(path) // Make a path under path, will create all folders if needed, returns true if success
dir.path() // Returns path, keeps symlinks but removes dots
dir.remove(filename) // Removes file in path, returns true if success
dir.removeRecursively() // Removes path including all children, returns true if success
dir.rename(oldFileName, newFileName) // Renames a file, returns true if success
dir.setNameFilters(QStringList("*.qml", "*.txt")) // Extension types to filter searches with
dir.setSorting(sortFlags) // Flags to use with entryList
QDir::cleanPath(path) // Returns normalized path; removes dots, seperators become single /, keeps symlinks
QDir::current() // Returns application's current directory as QString
QDir::currentPath() // Returns application's current path as QString                               
QDir::drives() // Returns QFileInfoList of all root drives in the system
QDir::home() // Returns user's home directory as QString
QDir::homePath() // Returns the absolute path of the user's home directory as QString
QDir::listSeparator() // Returns native path list seperator ; or :
QDir::root() // Returns root directory as QDir
QDir::rootPath() // Returns the absolute path of the root directory (eg. c:/)
QDir::separator() // Returns QChar native directory seperator
QDir::temp() // Returns folder for temp files as QDir
QDir::toNativeSeparators(path) // Converts seperators to native seperator
    
// QIODevice
// base interface class of all I/O devices (QFile)
file.close()
file.errorString() // Returns QString
file.isOpen()
file.isReadable() // Returns true if data can be read from the device
file.isWritable()
file.open(mode) // QIODevice OpenMode, returns true if successful
file.openMode() // Returns QIODevice OpenMode
file.readAll() // Returns QByteArray
file.readLine() // Returns QByteArray
file.write(data) // Can be const char* or QByteArray
connect(file, &QIODevice::aboutToClose, fn);
connect(file, &QIODevice::bytesWritten, fn); // qint64 bytes

// QFile
// Interface for reading from and writing to files, inherits QIODevice
QFile file("myFile.txt");
file.remove() // Close the file and remove it, returns true if successful
file.rename(newName) // Close the file, renames and returns true if successful
file.setPermissions(permissions) // QFileDevice Permissions flags
file.permissions() // Returns QFileDevice Permissions flags
file.exists() // Returns true if exists on disk
file.flush() // Flush data to file

// QDataStream
// serialization of binary data to a QIODevice
QDataStream stream(&file)
stream << value // write value to binary
stream >> value // read value from binary

// QTextStream
// Can write to QString and QFile
QTextStream stream(&file)
stream << "str" << value // Write value to stream
stream.setCodec("UTF-8") // Required for windows reading non-ANSI characters
stream.read(count) // Read 'count' characters from stream and return QString
stream.readAll() // Read all and return QString
stream.readNext() // Read next line and return QString
stream.readLineInto(&line) // Read next line into QString
stream.flush() // Write everything to desk

// QDir Filter Flags
QDir::NoFilter         // No filter flag used
QDir::Dirs             // Apply filters to directory names
QDir::AllDirs          // Don't apply the filters to directory names
QDir::Files            // List files
QDir::Drives           // List disk drives
QDir::NoSymLinks       // Do not list symbolic links
QDir::NoDotAndDotDot   // NoDot | NoDotDot
QDir::NoDot            // Do not list the special entry "."
QDir::NoDotDot         // Do not list the special entry ".."
QDir::AllEntries       // Dirs | Files | Drives
QDir::Readable         // List files which application has read access
QDir::Writable         // List files which application has write access
QDir::Executable       // List files which application has execute access
QDir::Modified         // Only list files that have been modified
QDir::Hidden           // List hidden files
QDir::System           // List system files
QDir::CaseSensitive    // The filter should be case sensitive
    
// QDir Sort Flags
QDir::NoSort           // No sorting
QDir::Name             // Sort by name
QDir::Time             // Sort by time (modification time)
QDir::Size             // Sort by file size
QDir::Type             // Sort by file type (extension)
QDir::Unsorted         // Do not sort
QDir::NoSort           // Not sorted by default
QDir::DirsFirst        // Put the directories first, then the files
QDir::DirsLast         // Put the files first, then the directories
QDir::Reversed         // Reverse the sort order
QDir::IgnoreCase       // Sort case-insensitively
QDir::LocaleAware      // Sort using the current locale settings

// QFileDevice Permissions
QFileDevice::ReadOwner      // The file is readable by the owner of the file
QFileDevice::WriteOwner     // The file is writable by the owner of the file
QFileDevice::ExeOwner       // The file is executable by the owner of the file
QFileDevice::ReadUser       // The file is readable by the user
QFileDevice::WriteUser      // The file is writable by the user
QFileDevice::ExeUser        // The file is executable by the user
QFileDevice::ReadGroup      // The file is readable by the group
QFileDevice::WriteGroup     // The file is writable by the group
QFileDevice::ExeGroup       // The file is executable by the group
QFileDevice::ReadOther      // The file is readable by anyone
QFileDevice::WriteOther     // The file is writable by anyone
QFileDevice::ExeOther       // The file is executable by anyone

// QIODevice OpenMode
QIODevice::NotOpen
QIODevice::ReadOnly
QIODevice::WriteOnly    // For file-system subclasses implies Truncate unless combined with ReadOnly/Append/NewOnly
QIODevice::ReadWrite    // ReadOnly | WriteOnly
QIODevice::Append       // Data written to end of file
QIODevice::Truncate     // Truncated before opening (All earlier contents of the device are lost)
QIODevice::Text         // Reading uses '\n', Writing uses local encoding for end of line
QIODevice::Unbuffered   // Any buffer in the device is bypassed
QIODevice::NewOnly      // Create and open the file only if it does not exist
QIODevice::ExistingOnly // Fail if the file to be opened does not exist

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT XML
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QXmlStreamWriter
/************************************************************
<?xml version="1.0" encoding="UTF-8"?>
<A aa="attr">value</A>
<B bb="attr">
    <bbb>value</bbb>
</B>
************************************************************/
QFile file("c:/file.xml");
QXmlStreamWriter stream(&file);
file.open(QIODevice::WriteOnly | QIODevice::Text); // creates if doesn't exist
stream.writeStartDocument();
stream.setCodec("UTF-8");
stream.setAutoFormatting(true);
stream.writeStartElement("A");
stream.writeAttribute("aa", "attr");
stream.writeCharacters("value");
stream.writeEndElement();
stream.writeStartElement("B");
stream.writeAttribute("bb", "attr");
stream.writeTextElement("bbb", "value");
stream.writeEndElement();
stream.writeEndDocument();
stream.hasError(); // Returns true if failed to write to document
file.errorString(); // Returns error as string

// QXmlSchema / QXmlSchemaValidator
// Requires Qt5::XmlPatterns
// Requires QCoreApplication as will output errors in message loop
QXmlSchema schema;
schema.load(QUrl::fromFile("c:/schema.xsd")); // Returns true if success
if (schema.isValid()) {
    QFile file("c:/file.xml");
    file.open(QIODevice::ReadOnly);
    QXmlSchemaValidator validator(schema);
    validator.validate(&file, QUrl::fromLocalFile(file.fileName())); // Returns true if success
}
