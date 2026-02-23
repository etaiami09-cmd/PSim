#include "Physics.hpp"
#include "Constants.hpp"
#include <cmath>

float max(float a, float b) {
	return (a > b) ? a : b;
}
float min(float a, float b) {
	return (a < b) ? a : b;
}

sf::Vector2f coulombForce(const Particle &a, const Particle &b)
{
	float distance = a.distanceFrom(b);
	if (distance < 20.0f) return { 0, 0 };
	sf::Vector2f delta = a.position - b.position;
	float sigmaF = Consts::K * (a.getCharge() * b.getCharge()) / (powf(distance, 2));
	float fX = sigmaF * cosf(delta.angle().asRadians());
	float fY = sigmaF * sinf(delta.angle().asRadians());
	return sf::Vector2f{ fX, fY };
}

void accumulateForces(std::vector<Particle> &particles)
{
	for (int i = 0; i < particles.size(); i++) {
		for (int j = 0; j < particles.size(); j++) {
			if (i != j) {
				particles[i].force += coulombForce(particles[i], particles[j]);
			}
		}
	}
}

void resetForces(std::vector<Particle> &particles)
{
	for (Particle &particle : particles) {
		particle.force = {0, 0};
	}
}

void integrate(std::vector<Particle> &particles, float dt)
{
	for (Particle& particle : particles) {
		particle.velocity.x += (particle.force.x / particle.mass) * dt*0.9f;
		particle.velocity.y += (particle.force.y / particle.mass) * dt*0.9f;
		particle.position += particle.velocity * dt;
	}
}

void applyBoundaries(std::vector<Particle> &particles, int width, int height)
{
	for (Particle& particle : particles) {
		//particle.position.x = max(0, particle.position.x);
		//particle.position.x = min(width-particle.radius*2, particle.position.x);
		//particle.position.y = max(0, particle.position.y);
		//particle.position.y = min(height-particle.radius*2, particle.position.y);
		//particle.velocity.x = (particle.position.x <= 0 || particle.position.x >= width-particle.radius*2)
		//	? -particle.velocity.x : particle.velocity.x;
		//particle.velocity.y = (particle.position.y <= 0 || particle.position.y >= height-particle.radius*2)
		//	? -particle.velocity.y : particle.velocity.y;
		if (particle.position.x <= 0) {
			particle.position.x = 0;
			particle.velocity.x = std::abs(particle.velocity.x);
		}
		else if (particle.position.x >= width - particle.radius * 2) {
			particle.position.x = width - particle.radius * 2;
			particle.velocity.x = -std::abs(particle.velocity.x);
		}

		if (particle.position.y <= 0) {
			particle.position.y = 0;
			particle.velocity.y = std::abs(particle.velocity.y);
		}
		else if (particle.position.y >= height - particle.radius * 2) {
			particle.position.y = height - particle.radius * 2;
			particle.velocity.y = -std::abs(particle.velocity.y);
		}
	}
}
