#include "cnpch.h"

#include "Texture.h"

#include "Crimson/Core/Log.h"
#include "Crimson/Core/Core.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "RendererAPI.h"
#include "Renderer.h"

namespace Crimson {

	 Ref<Texture2D> Texture2D::Create(const std::string& path) 
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:		return  MakeRef<OpenGLTexture2D>(path);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;


	}


	 Crimson::Ref<Crimson::Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	 {
		 switch (Renderer::GetAPI())
		 {
		 case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		 case RendererAPI::API::OpenGL:		return  MakeRef<OpenGLTexture2D>(width, height);
		 }

		 CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		 return nullptr;

	 }

}