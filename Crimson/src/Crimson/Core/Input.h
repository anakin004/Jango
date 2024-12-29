#pragma once

#include "Crimson/Core/Core.h"

namespace Crimson
{
	// going to be singleton since there will be global input polling and key states
	class CRIMSON_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:

		// this is what we implement per platform
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		
		virtual std::pair<float, float> GetMousePosImpl() const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

	private:
		static Input* s_Instance;
	};
}