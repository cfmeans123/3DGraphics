#pragma once
#include "Command.h"

class CmdModels : public Command
{
public:
	const char* GetName() override
	{
		return "Model";
	}
	const char* GetDescription() override
	{
		return "Model(fileName)";
	}

	bool Execute(const std::vector<std::string>& params);
};

