#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class SkyBox : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Render(Miya::Timestep ts, glm::mat4 view, glm::mat4 projection);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		Miya::Shader_* shader;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int Texture;
		glm::mat4 view;
		glm::mat4 projection;
	};
}