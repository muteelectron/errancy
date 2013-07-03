#include "Poker.h"


Poker::Poker()
: num_of_seats(10)
{

}


bool Poker::run()
{
    Log::write("Poker::run start");

    if(std::ifstream("choosen_save.txt") != NULL)
    {
        std::ifstream path_to_save("choosen_save.txt");
        char* save_file_name;
        path_to_save >> save_file_name;

        load_game(save_file_name);
    }
    else
    {
        load_template_game();
    }

    running = true;

    boost::thread game_loop_thread(&Poker::game_loop, this);
    boost::thread event_thread(&Poker::event, this);

    render();

    game_loop_thread.join();
    event_thread.join();

    CleanUp();

    Log::write("Poker::run finish");

    return true;
}


void Poker::CleanUp()
{
    Log::write("Poker::CleanUp start");

    for(int i = 0; i < num_of_seats; ++i)
    {
        delete[] seat[i];
    }
    delete[] seat;

    delete[] pack;

    Log::write("Poker::CleanUp finish");
}


void Poker::render()
{
    Log::write("Poker::render start");

    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        for(int i = 0; i < num_of_seats; ++i)
        {
            if(seat[i] != NULL)
            {
                seat[i]->render();
            }
        }
        int i;
        i = 0;
        while(table_card[i] != NULL && i < 5)
        {
            table_card[i]->render();
        }

        running_mtx.lock();
    }
    running_mtx.unlock();

    Log::write("Poker::render finish");
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
    running_mtx.unlock();
}


void Poker::poker_round()
{
    bank = 0;

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < num_of_seats; ++j)
        {
            if(seat[j] != NULL)
            {
                seat[j]->pick_card(pack->pop_top());
            }
        }
    }

    // BLINDS
    cur_player = closer_seat(button + 1);
    seat[cur_player]->give_money(small_blind);
    cur_player = closer_seat(cur_player + 1);
    seat[cur_player]->give_money(big_blind);
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

    cur_player = closer_seat(closer_seat(closer_seat(button + 1)
                 + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // TURN
    table_card[3] = pack->pop_top();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat
                 (button + 1) + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // RIVER
    table_card[4] = pack->pop_top();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat
                 (closer_seat(button + 1) + 1) + 1) + 1) + 1);
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
            Card** folded_card;
            folded_card = seat[cur_player]->fold();
            pack->push_bot(folded_card[0]);
            pack->push_bot(folded_card[1]);
        }
        cur_player = closer_seat(cur_player + 1);
    }while(cur_player != highest_stake_player);
}


void Poker::event()
{
    Log::write("Poker::event start");

    SDL_Event event;

    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        SDL_PollEvent(&event);
        Event::OnEvent(&event);
        
        running_mtx.lock();
    }
    running_mtx.unlock();

    Log::write("Poker::event finish");
}


void Poker::save_game(char* save_file_name)
{

}


void Poker::load_game(char* load_file_name)
{
    // UNDONE
    ifstream load_file(load_file_name);

    if()
    {

    }

    bool* seat_taken;
    seat_taken = new bool[num_of_seats];

    load_file.read((char*)&user_seat, sizeof(int));

    num_of_players = 0;
    for(int i = 0; i < num_of_seats; ++i)
    {
        if(seat_taken[i])
        {
            ++num_of_players;
            if(i != user_seat)
            {
                load_file.read((char*)seat[i], sizeof(PokerBot));
            }
            else
            {
                load_file.read((char*)seat[i], sizeof(PokerPlayer));
            }
        }
        else
        {
            seat[i] = NULL;
        }
    }

    int cards_in_pack;
    Card* card_temp;
    load_file.read((char*)cards_in_pack, sizeof(int));
    for(int i = 0; i < cards_in_pack; ++i)
    {
        card_temp = new Card();
        load_file.read((char*)card_temp, sizeof(Card));
        pack->push_bot(card_temp);
    }

    load_file.read((char*)&small_blind, sizeof(int));
    load_file.read((char*)&big_blind, sizeof(int));
}


void Poker::load_template_game()
{
    num_of_players = 10;
    user_seat = 0;

    seat = new PokerPlayer*[num_of_players];

    seat[user_seat] = new PokerUser();
    seat[user_seat]->pick_cash(10000);

    for(int i = 1; i < num_of_players; ++i)
    {
        seat[i] = new PokerBot();
        seat[i]->pick_cash(10000);
    }

    pack = new Pack("card_back.graphics");

    Card* card_temp;
    Graphics* card_back;
    Graphics* card_front;
    card_front = new Graphics("card_back.graphics");
    string file_name_temp;
    file_name_temp = "X00";
    file_name_temp += ".graphics";
    for(int i = 2; i <= 14; ++i)
    {
        file_name_temp[0] = 'C';
        file_name_temp[1] = i / 10 + 48;
        file_name_temp[2] = i % 10 + 48;
        card_front = new Graphics(file_name_temp);
        card_temp = new Card(CLUBS, i, card_front, card_back);
        pack->push_bot(card_temp);
        file_name_temp[0] = 'D';
        file_name_temp[1] = i / 10 + 48;
        file_name_temp[2] = i % 10 + 48;
        card_front = new Graphics(file_name_temp);
        card_temp = new Card(DIAMONDS, i, card_front, card_back);
        pack->push_bot(card_temp);
        file_name_temp[0] = 'H';
        file_name_temp[1] = i / 10 + 48;
        file_name_temp[2] = i % 10 + 48;
        card_front = new Graphics(file_name_temp);
        card_temp = new Card(HEARTS, i, card_front, card_back);
        pack->push_bot(card_temp);
        file_name_temp[0] = 'S';
        file_name_temp[1] = i / 10 + 48;
        file_name_temp[2] = i % 10 + 48;
        card_front = new Graphics(file_name_temp);
        card_temp = new Card(SPADES, i, card_front, card_back);
        pack->push_bot(card_temp);
    }
    pack->shuffle();

    table_card = new Card*[5];
    small_blind = 2;
    big_blind = 4;
    button = 0;
}


void Poker::OnExit()
{
    Log::write("Poker::OnExit start");
    running_mtx.lock();
    running = false;
    running_mtx.unlock();
    Log::write("Poker::OnExit finish");
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
        if(i == num_of_seats)
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
