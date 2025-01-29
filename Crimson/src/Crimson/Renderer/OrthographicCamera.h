#pragma once
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"

namespace Crimson {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) {
			m_Position = position;
			ReCalculateViewMatrix();
		}

		void SetRotation(float rotation) {
			m_Rotation = rotation;
			ReCalculateViewMatrix();
		}

		void SetScale(float scale) {
			m_Scale = scale;
			ReCalculateViewMatrix();
		}

		void SetOrthographicProjection(float left, float right, float bottom, float top);
		inline glm::vec3& GetPosition() { return m_Position; }
		inline float& GetRotation() { return m_Rotation; }
		inline glm::mat4 GetProjectionViewMatix() { return m_ProjectionView; }

		void ReCalculateViewMatrix();
	private:
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_ProjectionView;

		glm::vec3 m_Position = { 0,0,0 };
		float m_Rotation;
		float m_Scale = 1.0;
	};
}

// #pragma once
// 
// #include "Crimson/Events/KeyEvent.h"
// #include <crm_mth.h>
// 
// namespace Crimson {
// 
// 	class OrthographicCamera
// 	{
// 	public:
// 		OrthographicCamera(float left, float right, float top, float bottom);
// 		void SetProjection(float left, float right, float top, float bottom);
// 
// 		inline void SetPosition(const crm::vec3& position) {m_Position = position; RecalculateViewMatrix();}
// 												
// 
// 		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix (); }
// 
// 
// 		inline const crm::vec3& GetPostition() const { return m_Position; }
// 		inline const float GetRotation() { return m_Rotation; RecalculateViewMatrix(); }
// 
// 		inline const crm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
// 		inline const crm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
// 		inline const crm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
// 
// 
// 
// 	private:
// 		void RecalculateViewMatrix();
// 
// 	private:
// 		crm::mat4 m_ProjectionMatrix;
// 		crm::mat4 m_ViewMatrix;
// 		crm::mat4 m_ViewProjectionMatrix;
// 
// 		crm::vec3 m_Position;
// 		float m_Rotation;
// 	};
// 
// 
// }