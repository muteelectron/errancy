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
    virtual int stake(int min_stake) = 0;
    int blind(int value);
    void pick_card(Card* card);

private:

    Card** hand;
    std::string name;
    int cash;
};

#endif
