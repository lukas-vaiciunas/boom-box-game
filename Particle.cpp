#include "Particle.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

Particle::Particle(
	const sf::Vector2f &position,
	const sf::Vector2f &velocity,
	const sf::Vector2f &acceleration,
	float velRotation,
	float durationSecs,
	TextureId textureId)
	:
	sf::Drawable(),
	durationClock_(durationSecs),
	sprite_(TextureData::getInstance().getTexture(textureId)),
	position_(position),
	velocity_(velocity),
	acceleration_(acceleration),
	rotation_(0.0f),
	velRotation_(velRotation),
	scale_(1.0f)
{
	sprite_.setPosition(position_);
	sprite_.setRotation(rotation_);

	const sf::FloatRect spriteLocalBounds = sprite_.getLocalBounds();

	sprite_.setOrigin(
		spriteLocalBounds.width * 0.5f,
		spriteLocalBounds.height * 0.5f);
}

void Particle::update(float deltaTime)
{
	durationClock_.update(deltaTime);

	scale_ = (durationClock_.getTargetSecs() - durationClock_.getSecs()) / durationClock_.getTargetSecs();

	position_ += velocity_ * deltaTime;
	velocity_ += acceleration_ * deltaTime;
	rotation_ += velRotation_ * deltaTime;

	if (rotation_ >= 360.0f)
	{
		rotation_ -= 360.0f;
	}
	else if (rotation_ <= -360.0f)
	{
		rotation_ += 360.0f;
	}

	sprite_.setPosition(position_);
	sprite_.setRotation(rotation_);
	sprite_.setScale(sf::Vector2f(scale_, scale_));
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

bool Particle::isLive() const
{
	return !durationClock_.isDone();
}