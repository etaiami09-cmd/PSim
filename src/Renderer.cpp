#include "Renderer.hpp"


Renderer::Renderer(int width, int height, std::string name) {
	window = sf::RenderWindow(sf::VideoMode({
		static_cast<unsigned int>(width),static_cast<unsigned int>(height)
	}), name);
}

void Renderer::draw(std::vector<Particle>* particles)
{
	for (Particle &particle : *particles) {
		sf::CircleShape circle(particle.radius);
		circle.setFillColor((particle.charge < 0) ? sf::Color::Yellow : sf::Color::Red);
		circle.setPosition(particle.position);
		window.draw(circle);
	}
}

bool Renderer::isActive() {
	return window.isOpen();
}

sf::RenderWindow* Renderer::getWindow() {
	return &window;
}