#include "Arrow.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

Arrow::Arrow(const sf::Vector2f &position, float rotation) :
	sf::Drawable(),
	state_(State::Contract),
	sprite_(TextureData::getInstance().getTexture(41)),
	scale_(1.0f),
	minScale_(0.75f),
	maxScale_(1.0f),
	velScale_(1.0f)
{
	sprite_.setPosition(position);
	sprite_.setRotation(rotation);

	const sf::FloatRect spriteLocalBounds = sprite_.getLocalBounds();

	sprite_.setOrigin(
		spriteLocalBounds.width * 0.5f,
		spriteLocalBounds.height * 0.5f);
}

void Arrow::update(float deltaTime)
{
	switch (state_)
	{
		case State::Contract:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Contract;
			}
			break;
	}
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(scale_, scale_),
		sprite_.getPosition());

	target.draw(sprite_, states);
}