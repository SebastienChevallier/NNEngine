#pragma once
#include "imgui.h"

namespace NNE::Debug {
class DebugOverlay {
public:
    static void Init();
    static void Render();
    static void Shutdown();
};
} // namespace NNE::Debug


