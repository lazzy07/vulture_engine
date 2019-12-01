#pragma once
#include "DispatchQueue.h"

namespace Vulture {
	typedef std::function<void(void)> fp_t;

	class TaskManager {
	public:
		static void Dispatch(fp_t func);

	private:
		static unsigned int m_NoOfThreads;
		static DispatchQueue m_DispatchQueue;
	};
}