cmake_minimum_required(VERSION 3.15)
project(NNE_GameTemplate)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
)

# Cr�er l'ex�cutable du jeu
add_executable(NNE_GameTemplate ${SOURCES})

# Indiquer que NNE_GameTemplate d�pend de NoNameEngine
target_link_libraries(NNE_GameTemplate PRIVATE NoNameEngine)

# Ajouter le dossier include du moteur pour que le jeu trouve les headers
target_include_directories(NNE_GameTemplate PRIVATE ../NoNameEngine/include)