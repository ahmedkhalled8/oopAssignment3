#ifndef GAME10H_H
#define GAME10H_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class game10h : public BoardGame {
private:
    vector<vector<char>> board;
    int size;
    int movesInRound;

public:
    game10h();
    void displayBoard() override;
    bool makeMove(int row, int col, char player) override;
    char checkWinner() override;
    void addObstacles() override;
};

#endif
