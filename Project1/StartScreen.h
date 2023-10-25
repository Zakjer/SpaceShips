#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "../AnimatedTexture.h"
#include "../InputManager.h"

using namespace QuickSDL;

class StartScreen : public GameEntity {

private:

	Timer* mTimer;

	//Informacje na górze ekranu startowego
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;

	//Logo
	Texture* mLogo;

	//Informacje o trybie gry
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;

	//Animacja ekranu
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;


public:

	StartScreen();
	~StartScreen();

	void Update();

	void Render();

};

#endif

