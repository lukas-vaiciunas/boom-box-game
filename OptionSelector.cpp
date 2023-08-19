#include "OptionSelector.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "FontData.h"
#include <SFML/Graphics/RenderTarget.hpp>

OptionSelector::OptionSelector(const std::vector<std::string> &optionStrings) :
	sf::Drawable(),
	options_(),
	selectorArrow_(),
	selectedOptionIndex_(0)
{
	const unsigned int fontSize = 16;

	const float gap = 2.0f;
	const float lineHeight = fontSize * 0.5f + gap;

	float x = 25.0f;
	float startY = 32.0f - ((optionStrings.size() - 1) * lineHeight + gap) * 0.5f;

	for (size_t i = 0; i < optionStrings.size(); ++i)
	{
		options_.push_back(
			Option(
				optionStrings[i],
				sf::Vector2f(x, startY + lineHeight * i),
				16));
	}

	options_[selectedOptionIndex_].startShaking();

	this->updateSelectorPosition_();
}

void OptionSelector::update(float deltaTime)
{
	for (Option &option : options_)
	{
		option.update(deltaTime);
	}

	selectorArrow_.update(deltaTime);
}

void OptionSelector::updateOnMouseMove(const sf::Vector2f &worldMousePosition)
{
	for (size_t i = 0; i < options_.size(); ++i)
	{
		options_[i].updateOnMouseMove(worldMousePosition);

		if (options_[i].isHovered())
		{
			this->setSelectedOptionIndex_(i);
			break;
		}
	}
}

void OptionSelector::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left
		|| !options_[selectedOptionIndex_].isHovered())
	{
		return;
	}

	this->selectOption_();
}

void OptionSelector::updateOnKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
		case sf::Keyboard::Key::Up:
			this->decrementSelectedOptionIndex_();
			break;
		case sf::Keyboard::Key::S:
		case sf::Keyboard::Key::Down:
			this->incrementSelectedOptionIndex_();
			break;
		case sf::Keyboard::Key::Space:
		case sf::Keyboard::Key::Enter:
			this->selectOption_();
			break;
	}
}

void OptionSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const Option &option : options_)
	{
		target.draw(option, states);
	}

	target.draw(selectorArrow_, states);
}

void OptionSelector::selectOption_()
{
	EventQueue::getInstance().send(
		new EventPlaySound(
			2));
}

void OptionSelector::decrementSelectedOptionIndex_()
{
	this->setSelectedOptionIndex_(
		(selectedOptionIndex_ == 0)
			? options_.size() - 1
			: selectedOptionIndex_ - 1);
}

void OptionSelector::incrementSelectedOptionIndex_()
{
	this->setSelectedOptionIndex_(
		(selectedOptionIndex_ + 1) % options_.size());
}

void OptionSelector::updateSelectorPosition_()
{
	const sf::Vector2f &selectedOptionPosition = options_[selectedOptionIndex_].getPosition();

	selectorArrow_.setPosition(
		sf::Vector2f(
			selectedOptionPosition.x - 5.0f,
			selectedOptionPosition.y + options_[selectedOptionIndex_].getSize().y * 0.5f));
}

void OptionSelector::setSelectedOptionIndex_(size_t index)
{
	if (selectedOptionIndex_ == index)
	{
		return;
	}

	options_[selectedOptionIndex_].stopShaking();

	selectedOptionIndex_ = index;

	options_[selectedOptionIndex_].startShaking();

	this->updateSelectorPosition_();

	EventQueue::getInstance().send(
		new EventPlaySound(
			1));
}