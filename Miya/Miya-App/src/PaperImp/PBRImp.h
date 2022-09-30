#pragma once
#include "render/Renderer.h"
#include "Components/SkyBox.h"
namespace MiyaApp {

	class PBRImp : public Miya::Renderer {
	public:
		virtual void Render(Miya::Timestep ts);
		virtual void Init();
		virtual void Destory();
		virtual void OnEvent(Miya::Event& e) {};
	private:
		Miya::Shader_* shader;
		unsigned int VAO;
		unsigned int VBO;
		glm::vec3* lightPos;
		glm::vec3* lightColors;
		glm::mat4 projection;
		Miya::CameraController* m_CameraController;
		SkyBox* m_Skybox;
		GLint albedo;
		GLint normal;
		GLint metallic;
		GLint roughness;
		GLint ao;
		unsigned int indexCount;
		const int nrRows = 7;
		const int nrColumns = 7;
		const float spacing = 2.5;
	};
}