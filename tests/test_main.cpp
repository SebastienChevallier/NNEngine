#include <iostream>
#include <cassert>
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "AEntity.h"
#include "AComponent.h"

static void test_default_transform()
{
    NNE::TransformComponent t;
    assert(t.position == glm::vec3(0.0f));
    assert(t.rotation == glm::vec3(0.0f));
    assert(t.scale == glm::vec3(1.0f, 1.0f, 1.0f));
}

static void test_parent_relationship()
{
    NNE::TransformComponent parent;
    NNE::TransformComponent child;
    child.SetParent(&parent);
    assert(child.parent == &parent);
    assert(parent.children.size() == 1);
    assert(parent.children[0] == &child);
}

static void test_transform_directions()
{
    NNE::TransformComponent t;
    glm::vec3 forward = t.GetForward();
    glm::vec3 up = t.GetUp();
    assert(glm::all(glm::epsilonEqual(forward, glm::vec3(0, 0, -1), 0.0001f)));
    assert(glm::all(glm::epsilonEqual(up, glm::vec3(0, 1, 0), 0.0001f)));
}

static void test_world_position()
{
    NNE::TransformComponent parent;
    parent.position = glm::vec3(1.0f, 2.0f, 3.0f);
    NNE::TransformComponent child;
    child.position = glm::vec3(1.0f, 0.0f, 0.0f);
    child.SetParent(&parent);
    glm::vec3 worldPos = child.GetWorldPosition();
    assert(glm::all(glm::epsilonEqual(worldPos, glm::vec3(2.0f, 2.0f, 3.0f), 0.0001f)));
}

static void test_mesh_component_paths()
{
    NNE::MeshComponent m;
    m.SetModelPath("model.obj");
    m.SetTexturePath("texture.png");
    assert(m.GetModelPath() == "model.obj");
    assert(m.GetTexturePath() == "texture.png");
}

static void test_camera_perspective()
{
    NNE::CameraComponent c;
    c.SetPerspective(60.0f, 4.0f/3.0f, 0.1f, 200.0f);
    assert(c.GetFOV() == 60.0f);
    assert(c.GetAspectRatio() == 4.0f/3.0f);
    assert(c.GetNearPlane() == 0.1f);
    assert(c.GetFarPlane() == 200.0f);
}

static void test_entity_component_management()
{
    NNE::AEntity e;
    NNE::MeshComponent* mc = e.AddComponent<NNE::MeshComponent>();
    assert(mc->GetEntity() == &e);
    assert(e.GetComponent<NNE::MeshComponent>() == mc);
}

int main()
{
    test_default_transform();
    test_parent_relationship();
    test_transform_directions();
    test_world_position();
    test_mesh_component_paths();
    test_camera_perspective();
    test_entity_component_management();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
