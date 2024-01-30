#include "stdafx.h"
//#include "TeleportBlock.h"
//#include "SpriteManager.h"
//
///*COULD NOT GET TELEPORT BLOCK WORKING -> RAN OUT OF TIME*/
//void TeleportBlock::TeleportBlockCollisionHandler(PhysicsEntity& teleporterBlock, PhysicsEntity& other)
//{
//	if (other.GetTag() == MAIL)
//	{
//		other.SetPosition(Vector2{ PhysicsEntity::pairTeleporter->GetPosition().x, PhysicsEntity::pairTeleporter->GetPosition().y - 0.5f });
//	}
//}
//
//PhysicsEntity TeleportBlock::CreateTeleportBlock(Vector2 position, float scale, float angle)
//{
//	/*TELEPORTBLOCK SPECIFIC SETTINGS*/
//	PhysicsEntity block(CreateSprite(TELEPORT_BLOCK));
//	block.SetTag(TELEPORT_BLOCK);
//	block.SetOnCollision(TeleportBlockCollisionHandler);
//	block.SetRestutition(0.0f);
//
//	if (PhysicsEntity::isFirstTelporter)
//	{
//		PhysicsEntity::isFirstTelporter = false;
//	}
//	else
//	{
//		PhysicsEntity::pairTeleporter = &block;
//		PhysicsEntity::pairTeleporter->SetPosition(block.GetPosition());
//	}
//	/*GENERIC AABB SETTINGS*/
//	block.SetIsPlaced(true);
//	block.GetSprite()->SetScale(scale);
//	block.GetCollider().shape = AABB;
//	block.SetPosition(position);
//	block.SetGravityScale(0.0f);
//	block.SetFriction(1.0f);
//	block.SetInvMass(0.0000001f);
//	block.GetSprite()->SetAngle(angle);
//
//	block.SetColliderSize();
//	block.GetCollider().extents = { block.GetColliderWidth(), block.GetColliderHeight() };
//	
//	return block;
//}
