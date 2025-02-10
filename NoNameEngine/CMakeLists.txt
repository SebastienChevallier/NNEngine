cmake_minimum_required(VERSION 3.15)
project(NoNameEngine)

# Intégration avec VCPKG
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SUPPRESS_REGENERATION ON)
set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")
set(glfw3_DIR "C:/vcpkg/installed/x64-windows/share/glfw3")

# Inclure les sources et en-têtes
set(SOURCES
    src/main.cpp
    src/VulkanManager.cpp
    src/Application.cpp
    src/AEntity.cpp
    src/AComponent.cpp
    src/AScene.cpp    
    src/MeshComponent.cpp
)


set(HEADERS
    include/VulkanManager.h
    include/Application.h
    include/AComponent.h
    include/AEntity.h
    include/AScene.h  
    include/MeshComponent.h  
)

# Créer l'exécutable
add_executable(NoNameEngine ${SOURCES} ${HEADERS})

# Ajouter les répertoires d'inclusion
target_include_directories(NoNameEngine PRIVATE include)

# Lier les dépendances avec VCPKG
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
#find_package(stb CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

target_include_directories(NoNameEngine PRIVATE ${VCPKG_ROOT}/installed/x64-windows/include)

target_link_libraries(NoNameEngine PRIVATE glfw glm::glm Vulkan::Vulkan tinyobjloader::tinyobjloader)

#enable_testing()

#add_executable(TestApp test/test_main.cpp)
#target_link_libraries(TestApp PRIVATE glfw glm::glm Vulkan::Vulkan)
#add_test(NAME TestApp COMMAND TestApp)