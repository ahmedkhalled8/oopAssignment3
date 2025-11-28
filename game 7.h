#pragma once
#ifndef FOURBYFOUR_CLASSES_H
#define FOURBYFOUR_CLASSES_H

#include <vector>
#include <utility>

class FourByFourBoard {
private:
    std::vector<std::vector<char>> board;
    std::vector<std::pair<int, int>> xPositions;
    std::vector<std::pair<int, int>> oPositions;
    int moveCount;

public:
    FourByFourBoard();
    void display();
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol, char player);
    bool isGameOver(char currentPlayer);

private:
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, char player);
    bool hasThreeInRow(char player);
};

#endif