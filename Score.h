#pragma once

#include "Listener.h"

class Score : public Listener
{
public:
	Score();

	void onEvent(const Event &ev) override;
private:
	uint64_t score_;

	void reportScore_();
};