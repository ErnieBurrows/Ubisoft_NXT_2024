#pragma once
#include "PhysicsEntity.h"
class StartButton
{
public:
	static void StartButtonCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateStartButton(Vector2 position, float scale, float angle);

};