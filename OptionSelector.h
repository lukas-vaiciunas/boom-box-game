#pragma once

#include "SelectorArrow.h"
#include "Option.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class OptionSelector : public sf::Drawable
{
public:
	OptionSelector(const std::vector<std::string> &optionStrings);

	virtual ~OptionSelector() {}

	void update(float deltaTime);
	void updateOnMouseMove(const sf::Vector2f &worldMousePosition);
	void updateOnMouseButtonPress(sf::Mouse::Button button);
	void updateOnKeyPress(sf::Keyboard::Key key);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
	std::vector<Option> options_;
	SelectorArrow selectorArrow_;

	size_t selectedOptionIndex_;

	virtual void selectOption_();

	void decrementSelectedOptionIndex_();
	void incrementSelectedOptionIndex_();
	void updateSelectorPosition_();

	void setSelectedOptionIndex_(size_t index);
};