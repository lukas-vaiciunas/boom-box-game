#include "Shakable.h"
#include "Randomizer.h"

Shakable::Shakable(float maxOffset, float traumaDecay) :
	offset_(0.0f, 0.0f),
	maxOffset_(maxOffset),
	trauma_(0.0f),
	traumaDecay_(traumaDecay)
{}

void Shakable::update(float deltaTime)
{
	if (trauma_ <= 0.0f)
	{
		return;
	}

	std::mt19937 &eng = Randomizer::getInstance().getEng();
	std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

	float currOffset = maxOffset_ * trauma_;

	offset_.x = currOffset * dis(eng);
	offset_.y = currOffset * dis(eng);

	trauma_ -= traumaDecay_ * deltaTime;

	if (trauma_ < 0.0f)
	{
		trauma_ = 0.0f;
	}
}