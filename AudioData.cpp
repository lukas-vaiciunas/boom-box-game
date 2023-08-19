#include "AudioData.h"
#include <fstream>
#include <sstream>

AudioData &AudioData::getInstance()
{
	static AudioData instance;
	return instance;
}

void AudioData::playMusic(MusicId id)
{
	music_.openFromFile(musicFilePaths_.at(id));
	music_.setLoop(true);
	music_.setVolume(25.0f);
	music_.play();
}

const sf::SoundBuffer &AudioData::getSoundBuffer(SoundId id) const
{
	return soundBuffers_.at(id);
}

AudioData::AudioData() :
	soundBuffers_(),
	musicFilePaths_(),
	music_()
{
	this->loadSoundBuffers_("./data/sounds.txt");
	this->loadMusic_("./data/music.txt");
}

void AudioData::loadSoundBuffers_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in AudioData::loadSoundBuffers_!\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		int soundBufferId;
		std::string soundBufferFilePath;

		ss.clear();
		ss.str(line);

		ss >> soundBufferId >> soundBufferFilePath;

		sf::SoundBuffer soundBuffer;

		soundBuffer.loadFromFile(soundBufferFilePath);

		soundBuffers_.emplace(soundBufferId, std::move(soundBuffer));
	}

	in.close();
}

void AudioData::loadMusic_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in AudioData::loadMusic_!\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		int musicId;
		std::string musicFilePath;

		ss.clear();
		ss.str(line);

		ss >> musicId >> musicFilePath;

		musicFilePaths_.emplace(musicId, musicFilePath);
	}

	in.close();
}