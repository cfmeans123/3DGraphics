#pragma once
#include "Vertex.h"


//using 'class' in enum resolves naming conflicts if there are structs/classes with the same name of an enum member
enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None, // dont cull anything
	Back, // cull anything facing away from the camera
	Front // cull anything facing the camera
};

class PrimitivesManager
{
public: 
	~PrimitivesManager();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	static PrimitivesManager* Get();

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(const Vertex& vertex);
	bool EndDraw();

private: 
	PrimitivesManager();
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::Back;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};