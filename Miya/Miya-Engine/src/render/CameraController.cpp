#include "MYpch.h"
#include "CameraController.h"

#include "event/Input.h"
#include "event/KeyCodes.h"

namespace Miya {

	CameraController::CameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(glm::vec3(0.0f, 0.0f, 3.0f)), m_Rotation(rotation)
	{

	}

	void CameraController::OnUpdate(Timestep ts)
	{

		//---key event----------------------------------------------------
		if (Input::IsKeyPressed(Key::W))
			m_Camera.ProcessKeyboard(FORWARD, m_Camera.deltaTime);
		if (Input::IsKeyPressed(Key::S))
			m_Camera.ProcessKeyboard(BACKWARD, m_Camera.deltaTime);
		if (Input::IsKeyPressed(Key::A))
			m_Camera.ProcessKeyboard(LEFT, m_Camera.deltaTime);
		if (Input::IsKeyPressed(Key::D))
			m_Camera.ProcessKeyboard(RIGHT, m_Camera.deltaTime);

		if (Input::IsKeyPressed(Key::E))
			m_Camera.ProcessKeyboard(UP, m_Camera.deltaTime);
		if (Input::IsKeyPressed(Key::Q))
			m_Camera.ProcessKeyboard(DOWN, m_Camera.deltaTime);
		//---------------------------------------------------------------


		//---mouse event----------------------------------------------------
		float xpos = static_cast<float>(Input::GetMouseX());
		float ypos = static_cast<float>(Input::GetMouseY());

		if (m_Camera.firstMouse)
		{
			m_Camera.lastX = xpos;
			m_Camera.lastY = ypos;
			m_Camera.firstMouse = false;
		}

		float xoffset = xpos - m_Camera.lastX;
		float yoffset = m_Camera.lastY - ypos; // reversed since y-coordinates go from bottom to top

		m_Camera.lastX = xpos;
		m_Camera.lastY = ypos;

		m_Camera.ProcessMouseMovement(xoffset, yoffset);

		//---------------------------------------------------------------

		//if (m_Rotation)
		//{
		//	if (Input::IsKeyPressed(Key::Q))
		//		m_CameraRotation += m_CameraRotationSpeed * ts;
		//	if (Input::IsKeyPressed(Key::E))
		//		m_CameraRotation -= m_CameraRotationSpeed * ts;

		//	if (m_CameraRotation > 180.0f)
		//		m_CameraRotation -= 360.0f;
		//	else if (m_CameraRotation <= -180.0f)
		//		m_CameraRotation += 360.0f;

		//	m_Camera.SetRotation(m_CameraRotation);
		//}


		//m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void CameraController::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MY_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MY_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::OnResize(float width, float height)
	{
		//m_AspectRatio = width / height;
		//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{

		//m_ZoomLevel -= e.GetYOffset() * 0.25f;
		//m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}



}