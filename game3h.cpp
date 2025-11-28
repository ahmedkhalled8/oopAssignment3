#include "game3h.h"

game3h::game3h() {
    board.resize(size, vector<char>(size,' '));
}

void game3h::displayBoard() {
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout << board[i][j];
            if(j!=size-1) cout << " | ";
        }
        cout << endl;
        if(i!=size-1) cout << string(size*4-3,'-') << endl;
    }
}

bool game3h::makeMove(int row, int col, char player){
    if(row<0 || row>=size || col<0 || col>=size || board[row][col]!=' ')
        return false;
    board[row][col]=player;
    return true;
}

char game3h::checkWinner(){
    int Xcount = 0, Ocount = 0;

    for(int i=0;i<size;i++)
        for(int j=0;j<size-2;j++)
            if(board[i][j]=='X' && board[i][j+1]=='X' && board[i][j+2]=='X') Xcount++;
            else if(board[i][j]=='O' && board[i][j+1]=='O' && board[i][j+2]=='O') Ocount++;

    for(int j=0;j<size;j++)
        for(int i=0;i<size-2;i++)
            if(board[i][j]=='X' && board[i+1][j]=='X' && board[i+2][j]=='X') Xcount++;
            else if(board[i][j]=='O' && board[i+1][j]=='O' && board[i+2][j]=='O') Ocount++;

    for(int i=0;i<size-2;i++)
        for(int j=0;j<size-2;j++)
            if(board[i][j]=='X' && board[i+1][j+1]=='X' && board[i+2][j+2]=='X') Xcount++;
            else if(board[i][j]=='O' && board[i+1][j+1]=='O' && board[i+2][j+2]=='O') Ocount++;

    for(int i=0;i<size-2;i++)
        for(int j=2;j<size;j++)
            if(board[i][j]=='X' && board[i+1][j-1]=='X' && board[i+2][j-2]=='X') Xcount++;
            else if(board[i][j]=='O' && board[i+1][j-1]=='O' && board[i+2][j-2]=='O') Ocount++;

    if(Xcount>Ocount) return 'X';
    if(Ocount>Xcount) return 'O';
    return 'D';
}


void game3h::addObstacles() {}
