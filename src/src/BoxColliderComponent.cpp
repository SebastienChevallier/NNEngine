#include "BoxColliderComponent.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Application.h>

NNE::BoxColliderComponent::BoxColliderComponent(const glm::vec3& size) : size(size)
{
	
}

void NNE::BoxColliderComponent::Awake()
{
	CreateShape();  // Maintenant le système physique est prêt
}

void NNE::BoxColliderComponent::CreateShape()
{
	shape = new JPH::BoxShape(JPH::Vec3(size.x, size.y, size.z));

	JPH::BodyCreationSettings bodySettings(shape, JPH::RVec3::sZero(), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, 0);
	auto& bodyInterface = NNE::Application::GetInstance()->physicsManager->GetPhysicsSystem()->GetBodyInterface();
	bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

	Application::GetInstance()->RegisterCollider(bodyID, this);
}

//void NNE::BoxColliderComponent::OnHit(ColliderComponent* other)
//{
//	std::cout << "Collision avec : " << typeid(*other).name() << std::endl;
//}
//
//void NNE::BoxColliderComponent::OnTriggerHit(ColliderComponent* other)
//{
//	std::cout << "Trigger avec : " << typeid(*other).name() << std::endl;
//}
