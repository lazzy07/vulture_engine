#pragma once
#include "Core.h"
#include "Window.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"

namespace Vulture {
	class VULTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
	};

	//To be defined in Client application
	Application* CreateApplication();
}


