#include "cnpch.h"

#include "OpenGLWater.h"
#include "glad/glad.h"

namespace Crimson {

	OpenGLWater::OpenGLWater(const glm::vec3& dims, const glm::vec3& water_color, const glm::vec2& screen_size)
	{
		CN_PROFILE_FUNCTION()

		m_waterShader = Shader::Create("Assets/Shaders/waterShader.glsl");


		// making two fbos and textures for them

		glGenFramebuffers(1, &m_framebuffer1ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer1ID);

		glGenTextures(1, &m_texture1ID);
		glBindTexture(GL_TEXTURE_2D, m_texture1ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_screenSize.x, m_screenSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture1ID, 0);
		GLenum buff[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buff);


		glGenFramebuffers(1, &m_framebuffer2ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer2ID);

		glGenTextures(1, &m_texture2ID);
		glBindTexture(GL_TEXTURE_2D, m_texture2ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_screenSize.x, m_screenSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture2ID, 0);
		GLenum buff[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buff);



		// water quad

		std::array<glm::vec4, 8> data =
		{
			{
				glm::vec4(-1,-1,0,1),
				glm::vec4(0,0,0,0),
				glm::vec4(1,-1,0,1),
				glm::vec4(1,0,0,0),
				glm::vec4(1,1,0,1),
				glm::vec4(1,1,0,0),
				glm::vec4(-1,1,0,1),
				glm::vec4(0,1,0,0)
			}
		};

		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(&data[0].x, sizeof(data));

		std::array<uint32_t, 6> i_data = { 0,1,2,0,2,3 };
		m_EBO = IndexBuffer::Create(&i_data[0], sizeof(i_data));

		m_Bl = std::make_shared<BufferLayout>(); //buffer layout

		m_Bl->push("position", ShaderDataType::Float4);
		m_Bl->push("direction", ShaderDataType::Float4);

		m_VAO->AddBuffer(m_Bl, m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);

	}

	void SetWaterParameters(const glm::vec3& dims, const glm::vec3& water_color)
	{

	}

	void RenderWater(Camera& cam, const glm::vec2& screen_size)
	{

	}

}