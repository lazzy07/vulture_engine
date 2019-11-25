#pragma once

#ifdef VUL_USE_GPU
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

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