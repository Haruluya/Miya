#include "MiyaEngine.h"
#include "AppLayer.h"


class App : public Miya::Application
{
public:
	App()
	{
		PushLayer(new MiyaApp::AppLayer());
	}
};

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
	return 0;
}


