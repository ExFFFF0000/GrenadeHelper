#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <fstream>

#include "../Library/ImGui/imgui_impl_dx11.h"
#include "../Library/ImGui/imgui_impl_win32.h"
#include "../Library/ImGui/imgui.h"
#include "../Library/math.h"

#include "Render.h"
#include "Style.h"
#include "Windows/WindowBase.h"
#include "Manager.h"

#include "Windows/LoginWindow.h"
#include "Windows/MainWindow.h"
#include "handle.h"
#include <nlohmann/json.hpp>

#include "output/client.dll.hpp"
#include "output/offsets.hpp"
#include "GrenadeHelper.h"

using namespace cs2_dumper::offsets;
using namespace cs2_dumper::schemas::client_dll;
using json = nlohmann::json;

inline uint64_t client;
inline view_matrix_t matrix;

namespace Global
{
    inline bool ShouldExit = false;
}