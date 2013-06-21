#include "VisualCard.h"



VisualCard::VisualCard(Card* card_init)
{
    card = card_init;
}


VisualCard::~VisualCard()
{
    delete front;
}


void VisualCard::render_front()
{
    front->render();
}


void VisualCard::render_back()
{
    back.set_center_x(center_x);
    back.set_center_y(center_y);
    back.set_angle(angle_ccw_rad, CCW, RADIAN);

    back->render();
}


int VisualCard::get_center_x()
{
    return center_x;
}


int VisualCard::get_center_y()
{
    return center_y;
}


double VisualCard::get_angle(AngleDirection angle_direction, AngleType angle_type)
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



void VisualCard::set_center_x(int center_x_init)
{
    center_x = center_x_init;
}


void VisualCard::set_center_y(int center_y_init)
{
    center_y = center_y_init;
}


void VisualCard::set_angle(int angle_init, AngleDirection angle_direction, AngleType angle_type)
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
}
