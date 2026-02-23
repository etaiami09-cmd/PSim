#pragma once
#include "Simulation.hpp"

class Renderer {
private:
	sf::RenderWindow window;
public:
	Renderer(int width, int height, std::string title);
	void draw(std::vector<Particle>* particles);
	bool isActive();
	sf::RenderWindow* getWindow();
};