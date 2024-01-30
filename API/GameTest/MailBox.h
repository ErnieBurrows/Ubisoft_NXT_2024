#pragma once
#include "PhysicsEntity.h"
class MailBox
{
public:
	static void MailBoxCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateMailBox(Vector2 position, float scale, float angle);

};

