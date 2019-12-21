#include "vulpch.h"
#include "ModelLibrary.h"

namespace Vulture {
	ModelLibrary::ModelLibrary()
	{

	}
	void ModelLibrary::AddModel(const std::string & name, Ref<Model>& model)
	{
		VUL_CORE_ASSERT(!Exists(name), "Shader Already exists");
		m_ModelCollection[name] = model;
	}

	void ModelLibrary::RemoveModel(const std::string & name)
	{
	}

	Ref<Model> ModelLibrary::GetModel(const std::string & name)
	{
		VUL_CORE_ASSERT(Exists(name), "Shader couln't be found");
		return m_ModelCollection[name];
	}

	bool ModelLibrary::Exists(const std::string & name)
	{
		return m_ModelCollection.find(name) != m_ModelCollection.end();
	}
}