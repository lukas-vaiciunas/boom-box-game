#include "Player.h"
#include "Event.h"
#include "EventQueue.h"
#include <SFML/Graphics/RenderTarget.hpp>

Player::Player(uint8_t health) :
	Collidable(
		sf::Vector2f(32.0f, 32.0f),
		sf::Vector2f(5.0f, 6.0f)),
	Listener({ EventType::HurtPlayer }),
	sf::Drawable(),
	moveFlags_(MoveFlag::None),
	animations_(1, 0.2f),
	health_(health),
	speed_(32.0f)
{
	position_ -= size_ * 0.5f;
	animations_.setPosition(position_);

	EventQueue::getInstance().send(
		new EventUpdateHealthInterface(
			health_));
}

void Player::onEvent(const Event &ev)
{
	this->hurt_();
}

void Player::update(float deltaTime)
{
	animations_.update(deltaTime);

	if (moveFlags_ == MoveFlag::None)
	{
		animations_.setState(PlayerAnimations::State::Idle);
		return;
	}

	sf::Vector2f velocity(0.0f, 0.0f);

	if (moveFlags_ & MoveFlag::Up)
	{
		velocity.y -= speed_;
	}
	if (moveFlags_ & MoveFlag::Left)
	{
		velocity.x -= speed_;
	}
	if (moveFlags_ & MoveFlag::Down)
	{
		velocity.y += speed_;
	}
	if (moveFlags_ & MoveFlag::Right)
	{
		velocity.x += speed_;
	}

	if (velocity.x == 0.0f && velocity.y == 0.0f)
	{
		animations_.setState(PlayerAnimations::State::Idle);
		return;
	}

	animations_.setState(PlayerAnimations::State::Walk);

	if (velocity.x != 0.0f)
	{
		animations_.setDirection(
			(velocity.x > 0.0f)
			? PlayerAnimations::Direction::Right
			: PlayerAnimations::Direction::Left);
	}

	velocity = velocity / sqrtf(velocity.x * velocity.x + velocity.y * velocity.y) * speed_;

	position_ += velocity * deltaTime;

	animations_.setPosition(position_);
}

void Player::updateOnKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
		case sf::Keyboard::Key::Up:
			moveFlags_ |= MoveFlag::Up;
			break;
		case sf::Keyboard::Key::A:
		case sf::Keyboard::Key::Left:
			moveFlags_ |= MoveFlag::Left;
			break;
		case sf::Keyboard::Key::S:
		case sf::Keyboard::Key::Down:
			moveFlags_ |= MoveFlag::Down;
			break;
		case sf::Keyboard::Key::D:
		case sf::Keyboard::Key::Right:
			moveFlags_ |= MoveFlag::Right;
			break;
	}
}

void Player::updateOnKeyRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
		case sf::Keyboard::Key::Up:
			moveFlags_ &= ~MoveFlag::Up;
			break;
		case sf::Keyboard::Key::A:
		case sf::Keyboard::Key::Left:
			moveFlags_ &= ~MoveFlag::Left;
			break;
		case sf::Keyboard::Key::S:
		case sf::Keyboard::Key::Down:
			moveFlags_ &= ~MoveFlag::Down;
			break;
		case sf::Keyboard::Key::D:
		case sf::Keyboard::Key::Right:
			moveFlags_ &= ~MoveFlag::Right;
			break;
	}
}

void Player::constrain(const Boundable &bounds)
{
	const sf::Vector2f &minBounds = bounds.getPosition();
	const sf::Vector2f maxBounds = minBounds + bounds.getSize();

	if (position_.x < minBounds.x)
	{
		position_.x = minBounds.x;
	}
	if (position_.y < minBounds.y)
	{
		position_.y = minBounds.y;
	}
	if (position_.x + size_.x > maxBounds.x)
	{
		position_.x = maxBounds.x - size_.x;
	}
	if (position_.y + size_.y > maxBounds.y)
	{
		position_.y = maxBounds.y - size_.y;
	}

	animations_.setPosition(position_);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(animations_, states);
}

bool Player::isLive() const
{
	return health_ > 0;
}

void Player::hurt_()
{
	if (health_ == 0)
	{
		return;
	}

	EventQueue &eventQueue = EventQueue::getInstance();

	health_ -= 1;

	if (health_ == 0)
	{
		eventQueue.send(
			new EventChangePlayState(
				PlayStateType::Death));

		eventQueue.send(
			new EventPlaySound(
				15));
	}
	else
	{
		eventQueue.send(
			new EventPlaySound(
				13));
	}

	eventQueue.send(
		new EventShakeCamera(
			1.0f));

	eventQueue.send(
		new EventUpdateHealthInterface(
			health_));
}