#include "IntroPlayState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

IntroPlayState::IntroPlayState(PlayDriverState &play) :
	PlayState(play),
	countdownInterface_(),
	durationClock_(3.0f)
{}

void IntroPlayState::update(float deltaTime)
{
	durationClock_.update(deltaTime);

	countdownInterface_.update(
		durationClock_.getTargetSecs() - durationClock_.getSecs());

	if (durationClock_.isDone())
	{
		EventQueue::getInstance().send(
			new EventChangePlayState(
				PlayStateType::Arrow));
	}

	play_.player_.update(deltaTime);
	play_.player_.constrain(play_.bounds_); // TODO only update when moving

	play_.camera_.update(deltaTime);
}

void IntroPlayState::updateOnKeyPress(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyPress(key);
}

void IntroPlayState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	play_.player_.updateOnKeyRelease(key);
}

void IntroPlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-play_.camera_.getPosition());

	target.draw(play_.arenaSprite_, states);
	target.draw(play_.player_, states);
	target.draw(play_.healthInterface_, states);
	target.draw(countdownInterface_, states);
}