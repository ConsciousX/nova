#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>

class Animation
{
public:
    std::vector<std::string> animate(int speed, const std::string &init);
private:
    enum Direction
    {
        L = 'L',
        R = 'R'
    };
    struct Particle
    {
        Particle(int position, Direction direction)
            :pos(position), dir(direction)
        {}
        int pos;
        Direction dir;
    };
};

#endif


