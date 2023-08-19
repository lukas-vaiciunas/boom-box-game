#pragma once

#include "EventType.h"
#include "SoundId.h"
#include "TextureId.h"
#include "DriverStateType.h"
#include "PlayStateType.h"
#include <SFML/System/Vector2.hpp>

class Event
{
public:
	Event(EventType type) :
		type_(type)
	{}

	virtual ~Event() {}

	EventType getType() const
	{
		return type_;
	}
private:
	EventType type_;
};

class EventQuit : public Event
{
public:
	EventQuit() :
		Event(EventType::Quit)
	{}
};

class EventChangeDriverState : public Event
{
public:
	EventChangeDriverState(DriverStateType type) :
		Event(EventType::ChangeDriverState),
		type_(type)
	{}

	DriverStateType getType() const
	{
		return type_;
	}
private:
	DriverStateType type_;
};

class EventChangePlayState : public Event
{
public:
	EventChangePlayState(PlayStateType type) :
		Event(EventType::ChangePlayState),
		type_(type)
	{}

	PlayStateType getType() const
	{
		return type_;
	}
private:
	PlayStateType type_;
};

class EventShakeCamera : public Event
{
public:
	EventShakeCamera(float trauma) :
		Event(EventType::ShakeCamera),
		trauma_(trauma)
	{}

	float getTrauma() const
	{
		return trauma_;
	}
private:
	float trauma_;
};

class EventHurtPlayer : public Event
{
public:
	EventHurtPlayer() :
		Event(EventType::HurtPlayer)
	{}
};

class EventSpawnBullet : public Event
{
public:
	EventSpawnBullet(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		float rotation)
		:
		Event(EventType::SpawnBullet),
		position_(position),
		velocity_(velocity),
		rotation_(rotation)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	float getRotation() const
	{
		return rotation_;
	}
private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	float rotation_;
};

class EventSpawnParticle : public Event
{
public:
	EventSpawnParticle(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const sf::Vector2f &acceleration,
		float velRotation,
		float durationSecs,
		TextureId textureId)
		:
		Event(EventType::SpawnParticle),
		position_(position),
		velocity_(velocity),
		acceleration_(acceleration),
		velRotation_(velRotation),
		durationSecs_(durationSecs),
		textureId_(textureId)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	const sf::Vector2f &getAcceleration() const
	{
		return acceleration_;
	}

	float getVelRotation() const
	{
		return velRotation_;
	}

	float getDurationSecs() const
	{
		return durationSecs_;
	}

	TextureId getTextureId() const
	{
		return textureId_;
	}
private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	sf::Vector2f acceleration_;
	float velRotation_;
	float durationSecs_;
	TextureId textureId_;
};

class EventAddScore : public Event
{
public:
	EventAddScore(uint64_t score) :
		Event(EventType::AddScore),
		score_(score)
	{}

	uint64_t getScore() const
	{
		return score_;
	}
private:
	uint64_t score_;
};

class EventPlaySound : public Event
{
public:
	EventPlaySound(SoundId id) :
		Event(EventType::PlaySound),
		id_(id)
	{}

	SoundId getId() const
	{
		return id_;
	}
private:
	SoundId id_;
};

class EventUpdateHealthInterface : public Event
{
public:
	EventUpdateHealthInterface(uint8_t health) :
		Event(EventType::UpdateHealthInterface),
		health_(health)
	{}

	uint8_t getHealth() const
	{
		return health_;
	}
private:
	uint8_t health_;
};

class EventUpdateScoreInterface : public Event
{
public:
	EventUpdateScoreInterface(uint64_t score) :
		Event(EventType::UpdateScoreInterface),
		score_(score)
	{}

	uint64_t getScore() const
	{
		return score_;
	}
private:
	uint64_t score_;
};