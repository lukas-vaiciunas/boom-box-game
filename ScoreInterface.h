#pragma once

#include "Listener.h"
#include <SFML/Graphics/Text.hpp>

class ScoreInterface :
	public Listener,
	public sf::Drawable
{
public:
	ScoreInterface();

	void onEvent(const Event &ev) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text text_;

	void update_(uint64_t score);
};