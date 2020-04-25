#pragma once
#include <optional>
#include "Mine.h"

struct Cell
{
	std::unique_ptr<Mine> mine;
	bool flagged = false;
};