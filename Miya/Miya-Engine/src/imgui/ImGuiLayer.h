#pragma once

#include "layer/Layer.h"

#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include<map>

#include <Imgui/imgui.h>
namespace Miya {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void SetThemeColors();
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		bool show_theme_color_window = false;
		std::map<std::string, ImVec4> theme_color_map;
	};

}