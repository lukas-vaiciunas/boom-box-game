#pragma once

#include "DriverState.h"
#include "TitleText.h"
#include "Camera.h"
#include "MainMenuOptionSelector.h"

class MainMenuDriverState : public DriverState
{
public:
	MainMenuDriverState();

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Sprite arenaSprite_;

	sf::Text ownerText_;

	TitleText titleText_;

	MainMenuOptionSelector optionSelector_;

	Camera camera_;
};