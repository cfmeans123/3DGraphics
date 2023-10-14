#include "Rasterizer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	mColor = v.color;
	DrawPoint(v.position.x + 0.5f, v.position.y + 0.5f);
	//X::DrawPixel(v.position.x + 0.5f, v.position.y, v.color);
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{

	float dx = v1.position.x - v0.position.x;
	float dy = v1.position.y - v0.position.y;

	//normal slope lerp
	Vertex startV, endV;
	if (std::abs(dy) < std::abs(dx))
	{
		if (v0.position.x < v1.position.x)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float x = startV.position.x; x <= endV.position.x; ++x)
		{
			float t = (x - startV.position.x) / (endV.position.x - startV.position.x);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}
	else
	{
		if (v0.position.y < v1.position.y)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float y = startV.position.y; y <= endV.position.y; ++y)
		{
			float t = (y - startV.position.y) / (endV.position.y - startV.position.y);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}


}

void Rasterizer::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	switch (mFillMode)
	{
		case FillMode::WireFrame:
		{
			DrawLine(v0, v1);
			DrawLine(v1, v2);
			DrawLine(v0, v2);
		}
		break;
		case FillMode::Solid:
		{
			std::vector<Vertex> sortedVertices = { v0, v1, v2 };
			std::sort(sortedVertices.begin(), sortedVertices.end(),
				[](const Vertex& lhs, const Vertex& rhs)
				{
					return lhs.position.y < rhs.position.y;
				});
			DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
		}
		break;

		default:
			break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

}
