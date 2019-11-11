#pragma once
#include "Core.h"
#include "Window.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include"Vulture/LayerStack.h"

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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	//To be defined in Client application
	Application* CreateApplication();
}


