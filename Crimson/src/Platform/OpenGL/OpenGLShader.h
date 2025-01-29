
#pragma once
#include "Crimson/Core/Log.h"
#include "glm/glm.hpp"
#include "Crimson/Renderer/Shader.h"
namespace Crimson {

	struct Shaders {
		std::string VertexShader;
		std::string Fragmentshader;
		std::string GeometryShader;
		std::string TessellationControlShader;
		std::string TessellationEvaluationShader;
		std::string ComputeShader;
		//compute shader, tess shader....
	};

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::string& vertexshader, std::string& fragmentshader);
		OpenGLShader(const std::string& path);
		~OpenGLShader();

		unsigned int CompileShader(std::string&, unsigned int);
		Shaders ParseFile(const std::string& path);

		void Bind()override;
		void UnBind()override;

		void SetMat4(const std::string& str, glm::mat4& UniformMat4, size_t count = 1) override;
		void SetInt(const std::string& str, const int& UniformInt) override;
		void SetIntArray(const std::string& str, const size_t size, const void* pointer) override;
		void SetFloat(const std::string& str, const float& UniformFloat) override;
		virtual void SetFloatArray(const std::string& str, float& UniformFloat, size_t count) override;
		void SetFloat4(const std::string& str, const glm::vec4& UniformFloat4) override;
		void SetFloat3(const std::string& str, const glm::vec3& UniformFloat4) override;
		void SetFloat3Array(const std::string& str, const float* pointer, size_t count) override;
		void SetFloat4Array(const std::string& str, const float* arr, size_t count) override;

	private://opengl specific
		void UploadUniformMat4(const std::string& str, glm::mat4& UniformMat4, size_t count = 1);
		void UploadUniformInt(const std::string& str, const int& UniformInt);
		void UploadIntArray(const std::string& str, const size_t size, const void* pointer);
		void UpladUniformFloat(const std::string& str, const float& UniformFloat);
		void UpladUniformFloatArray(const std::string& str, size_t count, float& UniformFloat);
		void UpladUniformFloat4(const std::string& str, const glm::vec4& UniformFloat4);
		void UpladUniformFloat3(const std::string& str, const glm::vec3& UniformFloat3);
		void UpladUniformFloat3Array(const std::string& str, const float* pointer, size_t count);
		void UpladUniformFloat4Array(const std::string& str, const float* pointer, size_t count);

		unsigned int program;
		Shaders m_shaders;
	};
}

// #pragma once
// 
// #include "Crimson/Renderer/Shader.h"
// #include <crm_mth.h>
// 
// namespace Crimson {
// 
// 
// 	struct ShaderProgramSource
// 	{
// 		std::string VertexSource;
// 		std::string FragmentSource;
// 	};
// 
// 
// 	class OpenGLShader : public Shader
// 	{
// 	public:
// 		OpenGLShader(const std::string& filename);
// 		OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
// 		virtual ~OpenGLShader();
// 
// 		virtual void Bind() const override;
// 		virtual void Unbind() const override;
// 
// 		virtual const std::string& GetName() const override { return m_Name; }
// 		
// 		virtual void SetInt(const std::string& name, int val) override;
// 		virtual void SetIntArray(const std::string& name, int* vals, uint32_t count) override;
// 		virtual void SetFloat(const std::string& name, const float f) override;
// 		virtual void SetFloat2(const std::string& name, const crm::vec2& v) override;
// 		virtual void SetFloat3(const std::string& name, const crm::vec3& v) override;
// 		virtual void SetFloat4(const std::string& name, const crm::vec4& v) override;
// 		virtual void SetMat4(const std::string& name, const crm::mat4& m) override;
// 
// 		void UploadUniformInt(const std::string& name, int value);
// 		void UploadUniformIntArray(const std::string& name, int* vals, uint32_t count);
// 
// 		void UploadUniformMat4(const std::string& name, const crm::mat4& matrix);
// 		void UploadUniformMat3(const std::string& name, const crm::mat3& matrix);
// 
// 		void UploadUniformFloat(const std::string& name, float value);
// 		void UploadUniformFloat2(const std::string& name, const crm::vec2& v);
// 		void UploadUniformFloat3(const std::string& name, const crm::vec3& v);
// 		void UploadUniformFloat4(const std::string& name, const crm::vec4& v);
// 
// 
// 
// 	private:
// 		void compileErrors(unsigned int shader, const std::string& type);
// 		int GetUniform(const std::string& name);
// 
// 	private:
// 		ShaderProgramSource get_file_contents(const std::string& filename);
// 
// 		//shaders might change often, this will not be static atleast for now
// 		std::unordered_map<std::string, int> m_UniformCache;
// 
// 
// 		uint32_t m_RendererID;
// 		std::string m_Name;
// 	};
// 
// 
// }