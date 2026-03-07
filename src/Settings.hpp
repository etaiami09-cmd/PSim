#pragma once
#include "Simulation.hpp"

/*
* This represents the private user settings of the user and is
* independent from any simulation data. It should be treated as a singleton
*/
struct UserSettings {
	bool vsync;
	int FPS;
	int width;
	int height;
	float speed;
};

UserSettings getDefaultSettings();

UserSettings* getUserSettings();

void setWindow(sf::RenderWindow* window);

void setSimulation(Simulation* sim);

sf::Vector2f windowToSim(sf::Vector2f& original);

sf::Vector2f simToWindow(sf::Vector2f& original);