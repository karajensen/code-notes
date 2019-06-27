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
// base interface class of all I/O devices

// QDataStream
// serialization of binary data to a QIODevice

// QFile
// Interface for reading from and writing to files

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
