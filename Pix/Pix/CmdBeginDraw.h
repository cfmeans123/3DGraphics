#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(x, y)\n"
			"\n"
			"- Prepares vertices for rasterizer.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
