#pragma once
#include "PhysicsEntity.h"
class QuitButton
{
public:
	static void QuitButtonCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateQuitButton(Vector2 position, float scale, float angle);
};

