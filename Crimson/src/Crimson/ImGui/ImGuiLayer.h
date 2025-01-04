#pragma once

#include "Crimson/Core/Layer.h"
#include "Crimson/Events/KeyEvent.h"
#include "Crimson/Events/MouseEvent.h"
#include "Crimson/Events/ApplicationEvent.h"
#include "imgui.h"

namespace Crimson {

	class ImGuiLayer : public Layer
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
		void SetDarkThemeColors();

	private:

		bool m_DispatchEvents = false;
		static ImFont* m_Font;
	};

}