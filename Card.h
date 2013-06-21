#ifndef CARD_H
#define CARD_H

enum Suit{CLUBS, DIAMONDS, HEARTS, SPADES};

struct Card
{
    int val;
    Suit suit;
};

#endif
