#pragma once

#include "Camera_.h"
#include "utils/Timestep.h"

#include "event/ApplicationEvent.h"
#include "event/MouseEvent.h"

namespace Miya {

	class CameraController
	{
	public:
		CameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		Camera_& GetCamera() { return m_Camera; }
		const Camera_& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 45.0f;
		Camera_ m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 3.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 60.0f;
	};

}