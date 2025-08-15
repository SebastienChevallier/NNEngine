#pragma once

#include <vector>
#include <string>

#include "AEntity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"

namespace NNE {

    /**
     * @brief Very small scene container able to serialize and deserialize
     *        entities and a subset of components in a JSON style format.
     */
    class AScene
    {
    public:
        std::vector<AEntity*> entities;

        /**
         * <summary>
         * Détruit la scène et libère ses entités.
         * </summary>
         */
        ~AScene();

        /**
         * <summary>
         * Sauvegarde la scène dans un fichier.
         * </summary>
         */
        bool Save(const std::string& path) const;

        /**
         * <summary>
         * Charge la scène depuis un fichier.
         * </summary>
         */
        bool Load(const std::string& path);
    };
}


