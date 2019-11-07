#pragma once
#include "Core.h"
#include "Window.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include"Vulture/LayerStack.h"

namespace Vulture {
	class VULTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};

	//To be defined in Client application
	Application* CreateApplication();
}


