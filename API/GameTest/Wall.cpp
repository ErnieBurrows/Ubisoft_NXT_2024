#include "stdafx.h"
#include "Wall.h"
#include "MyMath.h"
#include "SpriteManager.h"
#include "SlingShot.h"

void Wall::WallCollisionHandler(PhysicsEntity& wall, PhysicsEntity& other)
{
	if (other.GetTag() == MAIL)
	{
		if (other.GetLivesLeft() != 0)
			other.ResetPlayer();
	}
}

PhysicsEntity Wall::CreateWall(Vector2 position, Vector2 normal, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity wall(CreateSprite(WALL));
	wall.SetOnCollision(WallCollisionHandler);

	/*Set the tag to be used for rendering purposes*/
	wall.SetTag(WALL);

	/*Set isPlaced so the object can be rendered.*/
	wall.SetIsPlaced(true);

	/*Set InvMass to 0.0f to make this a non dynamic object*/
	wall.SetInvMass(0.0f);

	/*Set sprite angle to be based on the normal of each wall*/
	wall.GetSprite()->SetAngle(DEG_TO_RAD(angle));

	if (wall.GetSprite()->GetAngle() > 0)
		wall.GetCollider().extents = { 0.06f,0.92f };
	else
		wall.GetCollider().extents = { 0.92f,0.06f };

	/*Physics Settings*/
	wall.GetCollider().shape = AABB;
	wall.SetPosition(position);
	wall.SetFriction(1.0f);
	wall.SetGravityScale(0.0f);

	return wall;
}