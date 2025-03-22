cmake_minimum_required(VERSION 3.15)
project(NoNameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Users/schev/vcpkg/installed/x64-windows")

set(SOURCES
    src/Application.cpp
    src/VulkanManager.cpp
    src/AEntity.cpp
    src/AComponent.cpp
    src/AScene.cpp    
    src/MeshComponent.cpp
    src/TransformComponent.cpp
    src/CameraComponent.cpp
    src/PhysicsManager.cpp
    src/ColliderComponent.cpp
    src/BoxColliderComponent.cpp
    src/PlaneCollider.cpp
    src/RigidbodyComponent.cpp
    src/InputManager.cpp
)

set(HEADERS
    include/Application.h
    include/VulkanManager.h
    include/AEntity.h
    include/AComponent.h
    include/AScene.h  
    include/MeshComponent.h  
    include/TransformComponent.h  
    include/CameraComponent.h
    include/PhysicsManager.h
    include/ColliderComponent.h
    include/BoxColliderComponent.h
    include/PlaneCollider.h
    include/RigidbodyComponent.h
    include/InputManager.h
)

add_compile_definitions(SHADER_PATH="${CMAKE_SOURCE_DIR}/NoNameEngine/shaders")

# Création d'une bibliothèque statique
add_library(NoNameEngine STATIC ${SOURCES} ${HEADERS})

# Ajout des dossiers d'include pour les autres projets
target_include_directories(NoNameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Lier Vulkan, GLFW, glm, etc.
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(Jolt CONFIG REQUIRED)

target_link_libraries(NoNameEngine PUBLIC glfw glm::glm Vulkan::Vulkan tinyobjloader::tinyobjloader Jolt::Jolt)
