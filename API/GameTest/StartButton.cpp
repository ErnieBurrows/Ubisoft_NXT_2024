#include "stdafx.h"
#include "StartButton.h"
#include "SpriteManager.h"

void StartButton::StartButtonCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other)
{
}

PhysicsEntity StartButton::CreateStartButton(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity startButton(CreateSprite(STARTBUTTON));
	startButton.SetOnCollision(StartButtonCollisionHandler);
	startButton.SetTag(STARTBUTTON);

	/*Set is Placed for rendering purposes*/
	startButton.SetIsPlaced(true);

	/*Sprite Settings*/
	startButton.GetSprite()->SetScale(scale);
	startButton.GetSprite()->SetAngle(angle);

	/*Set collider for mouse collision check*/
	startButton.SetPosition(position);
	startButton.GetCollider().shape = AABB;

	/*Setting the collider size to be based off of the size of the sprite*/
	startButton.SetColliderSize();
	startButton.GetCollider().extents = { startButton.GetColliderWidth(), startButton.GetColliderHeight() };

	
	return startButton;
}
