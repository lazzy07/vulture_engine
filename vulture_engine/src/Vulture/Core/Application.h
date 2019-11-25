#pragma once
#include "Core.h"
#include "Window.h"

#include "Vulture/Events/Event.h"
#include "Vulture/Events/ApplicationEvent.h"
#include"Vulture/Core/LayerStack.h"

#include "Vulture/Core/Timestep.h"

#include "Vulture/ImGui/ImGuiLayer.h"

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

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; };
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		float m_LastFrameTime = 0.0f;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	//To be defined in Client application
	Application* CreateApplication();
}


