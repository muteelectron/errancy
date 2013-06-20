#include "PokerPlayer.h"

PokerPlayer::PokerPlayer()
{
    hand = new Card*[2];
    hand[0] = NULL;
    hand[1] = NULL;
}


PokerPlayer::~PokerPlayer()
{
    delete[] hand;
}


Card** PokerPlayer::fold()
{
    return hand;
}


int PokerPlayer::stake(int min_stake)
{
    if(min_stake >= cash)
    {
        int rest_money;
        rest_money = cash;
        cash = 0;
        //ALL IN
        return rest_money;
    }
    else
    {
        cash -= min_stake;
        return min_stake;
    }
}


void PokerPlayer::pick_card(Card* card)
{
    if(hand[0] == NULL)
    {
        hand[0] = card;
    }
    else if(hand[1] == NULL)
    {
        hand[1] = card;
    }
    else
    {
        Log::write("");
    }
}
