#pragma once
#include <vector>
#include "Application.h"
#include "AEntity.h"

namespace NNE::Debug {
class DebugOverlay {
public:
    static void Init(NNE::Systems::VulkanManager* manager);
    static void Render();
};
}

