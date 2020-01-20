#include "vulpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Vulture {
	Ref<Shader> Shader::Create(const std::string& filePath) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			VUL_CORE_TRACE("Shader with OpenGL loaded : {0}", filePath);
			return std::make_shared<OpenGLShader>(filePath);
		};
		VUL_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		};
		VUL_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}
}