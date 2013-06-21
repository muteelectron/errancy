#ifndef POKERBOT_H
#define POKERBOT_H

#include "PokerPlayer.h"

class PokerBot : PokerPlayer
{
public:

    PokerBot();
    ~PokerBot();

    int stake(int min_stake);
    
private:

};

#endif
