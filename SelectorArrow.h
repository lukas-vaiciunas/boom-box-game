#pragma once

#include <SFML/Graphics/Sprite.hpp>

class SelectorArrow : public sf::Drawable
{
public:
	SelectorArrow();

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setPosition(const sf::Vector2f &position);
private:
	enum class State : uint8_t
	{
		Left,
		Right
	};

	State state_;

	sf::Sprite sprite_;

	sf::Vector2f anchorPosition_;

	float speed_;
	float maxOffsetX_;
	float offsetX_;

};