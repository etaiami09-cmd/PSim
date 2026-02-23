#include "Particle.hpp"
#include <cmath>

Particle::Particle(sf::Vector2f position, float mass, float charge)
	: position(position), mass(mass), charge(charge)
{
	this->velocity = sf::Vector2f();
	this->force = sf::Vector2f();
	this->radius = 10;
}

float Particle::getCharge() const {
	return this->charge;
}

float Particle::distanceFrom(const Particle &other) const {
	return hypot(this->position.x - other.position.x, this->position.y - other.position.y);
}

Particle::Particle()
	: charge(0), radius(0), mass(0) {};