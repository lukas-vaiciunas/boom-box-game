#pragma once

#include "Listener.h"
#include "Shakable.h"

class Camera :
	public Shakable,
	public Listener
{
public:
	Camera();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;

	sf::Vector2f getPosition() const;
private:
	sf::Vector2f position_;
};