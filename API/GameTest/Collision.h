#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "PhysicsEntity.h"

struct Manifold
{
    PhysicsEntity* a = nullptr;
    PhysicsEntity* b = nullptr;
    Vector2 mtv{};
};

/// <summary>
/// Circle cirlce collision check based on radiiSum < distance. This will set the mtv of the colliding entities.
/// </summary>
inline bool CircleCircle(Vector2 pos1, float radius1, Vector2 pos2, float radius2, Vector2* mtv)
{
    Vector2 direction = pos1 - pos2;
    float distance = Length(direction);
    float radiiSum = radius1 + radius2;
    bool collision = distance <= radiiSum;
    if (collision && mtv != nullptr)
        *mtv = Normalize(direction) * (radiiSum - distance);

    return collision;
}

inline bool CirclePlane(Vector2 circle, float radius, Vector2 plane, Vector2 normal, Vector2* mtv)
{
    float distance = Dot(circle - plane, normal);
    bool collision = distance <= radius;
    if (collision && mtv != nullptr)
        *mtv = normal * (radius - distance);

    return collision;
}

/// <summary>
/// Projects circle unto nearest line of rectangle then runs circlePlane collision based on this projection
/// </summary>
inline bool CircleRect(Vector2 circle, float radius, Vector2 rect, Vector2 extents, Vector2* mtv)
{
    Vector2 nearest = Clamp(circle, rect - extents, rect + extents);
    return CirclePlane(circle, radius, nearest, Normalize(circle - nearest), mtv);
}

/// <summary>
///  Checks bounding box coordinates for two rectangles and checks for overlap.
///  If a collision occurs, it calculates the Minimum Translation Vector (MTV) and separates 
///  the rectangles along the axis of minimum overlap.
/// </summary>
inline bool RectRect(Vector2 rect1, Vector2 extents1, Vector2 rect2, Vector2 extents2, Vector2* mtv)
{
    float xMin1 = rect1.x - extents1.x;
    float xMax1 = rect1.x + extents1.x;
    float yMin1 = rect1.y - extents1.y;
    float yMax1 = rect1.y + extents1.y;

    float xMin2 = rect2.x - extents2.x;
    float xMax2 = rect2.x + extents2.x;
    float yMin2 = rect2.y - extents2.y;
    float yMax2 = rect2.y + extents2.y;

    bool collision = Overlaps(xMin1, xMax1, xMin2, xMax2) && Overlaps(yMin1, yMax1, yMin2, yMax2);
    if (collision && mtv != nullptr)
    {
        float xMin = fmaxf(xMin1, xMin2);
        float xMax = fminf(xMax1, xMax2);
        float yMin = fmaxf(yMin1, yMin2);
        float yMax = fminf(yMax1, yMax2);

        float x = xMax - xMin;
        float y = yMax - yMin;
        if (x < y)
        {
            *mtv = { x, 0.0f };
            if (rect1.x > xMin) mtv->x *= -1.0f;
        }
        else if (y < x)
        {
            *mtv = { 0.0f, y };
            if (rect1.y > yMin) mtv->y *= -1.0f;
        }
        else
        {
            *mtv = { x, y };
            if (rect1.x > xMin) mtv->x *= -1.0f;
            if (rect1.y > yMin) mtv->y *= -1.0f;
        }
    }
    return collision;
}

/// <summary>
/// Switch Statement for which collision check function should be called based on enum Shape
/// </summary>
inline bool HitTest(Vector2 pos1, Vector2 pos2, Collider col1, Collider col2, Vector2* mtv = nullptr)
{
    if (col1.shape == CIRCLE && col2.shape == CIRCLE)
        return CircleCircle(pos1, col1.radius, pos2, col2.radius, mtv);

    if (col1.shape == CIRCLE && col2.shape == PLANE)
        return CirclePlane(pos1, col1.radius, pos2, col2.normal, mtv);

    if (col1.shape == PLANE && col2.shape == CIRCLE)
        return CirclePlane(pos2, col2.radius, pos1, col1.normal, mtv);

    if (col1.shape == CIRCLE && col2.shape == AABB)
        return CircleRect(pos1, col1.radius, pos2, col2.extents, mtv);

    if (col1.shape == AABB && col2.shape == CIRCLE)
        return CircleRect(pos2, col2.radius, pos1, col1.extents, mtv);

    if (col1.shape == AABB && col2.shape == AABB)
        return RectRect(pos1, col1.extents, pos2, col2.extents, mtv);

    return false;
}

