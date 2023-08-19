#pragma once

#include "Boundable.h"
#include <SFML/Graphics/Sprite.hpp>

class Arrow : public sf::Drawable
{
public:
	Arrow(const sf::Vector2f &position, float rotation);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	enum class State : uint8_t
	{
		Contract,
		Expand
	};

	State state_;

	sf::Sprite sprite_;

	float scale_;
	float minScale_;
	float maxScale_;
	float velScale_;
};