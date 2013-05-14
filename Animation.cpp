#include "Animation.h"


Animation::Animation()
{
    update_interval = 1000 / fps;
    frame_amount = image->w / frame_width;
}


Animation::~Animation()
{
    SDL_FreeSurface(image);
}


void Animation::render()
{
    int current_frame_x;
    current_frame_x = ((int)((SDL_GetTicks() - start_time) / update_interval) % frame_amount) * frame_width;

    Surface::OnDraw(SDL_GetVideoSurface(), image, x, y, current_frame_x, 0, frame_width, image->h);
}