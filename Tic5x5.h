#pragma once

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TicTacToe5x5Board : public Board<char> {
private:
    int p1_score = 0; 
    int p2_score = 0; 

    bool check_three(int r, int c, int dr, int dc, char symbol);
    
public:
    TicTacToe5x5Board();
    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool game_is_over(Player<char>* player) override { return is_draw(player); }

    void display_board() ; 
 
    void update_score(char symbol, int row, int col);
    
    int get_score(char symbol) const {
        return (symbol == 'X' ? p1_score : p2_score);
    }
};

class TicTacToe5x5UI : public UI<char> {
public:
    TicTacToe5x5UI() : UI<char>("5x5 Tic-Tac-Toe (Most 3-in-a-Row)", 2) {}

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

void launchTicTacToe5x5();