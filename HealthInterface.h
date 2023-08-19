#pragma once

#include "Listener.h"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class HealthInterface :
	public Listener,
	public sf::Drawable
{
public:
	HealthInterface();

	void onEvent(const Event &ev) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<sf::Sprite> sprites_;

	void update_(uint8_t health);
};