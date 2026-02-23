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
	simulation.addParticle(Particle({ 50, 50 }, 1, -1));
	Renderer renderer(width, height, "Etai's Electromagnetism Simulator");
	sf::RenderWindow* window = renderer.getWindow();
	window->setFramerateLimit(FPS);
	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
		}
		handleEvents(window, simulation);
		simulation.update();
		window->clear({255, 255, 255, 255});
		renderer.draw(simulation.getParticles());
		window->display();
	}
}