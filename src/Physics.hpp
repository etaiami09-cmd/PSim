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
void integrate(std::vector<Particle> &particles, float dt, std::vector<bool> &isPaused);
/*
* Makes sure particles don't escape
*/
void applyBoundaries(std::vector<Particle>& particles, int width, int height);
/*
* Calculates the total electrical field vector from all particles relative to a position
* Returns unit is N/C
*/
sf::Vector2f electricField(std::vector<Particle>& particles, sf::Vector2f position);
/*
* Calculates the lorentz force on a particle
*/
sf::Vector2f lorentzForce(const Particle& a);