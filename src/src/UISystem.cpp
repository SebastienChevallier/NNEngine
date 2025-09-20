#include "UISystem.h"
#include "VulkanManager.h"
#include "PerformanceMetrics.h"
#include <imgui.h>
#include "Application.h"
#include "IDebugUI.h"
#include <unordered_map>
#include <array>
#include <cstring>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <imgui_internal.h>
#include "AEntity.h"
#include "TransformComponent.h"

namespace NNE::Systems {

UISystem::UISystem(VulkanManager* manager) : _vkManager(manager) {}

void UISystem::Start() {
    _app = Application::GetInstance();
    if (_app) {
        _sceneTabActive = _app->IsSceneViewActive();
    }
}

void UISystem::Update(float deltaTime) {
    (void)deltaTime;
    if (!_vkManager) return;

    _vkManager->beginImGuiFrame();

    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    static ImGuiID hierarchyDockID = 0;
    static ImGuiID inspectorDockID = 0;
    static ImGuiID viewportDockID = 0;
    static ImGuiID toolbarDockID = 0;
    static bool dockInit = false;
    if (!dockInit) {
        dockInit = true;
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = dockspace_id;
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.12f, &toolbarDockID, &dock_main_id);
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.22f, &hierarchyDockID, &dock_main_id);
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, &inspectorDockID, &dock_main_id);
        viewportDockID = dock_main_id;

        ImGui::DockBuilderDockWindow("Hierarchy", hierarchyDockID);
        ImGui::DockBuilderDockWindow("Inspector", inspectorDockID);
        ImGui::DockBuilderDockWindow("Viewport", viewportDockID);
        ImGui::DockBuilderDockWindow("Toolbar", toolbarDockID);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    if (ImGui::IsKeyPressed(ImGuiKey_F11)) showPerf = !showPerf;

    DrawToolbarWindow(toolbarDockID);
    DrawHierarchyWindow(hierarchyDockID);
    DrawInspectorWindow(inspectorDockID);
    DrawViewportWindow(viewportDockID);
    if (showPerf) {
        DrawDebugWindow(inspectorDockID);
    }

    ImGui::Render();
}

void UISystem::DrawToolbarWindow(ImGuiID dockId) {
    ImGui::SetNextWindowDockID(dockId, ImGuiCond_FirstUseEver);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    if (ImGui::Begin("Toolbar", nullptr, flags)) {
        if (_app) {
            bool isSceneView = _app->IsSceneViewActive();
            bool isPlaying = _app->IsPlayMode();

            if (isSceneView) {
                // Scene view always pauses the game logic.
                if (isPlaying) {
                    _app->SetPlayMode(false);
                    isPlaying = false;
                }
                ImGui::BeginDisabled();
            }

            if (ImGui::Button(isPlaying ? "Stop" : "Play", ImVec2(80.0f, 0.0f))) {
                _app->SetPlayMode(!isPlaying);
            }

            if (isSceneView) {
                ImGui::EndDisabled();
            }

            ImGui::SameLine();
            ImGui::Text("Mode: %s", _app->IsPlayMode() ? "Play" : "Edit");
            ImGui::SameLine();
            ImGui::Text("View: %s", isSceneView ? "Scene" : "Game");
            ImGui::SameLine();
            ImGui::Text("Frame %.2f ms", _app->GetDeltaTime() * 1000.0f);
            ImGui::SameLine();
            ImGui::Text("Game %.2f ms", _app->GetGameDeltaTime() * 1000.0f);
            ImGui::SameLine();
            ImGui::Checkbox("Debug", &showPerf);
        }
    }
    ImGui::End();
}

void UISystem::DrawHierarchyWindow(ImGuiID dockId) {
    ImGui::SetNextWindowDockID(dockId, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Hierarchy")) {
        if (_app) {
            bool hasEntities = false;
            for (NNE::AEntity* entity : _app->_entities) {
                if (!entity || !entity->transform) continue;
                if (entity->transform->parent) continue;
                hasEntities = true;
                DrawHierarchyNode(entity->transform);
            }
            if (!hasEntities) {
                ImGui::TextUnformatted("No root entities found.");
            }
        }
    }
    ImGui::End();
}

void UISystem::DrawHierarchyNode(NNE::Component::TransformComponent* transform) {
    if (!transform) return;
    NNE::AEntity* entity = transform->GetEntity();
    if (!entity) return;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (transform->children.empty()) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    if (entity == _selectedEntity) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    bool open = ImGui::TreeNodeEx(entity, flags, "%s", entity->GetName().c_str());
    if (ImGui::IsItemClicked()) {
        _selectedEntity = entity;
    }

    if (open && !(flags & ImGuiTreeNodeFlags_Leaf)) {
        for (auto* child : transform->children) {
            DrawHierarchyNode(child);
        }
        ImGui::TreePop();
    }
}

