#include "stdafx.h"
#include "Grid.h"
#include <random>

void SquareGrid::Init(const GridOptions& opts)
{
	const GridOptions::SquareGridOptions& sqOpts = opts.squareGridOptions;
	ASSERT_MSG(sqOpts.numMines <= numCells_, "Cannot have more mines than cells!");
	
	// makes a vector with positions of all cells in grid...
	std::vector<glm::ivec2> positions;
	positions.reserve(numCells_);
	for (int x = 0; x < dim_.x; x++)
		for (int y = 0; y < dim_.y; y++)
			positions.push_back({x, y});

	// shuffle vector, then delete all but first N mines
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(positions.begin(), positions.end(), g);
	positions.erase(positions.begin() + sqOpts.numMines, positions.end());
	ASSERT(positions.size() == sqOpts.numMines);

	// cells in remaining positions are added as mines in the grid
	for (const auto& pos : positions)
	{
		auto mine = factory_.MakeMine<SimpleMine>(pos);
		int index = pos.x + pos.y * dim_.x; // maybe make this a function
		gridData_[index].mine = std::move(mine);
	}
}

std::unordered_map<glm::ivec2, float> SquareGrid::Evaluate() const
{
	std::unordered_map<glm::ivec2, float> ret;
	for (int i = 0; i < numCells_; i++)
	{
		if (auto& mine = gridData_[i].mine)
		{
			// add location, intensity of mine to map
			auto pair = mine->Evaluate();
			ret[pair.first] += pair.second;
		}
	}
	return ret;
}

float SquareGrid::Evaluate(glm::ivec2, float radius) const
{
	ASSERT(0); // does nothin' yet
	return 0.0f;
}
