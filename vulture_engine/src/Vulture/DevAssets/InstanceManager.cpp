#include "vulpch.h"
#include "InstanceManager.h"

#include "Outliner.h"
#include "Vulture/Core/Application.h"
#include "imgui.h"

namespace Vulture {
	InstanceManager::InstanceManager() : Layer("InstanceManager")
	{

	}

	InstanceManager::~InstanceManager()
	{

	}

	void InstanceManager::OnAttach()
	{

	}

	void InstanceManager::OnDetach()
	{

	}

	void InstanceManager::OnImGuiRender()
	{
		SetCurrentInstance();

		
	}

	void InstanceManager::SetCurrentInstance()
	{
		std::string selected = Outliner::GetSelectedInstance();

		if (selected != "") {
			Ref<Level> level = Application::Get().GetCurrentLevel();
			auto instances = level->GetInstanceData();

			for (auto elem : *instances) {
				if(selected == elem.second->Id)
					m_CurrentInstance = elem.second;
			}
		}
	}
}
