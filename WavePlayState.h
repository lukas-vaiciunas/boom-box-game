#pragma once

#include "PlayState.h"

class WavePlayState : public PlayState
{
public:
	WavePlayState(PlayDriverState &play);

	void update(float deltaTime) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};