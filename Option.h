#pragma once

#include "Shakable.h"
#include "Collidable.h"
#include <SFML/Graphics/Text.hpp>

class Option :
	public Shakable,
	public Collidable,
	public sf::Drawable
{
public:
	Option(
		const std::string &string,
		const sf::Vector2f &position,
		unsigned int fontSize);

	void update(float deltaTime) override;
	void updateOnMouseMove(const sf::Vector2f &worldMousePosition);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void startShaking();
	void stopShaking();

	bool isHovered() const;
private:
	sf::Text text_;

	bool isHovered_;
};