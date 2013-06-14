#ifndef BUTTON_H
#define BUTTON_H

#include "Graphics.h"

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

    Graphics* image;
    Graphics* image_hovered;
    Graphics* image_pressed;

    int image_x;
    int image_y;
};

#endif
