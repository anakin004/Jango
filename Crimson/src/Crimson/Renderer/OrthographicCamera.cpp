#include "cnpch.h"
#include "OrthographicCamera.h"
#include "Crimson/KeyCodes.h"

namespace Crimson {

	#define BIND_EVENT_FN(x) std::bind(&OrthographicCamera::x, this, std::placeholders::_1)

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
		: m_ProjectionMatrix(crm::Ortho(left, right, top, bottom))
	{
		m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
	}


	void OrthographicCamera::RecalculateViewMatrix()
	{	
		// translation * rot
		crm::mat4 transformMatrix = crm::Mul(crm::Translation(crm::mat4(1.0f), m_Position), 
											 crm::ZRotation(m_Rotation)
											);

		m_ViewMatrix = crm::Inverse(transformMatrix);
		m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
	}

}