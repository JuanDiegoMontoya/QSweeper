#pragma once

struct Mine
{
	virtual float Evaluate(float dist) = 0;
	virtual float Evaluate(glm::vec2 posOther) = 0;
	virtual glm::vec2 GetPos() = 0;

	Mine() {};
private:
};

struct SimpleMine : public Mine
{
	SimpleMine();
	SimpleMine(glm::vec2, float) {};
	float Evaluate(float dist) override;
	float Evaluate(glm::vec2 posOther) override;
	glm::vec2 GetPos() override { return pos; } const

	// simple mode
	glm::vec2 pos;
	float falloff;
};

struct ComplexMine : public Mine
{
	float Evaluate(float dist) override;
	float Evaluate(glm::vec2 posOther) override;
	glm::vec2 GetPos() override { return pos; } const

		// complex mode
		glm::vec2 pos;
	float falloff;
	float amplitude;
	float wavelength;
};