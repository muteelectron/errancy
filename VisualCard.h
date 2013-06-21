#ifndef VISUALCARD_H
#define VISUALCARD_H

#include "Card.h"
#include "Graphics.h"

class VisualCard
{
public:

    VisualCard(Card* card_init);
    ~VisualCard();

    render();

private:

    Card* card;

    Graphics front;
    static Graphics back;
};

#endif
