#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class MutiLightImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e);
	private:
		Miya::Shader_* shader_obj;
		Miya::Shader_* shader_light;
		unsigned int VBO;
		unsigned int obj_VAO;
		unsigned int light_VAO;
		unsigned int EBO;
		unsigned int diffuseMap;
		unsigned int specularMap;
		glm::vec3* cubePositions;
		glm::vec3* pointLightPositions;
		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;

	};
}