#include "game10h.h"
#include <iostream>
#include <iomanip>

game10h::game10h() {
    size = 6;
    board.resize(size, vector<char>(size,' '));
    movesInRound = 0;
    srand(time(0));
}

void game10h::displayBoard() {
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout << board[i][j];
            if(j!=size-1) cout << " | ";
        }
        cout << endl;
        if(i!=size-1) cout << string(size*4-3,'-') << endl;
    }
}

bool game10h::makeMove(int row, int col, char player) {
    if(row<0 || row>=size || col<0 || col>=size || board[row][col]!=' ')
        return false;
    board[row][col]=player;
    movesInRound++;
    return true;
}

char game10h::checkWinner() {
    for(int i=0;i<size;i++)
        for(int j=0;j<size-3;j++){
            char c = board[i][j];
            if(c!=' ' && c==board[i][j+1] && c==board[i][j+2] && c==board[i][j+3])
                return c;
        }
    for(int j=0;j<size;j++)
        for(int i=0;i<size-3;i++){
            char c = board[i][j];
            if(c!=' ' && c==board[i+1][j] && c==board[i+2][j] && c==board[i+3][j])
                return c;
        }
    for(int i=0;i<size-3;i++)
        for(int j=0;j<size-3;j++){
            char c = board[i][j];
            if(c!=' ' && c==board[i+1][j+1] && c==board[i+2][j+2] && c==board[i+3][j+3])
                return c;
        }
    for(int i=0;i<size-3;i++)
        for(int j=3;j<size;j++){
            char c = board[i][j];
            if(c!=' ' && c==board[i+1][j-1] && c==board[i+2][j-2] && c==board[i+3][j-3])
                return c;
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(board[i][j]==' ')
                return ' ';
    return 'D';
}

void game10h::addObstacles() {
    int added = 0;
    while(added<2){
        int r = rand()%size;
        int c = rand()%size;
        if(board[r][c]==' '){
            board[r][c]='#';
            added++;
        }
    }
    movesInRound = 0;
}
