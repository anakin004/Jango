#pragma once

#include "Crimson/Renderer/OrthographicCamera.h"
#include "Crimson/Core/TimeStep.h"

#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Events/ApplicationEvent.h"

#include <crm_mth.h>

namespace Crimson {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false); //defaults to 2 units of space * aspect ratio

		
		void OnUpdate(TimeStep timeStep);
		void OnEvent(Event& e);
		
		inline OrthographicCamera& GetCamera() { return m_Camera; }


		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
		inline float GetZoomLevel() { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		float m_CameraSpeed = 3.0f;
		float m_RotationSpeed = 45.0f;
		float m_Rotation = 0.f;
		crm::vec3 m_Position;

		bool m_RotationOn = false;
	};

}
