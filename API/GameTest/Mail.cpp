#include "stdafx.h"
#include "Mail.h"
#include "app\app.h"
#include "Utils.h"
#include "SpriteManager.h"


void Mail::MailCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other)
{
}

PhysicsEntity Mail::CreateMail(Vector2 position)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity mail(CreateSprite(MAIL));
	mail.SetOnCollision(MailCollisionHandler);

	/*Set is Placed for rendering purposes*/
	mail.SetIsPlaced(true);
	mail.SetTag(MAIL);

	/*Set shape to be circle->This is the only circle in the game*/
	mail.GetCollider().SetShape(CIRCLE);

	/*Sprite Settings*/
	mail.GetSprite()->SetScale(0.8f);

	/*Manually setting the scale and the radius of the sprite to be equal*/
	mail.GetCollider().radius = 0.1f;
	mail.SetPosition(position);
	mail.SetRestutition(1.0f);
	mail.SetInvMass(1.5f);

	return mail;
}

