#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <thread>
#include "concurrent_queue.h"

class thread_pool {

	public:

		thread_pool(int n) {
			threads.reserve(n);
			for (int i = 0; i < n; ++i)
				threads.emplace_back(std::bind(&thread_pool::work, this, i));
			ended = false;
		};

		~thread_pool() {
			end();
		}

		void add(std::function<void()> task)
		{
			task_queue.enq(task);
		}

		void endWhenEmpty()
		{	
			task_queue.waitUntilEmpty();
			end();
		} 

		void end()
		{
			if (ended) return;

			ended = true;
			task_queue.end();

			for (auto& t : threads)
				t.join();
		}
		
	private:
		std::vector<std::thread> threads;
		concurrent_queue<std::function<void()>> task_queue;
		bool ended;

		void work(int i)
		{
			std::function<void()> task;

			while(true)
			{
				task = task_queue.deq();
				if (task == NULL)
					return;
				task();
			}
		}
};

#endif
