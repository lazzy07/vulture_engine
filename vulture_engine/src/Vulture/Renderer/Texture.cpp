#include "vulpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Vulture {
	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			VUL_CORE_ASSERT(false, "Renderer API Currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			VUL_CORE_TRACE("Texture 2d: OpenGL added : {0}", path);
			return std::make_shared<OpenGLTexture2D>(path);
		};
		VUL_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}
}
