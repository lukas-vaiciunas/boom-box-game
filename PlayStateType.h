#pragma once

#include <cstdint>

enum class PlayStateType : uint8_t
{
	Intro,
	Arrow,
	Wave,
	Death,
	GameOver
};