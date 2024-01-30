#pragma once
#include "PhysicsEntity.h"
class Mail
{
public:
	static void MailCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other);
	static PhysicsEntity CreateMail(Vector2 position);
};

