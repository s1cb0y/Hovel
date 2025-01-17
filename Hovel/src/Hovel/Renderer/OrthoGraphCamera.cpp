#include "hvpch.h"
#include "OrthoGraphCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Hovel {
	
	OrthographicCamera::OrthographicCamera(float xmin, float xmax, float ymin, float ymax)
		: m_ViewMatrix(1.0f), m_ProjectionMatrix(glm::ortho(xmin, xmax, ymin, ymax, -1.0f, 1.0f))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateMatrices()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0), m_Rotation, glm::vec3(0, 0, 1));		
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	 
}