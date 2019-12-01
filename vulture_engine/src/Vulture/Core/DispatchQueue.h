#pragma once
#include <thread>
#include <queue>
#include <mutex>

namespace Vulture {
	class DispatchQueue {
		typedef std::function<void(void)> fp_t;
	public:
		DispatchQueue(std::string name, size_t thread_cnt = 1);
		~DispatchQueue();

		void Dispatch(const fp_t& op);
		void Dispatch(fp_t&& op);

		DispatchQueue(const DispatchQueue& rhs) = delete;
		DispatchQueue& operator=(const DispatchQueue& rhs) = delete;
		DispatchQueue(DispatchQueue&& rhs) = delete;
		DispatchQueue& operator=(DispatchQueue&& rhs) = delete;

	private:
		std::string m_Name;
		std::mutex m_Lock;
		std::vector<std::thread> m_Threads;
		std::queue<fp_t> m_Queue;
		std::condition_variable m_Cv;
		bool m_Quit = false;

		void DispatchThreadHandler(void);
	};
}