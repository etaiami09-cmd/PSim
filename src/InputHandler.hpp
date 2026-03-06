#pragma once

#include "Simulation.hpp"

/*
* Handles all input events
* Escape key: exit program
* Right click: create positive particle
* Left click: create negative particle
* Up key: increase simulation speed
* Down key: decrease simulation speed
* Space key: pause/resume simulation
* Left shift: pause particles your mouse is hovering on
* Crtl + S: save simulation state to file
* Ctrl + O: open simulation state from file
*/
void handleEvents(sf::RenderWindow* window, Simulation& simulation);