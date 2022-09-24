#include "MApch.h"
#include "PhoneImp.h"
#include <GLFW/glfw3.h>

namespace MiyaApp {
	void PhoneImp::Render(Miya::Timestep ts)
	{
        float currentFrame = static_cast<float>(glfwGetTime());
        m_CameraController->GetCamera().deltaTime = currentFrame - m_CameraController->GetCamera().lastFrame;
        m_CameraController->GetCamera().lastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // change light position.
        lightPos->x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos->y = sin(glfwGetTime() / 2.0f) * 1.0f;


        // be sure to activate shader when setting uniforms/drawing objects
        shader_light->use();
        shader_light->setVec3("objectColor", 1.0f, 1.0f, 0.6f);
        shader_light->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shader_light->setVec3("lightPos", *lightPos);
        shader_light->setVec3("viewPos", m_CameraController->GetCamera().Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(m_CameraController->GetCamera().Zoom), (float)MIYA_WINDOW_WIDTH / (float)MIYA_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = m_CameraController->GetCamera().GetViewMatrix();
        shader_light->setMat4("projection", projection);
        shader_light->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        shader_light->setMat4("model", model);

        // render the cube
        glBindVertexArray(obj_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        shader_obj->use();
        shader_obj->setMat4("projection", projection);
        shader_obj->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, *lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        shader_obj->setMat4("model", model);

        glBindVertexArray(light_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_CameraController->OnUpdate(ts);
	}
	void PhoneImp::Init()
	{
		glEnable(GL_DEPTH_TEST);
        m_CameraController = new Miya::CameraController(1280.0f / 720.0f);

		// build and compile our shader zprogram
		// ------------------------------------
		shader_obj =  new Miya::Shader_("resource/shaders/PhoneImp_V.txt", "resource/shaders/PhoneImp_F.txt");
		shader_light = new Miya::Shader_("resource/shaders/PhoneImp_Light_V.txt", "resource/shaders/PhoneImp_Light_F.txt");
        lightPos = new glm::vec3(1.2f, 1.0f, 2.0f);


        float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };


        glGenVertexArrays(1, &obj_VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(obj_VAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
        glGenVertexArrays(1, &light_VAO);
        glBindVertexArray(light_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // note that we update the lamp's position attribute's stride to reflect the updated buffer data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

	}
	void PhoneImp::Destory()
	{
        glDeleteVertexArrays(1, &obj_VAO);
        glDeleteVertexArrays(1, &light_VAO);
        glDeleteBuffers(1, &VBO);
	}
	void PhoneImp::OnEvent(Miya::Event& e)
	{
        m_CameraController->OnEvent(e);
	}
}