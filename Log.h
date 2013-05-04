#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
using namespace std;

class Log
{
public:

    static void init();
    static void write(string entry);

private:

    static ofstream* logfile;
};

#endif