#pragma once

#include "AlarmClock.h"
#include "TextureId.h"
#include <SFML/Graphics/Sprite.hpp>

class Particle : public sf::Drawable
{
public:
	Particle(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const sf::Vector2f &acceleration,
		float velRotation,
		float durationSecs,
		TextureId textureId);

	virtual void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
protected:
	AlarmClock durationClock_;

	sf::Sprite sprite_;
	
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	sf::Vector2f acceleration_;

	float rotation_;
	float velRotation_;

	float scale_;
};