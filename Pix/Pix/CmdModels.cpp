#include "CmdModels.h"
#include "ModelCache.h"
#include "PrimitivesManager.h"

bool CmdModels::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	auto model = ModelCache::Get()->GetModel(params[0]);
	auto pm = PrimitivesManager::Get();

	for (int i = 0; i < model->GetVertexCount(); ++i)
	{
		pm->AddVertex(model->GetVertex(i));
	}

	return true;
}