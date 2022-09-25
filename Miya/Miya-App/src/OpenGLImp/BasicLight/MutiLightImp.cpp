#include "MApch.h"
#include "MutiLightImp.h"
#include <GLFW/glfw3.h>

namespace MiyaApp {



	void MutiLightImp::Render(Miya::Timestep ts)
	{
        float currentFrame = static_cast<float>(glfwGetTime());
        m_CameraController->GetCamera().deltaTime = currentFrame - m_CameraController->GetCamera().lastFrame;
        m_CameraController->GetCamera().lastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_obj->use();
        shader_obj->setVec3("viewPos", m_CameraController->GetCamera().Position);
        shader_obj->setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        shader_obj->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader_obj->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        shader_obj->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader_obj->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        shader_obj->setVec3("pointLights[0].position", pointLightPositions[0]);
        shader_obj->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader_obj->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shader_obj->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader_obj->setFloat("pointLights[0].constant", 1.0f);
        shader_obj->setFloat("pointLights[0].linear", 0.09f);
        shader_obj->setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        shader_obj->setVec3("pointLights[1].position", pointLightPositions[1]);
        shader_obj->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        shader_obj->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shader_obj->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        shader_obj->setFloat("pointLights[1].constant", 1.0f);
        shader_obj->setFloat("pointLights[1].linear", 0.09f);
        shader_obj->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        shader_obj->setVec3("pointLights[2].position", pointLightPositions[2]);
        shader_obj->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        shader_obj->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shader_obj->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        shader_obj->setFloat("pointLights[2].constant", 1.0f);
        shader_obj->setFloat("pointLights[2].linear", 0.09f);
        shader_obj->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        shader_obj->setVec3("pointLights[3].position", pointLightPositions[3]);
        shader_obj->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader_obj->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader_obj->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shader_obj->setFloat("pointLights[3].constant", 1.0f);
        shader_obj->setFloat("pointLights[3].linear", 0.09f);
        shader_obj->setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        shader_obj->setVec3("spotLight.position", m_CameraController->GetCamera().Position);
        shader_obj->setVec3("spotLight.direction", m_CameraController->GetCamera().Front);
        shader_obj->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        shader_obj->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        shader_obj->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader_obj->setFloat("spotLight.constant", 1.0f);
        shader_obj->setFloat("spotLight.linear", 0.09f);
        shader_obj->setFloat("spotLight.quadratic", 0.032f);
        shader_obj->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader_obj->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(m_CameraController->GetCamera().Zoom), (float)MIYA_WINDOW_WIDTH/ (float)MIYA_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = m_CameraController->GetCamera().GetViewMatrix();
        shader_obj->setMat4("projection", projection);
        shader_obj->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        shader_obj->setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        // render containers
        glBindVertexArray(obj_VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader_obj->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // also draw the lamp object(s)
        shader_light->use();
        shader_light->setMat4("projection", projection);
        shader_light->setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(light_VAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            shader_light->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        m_CameraController->OnUpdate(ts);

	}
	void MutiLightImp::Init()
	{
		glEnable(GL_DEPTH_TEST);
		m_CameraController = new Miya::CameraController(1280.0f / 720.0f);
		lightPos = new glm::vec3(1.2f, 1.0f, 2.0f);
		// build and compile our shader zprogram
		// ------------------------------------
		shader_light = new Miya::Shader_("resource/shaders/MutiLightImp_Light_V.txt", "resource/shaders/MutiLightImp_Light_F.txt");
		shader_obj = new Miya::Shader_("resource/shaders/MutiLightImp_V.txt", "resource/shaders/MutiLightImp_F.txt");
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        // positions all containers
        cubePositions = new glm::vec3[]{
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        // positions of the point lights
        pointLightPositions = new glm::vec3[]{
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };
        // first, configure the cube's VAO (and VBO)

        glGenVertexArrays(1, &obj_VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(obj_VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenVertexArrays(1, &light_VAO);
        glBindVertexArray(light_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // load textures (we now use a utility function to keep the code more organized)
        // -----------------------------------------------------------------------------
        unsigned int diffuseMap = Miya::Load::loadTexture("resource/images/haruluya_bd.jpg");
        unsigned int specularMap = Miya::Load::loadTexture("resource/images/haruluya_bd.jpg");

        // shader configuration
        // --------------------
        shader_obj->use();
        shader_obj->setInt("material.diffuse", 0);
        shader_obj->setInt("material.specular", 1);
	}
	void MutiLightImp::Destory()
	{
        glDeleteVertexArrays(1, &obj_VAO);
        glDeleteVertexArrays(1, &light_VAO);
        glDeleteBuffers(1, &VBO);
	}
	void MutiLightImp::OnEvent(Miya::Event& e)
	{
        m_CameraController->OnEvent(e);
	}


}