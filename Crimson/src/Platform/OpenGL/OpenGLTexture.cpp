#include "cnpch.h"


#include "Crimson/Core/Log.h"

#include "OpenGLTexture.h"

#include "stb_image.h"
#include <Glad/glad.h>

namespace Crimson {


	OpenGLTexture2D::OpenGLTexture2D(const std::string path)
		: m_Path(path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		CN_CORE_ASSERT(data, "Failed to load texture {0}", path);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFmt = internalFormat;
		m_DataFmt = dataFormat;


		// both will be zero if one is zero
		CN_CORE_ASSERT(internalFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		// allocate memory on gpu 
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_NEAREST);


		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
	

		stbi_image_free(data);

	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height), m_InternalFmt(GL_RGBA8), m_DataFmt(GL_RGBA)
	{

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		// allocate memory on gpu 
		glTextureStorage2D(m_RendererID, 1, m_InternalFmt, m_Width, m_Height);

		// to paramaterize
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_NEAREST);



	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) const
	{
		uint32_t bpp = m_DataFmt == GL_RGBA ? 4 : 3;
		CN_CORE_ASSERT(size == m_Width * m_Height * bpp, "Invalid Texture Data Size!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFmt, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}