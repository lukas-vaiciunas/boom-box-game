#include "HealthInterface.h"
#include "Event.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

HealthInterface::HealthInterface() :
	Listener({ EventType::UpdateHealthInterface }),
	sf::Drawable(),
	sprites_()
{}

void HealthInterface::onEvent(const Event &ev)
{
	this->update_(
		static_cast<const EventUpdateHealthInterface &>(ev).getHealth());
}

void HealthInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const sf::Sprite &sprite : sprites_)
	{
		target.draw(sprite, states);
	}
}

void HealthInterface::update_(uint8_t health)
{
	if (sprites_.size() < health)
	{
		const sf::Texture &heartTexture = TextureData::getInstance().getTexture(21);

		while (sprites_.size() < health)
		{
			sf::Sprite sprite(heartTexture);

			sprite.setPosition(
				sf::Vector2f(
					12.0f + 8.0f * sprites_.size(),
					60.0f));

			const sf::FloatRect spriteLocalBounds = sprite.getLocalBounds();

			sprite.setOrigin(
				sf::Vector2f(
					spriteLocalBounds.width * 0.5f,
					spriteLocalBounds.height * 0.5f));

			sprites_.push_back(std::move(sprite));
		}
	}
	else if (sprites_.size() > health)
	{
		while (sprites_.size() > health)
		{
			sprites_.pop_back();
		}
	}
}