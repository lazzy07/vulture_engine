#pragma once

#include <unordered_map>
#include "Model.h"

namespace Vulture {
	class ModelLibrary {
	public:
		ModelLibrary();
		~ModelLibrary() = default;

		void AddModel(const std::string & name, Ref<Model>& model);
		void RemoveModel(const std::string & name);
		Ref<Model> GetModel(const std::string & name);
		bool Exists(const std::string & name);

		std::string ModelsToConfigBuffer();
	private:
		Configurations m_Config;
		std::unordered_map<std::string, Ref<Model>> m_ModelCollection;
	};
}