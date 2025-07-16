cmake_minimum_required(VERSION 3.15)
project(NNEngine)

# Disable regeneration target
set(CMAKE_SUPPRESS_REGENERATION true)

# Disable ALL_BUILD
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

# Add subprojects
add_subdirectory(NoNameEngine)
add_subdirectory(NNE_GameTemplate)

# Enable tests
enable_testing()
add_subdirectory(NoNameEngine/test)
