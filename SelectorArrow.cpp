#include "SelectorArrow.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

SelectorArrow::SelectorArrow() :
	sf::Drawable(),
	state_(State::Left),
	sprite_(TextureData::getInstance().getTexture(31)),
	anchorPosition_(),
	speed_(8.0f),
	maxOffsetX_(2.0f),
	offsetX_(0.0f)
{
	const sf::FloatRect spriteLocalBounds = sprite_.getLocalBounds();

	sprite_.setOrigin(
		sf::Vector2f(
			spriteLocalBounds.width * 0.5f,
			spriteLocalBounds.height * 0.5f));

	sprite_.setRotation(45.0f);
}

void SelectorArrow::update(float deltaTime)
{
	switch (state_)
	{
		case State::Left:
			offsetX_ -= speed_ * deltaTime;
			if (offsetX_ <= -maxOffsetX_)
			{
				offsetX_ = -maxOffsetX_;
				state_ = State::Right;
			}
			break;
		case State::Right:
			offsetX_ += speed_ * deltaTime;
			if (offsetX_ >= 0.0f)
			{
				offsetX_ = 0.0f;
				state_ = State::Left;
			}
			break;
	}

	sprite_.setPosition(
		sf::Vector2f(
			anchorPosition_.x + offsetX_,
			anchorPosition_.y));
}

void SelectorArrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void SelectorArrow::setPosition(const sf::Vector2f &position)
{
	anchorPosition_ = position;

	sprite_.setPosition(
		sf::Vector2f(
			anchorPosition_.x + offsetX_,
			anchorPosition_.y));
}