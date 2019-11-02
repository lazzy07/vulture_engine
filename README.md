![Vulture Logo](https://github.com/lazzy07/vulture_engine/blob/master/dependencies/logo/export/logo_with_text.png)

# Vulture Engine

### Created by @lazzy07

Vulture game engine version 0.1 alpha

#### To start the engine,

```cpp
class Sandbox : public Vulture::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Vulture::Application* Vulture::CreateApplication() {
	return new Sandbox();
}
```
