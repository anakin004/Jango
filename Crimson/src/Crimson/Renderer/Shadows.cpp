#include "cnpch.h"
#include "Shadows.h"
#include "Platform/Opengl/OpenGlShadows.h"

namespace Crimson
{
	Shadows::Shadows()
	{
	}
	Shadows::Shadows(float width, float height)
	{
	}
	Shadows::~Shadows()
	{
	}
	Ref<Shadows> Shadows::Create(float width, float height)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			return MakeRef<OpenGLShadows>(width,height);
		}
	}
	Ref<Shadows> Shadows::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			return MakeRef<OpenGLShadows>(2048, 2048);
		}
	}
}