#pragma once

#include <SFML/Graphics/Text.hpp>

class CountdownInterface : public sf::Drawable
{
public:
	CountdownInterface();

	void update(float secs);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text text_;
};