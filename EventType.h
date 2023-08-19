#pragma once

#include <cstdint>

enum class EventType : uint8_t
{
	Quit,
	ChangeDriverState,
	ChangePlayState,
	ShakeCamera,
	HurtPlayer,
	SpawnBullet,
	SpawnParticle,
	AddScore,
	PlaySound,
	UpdateHealthInterface,
	UpdateScoreInterface
};