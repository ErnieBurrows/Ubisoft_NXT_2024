#include "stdafx.h"
#include "PhysicsEntity.h"
#include "SlingShot.h"
#include "SpriteManager.h"

PhysicsEntity* PhysicsEntity::pairTeleporter = nullptr;
bool PhysicsEntity::isFirstTelporter = true;

void PhysicsEntity::SetPosition(Vector2 position){
	this->position = position;
}

void PhysicsEntity::SetVelocity(Vector2 velocity){
	this->velocity = velocity;
}

void PhysicsEntity::SetAccelleration(Vector2 accelleration){
	this->accelleration = accelleration;
}

void PhysicsEntity::SetForce(Vector2 force){
	this->force = force;
}

void PhysicsEntity::SetGravityScale(float gravityScale){
	this->gravityScale = gravityScale;
}

void PhysicsEntity::SetInvMass(float invMass){
	this->invMass = invMass;
}

void PhysicsEntity::SetFriction(float friction){
	this->friction = friction;
}

void PhysicsEntity::SetRestutition(float restitution){
	this->restitution = restitution;
}

void PhysicsEntity::SetTougness(float toughness){
	this->tougness = toughness;
}

void PhysicsEntity::SetDisabled(bool Disabled){
	this->disabled = disabled;
}

void PhysicsEntity::SetIsPlaced(bool isPlaced){
	this->isPlaced = isPlaced;
}

void PhysicsEntity::SetHasWon(bool hasWon){
    this->hasWon = hasWon;
}

void PhysicsEntity::SetCollider(Collider collider) {
	this->collider = collider;
}

void PhysicsEntity::SetOnCollision(OnCollision onCollision){
	this->onCollision = onCollision;
}

void PhysicsEntity::SetTag(SpriteType tag){
	this->tag = tag;
}

void PhysicsEntity::SetSprite(CSimpleSprite* sprite, float scale){
	this->sprite = sprite;
    this->sprite->SetScale(scale);
}

void PhysicsEntity::SetMinSize(float minSize){
    this->minSize = minSize;
}

void PhysicsEntity::SetMaxSize(float maxSize){
    this->maxSize = maxSize;
}

void PhysicsEntity::SetLivesLeft(int livesLeft){
    this->livesLeft = livesLeft;
}

void PhysicsEntity::ResetPlayer(){
   SetPosition(SlingShot::initalPosition);
   SetVelocity(Vector2Zero);
   SetGravityScale(0.0f);
   SetRestutition(1.0f);
   SetFriction(0.05f);
   SetInvMass(1.5f);
   SetSprite(CreateSprite(GetTag()), GetSprite()->GetScale());
   SetIsPlaced(false);

   SetLivesLeft(GetLivesLeft() - 1);
}


void PhysicsEntity::SetColliderSize() {
#if APP_USE_VIRTUAL_RES
    float scaleX;
    float scaleY;
    if (GetSprite()->GetAngle() > 0)
    {
        // Convert virtual screen space size to native screen space
        scaleX = (GetSprite()->GetScale() / APP_VIRTUAL_WIDTH) / 2.0f;  //Dividing by 2 due to the extents being half width and half height.
        scaleY = (GetSprite()->GetScale() / APP_VIRTUAL_HEIGHT) / 1.1f;
    }
    else
    {
        scaleX = (GetSprite()->GetScale() / APP_VIRTUAL_WIDTH) / 1.1f;
        scaleY = (GetSprite()->GetScale() / APP_VIRTUAL_HEIGHT) / 2.0f;
    }

    colliderWidth = GetSprite()->GetWidth() * scaleX;
    colliderHeight = GetSprite()->GetHeight() * scaleY;
#else
    m_colliderWidth = m_width;
    m_colliderHeight = m_height;
#endif
}


