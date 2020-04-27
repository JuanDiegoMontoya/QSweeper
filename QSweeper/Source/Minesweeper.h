#pragma once
#include "Grid.h"

class VBO;
class VAO;

class Minesweeper
{
public:
	Minesweeper();
	void Draw();

private:
	std::unique_ptr<Grid> grid_;
};