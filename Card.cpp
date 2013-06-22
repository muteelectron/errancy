#include "Card.h"

Card::Card(Graphics* front_init, Graphics* back_init)
{
    front = front_init;
    back  = back_init;
}


Card::~Card()
{

}


void Card::render_front()
{
    front->render();
}


void Card::render_back()
{
    back->set_center_x(center_x);
    back->set_center_y(center_y);
    back->set_angle(angle_ccw_rad, CCW, RADIAN);

    back->render();
}


int Card::get_center_x()
{
    return center_x;
}


int Card::get_center_y()
{
    return center_y;
}


double Card::get_angle(AngleDirection angle_direction, AngleType angle_type)
{
    double angle_return;

    if(angle_direction == CCW)
    {
        angle_return = angle_ccw_rad;
    }
    else
    {
        angle_return = (angle_ccw_rad == 0 ? 0 : 2 - angle_ccw_rad);
    }

    if(angle_type == RADIAN)
    {
        return angle_return;
    }
    else
    {
        return angle_return * 180 / M_PI;
    }
}



void Card::set_center_x(int center_x_init)
{
    center_x = center_x_init;
    front->set_center_x(center_x);
}


void Card::set_center_y(int center_y_init)
{
    center_y = center_y_init;
    front->set_center_y(center_y);
}


void Card::set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type)
{
    if(angle_init < 0)
    {
        // ERROR
    }

    if(angle_type == RADIAN)
    {
        angle_ccw_rad = angle_init;
    }
    else
    {
        angle_ccw_rad = angle_init * M_PI / 180;
    }

    angle_ccw_rad -= ((int)angle_ccw_rad / 2) * 2;

    if(angle_direction == CW)
    {
        angle_ccw_rad = (angle_ccw_rad == 0 ? 0 : 2 - angle_ccw_rad);
    }

    front->set_angle(angle_ccw_rad, CCW, RADIAN);
}
