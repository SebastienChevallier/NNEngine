#include <iostream>
#include <cassert>
#include "TransformComponent.h"

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

int main()
{
    test_default_transform();
    test_parent_relationship();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
