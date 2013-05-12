#ifndef POKER_H
#define POKER_H

#include "ProgramState.h"
#include "Pack.h"

class Poker : public ProgramState
{
public:

    bool run();

private:

    Pack* pack;

    void OnExit();
};

#endif