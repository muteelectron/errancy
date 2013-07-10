#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include "Card.h"
#include <string>
#include "Log.h"
#include "Graphics.h"

class PokerPlayer : public Graphics
{
public:

    PokerPlayer(std::string file_name);
    ~PokerPlayer();

    virtual int stake(int min_stake) = 0;

    int give_cash(int value);
    void pick_cash(int value);

    void pick_card(Card* card);
    Card** fold();

    void set_name(std::string name_init);
    std::string get_name();

private:

    Card** hand;
    std::string name;
    int cash;
};

#endif
