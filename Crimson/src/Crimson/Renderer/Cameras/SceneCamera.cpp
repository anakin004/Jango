#include "cnpch.h"
#include "SceneCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Crimson/Renderer/CubeMapEnvironment.h"

namespace Crimson {
	SceneCamera::SceneCamera(float Width, float Height)
	{
		SetViewportSize(Width/Height);
	}
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
		RecalculateProjectionView();
	}
	void SceneCamera::SetPerspctive(float v_FOV, float Near, float Far)
	{
		m_verticalFOV = v_FOV;
		m_PerspectiveNear = Near;
		m_PerspectiveFar = Far;

		RecalculateProjection();
		RecalculateProjectionView();
	}
	void SceneCamera::SetCameraPosition(const glm::vec3& pos)
	{
		m_Position = pos; 
		RecalculateProjectionView();
	}
	void SceneCamera::SetViewDirection(const glm::vec3& dir)
	{
		m_ViewDirection = dir; 
		RecalculateProjectionView();
	}

	void SceneCamera::SetUPVector(const glm::vec3& up)
	{
		Up = up; 
		RecalculateProjectionView();
	}
	void SceneCamera::SetViewportSize(float aspectratio)
	{
		m_AspectRatio = aspectratio;
		RecalculateProjection();
		RecalculateProjectionView();
	}
	void SceneCamera::OnEvent(Event& e)
	{

	}

	void SceneCamera::OnUpdate(TimeStep ts)
	{
		RightVector = glm::cross(m_ViewDirection, Up);
		RecalculateProjectionView();
	}

	void SceneCamera::RotateCamera(float pitch , float yaw, float roll)
	{
		m_pitch = pitch;
		m_yaw = yaw;
		m_roll = roll;
		//pitch = glm::clamp(pitch, -89.0f, 89.0f);
		m_ViewDirection = glm::mat3(glm::rotate(glm::radians(yaw), Up)) * glm::mat3(glm::rotate(glm::radians(pitch), RightVector)) * glm::mat3(glm::rotate(glm::radians(roll), m_ViewDirection)) * glm::vec3(0, 0, 1);
		RecalculateProjectionView();
	}

	void SceneCamera::SetOrthographic(float Size, float Near, float Far)
	{
		m_projection_type = ProjectionTypes::Orhtographic;
		m_OrthographicSize = Size;
		m_OrthographicNear = Near;
		m_OrthographicFar = Far;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		switch (m_projection_type)
		{
		case ProjectionTypes::Orhtographic:
		{
			float left = -m_AspectRatio * m_OrthographicSize * 0.5;
			float right = m_AspectRatio * m_OrthographicSize * 0.5;
			float bottom = -m_OrthographicSize * 0.5;
			float Up = m_OrthographicSize * 0.5;
			m_Projection = glm::ortho(left, right, bottom, Up, m_OrthographicNear, m_OrthographicFar);
			return;
		}
		case ProjectionTypes::perspective:
			m_Projection = glm::perspective(glm::radians(m_verticalFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
			return;
		}
	}
	void SceneCamera::RecalculateProjectionView()
	{
		//moving the camera is nothing but transforming the world
		m_View = glm::lookAt(m_Position, glm::normalize(m_ViewDirection) + m_Position, Up);//this gives the view matrix
		m_ProjectionView = m_Projection * m_View;
	}
}
