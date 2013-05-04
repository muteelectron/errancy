#ifndef PROGRAM_H
#define PROGRAM_H

#include "SDL.h"
#include "ProgramState.h"

class Program : public ProgramState
{
public:

    int start();

private:

    int init();
};

#endif