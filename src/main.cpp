#include "Constants.hpp"
#include "Particle.hpp"
#include "Physics.hpp"
#include "Simulation.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "external_libraries/tinyfiledialogs.h"

const int width = 800;
const int height = 600;
const int FPS = 60;

int main() {
	// set up stack
	Simulation simulation(width, height, FPS);
	Renderer renderer(width, height, "Electromagnetism Simulator");
	sf::RenderWindow* window = renderer.getWindow();
	bool focused = true;
	// TODO: fix cross-platform issues with vsync (low priority)
	window->setVerticalSyncEnabled(true);
	// event loop
	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
			else if (event->is<sf::Event::FocusLost>()) {
				focused = false;
			}
			else if (event->is<sf::Event::FocusGained>()) {
				focused = true;
			}
		}
		// prevent listening for inputs when window is not in focus
		if (focused) handleEvents(window, simulation);
		if (simulation.active) {
			simulation.update();
			window->clear({ 255, 255, 255, 255 });
		}
		else {
			window->clear({ 255, 255, 255, 255 });
			renderer.drawPauseMenu();
		}
		// TOOD: make menu for triggering force arrows and other features
		renderer.drawForceArrows(simulation.getParticles());
		renderer.drawParticles(simulation.getParticles());
		renderer.drawFPS(simulation.getParticles());
		window->display();
	}
}