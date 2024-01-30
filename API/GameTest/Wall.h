#pragma once
#include "PhysicsEntity.h"
class Wall
{
public:
	static PhysicsEntity CreateWall(Vector2 position, Vector2 normal, float angle);
	static void WallCollisionHandler(PhysicsEntity& wall, PhysicsEntity& other);
	
};

