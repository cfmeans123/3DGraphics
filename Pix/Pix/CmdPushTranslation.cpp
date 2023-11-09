#include "CmdPushTranslation.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{	
    if (params.size() < 3)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();

    float x = vc->GetFloat(params[0]);
    float y = vc->GetFloat(params[1]);
    float z = vc->GetFloat(params[2]);

    MatrixStack::Get()->PushTranslation({ x, y, z });
    return true;
}
