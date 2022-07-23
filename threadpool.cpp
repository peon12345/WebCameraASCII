#include "threadpool.h"


template<typename T>
ThreadPool<T>::ThreadPool()
{
  m_threads.reserve(std::thread::hardware_concurrency());
}

template<typename T>
void ThreadPool<T>::addTask(std::packaged_task<T> task)
{
  m_tasks.push(task);
}
