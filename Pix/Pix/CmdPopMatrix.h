#pragma once

#include "Command.h"

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "CmdPopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"CmdPopMatrix(X, Y, Z)\n"
			"\n"
			"- Pops Matrix.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
