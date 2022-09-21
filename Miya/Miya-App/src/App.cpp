#include "MiyaEngine.h"
#include "AppLayer.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
using namespace Miya;

class App : public Application
{
public:
	App()
	{
		PushLayer(new AppLayer());
	}
};

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
}