#include "Constants.hpp"
#include "Particle.hpp"
#include "Physics.hpp"
#include "Simulation.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "Settings.hpp"
#include "external_libraries/tinyfiledialogs.h"

UserSettings* settings = getUserSettings();

int main() {
	// set up stack
	Simulation simulation(800, 600, 60);
	Renderer renderer(settings->width, settings->height, "Electromagnetism Simulator");
	sf::RenderWindow* window = renderer.getWindow();
	bool focused = true;
	renderer.resize(simulation);
	// TODO: fix cross-platform issues with vsync (low priority)
	window->setVerticalSyncEnabled(settings->vsync);
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
			else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				window->setSize(resized->size);
				renderer.resize(simulation);
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