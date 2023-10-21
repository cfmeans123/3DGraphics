#include "MathHelper.h"
#include <math.h>

float MathHelper::MagnitudSqrd(const Vec2& v)
{
	return (v.x * v.x) + (v.y * v.y);
}

float MathHelper::MagnitudSqrd(const Vec3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float MathHelper::Magnitud(const Vec2& v)
{
	return sqrtf(MagnitudSqrd(v));
}

float MathHelper::Magnitud(const Vec3& v)
{
	return sqrtf(MagnitudSqrd(v));
}

Vec2 MathHelper::Normalize(const Vec2& v)
{
	return v / Magnitud(v);
}

Vec3 MathHelper::Normalize(const Vec3& v)
{
	return v / Magnitud(v);
}

float MathHelper::Dot(const Vec2& v, const Vec2& b)
{
	return (v.x * b.x) + (v.y * b.y);
}

float MathHelper::Dot(const Vec3& v, const Vec3& b)
{
	return (v.x * b.x) + (v.y * b.y) + (v.z * b.z);
}

Vec3 MathHelper::Cross(const Vec3& v, const Vec3& b)
{
	return Vec3(
		v.y * b.z - b.y * v.z,
		b.x * v.z - v.x * b.z,
		v.x * b.y - b.x * v.y);

	//[][][]
	//[][][] i, -j, k
}

float MathHelper::Lerp(const float& a, const float& b, float t)
{
	return a + (b - a) * t;
}

Vec2 MathHelper::Lerp(const Vec2& a, const Vec2& b, float t)
{
	return
	{
		Lerp(a.x, b.x, t),
		Lerp(a.y, b.y, t)
	};
}

Vec3 MathHelper::Lerp(const Vec3& a, const Vec3& b, float t)
{
	return
	{
		Lerp(a.x, b.x, t),
		Lerp(a.y, b.y, t),
		Lerp(a.z, b.z, t)
	};
}

bool MathHelper::CheckEqual(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

bool MathHelper::CheckEqual(const Vec2& a, const Vec2& b)
{
	return CheckEqual(a.x, b.x) && CheckEqual(a.y, b.y);
}

bool MathHelper::CheckEqual(const Vec3& a, const Vec3& b)
{
	return CheckEqual(a.x, b.x) && CheckEqual(a.y, b.y) && CheckEqual(a.z, b.z);
}
