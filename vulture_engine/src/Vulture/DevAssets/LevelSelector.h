#pragma once
#include "imgui.h"
#include "Vulture/Core/Layer.h"

namespace Vulture {
	class LevelSelector : public Layer {
	public:
		LevelSelector();
		~LevelSelector() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void AddNewLevel(std::string levelName);
		std::string getFileName(const std::string path);
	private:
		void SetLevelFiles();
		char* Convert(const std::string & s);
	private:
		int m_CurrentLevel = 0;
		std::vector<std::string> m_LevelNames;
	};
}
