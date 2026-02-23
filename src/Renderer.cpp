#include "Renderer.hpp"

Renderer::Renderer(int width, int height, std::string name) {
	window = sf::RenderWindow(sf::VideoMode({
		static_cast<unsigned int>(width),static_cast<unsigned int>(height)
	}), name);
	clock = sf::Clock();
	font = sf::Font("assets/Arial.ttf");
	frameTimes = std::vector<float>(60, 1.0f / 60.0f);
	frameIndex = 0;
	frameCount = 0;
	displayedFPS = 60;
}

void Renderer::drawParticles(std::vector<Particle>* particles)
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

float Renderer::getDelta()
{
	return clock.restart().asSeconds();
}

void Renderer::drawFPS(std::vector<Particle> *particles)
{
	float timeDelta = clock.restart().asSeconds();
	frameTimes[frameIndex] = timeDelta;
	frameIndex = (frameIndex + 1) % 60;
	frameCount++;
	if (frameCount >= 60) {
		float avgFrameTime = 0.0f;
		for (float ft : frameTimes) avgFrameTime += ft;
		avgFrameTime /= 60.0f;
		displayedFPS = static_cast<int>(1.0f / avgFrameTime);
		frameCount = 0;
	}
	sf::Text text(font,
		"FPS: " + std::to_string(displayedFPS) + " | Particles: "
		+ std::to_string(particles->size()));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ 0, 0 });
	window.draw(text);
}
