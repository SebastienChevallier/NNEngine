cmake_minimum_required(VERSION 3.15)
project(NNE_GameTemplate)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/Main.cpp
    src/PlayerController.cpp
)

set(HEADERS
    include/PlayerController.h
)

add_executable(NNE_GameTemplate ${SOURCES} ${HEADERS})

target_link_libraries(NNE_GameTemplate PRIVATE NoNameEngine)

target_include_directories(NNE_GameTemplate PRIVATE ${CMAKE_SOURCE_DIR}/NNE_GameTemplate/include)

# Copy assets next to the executable so relative paths like "../assets" work
add_custom_command(TARGET NNE_GameTemplate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
