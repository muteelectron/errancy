#include "Pack.h"


Pack::Pack(char* file_name)
: Graphics(file_name)
{

}


void Pack::shuffle()
{
    std::random_shuffle(pack_card.begin(), pack_card.end());
}


Card* Pack::pop_top()
{
    Card* temp;
    temp = pack_card.front();
    pack_card.pop_front();
    return temp;
}


void Pack::push_top(Card* card)
{
    pack_card.push_front(card);
}


void Pack::push_bot(Card* card)
{
    pack_card.push_back(card);
}


int Pack::get_num_of_cards()
{
    return pack_card.size();
}
