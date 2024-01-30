#pragma once
#include "PhysicsEntity.h"
class SlippyBlock
{
public:
	static void SlippyBlockCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateSlippyBlock(Vector2 position, float scale, float angle);

};