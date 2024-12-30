#pragma once


#include "Crimson/Core/Core.h"
#include "Crimson/Events/Event.h"
#include "Crimson/Core/TimeStep.h"

namespace Crimson {

	/*
	subclass this class to make wanted layers
	might have game layer, app layer, debug layer, etc
	*/
	class Layer
	{
	public:
		
		// using const char* avoids dyanmic allocation with std::string
		// we dont need that since layer names will not change
		// dyanmic layer names should be known at compile time, so if we can push and pop
		// on the layer stack, we are only doing so with layers defined in the application
		Layer(const char* name = "Layer");
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
		inline const char* GetName() const { return m_DebugName; }

	protected:
		const char* m_DebugName;
	};
}