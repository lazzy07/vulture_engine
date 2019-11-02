#pragma once
#include "Core.h"

namespace Vulture {
	class VULTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//To be defined in Client application
	Application* CreateApplication();
}


