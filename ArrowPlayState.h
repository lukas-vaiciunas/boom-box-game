#pragma once

#include "PlayState.h"
#include "AlarmClock.h"
#include "Arrow.h"
#include <vector>

class ArrowPlayState : public PlayState
{
public:
	ArrowPlayState(PlayDriverState &play);

	void update(float deltaTime) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<Arrow> arrows_;

	AlarmClock durationClock_;
};