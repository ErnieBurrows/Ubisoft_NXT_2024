#pragma once
#include "PhysicsEntity.h"
class BouncyBlock
{
public:
	static void BouncyBlockCollisionHandler(PhysicsEntity& bouncyBlock, PhysicsEntity& other);
	static PhysicsEntity CreateBouncyBlock(Vector2 position, float scale, float angle);

};
