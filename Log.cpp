#include "Log.h"


ofstream Log::logfile ("log.txt");


void Log::write(string entry)
{
    logfile << entry << endl;
}