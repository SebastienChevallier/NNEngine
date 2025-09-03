#include "AComponent.h"
#include "AEntity.h"
#include "AScene.h"
#include "Application.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "PlaneCollider.h"
#include "RigidbodyComponent.h"
#include <cstdio>
#include <glm/gtc/epsilon.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

// Simple assertion macro that throws on failure so tests can continue
#define EXPECT_TRUE(cond)                                                        \
  do {                                                                          \
    if (!(cond))                                                                \
      throw std::runtime_error("Expectation failed: " #cond);                  \
  } while (0)

static void test_default_transform() {
  NNE::Component::TransformComponent t;
  EXPECT_TRUE(t.position == glm::vec3(0.0f));
  EXPECT_TRUE(t.rotation == glm::vec3(0.0f));
  EXPECT_TRUE(t.scale == glm::vec3(1.0f, 1.0f, 1.0f));
}

static void test_parent_relationship() {
  NNE::Component::TransformComponent parent;
  NNE::Component::TransformComponent child;
  child.SetParent(&parent);
  EXPECT_TRUE(child.parent == &parent);
  EXPECT_TRUE(parent.children.size() == 1);
  EXPECT_TRUE(parent.children[0] == &child);
}

static void test_transform_directions() {
  NNE::Component::TransformComponent t;
  glm::vec3 forward = t.GetForward();
  glm::vec3 up = t.GetUp();
  EXPECT_TRUE(
      glm::all(glm::epsilonEqual(forward, glm::vec3(0, 0, 1), 0.0001f)));
  EXPECT_TRUE(
      glm::all(glm::epsilonEqual(up, glm::vec3(0, 1, 0), 0.0001f)));
}

static void test_world_position() {
  NNE::Component::TransformComponent parent;
  parent.position = glm::vec3(1.0f, 2.0f, 3.0f);
  NNE::Component::TransformComponent child;
  child.position = glm::vec3(1.0f, 0.0f, 0.0f);
  child.SetParent(&parent);
  glm::vec3 worldPos = child.GetWorldPosition();
  EXPECT_TRUE(glm::all(
      glm::epsilonEqual(worldPos, glm::vec3(2.0f, 2.0f, 3.0f), 0.0001f)));
}

static void test_mesh_component_paths() {
  NNE::Component::Render::MeshComponent m;
  m.SetModelPath("model.obj");
  m.SetTexturePath("texture.png");
  EXPECT_TRUE(m.GetModelPath() == "model.obj");
  EXPECT_TRUE(m.GetTexturePath() == "texture.png");
}

static void test_camera_perspective() {
  NNE::Component::Render::CameraComponent c;
  c.SetPerspective(60.0f, 4.0f / 3.0f, 0.1f, 200.0f);
  EXPECT_TRUE(c.GetFOV() == 60.0f);
  EXPECT_TRUE(c.GetAspectRatio() == 4.0f / 3.0f);
  EXPECT_TRUE(c.GetNearPlane() == 0.1f);
  EXPECT_TRUE(c.GetFarPlane() == 200.0f);
}

static void test_entity_component_management() {
  NNE::AEntity e;
  NNE::Component::Render::MeshComponent *mc =
      e.AddComponent<NNE::Component::Render::MeshComponent>();
  EXPECT_TRUE(mc->GetEntity() == &e);
  EXPECT_TRUE(e.GetComponent<NNE::Component::Render::MeshComponent>() == mc);
}

static void test_get_components_multiple() {
  NNE::AEntity e;
  e.AddComponent<NNE::Component::Render::MeshComponent>();
  e.AddComponent<NNE::Component::Render::MeshComponent>();
  auto meshes = e.GetComponents<NNE::Component::Render::MeshComponent>();
  EXPECT_TRUE(meshes.size() == 2);
  for (auto *m : meshes) {
    EXPECT_TRUE(m->GetEntity() == &e);
  }
}

static void test_application_id_increment() {
  int id1 = NNE::Systems::Application::GetInstance()->GenerateID();
  int id2 = NNE::Systems::Application::GetInstance()->GenerateID();
  EXPECT_TRUE(id2 == id1 + 1);
}

static void test_model_matrix_translation() {
  NNE::Component::TransformComponent t;
  t.position = glm::vec3(1.0f, 2.0f, 3.0f);
  glm::mat4 mat = t.getModelMatrix();
  glm::vec3 trans(mat[3]);
  EXPECT_TRUE(glm::all(
      glm::epsilonEqual(trans, glm::vec3(1.0f, 2.0f, 3.0f), 0.0001f)));
}

static void test_plane_collider_awake_creates_shape() {
  NNE::AEntity e;
  auto *pc = e.AddComponent<NNE::Component::Physics::PlaneCollider>(
      glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
  pc->Awake();
  EXPECT_TRUE(pc->GetShape().GetPtr() != nullptr);
}

static void test_rigidbody_awake_initializes_collider() {
  NNE::AEntity e;
  auto *rb = e.AddComponent<NNE::Component::Physics::RigidbodyComponent>();
  auto *pc = e.AddComponent<NNE::Component::Physics::PlaneCollider>(
      glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
  rb->Awake();
  EXPECT_TRUE(pc->GetShape().GetPtr() != nullptr);
}



int main() {
  NNE::Systems::Application app;
  struct TestCase {
    const char *name;
    void (*func)();
  };
  std::vector<TestCase> tests = {
      {"application_id_increment", test_application_id_increment},
      {"default_transform", test_default_transform},
      {"parent_relationship", test_parent_relationship},
      {"transform_directions", test_transform_directions},
      {"world_position", test_world_position},
      {"model_matrix_translation", test_model_matrix_translation},
      {"mesh_component_paths", test_mesh_component_paths},
      {"camera_perspective", test_camera_perspective},
      {"entity_component_management", test_entity_component_management},
      {"get_components_multiple", test_get_components_multiple},
      {"rigidbody_awake_initializes_collider",
       test_rigidbody_awake_initializes_collider},
      {"plane_collider_awake_creates_shape",
       test_plane_collider_awake_creates_shape},
  };

  int failed = 0;
  for (const auto &t : tests) {
    try {
      t.func();
      std::cout << "[PASS] " << t.name << std::endl;
    } catch (const std::exception &e) {
      failed++;
      std::cout << "[FAIL] " << t.name << ": " << e.what() << std::endl;
    }
  }

  if (failed == 0) {
    std::cout << "All tests passed" << std::endl;
  } else {
    std::cout << failed << " tests failed" << std::endl;
  }
  return failed == 0 ? 0 : 1;
}
