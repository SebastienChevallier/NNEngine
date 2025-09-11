#include "UISystem.h"
#include "VulkanManager.h"
#include "PerformanceMetrics.h"
#include <imgui.h>
#include "Application.h"
#include "IDebugUI.h"
#include <functional>
#include <unordered_map>
#include <array>
#include <cstring>
#include <glm/glm.hpp>
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "InputComponent.h"
#include <imgui_internal.h>

namespace NNE::Systems {

UISystem::UISystem(VulkanManager* manager) : _vkManager(manager) {}

void UISystem::Start() {
    _app = Application::GetInstance();
}

void UISystem::Update(float deltaTime) {
    (void)deltaTime;
    if (!_vkManager) return;

    _vkManager->beginImGuiFrame();

    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    static ImGuiID leftDockID = 0;
    static bool dockInit = false;
    if (!dockInit) {
        dockInit = true;
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGuiID dock_main_id = dockspace_id;
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, &leftDockID, &dock_main_id);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    //showPerf = false;
    
    if (ImGui::IsKeyPressed(ImGuiKey_F11)) showPerf = !showPerf;

    if (showPerf) {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::SetNextWindowDockID(leftDockID, ImGuiCond_FirstUseEver);
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

                    bool open = ImGui::CollapsingHeader("Application",
                        ImGuiTreeNodeFlags_SpanAvailWidth);
                    if (open) {
						Application* app = Application::GetInstance();
                        ImGui::Text("Window Size: %u * %u", app->WIDTH, app->HEIGHT);
                        ImGui::Text("Delta time: %u", app->GetDeltaTime());
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Shadow Map")) {
                    VkDescriptorSet desc = _vkManager->getShadowMapDebugDescriptor();
                    if (desc != VK_NULL_HANDLE) {
                        ImGui::Image((ImTextureID)desc, ImVec2(256, 256), ImVec2(0, 1), ImVec2(1, 0));
                    } else {
                        ImGui::TextUnformatted("Shadow map unavailable");
                    }
                    auto& cfg = _vkManager->shadowConfig;
                    ImGui::Separator();
                    ImGui::DragFloat("orthoHalfSize", &cfg.orthoHalfSize, 0.1f, 0.0f, 1000.0f);
                    ImGui::DragFloat("Near Plane", &cfg.nearPlane, 0.01f, 0.001f, 100.0f);
                    ImGui::DragFloat("far Plane", &cfg.farPlane, 0.01f, 0.001f, 100.0f);
                    ImGui::DragFloat("lightDistance", &cfg.lightDistance, 0.01f, 0.1f, 1000.0f);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Entities")) {
                    static std::unordered_map<NNE::AEntity*, std::array<char, 128>> nameBuffers;
                    for (NNE::AEntity* e : _app->_entities) {
                        ImGui::PushID(e); 
                        bool open = ImGui::CollapsingHeader(e->GetName().c_str(),
                            ImGuiTreeNodeFlags_SpanAvailWidth);
                        if (open) {                            
                            ImGui::Text("Id: %u", (unsigned)e->GetID());

                            auto& buf = nameBuffers[e];
                            if (buf[0] == '\0') {
                                std::strncpy(buf.data(), e->GetName().c_str(), buf.size());
                            }
                            if (ImGui::InputText("Name", buf.data(), buf.size())) {
                                e->SetName(buf.data());
                            }

                            
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
                                    if (auto* ui = dynamic_cast<NNE::IDebugUI*>(c)) {
                                        ui->DrawImGui();  // chaque composant dessine ses propres champs
                                    }
                                    else {
                                        ImGui::TextUnformatted("Pas d'UI pour ce composant.");
                                    }
                                    ImGui::TreePop();
                                }

                                ImGui::PopID();
                            }

                            /*if (ImGui::Button("Add Component")) {
                                ImGui::OpenPopup("AddComponentPopup");
                            }
                            if (ImGui::BeginPopup("AddComponentPopup")) {
                                struct ComponentEntry { const char* name; std::function<void(NNE::AEntity*)> add; };
                                static const ComponentEntry entries[] = {
                                    {"MeshComponent", [](NNE::AEntity* ent) { ent->AddComponent<NNE::Component::Render::MeshComponent>(); }},
                                    {"CameraComponent", [](NNE::AEntity* ent) { ent->AddComponent<NNE::Component::Render::CameraComponent>(); }},
                                    {"RigidbodyComponent", [](NNE::AEntity* ent) { ent->AddComponent<NNE::Component::Physics::RigidbodyComponent>(); }},
                                    {"BoxColliderComponent", [](NNE::AEntity* ent) { ent->AddComponent<NNE::Component::Physics::BoxColliderComponent>(glm::vec3(1.0f)); }},
                                    {"InputComponent", [](NNE::AEntity* ent) { ent->AddComponent<NNE::Component::Input::InputComponent>(); }}
                                };
                                for (const auto& entry : entries) {
                                    if (ImGui::Selectable(entry.name)) {
                                        entry.add(e);
                                        ImGui::CloseCurrentPopup();
                                    }
                                }
                                ImGui::EndPopup();
                            }*/
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

