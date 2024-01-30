#pragma once
#include "PhysicsEntity.h"
#include "vector"
class SlingShot
{
public:
	static void CalculateSlingshotTrajectory(Vector2 startPos, Vector2 initialVelocity, int numPoints);
	static void DrawSlingshotTrajectoryLine();
	static void SlingshotSpringPhysics(PhysicsEntity*& Entity);

	static Vector2 initalPosition, displacement;
private:
};

