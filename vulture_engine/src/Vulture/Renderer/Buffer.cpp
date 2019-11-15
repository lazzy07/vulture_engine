#include "vulpch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Vulture {
	VertexBuffer * VertexBuffer::Create(float * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		};
		VUL_CORE_ASSERT(false, "RendererAPI unknown choice");
		return nullptr;
	}




	IndexBuffer * IndexBuffer::Create(uint32_t * indecies, uint32_t size)
	{
		switch (RendererAPI::OpenGL) {
		case RendererAPI::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indecies, size);
		};
		VUL_CORE_ASSERT(false, "RendererAPI unknown choice");
		return nullptr;
	}
}