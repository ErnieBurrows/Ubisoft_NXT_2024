#include "stdafx.h"
#include "BouncyBlock.h"
#include "SpriteManager.h"

void BouncyBlock::BouncyBlockCollisionHandler(PhysicsEntity& bouncyBlock, PhysicsEntity& other)
{
	if (other.GetTag() == MAIL)
	{
		other.SetVelocity(other.GetVelocity() + other.GetVelocity() * 3.0f);
	}
}

PhysicsEntity BouncyBlock::CreateBouncyBlock(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/ 
	PhysicsEntity block(CreateSprite(BOUNCY_BLOCK));
	block.SetOnCollision(BouncyBlockCollisionHandler);

	/*Set the tag to be used for rendering purposes*/
	block.SetTag(BOUNCY_BLOCK);

	/*Set isPlaced so the object can be rendered.*/
	block.SetIsPlaced(true);

	/*Set Friction on the bouncy block to 0 to make not affect the players increased velocity off of the block*/
	block.SetFriction(0.0f);

	/*Sprite Settings*/
	block.GetSprite()->SetScale(scale);
	block.GetSprite()->SetAngle(angle);

	/*Physics Settings*/
	block.SetPosition(position);
	block.GetCollider().shape = AABB;
	block.SetGravityScale(0.0f);

	/*Set Inverse mass to a low float value so it is not affected by player, but it does not affect non dynamic objects(invMass value of 0)*/
	block.SetInvMass(0.0000001f);

	/*Setting the collider size to be based off of the size of the sprite*/
	block.SetColliderSize();
	block.GetCollider().extents = { block.GetColliderWidth(), block.GetColliderHeight() };

	

	return block;
}
