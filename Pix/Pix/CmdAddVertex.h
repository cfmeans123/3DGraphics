#pragma once
#include "Command.h"
class CmdAddVertex : public Command
{
public:
	const char* GetName() override
	{
		return "Vertex";
	}

	const char* GetDescription() override
	{
		return
			"vertex(x, y)\n"
			"vertex(x, y, z)\n"
			"vertex(x, y, r, g, b)\n"
			"vertex(x, y, z, r, g, b)\n"
			"\n"
			"- Sends vertices to primitives manager";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

