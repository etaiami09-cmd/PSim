#include "Physics.hpp"
#include "Constants.hpp"

sf::Vector2f coulombForce(const Particle &a, const Particle &b)
{
	float distance = a.distanceFrom(b);
	if (distance < 20.0f) return { 0, 0 };
	sf::Vector2f delta = a.position - b.position;
	float sigmaF = Consts::K * (a.getCharge() * b.getCharge()) / (powf(distance, 2));
	float fX = sigmaF * cosf(delta.angle().asRadians());
	float fY = sigmaF * sinf(delta.angle().asRadians());
	return sf::Vector2f{ fX, fY };
}

void accumulateForces(std::vector<Particle> &particles)
{
	for (int i = 0; i < particles.size(); i++) {
		for (int j = i+1; j < particles.size(); j++) {
			if (i != j) {
				sf::Vector2f force = coulombForce(particles[i], particles[j]);
				particles[i].force += force;
				particles[j].force -= force;
			}
		}
		particles[i].force += lorentzForce(particles[i]);
	}
}

void resetForces(std::vector<Particle> &particles)
{
	for (Particle &particle : particles) {
		particle.force = {0, 0};
	}
}

void integrate(std::vector<Particle> &particles, float dt, std::vector<bool> &isPaused)
{
	for (int i = 0; i < particles.size(); i++) {
		if (!isPaused[i]) {
			Particle& particle = particles[i];
			particle.velocity.x += (particle.force.x / particle.mass) * dt * 0.9f;
			particle.velocity.y += (particle.force.y / particle.mass) * dt * 0.9f;
			particle.position += particle.velocity * dt;
		}
	}
}

void applyBoundaries(std::vector<Particle> &particles, int width, int height)
{
	for (Particle& particle : particles) {
		if (particle.position.x <= particle.radius) {
			particle.position.x = particle.radius;
			particle.velocity.x = std::abs(particle.velocity.x);
		}
		else if (particle.position.x >= width - particle.radius ) {
			particle.position.x = width - particle.radius ;
			particle.velocity.x = -std::abs(particle.velocity.x);
		}

		if (particle.position.y <= particle.radius) {
			particle.position.y = particle.radius;
			particle.velocity.y = std::abs(particle.velocity.y);
		}
		else if (particle.position.y >= height - particle.radius) {
			particle.position.y = height - particle.radius;
			particle.velocity.y = -std::abs(particle.velocity.y);
		}
	}
}

sf::Vector2f particleElectricField(Particle &particle, sf::Vector2f position)
{
	Particle fakeParticle(position, 1, 1);
	float distance = particle.distanceFrom(fakeParticle);
	if (distance < particle.radius) return { 0, 0 };
	sf::Vector2f delta = particle.position - position;
	float sigmaF = Consts::K * (particle.getCharge()) / (std::pow(distance, 2));
	float fX = sigmaF * std::cos(delta.angle().asRadians());
	float fY = sigmaF * std::sin(delta.angle().asRadians());
	return sf::Vector2f{ fX, fY };
}

sf::Vector2f electricField(std::vector<Particle>& particles, sf::Vector2f position)
{
	sf::Vector2f result(0, 0);
	for (Particle& particle : particles) {
		result += particleElectricField(particle, position);
	}
	return result;
}

sf::Vector2f lorentzForce(const Particle& a) {
	sf::Vector3f magneticField = sf::Vector3f{ 0, 0, 0.1f };
	return a.charge * sf::Vector2f{
		a.velocity.y * magneticField.z,
		-a.velocity.x * magneticField.z
	};
}