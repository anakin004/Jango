#include "cnpch.h"

#include "Texture.h"

#include "Crimson/Core/Log.h"
#include "Crimson/Core/Core.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "RendererAPI.h"
#include "Renderer3D.h"
#include "Renderer2D.h"

namespace Crimson {

	 Ref<Texture2D> Texture2D::Create(const std::string& path) 
	{

		switch (Renderer2D::GetAPI())
		{
		case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
		case RendererAPI::API::OpenGL:		return  MakeRef<OpenGLTexture2D>(path);
		}

		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;


	}


}