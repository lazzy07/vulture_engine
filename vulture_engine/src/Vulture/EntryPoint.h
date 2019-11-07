#pragma once

#ifdef VUL_PLATFORM_WINDOWS

extern Vulture::Application* Vulture::CreateApplication();

int main(int argc, char** argv) {
	Vulture::Log::Init();
	VUL_CORE_WARN("Log initialization complete");
	VUL_INFO("Client initialization complete");
	auto app = Vulture::CreateApplication();
	app->run();
	delete app;
}
#endif