#ifndef CARD_H
#define CARD_H

#include "Graphics.h"

// КОСТЫЛИ, УТЕЧКИ ПАМЯТИ И МНОГОЕ ДРУГОЕ

enum CardSuit{CLUBS, DIAMONDS, HEARTS, SPADES};

class Card
{
public:

    Card(CardSuit suit_init, int value_init, Graphics* front_init, Graphics* back_init);
    ~Card();

    void render();

    CardSuit get_suit();
    int get_value();

    bool get_opened();

    int get_center_x();
    int get_center_y();
    double get_angle(AngleDirection angle_direction, AngleType angle_type);

    void set_opened(bool opened_init);

    void set_center_x(int center_x_init);
    void set_center_y(int center_y_init);
    void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);

private:

    bool opened;

    Graphics* front;
    Graphics* back;

    int center_x;
    int center_y;
    int angle_ccw_rad;

    const CardSuit suit;
    const int value;
};

#endif
