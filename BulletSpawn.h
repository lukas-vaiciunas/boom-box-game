#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>

class BulletSpawn
{
public:
	enum class Direction : uint8_t
	{
		Up,
		Down,
		Left,
		Right
	};

	BulletSpawn(const sf::Vector2f &position, Direction direction);

	void spawnBullet(float speed);

	const sf::Vector2f &getPosition() const;
	float getRotation() const;
private:
	sf::Vector2f position_;
	sf::Vector2f unitVelocity_;
	float rotation_;
};