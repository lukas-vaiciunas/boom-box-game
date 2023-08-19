#pragma once

#include "Collidable.h"
#include "Listener.h"
#include "PlayerAnimations.h"
#include <SFML/Window/Keyboard.hpp>

class Player :
	public Collidable,
	public Listener,
	public sf::Drawable
{
public:
	Player(uint8_t health);

	void onEvent(const Event &ev) override;

	void update(float deltaTime);
	void updateOnKeyPress(sf::Keyboard::Key key);
	void updateOnKeyRelease(sf::Keyboard::Key key);

	void constrain(const Boundable &bounds);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
private:
	enum MoveFlag : uint8_t
	{
		None = 0,
		Up = 1,
		Down = 2,
		Left = 4,
		Right = 8
	};

	uint8_t moveFlags_;

	PlayerAnimations animations_;

	uint8_t health_;

	float speed_;

	void hurt_();
};