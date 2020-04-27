#include "stdafx.h"
#include "Grid.h"

std::unordered_map<glm::ivec2, float> SquareGrid::Evaluate() const
{
	std::unordered_map<glm::ivec2, float> ret;
	for (int i = 0; i < glm::compMul(dim_); i++)
	{
		if (auto& mine = gridData_[i].mine)
		{
			auto pair = mine->Evaluate();
			ret[pair.first] += pair.second;
		}
	}
	return ret;
}

float SquareGrid::Evaluate(glm::ivec2, float radius) const
{
	return 0.0f;
}
