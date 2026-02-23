cmake_minimum_required(VERSION 3.20)
project(PSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(PSim ${SOURCES} "src/Particle.cpp" "src/Physics.cpp" "src/Constants.hpp" "src/Simulation.cpp" "src/Renderer.cpp" "src/InputHandler.cpp")

target_include_directories(PSim PRIVATE src)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(PSim PRIVATE SFML::Graphics SFML::Window SFML::System)

target_include_directories(PSim PRIVATE 
    src
    C:/dev/vcpkg/installed/x64-windows/include
)