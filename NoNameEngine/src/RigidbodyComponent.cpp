#include "RigidBodyComponent.h"
#include "Application.h"
#include "TransformComponent.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h> 

namespace NNE {

    RigidbodyComponent::RigidbodyComponent(float mass, bool kinematic)
        : bodyID(), mass(mass), isKinematic(kinematic) {
    }

    RigidbodyComponent::~RigidbodyComponent() {
        auto physicsSystem = Application::GetInstance()->physicsManager->GetPhysicsSystem();
        if (!bodyID.IsInvalid()) {
            physicsSystem->GetBodyInterface().RemoveBody(bodyID);
        }
    }

    void RigidbodyComponent::Awake() {
        std::cout << "RigidBodyAwake" << std::endl;
        auto physicsSystem = Application::GetInstance()->physicsManager->GetPhysicsSystem();
        auto* transform = GetEntity()->GetComponent<TransformComponent>();
        auto* collider = GetEntity()->GetComponent<ColliderComponent>();

        if (!collider || !collider->GetShape()) {
            std::cerr << "ColliderComponent manquant ou invalide sur l'entité." << std::endl;
            return;
        }

        
        JPH::BodyCreationSettings bodySettings(
            collider->GetShape(),
            JPH::RVec3(transform->position.x, transform->position.y, transform->position.z),
            JPH::Quat::sIdentity(),
            (mass > 0.0f) ? JPH::EMotionType::Dynamic : (isKinematic ? JPH::EMotionType::Kinematic : JPH::EMotionType::Static),
            0 
        );

        
        if (mass > 0.0f) {
            bodySettings.mMassPropertiesOverride.mMass = mass;
        }

        
        JPH::BodyInterface& bodyInterface = physicsSystem->GetBodyInterface();
        bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

        
        if (bodyID.IsInvalid()) {
            std::cerr << "❌ Échec de la création du RigidBody !" << std::endl;
            return;
        }
    }

    void RigidbodyComponent::Update(float deltaTime) {
        
        auto physicsSystem = Application::GetInstance()->physicsManager->GetPhysicsSystem();
        auto& bodyInterface = physicsSystem->GetBodyInterface();
        //std::cout << bodyID.IsInvalid() << std::endl;
        if (!bodyID.IsInvalid()) {
            auto* transform = GetEntity()->GetComponent<TransformComponent>();

            JPH::RVec3 pos = bodyInterface.GetPosition(bodyID);
            JPH::Quat rot = bodyInterface.GetRotation(bodyID);

            transform->position = glm::vec3(pos.GetX(), pos.GetY(), pos.GetZ());
            std::cout << pos.GetY() << std::endl;

            // 🔥 Correction : Convertir le quaternion en Euler angles
            glm::quat glmQuat(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ());
            glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(glmQuat));

            transform->rotation = eulerAngles;
        }
    }

    JPH::BodyID RigidbodyComponent::GetBodyID() const {
        return bodyID;
    }

}