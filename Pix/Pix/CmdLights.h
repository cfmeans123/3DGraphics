#pragma once

#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightAmbient";
    }
    const char* GetDescription() override
    {
        return "Sets the light ambient(r, g, b)";
    }

    bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightDiffuse : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightDiffuse";
    }
    const char* GetDescription() override
    {
        return "Sets the light diffuse(r, g, b)";
    }

    bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightSpecular : public Command
{
public:
    const char* GetName() override
    {
        return "SetLightSpecular";
    }
    const char* GetDescription() override
    {
        return "Sets the light specular(r, g, b)";
    }

    bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetDirectionalLight : public Command
{
public:
    const char* GetName() override
    {
        return "AddDirectionalLight";
    }
    const char* GetDescription() override
    {
        return "Sets direction of light";
    }

    bool Execute(const std::vector<std::string>& params);
};

class CmdSetPointLight : public Command
{
public:
    const char* GetName() override
    {
        return "AddPointLight";
    }
    const char* GetDescription() override
    {
        return "Sets  a Point of light";
    }

    bool Execute(const std::vector<std::string>& params);
};

class CmdSpotLight : public Command
{
public:
    const char* GetName() override
    {
        return "AddSpotLight";
    }
    const char* GetDescription() override
    {
        return "Sets a spot of light";
    }

    bool Execute(const std::vector<std::string>& params);
};