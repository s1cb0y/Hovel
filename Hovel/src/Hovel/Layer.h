#pragma once
#include "Hovel/Core.h"
#include "Events/Event.h"
#include "Hovel/Core/TimeStep.h"

namespace Hovel{

	class HOVEL_API Layer
	{	
	public:
		
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = 0;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(TimeStep ts) {};
		virtual void OnEvent(Event& event) {};
		virtual void OnImGuiRender() {};
		inline const std::string GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;

	};
	

}
