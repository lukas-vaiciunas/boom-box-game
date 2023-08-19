#pragma once

class AlarmClock
{
public:
	AlarmClock(float targetSecs);

	void update(float deltaTime);

	void resetSoft();
	void resetHard();

	bool isDone() const;
	float getTargetSecs() const;
	float getSecs() const;
private:
	float targetSecs_;
	float secs_;
};