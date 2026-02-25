#include "Simulation.hpp"
#include <SFML/Graphics.hpp>

Simulation::Simulation(int width, int height, int FPS)
	: width(width), height(height), FPS(FPS)
{
	particles = std::vector<Particle>(0);
	speed = 1;
	active = true;
	isPaused = std::vector<bool>(0);
}

void Simulation::addParticle(Particle particle)
{
	particles.push_back(particle);
	isPaused.push_back(false);
}

void Simulation::update()
{
	accumulateForces(particles);
	float dt = 1.0f / FPS;
	integrate(particles, dt * speed, isPaused);
	applyBoundaries(particles, width, height);
	resetForces(particles);
}

std::vector<Particle>* Simulation::getParticles()
{
	return &particles;
}
