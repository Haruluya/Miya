#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class PerspectiveImp : public Miya::Renderer {
	public:
		virtual void Render();
		virtual void Init();
		virtual void Destory();
	private:
		Miya::Shader_* shader;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		unsigned int texture1;
		unsigned int texture2;
		glm::vec3* cubePositions;
	};
}