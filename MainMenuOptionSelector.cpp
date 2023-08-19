#include "MainMenuOptionSelector.h"
#include "Event.h"
#include "EventQueue.h"

MainMenuOptionSelector::MainMenuOptionSelector() :
	OptionSelector(
		{
			"Play",
			"Quit"
		})
{}

void MainMenuOptionSelector::selectOption_()
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
				new EventQuit());
			break;
	}
}