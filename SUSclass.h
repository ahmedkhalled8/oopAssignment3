#pragma once
#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include <vector>
#include <string>

class SUSBoard {
private:
    std::vector<std::vector<char>> board;
    int xScore;
    int oScore;

public:
    SUSBoard();
    void display();
    bool makeMove(int row, int col, char player, char letter);
    bool isBoardFull();
    void declareWinner();

private:
    void updateScores(char player);
    int countSUS(const std::string& sequence);
};

#endif