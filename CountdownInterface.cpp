#include "CountdownInterface.h"
#include "Event.h"
#include "EventQueue.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

CountdownInterface::CountdownInterface() :
	sf::Drawable(),
	text_()
{
	text_.setFont(FontData::getInstance().getFont());
	text_.setCharacterSize(16);
	text_.setFillColor(
		sf::Color(64, 64, 64));
	text_.setPosition(
		sf::Vector2f(32.0f, 4.0f));
	text_.setScale(
		sf::Vector2f(
			Config::Font::scale,
			Config::Font::scale));
}

void CountdownInterface::update(float secs)
{
	std::string secsString = std::to_string(static_cast<uint8_t>(std::ceilf(secs)));

	if (text_.getString() == secsString)
	{
		return;
	}

	text_.setString(secsString);

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left + textLocalBounds.width * 0.5f,
		textLocalBounds.top + textLocalBounds.height * 0.5f);

	EventQueue::getInstance().send(
		new EventPlaySound(
			14));
}

void CountdownInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text_, states);
}