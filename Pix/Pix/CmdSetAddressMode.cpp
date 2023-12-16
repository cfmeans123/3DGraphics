#include "CmdSetAddressMode.h"
#include "VariableCache.h"
#include "TextureCache.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    AddressMode mode;
    if (params[0] == "clamp")
    {
        mode = AddressMode::Clamp;
    }
    else if (params[0] == "wrap")
    {
        mode = AddressMode::Wrap;
    }
    else if (params[0] == "mirror")
    {
        mode = AddressMode::Mirror;
    }
    else if (params[0] == "border")
    {
        mode = AddressMode::Border;
    }
    else
    {
        return false;
    }
        TextureCache::Get()->SetAddressMode(mode);
    return true;
}