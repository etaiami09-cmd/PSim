#pragma once

#include <string>
#include "Simulation.hpp"

struct CompressedParticle {
	float posX, posY, velX, velY;
	float mass, radius, charge;
	CompressedParticle(Particle& particle);
	CompressedParticle() = default;
	Particle toParticle();
};

struct SimulationMetadata {
	int particleCount;
	int width, height, FPS;
	float speed;
};

Simulation openFrom(std::string path);

std::string promptOpenPath();

std::string promptSavePath();

void saveToPath(std::string path, Simulation& simulation);