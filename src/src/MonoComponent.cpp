#include "MonoComponent.h"

/**
 * <summary>
 * Initialisation spécifique du script mono.
 * </summary>
 */
void NNE::Component::MonoComponent::Awake()
{

}

/**
 * <summary>
 * Exécuté au démarrage du script mono.
 * </summary>
 */
void NNE::Component::MonoComponent::Start()
{
}

/**
 * <summary>
 * Met à jour le script mono à chaque frame.
 * </summary>
 */
void NNE::Component::MonoComponent::Update(float deltaTime)
{
}

/**
 * <summary>
 * Effectue les mises à jour tardives du script mono.
 * </summary>
 */
void NNE::Component::MonoComponent::LateUpdate(float deltaTime)
{
}

/**
 * <summary>
 * Appelé lorsqu'une collision physique est détectée.
 * </summary>
 */
void NNE::Component::MonoComponent::OnHit(NNE::Component::Physics::ColliderComponent* other)
{
}

/**
 * <summary>
 * Appelé lorsqu'une collision de type trigger est détectée.
 * </summary>
 */
void NNE::Component::MonoComponent::OnTriggerHit(NNE::Component::Physics::ColliderComponent* other)
{
}
