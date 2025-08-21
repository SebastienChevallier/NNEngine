#pragma once
#include "imgui.h"

namespace NNE::Debug {
class DebugOverlay {
public:
    void Init();
    void Render();
    void Shutdown();
};
} // namespace NNE::Debug


