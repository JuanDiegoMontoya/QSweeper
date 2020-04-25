#pragma once
#include "MineOptions.h"

struct Mine
{
	virtual float Evaluate(float dist) const = 0;
	virtual float Evaluate(glm::vec2 posOther) const = 0;
	virtual glm::vec2 GetPos() const = 0;
};

struct SimpleMine final : public Mine
{
	SimpleMine(MineOptions) {};
	SimpleMine(glm::vec2, float) {};
	float Evaluate(float dist) const override;
	float Evaluate(glm::vec2 posOther) const override;
	glm::vec2 GetPos() const override { return pos; }

	// simple mode
	glm::vec2 pos;
	float falloff;
};

struct ComplexMine final : public Mine
{
	float Evaluate(float dist) const override;
	float Evaluate(glm::vec2 posOther) const override;
	glm::vec2 GetPos() const override { return pos; }

	// complex mode
	glm::vec2 pos;
	float falloff;
	float amplitude;
	float wavelength;
};