#include "AlarmClock.h"

AlarmClock::AlarmClock(float targetSecs) :
	targetSecs_(targetSecs),
	secs_(0.0f)
{}

void AlarmClock::update(float deltaTime)
{
	secs_ += deltaTime;
}

void AlarmClock::resetSoft()
{
	secs_ -= targetSecs_;
}

void AlarmClock::resetHard()
{
	secs_ = 0.0f;
}

bool AlarmClock::isDone() const
{
	return secs_ >= targetSecs_;
}

float AlarmClock::getTargetSecs() const
{
	return targetSecs_;
}

float AlarmClock::getSecs() const
{
	return secs_;
}