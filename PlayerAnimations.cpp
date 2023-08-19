#include "PlayerAnimations.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayerAnimations::PlayerAnimations(TextureId textureId, float frameSecs) :
	sf::Drawable(),
	state_(State::Idle),
	direction_(Direction::Right),
	sprite_(TextureData::getInstance().getTexture(textureId)),
	frameWidth_(5),
	frameHeight_(6),
	numCols_(4),
	col_(0),
	row_(0),
	frameClock_(frameSecs)
{
	this->updateFrameRect_();
}

void PlayerAnimations::update(float deltaTime)
{
	frameClock_.update(deltaTime);

	if (frameClock_.isDone())
	{
		frameClock_.resetSoft();

		col_ = (col_ + 1) % numCols_;

		this->updateFrameRect_();
	}
}

void PlayerAnimations::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void PlayerAnimations::setState(State state)
{
	if (state_ == state)
	{
		return;
	}

	state_ = state;

	this->updateRow_();
}

void PlayerAnimations::setDirection(Direction direction)
{
	if (direction_ == direction)
	{
		return;
	}

	direction_ = direction;

	this->updateRow_();
}

void PlayerAnimations::setPosition(const sf::Vector2f &position)
{
	sprite_.setPosition(position);
}

void PlayerAnimations::updateRow_()
{
	uint8_t newRow = 0;

	if (state_ == State::Idle)
	{
		if (direction_ == Direction::Left)
		{
			newRow = 2;
		}
		else if (direction_ == Direction::Right)
		{
			newRow = 0;
		}
	}
	else if (state_ == State::Walk)
	{
		if (direction_ == Direction::Left)
		{
			newRow = 3;
		}
		else if (direction_ == Direction::Right)
		{
			newRow = 1;
		}
	}

	if (row_ == newRow)
	{
		return;
	}

	row_ = newRow;

	this->updateFrameRect_();
}

void PlayerAnimations::updateFrameRect_()
{
	sprite_.setTextureRect(
		sf::IntRect(
			col_ * frameWidth_,
			row_ * frameHeight_,
			frameWidth_,
			frameHeight_));
}