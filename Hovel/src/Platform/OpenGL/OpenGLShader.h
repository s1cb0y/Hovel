#pragma once

#include "Hovel/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Hovel {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformFloat4(const std::string& name, const glm::vec4& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);

	private:
		uint32_t m_RendererId;

	};

}