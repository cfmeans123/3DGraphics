#include "Clipper.h"
#include "Viewport.h"


const int BIT_INSIDE	= 0;
const int BIT_LEFT		= 1 << 1; // 0001
const int BIT_RIGHT		= 1 << 2; // 0010
const int BIT_BOTTOM	= 1 << 3; // 0100
const int BIT_TOP		= 1 << 4; // 1000

enum class ClipEdge : int
{
	Left,
	Bottom,
	Right,
	Top,
	Count
};

bool IsInFront(ClipEdge edge, const Vec3& pos)
{
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	switch (edge)
	{
	case ClipEdge::Left: 
		return pos.x > minX;
	
	case ClipEdge::Bottom: 
		return pos.y < maxY;
	
	case ClipEdge::Right: 
		return pos.x < maxX;
	
	case ClipEdge::Top: 
		return pos.y > minY;
	
	default:
		break;
	}

	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v0, const Vertex& v1)
{
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	float t = 0.0f;
	switch (edge)
	{
	case ClipEdge::Left: t = (minX - v0.position.x) / (v1.position.x - v0.position.x); break;
	case ClipEdge::Bottom: t = (maxY - v0.position.y) / (v1.position.y - v0.position.y); break;
	case ClipEdge::Right: t = (maxX - v0.position.x) / (v1.position.x - v0.position.x); break;
	case ClipEdge::Top: t = (minY - v0.position.y) / (v1.position.y - v0.position.y); break;
	default:
		break;
	}
	return LerpVertex(v0, v1, t);
}

int GetOutputCode(float x, float y)
{
	int code = BIT_INSIDE;
	if (x < Viewport::Get()->GetMinX())
	{
		code |= BIT_LEFT; // 0000 | 0001 = 0001;
	}
	else if (x > Viewport::Get()->GetMaxX())
	{
		code |= BIT_RIGHT; // 0000 | 0010 = 0010;
	}
	if (y < Viewport::Get()->GetMinY())
	{
		code |= BIT_TOP; // 0000 | 1000 = 1000;
	}
	else if (y > Viewport::Get()->GetMaxY())
	{
		code |= BIT_BOTTOM; // 0000 | 0100 = 0100;
	}
	return code;
	//0001 | 0010 = 0101;
}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

Clipper::Clipper()
{

}

Clipper::~Clipper()
{

}

void Clipper::OnNewFrame()
{
	mIsClipping = false;
}

//return true if clip test passes

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!mIsClipping)
	{
		return true;
	}

	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	return v.position.x >= minX && v.position.x <= maxX
		&& v.position.y >= minY && v.position.y <= maxY;

}

bool Clipper::ClipLine(Vertex& v0, Vertex& v1)
{
	//first, sift out cases that can be ignored completely to save compile time (if lines aren't on the screen at all)
	if (!mIsClipping)
	{
		return true;
	}
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	int codeV0 = GetOutputCode(v0.position.x, v0.position.y);
	int codeV1 = GetOutputCode(v1.position.x, v1.position.y);
	bool accept = false;

	while (!accept)
	{
		//if codeV0 == 0000 && codeV1 == 0000 (they are both inside)
		if ((codeV0 | codeV1) == BIT_INSIDE)
		{
			accept = true;
		}
		//if codev0 and codeV1 are both outside of viewspace
		else if ((codeV0 & codeV1) > 0)
		{
			accept = false;
			break;
		}
		//the line crosses at some point
		else
		{
			float t = 0.0f;
			int outCodeActive = (codeV1 > codeV0) ? codeV1 : codeV0;
			if ((outCodeActive & BIT_TOP) > 0)
			{
				t = (minY - v0.position.y) / (v1.position.y - v0.position.y);
			}
			else if ((outCodeActive & BIT_BOTTOM) > 0)
			{
				t = (maxY - v0.position.y) / (v1.position.y - v0.position.y);
			}
			else if ((outCodeActive & BIT_RIGHT) > 0)
			{
				t = (maxX - v0.position.x) / (v1.position.x - v0.position.x);
			}
			else if ((outCodeActive & BIT_LEFT) > 0)
			{
				t = (minX - v0.position.x) / (v1.position.x - v0.position.x);
			}

			if (outCodeActive == codeV0)
			{
				v0 = LerpVertex(v0, v1, t);
				codeV0 = GetOutputCode(v0.position.x, v0.position.y);
			}
			else
			{
				v1 = LerpVertex(v0, v1, t);
				codeV1 = GetOutputCode(v1.position.x, v1.position.y);
			}

		}
	}

	return accept;
}
bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (!mIsClipping)
	{
		return true;
	}

	std::vector<Vertex> newVertices;
	for (int i = 0; i < (int)ClipEdge::Count; ++i)
	{
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (size_t n = 0; n < vertices.size(); ++n)
		{
			size_t np1 = (n + 1) % vertices.size();
			const Vertex& v0 = vertices[n];
			const Vertex& v1 = vertices[np1];
			bool isInFrontV0 = IsInFront(edge, v0.position);
			bool isInFrontV1 = IsInFront(edge, v1.position);
			if (isInFrontV0 && isInFrontV1)
			{
				newVertices.push_back(v1);
			}
			else if (isInFrontV0 && !isInFrontV1)
			{
				newVertices.push_back(ComputeIntersection(edge, v0, v1));
			}
			else if (!isInFrontV0 && !isInFrontV1)
			{
				//save nothing
			}
			else if (!isInFrontV0 && isInFrontV1)
			{
				newVertices.push_back(ComputeIntersection(edge, v0, v1));
				newVertices.push_back(v1);
			}
		}
		vertices = newVertices;
	}
	return vertices.size() > 0;
}

