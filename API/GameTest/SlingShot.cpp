#include "stdafx.h"
#include "SlingShot.h"
#include "Utils.h"
#include "app\app.h"

std::vector<Vector2> trajectoryPoints;
Vector2 newPosition;
float dragRadius = 0.2f, slingshotPower = 30.0f;

/// <summary>
/// Used for printing trajectory line, performs projectile motion equation based number of points entered and a "deltaTime variable"
/// iterates through the points at speed of deltaTime (represented as a *) and stores the future trajectory points in a vector.
/// </summary>
void SlingShot::CalculateSlingshotTrajectory(Vector2 startPos, Vector2 initialVelocity, int numPoints)
{
		trajectoryPoints.clear(); // Clear previous trajectory points

		const float deltaTime = 0.01f; // Adjust as needed
		Vector2 currentPos = startPos;
		Vector2 gravity = { 0.0f,-9.81f * 3.0f };

		for (int i = 0; i < numPoints; ++i)
		{
			trajectoryPoints.push_back(currentPos);

			/*Updating the position according to projectile motion*/
			currentPos.x += -initialVelocity.x * deltaTime;
			currentPos.y += initialVelocity.y * deltaTime + 0.5f * gravity.y * deltaTime * deltaTime;

			/*Increasing gravity(downward velocity) each iteration according to deltaTime.*/
			initialVelocity.y += gravity.y * deltaTime;
		}
}

/// <summary>
/// Iterates through the points in the vector set by CalculateSlingshotTrajectory, Draws a line between i - 1 resulting in a curved line
/// </summary>
void SlingShot::DrawSlingshotTrajectoryLine()
{
	// Draw line connecting trajectory points
	for (size_t i = 1; i < trajectoryPoints.size(); ++i)
	{
		Vector2 loc1 = { trajectoryPoints[i - 1].x, trajectoryPoints[i - 1].y };
		Vector2 loc2 = { trajectoryPoints[i].x, trajectoryPoints[i].y };
		APP_NATIVE_TO_VIRTUAL_COORDS(loc1.x, loc1.y);
		APP_NATIVE_TO_VIRTUAL_COORDS(loc2.x, loc2.y);
		App::DrawLine(
			loc1.x, loc1.y,
			loc2.x, loc2.y,
			1.0f, 1.0f, 1.0f
		);
	}
}

/// <summary>
/// To be called every frame the Right mouse is down, sets the position of the bird to be within the drag radius while also maintaining the velocity vector
/// the mouse has when compared to the inital position. Uses spring equation F = -kx
/// </summary>
void SlingShot::SlingshotSpringPhysics(PhysicsEntity*& entity)
{
	entity->SetPosition(GetMouseNativeSpace());
	entity->SetGravityScale(0.0f);

	newPosition = initalPosition + Normalize(entity->GetPosition() - initalPosition)
		* min(Length(entity->GetPosition() - initalPosition), dragRadius);
	entity->SetPosition(newPosition);
	displacement = newPosition - initalPosition;

	/*Invert displacement before CalculateSlingshotTrajectory and reset it after*/
	displacement.y = -displacement.y;
	SlingShot::CalculateSlingshotTrajectory(initalPosition, displacement * slingshotPower, 100);
	displacement.y = -displacement.y;
}

Vector2 SlingShot::initalPosition;
Vector2 SlingShot::displacement;