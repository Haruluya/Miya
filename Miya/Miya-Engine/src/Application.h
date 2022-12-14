#pragma once
#include "window/Window.h"
#include "layer/LayerStack.h"
#include "event/Event.h"
#include "event/ApplicationEvent.h"

#include "utils/Timestep.h"

#include "imgui/ImGuiLayer.h"

#define MIYA_WINDOW_WIDTH 1600
#define MIYA_WINDOW_HEIGHT 900



namespace Miya {

	class Application
	{
	public:
		Application(const std::string& name = "Miya-Haruluya", uint32_t width = MIYA_WINDOW_WIDTH, uint32_t height = MIYA_WINDOW_HEIGHT);
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		void Close();
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

}