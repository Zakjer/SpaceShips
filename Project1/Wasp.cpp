#include "Wasp.h"
#include "BoxCollider.h"
#include "../AudioManager.h"

std::vector<std::vector<Vector2>> Wasp::sDivePaths;

void Wasp::CreateDivePaths() {

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(-60.0f, -45.0f), Vector2(-60.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(-60.0f, 0.0f), Vector2(-60.0f, 80.0f), Vector2(0.0f, 150.0f), Vector2(100.0f, 150.0f) }, 15);
	path->AddCurve({ Vector2(100.0f, 150.0f), Vector2(250.0f, 150.0f), Vector2(350.0f, 200.0f), Vector2(350.0f, 350.0f) }, 15);
	path->AddCurve({ Vector2(350.0f, 350.0f), Vector2(350.0f, 575.0f), Vector2(100.0f, 575.0f), Vector2(100.0f, 350.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;


	currentPath = 1;
	path = new BezierPath();


	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(60.0f, -45.0f), Vector2(60.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(60.0f, 0.0f), Vector2(60.0f, 80.0f), Vector2(0.0f, 150.0f), Vector2(-100.0f, 150.0f) }, 15);
	path->AddCurve({ Vector2(-100.0f, 150.0f), Vector2(-250.0f, 150.0f), Vector2(-350.0f, 200.0f), Vector2(-350.0f, 350.0f) }, 15);
	path->AddCurve({ Vector2(-350.0f, 350.0f), Vector2(-350.0f, 575.0f), Vector2(-100.0f, 575.0f), Vector2(-100.0f, 350.0f) }, 15);





	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);


	delete path;

}

Wasp::Wasp(int index, int path, bool challengeStage, bool diver)
	: Enemy(index, path, challengeStage)
{


	mDiver = diver;

	mTextures[0] = new Texture("wasp.png");
	mTextures[0]->Parent(this);
	mTextures[0]->Pos(VEC2_ZERO);

	mTextures[1] = new Texture("wasp_animated.png");
	mTextures[1]->Parent(this);
	mTextures[1]->Pos(VEC2_ZERO);

	mType = wasp;

	AddCollider(new BoxCollider(mTextures[1]->ScaledDimensions()));
}

Wasp::~Wasp() {


}

void Wasp::PathComplete() {

	Enemy::PathComplete();

}

void Wasp::FlyInComplete() {

	if (mDiver)
		mCurrentState = dead;
	else
		JoinFormation();

}

Vector2 Wasp::LocalFormationPosition() {

	Vector2 retVal;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) * pow(-1, mIndex % 2 + 1);
	retVal.y = sFormation->GridSize().y * 2 + sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;

}

void Wasp::HandleDiveState() {

	int currentPath = mIndex % 2;

	if (mCurrentWaypoint < sDivePaths[currentPath].size()) {

		Vector2 waypointPos = mDiveStartPosition + sDivePaths[currentPath][mCurrentWaypoint];

		Vector2 dist = waypointPos - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((waypointPos - Pos()).MagnitudeSqr() < EPSILON)
			mCurrentWaypoint++;
	}
	else {

		Vector2 dist = WorldFormationPosition() - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON)
			JoinFormation();
	}

}

void Wasp::RenderDiveState() {

	mTextures[0]->Render();
}

void Wasp::Hit(PhysEntity* other) {

	AudioManager::Instance()->PlaySFX("enemy_death.mp3", 0, 4);
	sPlayer->AddScore(mCurrentState == Enemy::formation ? 500 : 1000);
	Enemy::Hit(other);
}