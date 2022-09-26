#include "MApch.h"
#include "CubeMapImp.h"

namespace MiyaApp {
	void CubeMapImp::Render(Miya::Timestep ts)
	{

        float currentFrame = static_cast<float>(glfwGetTime());
        m_CameraController->GetCamera().deltaTime = currentFrame - m_CameraController->GetCamera().lastFrame;
        m_CameraController->GetCamera().lastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw scene as normal
        shader_obj->use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = m_CameraController->GetCamera().GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(m_CameraController->GetCamera().Zoom), (float)MIYA_WINDOW_WIDTH / (float)MIYA_WINDOW_HEIGHT, 0.1f, 100.0f);
        shader_obj->setMat4("model", model);
        shader_obj->setMat4("view", view);
        shader_obj->setMat4("projection", projection);
        // cubes
        glBindVertexArray(obj_VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, obj_Texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        m_Skybox->Render(ts,view,projection);
        m_CameraController->OnUpdate(ts);
	}
	void CubeMapImp::Init()
	{
        m_Skybox = new SkyBox();

        m_Skybox->Init();
        glEnable(GL_DEPTH_TEST);
        m_CameraController = new Miya::CameraController(1280.0f / 720.0f);
        lightPos = new glm::vec3(1.2f, 1.0f, 2.0f);
        // build and compile shaders
        // -------------------------
        shader_obj = new Miya::Shader_("resource/shaders/CubeMapImp_V.txt", "resource/shaders/CubeMapImp_F.txt");
   

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        // cube VAO
        glGenVertexArrays(1, &obj_VAO);
        glGenBuffers(1, &obj_VBO);
        glBindVertexArray(obj_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, obj_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        // load textures
        // -------------
        obj_Texture = Miya::Load::loadTexture("resource/images/haruluya_bd.jpg");

        
        // shader configuration
        // --------------------
        shader_obj->use();
        shader_obj->setInt("texture1", 0);

	}
	void CubeMapImp::Destory()
	{
        glDeleteVertexArrays(1, &obj_VAO);
        glDeleteBuffers(1, &obj_VBO);

        m_Skybox->Destory();
	}
	void CubeMapImp::OnEvent(Miya::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}