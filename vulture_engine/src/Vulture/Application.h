#pragma once
#include "Core.h"
#include "Window.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include"Vulture/LayerStack.h"

#include "Vulture/ImGui/ImGuiLayer.h"
#include "Vulture/Renderer/Shader.h"
#include "Vulture/Renderer/VertexArray.h"
#include "Vulture/Renderer/Buffer.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

	//To be defined in Client application
	Application* CreateApplication();
}


