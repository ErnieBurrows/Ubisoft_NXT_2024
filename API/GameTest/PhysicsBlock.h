#pragma once
#include "PhysicsEntity.h"
class PhysicsBlock
{
public:
	static void PhysicsBlockCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreatePhysicsBlock(Vector2 position, float scale, float angle);

};