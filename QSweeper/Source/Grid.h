#pragma once
#include "Cell.h"
#include "MineFactory.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/gtx/component_wise.hpp>


// TODO: find good place for this struct
struct GridOptions
{
	struct SquareGridOptions
	{
		int numMines;
	}squareGridOptions;

	struct HexGridOptions
	{

	}hexGridOptions;
};


class Grid
{
public:
	virtual void Init(const GridOptions&) = 0;

	// evaluates all mines
	// returns positions and magnitudes
	virtual std::unordered_map<glm::ivec2, float>
	Evaluate() const = 0;

	// returns sum of all magnitudes that appeared in the given circle
	virtual float Evaluate(glm::ivec2, float radius) const = 0;

private:

};


class SquareGrid final : public Grid
{
public:
	SquareGrid(glm::uvec2 dim) : dim_(dim), numCells_(glm::compMul(dim_))
	{
		gridData_ = new Cell[numCells_];
		factory_.SetSimpleMineOptions({ .1, .5 });
	}

	~SquareGrid()
	{
		delete[] gridData_;
	}

	void Init(const GridOptions&) override;
	std::unordered_map<glm::ivec2, float> Evaluate() const override;
	float Evaluate(glm::ivec2 pos, float radius) const override;

private:
	MineFactory factory_;
	const glm::uvec2 dim_;
	const size_t numCells_;
	Cell* gridData_;
	int time_ = 0; // complex mode, incremented after each move or in real time
};