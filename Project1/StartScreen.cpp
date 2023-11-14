#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Informacje na górze ekranu startowego
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHiScore = new Texture("HI-SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerOneScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();
	mTopScore = new Scoreboard();
	

	mPlayerOne->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	//Pozycjonowanie informacji
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
	mHiScore->Pos(Vector2(-30.0f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.2f, 0.0f));

	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.23f, 40.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.05f, 40.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.32f, 40.0f));

	mTopScore->Score(30000);

	//"Rodzicem" TopBar jest StartScreen
	mTopBar->Parent(this);

	//Logo
	mLogo = new Texture("logo-spaceships.png");

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.34f));

	mLogo->Parent(this);

	//Informacje o trybie gry
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Cursor.png");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	//Pozycjonowanie trybów gry
	mOnePlayerMode->Pos(Vector2(-18.0f,-35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(-175.0f, -35.0f));

	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	ResetAnimation();

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen() {

	//Usuwanie informacji na górze ekranu
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mHiScore;
	mHiScore = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mPlayerTwoScore;
	mPlayerTwoScore = NULL;
	delete mTopScore;
	mTopScore = NULL;

	//Usuwanie logo
	delete mLogo;
	mLogo = NULL;

	//Usuwanie informacji o trybie gry
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mCursor;
	mCursor = NULL;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = Vector2(0.0f, 0.0f);
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {

	mSelectedMode += change;

	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::Update() {

	//Animacja ekranu
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			mStars->Scroll(false);
		}

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
			mAnimationTimer = mAnimationTotalTime;
	}
	else {
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
			ChangeSelectedMode(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP))
			ChangeSelectedMode(-1);
	}
}

void StartScreen::Render() {

	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	
	mPlayerOneScore->Render();
	mPlayerTwoScore->Render();
	mTopScore->Render();

	mLogo->Render();

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();
}