#pragma once
#include <cmath>
#undef near
#undef far

#define DEG_TO_RAD(degrees) ((degrees) * PI / 180.0)

struct Color
{
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
};

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;
};

constexpr Vector2 Vector2Zero = { 0.0f, 0.0f };

inline Vector2 operator+(const Vector2& vector, float scalar)
{
	return { vector.x + scalar, vector.y + scalar };
}

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return { a.x + b.x, a.y + b.y };
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return { a.x - b.x, a.y - b.y };
}

inline Vector2 operator*(const Vector2& a, float b)
{
	return { a.x * b, a.y * b };
}

inline Vector2 operator*(float b, const Vector2& a)
{
	return { a.x * b, a.y * b };
}

inline Vector2 operator*(const Vector2& a, const Vector2& b)
{
	return { a.x * b.x, a.y * b.y };
}

inline Vector2 operator/(const Vector2& a, float b)
{
	return { a.x / b, a.y / b };
}

inline float Length(const Vector2& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

inline float LengthSqr(const Vector2& v)
{
	return v.x * v.x + v.y * v.y;
}

inline Vector2 Normalize(const Vector2& v)
{
	float length = Length(v);
	return length > 0.0f ? v / length : Vector2Zero;
}

inline float Dot(const Vector2& a, const Vector2& b)
{
	return { a.x * b.x + a.y * b.y };
}

inline Vector2 Project(const Vector2& a, const Vector2& b)
{
	return b * (Dot(a, b) / LengthSqr(b));
}

/// <summary>
/// Scalar overlap test on a per vert basis for AABB collision checking
/// Checks if 
/// </summary>
/// <returns></returns>
inline bool Overlaps(float min1, float max1, float min2, float max2)
{
	return !((max1 < min2) || (max2 < min1));
}

inline float Clamp(float value, float min, float max)
{
	return fminf(max, fmaxf(min, value));
}

inline Vector2 Clamp(Vector2 v, Vector2 min, Vector2 max)
{
	return { fminf(max.x, fmaxf(min.x, v.x)), fminf(max.y, fmaxf(min.y, v.y)) };
}
