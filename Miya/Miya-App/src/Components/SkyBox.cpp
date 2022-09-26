#include "MApch.h"
#include "SkyBox.h"
namespace MiyaApp {
	void SkyBox::Render(Miya::Timestep ts)
	{
		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		shader->use();
		view = glm::mat4(glm::mat3(view));
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);
		// skybox cube
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
	}
	void SkyBox::Render(Miya::Timestep ts, glm::mat4 view, glm::mat4 projection)
	{
		this->view = view;
		this->projection = projection;
		this->Render(ts);
	}
	void SkyBox::Init()
	{

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		shader = new Miya::Shader_("resource/shaders/CubeMapImp_Skybox_V.txt", "resource/shaders/CubeMapImp_Skybox_F.txt");


		// skybox VAO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		std::vector<std::string> faces
		{
			"resource/images/skybox/exosystem/exosystem_lf.jpg",
			"resource/images/skybox/exosystem/exosystem_rt.jpg",
			"resource/images/skybox/exosystem/exosystem_up(1).jpg",
			"resource/images/skybox/exosystem/exosystem_dn(1).jpg",
			"resource/images/skybox/exosystem/exosystem_ft.jpg",
			"resource/images/skybox/exosystem/exosystem_bk.jpg"

		};
		Texture = Miya::Load::loadCubemap(faces);

		shader->use();
		shader->setInt("skybox", 0);
	}
	void SkyBox::Destory()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}


}