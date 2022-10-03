#pragma once

#include "MiyaEngine.h"
#include "Layout.h"
namespace MiyaApp {
	class AppLayer : public Miya::Layer
	{
	public:
		AppLayer();
		virtual ~AppLayer();
		void SetRenderer(Miya::Renderer*);
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Miya::Event& event) override;
		virtual void OnUpdate(Miya::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void DrawMainAppFrame();

	private:

		Miya::Renderer* renderer;
		float m_LastRenderTime = 0.0f;
		Layout* m_layout;
		bool m_changeRender = false;
		int m_render = 1;
	};
}