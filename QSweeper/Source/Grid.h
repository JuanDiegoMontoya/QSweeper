#pragma once
#include "Cell.h"
#include "MineFactory.h"
#include <glm/gtx/component_wise.hpp>

class Grid
{
public:
	// evaluates all mines
	// returns positions and magnitudes
	virtual std::unordered_map<glm::vec2, float>
	Evaluate() const = 0;

	// returns sum of all magnitudes that appeared in the given circle
	virtual float Evaluate(glm::vec2, float radius) const = 0;

private:

};


class SquareGrid final : public Grid
{
public:
	SquareGrid(glm::uvec2 dim) : dim_(dim)
	{
		gridData_ = new Cell[glm::compMul(dim_)];
	}

	~SquareGrid()
	{
		delete[] gridData_;
	}

	std::unordered_map<glm::vec2, float>
	Evaluate() const override
	{
		std::unordered_map<glm::vec2, float> ret;
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

private:
	const glm::uvec2 dim_;
	Cell* gridData_;
	int time_ = 0; // complex mode, incremented after each move or in real time
};