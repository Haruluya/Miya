#pragma once
#include "render/Renderer.h"
#include "Components/SkyBox.h"
namespace MiyaApp {

	class NormalMapImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		Miya::Shader_* shader;
		unsigned int quad_VAO;
		unsigned int quad_VBO;
		GLuint diffuseMap;
		GLuint normalMap;

		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;
		SkyBox* m_Skybox;

	};
}