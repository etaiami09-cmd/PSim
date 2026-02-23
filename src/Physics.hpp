#pragma once

#include "Particle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/*
* Calculates the force between 2 particles using Coloumb's formula
*/
sf::Vector2f coulombForce(const Particle &a, const Particle &b);
/*
* Calculates the total force for each particle
*/
void accumulateForces(std::vector<Particle> &particles);
/*
* Sets all forces to 0
*/
void resetForces(std::vector<Particle> &particles);
/*
* Updates particles based on time passed
*/
void integrate(std::vector<Particle> &particles, float dt);
/*
* Makes sure particles don't escape
*/
void applyBoundaries(std::vector<Particle>& particles, int width, int height);