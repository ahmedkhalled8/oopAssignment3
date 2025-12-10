
#ifndef TIC4X4_H
#define TIC4X4_H

#include <string>
#include <vector>

class Tic4x4 {
public:
    char board[4][4];   
    char turn;          

   
    Tic4x4();

    void printBoard();


    void runGame();

private:

    struct Move { int r1, c1, r2, c2; };

    Move readMove();

    bool validMove(const Move& m, char player) const;

   
    void applyMove(const Move& m);

    bool checkWin(char s) const;

    std::vector<Move> genMoves(char player) const;

   
    Move aiChooseMove(char aiSymbol);
};
void launchMovingTTT();


#endif

