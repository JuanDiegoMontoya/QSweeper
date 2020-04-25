#pragma once
#include "Cell.h"
#include "MineFactory.h"

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
		gridData_ = new Cell[dim.x * dim.y];
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