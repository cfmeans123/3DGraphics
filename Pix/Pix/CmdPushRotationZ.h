#pragma once

#include "Command.h"

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationZ(deg)\n"
			"\n"
			"- Pushes a rotation matrix into the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
