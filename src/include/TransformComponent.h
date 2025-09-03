#pragma once
#include "AComponent.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

namespace NNE::Component {
class alignas(16) TransformComponent : public AComponent {
public:
  alignas(16) glm::vec3 position;
  alignas(16) glm::vec3 rotation; // en degrés ou radians selon votre convention
  alignas(16) glm::vec3 scale;

  TransformComponent *parent = nullptr;
  std::vector<TransformComponent *> children;

  /**
   * <summary>
   * Initialise le transform avec des valeurs par défaut.
   * </summary>
   */
  TransformComponent();

  /**
   * <summary>
   * Met à jour les transformations chaque frame.
   * </summary>
   */
  virtual void Update(float deltaTime);

  /**
   * <summary>
   * Calcule la matrice modèle de l'entité.
   * </summary>
   */
  glm::mat4 getModelMatrix() const { return getWorldMatrix(); }

  /**
   * <summary>
   * Calcule la matrice de transformation globale.
   * </summary>
   */
  glm::mat4 getWorldMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));

    model = glm::scale(model, scale); // Échelle fixe (pas d'écrasement)
    // std::cout << "scale : " << scale.x << " " << scale.y << " " << scale.z <<
    // std::endl; return model;

    if (parent)
      return parent->getWorldMatrix() * model;
    return model;
  }

  /**
   * <summary>
   * Définit un nouveau parent pour ce transform.
   * </summary>
   */
  void SetParent(TransformComponent *newParent) {
    if (parent) {
      auto &siblings = parent->children;
      siblings.erase(std::remove(siblings.begin(), siblings.end(), this),
                     siblings.end());
    }
    parent = newParent;
    if (parent)
      parent->children.push_back(this);
  }

  /**
   * <summary>
   * Obtient la position globale de l'entité.
   * </summary>
   */
  glm::vec3 GetWorldPosition() const {
    glm::mat4 world = getWorldMatrix();
    return glm::vec3(world[3]); // translation de la matrice
  }

  /**
   * <summary>
   * Retourne la direction avant dans l'espace monde.
   * </summary>
   */
  glm::vec3 GetForward() const {
    glm::mat4 world = getWorldMatrix();
    return glm::normalize(glm::vec3(world * glm::vec4(0, 0, 1, 0)));
  }

  /**
   * <summary>
   * Retourne le vecteur haut dans l'espace monde.
   * </summary>
   */
  glm::vec3 GetUp() const {
    glm::mat4 world = getWorldMatrix();
    return glm::normalize(glm::vec3(world * glm::vec4(0, 1, 0, 0)));
  }
};
} // namespace NNE::Component
