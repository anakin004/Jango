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
		OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }
		

		virtual void SetFloat3(const std::string& name, const crm::vec3& v) override;
		virtual void SetFloat4(const std::string& name, const crm::vec4& v) override;
		virtual void SetMat4(const std::string& name, const crm::mat4& m) override;

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
		std::string m_Name;
	};


}