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
            button = closer_seat(button + 1);
        }

        running_mtx.lock();
    }
}


void Poker::poker_round()
{
    bank = 0;

    cur_player = closer_seat(button + 1);
    seat[cur_player]->blind(small_blind);
    cur_player = closer_seat(cur_player + 1);
    seat[cur_player]->blind(big_blind);
// УТОЧНИТЬ: ОСТАЛЬНЫЕ ПОВЫШАЮТ ДО БОЛЬШОГО БЛАИНДА ИЛИ ОЛ-ИНА ИГРОКА С БОЛЬШИМ БЛАИНДОМ
    highest_stake = big_blind;
    highest_stake_player = cur_player;
    cur_player = closer_seat(cur_player + 1);
    // PREFLOP
    trade_round();
    if(highest_stake == big_blind)
    {
        highest_stake_player = closer_seat(cur_player + 1);
        trade_round();
    }

    // FLOP
    table_card[0] = pack->pop_top();
    table_card[1] = pack->pop_top();
    table_card[2] = pack->pop_top();

    cur_player = closer_seat(closer_seat(closer_seat(button + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // TURN
    table_card[3] = pack->pop_top();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat(button + 1) + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // RIVER
    table_card[4] = pack->pop_top();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat(closer_seat(button + 1) + 1) + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();
}


void Poker::trade_round()
{
    int stake;

    do
    {
        stake = seat[cur_player]->stake(highest_stake);
        bank += stake;
        if(stake == 0)
        {
            // CHECK
        }
        else if(stake > 0 && highest_stake == 0)
        {
            // BET
            highest_stake = stake;
            highest_stake_player = cur_player;
        }
        else if(stake > 0 && highest_stake > 0)
        {
            // RAISE
            highest_stake = stake;
            highest_stake_player = cur_player;
        }
        else if(highest_stake > 0 && stake < highest_stake)
        {
            // ALL IN
        }
        else if(stake == highest_stake)
        {
            // CALL
        }
        else if(stake == -1)
        {
            // FOLD
            Card* folded_card[2];
            folded_card = seat[cur_player]->fold();
            pack->push_bot(folded_card[0]);
            pack->push_bot(folded_card[1]);
        }
        cur_player = closer_seat(cur_player + 1);
    }while(cur_player != highest_stake_player);
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


int Poker::closer_seat(int seat_num)
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
