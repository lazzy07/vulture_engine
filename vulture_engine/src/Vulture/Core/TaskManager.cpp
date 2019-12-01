#include "vulpch.h"
#include <thread>
#include "TaskManager.h"

namespace Vulture {
	unsigned int TaskManager::m_NoOfThreads = std::thread::hardware_concurrency();
	DispatchQueue TaskManager::m_DispatchQueue = DispatchQueue("Task Manager", TaskManager::m_NoOfThreads);

	void TaskManager::Dispatch(fp_t func)
	{
		m_DispatchQueue.Dispatch(func);
	}
}
