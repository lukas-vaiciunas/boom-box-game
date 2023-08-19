#include "FontData.h"

FontData &FontData::getInstance()
{
	static FontData instance;
	return instance;
}

const sf::Font &FontData::getFont() const
{
	return font_;
}

FontData::FontData() :
	font_()
{
	font_.loadFromFile("./assets/font/chary___.ttf");
	font_.setSmooth(false);
}