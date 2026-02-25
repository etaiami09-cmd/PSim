#pragma once

#include "Particle.hpp"
#include "Physics.hpp"
#include <vector>

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
	Simulation(int width, int height, int FPS);
	void addParticle(Particle particle);
	void update();
	std::vector<Particle>* getParticles();
};