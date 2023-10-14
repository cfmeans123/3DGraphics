#pragma once

#include "Vector2.h"
#include "Vector3.h"

class MathHelper
{
public:
	static float MagnitudSqrd(const Vec2& v);
	static float MagnitudSqrd(const Vec3& v);
	static float Magnitud(const Vec2& v);
	static float Magnitud(const Vec3& v);
	static Vec2 Normalize(const Vec2& v);
	static Vec3 Normalize(const Vec3& v);
	static float Dot(const Vec2& v, const Vec2& b);
	static float Dot(const Vec3& v, const Vec3& b);
	static Vec3 Cross(const Vec3& v, const Vec3& b);

	static float Lerp(const float& a, const float& b, float t);
	static Vec2 Lerp(const Vec2& a, const Vec2& b, float t);
	static Vec3 Lerp(const Vec3& a, const Vec3& b, float t);
};
