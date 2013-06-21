#ifndef VISUALCARD_H
#define VISUALCARD_H

#include "Card.h"
#include "Graphics.h"

class VisualCard : public Graphics
{
public:

    VisualCard(Card* card_init);
    ~VisualCard();

    static init_graphics();

    render_front();

    int get_center_x();
    int get_center_y();
    int get_angle();

    void set_center_x(int center_x_init);
    void set_center_y(int center_y_init);

private:

    Card* card;

    static Graphics*** front;
    static Graphics* back;
};

#endif
