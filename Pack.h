#ifndef PACK_H
#define PACK_H

#include "Card.h"
#include <deque>
#include <algorithm>

class Pack
{
public: 
    
    void shuffle();

    Card* pop_top();
    void push_top(Card* card);
    void push_bot(Card* card);

private:

    std::deque<Card*> pack_card;
};

#endif
