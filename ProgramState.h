#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include "Log.h"

class ProgramState
{
public:

    virtual bool run() = 0;
};

#endif