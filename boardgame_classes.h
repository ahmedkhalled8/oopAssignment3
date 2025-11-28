#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <vector>
#include <iostream>
using namespace std;

class BoardGame {
public:
    virtual void displayBoard() = 0;
    virtual bool makeMove(int row, int col, char player) = 0;
    virtual char checkWinner() = 0;
    virtual void addObstacles() = 0;
    virtual ~BoardGame() = default;
};

#endif
