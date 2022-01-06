#include "hvpch.h"
#include "OrthographicCameraController.h"
#include "Hovel/Input.h"
#include "Hovel/KeyCodes.h"


namespace Hovel
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		if (Input::IsKeyPressed(HV_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(HV_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(HV_KEY_W))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(HV_KEY_S))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;			
		if (m_Rotation){
			if (Input::IsKeyPressed(HV_KEY_Q))
				m_CameraRotation += m_RotationSpeed * ts;
			else if (Input::IsKeyPressed(HV_KEY_E))
				m_CameraRotation -= m_RotationSpeed * ts;
		
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);		
	}

	void OrthographicCameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HV_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(HV_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizeEvent));
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjectionMatrix(m_ZoomLevel * -m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResizeEvent(WindowResizeEvent & e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjectionMatrix(m_ZoomLevel * -m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}


}
