#pragma once

#include "Particle.hpp"
#include "Physics.hpp"
#include <vector>

class Simulation {
private:
	std::vector<Particle> particles;
	sf::Clock clock;
	int width, height;
public:
	float speed;
public:
	Simulation(int width, int height);
	void addParticle(Particle particle);
	void update();
	std::vector<Particle>* getParticles();
};