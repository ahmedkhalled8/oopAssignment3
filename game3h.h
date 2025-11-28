#ifndef GAME3H_H
#define GAME3H_H

#include "boardgame_classes.h"
#include <vector>
#include <iostream>
using namespace std;

class game3h : public BoardGame {
private:
    int size = 5;
    vector<vector<char>> board;

public:
    game3h();
    void displayBoard() override;
    bool makeMove(int row, int col, char player) override;
    char checkWinner() override;
    void addObstacles() override;
};

#endif
