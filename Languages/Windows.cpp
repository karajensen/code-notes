/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Get the executable Path */
wchar_t exePath[MAX_PATH];
::GetModuleFileNameW(NULL, exePath, MAX_PATH);
::PathRemoveFileSpecW(exePath);

/** Get the mouse position */
POINT cursor;
::GetCursorPos(&cursor);

/** Get short path from an existing file */
auto length = GetShortPathNameW(longWPath.c_str(), NULL, 0);
wchar_t* buffer = new wchar_t[length];
length = GetShortPathNameW(longWPath.c_str(), buffer, length); 
if(length == 0){ /*show error*/ }
std::wstring result(buffer);
delete [] buffer;

