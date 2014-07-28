#pragma once

#include <queue>
#include <mutex>
#include <queue>

//thread safe queue adaptor
template<typename T>
class safe_queue
{
public:
    void push(const T t)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(t);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.pop();
    }

    const T& front()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.front();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
private:
    std::mutex mutex;
    std::queue<T> queue;
};

