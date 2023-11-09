#pragma once

#include "Command.h"

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}

	const char* GetDescription() override
	{
		return
			"PushTranslation(X, Y, Z)\n"
			"\n"
			"- Scales a matrix by the given scaling vector3.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
