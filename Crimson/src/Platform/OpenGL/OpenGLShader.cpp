#include "cnpch.h"
#include "OpenGlShader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Crimson {
	//not adding geometry shader feature here as this different shader technique is not used for now
	OpenGLShader::OpenGLShader(std::string& vertexshader, std::string& fragmentshader)
	{

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		const char* chr = vertexshader.c_str();
		glShaderSource(vs, 1, &chr, nullptr);
		glCompileShader(vs);
		{
			int id;
			glGetShaderiv(vs, GL_COMPILE_STATUS, &id);
			if (id == GL_FALSE)//if the shader code is not successfully compiled
			{
				int length;
				glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
				char* message = new char[length];
				glGetShaderInfoLog(vs, length, &length, message);
				CN_CORE_ERROR(message);
			}

		}

		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char* chr1 = fragmentshader.c_str();
		glShaderSource(fs, 1, &chr1, nullptr);
		glCompileShader(fs);
		int id;
		glGetShaderiv(fs, GL_COMPILE_STATUS, &id);
		if (id)
		{
			int length;
			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(fs, length, &length, message);
			CN_CORE_ERROR(message);
		}

		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glUseProgram(program);
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		program = glCreateProgram();

		m_shaders = ParseFile(path);
		if (m_shaders.ComputeShader != "")
		{
			unsigned int cs = CompileShader(m_shaders.ComputeShader, GL_COMPUTE_SHADER);
			glAttachShader(program, cs);
		}
		else
		{
			unsigned int vs = CompileShader(m_shaders.VertexShader, GL_VERTEX_SHADER);
			unsigned int fs = CompileShader(m_shaders.Fragmentshader, GL_FRAGMENT_SHADER);

			glAttachShader(program, vs);
			glAttachShader(program, fs);
		}

		if (m_shaders.GeometryShader != "")// all optional shaders must be done in this manner
		{
			unsigned int gs = CompileShader(m_shaders.GeometryShader, GL_GEOMETRY_SHADER);
			glAttachShader(program, gs);
		}

		if (m_shaders.TessellationControlShader != "")
		{
			unsigned int tcs = CompileShader(m_shaders.TessellationControlShader, GL_TESS_CONTROL_SHADER);
			glAttachShader(program, tcs);
		}

		if (m_shaders.TessellationEvaluationShader != "")
		{
			unsigned int tes = CompileShader(m_shaders.TessellationEvaluationShader, GL_TESS_EVALUATION_SHADER);
			glAttachShader(program, tes);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		glUseProgram(program);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(program);
	}

	unsigned int OpenGLShader::CompileShader(std::string& Shader, unsigned int type)
	{
		unsigned int s = glCreateShader(type);
		const char* chr = Shader.c_str();
		int length = Shader.size();
		glShaderSource(s, 1, &chr, nullptr);
		glCompileShader(s);

		int id;
		glGetShaderiv(s, GL_COMPILE_STATUS, &id);
		if (id == GL_FALSE)//if the shader code is not successfully compiled
		{
			int length;
			glGetShaderiv(s, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(s, length, &length, message);
			CN_CORE_ERROR(message);
		}

		return s;
	}

	Shaders OpenGLShader::ParseFile(const std::string& path)
	{
		enum type {
			VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, TESS_CONTROL_SHADER, TESS_EVALUATION_SHADER, COMPUTE_SHADER
		};

		std::ifstream stream(path);
		if (&stream == nullptr)
			CN_CORE_ERROR("Shader File Not Found!!");
		std::string ShaderCode;
		std::string Shader[6];//as for now we have 6 shaders
		int index;
		while (std::getline(stream, ShaderCode))
		{
			if (ShaderCode.find("#shader vertex") != std::string::npos)
			{
				index = type::VERTEX_SHADER;
				continue;
			}
			if (ShaderCode.find("#shader fragment") != std::string::npos)
			{
				index = type::FRAGMENT_SHADER;
				continue;
			}
			if (ShaderCode.find("#shader geometry") != std::string::npos)
			{
				index = type::GEOMETRY_SHADER;
				continue;
			}

			if (ShaderCode.find("#shader tessellation control") != std::string::npos)
			{
				index = type::TESS_CONTROL_SHADER;
				continue;
			}

			if (ShaderCode.find("#shader tessellation evaluation") != std::string::npos)
			{
				index = type::TESS_EVALUATION_SHADER;
				continue;
			}
			if (ShaderCode.find("#shader compute") != std::string::npos)
			{
				index = type::COMPUTE_SHADER;
				continue;
			}

			Shader[index].append(ShaderCode + "\n");
		}
		return { Shader[0],Shader[1],Shader[2],Shader[3],Shader[4], Shader[5] };
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(program);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetMat4(const std::string& str, glm::mat4& UniformMat4, size_t count)
	{
		UploadUniformMat4(str, UniformMat4, count);
	}

	void OpenGLShader::SetInt(const std::string& str, const int& UniformInt)
	{
		UploadUniformInt(str, UniformInt);
	}

	void OpenGLShader::SetFloat(const std::string& str, const float& UniformFloat)
	{
		UpladUniformFloat(str, UniformFloat);
	}

	void OpenGLShader::SetFloatArray(const std::string& str, float& UniformFloatArr, size_t count)
	{
		UpladUniformFloatArray(str, count, UniformFloatArr);
	}

	void OpenGLShader::SetFloat4(const std::string& str, const glm::vec4& UniformFloat4)
	{
		UpladUniformFloat4(str, UniformFloat4);
	}

	void OpenGLShader::SetFloat3(const std::string& str, const glm::vec3& UniformFloat3)
	{
		UpladUniformFloat3(str, UniformFloat3);
	}

	void OpenGLShader::SetFloat3Array(const std::string& str, const float* pointer, size_t count)
	{
		UpladUniformFloat3Array(str, pointer, count);
	}

	void OpenGLShader::SetFloat4Array(const std::string& str, const float* arr, size_t count)
	{
		UpladUniformFloat4Array(str, arr, count);
	}

	void OpenGLShader::SetIntArray(const std::string& str, const size_t size, const void* pointer)
	{
		UploadIntArray(str, size, pointer);
	}

	//opengl specific upload uniform
	void OpenGLShader::UploadUniformMat4(const std::string& str, glm::mat4& UniformMat4, size_t count)
	{
		unsigned int location = glGetUniformLocation(program, str.c_str());
		glUniformMatrix4fv(location, count, false, glm::value_ptr(UniformMat4));

	}

	void OpenGLShader::UploadUniformInt(const std::string& str, const int& UniformInt)
	{
		unsigned int location = glGetUniformLocation(program, str.c_str());
		glUniform1i(location, UniformInt);
	}

	void OpenGLShader::UploadIntArray(const std::string& str, const size_t size, const void* pointer)
	{
		auto location = glGetUniformLocation(program, str.c_str());
		glUniform1iv(location, size, (const GLint*)pointer);
	}

	void OpenGLShader::UpladUniformFloat(const std::string& str, const float& UniformFloat)
	{
		unsigned int location = glGetUniformLocation(program, str.c_str());
		glUniform1f(location, UniformFloat);
	}

	void OpenGLShader::UpladUniformFloatArray(const std::string& str, size_t count, float& UniformFloatArr)
	{
		unsigned int location = glGetUniformLocation(program, str.c_str());
		glUniform1fv(location, count, &UniformFloatArr);
	}

	void OpenGLShader::UpladUniformFloat4(const std::string& str, const glm::vec4& UniformFloat4)
	{
		unsigned int location = glGetUniformLocation(program, &str[0]);
		glUniform4f(location, UniformFloat4.r, UniformFloat4.g, UniformFloat4.b, UniformFloat4.a);
	}
	void OpenGLShader::UpladUniformFloat3(const std::string& str, const glm::vec3& UniformFloat3)
	{
		uint32_t location = glGetUniformLocation(program, str.c_str());
		glUniform3f(location, UniformFloat3.x, UniformFloat3.y, UniformFloat3.z);
	}
	void OpenGLShader::UpladUniformFloat3Array(const std::string& str, const float* pointer, size_t count)
	{
		uint32_t location = glGetUniformLocation(program, str.c_str());
		glUniform3fv(location, count, (const GLfloat*)pointer);
	}
	void OpenGLShader::UpladUniformFloat4Array(const std::string& str, const float* pointer, size_t count)
	{
		uint32_t location = glGetUniformLocation(program, str.c_str());
		glUniform4fv(location, count, (const GLfloat*)pointer);
	}
}



// #include "cnpch.h"
// 
// #include "OpenGLShader.h"
// 
// #include <Glad/glad.h>
// 
// #include <filesystem>
// 
// 
// 
// namespace Crimson {
// 
// 
// 	OpenGLShader::OpenGLShader(const std::string& filepath)
// 		: m_UniformCache(), m_RendererID(0)
// 	{
// 
// 		CN_PROFILE_FUNCTION()
// 
// 		std::filesystem::path path(filepath);
// 		m_Name = path.stem().string();
// 
// 		// Read vertexFile and fragmentFile 
// 		ShaderProgramSource shaderCode = get_file_contents(filepath);
// 
// 
// 		// Convert the shader source strings into character arrays
// 		const char* vertexSource = shaderCode.VertexSource.c_str();
// 		const char* fragmentSource = shaderCode.FragmentSource.c_str();
// 
// 
// 		// Create Vertex Shader Object and get its reference
// 		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 		// Attach Vertex Shader source to the Vertex Shader Object
// 		glShaderSource(vertexShader, 1, &vertexSource, NULL);
// 		// Compile the Vertex Shader into machine code
// 		glCompileShader(vertexShader);
// 		compileErrors(vertexShader, "Vertex");
// 
// 		// Create Fragment Shader Object and get its reference
// 		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 		// Attach Fragment Shader source to the Fragment Shader Object
// 		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
// 		// Compile the Vertex Shader into machine code
// 		glCompileShader(fragmentShader);
// 		compileErrors(fragmentShader, "Fragment");
// 
// 		// Create Shader Program Object and get its reference
// 		uint32_t program = glCreateProgram();
// 
// 		// Attach the Vertex and Fragment Shaders to the Shader Program
// 		glAttachShader(program, vertexShader);
// 		glAttachShader(program, fragmentShader);
// 
// 		glLinkProgram(program);
// 
// 		// checking for link errors
// 		compileErrors(program, "Program");
// 
// 		glValidateProgram(program);
// 
// 
// 		// Delete the now useless Vertex and Fragment Shader objects
// 		glDeleteShader(vertexShader);
// 		glDeleteShader(fragmentShader);
// 
// 		//asign if no errors / asserts evaluated
// 		m_RendererID = program;
// 
// 	}
// 
// 	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
// 		: m_UniformCache(), m_RendererID(0), m_Name(name)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		// Create an empty vertex shader handle
// 		GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
// 
// 		// Send the vertex shader source code to GL
// 		// Note that std::string's .c_str is NULL character terminated.
// 		const char *source = vertexShader.c_str();
// 		glShaderSource(vertexShaderHandle, 1, &source, 0);
// 
// 		// Compile the vertex shader
// 		glCompileShader(vertexShaderHandle);
// 
// 		GLint isCompiled = 0;
// 		glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &isCompiled);
// 		if(isCompiled == GL_FALSE)
// 		{
// 			GLint maxLength = 0;
// 			glGetShaderiv(vertexShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);
// 
// 			// The maxLength includes the NULL character
// 			std::vector<GLchar> infoLog(maxLength);
// 			glGetShaderInfoLog(vertexShaderHandle, maxLength, &maxLength, &infoLog[0]);
// 	
// 			// We don't need the shader anymore.
// 			glDeleteShader(vertexShaderHandle);
// 
// 			CN_CORE_ERROR("Error Compililing Vertex Shader!")
// 			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
// 			return;
// 		}
// 
// 		// Create an empty fragment shader handle
// 		GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
// 
// 		// Send the fragment shader source code to GL
// 		// Note that std::string's .c_str is NULL character terminated.
// 		source = fragmentShader.c_str();
// 		glShaderSource(fragmentShaderHandle, 1, &source, 0);
// 
// 		// Compile the fragment shader
// 		glCompileShader(fragmentShaderHandle);
// 
// 		glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &isCompiled);
// 		if (isCompiled == GL_FALSE)
// 		{
// 			GLint maxLength = 0;
// 			glGetShaderiv(fragmentShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);
// 
// 			// The maxLength includes the NULL character
// 			std::vector<GLchar> infoLog(maxLength);
// 			glGetShaderInfoLog(fragmentShaderHandle, maxLength, &maxLength, &infoLog[0]);
// 	
// 			// We don't need the shader anymore.
// 			glDeleteShader(fragmentShaderHandle);
// 			// Either of them. Don't leak shaders.
// 			glDeleteShader(fragmentShaderHandle);
// 
// 			CN_CORE_ERROR("Error Compililing Fragment Shader!")
// 			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
// 			return;
// 		}
// 
// 		// Vertex and fragment shaders are successfully compiled.
// 		// Now time to link them together into a program.
// 		// Get a program object.
// 		m_RendererID = glCreateProgram();
// 		uint32_t program = m_RendererID;
// 
// 		// Attach our shaders to our program
// 		glAttachShader(program, vertexShaderHandle);
// 		glAttachShader(program, fragmentShaderHandle);
// 
// 		// Link our program
// 		glLinkProgram(program);
// 
// 		// Note the different functions here: glGetProgram* instead of glGetShader*.
// 		GLint isLinked = 0;
// 		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
// 		if (isLinked == GL_FALSE)
// 		{
// 			GLint maxLength = 0;
// 			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
// 
// 			// The maxLength includes the NULL character
// 			std::vector<GLchar> infoLog(maxLength);
// 			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
// 	
// 			// We don't need the program anymore.
// 			glDeleteProgram(program);
// 			// Don't leak shaders either.
// 			glDeleteShader(vertexShaderHandle);
// 			glDeleteShader(fragmentShaderHandle);
// 
// 			CN_CORE_ERROR("Error Linking Vertex and Fragment Shader!")
// 			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
// 			return;
// 		}
// 
// 		// Always detach shaders after a successful link.
// 		glDetachShader(program, vertexShaderHandle);
// 		glDetachShader(program, fragmentShaderHandle);
// 	}
// 
// 
// 	OpenGLShader::~OpenGLShader()
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glDeleteProgram(m_RendererID);
// 	}
// 
// 	void OpenGLShader::Bind() const
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glUseProgram(m_RendererID);
// 	}
// 
// 	void OpenGLShader::Unbind() const
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		glUseProgram(0);
// 	}
// 
// 	void OpenGLShader::SetInt(const std::string& name, int val)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		UploadUniformInt(name, val);
// 
// 	}
// 
// 	void OpenGLShader::SetIntArray(const std::string& name, int* vals, uint32_t count)
// 	{
// 		UploadUniformIntArray(name, vals, count);
// 	}
// 
// 	void OpenGLShader::SetFloat(const std::string& name, const float f)
// 	{
// 		UploadUniformFloat(name, f);
// 	}
// 
// 	void OpenGLShader::SetFloat2(const std::string& name, const crm::vec2& v)
// 	{
// 		UploadUniformFloat2(name, v);
// 	}
// 
// 	void OpenGLShader::SetFloat3(const std::string& name, const crm::vec3& v)
// 	{
// 		UploadUniformFloat3(name, v);
// 	}
// 
// 	void OpenGLShader::SetFloat4(const std::string& name, const crm::vec4& v)
// 	{
// 		UploadUniformFloat4(name, v);
// 	}
// 
// 	void OpenGLShader::SetMat4(const std::string& name, const crm::mat4& m)
// 	{
// 		UploadUniformMat4(name, m);
// 	}
// 
// 	// Reads a text file and outputs a string with everything in the text file
// 	ShaderProgramSource OpenGLShader::get_file_contents(const std::string& filename)
// 	{
// 		CN_PROFILE_FUNCTION()
// 
// 		std::ifstream in(filename.c_str(), std::ios::in, std::ios::binary);
// 
// 	
// 		CN_CORE_ASSERT(in, "Failed to open filename: {0}", filename);
// 
// 		enum class ShaderType
// 		{
// 			NONE = -1, VERTEX = 0, FRAGMENT = 1
// 		};
// 
// 		// 1 for vert and 1 for frag
// 		std::stringstream ss[2];
// 
// 		ShaderType type = ShaderType::NONE;
// 
// 
// 
// 		std::string line;
// 
// 
// 		while (getline(in, line))
// 		{
// 
// 			if (line.find("#shader") != std::string::npos)
// 			{
// 				if (line.find("vertex") != std::string::npos)
// 				{
// 
// 					type = ShaderType::VERTEX;
// 				}
// 				else if (line.find("fragment") != std::string::npos)
// 				{
// 
// 					type = ShaderType::FRAGMENT;
// 
// 				}
// 			}
// 
// 			else if (type != ShaderType::NONE) {
// 				ss[(int)type] << line << "\n";
// 			}
// 		}
// 
// 		// ifstream destructor calls close
// 
// 		return { ss[0].str() , ss[1].str() };
// 
// 	}
// 
// 
// 
// 	// Checks if the different Shaders have compiled properly
// 	void OpenGLShader::compileErrors(unsigned int shader, const std::string& type)
// 	{
// 
// 		CN_PROFILE_FUNCTION()
// 
// 		// Stores status of compilation
// 		int hasCompiled;
// 
// 		// status of linking
// 		int hasLinked;
// 
// 		// Character array to store error message in
// 		char infoLog[1024];
// 		if (type != "Program")
// 		{
// 			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
// 			if (hasCompiled == GL_FALSE)
// 			{
// 				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
// 				CN_CORE_ERROR("Shader Compilation Error for {0}: {1}", type, infoLog)
// 				CN_CORE_ASSERT(false, "Shader Compilation Error")
// 			}
// 		}
// 		else
// 		{
// 			glGetProgramiv(shader, GL_LINK_STATUS, &hasLinked);
// 			if (hasLinked == GL_FALSE)
// 			{
// 				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
// 				CN_CORE_ERROR("Shader Linking Error for {0}: {1}", type, infoLog)
// 				CN_CORE_ASSERT(false, "Shader Linking Error")
// 			}
// 		}
// 	}
// 
// 	int OpenGLShader::GetUniform(const std::string& name)
// 	{
// 
// 		CN_PROFILE_FUNCTION()
// 
// 		if (m_UniformCache.find(name) != m_UniformCache.end())
// 			return m_UniformCache[name];
// 
// 		int loc = glGetUniformLocation(m_RendererID, name.c_str());
// 		if (loc == -1) {
// 			CN_CORE_ERROR("Uniform ( {0} ) does not exist!", name)
// 		}
// 		else {
// 			m_UniformCache[name] = loc;
// 		}
// 		return loc;
// 	}
// 
// 	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
// 	{
// 		glUniform1i(GetUniform(name), value);
// 	}
// 
// 	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* vals, uint32_t count)
// 	{
// 		glUniform1iv(GetUniform(name), count, vals);
// 	}
// 
// 	void OpenGLShader::UploadUniformMat4(const std::string& name, const crm::mat4& matrix)
// 	{
// 		glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, matrix.data);
// 	}
// 
// 	void OpenGLShader::UploadUniformMat3(const std::string& name, const crm::mat3& matrix)
// 	{
// 		glUniformMatrix3fv(GetUniform(name), 1, GL_FALSE, matrix.data);
// 	}
// 
// 	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) 
// 	{
// 		glUniform1f(GetUniform(name), value);
// 	}
// 
// 	void OpenGLShader::UploadUniformFloat2(const std::string& name, const crm::vec2& v) 
// 	{
// 		glUniform2f(GetUniform(name),v.x, v.y);
// 	}
// 
// 	void OpenGLShader::UploadUniformFloat3(const std::string& name, const crm::vec3& v) 
// 	{
// 		glUniform3f(GetUniform(name), v.x, v.y, v.z);
// 	}
// 
// 	void OpenGLShader::UploadUniformFloat4(const std::string& name, const crm::vec4& vec)
// 	{
// 		glUniform4f(GetUniform(name), vec.x, vec.y, vec.z, vec.w);
// 	}
// }