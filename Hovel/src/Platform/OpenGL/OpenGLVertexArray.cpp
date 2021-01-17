#include "hvpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"
namespace Hovel {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Hovel::ShaderDataType::Float:	return GL_FLOAT;
		case Hovel::ShaderDataType::Float2:	return GL_FLOAT;
		case Hovel::ShaderDataType::Float3:	return GL_FLOAT;
		case Hovel::ShaderDataType::Float4:	return GL_FLOAT;
		case Hovel::ShaderDataType::Int:    return GL_INT;
		case Hovel::ShaderDataType::Int2:   return GL_INT;
		case Hovel::ShaderDataType::Int3:   return GL_INT;
		case Hovel::ShaderDataType::Int4:	return GL_INT;
		case Hovel::ShaderDataType::Mat3:	return GL_FLOAT;
		case Hovel::ShaderDataType::Mat4:	return GL_FLOAT;
		case Hovel::ShaderDataType::Bool:	return GL_BOOL;
		}
		HV_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() 
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HV_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "No buffer layout specified");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}
		
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>> OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}