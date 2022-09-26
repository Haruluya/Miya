#pragma once
#include "render/Renderer.h"
#include "Components/SkyBox.h"
namespace MiyaApp {

	class ShadowMapImp: public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		Miya::Shader_* shader;
		Miya::Shader_* shader_depth;
		Miya::Shader_* shader_quad;
		unsigned int plane_VAO;
		unsigned int plane_VBO;
		unsigned int depth_FBO;
		unsigned int depth_Map;
		const unsigned int SHADOW_WIDTH = 1024;
		const unsigned int SHADOW_HEIGHT = 1024;
		unsigned int texture_wood;
		glm::vec3* cubePositions;
		glm::vec3* pointLightPositions;
		glm::vec3* lightPos;
		Miya::CameraController* m_CameraController;
		SkyBox* m_Skybox;

	};
}