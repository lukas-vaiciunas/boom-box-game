#pragma once

class PlayDriverState;

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class PlayState : public sf::Drawable
{
public:
	PlayState(PlayDriverState &play);

	virtual ~PlayState() {}

	virtual void update(float deltaTime) {}
	virtual void updateOnMouseMove(int mouseX, int mouseY) {}
	virtual void updateOnMouseButtonPress(sf::Mouse::Button button) {}
	virtual void updateOnKeyPress(sf::Keyboard::Key key) {}
	virtual void updateOnKeyRelease(sf::Keyboard::Key key) {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
protected:
	PlayDriverState &play_;
};