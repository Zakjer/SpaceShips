#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius, bool broadPhase)
	: Collider(ColliderType::Circle)
{
	mRadius = radius;

	if (DEBUG_COLLIDERS) {

		if (broadPhase)
			SetDebugTexture(new Texture("BroadPhaseCollider.jpg"));
		else
			SetDebugTexture(new Texture("CircleCollider.jpg"));

		mDebugTexture->Scale(VEC2_ONE * (radius * 2 / 100.0f));
	}
}

CircleCollider::~CircleCollider() {

}

Vector2 CircleCollider::GetFurthestPoint() {

	return VEC2_RIGHT * (mRadius + Pos(GameEntity::local).Magnitude());
}

float CircleCollider::GetRadius() {

	return mRadius;
}