#ifndef _PHYSENTITY_H
#define _PHYSENTITY_H

#include <vector>

#include "Collider.h"

class PhysEntity : public GameEntity {

protected:


	std::vector<Collider*> mColliders;

	Collider* mBroadPhaseCollider;

public:

	PhysEntity();
	virtual ~PhysEntity();

	virtual void Render();

protected:

	void AddCollider(Collider* collider, Vector2 localpos = VEC2_ZERO);
};

#endif
