#include "AEntity.h"
#include "Application.h"
#include "MonoComponent.h"


/**
 * <summary>
 * Initialise l'entité avec un identifiant et un transform.
 * </summary>
 */
NNE::AEntity::AEntity()
{
        _ID = NNE::Systems::Application::GetInstance()->GenerateID();
        transform = this->AddComponent<NNE::Component::TransformComponent>();
		_Name = "Entity_" + std::to_string(_ID);
}

/**
 * <summary>
 * Détruit tous les composants attachés à l'entité.
 * </summary>
 */
NNE::AEntity::~AEntity()
{
        for (NNE::Component::AComponent* comp : NNE::AEntity::components) {
                delete comp;
        }
        components.clear();
}

/**
 * <summary>
 * Retourne l'identifiant de l'entité.
 * </summary>
 */
int NNE::AEntity::GetID()
{

        return _ID;
}

/**
 * <summary>
 * Renvoie le nom attribué à l'entité.
 * </summary>
 */
std::string NNE::AEntity::GetName()
{
        return _Name;
}

void NNE::AEntity::SetName(const std::string& name)
{
	_Name = name;
}

/**
 * <summary>
 * Appelle Awake sur chaque composant.
 * </summary>
 */
void NNE::AEntity::Awake()
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        component->Awake();
                }
        }
}

/**
 * <summary>
 * Appelle Start sur tous les composants.
 * </summary>
 */
void NNE::AEntity::Start()
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        component->Start();
                }
        }
}

/**
 * <summary>
 * Met à jour les composants non mono chaque frame.
 * </summary>
 */
void NNE::AEntity::Update(float delta)
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        if (!dynamic_cast<NNE::Component::MonoComponent*>(component))
                                component->Update(delta);
                }
        }
}

/**
 * <summary>
 * Exécute les mises à jour tardives des composants non mono.
 * </summary>
 */
void NNE::AEntity::LateUpdate(float delta)
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        if (!dynamic_cast<NNE::Component::MonoComponent*>(component))
                                component->LateUpdate(delta);
                }
        }
}
