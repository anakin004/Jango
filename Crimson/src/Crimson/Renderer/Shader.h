#pragma once

#include <string>

namespace Crimson {


	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void compileErrors(unsigned int shader, const std::string& type) = 0;

		// shorthand to handle uniforms for testing, no all api's have a "id" for shader
		virtual uint32_t GetID() const { return -1; };

		static Shader* Create(const std::string& filename);
	};
}