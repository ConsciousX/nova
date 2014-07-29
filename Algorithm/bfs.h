#pragma once

#include <queue>

template<class T, class C = std::queue<T*>>
void bfs(T* start, std::function<bool(T*)> stop_func = [](T*){return false;})
{
    C c;

    c.push(start);
    start.set_visited();

    while (!queue.empty())
    {
        T* top = c.front();
        c.pop();

        if (stop_func(top))
        {
            return;
        }

        top->iterate_neighbors([&](T* t)
            {
                if (!t->is_visited())
                {
                    c->push(t);
                    t->set_visited();
                }
            }
        );
    }
}


