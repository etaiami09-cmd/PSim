#include "InputHandler.hpp"

bool mouseWithinBounds(int width, int height, sf::RenderWindow* window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	return (mousePosition.x <= width && mousePosition.x >= 0
		&& mousePosition.y <= height && mousePosition.y >= 0);
}

void handleEvents(sf::RenderWindow* window, Simulation& simulation)
{
	static bool pressedRightBefore = false;
	static bool pressedLeftBefore = false;
	static bool pressedDownBefore = false;
	static bool pressedUpBefore = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		window->close();
		return;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		if (!pressedRightBefore) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = sf::Vector2f{
				static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)
			};
			sf::Vector2u windowDimensions = window->getSize();
			if (mouseWithinBounds(windowDimensions.x, windowDimensions.y, window)) {
				simulation.addParticle(Particle(mousePosFloat, 1, 1));
			}
		}
		pressedRightBefore = true;
	}
	else {
		pressedRightBefore = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!pressedLeftBefore) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = sf::Vector2f{
				static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)
			};
			sf::Vector2u windowDimensions = window->getSize();
			if (mouseWithinBounds(windowDimensions.x, windowDimensions.y, window)) {
				simulation.addParticle(Particle(mousePosFloat, 1, -1));
			}
		}
		pressedLeftBefore = true;
	}
	else {
		pressedLeftBefore = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		if (!pressedUpBefore) {
			simulation.speed *= 1.2;
		}
		pressedUpBefore = true;
	}
	else {
		pressedUpBefore = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		if (!pressedDownBefore) {
			simulation.speed *= 1.0f / (1.2);

		}
		pressedDownBefore = true;
	}
	else {
		pressedDownBefore = false;
	}
}
