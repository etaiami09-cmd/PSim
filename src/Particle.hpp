#pragma once
#include <SFML/Graphics.hpp>

/*
* This class represents a single electromagnetic particle
* A particle has a position, velocity, and force
* It also has mass, radius, and charge
* to make visualization easier, this implementation also includes a color
*/
class Particle {
public:
	sf::Vector2f position, velocity, force;
	float mass, radius, charge;
public:
	Particle();
	/*
	* Simple constructor
	* Default values: velocity and force are 0, radius is 10, and the color is red
	*/
	Particle(sf::Vector2f position, float mass, float charge);
	/*
	* Retrieves the charge from a particle
	*/
	float getCharge() const;
	/*
	* Calculates the distance of a particle from another one
	*/
	float distanceFrom(const Particle &other) const;
};