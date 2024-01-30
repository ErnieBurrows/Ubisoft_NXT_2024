#include "stdafx.h"

#include "Physics.h"

void Physics::Update(float dt, PhysicsEntities& entities)
{
    while (prevTime < currTime)
    {
        prevTime += timestep;
        Step(timestep, entities);
    }
    currTime += dt;
}

/// <summary>
/// Adds forces to each entity that has been placed on a frame by frame bases and resolves collision based on Manifold vector of colliding objects
/// Essentially used to control Y velocity by adding gravity and X vector by the current force * the mass of the object
/// Uses projectile motion formula (y)t = y0+v0 * sin(theta) * t - 1/2 * g * t^2 
/// </summary>
void Physics::Step(float dt, PhysicsEntities& entities)
{
    for (PhysicsEntity& entity : entities)
    {
        /*Only add force to the entity if it has been placed -> Happens when loaded into a vector OR when mail slingshot is released*/
        if (entity.GetIsPlaced())
        {
            Vector2 fa = entity.GetForce() * entity.GetInvMass();
            Vector2 fg = gravity * entity.GetGravityScale();
            entity.SetAccelleration(fa + fg);

            entity.SetVelocity(entity.GetVelocity() + entity.GetAccelleration() * dt);
            entity.SetPosition(entity.GetPosition() + entity.GetVelocity() * dt);

            entity.SetForce(Vector2Zero);
        }  
    }

    std::vector<Manifold> collisions = HitTest(entities);
    for (const Manifold& collision : collisions)
    {
        ResolveVelocity(collision);
        ResolvePosition(collision);
        PhysicsEntity& a = *collision.a;
        PhysicsEntity& b = *collision.b;
       
        if (a.GetOnCollision() != nullptr)
            a.GetOnCollision()(a, b);
        if (b.GetOnCollision() != nullptr)
            b.GetOnCollision()(b, a);
    }   
}

