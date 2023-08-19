#pragma once

#include "OptionSelector.h"

class GameOverOptionSelector : public OptionSelector
{
public:
	GameOverOptionSelector();
private:
	void selectOption_() override;
};