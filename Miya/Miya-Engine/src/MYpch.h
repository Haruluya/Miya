#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "log/Log.h"
#include "utils/Timestep.h"

#ifdef GLCORE_PLATFORM_WINDOWS
#include <Windows.h>
#endif