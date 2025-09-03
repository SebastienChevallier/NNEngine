#include "AComponent.h"
#include "AEntity.h"
#include "AScene.h"
#include "Application.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "PlaneCollider.h"
#include "RigidbodyComponent.h"
#include <cassert>
#include <cstdio>
#include <glm/gtc/epsilon.hpp>
#include <iostream>

static void test_default_transform() {
  NNE::Component::TransformComponent t;
  assert(t.position == glm::vec3(0.0f));
  assert(t.rotation == glm::vec3(0.0f));
  assert(t.scale == glm::vec3(1.0f, 1.0f, 1.0f));
}

static void test_parent_relationship() {
  NNE::Component::TransformComponent parent;
  NNE::Component::TransformComponent child;
  child.SetParent(&parent);
  assert(child.parent == &parent);
  assert(parent.children.size() == 1);
  assert(parent.children[0] == &child);
}

static void test_transform_directions() {
  NNE::Component::TransformComponent t;
  glm::vec3 forward = t.GetForward();
  glm::vec3 up = t.GetUp();
  assert(glm::all(glm::epsilonEqual(forward, glm::vec3(0, 0, 1), 0.0001f)));
  assert(glm::all(glm::epsilonEqual(up, glm::vec3(0, 1, 0), 0.0001f)));
}

static void test_world_position() {
  NNE::Component::TransformComponent parent;
  parent.position = glm::vec3(1.0f, 2.0f, 3.0f);
  NNE::Component::TransformComponent child;
  child.position = glm::vec3(1.0f, 0.0f, 0.0f);
  child.SetParent(&parent);
  glm::vec3 worldPos = child.GetWorldPosition();
  assert(glm::all(
      glm::epsilonEqual(worldPos, glm::vec3(2.0f, 2.0f, 3.0f), 0.0001f)));
}

static void test_mesh_component_paths() {
  NNE::Component::Render::MeshComponent m;
  m.SetModelPath("model.obj");
  m.SetTexturePath("texture.png");
  assert(m.GetModelPath() == "model.obj");
  assert(m.GetTexturePath() == "texture.png");
}

static void test_camera_perspective() {
  NNE::Component::Render::CameraComponent c;
  c.SetPerspective(60.0f, 4.0f / 3.0f, 0.1f, 200.0f);
  assert(c.GetFOV() == 60.0f);
  assert(c.GetAspectRatio() == 4.0f / 3.0f);
  assert(c.GetNearPlane() == 0.1f);
  assert(c.GetFarPlane() == 200.0f);
}

static void test_entity_component_management() {
  NNE::AEntity e;
  NNE::Component::Render::MeshComponent *mc =
      e.AddComponent<NNE::Component::Render::MeshComponent>();
  assert(mc->GetEntity() == &e);
  assert(e.GetComponent<NNE::Component::Render::MeshComponent>() == mc);
}

static void test_get_components_multiple() {
  NNE::AEntity e;
  e.AddComponent<NNE::Component::Render::MeshComponent>();
  e.AddComponent<NNE::Component::Render::MeshComponent>();
  auto meshes = e.GetComponents<NNE::Component::Render::MeshComponent>();
  assert(meshes.size() == 2);
  for (auto *m : meshes) {
    assert(m->GetEntity() == &e);
  }
}

static void test_application_id_increment() {
  int id1 = NNE::Systems::Application::GetInstance()->GenerateID();
  int id2 = NNE::Systems::Application::GetInstance()->GenerateID();
  assert(id2 == id1 + 1);
}

static void test_model_matrix_translation() {
  NNE::Component::TransformComponent t;
  t.position = glm::vec3(1.0f, 2.0f, 3.0f);
  glm::mat4 mat = t.getModelMatrix();
  glm::vec3 trans(mat[3]);
  assert(
      glm::all(glm::epsilonEqual(trans, glm::vec3(1.0f, 2.0f, 3.0f), 0.0001f)));
}

static void test_plane_collider_awake_creates_shape() {
  NNE::AEntity e;
  auto *pc = e.AddComponent<NNE::Component::Physics::PlaneCollider>(
      glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
  pc->Awake();
  assert(pc->GetShape().GetPtr() != nullptr);
}

static void test_rigidbody_awake_initializes_collider() {
  NNE::AEntity e;
  auto *rb = e.AddComponent<NNE::Component::Physics::RigidbodyComponent>();
  auto *pc = e.AddComponent<NNE::Component::Physics::PlaneCollider>(
      glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
  rb->Awake();
  assert(pc->GetShape().GetPtr() != nullptr);
}

static void test_scene_serialization() {
  NNE::AScene scene;

  NNE::AEntity *e1 = new NNE::AEntity();
  e1->transform->position = glm::vec3(1.0f, 2.0f, 3.0f);
  NNE::Component::Render::MeshComponent *m1 =
      e1->AddComponent<NNE::Component::Render::MeshComponent>();
  m1->SetModelPath("model1.obj");
  m1->SetTexturePath("texture1.png");
  scene.entities.push_back(e1);

  NNE::AEntity *e2 = new NNE::AEntity();
  e2->transform->position = glm::vec3(4.0f, 5.0f, 6.0f);
  scene.entities.push_back(e2);

  bool saved = scene.Save("test_scene.json");
  assert(saved);

  NNE::AScene loaded;
  bool loadedOk = loaded.Load("test_scene.json");
  assert(loadedOk);
  assert(loaded.entities.size() == 2);

  auto *lt1 =
      loaded.entities[0]->GetComponent<NNE::Component::TransformComponent>();
  auto *lm1 =
      loaded.entities[0]->GetComponent<NNE::Component::Render::MeshComponent>();
  assert(lt1 && lm1);
  assert(glm::all(
      glm::epsilonEqual(lt1->position, glm::vec3(1.0f, 2.0f, 3.0f), 0.0001f)));
  assert(lm1->GetModelPath() == "model1.obj");
  assert(lm1->GetTexturePath() == "texture1.png");

  auto *lt2 =
      loaded.entities[1]->GetComponent<NNE::Component::TransformComponent>();
  assert(lt2);
  assert(glm::all(
      glm::epsilonEqual(lt2->position, glm::vec3(4.0f, 5.0f, 6.0f), 0.0001f)));

  std::remove("test_scene.json");
}

int main() {
  NNE::Systems::Application app;
  test_application_id_increment();
  test_default_transform();
  test_parent_relationship();
  test_transform_directions();
  test_world_position();
  test_model_matrix_translation();
  test_scene_serialization();
  test_mesh_component_paths();
  test_camera_perspective();
  test_entity_component_management();
  test_get_components_multiple();
  test_rigidbody_awake_initializes_collider();
  test_plane_collider_awake_creates_shape();
  std::cout << "All tests passed" << std::endl;
  return 0;
}
