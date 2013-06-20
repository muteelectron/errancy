#include "Poker.h"


bool Poker::run(char* template_file_name)
{
    std::ifstream input(template_file_name);

    table_card = new Card*[5];

    running = true;

    boost::thread render_thread(&Poker::render, this);
    boost::thread game_loop_thread(&Poker::game_loop, this);
    boost::thread event_thread(&Poker::event, this);

    render_thread.join();
    game_loop_thread.join();
    event_thread.join();



    return true;
}


void Poker::CleanUp()
{
    for(int i = 0; i < seat_amount; ++i)
    {
        delete[] seat[i];
    }
    delete[] seat;

    delete[] pack;
}


void Poker::render()
{
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        running_mtx.lock();
    }
}


void Poker::game_loop()
{
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        while(num_of_players > 1)
        {
            poker_round();
        }

        running_mtx.lock();
    }
}


void Poker::poker_round()
{
    trade_round();
    table_card[0] = pack->pop_top();
    table_card[1] = pack->pop_top();
    table_card[2] = pack->pop_top();
    trade_round();
    table_card[3] = pack->pop_top();
    trade_round();
    table_card[4] = pack->pop_top();
    trade_round();
}


void Poker::trade_round()
{

}


void Poker::event()
{
    SDL_Event event;
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        SDL_PollEvent(&event);
        Event::OnEvent(&event);
        running_mtx.lock();
    }
}


void Poker::OnExit()
{
    running_mtx.lock();
    running = false;
    running_mtx.unlock();
}


int Poker::closer::seat(int seat_num)
{
    if(seat[seat_num] != NULL)
    {
        return seat_num;
    }

    int i;
    i = seat_num;

    do
    {
        ++i;
        if(i == seat_amount)
        {
            i = 0;
        }
    }while(seat[i] == NULL && i != seat_num);
    if(seat[i] != NULL)
    {
        return i;
    }
    else
    {
        // ERROR: THERE AREN'T ANY PLAYERS
    }
}
