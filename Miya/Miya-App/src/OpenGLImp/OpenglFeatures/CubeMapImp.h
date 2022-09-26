#pragma once
#include "render/Renderer.h"
#include "Components/SkyBox.h"
namespace MiyaApp {

	class CubeMapImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e);
	private:
		Miya::Shader_* shader_obj;
		unsigned int obj_VBO;
		unsigned int obj_VAO;
		unsigned int obj_Texture;
		glm::vec3* cubePositions;
		glm::vec3* pointLightPositions;
		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;
		SkyBox* m_Skybox;

	};
}