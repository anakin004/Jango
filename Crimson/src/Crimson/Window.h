#pragma once


#include "Crimson/Core.h"
#include "Crimson/Events/Event.h"

namespace Crimson {

	struct WindowAttribs
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowAttribs(const std::string& title = "Crimson Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};


	class CRIMSON_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// void* allows us to cast to any other type of window depending on platform
		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowAttribs& attribs = WindowAttribs());
	};
}