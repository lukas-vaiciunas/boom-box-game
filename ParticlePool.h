#pragma once

#include "Pool.h"
#include "Particle.h"
#include "Listener.h"

class ParticlePool :
	public Pool<Particle>,
	public Listener,
	public sf::Drawable
{
public:
	ParticlePool(Size capacity);

	void onEvent(const Event &ev) override;

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};