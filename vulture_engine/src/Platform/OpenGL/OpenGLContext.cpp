#include "vulpch.h"
#include "OpenGLContext.h"

namespace Vulture {
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle) : m_WindowHandle(windowHandle)
	{
		VUL_CORE_ASSERT(windowHandle, "WindowHandle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VUL_CORE_ASSERT(status, "Failed to initialize Glad");

		VUL_CORE_INFO("::::OpenGL Info::::");
		VUL_CORE_INFO("  GPU Vendor     : {0}", glGetString(GL_VENDOR));
		VUL_CORE_INFO("  GPU Renderer   : {0}", glGetString(GL_RENDERER));
		VUL_CORE_INFO("  OpenGL Version : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}