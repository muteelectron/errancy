#ifndef POKERUSER_H
#define POKERUSER_H

#include "PokerPlayer.h"

class PokerUser : public PokerPlayer
{
public:

    PokerUser(std::string file_name);

    int stake(int min_stake);

private:
};

#endif