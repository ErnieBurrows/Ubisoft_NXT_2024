#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Collision.h"
#include "MyMath.h"

class Physics
{
public:
    void Update(float dt, PhysicsEntities& entities);

    float timestep = 1.0f / 50.0f;   
    
    Vector2 gravity = { 0.0f, -9.8f };

    std::vector<PhysicsEntities> entities;
    const std::vector<Manifold>& Collisions() { return collisions; }

private:
    std::vector<Manifold> collisions;

    float prevTime = 0.0f;
    float currTime = 0.0f;

    void Step(float dt, PhysicsEntities& entities);
};

#endif // __PHYSICS_H__