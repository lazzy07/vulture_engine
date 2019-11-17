#include "vulpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Vulture {
	Shader* Shader::Create(const std::string& filePath) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filePath);
		};
		VUL_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader("example", vertexSrc, fragmentSrc);
		};
		VUL_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}
}