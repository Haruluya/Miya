#pragma once
#include "glm/glm.hpp"
#include "MiyaEngine.h"
namespace MiyaApp {
	class Layout {
	public: 
		Layout();
		void SetMainLayout();
		std::shared_ptr<Miya::Framebuffer> GetFrameBuffer() { return m_Framebuffer; };
	private:
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		Miya::CameraController* m_CameraController;
		std::shared_ptr<Miya::Framebuffer> m_Framebuffer;
		
	};
}