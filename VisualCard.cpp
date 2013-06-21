#include "VisualCard.h"

Graphics back("card_back.graphics");

VisualCard::VisualCard(Card* card_init)
{
    card = card_init;
    char suit;
    char value;
    switch(card->suit)
    {
        case CLUBS:
            suit = 'C';
            break;
        case DIAMONDS:
            suit = 'D';
            break;
        case HEARTS:
            suit = 'H';
            break;
        case SPADES:
            suit = 'S';
            break;
    }
    value = (char)card->val + 48;
// ПЕРЕДЕЛАТЬ ЭТО БЕЗОБРАЗИЕ
    char file_name[11];
    file_name[0] = suit;
    file_name[1] = value;
    file_name[2] = '.';
    file_name[3] = 'g';
    file_name[4] = 'r';
    file_name[5] = 'a';
    file_name[6] = 'p';
    file_name[7] = 'h';
    file_name[8] = 'i';
    file_name[9] = 'c';
    file_name[10] = 's';

    front = new Graphics(file_name);
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

    back.render();
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
    front->set_center_x(center_x);
}


void VisualCard::set_center_y(int center_y_init)
{
    center_y = center_y_init;
    front->set_center_y(center_y);
}


void VisualCard::set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type)
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
