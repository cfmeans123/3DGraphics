#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}

	const char* GetDescription() override
	{
		return
			"PushTranslation(X, Y, Z)\n"
			"\n"
			"- Pushes a translation matrix into the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
