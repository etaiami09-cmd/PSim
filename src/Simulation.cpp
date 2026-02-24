#include "Simulation.hpp"
#include <SFML/Graphics.hpp>

Simulation::Simulation(int width, int height)
	: width(width), height(height)
{
	particles = std::vector<Particle>(0);
	clock = sf::Clock();
	speed = 1;
}

void Simulation::addParticle(Particle particle)
{
	particles.push_back(particle);
}

void Simulation::update()
{
	accumulateForces(particles);
	float dt = clock.restart().asSeconds();
	dt = std::max(dt, 0.016f);
	integrate(particles, dt * speed);
	applyBoundaries(particles, width, height);
	resetForces(particles);
}

std::vector<Particle>* Simulation::getParticles()
{
	return &particles;
}
