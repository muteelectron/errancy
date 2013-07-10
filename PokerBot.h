#ifndef POKERBOT_H
#define POKERBOT_H

#include "PokerPlayer.h"

class PokerBot : public PokerPlayer
{
public:

    PokerBot(std::string file_name);
    ~PokerBot();

    int stake(int min_stake);
    
private:

};

#endif
