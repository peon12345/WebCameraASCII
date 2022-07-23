#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <future>


//заполняем очередь
//говорим старт
//и шайтан машина

template <typename T>
class ThreadPool
{
public:
  ThreadPool();
  void addTask(std::packaged_task<T> task);
  std::future<T> getResult();
private:
  std::mutex m_mutex;
  std::vector<std::thread> m_threads;
  std::queue<std::packaged_task<T()>> m_tasks;
};

#endif // THREADPOOL_H
