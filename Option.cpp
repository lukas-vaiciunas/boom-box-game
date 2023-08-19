#include "Option.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Option::Option(
	const std::string &string,
	const sf::Vector2f &position,
	unsigned int fontSize)
	:
	Shakable(0.25f, 0.0f),
	Collidable(position, sf::Vector2f()),
	sf::Drawable(),
	text_(string, FontData::getInstance().getFont(), fontSize),
	isHovered_(false)
{
	text_.setFillColor(sf::Color(236, 236, 236));

	text_.setScale(
		sf::Vector2f(
			Config::Font::scale,
			Config::Font::scale));

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left,
		textLocalBounds.top);

	const sf::FloatRect textGlobalBounds = text_.getGlobalBounds();

	size_.x = textGlobalBounds.width;
	size_.y = textGlobalBounds.height;

	position_.y -= size_.y * 0.5f;

	text_.setPosition(position_);
}

void Option::update(float deltaTime)
{
	Shakable::update(deltaTime);

	text_.setPosition(position_ + offset_);
}

void Option::updateOnMouseMove(const sf::Vector2f &worldMousePosition)
{
	isHovered_ = this->contains(worldMousePosition);
}

void Option::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text_, states);
}

void Option::startShaking()
{
	trauma_ = 1.0f;
}

void Option::stopShaking()
{
	trauma_ = 0.0f;
}

bool Option::isHovered() const
{
	return isHovered_;
}