inline std::vector<Manifold> HitTest(const std::vector<PhysicsEntity>& entities)
{
    std::vector<Manifold> collisions;
    for (size_t i = 0; i < entities.size(); i++)
    {
        for (size_t j = i + 1; j < entities.size(); j++)
        {
            Manifold manifold;
            const PhysicsEntity& a = entities[i];
            const PhysicsEntity& b = entities[j];
            if (a.GetIsDisabled() || b.GetIsDisabled()) continue;
            if (HitTest(a.GetPosition(), b.GetPosition(), a.GetCollider(), b.GetCollider(), &manifold.mtv))
            {
                // Ensure A is always dynamic and B is either static or dynamic
                if (!a.GetInvMass() > 0.0f && b.GetInvMass() > 0.0f)
                    manifold.a = (PhysicsEntity*)&b, manifold.b = (PhysicsEntity*)&a;
                else
                    manifold.a = (PhysicsEntity*)&a, manifold.b = (PhysicsEntity*)&b;

                // Ensure the mtv always points from B to A
                if (Dot(manifold.a->GetPosition() - manifold.b->GetPosition(), manifold.mtv) < 0.0f)
                    manifold.mtv = manifold.mtv * -1.0f;

                collisions.push_back(manifold);
            }
        }
    }
    return collisions;
}

/// <summary>
/// Sets the velocity of two colliding object by adding impulses in accordance to a force based physics system
/// (Restitution(bounciness) - how much energy is conserved during impact)
/// Friction(Stickiness) - Per frame decrease in velocity determined by friction coefficient)
/// </summary>
inline void ResolveVelocity(Manifold collision)
{
    // e = restitution, j = impulse, jt = tangent impulse (friction), mu = friction coefficient
    PhysicsEntity& a = *collision.a;
    PhysicsEntity& b = *collision.b;

    // Exit if objects are separating or both have infinite masses - No need to keep adding forces after MTV is applied
    Vector2 normal = Normalize(collision.mtv);
    Vector2 velBA = a.GetVelocity() - b.GetVelocity();
    float t = Dot(velBA, normal);
    if (t > 0.0f) return;
    if ((a.GetInvMass() + b.GetInvMass()) <= FLT_MIN) return;

    // Restitution -> v 2−v 1=−e(u 2−u 1).
    float e = fminf(a.GetRestitiution(), b.GetRestitiution());
    float j = -(1.0f + e) * t / (a.GetInvMass() + b.GetInvMass());
    a.SetVelocity(a.GetVelocity() + normal * j * a.GetInvMass());
    b.SetVelocity(b.GetVelocity() - normal * j * b.GetInvMass());

    // Friction -> f = μN,
    Vector2 tangent = Normalize(velBA - normal * t);
    float jt = -Dot(velBA, tangent) / (a.GetInvMass() + b.GetInvMass());
    float mu = sqrtf(a.GetFriction() * b.GetFriction());
    jt = Clamp(jt, -j * mu, j * mu);
    a.SetVelocity(a.GetVelocity() + tangent * jt * a.GetInvMass());
    b.SetVelocity(b.GetVelocity() + tangent * jt * b.GetInvMass());
}

/// <summary>
/// Sets position of 2 objects based on the calculated MTV, has params to prevent jittering
/// </summary>
inline void ResolvePosition(Manifold collision)
{
    PhysicsEntity& a = *collision.a;
    PhysicsEntity& b = *collision.b;

    const float percent = 1.0f; // Amount we are * the correction by
    const float slop = 0.001f;   // Amount we subtract from the mtv to prevent jittering

    float correction = Length(collision.mtv) - slop;
    if (correction > 0.0f)
    {
        correction /= a.GetInvMass() + b.GetInvMass();
        correction *= percent;

        Vector2 correctionVector = Normalize(collision.mtv) * correction;
        a.SetPosition(a.GetPosition() + a.GetInvMass() * correctionVector);

        if(b.GetInvMass() > 0.0f)
            b.SetPosition(b.GetPosition() - b.GetInvMass() * correctionVector);
    }
}

#endif // __COLLISION_H__
