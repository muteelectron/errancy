#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include "Card.h"
#include <string>
#include "Log.h"

class PokerPlayer
{
public:

    PokerPlayer();
    ~PokerPlayer();
    Card** fold();
    int stake(int value);
    void pick_card(Card* card);

private:

    Card** hand;
    std::string name;
    int cash;
};

#endif
