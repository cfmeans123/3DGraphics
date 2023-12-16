#pragma once
#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vec3 position;
	Vec3 normal;
	Vec3 worldPosition;
	Vec3 worldNormal;
	X::Color color;

	Vertex operator*(const bool& b) const
	{
		Vertex t;
		t.position = { t.position.x *= b, t.position.y *= b, t.position.z *= b };
		t.color = { t.color.r *= b, t.color.b *= b, t.color.g *= b, t.color.a *= b };
		return t;
	}

	Vertex operator+(const Vertex& b) const
	{
		Vertex t;
		t.position = {
			t.position.x = position.x + b.position.x,
			t.position.y = position.y + b.position.y,
			t.position.z = position.z + b.position.z };

		t.color = {
			t.color.r = color.r + b.color.r,
			t.color.b = color.b + b.color.b,
			t.color.g = color.g + b.color.g,
			t.color.a = color.a + b.color.a };
		return t;
	}
};

inline static Vec3 LerpPos(const Vec3& a, const Vec3& b, float t)
{
	return MathHelper::Lerp(a, b, t);
}

inline static Vec3 LerpNormal(const Vec3& a, const Vec3& b, float t)
{
	return MathHelper::Normalize(MathHelper::Lerp(a, b, t));
}

inline static X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return { MathHelper::Lerp(a.r, b.r, t),
			 MathHelper::Lerp(a.g, b.g, t),
			 MathHelper::Lerp(a.b, b.b, t),
			 MathHelper::Lerp(a.a, b.a, t) };
}

inline static Vertex LerpVertex(const Vertex& a, const Vertex& b, float t, bool lerpNormal = false)
{
	Vertex ret;
	ret.position = LerpPos(a.position, b.position, t);
	ret.worldNormal = LerpPos(a.worldPosition, b.worldPosition, t);
	ret.color = LerpColor(a.color, b.color, t);
	if (lerpNormal)
	{
		ret.normal = LerpNormal(a.normal, b.normal, t);
		ret.worldNormal = LerpNormal(a.worldNormal, b.worldNormal, t);
	}
	return ret;
}