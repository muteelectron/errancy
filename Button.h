#ifndef BUTTON_H
#define BUTTON_H

#include "Graphics.h"
#include "Surface.h"
#include <fstream>
#include <cmath>

enum ButtonState{NORMAL, HOVERED, PRESSED};

class Button
{
public:

    Button(std::string file_name, void (*foo)());
    ~Button();

    bool mouse_event(int click_x, int click_y, bool clicked);

    void render();

    void set_state(ButtonState state_init);
    ButtonState get_state();

    int get_center_x();
    void set_center_x(int x_init);
    int get_center_y();
    void set_center_y(int y_init);
    double get_angle(AngleDirection angle_direction, AngleType angle_type);
    void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);

private:

    void (*action)();

    ButtonState state;

    SDL_Surface* transparency_map;
    Graphics* image;
    Graphics* image_hovered;
};

#endif
