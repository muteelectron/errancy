#ifndef BUTTON_H
#define BUTTON_H

#include "Graphics.h"
#include "Surface.h"
#include <fstream>

enum ButtonState{NORMAL, HOVERED, PRESSED};

class Button
{
public:

    Button(char* file_name, void (*foo)());
    ~Button();

    bool hover(int x, int y);
    bool press(int x, int y);

    void render();

private:

    void (*action)();

    ButtonState button_state;

    SDL_Surface* transparrency_map;
    Graphics* image;
    Graphics* image_hovered;

    int image_x;
    int image_y;
};

#endif
