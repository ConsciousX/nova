#include <list>
#include "Animation.h"

using namespace std;

vector<string> Animation::animate(int speed, const string &init)
{
    vector<string> result;
    list<Particle> particles;
    result.push_back(init);

    size_t size = init.length();
    if (size == 0)
    {
        return result;
    }

    //Scan the init string
    for (size_t i = 0; i < size; ++i)
    {
        if (init[i] == 'L')
        {
            particles.emplace_back(i, L);
        }
        else if (init[i] == 'R')
        {
            particles.emplace_back(i, R);
        }
    }

    //Loop
    while (!particles.empty())
    {
        string temp(size, '.');
        //update each particle
        auto iter = particles.begin();
        while (iter != particles.end())
        {
            iter->dir == L ? iter->pos -= speed : iter->pos += speed;
            if (iter->pos < 0 || iter->pos >= int(size))
            {
                iter = particles.erase(iter);
                continue;
            }

            temp[iter->pos] = iter->dir == L ? 'L' : 'R';
            ++iter;
        }

        result.push_back(temp);
    }

    return result;
}
        
