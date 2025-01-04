#include "cnpch.h"
#include "OrthographicCameraController.h"
#include "Crimson/Core/Input.h";
#include "Crimson/Core/KeyCodes.h"

#define CN_BIND_FN(x) std::bind(&OrthographicCameraController::x,this,std::placeholders::_1)

namespace Crimson {
	OrthographicCameraController::OrthographicCameraController(float aspectratio)
		:m_AspectRatio(aspectratio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}
	void OrthographicCameraController::OnUpdate(TimeStep deltatime)
	{
		if (Input::IsKeyPressed(CRIMSON_KEY_W))
			v3.y -= m_movespeed * deltatime;
		if (Input::IsKeyPressed(CRIMSON_KEY_S))
			v3.y += m_movespeed * deltatime;
		if (Input::IsKeyPressed(CRIMSON_KEY_A))
			v3.x -= m_movespeed * deltatime;
		if (Input::IsKeyPressed(CRIMSON_KEY_D))
			v3.x += m_movespeed * deltatime;

		if (bCanRotate)
		{
			if (Input::IsKeyPressed(CRIMSON_KEY_E))
				r += 60 * deltatime;
			if (Input::IsKeyPressed(CRIMSON_KEY_Q))
				r -= 60 * deltatime;
		}

		m_Camera.SetPosition(v3);
		m_Camera.SetRotation(r);
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CN_BIND_FN(ZoomEvent));
		dispatcher.Dispatch<WindowResizeEvent>(CN_BIND_FN(WindowResize));
	}
	void OrthographicCameraController::onResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	bool OrthographicCameraController::ZoomEvent(MouseScrolledEvent& e)
	{
		m_ZoomLevel = std::clamp(m_ZoomLevel - e.GetYOffset(), 1.0f, 30.0f);

		m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::WindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}

// #include "cnpch.h"
// 
// #include "OrthographicCameraController.h"
// 
// #include "Crimson/Core/Input.h"
// #include "Crimson/Core/KeyCodes.h"
// 
// 
// namespace Crimson {
// 
// 	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
// 		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel), m_RotationOn(rotation)
// 	{
// 
// 	}
// 
// 
// 	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 
// 		if (Input::IsKeyPressed(CRIMSON_KEY_W))
// 			m_Position.y += m_CameraSpeed * timeStep;
// 		if (Input::IsKeyPressed(CRIMSON_KEY_A))
// 			m_Position.x -= m_CameraSpeed * timeStep;
// 		if (Input::IsKeyPressed(CRIMSON_KEY_S))
// 			m_Position.y -= m_CameraSpeed * timeStep;
// 		if (Input::IsKeyPressed(CRIMSON_KEY_D))
// 			m_Position.x += m_CameraSpeed * timeStep;
// 
// 		if (m_RotationOn) {
// 			if (Input::IsKeyPressed(CRIMSON_KEY_Q))
// 				m_Rotation += m_RotationSpeed * timeStep;
// 			if (Input::IsKeyPressed(CRIMSON_KEY_E))
// 				m_Rotation -= m_RotationSpeed * timeStep;
// 			m_Camera.SetRotation(m_Rotation);
// 		}
// 
// 		m_Camera.SetPosition(m_Position);
// 
// 	}
// 
// 	void OrthographicCameraController::OnEvent(Event& e)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		EventDispatcher dispatcher(e);
// 		dispatcher.Dispatch<MouseScrolledEvent>(CN_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
// 		dispatcher.Dispatch<WindowResizeEvent>(CN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
// 	}
// 
// 	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		m_ZoomLevel -= e.GetYOffset() * 0.5f;
// 		m_ZoomLevel = std::max(m_ZoomLevel, 0.05f);
// 		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
// 		return false;
// 	}
// 
// 	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
// 		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
// 		return false;
// 	}
// 
// }