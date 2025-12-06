#ifndef FOURINAROW_H
#define FOURINAROW_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

using namespace std;

class FourInARow_Board : public Board<char> {
private:
    vector<int> col_heights;

public:
    FourInARow_Board();
    bool update_board(int x, int y, char mark) override;
    bool update_board(Move<char>* move) override;
    void display_board() override;
    bool is_winner(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool valid_col(int col) const;
    int get_row(int col) const;
};

class FourInARow_UI : public UI<char> {
public:
    FourInARow_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* setup_player() override;
    Player<char>* create_player(string name, char symbol, PlayerType type) override;
    void display_message(string message) override;
};

class FourInARow_ComputerPlayer : public Player<char> {
public:
    FourInARow_ComputerPlayer(char symbol, Board<char>* boardPtr);
    Move<char>* generate_move() override;
};

void playFourInARow();

#endif