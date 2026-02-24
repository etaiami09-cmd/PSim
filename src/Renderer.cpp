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
		circle.setFillColor((particle.getCharge() < 0) ? sf::Color::Yellow : sf::Color::Red);
		circle.setPosition(particle.position - sf::Vector2f{particle.radius, particle.radius});
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

void appendThickLine(sf::VertexArray& vertices, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color)
{
	sf::Vector2f direction = end - start;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unit = direction / length;
	sf::Vector2f perp = { -unit.y, unit.x };
	sf::Vector2f offset = perp * (thickness / 2.0f);

	vertices.append(sf::Vertex{ start - offset, color });
	vertices.append(sf::Vertex{ start + offset, color });
	vertices.append(sf::Vertex{ end + offset, color });
	vertices.append(sf::Vertex{ start - offset, color });
	vertices.append(sf::Vertex{ end + offset, color });
	vertices.append(sf::Vertex{ end - offset, color });
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
//// TODO: attempt refactor into a continuous line for easier-on-the-eye field arrows
//void Renderer::drawForceArrows(std::vector<Particle>* particles)
//{
//	sf::VertexArray lines(sf::PrimitiveType::Triangles);
//	for (int i = 0; i < window.getSize().x; i += 100) {
//		for (int j = 0; j < window.getSize().y; j += 100) {
//			sf::Vector2f position = sf::Vector2f{ static_cast<float>(i), static_cast<float>(j)};
//			sf::Vector2f field = electricField(*particles, position);
//			if (field.x != 0 || field.y != 0) {
//				float magnitude = std::sqrt(field.x * field.x + field.y * field.y);
//				float arrowLength = std::clamp(std::log(magnitude + 1.0f) * 5.0f, 5.0f, 40.0f);
//				sf::Vector2f arrowVector = field.normalized() * arrowLength;
//				sf::Vertex start;
//				start.position = position;
//				start.color = sf::Color::Black;
//				sf::Vertex end;
//				end.position = position + arrowVector * 5.0f;
//				end.color = sf::Color::Black;
//				lines.append(start);
//				lines.append(end);
//				sf::Vector2f tip = position + arrowVector * 5.0f;
//
//				float angle = std::atan2(arrowVector.y, arrowVector.x);
//				float branchLength = 5.0f;
//				float branchAngle = 0.5f;
//
//				sf::Vector2f branch1 = {
//					std::cos(angle + 3.14159f - branchAngle) * branchLength,
//					std::sin(angle + 3.14159f - branchAngle) * branchLength
//				};
//				sf::Vector2f branch2 = {
//					std::cos(angle + 3.14159f + branchAngle) * branchLength,
//					std::sin(angle + 3.14159f + branchAngle) * branchLength
//				};
//
//				lines.append(sf::Vertex{ tip, sf::Color::Black });
//				lines.append(sf::Vertex{ tip + branch1, sf::Color::Black });
//				lines.append(sf::Vertex{ tip, sf::Color::Black });
//				lines.append(sf::Vertex{ tip + branch2, sf::Color::Black });
//				appendThickLine(lines, position, tip, 2.0f, sf::Color::Black);
//			}
//		}
//	}
//	window.draw(lines);
//}
