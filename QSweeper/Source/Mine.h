#pragma once
#include "MineOptions.h"

struct Mine
{
	virtual std::pair<glm::vec2, float> Evaluate() const = 0;
	virtual glm::vec2 GetPos() const = 0;
};

struct SimpleMine final : public Mine
{
	SimpleMine(glm::vec2 p, MineOptions opts)
	: pos(p)
	{
		// set falloff
	};
	SimpleMine(glm::vec2, float) {};
	std::pair<glm::vec2, float> Evaluate() const override;
	glm::vec2 GetPos() const override { return pos; }

	// simple mode
	glm::vec2 pos;
	float falloff;
};

struct ComplexMine final : public Mine
{
	std::pair<glm::vec2, float> Evaluate() const override;
	glm::vec2 GetPos() const override { return pos; }

	// complex mode
	glm::vec2 pos;
	float falloff;
	float amplitude;
	float wavelength;
};