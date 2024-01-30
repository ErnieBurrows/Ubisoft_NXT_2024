#pragma once
#include "vector"
#include "app\app.h"
#include "MyMath.h"
#include "Enums.h"

//OnCollision function pointer
class PhysicsEntity;
using OnCollision = void(*)(PhysicsEntity& self, PhysicsEntity& other);


struct Collider
{
	union
	{
		Vector2 normal{};
		Vector2 extents;
		float radius;
	};

	Shape shape = CIRCLE;

	void SetShape(Shape shape) {
		this->shape = shape;
	}
	void SetNormal(Vector2 normal) {
		this->normal = normal;
	}
	void SetRadius(float& radius) {
		this->radius = radius;
	}
};

class PhysicsEntity
{
public:
	PhysicsEntity() { sprite = nullptr; }
	PhysicsEntity(CSimpleSprite* sprite) {
		this->sprite = sprite;
	}

	/*GETTER FUNCTIONS*/
	bool GetIsDisabled() const{ return disabled; }
	bool GetIsPlaced() const{ return isPlaced; }
	bool GetHasWon() const{ return hasWon; }

	int GetLivesLeft() const { return livesLeft; }
	float GetColliderWidth() const{ return colliderWidth; }
	float GetColliderHeight() const { return colliderHeight; }
	float GetInvMass() const{ return invMass; }
	float GetRestitiution() const{ return restitution; }
	float GetGravityScale() const{ return gravityScale; }
	float GetFriction() const{ return friction; }
	float GetTougness() const{ return tougness; }
	float GetMinSize() const { return minSize; }
	float GetMaxSize() const { return maxSize; }

	Vector2 GetPosition() const{ return position; }
	Vector2 GetVelocity() const{ return velocity; }
	Vector2 GetForce() const { return force; }	
	Vector2 GetAccelleration() const { return accelleration; }
	Collider& GetCollider() { return collider; }
	Collider GetCollider() const { return collider; }
	OnCollision GetOnCollision() const { return onCollision; }
	SpriteType GetTag() const { return tag; }
	CSimpleSprite* GetSprite() const  { return sprite; }


	/*SETTER FUNCTIONS*/
	void SetPosition(Vector2 position);
	void SetVelocity(Vector2 velocity);
	void SetAccelleration(Vector2 accelleration);
	void SetForce(Vector2 force);

	void SetGravityScale(float gravityScale);
	void SetInvMass(float invMass);
	void SetFriction(float friction);
	void SetRestutition(float restitution);
	void SetTougness(float toughness);

	void SetDisabled(bool isDisabled);
	void SetIsPlaced(bool isPlaced);
	void SetHasWon(bool hasWon);

	void SetCollider(Collider collider);
	void SetOnCollision(OnCollision onCollision);
	void SetTag(SpriteType tag);
	void SetSprite(CSimpleSprite* sprite, float scale);

	void SetColliderSize();
	void SetMinSize(float minSize);
	void SetMaxSize(float maxSize);

	void SetLivesLeft(int livesLeft);
	void ResetPlayer();

	static bool isFirstTelporter;
	
	static PhysicsEntity* pairTeleporter;

private:

	Vector2 position, velocity, accelleration, force;

	float gravityScale = 0.0f;
	float invMass = 0.1f;
	float friction = 0.05f;
	float restitution = 0.35f;
	float tougness = 100.0f;

	bool disabled = false;
	bool isPlaced = false;
	bool hasWon = false;
	
	Collider collider;
	OnCollision onCollision = nullptr;
	SpriteType tag = INVALID;

	CSimpleSprite* sprite;

	float colliderWidth = 0.0f;
	float colliderHeight = 0.0f;

	float minSize = 0.15f;
	float maxSize = 0.25f;

	int livesLeft = 3;
};

using PhysicsEntities = std::vector<PhysicsEntity>;

