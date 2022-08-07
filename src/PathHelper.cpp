#include "PathHelper.h"

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

std::string PathHelper::GetExePath() 
{
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    String wstrPath = String(buffer);
    size_t pos = wstrPath.find_last_of("\\/");
    wstrPath = wstrPath.substr(0, pos);
    std::string path(wstrPath.begin(), wstrPath.end());
    return path;
}

std::string PathHelper::GetConfigurationPath()
{
    return PathHelper::GetExePath() + GAME_CONFIGURATION_FILE_PATH;
}