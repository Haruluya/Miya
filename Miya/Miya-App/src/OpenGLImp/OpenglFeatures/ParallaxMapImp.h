#pragma once
#include "render/Renderer.h"
#include "Components/SkyBox.h"
namespace MiyaApp {

	class ParallaxMapImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		Miya::Shader_* shader;
		unsigned int quad_VAO;
		unsigned int quad_VBO;
		GLboolean parallax_mapping = true;
		GLfloat height_scale = 0.9;
		GLuint heightMap;
		GLuint diffuseMap;
		GLuint normalMap;
		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;
		SkyBox* m_Skybox;

	};
}