#include "stdafx.h"
#include "QuitButton.h"
#include "SpriteManager.h"

void QuitButton::QuitButtonCollisionHandler(PhysicsEntity& mail, PhysicsEntity& other)
{
}

PhysicsEntity QuitButton::CreateQuitButton(Vector2 position, float scale, float angle)
{
	/*Creating instance of Physics Entity*/
	PhysicsEntity quitButton(CreateSprite(QUITBUTTON));
	quitButton.SetOnCollision(QuitButtonCollisionHandler);
	quitButton.SetTag(QUITBUTTON);

	/*Set is Placed for rendering purposes*/
	quitButton.SetIsPlaced(true);

	/*Sprite Settings*/
	quitButton.GetSprite()->SetScale(scale);
	quitButton.GetSprite()->SetAngle(angle);

	/*Set collider for mouse collision check*/
	quitButton.GetCollider().shape = AABB;
	quitButton.SetPosition(position);
	
	/*Setting the collider size to be based off of the size of the sprite*/
	quitButton.SetColliderSize();
	quitButton.GetCollider().extents = { quitButton.GetColliderWidth(), quitButton.GetColliderHeight() };


	return quitButton;
}
