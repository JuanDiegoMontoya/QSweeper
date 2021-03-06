#include "stdafx.h"
#include "vbo.h"
#include "vao.h"
#include "ibo.h"
#include "shader.h"
#include "camera.h"
#include "pipeline.h"
#include "settings.h"
#include "input.h"

#include "Renderer.h"
#include <Vertices.h>
#include <Engine.h>


namespace Renderer
{
	// private variables
	namespace
	{
		Pipeline pipeline;
	}


	static void GLAPIENTRY
		GLerrorCB(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		//return; // UNCOMMENT WHEN DEBUGGING GRAPHICS

		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------" << std::endl;
		std::cout << "Debug message (" << id << "): " << message << std::endl;

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
		} std::cout << std::endl;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		} std::cout << std::endl;

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
		} std::cout << std::endl;
		std::cout << std::endl;
	}


	void CompileShaders()
	{

	}


	void RecompileShaders()
	{

	}

	// initializes the gBuffer and its attached textures
	void Init()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEPTH_TEST);

		// enable debugging stuff
		glDebugMessageCallback(GLerrorCB, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		GLint count;
		glGetIntegerv(GL_NUM_EXTENSIONS, &count);

		CompileShaders();
		pipeline.AddCamera(new Camera(CameraType::kControlCam));

		Engine::PushRenderCallback(DrawAll, 0);
		//Engine::PushUpdateCallback(Update, 0);
	}


	void DrawAll()
	{
		PERF_BENCHMARK_START;
		Clear();
		glEnable(GL_FRAMEBUFFER_SRGB); // gamma correction



		glDisable(GL_FRAMEBUFFER_SRGB);
		PERF_BENCHMARK_END;
	}


	void Clear()
	{
		//auto cc = World::bgColor_;
		//glClearColor(cc.r, cc.g, cc.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}


	void DrawCube()
	{
		static VAO* blockHoverVao = nullptr;
		static VBO* blockHoverVbo = nullptr;
		if (blockHoverVao == nullptr)
		{
			blockHoverVao = new VAO();
			blockHoverVbo = new VBO(Vertices::cube, sizeof(Vertices::cube));
			VBOlayout layout;
			layout.Push<float>(3);
			blockHoverVao->AddBuffer(*blockHoverVbo, layout);
		}
		blockHoverVao->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	void drawAxisIndicators()
	{
		static VAO* axisVAO;
		static VBO* axisVBO;
		if (axisVAO == nullptr)
		{
			float indicatorVertices[] =
			{
				// positions			// colors
				0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // x-axis
				1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // y-axis
				0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // z-axis
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
			};

			axisVAO = new VAO();
			axisVBO = new VBO(indicatorVertices, sizeof(indicatorVertices), GL_STATIC_DRAW);
			VBOlayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			axisVAO->AddBuffer(*axisVBO, layout);
		}
		/* Renders the axis indicator (a screen-space object) as though it were
			one that exists in the world for simplicity. */
		ShaderPtr currShader = Shader::shaders["axis"];
		currShader->Use();
		Camera* cam = GetPipeline()->GetCamera(0);
		currShader->setMat4("u_model", glm::translate(glm::mat4(1), cam->GetPos() + cam->front * 10.f)); // add scaling factor (larger # = smaller visual)
		currShader->setMat4("u_view", cam->GetView());
		currShader->setMat4("u_proj", cam->GetProj());
		glClear(GL_DEPTH_BUFFER_BIT); // allows indicator to always be rendered
		axisVAO->Bind();
		glLineWidth(2.f);
		glDrawArrays(GL_LINES, 0, 6);
		axisVAO->Unbind();
	}


	// draws a single quad over the entire viewport
	void drawQuad()
	{
		static unsigned int quadVAO = 0;
		static unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] =
			{
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}


	Pipeline* GetPipeline()
	{
		return &pipeline;
	}
}