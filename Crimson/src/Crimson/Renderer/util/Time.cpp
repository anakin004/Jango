#include "cnpch.h"

#include "Crimson/Renderer/util/Time.h"
#include "Platform/OpenGL/OpenGLTime.h"

namespace Crimson {

	double GetTime() {

		switch (RendererAPI::GetAPI()) {

		case GraphicsAPI::OpenGL:		return OpenGLGetTime();
		case GraphicsAPI::None:			CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return 0.0;

		}


	}


}