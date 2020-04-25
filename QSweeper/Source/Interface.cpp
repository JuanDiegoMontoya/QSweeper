#include "stdafx.h"
#include "Interface.h"

#include <shader.h>
#include "Renderer.h"
#include <Pipeline.h>
#include <camera.h>
#include <Engine.h>
#include "settings.h"
#include "ImGuiBonus.h"
#include <input.h>

namespace Interface
{
	void Init()
	{
		Engine::PushRenderCallback(DrawImGui, 1);
		Engine::PushRenderCallback(Update, 2);
	}

	void Update()
	{
		if (Input::Keyboard().pressed[GLFW_KEY_GRAVE_ACCENT])
			Interface::activeCursor = !Interface::activeCursor;
		glfwSetInputMode(Engine::GetWindow(), GLFW_CURSOR, Interface::activeCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}

	void DrawImGui()
	{

	}
}