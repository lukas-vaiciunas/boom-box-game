#include "Driver.h"
#include "MainMenuDriverState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "AudioData.h"
#include <SFML/Graphics/RenderTarget.hpp>

Driver::Driver() :
	DriverState(),
	Listener({ EventType::ChangeDriverState, EventType::Quit }),
	state_(nullptr),
	soundPool_(8),
	isLive_(true)
{
	this->changeState_(DriverStateType::MainMenu);

	AudioData::getInstance().playMusic(1);
}

Driver::~Driver()
{
	delete state_;
}

void Driver::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::ChangeDriverState:
			this->changeState_(
				static_cast<const EventChangeDriverState &>(ev).getType());
			break;
		case EventType::Quit:
			isLive_ = false;
			break;
	}
}

void Driver::update(float deltaTime)
{
	EventQueue::getInstance().dispatch();

	soundPool_.update();

	state_->update(deltaTime);
}

void Driver::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Driver::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonPress(button);
}

void Driver::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Driver::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Driver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

bool Driver::isLive() const
{
	return isLive_;
}

void Driver::changeState_(DriverStateType type)
{
	delete state_;

	switch (type)
	{
		case DriverStateType::MainMenu:
			state_ = new MainMenuDriverState();
			break;
		case DriverStateType::Play:
			state_ = new PlayDriverState();
			break;
	}
}