#include "vulpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Vulture {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}