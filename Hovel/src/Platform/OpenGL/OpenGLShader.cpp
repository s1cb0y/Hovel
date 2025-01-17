#include "hvpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
namespace Hovel {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		HV_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string & filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
		// Extract shader name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string s;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		HV_CORE_ASSERT(in, "Could not open shader file {0}", filepath);
		in.seekg(0, std::ios::end);
		s.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&s[0], s.size());
		in.close();

		return s;
	}
		
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			// Check if any shader code is present
			size_t eol = source.find_first_of("\r\n", pos);
			HV_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			// Determine type
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			HV_CORE_ASSERT(ShaderTypeFromString(type), "Unknown shader type specified");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;			   		
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		
		GLuint program = glCreateProgram();
		HV_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 different shaders!");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;
			GLuint shader = glCreateShader(type);

			const GLchar *sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				HV_CORE_ERROR("{0}", infoLog.data());
				HV_ASSERT(false, "Failed to compile shader!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.			

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
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			HV_CORE_ERROR("{0}", infoLog.data());
			HV_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}

		m_RendererId = program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string & name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string & name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string & name, const glm::vec2 & value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	
	
}