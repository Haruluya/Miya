#include "MApch.h"
#include "ParallaxMapImp.h"

namespace MiyaApp {
	void ParallaxMapImp::Render(Miya::Timestep ts)
	{
        float currentFrame = static_cast<float>(glfwGetTime());
        m_CameraController->GetCamera().deltaTime = currentFrame - m_CameraController->GetCamera().lastFrame;
        m_CameraController->GetCamera().lastFrame = currentFrame;

        // render
                // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // configure view/projection matrices
        glm::mat4 projection = glm::perspective(glm::radians( m_CameraController->GetCamera().Zoom), (float)MIYA_WINDOW_WIDTH / (float)MIYA_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view =  m_CameraController->GetCamera().GetViewMatrix();
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        // render parallax-mapped quad
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
        shader->setMat4("model", model);
        shader->setVec3("viewPos",  m_CameraController->GetCamera().Position);
        shader->setVec3("lightPos", *lightPos);
        shader->setFloat("heightScale", height_scale); // adjust with Q and E keys
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, heightMap);
        Miya::RenderSimpleObj::RenderQuad(quad_VAO, quad_VBO);

        m_Skybox->Render(ts, view, projection);
        m_CameraController->OnUpdate(ts);

	}
	void ParallaxMapImp::Init()
	{
        m_Skybox = new SkyBox();
        m_Skybox->Init();

        m_CameraController = new Miya::CameraController(1280.0f / 720.0f);
        lightPos = new glm::vec3(0.5f, 1.0f, 0.3f);

        glEnable(GL_DEPTH_TEST);

        // build and compile shaders
        // -------------------------
        shader = new Miya::Shader_("resource/shaders/ParallaxMapImp_V.txt", "resource/shaders/ParallaxMapImp_F.txt");

        // load textures
        // -------------
        unsigned int diffuseMap = Miya::Load::loadTexture("resource/images/wood.jpg");
        unsigned int normalMap = Miya::Load::loadTexture("resource/images/wood_normal.jpg");
        unsigned int heightMap = Miya::Load::loadTexture("resource/images/wood_parallax.jpg");

         // shader configuration
         // --------------------
        shader->use();
        shader->setInt("diffuseMap", 0);
        shader->setInt("normalMap", 1);
        shader->setInt("depthMap", 2);
	}
	void ParallaxMapImp::Destory()
	{
        m_Skybox->Destory();
	}
}