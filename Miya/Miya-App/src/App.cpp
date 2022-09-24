#include "App.h"
#include "AppLayer.h"
#include "OpenGLImp/CoreBase/InitImp.h"
namespace MiyaApp {
	
	AppLayer* App::m_nlayer = nullptr;

	App::App() {
	}

	void App::Init() {
		m_nlayer = new MiyaApp::AppLayer();
		m_nlayer->SetRenderer(new InitImp());
		PushLayer(m_nlayer);
	}
}


int main()
{
	std::unique_ptr<MiyaApp::App> app = std::make_unique<MiyaApp::App>();
	app->Init();
	app->Run();
	return 0;
}


