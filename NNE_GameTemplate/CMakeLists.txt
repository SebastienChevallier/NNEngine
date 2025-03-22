cmake_minimum_required(VERSION 3.15)
project(NNE_GameTemplate)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/PlayerController.cpp
)

set(HEADERS
    include/PlayerController.h
)

add_executable(NNE_GameTemplate ${SOURCES} ${HEADERS})

target_link_libraries(NNE_GameTemplate PRIVATE NoNameEngine)

target_include_directories(NNE_GameTemplate PRIVATE ${CMAKE_SOURCE_DIR}/NNE_GameTemplate/include)