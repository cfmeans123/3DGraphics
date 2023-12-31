#pragma once

#include "Command.h"

class CmdSetCameraPosition : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraPosition";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraPosition(X, Y, Z)\n"
			"\n"
			"- Sets a camera position.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
