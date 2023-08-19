#pragma once

#include "PlayState.h"
#include "AlarmClock.h"

class DeathPlayState : public PlayState
{
public:
	DeathPlayState(PlayDriverState &play);

	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	AlarmClock durationClock_;
};