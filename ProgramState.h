#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include "Event.h"
#include "Log.h"

class ProgramState : public Event
{

public:

    virtual bool run() = 0;
};

#endif