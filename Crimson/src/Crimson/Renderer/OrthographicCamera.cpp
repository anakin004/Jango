#include "cnpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Crimson {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_Projection(glm::ortho<float>(left, right, bottom, top, -1.0, 1.0)), m_View(1.0)
	{
		m_ProjectionView = m_Projection * m_View;
	}
	void OrthographicCamera::SetOrthographicProjection(float left, float right, float bottom, float top)
	{
		m_Projection = glm::ortho<float>(left, right, bottom, top, -1.0, 1.0);
		m_ProjectionView = m_Projection * m_View;
	}
	void OrthographicCamera::ReCalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0, 0.0, 1.0))
			* glm::scale(glm::mat4(1.0), glm::vec3(m_Scale));

		m_View = glm::inverse(transform); // invert the transform matrix to get the OrthographicCamera effect(i.e when OrthographicCamera moves up the object moves down and so on)
		m_ProjectionView = m_Projection * m_View;
	}
}

// #include "cnpch.h"
// #include "OrthographicCamera.h"
// #include "Crimson/Core/KeyCodes.h"
// 
// namespace Crimson {
// 
// 	#define BIND_EVENT_FN(x) std::bind(&OrthographicCamera::x, this, std::placeholders::_1)
// 
// 	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
// 								
// 		// flipping the far and near plane from the default -1 and 1 to 1 and -1 since norm device coords in opengl is left handed ...
// 		// we set it it 1 and -1 which will effectly flip all of our z inputs in a right handed system to be treated as a left handed z value
// 		// if you want to customize in Chroma you can, just be careful, if you take away the negation sign it will treat near and far as you input it
// 		// but always keep in my opengl's ndc is left handed
// 
// 		: m_ProjectionMatrix(crm::Ortho(left, right, top, bottom, 1.0f, -1.0f)), m_Rotation(0.0f), m_Position(0.0f, 0.0f, 0.0f)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
// 	}
// 
// 
// 	void OrthographicCamera::SetProjection(float left, float right, float top, float bottom)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		m_ProjectionMatrix = crm::Ortho(left, right, top, bottom, 1.0f, -1.0f);
// 		m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
// 	}
// 
// 	void OrthographicCamera::RecalculateViewMatrix()
// 	{
// 
// 		CN_PROFILE_FUNCTION();
// 
// 		crm::mat4 transformMatrix = crm::Mul(crm::Translation(crm::mat4(1.0f), m_Position),
// 			crm::ZRotation(m_Rotation)
// 		);
// 
// 
// 		{
// 			CN_PROFILE_SCOPE("OrthoGraphic Camera:: Inverse Matrix")
// 			m_ViewMatrix = crm::Inverse(transformMatrix);
// 		}
// 		{
// 			CN_PROFILE_SCOPE("OrthoGraphic Camera:: Mul Proj and View Matrix")
// 			m_ViewProjectionMatrix = crm::Mul(m_ProjectionMatrix, m_ViewMatrix);
// 		}
// 	}
// 	
// }