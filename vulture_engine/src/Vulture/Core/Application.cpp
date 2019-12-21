#include "vulpch.h"
#include "Application.h"
#include "Vulture/Core/Input.h"
#include "Vulture/Renderer/Renderer.h"
#include "Vulture/Renderer/ModelLoader.h"

#include <GLFW/glfw3.h>

namespace Vulture {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		VUL_ASSERT(!s_Instance, "Application aready has a instance");
		s_Instance = this;
		m_Window = Ref<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init(m_Window);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Vulture::ModelLoader::AddNewModel("./assets/fbx/door_01.fbx");
		Vulture::ModelLoader::LoadVulModel("./assets/model/door_01.vulmodel");
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event &e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void Application::run() {
		while (m_Running) {
			//Getting Deltatime
			float time = (float)glfwGetTime(); //TODO ::: Need to be platform specific
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		};
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return false;
	}
}