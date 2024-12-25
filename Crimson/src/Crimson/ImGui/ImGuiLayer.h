#pragma once

#include "Crimson/Layer.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Events/ApplicationEvent.h"

namespace Crimson {

	class CRIMSON_API ImGuiLayer : public Layer
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
		float m_Time = 0.f;

		// for copy and paste
		char m_InputBuffer[256] = "Hello";
	
	};

}