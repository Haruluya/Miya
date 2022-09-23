#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class TransformImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		unsigned int texture1;
		unsigned int texture2;
		Miya::Shader_* shader;
	};
}