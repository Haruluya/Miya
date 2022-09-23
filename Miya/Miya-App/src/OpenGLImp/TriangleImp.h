#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class TriangleImp : public Miya::Renderer{
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		unsigned int shaderProgram;
		unsigned int VBO;
		unsigned int VAO;
		Miya::Shader_* shader;
	};
}