#pragma once
#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}
	const char* GetDescription() override
	{
		return
			"SetCullMode(cullMode)\n"
			"\n"
			"- Sets the current culling mode.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};