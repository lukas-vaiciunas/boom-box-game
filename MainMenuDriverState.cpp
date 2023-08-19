#include "MainMenuDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

MainMenuDriverState::MainMenuDriverState() :
	DriverState(),
	arenaSprite_(TextureData::getInstance().getTexture(11)),
	ownerText_(
		"Created by Lukas Vaiciunas",
		FontData::getInstance().getFont(),
		16),
	titleText_(),
	optionSelector_(),
	camera_()
{
	ownerText_.setPosition(sf::Vector2f(32.0f, 60.0f));
	ownerText_.setFillColor(sf::Color(64, 64, 64));
	ownerText_.setScale(
		sf::Vector2f(
			Config::Font::scale * 0.25f,
			Config::Font::scale * 0.25f));

	const sf::FloatRect ownerTextLocalBounds = ownerText_.getLocalBounds();

	ownerText_.setOrigin(
		ownerTextLocalBounds.left + ownerTextLocalBounds.width * 0.5f,
		ownerTextLocalBounds.top + ownerTextLocalBounds.height * 0.5f);
}

void MainMenuDriverState::update(float deltaTime)
{
	titleText_.update(deltaTime);
	optionSelector_.update(deltaTime);
}

void MainMenuDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	const float invGameScale = 1.0f / Config::Game::scale;

	sf::Vector2f scaledMousePosition(
		mouseX * invGameScale,
		mouseY * invGameScale);

	optionSelector_.updateOnMouseMove(
		scaledMousePosition + camera_.getPosition());
}

void MainMenuDriverState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	optionSelector_.updateOnMouseButtonPress(button);
}

void MainMenuDriverState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Escape)
	{
		EventQueue::getInstance().send(
			new EventQuit());
	}
	else
	{
		optionSelector_.updateOnKeyPress(key);
	}
}

void MainMenuDriverState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		sf::Vector2f(
			Config::Game::scale,
			Config::Game::scale));

	states.transform.translate(-camera_.getPosition());

	target.draw(arenaSprite_, states);

	target.draw(titleText_, states);
	target.draw(ownerText_, states);

	target.draw(optionSelector_, states);
}