#pragma once

#include <string>
#include "glm/glm.hpp"
namespace Hovel {
	class Shader
	{
	public:
		Shader(std::string vertexSrc, std::string fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

		void UploadUniform(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererId;
	
	};

}