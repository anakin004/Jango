#include "cnpch.h"
#include "EditorCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Crimson/Renderer/CubeMapEnvironment.h"
#include "Crimson/Core/KeyCodes.h"

#include <glm/glm.hpp>

namespace Crimson {
	float EditorCamera::camera_MovementSpeed = 10;
	EditorCamera::EditorCamera()
		: m_View(1.0)
	{
		RightVector = glm::normalize(glm::cross(m_ViewDirection, Up));
		m_Projection = glm::perspective(glm::radians(m_verticalFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		m_ProjectionView = m_Projection * m_View;
		m_movespeed = camera_MovementSpeed;
	}
	EditorCamera::EditorCamera(float width, float Height)
	{
		bIsMainCamera = true;
		RightVector = glm::cross(m_ViewDirection, Up);
		SetViewportSize(width/Height);
		m_movespeed = camera_MovementSpeed;

	}

	void EditorCamera::SetViewportSize(float aspectratio)
	{
		m_AspectRatio = aspectratio;
		RecalculateProjection();
		RecalculateProjectionView();
	}

	void EditorCamera::RotateCamera(float pitch, float yaw, float roll)
	{
		m_pitch = pitch;
		m_yaw = yaw;
		m_roll = roll;
		m_ViewDirection = glm::mat3(glm::rotate(glm::radians(yaw), Up)) * glm::mat3(glm::rotate(glm::radians(pitch), RightVector)) * glm::mat3(glm::rotate(glm::radians(roll), m_ViewDirection)) * m_ViewDirection;
		RecalculateProjectionView();
	}

	void EditorCamera::RecalculateProjection()
	{
		m_Projection = glm::perspective(glm::radians(m_verticalFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
	}

	void EditorCamera::SetPerspctive(float v_FOV, float Near, float Far)
	{
		m_verticalFOV = v_FOV;
		m_PerspectiveNear = Near;
		m_PerspectiveFar = Far;

		RecalculateProjection();
		RecalculateProjectionView();
	}
	
	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dis(e);

		dis.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& event) {
			m_verticalFOV += event.GetYOffset() * 0.1;
			RecalculateProjection();
			RecalculateProjectionView();
			return true; });
	}

	void EditorCamera::OnUpdate(TimeStep deltatime)
	{
		m_movespeed = camera_MovementSpeed;
		RightVector  = glm::cross(m_ViewDirection, Up);//we get the right vector (as it is always perpendicular to up and m_ViewDirection)
		
		if (Input::IsKeyPressed(CRIMSON_KEY_W))
			m_Position += m_ViewDirection * glm::vec3(m_movespeed*deltatime);//move along the View direction
		if (Input::IsKeyPressed(CRIMSON_KEY_S))
			m_Position -= m_ViewDirection * glm::vec3(m_movespeed*deltatime);//move along the View direction
		if (Input::IsKeyPressed(CRIMSON_KEY_A))
			m_Position -= RightVector * glm::vec3(m_movespeed*deltatime);//move along the right vector
		if (Input::IsKeyPressed(CRIMSON_KEY_D))
			m_Position += RightVector * glm::vec3(m_movespeed*deltatime);
		if(Input::IsKeyPressed(CRIMSON_KEY_Q))
			m_Position += Up * glm::vec3(m_movespeed*deltatime);//move along up vector
		if (Input::IsKeyPressed(CRIMSON_KEY_E))
			m_Position -= Up * glm::vec3(m_movespeed*deltatime);
		//if (Input::IsKeyPressed(CRIMSON_KEY_R))//reset camera when R is pressed
		//{
		//	m_Position = { 0,0,-1 };
		//	m_ViewDirection = { 0,0,1 };
		//	m_verticalFOV = 45.0f;
		//}

		glm::vec2 NewMousePos = { Input::GetMousePos().first,Input::GetMousePos().second };
		if (Input::IsMouseButtonPressed(CRIMSON_MOUSE_BUTTON_2))//camera pan
		{
			auto& delta = NewMousePos - OldMousePos;//get change in mouse position

			m_ViewDirection = glm::mat3(glm::rotate(glm::radians(-delta.x) * 0.1f, Up)) * m_ViewDirection;//invert it
			m_ViewDirection = glm::mat3(glm::rotate(glm::radians(-delta.y) * 0.1f, RightVector)) * m_ViewDirection;//rotate along right vector
			m_ViewDirection = glm::normalize(m_ViewDirection);
		}
		OldMousePos = NewMousePos;

		RecalculateProjectionView();
	}

	void EditorCamera::RecalculateProjectionView()
	{
		m_View = glm::lookAt(m_Position - glm::normalize(m_ViewDirection), m_Position, Up);//this gives the view matrix
		m_ProjectionView = m_Projection * m_View;
	}
}
