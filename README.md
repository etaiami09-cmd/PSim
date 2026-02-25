# C++ Particle Simulator
## Idea
* I want to make a 2D particle simulator in C++ using SFML
* The focus of this simulator will be on electromagnetism
* Particles will have position, velocity, mass, and a charge
* You will be able to add particles
* Basic GUI 
## Current Features
* 2D particle simulator opens with a 800x600 window
* right click spawns positive particles, left click spawns negatives
* particles obey Coulomb's law & Lorentz force
* FPS + Particle Count HUD
* Electric field lines
* Press up/down to increase/decrease simulation speed
* Pause simulation with Space key
## Installation Guidelines
### Requirements
* Visual Studio 2022
* MSVS Desktop Development with C++ workload
* CMake 3.20 or later
* vcpkg
* Git
### Setup
#### Clone Repository
```
git clone https://github.com/etaiami09-cmd/PSim.git
cd PSim
```
#### Install vcpkg and SFML
```
* git clone https://github.com/microsoft/vcpkg.git C:/dev/vcpkg
* C:/dev/vcpkg/bootstrap-vcpkg.bat
* C:/dev/vcpkg/vcpkg install sfml
* C:/dev/vcpkg/vcpkg integrate install
```
#### Configure and build
```
mkdir out/build
cd out/build
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
```
### Run
```
./PSim.exe
```