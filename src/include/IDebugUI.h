#pragma once

namespace NNE {
class IDebugUI {
public:
    virtual ~IDebugUI() = default;
    virtual void DrawImGui() = 0;
};
}
