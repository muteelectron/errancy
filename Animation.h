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
    int frame_width;
    int frame_amount;

    int x;
    int y;

    unsigned int start_time;
};

#endif