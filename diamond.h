

#pragma once

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


class DiamondBoard : public Board<char> {
private:

    int count_consecutive(int r, int c, int dr, int dc, char symbol);


    bool check_intersection_win(int r, int c, char symbol);

public:
    DiamondBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool game_is_over(Player<char>* player) override;

    void display_board() ;
};


class DiamondUI : public UI<char> {
public:
    DiamondUI() : UI<char>("Diamond Tic-Tac-Toe", 2) {}

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};


void launchDiamondTTT();