#include "stdafx.h"
#include "SlippyBlock.h"
#include "SpriteManager.h"

void SlippyBlock::SlippyBlockCollisionHandler(PhysicsEntity& slippyBlock, PhysicsEntity& other)
{
	if (other.GetTag() == MAIL)
	{
	other.SetSprite(CreateSprite(ICYMAIL), other.GetSprite()->GetScale());
	other.SetRestutition(0.0f);
	}
}

PhysicsEntity SlippyBlock::CreateSlippyBlock(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity block(CreateSprite(ICE_BLOCK));
	block.SetOnCollision(SlippyBlockCollisionHandler);

	/*Set isPlaced so the object can be rendered.*/
	block.SetTag(ICE_BLOCK);

	/*Set the tag to be used for rendering purposes*/
	block.SetIsPlaced(true);

	/*Sprite Settings*/
	block.GetSprite()->SetScale(scale);
	block.GetSprite()->SetAngle(angle);
	
	/*Physics Settings*/
	block.GetCollider().shape = AABB;
	block.SetPosition(position);
	block.SetGravityScale(0.0f);
	block.SetInvMass(0.0000001f);

	/*Set friction and restitution to 0 since the object is supposed to be like ice (absorb impact and slippery)*/
	block.SetFriction(0.0f);
	block.SetRestutition(0.0f);

	/*Setting the collider size to be based off of the size of the sprite*/
	block.SetColliderSize();
	block.GetCollider().extents = { block.GetColliderWidth(), block.GetColliderHeight() };

	return block;
}
