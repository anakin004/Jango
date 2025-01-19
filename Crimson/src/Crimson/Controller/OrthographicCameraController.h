#pragma once

#include "Crimson/Renderer/OrthographicCamera.h"
#include "Crimson/Events/ApplicationEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Core/TimeStep.h"

namespace Crimson {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectratio);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);


		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline glm::vec3& GetPosition() { return m_Position; }
		inline OrthographicCamera& GetCamera() { return m_Camera; }

		inline void SetRotationAbility(bool able) { m_RotationOn = true; }
		inline void SetCameraPosition(const glm::vec3& pos) { m_Position = pos; }
		inline void SetCameraSpeed(const float& val) { m_MovementSpeed = val; }

	private:

		bool ZoomEvent(MouseScrolledEvent& e);
		bool WindowResize(WindowResizeEvent& e);

	private:

		float m_ZoomLevel = 3.0f;
		float m_AspectRatio;
		OrthographicCamera m_Camera;

		glm::vec3 m_Position = { 0,0,0 };
		float m_Rotation = 0.0f;

		float m_MovementSpeed = 80.0f;
		float m_RotationSpeed = 40.0f;

		bool m_RotationOn = true;

	};

}
