#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class CubeMapImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e);
	private:
		Miya::Shader_* shader_obj;
		Miya::Shader_* shader_skybox;
		unsigned int obj_VBO;
		unsigned int skybox_VBO;
		unsigned int obj_VAO;
		unsigned int skybox_VAO;
		unsigned int EBO;
		unsigned int diffuseMap;
		unsigned int specularMap;
		unsigned int obj_Texture;
		unsigned int skybox_Texture;
		glm::vec3* cubePositions;
		glm::vec3* pointLightPositions;
		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;

	};
}