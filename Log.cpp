#include "Log.h"

void Log::init()
{
    logfile = new ofstream("log.txt");
}


void Log::write(string entry)
{
    logfile << entry << endl;
}