#include "ArrowPlayState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "Randomizer.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

ArrowPlayState::ArrowPlayState(PlayDriverState &play) :
	PlayState(play),
	arrows_(),
	durationClock_(1.5f)
{
	std::mt19937 &eng = Randomizer::getInstance().getEng();
	std::uniform_int_distribution<size_t> dis(0, play_.bulletSpawns_.size() - 1);

	play_.selectedBulletSpawns_.clear();

	while (play_.selectedBulletSpawns_.size() < play_.numBullets_)
	{
		size_t i = dis(eng);

		if (play_.selectedBulletSpawns_.find(i) != play_.selectedBulletSpawns_.end())
		{
			continue;
		}

		play_.selectedBulletSpawns_.emplace(i);
	}

	for (size_t i : play_.selectedBulletSpawns_)
	{
		arrows_.push_back(
			Arrow(
				play_.bulletSpawns_[i].getPosition(),
				play_.bulletSpawns_[i].getRotation()));
	}

	EventQueue::getInstance().send(
		new EventPlaySound(
			11));
}

void ArrowPlayState::update(float deltaTime)
{
	durationClock_.update(deltaTime);

	if (durationClock_.isDone())
	{
		EventQueue::getInstance().send(
			new EventChangePlayState(
				PlayStateType::Wave));
	}

	for (Arrow &arrow : arrows_)
	{
		arrow.update(deltaTime);
	}

	play_.particlePool_.update(deltaTime);

	play_.player_.update(deltaTime);
	play_.player_.constrain(play_.bounds_); // TODO only update when moving

	play_.camera_.update(deltaTime);
}

void ArrowPlayState::updateOnKeyPress(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyPress(key);
}

void ArrowPlayState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyRelease(key);
}

void ArrowPlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-play_.camera_.getPosition());

	target.draw(play_.arenaSprite_, states);
	target.draw(play_.particlePool_, states);
	target.draw(play_.player_, states);

	for (const Arrow &arrow : arrows_)
	{
		target.draw(arrow, states);
	}

	target.draw(play_.bulletPool_, states);
	target.draw(play_.healthInterface_, states);
	target.draw(play_.scoreInterface_, states);
}