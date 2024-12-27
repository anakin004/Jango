#pragma once

#include <crm_mth.h>

namespace Crimson {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		inline void SetPosition(const crm::vec3& position) { m_Position = position; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix (); }

		inline const crm::vec3& GetPostition() const { return m_Position; }
		inline const float GetRotation() { return m_Rotation; RecalculateViewMatrix(); }

		inline const crm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const crm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const crm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }


	private:
		void RecalculateViewMatrix();

	private:
		crm::mat4 m_ProjectionMatrix;
		crm::mat4 m_ViewMatrix;
		crm::mat4 m_ViewProjectionMatrix;

		crm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}