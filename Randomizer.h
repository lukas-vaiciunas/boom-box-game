#pragma once

#include <random>

class Randomizer
{
public:
	Randomizer(const Randomizer &) = delete;
	Randomizer(Randomizer &&) = delete;

	Randomizer &operator=(const Randomizer &) = delete;
	Randomizer &operator=(Randomizer &&) = delete;

	static Randomizer &getInstance();

	std::mt19937 &getEng();
private:
	Randomizer();
	~Randomizer() {}

	std::mt19937 eng_;
};