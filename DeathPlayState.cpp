#include "DeathPlayState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

DeathPlayState::DeathPlayState(PlayDriverState &play) :
	PlayState(play),
	durationClock_(2.0f)
{
	EventQueue::getInstance().send(
		new EventSpawnParticle(
			play_.player_.getPosition() + play_.player_.getSize() * 0.5f,
			sf::Vector2f(0.0f, 0.0f),
			sf::Vector2f(0.0f, 0.0f),
			180.0f,
			2.0f,
			61));
}

void DeathPlayState::update(float deltaTime)
{
	durationClock_.update(deltaTime);

	if (durationClock_.isDone())
	{
		EventQueue::getInstance().send(
			new EventChangePlayState(
				PlayStateType::GameOver));
	}

	play_.bulletPool_.update(deltaTime, play_.player_, play_.bounds_);

	play_.particlePool_.update(deltaTime);

	play_.camera_.update(deltaTime);
}

void DeathPlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-play_.camera_.getPosition());

	target.draw(play_.arenaSprite_, states);
	target.draw(play_.particlePool_, states);
	target.draw(play_.bulletPool_, states);

	target.draw(play_.scoreInterface_, states);
}