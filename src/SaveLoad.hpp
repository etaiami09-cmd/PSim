#pragma once

#include <string>
#include "Simulation.hpp"

/*
* This struct represents all the information about a particle that
* is needed to retrieve its exact current state
* Specifically, force is not needed because it is recalculated every
* frame anyway
*/
struct CompressedParticle {
	float posX, posY, velX, velY;
	float mass, radius, charge;
	/*
	* Basic constructor from a normal particle
	*/
	CompressedParticle(Particle& particle);
	/*
	* Empty constructor
	*/
	CompressedParticle() = default;
	/*
	* Convert back to normal particle object
	*/
	Particle toParticle();
};

/*
* This struct contains all the metadata for a simulation
* When saving or opening a simulation state file, this will reinterpret-casted
* into or from the header of the file
*/
struct SimulationMetadata {
	int particleCount;
	int width, height, FPS;
	float speed;
};

/*
* Get simulation from file path
*/
Simulation openFrom(std::string path);

/*
* Asks the user to select a path to open a simulation state file
*/
std::string promptOpenPath();

/*
* Asks the user to select a path to save a simulation state file
*/
std::string promptSavePath();

/*
* Save a simulation to a file
*/
void saveToPath(std::string path, Simulation& simulation);