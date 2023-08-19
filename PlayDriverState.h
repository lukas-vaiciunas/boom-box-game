#pragma once

class PlayState;

#include "DriverState.h"
#include "PlayStateType.h"
#include "Player.h"
#include "BulletSpawn.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "Camera.h"
#include "Score.h"
#include "HealthInterface.h"
#include "ScoreInterface.h"

class PlayDriverState :
	public DriverState,
	public Listener
{
public:
	PlayDriverState();

	~PlayDriverState();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	friend class IntroPlayState;
	friend class ArrowPlayState;
	friend class WavePlayState;
	friend class DeathPlayState;
	friend class GameOverPlayState;

	PlayState *state_;

	std::vector<BulletSpawn> bulletSpawns_;
	std::unordered_set<size_t> selectedBulletSpawns_;
	Player player_;
	BulletPool bulletPool_;
	ParticlePool particlePool_;
	Camera camera_;
	Score score_;
	HealthInterface healthInterface_;
	ScoreInterface scoreInterface_;
	Boundable bounds_;
	sf::Sprite arenaSprite_;

	uint64_t wave_;
	uint8_t numBullets_;
	float bulletSpeed_;
	float arrowDurationSecs_;

	void incrementWave_();
	void changeState_(PlayStateType type);
};