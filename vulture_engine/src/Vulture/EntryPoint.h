#pragma once

#ifdef VUL_PLATFORM_WINDOWS

extern Vulture::Application* Vulture::CreateApplication();

int main(int argc, char** argv) {
	auto app = Vulture::CreateApplication();
	app->run();
	delete app;
}
#endif