void UISystem::DrawInspectorWindow(ImGuiID dockId) {
    ImGui::SetNextWindowDockID(dockId, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Inspector")) {
        if (_app && _selectedEntity) {
            auto it = std::find(_app->_entities.begin(), _app->_entities.end(), _selectedEntity);
            if (it == _app->_entities.end()) {
                _selectedEntity = nullptr;
            }
        }
        if (!_selectedEntity) {
            ImGui::TextUnformatted("Select an entity from the hierarchy.");
        } else {
            static std::unordered_map<NNE::AEntity*, std::array<char, 128>> nameBuffers;

            ImGui::Text("Id: %u", static_cast<unsigned>(_selectedEntity->GetID()));
            auto& buf = nameBuffers[_selectedEntity];
            if (buf[0] == '\0') {
                std::strncpy(buf.data(), _selectedEntity->GetName().c_str(), buf.size());
            }
            if (ImGui::InputText("Name", buf.data(), buf.size())) {
                _selectedEntity->SetName(buf.data());
            }

            const auto& comps = _selectedEntity->components;
            for (auto* c : comps) {
                ImGui::PushID(c);
                std::string typeName = typeid(*c).name();
                if (ImGui::TreeNodeEx("##comp", ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen,
                    "%s", typeName.c_str())) {
                    if (auto* ui = dynamic_cast<NNE::IDebugUI*>(c)) {
                        ui->DrawImGui();
                    } else {
                        ImGui::TextUnformatted("Pas d'UI pour ce composant.");
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        }
    }
    ImGui::End();
}

void UISystem::DrawViewportWindow(ImGuiID dockId) {
    ImGui::SetNextWindowDockID(dockId, ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    if (ImGui::Begin("Viewport", nullptr, flags)) {
        if (ImGui::BeginTabBar("ViewportTabs")) {
            bool sceneActive = false;
            if (ImGui::BeginTabItem("Scene")) {
                sceneActive = true;
                ImGui::TextWrapped("Scene view active. Physics and scripted time are paused.");
                ImGui::Dummy(ImGui::GetContentRegionAvail());
                ImGui::EndTabItem();
            }
            bool gameActive = false;
            if (ImGui::BeginTabItem("Game")) {
                gameActive = true;
                ImGui::TextWrapped("Game view. Use Play to start the simulation.");
                ImGui::Dummy(ImGui::GetContentRegionAvail());
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();

            bool newSceneState = sceneActive ? true : (gameActive ? false : _sceneTabActive);
            if (newSceneState != _sceneTabActive) {
                _sceneTabActive = newSceneState;
                if (_app) {
                    _app->SetSceneViewActive(_sceneTabActive);
                }
            } else if (_app && _app->IsSceneViewActive() != _sceneTabActive) {
                _app->SetSceneViewActive(_sceneTabActive);
            }
        }
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void UISystem::DrawDebugWindow(ImGuiID dockId) {
    ImGui::SetNextWindowDockID(dockId, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Debug", &showPerf)) {
        ImGuiIO& io = ImGui::GetIO();
        io.FontGlobalScale = 1.1f;

        if (ImGui::BeginTabBar("DebugTabs")) {
            if (ImGui::BeginTabItem("Performance")) {
                ImGui::Text("Frame time: %.2f ms  (%.1f FPS)", g_FrameTimeMs, g_FPS);

                static float history[120] = {};
                static int idx = 0;
                history[idx] = g_FrameTimeMs;
                idx = (idx + 1) % IM_ARRAYSIZE(history);

                ImGui::PlotLines("Frametime (ms)", history, IM_ARRAYSIZE(history), idx,
                    nullptr, 0.0f, 50.0f, ImVec2(-1, 80));

                if (_app) {
                    if (ImGui::CollapsingHeader("Application", ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        ImGui::Text("Window Size: %u * %u", _app->WIDTH, _app->HEIGHT);
                        ImGui::Text("Frame delta: %.4f", _app->GetDeltaTime());
                        ImGui::Text("Game delta: %.4f", _app->GetGameDeltaTime());
                        ImGui::Text("Play mode: %s", _app->IsPlayMode() ? "true" : "false");
                    }
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
        }
    }
    ImGui::End();
}

void UISystem::LateUpdate(float deltaTime) {
    (void)deltaTime;
}

} // namespace NNE::Systems

