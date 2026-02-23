#pragma once
#include "Simulation.hpp"

class Renderer {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Font font;
	std::vector<float> frameTimes;
	int frameIndex;
	int displayedFPS;
	int frameCount;
public:
	Renderer(int width, int height, std::string title);
	void drawParticles(std::vector<Particle>* particles);
	bool isActive();
	sf::RenderWindow* getWindow();
	float getDelta();
	void drawFPS(std::vector<Particle>* particles);
};