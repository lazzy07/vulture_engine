#pragma once
#include "Vulture/Renderer/VertexArray.h"

namespace Vulture {
	enum class RendererAPI {
		None=0, OpenGL=1
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; };
	private:
		static RendererAPI s_RendererAPI;
	};
}