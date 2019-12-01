#include "vulpch.h"
#include "DispatchQueue.h"

namespace Vulture {
	DispatchQueue::DispatchQueue(std::string name, size_t thread_cnt):
		m_Name{ std::move(name) }, m_Threads(thread_cnt)
	{
		for (size_t i = 0; i < m_Threads.size(); i++)
		{
			m_Threads[i] = std::thread(&DispatchQueue::DispatchThreadHandler, this);
		}
	}

	DispatchQueue::~DispatchQueue()
	{
		std::unique_lock<std::mutex> lock(m_Lock);
		m_Quit = true;
		lock.unlock();
		m_Cv.notify_all();

		// Wait for threads to finish before we exit
		for (size_t i = 0; i < m_Threads.size(); i++)
		{
			if (m_Threads[i].joinable())
			{
				m_Threads[i].join();
			}
		}
	}

	void DispatchQueue::Dispatch(const fp_t & op)
	{
		std::unique_lock<std::mutex> lock(m_Lock);
		m_Queue.push(op);
		lock.unlock();
		m_Cv.notify_all();
	}

	void DispatchQueue::Dispatch(fp_t && op)
	{
		std::unique_lock<std::mutex> lock(m_Lock);
		m_Queue.push(std::move(op));
		lock.unlock();
		m_Cv.notify_all();
	}

	void DispatchQueue::DispatchThreadHandler(void)
	{
		std::unique_lock<std::mutex> lock(m_Lock);

		do {
			m_Cv.wait(lock, [this] {
				return (m_Queue.size() || m_Quit);
			});

			if (!m_Quit && m_Queue.size())
			{
				auto op = std::move(m_Queue.front());
				m_Queue.pop();
				lock.unlock();
				op();
				lock.lock();
			}
		} while (!m_Quit);
	}
}