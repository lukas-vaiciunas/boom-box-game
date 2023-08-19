#include "BulletPool.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

BulletPool::BulletPool(Size capacity) :
	Pool(capacity),
	Listener({ EventType::SpawnBullet }),
	sf::Drawable()
{}

void BulletPool::onEvent(const Event &ev)
{
	if (this->isFull_())
	{
		return;
	}

	const EventSpawnBullet &trueEv = static_cast<const EventSpawnBullet &>(ev);

	this->add_(
		new Bullet(
			trueEv.getPosition(),
			trueEv.getVelocity(),
			31,
			trueEv.getRotation()));
}

void BulletPool::update(float deltaTime, const Player &player, const Boundable &bounds)
{
	for (Size i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime, player, bounds);

		if (!objects_[i]->isLive())
		{
			this->remove_(i);
		}
		else ++i;
	}
}

void BulletPool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Size i = 0; i < numLive_; ++i)
	{
		target.draw(*objects_[i], states);
	}
}