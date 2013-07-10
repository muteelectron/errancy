#include "PokerBot.h"

PokerBot::PokerBot(std::string file_name)
: PokerPlayer(file_name)
{

}


PokerBot::~PokerBot()
{

}



int PokerBot::stake(int min_stake)
{
    return min_stake;
}
