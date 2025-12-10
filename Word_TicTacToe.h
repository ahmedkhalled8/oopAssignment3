#ifndef WORD_TICTACTOE_H
#define WORD_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

class WordMove : public Move<char> {
public:
    WordMove(int x, int y, char symbol) : Move<char>(x, y, symbol) {}
};

class WordPlayer : public Player<char> {
public:
    WordPlayer(string name, char symbol, PlayerType type)
        : Player<char>(name, symbol, type) {}
};

class WordBoard : public Board<char> {
private:
    set<string> dictionary;
    bool is_valid_word(const string& w) const;
public:
    WordBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void load_dictionary();
    bool check_any_word() const;
};

class WordUI : public UI<char> {
public:
    WordUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
  
    void display_board_matrix(const vector<vector<char>>& matrix) const;
};

void playWordTicTacToe();
void launchWordTTT();
#endif