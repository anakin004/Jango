#pragma once


#include "Crimson/Core.h"
#include "Crimson/Events/Event.h"
#include "Crimson/Core/TimeStep.h"

namespace Crimson {

	/*
	subclass this class to make wanted layers
	might have game layer, app layer, debug layer, etc
	*/
	class CRIMSON_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// might make these pure virtual, but for example just made it so they dont need to be overiden
		virtual void OnAttach()  {};
		virtual void OnDetach()  {};
		virtual void OnUpdate(TimeStep timeStep) {};
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		
		// to setup
		//virtual void Enable() = 0;
		//virtual void Disable() = 0;

		// for debugging, not supposed to get the layer by name to find, update, etc
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}