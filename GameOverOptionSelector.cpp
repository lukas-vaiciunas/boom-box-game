#include "GameOverOptionSelector.h"
#include "Event.h"
#include "EventQueue.h"

GameOverOptionSelector::GameOverOptionSelector() :
	OptionSelector(
		{
			"Retry",
			"Main"
		})
{}

void GameOverOptionSelector::selectOption_()
{
	OptionSelector::selectOption_();

	switch (selectedOptionIndex_)
	{
		case 0:
			EventQueue::getInstance().send(
				new EventChangeDriverState(
					DriverStateType::Play));
			break;
		case 1:
			EventQueue::getInstance().send(
				new EventChangeDriverState(
					DriverStateType::MainMenu));
			break;
	}
}