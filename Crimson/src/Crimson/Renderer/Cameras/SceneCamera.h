#pragma once

#include "Camera.h"

namespace Crimson {
	enum ProjectionTypes {
		Orhtographic, perspective
	};

	class SceneCamera : public Camera {
	public:
		SceneCamera(float Width, float Height);
		SceneCamera();
		~SceneCamera() = default;

		//no support for orthographic projection these are just place holders for future
		void SetProjectionType(ProjectionTypes type) { m_projection_type = type; RecalculateProjection(); }
		void SetOrthographic(float Size, float Near = -1.0f, float Far = 1.0f);
		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline float GetOrthographicNear() const { return m_OrthographicNear; }
		inline float GetOrthographicFar() const { return m_OrthographicFar; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; }
		void SetOrthographicNear(float Near) { m_OrthographicNear = Near; RecalculateProjection(); }
		void SetOrthographicFar(float Far) { m_OrthographicFar = Far; RecalculateProjection(); }

		virtual void SetPerspctive(float v_FOV, float Near, float Far) override;
		virtual void SetCameraPosition(const glm::vec3& pos) override;
		virtual void SetViewDirection(const glm::vec3& dir) override;
		virtual void SetUPVector(const glm::vec3& up) override;
		virtual void SetViewportSize(float aspectratio) override;
		virtual void SetVerticalFOV(float fov) override { m_verticalFOV = fov; }
		void SetPerspectiveNear(float val) override { m_PerspectiveNear = val; SetPerspctive(m_verticalFOV, m_PerspectiveNear, m_PerspectiveFar); }
		void SetPerspectiveFar(float val) override { m_PerspectiveFar = val; SetPerspctive(m_verticalFOV, m_PerspectiveNear, m_PerspectiveFar); }

		float GetPerspectiveNear() override { return m_PerspectiveNear; };
		float GetPerspectiveFar() override { return m_PerspectiveFar; };
		virtual inline const glm::mat4& GetProjectionMatrix() override { return m_Projection; }
		virtual inline const glm::vec3& GetCameraPosition() override { return m_Position; }

		virtual inline const glm::mat4& GetProjectionView() override { return m_ProjectionView; }
		virtual inline const glm::mat4& GetViewMatrix() override { return m_View; }

		virtual inline const glm::vec3& GetViewDirection() override { return m_ViewDirection; }
		virtual inline float GetAspectRatio() override { return m_AspectRatio;}
		inline float GetVerticalFOV() override { return m_verticalFOV; }
	

		inline glm::vec3 GetCameraRotation() override { return glm::vec3(m_pitch, m_yaw, m_roll); };
		virtual inline void InvertPitch() override { m_pitch = -m_pitch; }
		virtual inline void Translate(const glm::vec3& translation) override { m_Position += m_Position; }

		virtual void OnEvent(Event& e) override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void RotateCamera(float pitch = 0, float yaw = 0, float roll = 0) override;

	public:
		ProjectionTypes m_projection_type = ProjectionTypes::perspective;
	private:
		void RecalculateProjection();//for now it is orthographic projection
		void RecalculateProjectionView();
	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ProjectionView;

		glm::vec3 m_Position = { 0,0,0 }, m_ViewDirection = { 0,0,1 };
		//m_Viewdirection is the location we are looking at (it is the vector multiplied with rotation matrix)
		glm::vec3 Up = { 0,1,0 }, RightVector;//we get right vector by getting the cross product of m_ViewDirection and Up vectors

		float m_verticalFOV = 90.f;
		float m_PerspectiveNear = 0.01;
		float m_PerspectiveFar = 1000;

		float m_AspectRatio = 1.0;
		float m_pitch = 0, m_yaw = 0, m_roll = 0;
		float m_OrthographicSize = 10.f;
		float m_OrthographicFar = 1.f, m_OrthographicNear = -1.f;
	};
}