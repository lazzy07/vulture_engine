
#pragma once

#include "Vulture/Core/Layer.h"

#include "Vulture/Events/ApplicationEvent.h"
#include "Vulture/Events/KeyEvent.h"
#include "Vulture/Events/MouseEvent.h"

namespace Vulture {

	class VULTURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}