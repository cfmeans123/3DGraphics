#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "MathHelper.h"
#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return Matrix4(
			  hw, 0.0f, 0.0f, 0.0f,
			0.0f,  -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			  hw,   hh, 0.0f, 1.0f
			);
	}

	bool DrawTriangle(CullMode mode, const Vec3& a, const Vec3& b, const Vec3& c)
	{
		if (mode == CullMode::None)
		{
			return true;
		}

		const Vec3 v0 = b - a;
		const Vec3 v1 = c - a;
		Vec3 facingNormal = MathHelper::Cross(v0, v1);

		switch (mode)
		{
		case CullMode::Back: return facingNormal.z <= 0.0f;
		case CullMode::Front: return facingNormal.z >= 0.0f;

		default:
			break;
		}
		return true;
	}
}

PrimitivesManager::PrimitivesManager()
{

}
PrimitivesManager::~PrimitivesManager()
{

}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}


bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mDrawBegin = true;
	mApplyTransform = applyTransform;
	mTopology = topology;
	mVertexBuffer.clear();
	return true;
}
void PrimitivesManager::AddVertex(const Vertex& vertex)
{
	mVertexBuffer.push_back(vertex);
}
bool PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}
	switch (mTopology)
	{
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
	}
		break;

	case Topology::Line:
	{
		for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
		break;

	case Topology::Triangle:
	{

		const Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		const Matrix4 matView = Camera::Get()->GetViewMatrix();
		const Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		const Matrix4 matScreen = GetScreenTransform();
		const Matrix4 matNDC = matWorld * matView * matProj;
		const Matrix4 matFinal = matScreen;

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
			if (mApplyTransform)
			{
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].position = MathHelper::TransformCoord(triangle[t].position, matNDC);
				}
				if (!DrawTriangle(mCullMode, triangle[0].position,
					triangle[1].position, triangle[2].position))
				{
					continue;
				}
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].position = MathHelper::TransformCoord(triangle[t].position, matScreen);
				}
				
			}
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
		break;

	default:
		return false;
		break;
	}
}
