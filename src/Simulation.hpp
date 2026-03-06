#pragma once

#include "Particle.hpp"
#include "Physics.hpp"
#include <vector>

/*
* This class represents a single particle Simulation
* It contains an FPS, width, height, speed, and a boolean flag for if it is active
* It also contains a std::vector of particles, and a std::vector of booleans
* with each boolean matching a particle and flagging if it's currently supposed to be moving
*/
class Simulation {
private:
	std::vector<Particle> particles;
	int FPS;
	int width, height;
public:
	float speed;
	bool active;
	std::vector<bool> isPaused;
public:
	/*
	* Constructor
	*/
	Simulation(int width, int height, int FPS);
	/*
	* Add a particle
	*/
	void addParticle(Particle particle);
	/*
	* Tick the simulation
	*/
	void update();
	/*
	* Get the FPS of the simulation
	*/
	int getFPS();
	int getWidth();
	/*
	* Get the width of the simulation
	*/
	int getHeight();
	/*
	* Get the height of the simulation
	*/
	float getSpeed();
	/*
	* Get pointer to the particles vector
	*/
	std::vector<Particle>* getParticles();
};