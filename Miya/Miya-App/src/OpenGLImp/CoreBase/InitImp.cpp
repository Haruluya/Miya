#include "MApch.h"
#include "InitImp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace MiyaApp {
	void InitImp::Render(Miya::Timestep ts)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void InitImp::Init()
	{
	}

	void InitImp::Destory()
	{
	}

}