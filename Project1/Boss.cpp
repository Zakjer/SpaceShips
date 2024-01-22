#include "Boss.h"
#include "BoxCollider.h"
#include "../AudioManager.h"

std::vector<std::vector<Vector2>> Boss::sDivePaths;

void Boss::CreateDivePaths() {

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(-90.0f, -60.0f), Vector2(-90.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(-90.0f, 0.0f), Vector2(-90.0f, 60.0f), Vector2(-100.0f, 272.0f), Vector2(-15.0f, 275.0f) }, 15);
	path->AddCurve({ Vector2(-15.0f, 275.0f), Vector2(85.0f, 275.0f), Vector2(85.0f, 125.0f), Vector2(-15.0f, 125.0f) }, 15);
	path->AddCurve({ Vector2(-15.0f, 125.0f), Vector2(-175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(120.0f, 450.0f) }, 15);
	path->AddCurve({ Vector2(120.0f, 450.0f), Vector2(160.0f, 450.0f), Vector2(200.0f, 500.0f), Vector2(200.0f, 550.0f) }, 15);
	path->AddCurve({ Vector2(200.0f, 550.0f), Vector2(200.0f, 540.0f), Vector2(200.0f, 810.0f), Vector2(200.0f, 800.0f) }, 1);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(90.0f, -60.0f), Vector2(90.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(90.0f, 0.0f), Vector2(90.0f, 60.0f), Vector2(100.0f, 272.0f), Vector2(15.0f, 275.0f) }, 15);
	path->AddCurve({ Vector2(15.0f, 275.0f), Vector2(-85.0f, 275.0f), Vector2(-85.0f, 125.0f), Vector2(15.0f, 125.0f) }, 15);
	path->AddCurve({ Vector2(15.0f, 125.0f), Vector2(175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(-120.0f, 450.0f) }, 15);
	path->AddCurve({ Vector2(-120.0f, 450.0f), Vector2(-160.0f, 450.0f), Vector2(-200.0f, 500.0f), Vector2(-200.0f, 550.0f) }, 15);
	path->AddCurve({ Vector2(-200.0f, 550.0f), Vector2(-200.0f, 540.0f), Vector2(-200.0f, 810.0f), Vector2(-200.0f, 800.0f) }, 1);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

}

Boss::Boss(int index, int path, bool ChallengeStage)
	: Enemy(index, path, ChallengeStage)
{

	mTextures[0] = new Texture("boss.png");
	mTextures[0]->Parent(this);
	mTextures[0]->Pos(VEC2_ZERO);

	mTextures[1] = new Texture("boss_animated.png");
	mTextures[1]->Parent(this);
	mTextures[1]->Pos(VEC2_ZERO);

	mType = boss;

	AddCollider(new BoxCollider(mTextures[1]->ScaledDimensions()));

	mWasHit = false;
}

Boss::~Boss() {


}

Vector2 Boss::LocalFormationPosition() {

	Vector2 retVal;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 2)) * pow(-1, mIndex % 2 + 1);
	retVal.y = -sFormation->GridSize().y;

	return retVal;

}


void Boss::HandleDiveState() {

	int currentPath = mIndex % 2;

	if (mCaptureDive)
		currentPath += 2;

	if (mCurrentWaypoint < sDivePaths[currentPath].size()) {

		Vector2 waypointPos = mDiveStartPosition + sDivePaths[currentPath][mCurrentWaypoint];

		Vector2 dist = waypointPos - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((waypointPos - Pos()).MagnitudeSqr() < EPSILON)
			mCurrentWaypoint++;

		if (mCurrentWaypoint == sDivePaths[currentPath].size())
			Pos(Vector2(WorldFormationPosition().x, 20.0f));
	}
	else {

		Vector2 dist = WorldFormationPosition() - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON)
			JoinFormation();

	}

}

void Boss::RenderDiveState() {

	mTextures[0]->Render();

	int currentPath = mIndex % 2;

	if (mCaptureDive)
		currentPath += 2;

}

void Boss::Dive(int type) {
	mCaptureDive = type != 0;

	Enemy::Dive();
}

void Boss::Hit(PhysEntity* other) {

	if (mWasHit) {

		Enemy::Hit(other);
		AudioManager::Instance()->PlaySFX("boss_injured.mp3", 0, 2);
	}
	else {
		mWasHit = true;
		delete mTextures[0];
		mTextures[0] = new Texture("bosshit.png");
		mTextures[0]->Parent(this);
		mTextures[0]->Pos(VEC2_ZERO);
		mTextures[0]->Rotation(0.0f);

		delete mTextures[1];
		mTextures[1] = new Texture("bosshit_animated.png");
		mTextures[1]->Parent(this);
		mTextures[1]->Pos(VEC2_ZERO);
		mTextures[1]->Rotation(0.0f);

		sPlayer->AddScore(mCurrentState == Enemy::formation ? 150 : mCaptureDive ? 4000 : 8000);
		AudioManager::Instance()->PlaySFX("boss_death.mp3", 0, 1);
	}
}