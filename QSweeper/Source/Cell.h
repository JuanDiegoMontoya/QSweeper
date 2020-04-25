#pragma once
#include <optional>
#include "Mine.h"

struct Cell
{
	std::optional<Mine> mine;
	bool flagged = false;
};