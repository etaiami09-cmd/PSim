#include <SFML/Graphics.hpp>

#include "Settings.hpp"
#include "Simulation.hpp"

UserSettings getDefaultSettings()
{
	UserSettings defaults;
	defaults.FPS = 60;
	defaults.vsync = true;
	defaults.speed = 1;
	defaults.height = 600;
	defaults.width = 800;
	return defaults;
}

UserSettings settings = getDefaultSettings();

UserSettings* getUserSettings()
{
	return &settings;
}

sf::RenderWindow* singletonWindow;

Simulation* singletonSim;

float xRatio, yRatio;
float simAspectRatio, winAspectRatio;

void setWindow(sf::RenderWindow* window)
{
	singletonWindow = window;
	winAspectRatio = (
		static_cast<float>(singletonWindow->getSize().x)
		/ static_cast<float>(singletonWindow->getSize().y)
		);
	if (singletonSim == nullptr) return;
	xRatio = (
		static_cast<float>(singletonSim->getWidth())
		/ static_cast<float>(singletonWindow->getSize().x)
	);
	yRatio = (
		static_cast<float>(singletonSim->getHeight())
		/ static_cast<float>(singletonWindow->getSize().y)
	);
}

void setSimulation(Simulation* sim)
{
	singletonSim = sim;
	simAspectRatio = (
		static_cast<float>(singletonSim->getWidth())
		/ static_cast<float>(singletonSim->getHeight())
	);
	if (singletonWindow == nullptr) return;
	xRatio = (
		static_cast<float>(singletonSim->getWidth())
		/ static_cast<float>(singletonWindow->getSize().x)
		);
	yRatio = (
		static_cast<float>(singletonSim->getHeight())
		/ static_cast<float>(singletonWindow->getSize().y)
		);
}

sf::Vector2f windowToSim(sf::Vector2f& windowPos)
{
	return singletonWindow->mapPixelToCoords(
		sf::Vector2i(windowPos),
		singletonWindow->getView()
	);
}

sf::Vector2f simToWindow(sf::Vector2f& simPos)
{
	sf::Vector2i pixel = singletonWindow->mapCoordsToPixel(
		simPos,
		singletonWindow->getView()
	);
	return sf::Vector2f(pixel);
}