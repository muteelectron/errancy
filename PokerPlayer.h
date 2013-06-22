#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include "VisualCard.h"
#include <string>
#include "Log.h"

class PokerPlayer
{
public:

    PokerPlayer();
    ~PokerPlayer();

    void render();

    virtual int stake(int min_stake) = 0;
    int blind(int value);

    void pick_card(Card* card);
    VisualCard** fold();

private:

    VisualCard** hand;
    std::string name;
    int cash;
};

#endif
