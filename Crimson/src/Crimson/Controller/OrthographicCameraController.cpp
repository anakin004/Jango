#include "cnpch.h"

#include "OrthographicCameraController.h"

#include "Crimson/Core/Input.h"
#include "Crimson/Core/KeyCodes.h"


namespace Crimson {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel), m_RotationOn(rotation)
	{

	}


	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		if (Input::IsKeyPressed(CRIMSON_KEY_W))
			m_Position.y += m_CameraSpeed * timeStep;
		if (Input::IsKeyPressed(CRIMSON_KEY_A))
			m_Position.x -= m_CameraSpeed * timeStep;
		if (Input::IsKeyPressed(CRIMSON_KEY_S))
			m_Position.y -= m_CameraSpeed * timeStep;
		if (Input::IsKeyPressed(CRIMSON_KEY_D))
			m_Position.x += m_CameraSpeed * timeStep;

		if (m_RotationOn) {
			if (Input::IsKeyPressed(CRIMSON_KEY_Q))
				m_Rotation += m_RotationSpeed * timeStep;
			if (Input::IsKeyPressed(CRIMSON_KEY_E))
				m_Rotation -= m_RotationSpeed * timeStep;
			m_Camera.SetRotation(m_Rotation);
		}

		m_Camera.SetPosition(m_Position);

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CN_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		CN_CORE_INFO("{0}", m_ZoomLevel);
		m_ZoomLevel = std::max(m_ZoomLevel, 0.05f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
		return false;
	}

}