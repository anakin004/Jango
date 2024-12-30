#pragma once

#include <string>
#include <unordered_map>

#include <crm_mth.h>

namespace Crimson {


	class Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int val) = 0;
		virtual void SetFloat(const std::string& name, const float f) = 0;
		virtual void SetFloat2(const std::string& name, const crm::vec2& v) = 0;
		virtual void SetFloat3(const std::string& name, const crm::vec3& v) = 0;
		virtual void SetFloat4(const std::string& name, const crm::vec4& v) = 0;
		virtual void SetMat4(const std::string& name, const crm::mat4& m) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filename);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
	};


	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		// for adding shaders as custom names
		void Add(const Ref<Shader>& shader, const std::string& name);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}