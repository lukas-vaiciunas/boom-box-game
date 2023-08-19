#include "Score.h"
#include "Event.h"
#include "EventQueue.h"

Score::Score() :
	Listener({ EventType::AddScore }),
	score_(0)
{
	this->reportScore_();
}

void Score::onEvent(const Event &ev)
{
	score_ += static_cast<const EventAddScore &>(ev).getScore();

	this->reportScore_();
}

void Score::reportScore_()
{
	EventQueue::getInstance().send(
		new EventUpdateScoreInterface(
			score_));
}