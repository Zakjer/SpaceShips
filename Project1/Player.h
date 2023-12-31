#ifndef _PLAYER_H
#define _PLAYER_H
#include "../AnimatedTexture.h"
#include "../InputManager.h"
#include "../AudioManager.h"
#include "Bullet.h"

using namespace QuickSDL;

class Player : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	int mScore;
	int mLives;

	Texture* mShip;

	AnimatedTexture* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

private:
	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void WasHit();

	void Update();

	void Render();
};

#endif
