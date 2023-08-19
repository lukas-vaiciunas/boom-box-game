#include "GameOverPlayState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

GameOverPlayState::GameOverPlayState(PlayDriverState &play) :
	PlayState(play),
	optionSelector_()
{}

void GameOverPlayState::update(float deltaTime)
{
	optionSelector_.update(deltaTime);
}

void GameOverPlayState::updateOnMouseMove(int mouseX, int mouseY)
{
	const float invGameScale = 1.0f / Config::Game::scale;

	sf::Vector2f scaledMousePosition(
		mouseX * invGameScale,
		mouseY * invGameScale);

	optionSelector_.updateOnMouseMove(
		scaledMousePosition + play_.camera_.getPosition());
}

void GameOverPlayState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	optionSelector_.updateOnMouseButtonPress(button);
}

void GameOverPlayState::updateOnKeyPress(sf::Keyboard::Key key)
{
	// Escaping to Main Menu is already handled by PlayDriverState::updateOnKeyPress

	if (key == sf::Keyboard::Key::R)
	{
		EventQueue::getInstance().send(
			new EventChangeDriverState(
				DriverStateType::Play));
	}
	else
	{
		optionSelector_.updateOnKeyPress(key);
	}
}

void GameOverPlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-play_.camera_.getPosition());

	target.draw(play_.arenaSprite_, states);

	target.draw(play_.scoreInterface_, states);

	target.draw(optionSelector_, states);
}