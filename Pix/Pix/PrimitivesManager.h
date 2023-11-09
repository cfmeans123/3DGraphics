#pragma once
#include "Vertex.h"


//using 'class' in enum resolves naming conflicts if there are structs/classes with the same name of an enum member
enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public: 
	~PrimitivesManager();

	static PrimitivesManager* Get();

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(const Vertex& vertex);
	bool EndDraw();

private: 
	PrimitivesManager();
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};