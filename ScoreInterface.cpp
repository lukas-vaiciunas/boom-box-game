#include "ScoreInterface.h"
#include "Event.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

ScoreInterface::ScoreInterface() :
	Listener({ EventType::UpdateScoreInterface }),
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

void ScoreInterface::onEvent(const Event &ev)
{
	this->update_(
		static_cast<const EventUpdateScoreInterface &>(ev).getScore());
}

void ScoreInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text_, states);
}

void ScoreInterface::update_(uint64_t score)
{
	text_.setString(std::to_string(score));

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left + textLocalBounds.width * 0.5f,
		textLocalBounds.top + textLocalBounds.height * 0.5f);
}