#include "SaveLoad.hpp"
#include <fstream>
#include "external_libraries/tinyfiledialogs.h"

CompressedParticle::CompressedParticle(Particle& particle)
{
	posX = particle.position.x;
	posY = particle.position.y;
	velX = particle.velocity.x;
	velY = particle.velocity.y;
	mass = particle.mass;
	charge = particle.charge;
	radius = particle.radius;
};

Particle CompressedParticle::toParticle()
{
	Particle particle(sf::Vector2f{ posX, posY }, mass, charge);
	particle.velocity = sf::Vector2f{ velX, velY };
	particle.radius = radius;
	return particle;
}

Simulation openFrom(std::string path)
{
	std::ifstream saveFile(path, std::ios::binary);
	if (!saveFile.is_open()) {
		std::perror("File could not be opened!\n");
		std::abort();
	}
	SimulationMetadata metadata;
	saveFile.read(reinterpret_cast<char*>(&metadata), sizeof(SimulationMetadata));
	Simulation simulation(metadata.width, metadata.height, metadata.FPS);
	simulation.active = false;
	simulation.getParticles()->resize(metadata.particleCount);
	simulation.isPaused.resize(metadata.particleCount);
	for (int i = 0; i < metadata.particleCount; i++) {
		CompressedParticle compressed;
		saveFile.read(reinterpret_cast<char*>(&compressed), sizeof(CompressedParticle));
		simulation.getParticles()->at(i) = compressed.toParticle();
	}
	saveFile.close();
	return simulation;
}

std::string promptOpenPath()
{
	return tinyfd_openFileDialog(
		"Open Simulation",
		"",
		0,
		nullptr,
		nullptr,
		0
	);
}

std::string promptSavePath()
{
	return tinyfd_saveFileDialog(
		"Save Simulation",
		"save.psim",
		0,
		nullptr,
		nullptr
	);
}

void saveToPath(std::string path, Simulation& simulation)
{
	std::ofstream saveFile(path, std::ios::binary);
	SimulationMetadata metadata;
	metadata.FPS = simulation.getFPS();
	metadata.particleCount = simulation.getParticles()->size();
	metadata.width = simulation.getWidth();
	metadata.height = simulation.getHeight();
	metadata.speed = simulation.getSpeed();
	saveFile.write(reinterpret_cast<char*>(&metadata), sizeof(SimulationMetadata));
	for (Particle& particle : *simulation.getParticles()) {
		CompressedParticle compressed(particle);
		saveFile.write(reinterpret_cast<char*>(&compressed), sizeof(CompressedParticle));
	}
	saveFile.close();
}