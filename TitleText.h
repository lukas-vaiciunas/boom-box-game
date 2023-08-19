#pragma once

#include "Shakable.h"
#include <SFML/Graphics/Text.hpp>

class TitleText : public sf::Drawable
{
public:
	TitleText();

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	enum class State : uint8_t
	{
		Contract,
		Expand
	};

	State state_;

	sf::Text text_;

	float maxScale_;
	float minScale_;
	float scale_;
	float velScale_;
};