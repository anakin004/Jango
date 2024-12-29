#include "cnpch.h"

#include "OpenGLShader.h"

#include <Glad/glad.h>

#include <filesystem>



namespace Crimson {


	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_UniformCache(), m_RendererID(0)
	{
		std::filesystem::path path(filepath);
		m_Name = path.stem().string();

		// Read vertexFile and fragmentFile 
		ShaderProgramSource shaderCode = get_file_contents(filepath);


		// Convert the shader source strings into character arrays
		const char* vertexSource = shaderCode.VertexSource.c_str();
		const char* fragmentSource = shaderCode.FragmentSource.c_str();


		// Create Vertex Shader Object and get its reference
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// Attach Vertex Shader source to the Vertex Shader Object
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(vertexShader);
		compileErrors(vertexShader, "Vertex");

		// Create Fragment Shader Object and get its reference
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach Fragment Shader source to the Fragment Shader Object
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "Fragment");

		// Create Shader Program Object and get its reference
		uint32_t program = glCreateProgram();

		// Attach the Vertex and Fragment Shaders to the Shader Program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		// checking for link errors
		compileErrors(program, "Program");

		glValidateProgram(program);


		// Delete the now useless Vertex and Fragment Shader objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//asign if no errors / asserts evaluated
		m_RendererID = program;

	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
		: m_UniformCache(), m_RendererID(0), m_Name(name)
	{

		// Create an empty vertex shader handle
		GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char *source = vertexShader.c_str();
		glShaderSource(vertexShaderHandle, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShaderHandle);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShaderHandle, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			glDeleteShader(vertexShaderHandle);

			CN_CORE_ERROR("Error Compililing Vertex Shader!")
			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentShader.c_str();
		glShaderSource(fragmentShaderHandle, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShaderHandle);

		glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShaderHandle, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			glDeleteShader(fragmentShaderHandle);
			// Either of them. Don't leak shaders.
			glDeleteShader(fragmentShaderHandle);

			CN_CORE_ERROR("Error Compililing Fragment Shader!")
			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		uint32_t program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShaderHandle);
		glAttachShader(program, fragmentShaderHandle);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShaderHandle);
			glDeleteShader(fragmentShaderHandle);

			CN_CORE_ERROR("Error Linking Vertex and Fragment Shader!")
			CN_CORE_ASSERT(false, "Error: {0}", &infoLog[0])
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShaderHandle);
		glDetachShader(program, fragmentShaderHandle);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const crm::vec3& v)
	{
		UploadUniformFloat3(name, v);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const crm::vec4& v)
	{
		UploadUniformFloat4(name, v);
	}

	void OpenGLShader::SetMat4(const std::string& name, const crm::mat4& m)
	{
		UploadUniformMat4(name, m);
	}

	// Reads a text file and outputs a string with everything in the text file
	ShaderProgramSource OpenGLShader::get_file_contents(const std::string& filename)
	{
		std::ifstream in(filename.c_str(), std::ios::in, std::ios::binary);

	
		CN_CORE_ASSERT(in, "Failed to open filename: {0}", filename);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		// 1 for vert and 1 for frag
		std::stringstream ss[2];

		ShaderType type = ShaderType::NONE;



		std::string line;


		while (getline(in, line))
		{

			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{

					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{

					type = ShaderType::FRAGMENT;

				}
			}

			else if (type != ShaderType::NONE) {
				ss[(int)type] << line << "\n";
			}
		}

		// ifstream destructor calls close

		return { ss[0].str() , ss[1].str() };

	}



	// Checks if the different Shaders have compiled properly
	void OpenGLShader::compileErrors(unsigned int shader, const std::string& type)
	{
		// Stores status of compilation
		int hasCompiled;

		// status of linking
		int hasLinked;

		// Character array to store error message in
		char infoLog[1024];
		if (type != "Program")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				CN_CORE_ERROR("Shader Compilation Error for {0}: {1}", type, infoLog)
				CN_CORE_ASSERT(false, "Shader Compilation Error")
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasLinked);
			if (hasLinked == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				CN_CORE_ERROR("Shader Linking Error for {0}: {1}", type, infoLog)
				CN_CORE_ASSERT(false, "Shader Linking Error")
			}
		}
	}

	int OpenGLShader::GetUniform(const std::string& name)
	{
		if (m_UniformCache.find(name) != m_UniformCache.end())
			return m_UniformCache[name];

		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc == -1) {
			CN_CORE_ERROR("Uniform ( {0} ) does not exist!", name)
		}
		else {
			m_UniformCache[name] = loc;
		}
		return loc;
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniform(name), value);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const crm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, matrix.data);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const crm::mat3& matrix)
	{
		glUniformMatrix3fv(GetUniform(name), 1, GL_FALSE, matrix.data);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) 
	{
		glUniform1f(GetUniform(name), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const crm::vec2& v) 
	{
		glUniform2f(GetUniform(name),v.x, v.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const crm::vec3& v) 
	{
		glUniform3f(GetUniform(name), v.x, v.y, v.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const crm::vec4& vec)
	{
		glUniform4f(GetUniform(name), vec.x, vec.y, vec.z, vec.w);
	}
}