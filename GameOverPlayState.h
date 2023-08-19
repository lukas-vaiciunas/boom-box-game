#pragma once

#include "PlayState.h"
#include "GameOverOptionSelector.h"

class GameOverPlayState : public PlayState
{
public:
	GameOverPlayState(PlayDriverState &play);

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	GameOverOptionSelector optionSelector_;
};