#include "cnpch.h"
#include "OpenGLFog.h"
#include "glad/glad.h"

namespace Crimson
{
	OpenGLFog::OpenGLFog()
		:m_density(0.005),m_gradient(1.3),m_fogStart(60.0f),m_fogEnd(5000)
	{
		m_fogShader = Shader::Create("Assets/Shaders/pp_fogShader.glsl");
	}
	OpenGLFog::OpenGLFog(float density, float fogStart, float fogEnd, float fogTop, float fogBottom, glm::vec2 ScreenSize)
		: m_density(density), m_gradient(1), m_fogStart(fogStart), m_fogEnd(fogEnd), m_screenSize(ScreenSize)
	{
		m_fogShader = Shader::Create("Assets/Shaders/pp_fogShader.glsl");

		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_screenSize.x, m_screenSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);
		GLenum buff[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buff);
	}
	OpenGLFog::~OpenGLFog()
	{
	}
	void OpenGLFog::RenderFog(Camera& cam, glm::vec2 screenSize)
	{
		m_fogShader->Bind();
		m_fogShader->SetInt("u_sceneDepth", SCENE_DEPTH_SLOT);
		m_fogShader->SetInt("u_sceneColor", ORIGINAL_SCENE_TEXTURE_SLOT);
		m_fogShader->SetFloat("u_nearPlane", cam.GetPerspectiveNear());
		m_fogShader->SetFloat("u_farPlane", cam.GetPerspectiveFar());
		m_fogShader->SetFloat("u_density", m_density);
		m_fogShader->SetFloat("u_gradient", m_gradient);
		m_fogShader->SetFloat3("u_fogColor", m_fogColor);
		m_fogShader->SetFloat("u_fogTop", m_fogTop);
		m_fogShader->SetFloat("u_fogEnd", m_fogEnd);
		m_fogShader->SetFloat3("u_sunDir", Renderer3D::m_SunLightDir);
		m_fogShader->SetFloat3("u_ViewDir", cam.GetViewDirection());
		m_fogShader->SetFloat3("u_CamPos", cam.GetCameraPosition());
		m_fogShader->SetMat4("u_Projection", cam.GetProjectionMatrix());
		m_fogShader->SetMat4("u_View", cam.GetViewMatrix());

		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		glViewport(0, 0, m_screenSize.x, m_screenSize.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderQuad();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, screenSize.x, screenSize.y);

		glBindTextureUnit(ORIGINAL_SCENE_TEXTURE_SLOT, m_textureID);//update these slotes to capture the post-processing
		glBindTextureUnit(SCENE_TEXTURE_SLOT, m_textureID);

	}


	void OpenGLFog::RenderQuad()
	{
		//this function renders a quad infront of the camera
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);

		//auto inv = glm::inverse(proj * glm::mat4(glm::mat3(view)));//get inverse of projection view to convert cannonical view to world space
		glm::vec4 data[] = {
			glm::vec4(-1,-1,0,1),glm::vec4(0,0,0,0),
			glm::vec4(1,-1,0,1),glm::vec4(1,0,0,0),
			glm::vec4(1,1,0,1),glm::vec4(1,1,0,0),
			glm::vec4(-1,1,0,1),glm::vec4(0,1,0,0)
		};

		Ref<VertexArray> vao = VertexArray::Create();
		Ref<VertexBuffer> vb = VertexBuffer::Create(&data[0].x, sizeof(data));
		unsigned int i_data[] = { 0,1,2,0,2,3 };
		Ref<IndexBuffer> ib = IndexBuffer::Create(i_data, sizeof(i_data));

		Ref<BufferLayout> bl = std::make_shared<BufferLayout>(); //buffer layout

		bl->push("position", ShaderDataType::Float4);
		bl->push("direction", ShaderDataType::Float4);

		vao->AddBuffer(bl, vb);
		vao->SetIndexBuffer(ib);

		RenderCommand::DrawIndex(*vao);

		glDepthMask(GL_TRUE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
}