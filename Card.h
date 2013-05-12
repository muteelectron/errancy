#ifndef CARD_H
#define CARD_H

enum Suit{SPADES, HEARTS, DIAMONDS, CLUBS};

struct Card
{
    int val;
    Suit suit;
};

#endif