#include "Randomizer.h"

Randomizer &Randomizer::getInstance()
{
	static Randomizer instance;
	return instance;
}

std::mt19937 &Randomizer::getEng()
{
	return eng_;
}

Randomizer::Randomizer() :
	eng_(std::random_device()())
{}