#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include <vector>
#include <string>
#include "boardgame_classes.h"

class SUSGame : public BoardGame {
public:
    SUSGame();
    void displayBoard() override;
    bool makeMove(int row, int col, char player) override;
    char checkWinner() override;

private:
    std::vector<std::vector<char>> board;
    int size = 3;
    int countSUS(char player);
};

#endif
