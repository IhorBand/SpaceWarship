#pragma once

#include <windows.h>
#include <string>
#include <iostream>

#include "Config.h"

class PathHelper
{
public:
    static std::string GetExePath();
    static std::string GetConfigurationPath();
};