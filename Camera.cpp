#include "Camera.h"
#include "Event.h"
#include "Randomizer.h"
#include "Config.h"

Camera::Camera() :
	Shakable(4.0f, 2.0f),
	Listener({ EventType::ShakeCamera }),
	position_(
		32.0f - Config::Window::width / Config::Game::scale * 0.5f,
		32.0f - Config::Window::height / Config::Game::scale * 0.5f)
{}

void Camera::onEvent(const Event &ev)
{
	trauma_ += static_cast<const EventShakeCamera &>(ev).getTrauma();

	if (trauma_ > 1.0f)
	{
		trauma_ = 1.0f;
	}
}

void Camera::update(float deltaTime)
{
	Shakable::update(deltaTime);
}

sf::Vector2f Camera::getPosition() const
{
	return position_ + offset_;
}