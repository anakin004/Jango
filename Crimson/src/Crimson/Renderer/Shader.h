#pragma once

#include <string>
#include <crm_mth.h>

namespace Crimson {


	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void compileErrors(unsigned int shader, const std::string& type) = 0;

		static Shader* Create(const std::string& filename);

		virtual void UploadUniformMat4(const std::string& name, crm::mat4& matrix) = 0;
	};
}