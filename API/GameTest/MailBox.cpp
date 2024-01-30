#include "stdafx.h"
#include "MailBox.h"
#include "SpriteManager.h"


void MailBox::MailBoxCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other)
{
	if (other.GetTag() == MAIL)
	{
		mail.SetVelocity(Vector2Zero);
		mail.SetGravityScale(0.0f);
		mail.SetIsPlaced(false);

		other.SetHasWon(true);		
	}
}

PhysicsEntity MailBox::CreateMailBox(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity mailBox(CreateSprite(MAILBOX));
	mailBox.SetOnCollision(MailBoxCollisionHandler);

	/*Set the tag to be used for rendering purposes*/
	mailBox.SetTag(MAILBOX);

	/*Set isPlaced so the object can be rendered.*/
	mailBox.SetIsPlaced(true);

	/*Sprite Settings*/
	mailBox.GetSprite()->SetScale(0.5f); // Manually setting the mailbox so it can be larger then PhysicsEntities.maxSize
	mailBox.GetSprite()->SetAngle(angle);

	/*Physics Settings*/
	mailBox.GetCollider().shape = AABB;
	mailBox.SetPosition(position);
	mailBox.SetGravityScale(0.0f);
	mailBox.SetFriction(100.0f);
	mailBox.SetRestutition(0.0f);

	/*Set Inverse mass to a low float value so it is not affected by player, but it does not affect non dynamic objects(invMass value of 0)*/
	mailBox.SetInvMass(0.0000001f);

	/*Setting the collider size to be based off of the size of the sprite*/
	mailBox.SetColliderSize();
	mailBox.GetCollider().extents = { mailBox.GetColliderWidth(), mailBox.GetColliderHeight() };

	return mailBox;
}
