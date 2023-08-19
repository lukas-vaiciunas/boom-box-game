#pragma once

#include "OptionSelector.h"

class MainMenuOptionSelector : public OptionSelector
{
public:
	MainMenuOptionSelector();
private:
	void selectOption_() override;
};