#include "stdafx.h"
#include "Minesweeper.h"
#include "Grid.h"

//#include "MineFactory.h"

Minesweeper::Minesweeper()
{
	// create n x m grid
	grid_ = std::make_unique<SquareGrid>(glm::uvec2(10, 10));
}

void Minesweeper::Draw()
{

}
