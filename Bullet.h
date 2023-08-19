#pragma once

class Player;

#include "TextureId.h"
#include "Collidable.h"
#include "AlarmClock.h"
#include <SFML/Graphics/Sprite.hpp>

class Bullet :
	public Collidable,
	public sf::Drawable
{
public:
	Bullet(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		TextureId textureId,
		float rotation);

	void update(float deltaTime, const Player &player, const Boundable &bounds);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
private:
	sf::Sprite sprite_;

	sf::Vector2f velocity_;

	float rotation_;

	bool isLive_;

	bool isInBounds_(const Boundable &bounds) const;
};