#include "vulpch.h"
#include "ModelLibrary.h"

namespace Vulture {
	ModelLibrary::ModelLibrary()
	{

	}

	void ModelLibrary::AddModel(const std::string & name, Ref<Model>& model)
	{
		VUL_CORE_ASSERT(!Exists(name), "Model Already exists");
		m_ModelCollection[name] = model;
		m_Config.SetString("models", name, name);
	}

	void ModelLibrary::RemoveModel(const std::string & name)
	{
		m_ModelCollection.erase(name);
		m_Config.RemoveEntry("models", name);
	}

	Ref<Model> ModelLibrary::GetModel(const std::string & name)
	{
		if (!Exists(name)) {
			VUL_CORE_WARN("Model couln't be found : {0}", name);
			return nullptr;
		}
		return m_ModelCollection[name];
	}

	bool ModelLibrary::Exists(const std::string & name)
	{
		return m_ModelCollection.find(name) != m_ModelCollection.end();
	}

	std::string ModelLibrary::ModelsToConfigBuffer()
	{
		return m_Config.GetConfigBuffer();
	}
}