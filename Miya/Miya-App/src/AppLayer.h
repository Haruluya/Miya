#pragma once

#include "MiyaEngine.h"

namespace MiyaApp {
	class AppLayer : public Miya::Layer
	{
	public:
		AppLayer();
		virtual ~AppLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Miya::Event& event) override;
		virtual void OnUpdate(Miya::Timestep ts) override;
		virtual void OnImGuiRender() override;
	private:

		Miya::Renderer* renderer;
		float m_LastRenderTime = 0.0f;
	};
}