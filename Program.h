#ifndef PROGRAM_H
#define PROGRAM_H

#include "ProgramState.h"

class Program : public ProgramState
{
public:

    Program();

    int start();
};

#endif