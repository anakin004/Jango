#pragma once

#include "RendererAPI.h"

namespace Crimson {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};
}