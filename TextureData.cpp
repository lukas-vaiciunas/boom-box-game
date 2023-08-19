#include "TextureData.h"
#include <fstream>
#include <sstream>

TextureData &TextureData::getInstance()
{
	static TextureData instance;
	return instance;
}

TextureData::TextureData() :
	textures_()
{
	this->load_("./data/textures.txt");
}

const sf::Texture &TextureData::getTexture(TextureId id) const
{
	return textures_.at(id);
}

void TextureData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in TextureData::load_!\n", filePath.c_str());
	}

	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		int textureId;
		std::string texturePath;

		ss.clear();
		ss.str(line);

		ss >> textureId >> texturePath;

		sf::Texture texture;

		texture.loadFromFile(texturePath);

		textures_.emplace(textureId, std::move(texture));
	}

	in.close();
}