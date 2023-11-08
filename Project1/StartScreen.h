#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "../AnimatedTexture.h"
#include "../InputManager.h"
#include "BackgroundStars.h"
#include "Scoreboard.h"

using namespace QuickSDL;

class StartScreen : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;

	//Informacje na górze ekranu startowego
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;

	//Logo
	Texture* mLogo;

	//Informacje o trybie gry
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	//Animacja ekranu
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	BackgroundStars* mStars;


public:

	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int change);

	void Update();

	void Render();

};

#endif

