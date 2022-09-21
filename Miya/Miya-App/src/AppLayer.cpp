#include "AppLayer.h"
#include "OpenGLImp/TriangleImp.h"

namespace MiyaApp {

	AppLayer::AppLayer()
	{
	}

	AppLayer::~AppLayer()
	{
	}

	void AppLayer::OnAttach()
	{
		//EnableGLDebugging();

		// Init here
		renderer = new TriangleImp();
		renderer->Init();

	}

	void AppLayer::OnDetach()
	{
		// Shutdown here
		renderer->Destory();
	}

	void AppLayer::OnEvent(Miya::Event& event)
	{
		// Events here
	}

	void AppLayer::OnUpdate(Miya::Timestep ts)
	{
		// Render here
		renderer->Render();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void AppLayer::OnImGuiRender()
	{
	}


}

