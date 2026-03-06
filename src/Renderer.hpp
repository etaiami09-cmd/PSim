#pragma once
#include "Simulation.hpp"

/*
* This class represents a Renderer object
* It contains a sf::RenderWindow, a clock, a font,
* a std::vector of floats to calculate average FPS,
* and a few other variables for keeping track of the FPS display
* It should handle all interactions with the simulation window
*/
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
	/*
	* Preferred constructor
	*/
	Renderer(int width, int height, std::string title);
	/*
	* Renders the particles
	*/
	void drawParticles(std::vector<Particle>* particles);
	/*
	* Checks if the window has been closed
	*/
	bool isActive();
	/*
	* Returns the pointer to the window
	*/
	sf::RenderWindow* getWindow();
	/*
	* Gets the time difference between now and the last time the function was called
	*/
	float getDelta();
	/*
	* Draws current FPS
	*/
	void drawFPS(std::vector<Particle>* particles);
	/*
	* Draws electric field arrows
	*/
	void drawForceArrows(std::vector<Particle>* particles);
	/*
	* Draws the pause menu
	*/
	void drawPauseMenu();
};