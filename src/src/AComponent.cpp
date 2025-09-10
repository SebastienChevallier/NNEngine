#include "AComponent.h"
#include <atomic>

/**
 * <summary>
 * Assigne un identifiant unique au composant.
 * </summary>
 */
namespace {
std::atomic<int> g_nextComponentId{0};
}

NNE::Component::AComponent::AComponent() : _id(g_nextComponentId++) {}

/**
 * <summary>
 * Appelé lors de l'initialisation du composant.
 * </summary>
 */
void NNE::Component::AComponent::Awake()
{
}

/**
 * <summary>
 * Appelé au démarrage du composant.
 * </summary>
 */
void NNE::Component::AComponent::Start()
{
}

/**
 * <summary>
 * Met à jour le composant chaque frame.
 * </summary>
 */
void NNE::Component::AComponent::Update(float deltaTime)
{
}

/**
 * <summary>
 * Réalise les mises à jour postérieures à l'Update principal.
 * </summary>
 */
void NNE::Component::AComponent::LateUpdate(float deltaTime)
{
}

/**
 * <summary>
 * Renvoie l'identifiant du composant.
 * </summary>
 */
int NNE::Component::AComponent::GetID() const { return _id; }

/**
 * <summary>
 * Retourne l'entité attachée à ce composant.
 * </summary>
 */
NNE::AEntity* NNE::Component::AComponent::GetEntity()
{
        return _entity;
}

/**
 * <summary>
 * Définit l'entité propriétaire du composant.
 * </summary>
 */
void NNE::Component::AComponent::SetEntity(NNE::AEntity* entity)
{
        _entity = entity;
}
