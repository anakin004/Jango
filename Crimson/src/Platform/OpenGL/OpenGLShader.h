#pragma once

#include "Crimson/Renderer/Shader.h"

namespace Crimson {


	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};


	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filename);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void compileErrors(unsigned int shader, const std::string& type) override;

		virtual inline uint32_t GetID() const override { return m_RendererID; }

	private:
		ShaderProgramSource get_file_contents(const std::string& filename);

		uint32_t m_RendererID;
	};


}