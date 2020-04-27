#include "stdafx.h"
#include "Mine.h"
#include <math_utils.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

SimpleMine::SimpleMine(glm::ivec2 p, MineOptions opts)
	: pos(p)
{
	falloff = Utils::get_random(
		opts.simpleMineOptions.minFalloff, 
		opts.simpleMineOptions.maxFalloff);
};

// returned float will be 1
std::pair<glm::ivec2, float> SimpleMine::Evaluate() const
{
	std::unordered_map<glm::ivec2, float> mappy;

	// add weights of cells in square region around the mine
	float sumWeight = 0;
	const int r = 5; // oof hardcoded
	for (int x = -r; x <= r; x++)
	{
		for (int y = -r; y <= r; y++)
		{
			// Y = Ae^(-bt)
			using namespace glm;
			ivec2 p(x, y);
			float weight = pow(e<float>(), -falloff * distance(vec2(p), vec2(this->pos)));
			sumWeight += weight;
			mappy[p] += weight;
		}
	}

	// generate a random number within the range
	// then add values in range up until random value is reached
	float rng = Utils::get_random(0, sumWeight);
	float summy = 0;
	for (const auto& p : mappy)
	{
		summy += p.second;
		if (summy > rng)
			return { p.first, 1 };
	}
	ASSERT_MSG(0, "Should not have gotten here!");
}


/*
// i'm sorry, little one
// iteratively generates outline of box shape
for (int r = 0;; r++)
{
	// Y = Ae^(-bt)
	bool succ = false; // unused
	std::vector<int> Xs{ -r, r };
	std::vector<int> Ys{ -r, r };
	for (int y : Ys)
	{
		for (int x = -r; x <= r; x++)
		{
			// evaluate
		}
	}
	for (int x : Xs)
	{
		for (int y = -r + 1; x <= r - 1; y++)
		{
			// evaluate
		}
	}
}
*/