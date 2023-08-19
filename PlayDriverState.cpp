#include "PlayDriverState.h"
#include "IntroPlayState.h"
#include "ArrowPlayState.h"
#include "WavePlayState.h"
#include "DeathPlayState.h"
#include "GameOverPlayState.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayDriverState::PlayDriverState() :
	DriverState(),
	Listener({ EventType::ChangePlayState }),
	state_(nullptr),
	bulletSpawns_(
		{
			BulletSpawn(sf::Vector2f(12.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(20.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(28.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(36.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(44.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(52.0f, 10.0f), BulletSpawn::Direction::Down),
			BulletSpawn(sf::Vector2f(10.0f, 12.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(10.0f, 20.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(10.0f, 28.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(10.0f, 36.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(10.0f, 44.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(10.0f, 52.0f), BulletSpawn::Direction::Right),
			BulletSpawn(sf::Vector2f(12.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(20.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(28.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(36.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(44.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(52.0f, 54.0f), BulletSpawn::Direction::Up),
			BulletSpawn(sf::Vector2f(54.0f, 12.0f), BulletSpawn::Direction::Left),
			BulletSpawn(sf::Vector2f(54.0f, 20.0f), BulletSpawn::Direction::Left),
			BulletSpawn(sf::Vector2f(54.0f, 28.0f), BulletSpawn::Direction::Left),
			BulletSpawn(sf::Vector2f(54.0f, 36.0f), BulletSpawn::Direction::Left),
			BulletSpawn(sf::Vector2f(54.0f, 44.0f), BulletSpawn::Direction::Left),
			BulletSpawn(sf::Vector2f(54.0f, 52.0f), BulletSpawn::Direction::Left)
		}),
	selectedBulletSpawns_(),
	player_(3),
	bulletPool_(100),
	particlePool_(100),
	camera_(),
	score_(),
	healthInterface_(),
	scoreInterface_(),
	bounds_(sf::Vector2f(8.0f, 8.0f), sf::Vector2f(48.0f, 48.0f)),
	arenaSprite_(TextureData::getInstance().getTexture(11)),
	wave_(1),
	numBullets_(1),
	bulletSpeed_(32.0f),
	arrowDurationSecs_(1.25f)
{
	this->changeState_(PlayStateType::Intro);
}

PlayDriverState::~PlayDriverState()
{
	delete state_;
}

void PlayDriverState::onEvent(const Event &ev)
{
	this->changeState_(
		static_cast<const EventChangePlayState &>(ev).getType());
}

void PlayDriverState::update(float deltaTime)
{
	state_->update(deltaTime);
}

void PlayDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void PlayDriverState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonPress(button);
}

void PlayDriverState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Escape)
	{
		EventQueue::getInstance().send(
			new EventChangeDriverState(
				DriverStateType::MainMenu));
	}
	else
	{
		state_->updateOnKeyPress(key);
	}
}

void PlayDriverState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void PlayDriverState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

void PlayDriverState::incrementWave_()
{
	++wave_;
	
	if (wave_ % 5 == 0
		&& numBullets_ < 5)
	{
		++numBullets_;
	}
	
	if(bulletSpeed_ < 96.0f)
	{
		bulletSpeed_ += 1.0f;
	}
	if (arrowDurationSecs_ > 0.5f)
	{
		arrowDurationSecs_ -= 0.05f;
	}
}

void PlayDriverState::changeState_(PlayStateType type)
{
	delete state_;

	switch (type)
	{
		case PlayStateType::Intro:
			state_ = new IntroPlayState(*this);
			break;
		case PlayStateType::Arrow:
			state_ = new ArrowPlayState(*this);
			break;
		case PlayStateType::Wave:
			state_ = new WavePlayState(*this);
			break;
		case PlayStateType::Death:
			state_ = new DeathPlayState(*this);
			break;
		case PlayStateType::GameOver:
			state_ = new GameOverPlayState(*this);
			break;
	}
}