#pragma once
#include "MineOptions.h"

struct Mine
{
	virtual std::pair<glm::ivec2, float> Evaluate() const = 0;
	virtual glm::ivec2 GetPos() const = 0;
};

struct SimpleMine final : public Mine
{
	SimpleMine(glm::ivec2 p, MineOptions opts);
	SimpleMine(glm::ivec2 p, float f) : pos(p), falloff(f) {};
	std::pair<glm::ivec2, float> Evaluate() const override;
	glm::ivec2 GetPos() const override { return pos; }

	// simple mode
	glm::ivec2 pos;
	float falloff;
};

struct ComplexMine final : public Mine
{
	std::pair<glm::ivec2, float> Evaluate() const override;
	glm::ivec2 GetPos() const override { return pos; }

	// complex mode
	glm::ivec2 pos;
	float falloff;
	float amplitude;
	float wavelength;
};