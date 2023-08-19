#pragma once

#include "SoundId.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>

class AudioData
{
public:
	typedef uint8_t MusicId;

	AudioData(const AudioData &) = delete;
	AudioData(AudioData &&) = delete;

	AudioData &operator=(const AudioData &) = delete;
	AudioData &operator=(AudioData &&) = delete;

	static AudioData &getInstance();

	void playMusic(MusicId id);

	const sf::SoundBuffer &getSoundBuffer(SoundId id) const;
private:
	AudioData();
	~AudioData() {}

	std::unordered_map<SoundId, sf::SoundBuffer> soundBuffers_;
	std::unordered_map<MusicId, std::string> musicFilePaths_;

	sf::Music music_;

	void loadSoundBuffers_(const std::string &filePath);
	void loadMusic_(const std::string &filePath);
};