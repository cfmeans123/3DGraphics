#pragma once

#include "Command.h"

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationY(deg)\n"
			"\n"
			"- Pushes a rotation matrix into the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
