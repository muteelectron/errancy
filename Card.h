#ifndef CARD_H
#define CARD_H

#include "Graphics.h"
// КОСТЫЛИ, УТЕЧКИ ПАМЯТИ И МНОГОЕ ДРУГОЕ
class Card
{
public:

    Card(Graphics* front_init, Graphics* back_init);
    ~Card();

    void render_front();
    void render_back();

    int get_center_x();
    int get_center_y();
    double get_angle(AngleDirection angle_direction, AngleType angle_type);

    void set_center_x(int center_x_init);
    void set_center_y(int center_y_init);
    void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);

private:

    Graphics* front;
    Graphics* back;

    int center_x;
    int center_y;
    int angle_ccw_rad;
};

#endif
