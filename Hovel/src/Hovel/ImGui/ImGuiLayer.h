#pragma once

#include "Hovel/Layer.h"

#include "Hovel/Events/ApplicationEvent.h"
#include "Hovel/Events/KeyEvent.h"
#include "Hovel/Events/MouseEvent.h"
namespace Hovel {

	class HOVEL_API ImGuiLayer : public Layer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}