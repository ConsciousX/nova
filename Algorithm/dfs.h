#pragma once

#include <stack>

template<class T, class C = std::stack<T*>>
void dfs(T* start, std::function<bool(T*)> stop_func = [](T*)->bool{return false;})
{
    C c;
    c.push(start);

    while (!c.empty())
    {
        T* top = stack.top();
        c.pop();

        if (!top->is_visited())
        {
            if (stop_func(top))
            {
                return;
            }

            top->set_visited();
            top->iterate_neighbors([&](T* t){c.push(t);});
        }
    }
}
