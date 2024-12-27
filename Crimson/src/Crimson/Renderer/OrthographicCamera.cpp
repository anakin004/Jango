#include "cnpch.h"
#include "OrthographicCamera.h"


namespace Crimson {

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

		m_ViewMatrix = crm::TransformInverse(transformMatrix);
		m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
	}

}