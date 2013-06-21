#ifndef VISUALCARD_H
#define VISUALCARD_H

#include "Card.h"
#include "Graphics.h"

class VisualCard : public Graphics
{
public:

    VisualCard(Card* card_init);
    ~VisualCard();

    render_front();
    render_back();

    int get_center_x();
    int get_center_y();
    double get_angle(AngleDirection angle_direction, AngleType angle_type);

    void set_center_x(int center_x_init);
    void set_center_y(int center_y_init);
    void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);

private:

    Card* card;

    Graphics* front;
    static Graphics* back;

    int center_x;
    int center_y;
    int angle_ccw_rad;
};

#endif
