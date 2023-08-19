#include "BulletSpawn.h"
#include "Event.h"
#include "EventQueue.h"

BulletSpawn::BulletSpawn(const sf::Vector2f &position, Direction direction) :
	position_(position),
	unitVelocity_(0.0f, 0.0f),
	rotation_(0.0f)
{
	switch (direction)
	{
		case Direction::Up:
			unitVelocity_.y = -1.0f;
			rotation_ = -45.0f;
			break;
		case Direction::Down:
			unitVelocity_.y = 1.0f;
			rotation_ = 135.0f;
			break;
		case Direction::Left:
			unitVelocity_.x = -1.0f;
			rotation_ = -135.0f;
			break;
		case Direction::Right:
			unitVelocity_.x = 1.0f;
			rotation_ = 45.0f;
			break;
	}
}

void BulletSpawn::spawnBullet(float speed)
{
	EventQueue::getInstance().send(
		new EventSpawnBullet(
			position_,
			unitVelocity_ * speed,
			rotation_));
}

const sf::Vector2f &BulletSpawn::getPosition() const
{
	return position_;
}

float BulletSpawn::getRotation() const
{
	return rotation_;
}