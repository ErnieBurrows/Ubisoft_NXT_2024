#pragma once
#include "PhysicsEntity.h"
class Block
{
public:
	static void BlockCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateBlock(Vector2 position, float scale, float angle);

};