#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "../AnimatedTexture.h"
#include "../InputManager.h"

using namespace QuickSDL;

class StartScreen : public GameEntity {

private:

	//Informacje na górze ekranu startowego
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;

	//Informacje o trybie gry
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;

public:

	StartScreen();
	~StartScreen();

	void Update();

	void Render();

};

#endif

