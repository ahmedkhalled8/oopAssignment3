

#ifndef pyramid_H
#define pyramid_H

#include <string>


class pyramid {
private:
    char board[3][5]; 

public:

    pyramid();

    void printBoard();

  
    void runGame();

private:
 
    bool place(int userRow, int userCol, char p);

 
    bool validCell(int userRow, int userCol) const;

 
    bool checkWin(char p) const;

    bool aiMove(char aiSymbol);
};
void launchPyramid();
#endif
