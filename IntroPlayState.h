#pragma once

#include "PlayState.h"
#include "CountdownInterface.h"
#include "AlarmClock.h"
#include <SFML/Graphics/Text.hpp>

class IntroPlayState : public PlayState
{
public:
	IntroPlayState(PlayDriverState &play);

	void update(float deltaTime) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	CountdownInterface countdownInterface_;

	AlarmClock durationClock_;
};