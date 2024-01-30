#pragma once

#include "stdafx.h"
#include "MyMath.h"
#include "app\app.h"
#include "PhysicsEntity.h"
#include <algorithm>

inline Vector2 GetMouseNativeSpace() {
	float mx, my;
	App::GetMousePos(mx, my);
	APP_VIRTUAL_TO_NATIVE_COORDS(mx, my);
	Vector2 mouse = { mx,my };
	return mouse;
}

inline Vector2 GetMouseVirtualSpace() {
	float mx, my;
	App::GetMousePos(mx, my);
	Vector2 mouse = { mx,my };
	return mouse;
}

/// <summary>
/// Used to check if the sprite has reached it Min size
/// </summary>
static inline bool CheckMinSizeReached(const PhysicsEntity& entity, float minSize)
{
	return entity.GetSprite()->GetScale() < minSize;
}

/// <summary>
/// Shrinks the sprites scale by a value of 0.05f
/// </summary>
static inline void ShrinkSprite(const PhysicsEntity& entity, float minSize)
{
	entity.GetSprite()->SetScale(entity.GetSprite()->GetScale() - 0.05f);
}

/// <summary>
/// Used to check if the sprite has reached it Max size
/// </summary>
static inline bool CheckMaxSizeReached(const PhysicsEntity& entity, float maxSize)
{
	return entity.GetSprite()->GetScale() > maxSize;
}

/// <summary>
/// Shrinks the sprites scale by a value of 0.05f
/// </summary>
static inline void EnlargeSprite(const PhysicsEntity& entity, float maxSize)
{
	entity.GetSprite()->SetScale(entity.GetSprite()->GetScale() + 0.05f);
}

/// <summary>
/// Toggles sprites rotation between 0 and 90 degrees
/// </summary>
static inline void FlipSprite(const PhysicsEntity& entity)
{
	entity.GetSprite()->SetAngle((entity.GetSprite()->GetAngle() == 0)
		? DEG_TO_RAD(90) : 0);
}


