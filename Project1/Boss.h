#ifndef Boss_h
#define Boss_h

#include "Enemy.h"

class Boss : public Enemy {

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mCaptureDive;

	bool mWasHit;

private:

	Vector2 LocalFormationPosition();

	void HandleDiveState();

	void RenderDiveState();

public:

	static void CreateDivePaths();

	Boss(int index, int path, bool challengeStage);

	~Boss();

	void Dive(int type = 0);

	void Hit(PhysEntity* other) override;

};

#endif 
