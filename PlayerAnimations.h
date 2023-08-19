#pragma once

#include "TextureId.h"
#include "AlarmClock.h"
#include <SFML/Graphics/Sprite.hpp>

class PlayerAnimations : public sf::Drawable
{
public:
	enum class State : uint8_t
	{
		Idle,
		Walk
	};

	enum class Direction : uint8_t
	{
		Right,
		Left
	};

	PlayerAnimations(TextureId textureId, float frameSecs);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setState(State state);
	void setDirection(Direction direction);
	void setPosition(const sf::Vector2f &position);
private:
	State state_;
	Direction direction_;

	sf::Sprite sprite_;

	uint8_t frameWidth_;
	uint8_t frameHeight_;
	
	uint8_t numCols_;
	uint8_t col_;
	uint8_t row_;

	AlarmClock frameClock_;

	void updateRow_();
	void updateFrameRect_();
};