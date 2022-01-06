#pragma once

#include "glm/glm.hpp"

namespace Hovel{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float xmin, float xmax, float ymin, float ymax);

		glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalculateMatrices(); }
		float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation) { m_Rotation = rotation; RecalculateMatrices();}
		
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		void SetProjectionMatrix(float left, float right, float bottom, float top);
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
	
		void RecalculateMatrices();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		
	};
}