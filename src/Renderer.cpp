#include "Renderer.hpp"
#include <iostream>

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
		circle.setFillColor((particle.getCharge() < 0) ? sf::Color::Yellow : sf::Color::Red);
		circle.setPosition(particle.position - sf::Vector2f{particle.radius, particle.radius});
		window.draw(circle);
		sf::Text chargeSymbol(font, (particle.charge > 0) ? "+" : "-");
		chargeSymbol.setCharacterSize(particle.radius * 2.5);
		sf::FloatRect symbolBounds = chargeSymbol.getLocalBounds();
		chargeSymbol.setOrigin({
			symbolBounds.position.x + symbolBounds.size.x / 2.0f,
			symbolBounds.position.y + symbolBounds.size.y / 2.0f
		});
		chargeSymbol.setPosition(particle.position);
		chargeSymbol.setFillColor(sf::Color::Black);
		window.draw(chargeSymbol);
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

void Renderer::drawForceArrows(std::vector<Particle>* particles) {
	sf::VertexArray lines(sf::PrimitiveType::Lines);
	
	for (Particle& particle : *particles) {
		float x = particle.position.x;
		float y = particle.position.y;
		for (int i = 0; i < 100; i++) {
			sf::Vector2f position = { x, y };
			sf::Vector2f field = electricField(*particles, position);
			if (field.x != 0 || field.y != 0) {
				sf::Vector2f arrowVector = field.normalized() * 5.0f;
				sf::Vertex start;
				start.position = position;
				start.color = sf::Color::Black;
				sf::Vertex end;
				end.position = position + arrowVector;
				end.color = sf::Color::Black;
				lines.append(start);
				lines.append(end);
				x += arrowVector.x;
				y += arrowVector.y;
			}
		}
	}
	window.draw(lines);
}
void Renderer::drawPauseMenu()
{
	sf::Text text(font, "SIMULATION PAUSED");
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(24);
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f position = sf::Vector2f{
		static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)
	};
	sf::Vector2f textDimensions = text.getLocalBounds().size;
	position.x -= textDimensions.x+20;
	position.y -= textDimensions.y*2+10;
	text.setPosition(position);
	window.draw(text);
}