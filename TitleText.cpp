#include "TitleText.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

TitleText::TitleText() :
	sf::Drawable(),
	state_(State::Contract),
	text_("Boom Box", FontData::getInstance().getFont(), 16),
	maxScale_(Config::Font::scale),
	minScale_(Config::Font::scale * 0.9f),
	scale_(Config::Font::scale),
	velScale_(Config::Font::scale * 0.3f)
{
	text_.setFillColor(sf::Color(64, 64, 64));
	text_.setPosition(sf::Vector2f(32.0f, 4.0f));
	text_.setScale(sf::Vector2f(scale_, scale_));

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left + textLocalBounds.width * 0.5f,
		textLocalBounds.top + textLocalBounds.height * 0.5f);
}

void TitleText::update(float deltaTime)
{
	switch (state_)
	{
		case State::Contract:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Contract;
			}
			break;
	}

	text_.setScale(sf::Vector2f(scale_, scale_));
}

void TitleText::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text_, states);
}