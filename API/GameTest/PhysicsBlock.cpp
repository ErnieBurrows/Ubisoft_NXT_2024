#include "stdafx.h"
#include "PhysicsBlock.h"
#include "SpriteManager.h"

void PhysicsBlock::PhysicsBlockCollisionHandler(PhysicsEntity& physicsBlock, PhysicsEntity& other)
{
	if (other.GetTag() == MAIL)
	{
		physicsBlock.SetGravityScale(0.3f);
		physicsBlock.SetRestutition(1.0f);
	}
}

PhysicsEntity PhysicsBlock::CreatePhysicsBlock(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity block(CreateSprite(PHYSICS_BLOCK));
	block.SetOnCollision(PhysicsBlockCollisionHandler);

	/*Set isPlaced so the object can be rendered.*/
	block.SetIsPlaced(true);

	/*Set the tag to be used for rendering purposes*/
	block.SetTag(PHYSICS_BLOCK);

	/*Sprite Settings*/
	block.GetSprite()->SetScale(scale);
	block.GetSprite()->SetAngle(angle);

	/*Physics Settings*/
	block.GetCollider().shape = AABB;
	block.SetPosition(position);
	block.SetGravityScale(0.0f);
	block.SetFriction(1.0f);

	/*Set inv mass like this so the player can affect the block and it will have a *somewhat "floaty" feel*/
	block.SetInvMass(0.01f);

	/*Setting the collider size to be based off of the size of the sprite*/
	block.SetColliderSize();
	block.GetCollider().extents = { block.GetColliderWidth(), block.GetColliderHeight() };

	return block;
}