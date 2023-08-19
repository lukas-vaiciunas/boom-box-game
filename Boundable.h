#pragma once

#include <SFML/System/Vector2.hpp>

class Boundable
{
public:
	Boundable(const sf::Vector2f &position, const sf::Vector2f &size);

	virtual ~Boundable() {}

	const sf::Vector2f &getPosition() const;
	const sf::Vector2f &getSize() const;
protected:
	sf::Vector2f position_;
	sf::Vector2f size_;
};