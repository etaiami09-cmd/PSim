#include "Constants.hpp"
#include "Particle.hpp"
#include "Physics.hpp"
#include "Simulation.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"

const int width = 800;
const int height = 600;
const int FPS = 60;

int main() {
	Simulation simulation(width, height);
	Renderer renderer(width, height, "Electromagnetism Simulator");
	sf::RenderWindow* window = renderer.getWindow();
	window->setVerticalSyncEnabled(true);
	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
		}
		handleEvents(window, simulation);
		simulation.update();
		window->clear({255, 255, 255, 255});
		renderer.drawParticles(simulation.getParticles());
		renderer.drawFPS(simulation.getParticles());
		renderer.drawForceArrows(simulation.getParticles());
		window->display();
	}
}