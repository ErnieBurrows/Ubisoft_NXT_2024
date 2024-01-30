#include "stdafx.h"
#include "Block.h"
#include "SpriteManager.h"

void Block::BlockCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other)
{

}

PhysicsEntity Block::CreateBlock(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity block(CreateSprite(REGULAR_BLOCK));
	block.SetOnCollision(BlockCollisionHandler);

	/*Set the tag to be used for rendering purposes*/
	block.SetTag(REGULAR_BLOCK);

	/*Set isPlaced so the object can be rendered.*/
	block.SetIsPlaced(true); // 

	/*Sprite Settings*/
	block.GetSprite()->SetScale(scale);
	block.SetPosition(position);
	block.GetSprite()->SetAngle(angle);

	/*Settings for physics engine*/
	block.GetCollider().shape = AABB;
	block.SetGravityScale(0.0f);
	block.SetFriction(1.0f);
	block.SetInvMass(0.0000001f);

	/*Setting the collider size to be based off of the size of the sprite*/
	block.SetColliderSize();
	block.GetCollider().extents = { block.GetColliderWidth(), block.GetColliderHeight()};
	
	
	return block;
}
