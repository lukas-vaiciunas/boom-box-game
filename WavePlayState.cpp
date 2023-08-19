#include "WavePlayState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

WavePlayState::WavePlayState(PlayDriverState &play) :
	PlayState(play)
{
	for (size_t i : play_.selectedBulletSpawns_)
	{
		play_.bulletSpawns_[i].spawnBullet(play_.bulletSpeed_);
	}

	EventQueue::getInstance().send(
		new EventPlaySound(
			12));
}

void WavePlayState::update(float deltaTime)
{
	play_.bulletPool_.update(deltaTime, play_.player_, play_.bounds_);

	if (play_.bulletPool_.isEmpty())
	{
		play_.incrementWave_();

		EventQueue::getInstance().send(
			new EventChangePlayState(
				PlayStateType::Arrow));
	}

	play_.particlePool_.update(deltaTime);

	play_.player_.update(deltaTime);
	play_.player_.constrain(play_.bounds_); // TODO only update when moving

	play_.camera_.update(deltaTime);
}

void WavePlayState::updateOnKeyPress(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyPress(key);
}

void WavePlayState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyRelease(key);
}

void WavePlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-play_.camera_.getPosition());

	target.draw(play_.arenaSprite_, states);
	target.draw(play_.particlePool_, states);
	target.draw(play_.player_, states);
	target.draw(play_.bulletPool_, states);

	target.draw(play_.healthInterface_, states);
	target.draw(play_.scoreInterface_, states);
}