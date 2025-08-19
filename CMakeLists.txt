cmake_minimum_required(VERSION 3.15...3.30)
cmake_policy(VERSION 3.15...3.30)
project(NNEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- Engine Library ----------------
file(GLOB ENGINE_SOURCES src/src/*.cpp)
file(GLOB ENGINE_HEADERS src/include/*.h)
add_library(NNEngine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(NNEngine PUBLIC src/include)

target_compile_definitions(NNEngine PUBLIC SHADER_PATH="${CMAKE_SOURCE_DIR}/src/shaders")

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(Jolt CONFIG REQUIRED)
# Try to locate nlohmann_json via package manager (e.g., vcpkg).
# If not available, fetch the header-only library from upstream.
find_package(nlohmann_json CONFIG QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found; fetching from source")
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

target_link_libraries(NNEngine PUBLIC glfw glm::glm Vulkan::Vulkan tinyobjloader::tinyobjloader Jolt::Jolt nlohmann_json::nlohmann_json)

# ---------------- Example ----------------
file(GLOB EXAMPLE_SOURCES examples/src/*.cpp)
file(GLOB EXAMPLE_HEADERS examples/include/*.h)
add_executable(GameTemplate ${EXAMPLE_SOURCES} ${EXAMPLE_HEADERS})

target_include_directories(GameTemplate PRIVATE examples/include)
target_link_libraries(GameTemplate PRIVATE NNEngine)

add_custom_command(TARGET GameTemplate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            ${CMAKE_BINARY_DIR}/assets/textures
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/textures
            ${CMAKE_BINARY_DIR}/assets/textures)

# ---------------- Tests ----------------
enable_testing()
add_executable(UnitTests tests/test_main.cpp)
target_link_libraries(UnitTests PRIVATE NNEngine)
add_test(NAME UnitTests COMMAND UnitTests)
