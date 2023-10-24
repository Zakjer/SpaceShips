#include "StartScreen.h"

StartScreen::StartScreen() {

	//Informacje na g�rze ekranu startowego
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHiScore = new Texture("HI-SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });

	mPlayerOne->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);

	//Pozycjonowanie informacji
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
	mHiScore->Pos(VEC2_ZERO);
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));

	//"Rodzicem" TopBar jest StartScreen
	mTopBar->Parent(this);

	//Informacje o trybie gry
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);

	//Pozycjonowanie tryb�w gry
	mOnePlayerMode->Pos(Vector2(-18.0f,-35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));

	mPlayModes->Parent(this);
}

StartScreen::~StartScreen() {

	//Usuwanie informacji na g�rze ekranu
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mHiScore;
	mHiScore = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;

	//Usuwanie informacji o trybie gry
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
}

void StartScreen::Update() {

}

void StartScreen::Render() {

	mPlayerOne->Render();
	mHiScore->Render();
	mPlayerTwo->Render();

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
}