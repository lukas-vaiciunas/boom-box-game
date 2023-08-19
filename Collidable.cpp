#include "Collidable.h"

Collidable::Collidable(const sf::Vector2f &position, const sf::Vector2f &size) :
	Boundable(position, size)
{}

bool Collidable::intersects(const Collidable &other) const
{
	return position_.x < other.position_.x + other.size_.x
		&& position_.x + size_.x > other.position_.x
		&& position_.y < other.position_.y + other.size_.y
		&& position_.y + size_.y > other.position_.y;
}

bool Collidable::contains(const sf::Vector2f &position) const
{
	return position.x > position_.x
		&& position.x < position_.x + size_.x
		&& position.y > position_.y
		&& position.y < position_.y + size_.y;
}