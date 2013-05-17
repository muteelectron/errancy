#ifndef ANIMATION_H
#define ANIMATION_H

#include "Surface.h"
#include "Image.h"

class AnimatedImage : public Image
{
public:

    AnimatedImage();
    ~AnimatedImage();

    void render();

private:

    SDL_Surface* image;
    SDL_Surface* target;

    double fps;
    double update_interval_ms;
    int frame_width;
    int frame_amount;

    int x;
    int y;

    unsigned int start_time;
};

#endif