#include "Bullet.h"
#include "Player.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

Bullet::Bullet(
	const sf::Vector2f &position,
	const sf::Vector2f &velocity,
	TextureId textureId,
	float rotation)
	:
	Collidable(position, sf::Vector2f(0.0f, 0.0f)),
	sf::Drawable(),
	sprite_(TextureData::getInstance().getTexture(textureId)),
	velocity_(velocity),
	rotation_(rotation),
	isLive_(true)
{
	const sf::FloatRect spriteLocalBounds = sprite_.getLocalBounds();

	size_.x = spriteLocalBounds.width;
	size_.y = spriteLocalBounds.height;

	position_ -= size_ * 0.5f;

	sprite_.setPosition(position_);
}

void Bullet::update(float deltaTime, const Player &player, const Boundable &bounds)
{
	position_ += velocity_ * deltaTime;

	sprite_.setPosition(position_);

	if (!isInBounds_(bounds))
	{
		isLive_ = false;

		if (player.isLive())
		{
			EventQueue::getInstance().send(
				new EventAddScore(
					100));
		}
	}

	if (player.isLive() && this->intersects(player))
	{
		isLive_ = false;

		EventQueue::getInstance().send(
			new EventHurtPlayer());
	}
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(rotation_, position_ + size_ * 0.5f);

	target.draw(sprite_, states);
}

bool Bullet::isLive() const
{
	return isLive_;
}

bool Bullet::isInBounds_(const Boundable &bounds) const
{
	const sf::Vector2f &minBounds = bounds.getPosition();
	const sf::Vector2f maxBounds = minBounds + bounds.getSize();

	return position_.x >= minBounds.x
		&& position_.y >= minBounds.y
		&& position_.x + size_.x <= maxBounds.x
		&& position_.y + size_.y <= maxBounds.y;
}