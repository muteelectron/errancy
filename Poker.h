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

    void OnExit();

    int num_of_seats;
    PokerPlayer** seat;
    Pack* pack;

    int user_seat;

    int closer_seat(int seat_num);
};

#endif
