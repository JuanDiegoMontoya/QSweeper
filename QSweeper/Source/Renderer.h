#pragma once
#include <functional>

class VAO;
class IBO;
class Shader;
class Pipeline;

// responsible for making stuff appear on the screen
namespace Renderer
{
	void Init();

	// interation
	void DrawAll();
	void Clear();

	void DrawCube();

	// broad-phase rendering
	void drawQuad();

	// debug
	void drawAxisIndicators();

	Pipeline* GetPipeline();
}