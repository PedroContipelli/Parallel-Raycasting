#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class concurrent_queue {
	public:
		concurrent_queue() : ending(false) {};

		void enq(T item) {
			std::unique_lock<std::mutex> l (lock);
			
			q.emplace(std::move(item));
			cV.notify_one();
		}

		T deq() {
			std::unique_lock<std::mutex> l (lock);

			while (!ending && q.empty())
				cV.wait(l);

			if (q.empty())
			{
				empty.notify_one();
				return NULL;
			}
			
			T item = std::move(q.front());
			q.pop();

			if (q.empty()) empty.notify_one();

			return item;
		}

		void waitUntilEmpty()
		{
			std::unique_lock<std::mutex> l (lock);
			if (!q.empty()) empty.wait(l);
		}

		void end()
		{
			std::unique_lock<std::mutex> l (lock);

			ending = true;
			cV.notify_all();
		}

	private:
		std::queue<T> q;
		std::mutex lock;
		std::condition_variable cV;
		std::condition_variable empty;
		bool ending;
		
};

#endif
