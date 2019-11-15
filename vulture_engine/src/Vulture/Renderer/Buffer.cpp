#include "vulpch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Vulture {
	VertexBuffer * VertexBuffer::Create(float * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		};
		VUL_CORE_ASSERT(false, "RendererAPI unknown choice");
		return nullptr;
	}




	IndexBuffer * IndexBuffer::Create(uint32_t * indecies, uint32_t size)
	{
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indecies, size);
		};
		VUL_CORE_ASSERT(false, "RendererAPI unknown choice");
		return nullptr;
	}
}