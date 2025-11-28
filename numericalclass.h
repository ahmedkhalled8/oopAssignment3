#pragma once
#ifndef NUMERICAL_CLASSES_H
#define NUMERICAL_CLASSES_H

#include "boardgameclass.h"
#include <vector>
using namespace std;

enum class Difficulty { EASY, MEDIUM, HARD };

class NumericalBoard : public Board<int> {
private:
    vector<int> used_numbers;
public:
    NumericalBoard();
    bool update_board(Move<int>* move);
    bool is_win(Player<int>* player);
    bool is_lose(Player<int>* player) { return false; }
    bool is_draw(Player<int>* player);
    bool game_is_over(Player<int>* player);

    vector<int> get_used_numbers() const;
};

template<typename T>
class NumericalPlayer : public Player<T> {
private:
    Difficulty difficulty;
public:
    NumericalPlayer(string name, T symbol, PlayerType type, Difficulty diff = Difficulty::EASY)
        : Player<T>(name, symbol, type), difficulty(diff) {}

    Difficulty get_difficulty() const { return difficulty; }
};

class NumericalUI : public UI<int> {
public:
    NumericalUI();

    Player<int>* create_player(string& name, int symbol, PlayerType type);
    Move<int>* get_move(Player<int>* player);
    Player<int>** setup_players();

    void display_board_matrix(const vector<vector<int>>& matrix) const;
    void show_winner(const string& winner_name);

    void print_colored(string text, string color) const;
    void display_available_numbers(const vector<int>& available_nums, char player_symbol);
    Move<int>* get_computer_move(Player<int>* player, NumericalBoard* board_ptr, Difficulty diff);
};

vector<int> get_available_numbers(const vector<int>& used_numbers, char symbol);
bool check_win_condition(const vector<vector<int>>& board);

#endif