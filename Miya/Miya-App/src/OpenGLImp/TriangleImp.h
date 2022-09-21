#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class TriangleImp : public Miya::Renderer{
	public:
		void Render();
		void Init();
		void destory();
	private:
		unsigned int shaderProgram;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

	};
}