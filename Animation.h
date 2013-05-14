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
    int fps;
    int frame_width;
    int current_frame;
};

#endif