#include "MApch.h"
#include "ModelLoadImp.h"
#include <stb_image.h>
#include <GLFW/glfw3.h>

namespace MiyaApp {
	void ModelLoadImp::Render(Miya::Timestep ts)
	{
        float currentFrame = static_cast<float>(glfwGetTime());
        m_CameraController->GetCamera().deltaTime = currentFrame - m_CameraController->GetCamera().lastFrame;
        m_CameraController->GetCamera().lastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(m_CameraController->GetCamera().Zoom), (float)MIYA_WINDOW_WIDTH / (float)MIYA_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = m_CameraController->GetCamera().GetViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model_t = glm::mat4(1.0f);
        model_t = glm::translate(model_t, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model_t = glm::scale(model_t, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
        shader->setMat4("model", model_t);
        model->Draw(*shader);

        m_CameraController->OnUpdate(ts);
	}
	void ModelLoadImp::Init()
	{
        m_CameraController = new Miya::CameraController(1280.0f / 720.0f);

		stbi_set_flip_vertically_on_load(true);

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		// build and compile shaders
		// -------------------------
		shader = new Miya::Shader_("resource/shaders/ModelLoadImp_V.txt", "resource/shaders/ModelLoadImp_F.txt");

		model = new Miya::Model_("resource/objects/backpack/backpack.obj");
	}
	void ModelLoadImp::Destory()
	{

	}
}
