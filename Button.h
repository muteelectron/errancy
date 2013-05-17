#ifndef BUTTON_H
#define BUTTON_H

#include "Surface.h"

class Button
{
public:

    Button(void (*foo)());
    ~Button();

    bool hover(int x, int y);
    bool press(int x, int y);

    void render();

private:

    void (*action)();

    SDL_Surface* image;
    SDL_Surface* image_hovered;
    SDL_Surface* image_pressed;

    int image_x;
    int image_y;
};

#endif
