#pragma once
#include "Vulture/Renderer/VertexArray.h"
#include "glad/glad.h"

namespace Vulture {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Vulture::ShaderDataType::Float:  return GL_FLOAT;
			case Vulture::ShaderDataType::Float2: return GL_FLOAT;
			case Vulture::ShaderDataType::Float3: return GL_FLOAT;
			case Vulture::ShaderDataType::Float4: return GL_FLOAT;
			case Vulture::ShaderDataType::Mat4:   return GL_FLOAT;
			case Vulture::ShaderDataType::Mat3:   return GL_FLOAT;
			case Vulture::ShaderDataType::Int:    return GL_INT;
			case Vulture::ShaderDataType::Int2:   return GL_INT;
			case Vulture::ShaderDataType::Int3:   return GL_INT;
			case Vulture::ShaderDataType::Int4:   return GL_INT;
			case Vulture::ShaderDataType::Bool:   return GL_BOOL;
		}
		VUL_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}