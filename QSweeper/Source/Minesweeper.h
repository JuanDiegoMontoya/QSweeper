#pragma once
#include <optional>

class Minesweeper
{
public:
	Minesweeper();

	void Draw();

	struct MineWave
	{
		// simple mode
		float falloff;

		// complex mode
		float amplitude;
		float wavelength;
	};

	struct Cell
	{
		std::optional<MineWave> mine;
		bool flagged = false;
	};
private:

};