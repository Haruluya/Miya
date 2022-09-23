#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class TriangleImp : public Miya::Renderer{
	public:
		virtual void Render();
		virtual void Init();
		virtual void Destory();
	private:
		unsigned int shaderProgram;
		unsigned int VBO;
		unsigned int VAO;
		Miya::Shader_* shader;
	};
}