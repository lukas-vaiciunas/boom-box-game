#include "SoundPool.h"
#include "Event.h"
#include "AudioData.h"

SoundPool::SoundPool(Size capacity) :
	Pool(capacity),
	Listener({ EventType::PlaySound })
{}

void SoundPool::onEvent(const Event &ev)
{
	if (this->isFull_())
	{
		return;
	}

	sf::Sound *sound = new sf::Sound(
		AudioData::getInstance().getSoundBuffer(
			static_cast<const EventPlaySound &>(ev).getId()));

	sound->setVolume(50.0f);
	sound->play();

	this->add_(sound);
}

void SoundPool::update()
{
	for (Size i = 0; i < numLive_; )
	{
		if (objects_[i]->getStatus() == sf::Sound::Status::Stopped)
		{
			this->remove_(i);
		}
		else ++i;
	}
}