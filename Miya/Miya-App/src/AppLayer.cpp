#include "AppLayer.h"


#include "OpenGLImp/CoreBase/TriangleImp.h"
#include "OpenGLImp/CoreBase/TextureImp.h"
#include "OpenGLImp/CoreBase/TransformImp.h"
#include "OpenGLImp/CoreBase/PerspectiveImp.h"
#include "OpenGLImp/CoreBase/CameraControllImp.h"
#include "OpenGLImp/CoreBase/ModelLoadImp.h"


#include "OpenGLImp/BasicLight/PhoneImp.h"
#include "OpenGLImp/BasicLight/LightingMapImp.h"
#include "OpenGLImp/BasicLight/MutiLightImp.h"


#include "OpenGLImp/OpenglFeatures/CubeMapImp.h"
#include "OpenGLImp/OpenglFeatures/ShadowMapImp.h"
#include "OpenGLImp/OpenglFeatures/NormalMapImp.h"
#include "OpenGLImp/OpenglFeatures/ParallaxMapImp.h"

#include "App.h"
namespace MiyaApp {

	void DrawMainAppFrame();


	AppLayer::AppLayer()
	{
	}

	AppLayer::~AppLayer()
	{
	}

	void AppLayer::OnAttach()
	{

		// Init here
		renderer = new ParallaxMapImp();
		renderer->Init();
		MY_INFO("AppLayer init!");

	}

	void AppLayer::OnDetach()
	{
		// Shutdown here
		renderer->Destory();
		MY_INFO("AppLayer destory!");
	}

	void AppLayer::OnEvent(Miya::Event& event)
	{
		// Events here
		renderer->OnEvent(event);
	}

	void AppLayer::OnUpdate(Miya::Timestep ts)
	{
		// Render here
		//MY_INFO("AppLayer Update!");
		renderer->Render(ts);
	}

	void AppLayer::OnImGuiRender()
	{
		// Render switch frame.
		DrawMainAppFrame();
	}

	void AppLayer::SetRenderer(Miya::Renderer* r)
	{
		renderer = r;
	}



	void DrawMainAppFrame() {
		bool main_app_frame = true;
		bool test1 = false;
		bool test2 = false;
		// Main menu bar.
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// Main body of the Demo window starts here.
		if (!ImGui::Begin("Miya(Haruluya)", &main_app_frame))
		{
			// Early out if the window is collapsed, as an optimization.
			ImGui::End();
			return;
		}


		// e.g. Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Menu")) {
				ImGui::MenuItem("test1", NULL, &test1);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Setting")) {
				ImGui::MenuItem("test2", NULL, &test2);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tool")) {
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text("Wecome to leran cg with Miya.");
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("OpenGL Example")) {
			if (ImGui::TreeNode("TriangleImp")) {
				ImGui::Text("Draw a Triangle to begin cg programing!");
				ImGui::Spacing();
				if (ImGui::Button("Rendering")) {
					Miya::Application::Get().PushLayer(new AppLayer());
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("TransformImp")) {
				ImGui::Text("");
				ImGui::Spacing();
				if (ImGui::Button("Rendering")) {
					Miya::Application::Get().PushLayer(new AppLayer());
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("TextureImp")) {
				ImGui::Text("");
				ImGui::Spacing();
				if (ImGui::Button("Rendering")) {
					Miya::Application::Get().PushLayer(new AppLayer());
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("PerspectiveImp")) {
				ImGui::Text("");
				ImGui::Spacing();
				if (ImGui::Button("Rendering")) {
					Miya::Application::Get().PushLayer(new AppLayer());
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("ModelLoadImp")) {
				ImGui::Text("Using classes mesh and model to describe objects,and rendering objects with assimp and opengl.");
				ImGui::Spacing();
				if (ImGui::Button("Rendering")) {
					Miya::Application::Get().PushLayer(new AppLayer());
				}
				ImGui::TreePop();
				ImGui::Separator();
			}

		}



		ImGui::End();


	}


}

