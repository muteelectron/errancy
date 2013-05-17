#ifndef POKER_H
#define POKER_H

#include "ProgramState.h"
#include "Pack.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Log.h"

class Poker : public ProgramState
{
public:

    bool run();

private:

    bool running;

    void render();
    void update();
    void game_loop();
    void event();

    void OnExit();

    Pack* pack;
};

#endif
