#include "PokerPlayer.h"

PokerPlayer::PokerPlayer()
{
    name = "Unknown";
    
    cash = 0;

    hand = new Card*[2];
    hand[0] = NULL;
    hand[1] = NULL;
}


PokerPlayer::~PokerPlayer()
{
    delete[] hand;
}


void PokerPlayer::render()
 {

 }


int PokerPlayer::give_cash(int value)
{
    if(value >= cash)
    {
        // ALL IN
        int rest_money;
        rest_money = cash;
        cash = 0;
        return rest_money;
    }
    else
    {
        cash -= value;
        return value;
    }
}


void PokerPlayer::pick_cash(int value)
{
    cash += value;
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


Card** PokerPlayer::fold()
{
    return hand;
}


void PokerPlayer::set_name(std::string name_init)
{
    name = name_init;
}


std::string PokerPlayer::get_name()
{
    return name;
}
