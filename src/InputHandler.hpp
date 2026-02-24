#pragma once

#include "Simulation.hpp"

/*
* This method handles keyboard and mouse inputs to the program
* Escape key - program shuts down
* Right or Left click on your mouse - spawn a particle
*/
void handleEvents(sf::RenderWindow* window, Simulation& simulation);