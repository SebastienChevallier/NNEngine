#include "DebugOverlay.h"
#include "imgui.h"

using namespace NNE;

namespace {
    bool g_initialized = false;
}

void Debug::DebugOverlay::Init(NNE::Systems::VulkanManager* manager)
{
    (void)manager;
    ImGui::CreateContext();
    g_initialized = true;
}

void Debug::DebugOverlay::Render()
{
    if (!g_initialized)
        return;
    ImGui::NewFrame();
    ImGui::Begin("Debug Overlay");
    auto& entities = Systems::Application::GetInstance()->_entities;
    for (auto* entity : entities) {
        ImGui::Text("Entity %d", entity->GetID());
        for (auto* comp : entity->components) {
            ImGui::Text("  - %s", typeid(*comp).name());
        }
    }
    ImGui::End();
    ImGui::Render();
}
