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
    int stake();
    void pick_card();

private:

    Card** hand;
    std::string name;
    int cash;
};

#endif