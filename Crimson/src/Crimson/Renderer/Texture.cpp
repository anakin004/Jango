#include "cnpch.h"
#include "Texture.h"
#include "stb_image.h"
#include "RendererAPI.h"
#include "Crimson/Core/ResourceManager.h"
#include "Platform/Opengl/OpenGlTexture2D.h"
#include "Platform/Opengl/OpenGlTexture2DArray.h"

namespace Crimson {
	bool Texture2D::ValidateTexture(const std::string& path)
	{
		int channels;
		int m_Height, m_Width;
		stbi_uc* pixel_data = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0);
		if (pixel_data == nullptr)
			return false;
		else
			return true;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path, bool bUse16BitTexture)
	{
		Ref<Texture2D> instance;
		uint64_t ID;
		switch (RendererAPI::GetAPI()) {
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			ID = UUID(path);
			if (ResourceManager::allTextures.find(ID) == ResourceManager::allTextures.end())// load a texture only once
			{
				instance = MakeRef<OpenGLTexture2D>(path, bUse16BitTexture);
				ResourceManager::allTextures[instance->uuid] = instance;
			}
			else
				instance = std::dynamic_pointer_cast<Texture2D>(ResourceManager::allTextures[ID]); //dynamic_pointer_cast helps to give a shared ptr of derived type casting from base
			return instance;
		default:
			return nullptr;
		}
	}
	Ref<Texture2D> Texture2D::Create(const unsigned int Width, const unsigned int Height, const unsigned int data)
	{
		switch (RendererAPI::GetAPI()) {
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			return MakeRef<OpenGLTexture2D>(Width, Height, data);
		default:
			return nullptr;
		}
	}
	Ref<Texture2DArray> Texture2DArray::Create(const std::vector<std::string>& paths, int numMaterials, int numChannels, bool bUse16BitTexture)
	{
		switch (RendererAPI::GetAPI()) {
		case GraphicsAPI::None:
			return nullptr;
		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLTexture2DArray>(paths, numMaterials, numChannels, bUse16BitTexture);
		default:
			return nullptr;
		}
	}
}

// #include "cnpch.h"
// 
// #include "Texture.h"
// 
// #include "Crimson/Core/Log.h"
// #include "Crimson/Core/Core.h"
// 
// #include "Platform/OpenGL/OpenGLTexture.h"
// 
// #include "RendererAPI.h"
// #include "Renderer.h"
// 
// namespace Crimson {
// 
// 	 Ref<Texture2D> Texture2D::Create(const std::string& path) 
// 	{
// 
// 		switch (Renderer::GetAPI())
// 		{
// 		case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
// 		case RendererAPI::API::OpenGL:		return  MakeRef<OpenGLTexture2D>(path);
// 		}
// 
// 		CN_CORE_ASSERT(false, "Unknown RendererAPI!");
// 		return nullptr;
// 
// 
// 	}
// 
// 
// 	 Crimson::Ref<Crimson::Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
// 	 {
// 		 switch (Renderer::GetAPI())
// 		 {
// 		 case RendererAPI::API::None:		CN_CORE_ASSERT(false, "RendererAPI: None not supported currently!"); return nullptr;
// 		 case RendererAPI::API::OpenGL:		return  MakeRef<OpenGLTexture2D>(width, height);
// 		 }
// 
// 		 CN_CORE_ASSERT(false, "Unknown RendererAPI!");
// 		 return nullptr;
// 
// 	 }
// 
// }