#ifndef ANIMATION_H
#define ANIMATION_H

#include "Surface.h"

class Animation
{
public:

    Animation();
    ~Animation();

    void render();

private:

    SDL_Surface* image;

    double fps;
    double update_interval;
    const int frame_width;
    const int frame_amount;

    int x;
    int y;

    const unsigned int start_time;
};

#endif