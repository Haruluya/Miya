
#include "MYpch.h"
#include "ImGuiLayer.h"

#include "imgui/imgui.h"


#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "Application.h"

// TEMPORARY
#include <GLFW/glfw3.h>





namespace Miya {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// font.
		io.Fonts->AddFontFromFileTTF("../Miya-Engine/resource/font/NotoSansCJKjp-Medium.otf", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}



		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");


		// Theme color.
		theme_color_map.insert(std::pair<std::string,ImVec4>("window_bg_color", ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f }));

		theme_color_map.insert(std::pair<std::string, ImVec4>("header_color", ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("header_hovered_color", ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("header_actived_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));

		theme_color_map.insert(std::pair<std::string, ImVec4>("button_color", ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("button_hovered_color", ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("button_actived_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));

		theme_color_map.insert(std::pair<std::string, ImVec4>("frame_bg_color", ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("frame_bg_hovered_color", ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("frame_bg_active_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));

		theme_color_map.insert(std::pair<std::string, ImVec4>("tab_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("tab_hovered_color", ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("tab_actived_color", ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("tab_unfocused_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("tab_unfocused_active_color", ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f }));

		theme_color_map.insert(std::pair<std::string, ImVec4>("title_bg_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("title_bg_active_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));
		theme_color_map.insert(std::pair<std::string, ImVec4>("title_bg_collapsed_color", ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f }));

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

	}





	void ImGuiLayer::Begin()
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (show_theme_color_window) {
			SetThemeColors();
		}
	}

	void ImGuiLayer::End()
	{


		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetThemeColors() {
		auto& colors = ImGui::GetStyle().Colors;




		ImGui::Begin("Miya Theme Color", &show_theme_color_window);

		ImGui::Text("Set the theme color.");
		ImGui::ColorEdit3("window_bg_color", (float*)&theme_color_map["window_bg_color"]);
		ImGui::ColorEdit3("header_color", (float*)&theme_color_map["header_color"]);
		ImGui::ColorEdit3("header_hovered_color", (float*)&theme_color_map["header_hovered_color"]);
		ImGui::ColorEdit3("header_actived_color", (float*)&theme_color_map["header_actived_color"]);
		ImGui::ColorEdit3("button_color", (float*)&theme_color_map["button_color"]);
		ImGui::ColorEdit3("button_hovered_color", (float*)&theme_color_map["button_hovered_color"]);
		ImGui::ColorEdit3("button_actived_color", (float*)&theme_color_map["button_actived_color"]);
		ImGui::ColorEdit3("frame_bg_color", (float*)&theme_color_map["frame_bg_color"]);
		ImGui::ColorEdit3("frame_bg_hovered_color", (float*)&theme_color_map["frame_bg_hovered_color"]);
		ImGui::ColorEdit3("frame_bg_active_color", (float*)&theme_color_map["frame_bg_active_color"]);
		ImGui::ColorEdit3("tab_color", (float*)&theme_color_map["tab_color"]);
		ImGui::ColorEdit3("tab_hovered_color", (float*)&theme_color_map["tab_hovered_color"]);
		ImGui::ColorEdit3("tab_actived_color", (float*)&theme_color_map["tab_actived_color"]);
		ImGui::ColorEdit3("tab_unfocused_color", (float*)&theme_color_map["tab_unfocused_color"]);
		ImGui::ColorEdit3("tab_unfocused_active_color", (float*)&theme_color_map["tab_unfocused_active_color"]);
		ImGui::ColorEdit3("title_bg_color", (float*)&theme_color_map["title_bg_color"]);
		ImGui::ColorEdit3("title_bg_active_color", (float*)&theme_color_map["title_bg_active_color"]);
		ImGui::ColorEdit3("title_bg_collapsed_color", (float*)&theme_color_map["title_bg_collapsed_color"]);
		ImGui::Separator();
		if (ImGui::Button("set",ImVec2(60.0f,30.0f))) {
			colors[ImGuiCol_WindowBg] = theme_color_map["window_bg_color"];

			// Headers
			colors[ImGuiCol_Header] = theme_color_map["header_color"];
			colors[ImGuiCol_HeaderHovered] = theme_color_map["header_hovered_color"];
			colors[ImGuiCol_HeaderActive] = theme_color_map["header_actived_color"];

			// Buttons
			colors[ImGuiCol_Button] = theme_color_map["button_color"];
			colors[ImGuiCol_ButtonHovered] = theme_color_map["button_hovered_color"];
			colors[ImGuiCol_ButtonActive] = theme_color_map["button_actived_color"];

			// Frame BG
			colors[ImGuiCol_FrameBg] = theme_color_map["frame_bg_color"];
			colors[ImGuiCol_FrameBgHovered] = theme_color_map["frame_bg_hovered_color"];
			colors[ImGuiCol_FrameBgActive] = theme_color_map["frame_bg_active_color"];

			// Tabs
			colors[ImGuiCol_Tab] = theme_color_map["tab_color"];
			colors[ImGuiCol_TabHovered] = theme_color_map["tab_hovered_color"];
			colors[ImGuiCol_TabActive] = theme_color_map["tab_actived_color"];
			colors[ImGuiCol_TabUnfocused] = theme_color_map["tab_unfocused_color"];
			colors[ImGuiCol_TabUnfocusedActive] = theme_color_map["tab_unfocused_active_color"];

			// Title
			colors[ImGuiCol_TitleBg] = theme_color_map["title_bg_color"];
			colors[ImGuiCol_TitleBgActive] = theme_color_map["title_bg_active_color"];
			colors[ImGuiCol_TitleBgCollapsed] = theme_color_map["title_bg_collapsed_color"];
		}
		ImGui::SameLine();
		ImGui::End();


		
	}


}
