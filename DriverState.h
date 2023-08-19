#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class DriverState : public sf::Drawable
{
public:
	DriverState();

	virtual ~DriverState() {}

	virtual void update(float deltaTime) {}
	virtual void updateOnMouseMove(int mouseX, int mouseY) {}
	virtual void updateOnMouseButtonPress(sf::Mouse::Button button) {}
	virtual void updateOnKeyPress(sf::Keyboard::Key key) {}
	virtual void updateOnKeyRelease(sf::Keyboard::Key key) {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
};