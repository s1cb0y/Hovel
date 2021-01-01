#pragma once
#include "Hovel/Core.h"
#include "Events/Event.h"

namespace Hovel{

	class HOVEL_API Layer
	{	
	public:
		
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = 0;

		virtual void OnAttach() {};
		virtual void OnDetatch() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;

	};
	

}