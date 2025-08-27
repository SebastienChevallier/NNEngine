#include "UISystem.h"
#include "VulkanManager.h"
#include "PerformanceMetrics.h"
#include <imgui.h>
#include "Application.h"

namespace NNE::Systems {

UISystem::UISystem(VulkanManager* manager) : _vkManager(manager) {}

void UISystem::Start() {
    if (_vkManager) {
        _vkManager->initImGui();
    }
    _app = Application::GetInstance();
}

void UISystem::Update(float deltaTime) {
    (void)deltaTime;
    if (!_vkManager) return;

    _vkManager->beginImGuiFrame();

    static bool showPerf = false;
    
    if (ImGui::IsKeyPressed(ImGuiKey_F11)) showPerf = !showPerf;

    if (showPerf) {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Appearing);
        if (ImGui::Begin("Debug", &showPerf)) {
            
            io.FontGlobalScale = 1.1f;

            
            if (ImGui::BeginTabBar("DebugTabs")) {
                if (ImGui::BeginTabItem("Performance")) {
                    ImGui::Text("Frame time: %.2f ms  (%.1f FPS)", g_FrameTimeMs, g_FPS);

                    static float history[120] = {};
                    static int idx = 0;
                    history[idx] = g_FrameTimeMs;
                    idx = (idx + 1) % IM_ARRAYSIZE(history);

                    ImGui::PlotLines("Frametime (ms)",
                        history, IM_ARRAYSIZE(history),
                        idx, nullptr, 0.0f, 50.0f, ImVec2(-1, 80));
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Entities")) {
                    for (NNE::AEntity* e : _app->_entities) {
                        ImGui::PushID(e); 
                        bool open = ImGui::CollapsingHeader(e->GetName().c_str(),
                            ImGuiTreeNodeFlags_SpanAvailWidth);
                        if (open) {                            
                            ImGui::Text("Id: %u", (unsigned)e->GetID());
                            
                            const auto& comps = e->components; 
                            for (auto* c : comps) {
                                ImGui::PushID(c);

                                // Récup du nom de type
                                std::string typeName;                                
                                typeName = typeid(*c).name();

                                // Node repliable pour le composant
                                if (ImGui::TreeNodeEx("##comp",
                                    ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen,
                                    "%s", typeName.c_str())) {
                                    // Contenu debug du composant
                                    //if (auto* ui = dynamic_cast<IDebugUI*>(c)) {
                                    //    ui->DrawImGui();  // chaque composant dessine ses propres champs
                                    //}
                                    //else {
                                    //    ImGui::TextUnformatted("Pas d'UI pour ce composant.");
                                    //}
                                    ImGui::TreePop();
                                }

                                ImGui::PopID();
                            }
                        }

                        ImGui::PopID();
                    }

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }

    ImGui::Render();
}

void UISystem::LateUpdate(float deltaTime) {
    (void)deltaTime;
}

} // namespace NNE::Systems

