cmake_minimum_required(VERSION 3.15)
project(NNEngine)

# Désactive la génération de ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

# Désactive ALL_BUILD
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

# Ajouter les sous-projets (le moteur et le jeu)
add_subdirectory(NoNameEngine)
add_subdirectory(NNE_GameTemplate)
