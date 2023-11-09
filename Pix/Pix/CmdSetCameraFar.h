#pragma once

#include "Command.h"

class CmdSetCameraFar : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFar";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraFar(float)\n"
			"\n"
			"- Sets camera far";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
