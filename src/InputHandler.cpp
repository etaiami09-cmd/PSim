#include "InputHandler.hpp"
#include "SaveLoad.hpp"

bool mouseWithinBounds(int width, int height, sf::RenderWindow* window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	return (mousePosition.x <= width && mousePosition.x >= 0
		&& mousePosition.y <= height && mousePosition.y >= 0);
}

float distanceMouse(sf::Vector2f &position, sf::RenderWindow* window) {
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	return std::hypot(mousePosition.x - position.x, mousePosition.y - position.y);
}

void handleEvents(sf::RenderWindow* window, Simulation& simulation)
{
	static bool pressedRightBefore = false;
	static bool pressedLeftBefore = false;
	static bool pressedDownBefore = false;
	static bool pressedUpBefore = false;
	static bool pressedSpaceBefore = false;
	static bool pressedEnterBefore = false;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!pressedSpaceBefore) {
			simulation.active = !simulation.active;
		}
		pressedSpaceBefore = true;
	}
	else {
		pressedSpaceBefore = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		for (int i = 0; i < simulation.getParticles()->size(); i++) {
			Particle& particle = simulation.getParticles()->at(i);
			if (distanceMouse(particle.position, window) <= particle.radius) {
				simulation.isPaused[i] = true;
			}
		}
		pressedEnterBefore = true;
	}
	else {
		if (pressedEnterBefore) {
			for (auto& pauseStatus : simulation.isPaused) {
				pauseStatus = false;
			}
		}
		pressedEnterBefore = false;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		std::string path = promptSavePath();
		if (path == "NULL") {
			return;
		}
		saveToPath(path, simulation);
		simulation.active = false;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
		std::string path = promptOpenPath();
		if (path == "NULL") {
			return;
		}
		simulation.~Simulation();
		simulation = openFrom(path);
	}
}