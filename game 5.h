#pragma once

#ifndef MISERE_CLASSES_H
#define MISERE_CLASSES_H

#include <vector>

class MisereBoard {
private:
    std::vector<std::vector<char>> board;
    int moveCount;

public:
    MisereBoard();
    void display();
    bool makeMove(int row, int col, char symbol);
    bool isGameOver(char currentPlayer);

private:
    bool hasThreeInRow(char symbol);
};

#endif