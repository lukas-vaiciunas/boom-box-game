#include "Boundable.h"

Boundable::Boundable(const sf::Vector2f &position, const sf::Vector2f &size) :
	position_(position),
	size_(size)
{}

const sf::Vector2f &Boundable::getPosition() const
{
	return position_;
}

const sf::Vector2f &Boundable::getSize() const
{
	return size_;
}