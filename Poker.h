#ifndef POKER_H
#define POKER_H

#include "ProgramState.h"
#include "PokerPlayer.h"
#include "PokerBot.h"
#include "Pack.h"
#include "Graphics.h"
#include "Card.h"
#include <boost/thread.hpp>
#include <fstream>
#include "Log.h"

class Poker : public ProgramState
{
public:

    bool run();

    void CleanUp();

private:

    bool running;
    boost::mutex running_mtx;

    void render();
    void game_loop();
    void event();

    void poker_round();
    void trade_round();

    void save_game(char* save_file_name);
    void load_game(char* load_file_name);

    void OnExit();

    const int num_of_seats;
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
