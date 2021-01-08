#pragma once

#include <string>

namespace Hovel {
	class Shader
	{
	public:
		Shader(std::string vertexSrc, std::string fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

	private:
		uint32_t m_RendererId;
	
	};

}