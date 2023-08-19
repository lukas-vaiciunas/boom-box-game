#pragma once

#include "Boundable.h"

class Collidable : public Boundable
{
public:
	Collidable(const sf::Vector2f &position, const sf::Vector2f &size);

	virtual ~Collidable() {}

	bool intersects(const Collidable &other) const;
	bool contains(const sf::Vector2f &position) const;
};