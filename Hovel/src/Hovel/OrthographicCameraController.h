#pragma once

#include "Hovel/Renderer/OrthoGraphCamera.h"

#include "Hovel/Core/TimeStep.h"
#include "Hovel/Events/MouseEvent.h"
#include "Hovel/Events/ApplicationEvent.h"

namespace Hovel {

	class OrthographicCameraController {
		
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		OrthographicCamera m_Camera;
		float m_AspectRatio;		
		bool m_Rotation;
		float m_ZoomLevel = 1.0f;

		float m_CameraRotation = 0.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 5.0f, m_RotationSpeed = 1.0f;

	};
}