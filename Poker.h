#ifndef POKER_H
#define POKER_H

#include "ProgramState.h"
#include "PokerPlayer.h"
#include "PokerBot.h"
#include "Pack.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include "Log.h"

class Poker : public ProgramState
{
public:

    bool run(char* template_file_name);

    void CleanUp();

private:

    bool running;
    boost::mutex running_mtx;

    void render();
    void game_loop();
    void event();

    void poker_round();
    void trade_round();

    void OnExit();

    int num_of_seats;
    int num_of_players;
    PokerPlayer** seat;
    Pack* pack;
    Card** table_card;

    int small_blind;
    int big_blind;

    int user_seat;
    int button;
    int cur_player;
    int bank;
    int highest_stake;
    int highest_stake_player;

    int closer_seat(int seat_num);
};

#endif
