#pragma once

#include "Crimson/Renderer/Shader.h"
#include <crm_mth.h>

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
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformMat4(const std::string& name, const crm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const crm::mat3& matrix);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const crm::vec2& v);
		void UploadUniformFloat3(const std::string& name, const crm::vec3& v);
		void UploadUniformFloat4(const std::string& name, const crm::vec4& v);

	private:
		void compileErrors(unsigned int shader, const std::string& type);
		int GetUniform(const std::string& name);

	private:
		ShaderProgramSource get_file_contents(const std::string& filename);

		//shaders might change often, this will not be static atleast for now
		std::unordered_map<std::string, int> m_UniformCache;


		uint32_t m_RendererID;
	};


}