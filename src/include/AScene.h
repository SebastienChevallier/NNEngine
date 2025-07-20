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

        ~AScene();


        /**
         * @brief Save the scene to a file.
         * @param path Path of the file to create.
         * @return true on success
         */
        bool Save(const std::string& path) const;

        /**
         * @brief Load entities/components from a file.
         * @param path Path of the scene file.
         * @return true on success
         */
        bool Load(const std::string& path);
    };
}


