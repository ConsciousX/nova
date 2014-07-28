#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <condition_variable>
#include <assert.h>
#include "safe_queue.h"

class thread_pool;

class job
{
public:
    job()
        :priority(0), m_finished(true)
    {}

    void set_task(std::function<void(void)> task)
    {
        func = task;
    }

    void set_priority(const int val)
    {
        priority = val;
    }

    void wait_for_finished()
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (!m_finished)
        {
            condition.wait(lock);
        }
    }

    bool finished()
    {
        return m_finished;
    }
private:
    std::mutex mutex;
    std::condition_variable condition;
    int priority;
    bool m_finished;
    std::function<void(void)> func;
    friend class thread_pool;
};

class thread_pool
{
public:
    thread_pool(size_t num_of_threads)
        :thread_group(num_of_threads), m_release_pool(false)
    {
        for (auto iter=thread_group.begin(); iter != thread_group.end(); ++iter)
        {
            (*iter) = std::shared_ptr<std::thread>(new std::thread(std::bind(&thread_pool::thread_func, this)));
            thread_status[(*iter)->get_id()] = false;
            release_thread[(*iter)->get_id()] = false;
        }
    }

    int get_num_of_threads()
    {
        return thread_group.size();
    }

    int get_current_thread_index()
    {
        std::thread::id id = std::this_thread::get_id();
        for (size_t i = 0; i < thread_group.size(); ++i)
        {
            if (id == thread_group[i]->get_id())
            {
                return i;
            }
        }

        return -1;
    }

    void set_num_of_threads(size_t val)
    {
        if (val > thread_group.size())
        {
            size_t old_size = thread_group.size();
            thread_group.resize(val);
            for (auto iter=thread_group.begin() + old_size; iter != thread_group.end(); ++iter)
            {
                (*iter) = std::shared_ptr<std::thread>(new std::thread(std::bind(&thread_pool::thread_func,this)));
                thread_status[(*iter)->get_id()] = false;
                release_thread[(*iter)->get_id()] = false;
            }
        }
        else if (val < thread_group.size())
        {
            for (auto iter = thread_group.begin() + val; iter != thread_group.end(); ++iter)
            {
                release_thread[(*iter)->get_id()] = true;
                (*iter)->join();
            }
            thread_group.resize(val);
        }
    }

    void add_job(job& func)
    {
        func.m_finished = false;
        job_queue.push(&func);
        condition.notify_all();
    }

    void wait_for_finished()
    {
    }

    bool idle()
    {
        for(auto iter = thread_status.begin(); iter != thread_status.end(); ++iter)
        {
            if (iter->second) return false;
        }
        return true;
    }

    ~thread_pool()
    {
        //Handle the case when some job is still processing in the queue but not throw exception
        if(!job_queue.empty())
        {
            assert(0);
        }
        //End all the threads
        m_release_pool = true;
        condition.notify_all();
        for (auto iter = thread_group.begin(); iter != thread_group.end(); ++iter)
        {
            (*iter)->join();
        }
    }
private:
   void thread_func()
   {
        job* current_job;
        while (true)
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (job_queue.empty())
                {
                    if (release_thread[std::this_thread::get_id()]) return;

                    thread_status[std::this_thread::get_id()] = false;
                    condition.wait(lock);
                    thread_status[std::this_thread::get_id()] = true;
                    if (m_release_pool)
                    {
                        return;
                    }
                }

                current_job = job_queue.front();
                job_queue.pop();
            }

            //run current job
            current_job->func();

            {
                std::lock_guard<std::mutex> lock(current_job->mutex);
                current_job->m_finished = true;
                current_job->condition.notify_one();
            }
        }
    }
private:
    std::mutex mutex;
    std::condition_variable condition;
    std::vector<std::shared_ptr<std::thread>> thread_group;
    std::map<std::thread::id, bool> release_thread;
    std::map<std::thread::id, bool> thread_status;
    bool m_release_pool;
    safe_queue<job*> job_queue;
};

