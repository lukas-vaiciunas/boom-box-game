#pragma once

#include "DriverState.h"
#include "Listener.h"
#include "DriverStateType.h"
#include "SoundPool.h"

class Driver :
	public DriverState,
	public Listener
{
public:
	Driver();

	~Driver();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
private:
	DriverState *state_;

	SoundPool soundPool_;

	bool isLive_;

	void changeState_(DriverStateType type);
};