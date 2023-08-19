#include "ParticlePool.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

ParticlePool::ParticlePool(Size capacity) :
	Pool(capacity),
	Listener({ EventType::SpawnParticle }),
	sf::Drawable()
{}

void ParticlePool::onEvent(const Event &ev)
{
	if (this->isFull_())
	{
		return;
	}

	const EventSpawnParticle &trueEv = static_cast<const EventSpawnParticle &>(ev);

	this->add_(
		new Particle(
			trueEv.getPosition(),
			trueEv.getVelocity(),
			trueEv.getAcceleration(),
			trueEv.getVelRotation(),
			trueEv.getDurationSecs(),
			trueEv.getTextureId()));
}

void ParticlePool::update(float deltaTime)
{
	for (Size i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime);

		if (!objects_[i]->isLive())
		{
			this->remove_(i);
		}
		else ++i;
	}
}

void ParticlePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Size i = 0; i < numLive_; ++i)
	{
		target.draw(*objects_[i], states);
	}
}