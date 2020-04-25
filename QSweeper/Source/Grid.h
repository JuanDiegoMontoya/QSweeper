#pragma once
#include "Cell.h"
#include "MineFactory.h"
#include <glm/gtx/component_wise.hpp>

class Grid
{
public:
	virtual float Evaluate(glm::vec2, float radius) const = 0;

private:

};


class SquareGrid final : public Grid
{
public:
	SquareGrid(glm::uvec2 dim)
	{
		gridData_ = new Cell[glm::compMul(dim)];
	}

	~SquareGrid()
	{
		delete[] gridData_;
	}

	float Evaluate(glm::vec2, float radius) const override
	{

	}

private:
	Cell* gridData_;
};