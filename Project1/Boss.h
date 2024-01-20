#ifndef Boss_h
#define Boss_h


#include "Enemy.h"

class Boss : public Enemy {

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mCaptureDive;

private:


	Vector2 LocalFormationPosition();

	void HandleDiveState();
	void HandleDeadState();

	void RenderDiveState();
	void RenderDeadState();


public:

	static void CreateDivePaths();

	Boss(int index, int path, bool challengeStage);

	~Boss();

	void Dive(int type = 0);

};

#endif 
