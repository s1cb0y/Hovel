#include "hvpch.h"
#include "Shader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
namespace HOVEL {


}


Hovel::Shader::Shader(std::string vertexSrc, std::string fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		HV_CORE_ERROR("{0}", infoLog.data());
		HV_ASSERT(false, "Failed to compile vertex shader!");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		HV_CORE_ERROR("{0}", infoLog.data());
		HV_ASSERT(false, "Failed to compile fragment shader!");
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererId = glCreateProgram();
	GLuint program = m_RendererId;

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

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
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		HV_CORE_ERROR("{0}", infoLog.data());
		HV_ASSERT(false, "Shader link failure!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

}

Hovel::Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

void Hovel::Shader::Bind()
{
	glUseProgram(m_RendererId);
}

void Hovel::Shader::Unbind()
{
	glUseProgram(0);
}

void Hovel::Shader::UploadUniform(const std::string& name, const glm::mat4& matrix)
{
	GLint MatrixID = glGetUniformLocation(m_RendererId, name.c_str());
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(matrix));
}
