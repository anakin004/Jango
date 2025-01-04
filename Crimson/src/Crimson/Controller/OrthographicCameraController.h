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
		inline OrthographicCamera GetCamera() { return m_Camera; }
		void onResize(float width, float height);
		glm::vec3 GetPosition() { return v3; }
		void SetCameraPosition(const glm::vec3& pos) { v3 = pos; }
		bool bCanBeRotated(bool val) {
			bCanRotate = val;
			return val;
		}
		inline void SetCameraSpeed(const float& val) { m_movespeed = val; }
		inline float GetZoomLevel() { return m_ZoomLevel; }
	private:
		bool ZoomEvent(MouseScrolledEvent& e);
		bool WindowResize(WindowResizeEvent& e);
	private:
		float m_ZoomLevel = 3.0f;
		float m_AspectRatio;
		OrthographicCamera m_Camera;

		glm::vec3 v3 = { 0,0,0 };

		float m_movespeed = 80;
		float r = 0;
		bool bCanRotate = true;
	};

}
