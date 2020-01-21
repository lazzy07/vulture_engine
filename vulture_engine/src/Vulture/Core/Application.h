#pragma once
#include "Core.h"
#include "Window.h"

#include "Vulture/Events/Event.h"
#include "Vulture/Events/ApplicationEvent.h"
#include"Vulture/Core/LayerStack.h"

#include "Vulture/Core/Timestep.h"

#include "Vulture/ImGui/ImGuiLayer.h"
#include "Vulture/Renderer/ModelLibrary.h"
#include "Vulture/Core/Level.h"

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

		static inline Application& Get() { return *s_Instance; };

		void LoadDefaultLevel();

		inline Ref<Level> GetCurrentLevel() const { return m_CurrentLevel; };
		inline void SetCurrentLevel(Ref<Level> level) { m_CurrentLevel = level; };

		inline Window& GetWindow() { return *m_Window; };
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		Ref<Level> m_CurrentLevel;
		float m_LastFrameTime = 0.0f;
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	//To be defined in Client application
	Application* CreateApplication();
}


