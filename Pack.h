#ifndef PACK_H
#define PACK_H

#include "Graphics.h"
#include "Card.h"
#include <deque>
#include <algorithm>

class Pack : public Graphics
{
public:

    Pack(char* image_file_name);

    void shuffle();

    Card* pop_top();
    void push_top(Card* card);
    void push_bot(Card* card);

    int get_num_of_cards();

private:

    std::deque<Card*> pack_card;
};

#endif
