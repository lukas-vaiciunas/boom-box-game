#pragma once

#include "Pool.h"
#include "Bullet.h"
#include "Listener.h"

class BulletPool :
	public Pool<Bullet>,
	public Listener,
	public sf::Drawable
{
public:
	BulletPool(Size capacity);

	void onEvent(const Event &ev) override;

	void update(float deltaTime, const Player &player, const Boundable &bounds);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};