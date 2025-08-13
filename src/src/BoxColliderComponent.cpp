#include "BoxColliderComponent.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include "Application.h"

NNE::Component::Physics::BoxColliderComponent::BoxColliderComponent(const glm::vec3& size) : size(size)
{
}

void NNE::Component::Physics::BoxColliderComponent::Awake()
{
        CreateShape();
}

void NNE::Component::Physics::BoxColliderComponent::CreateShape()
{
        shape = new JPH::BoxShape(JPH::Vec3(size.x, size.y, size.z));

        JPH::BodyCreationSettings bodySettings(shape, JPH::RVec3::sZero(), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, 0);
        auto& bodyInterface = NNE::Systems::Application::GetInstance()->physicsManager->GetPhysicsSystem()->GetBodyInterface();
        bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

        NNE::Systems::Application::GetInstance()->RegisterCollider(bodyID, this);
}
