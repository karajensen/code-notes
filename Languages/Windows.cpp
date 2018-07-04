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

/** Get last error as string
https://www.codeproject.com/Tips/479880/GetLastError-as-std-string */
DWORD error = GetLastError();
if (error)
{
    LPVOID lpMsgBuf;
    DWORD bufLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
  
    if (bufLen)
    {
      LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
      std::string result(lpMsgStr, lpMsgStr+bufLen);
      LocalFree(lpMsgBuf);
    }
}
