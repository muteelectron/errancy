#include "AnimatedImage.h"


AnimatedImage::AnimatedImage()
{
    update_interval_ms = 1000 / fps;
    frame_amount = image->w / frame_width;
}


AnimatedImage::~AnimatedImage()
{
    SDL_FreeSurface(image);
}


void AnimatedImage::render()
{
    int current_frame_x;
    current_frame_x = ((int)((SDL_GetTicks() - start_time) / update_interval_ms) % frame_amount) * frame_width;

    Surface::OnDraw(target, image, x, y, current_frame_x, 0, frame_width, image->h);
}