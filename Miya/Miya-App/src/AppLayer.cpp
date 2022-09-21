#include "AppLayer.h"

using namespace Miya;
//using namespace Miya::Utils;

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
}

void AppLayer::OnDetach()
{
	// Shutdown here
}

void AppLayer::OnEvent(Event& event)
{
	// Events here
}

void AppLayer::OnUpdate(Timestep ts)
{
	// Render here
}

void AppLayer::OnImGuiRender()
{
	// ImGui here
}
