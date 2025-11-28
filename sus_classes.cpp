#include "sus_classes.h"
#include <iostream>

using namespace std;

SUSGame::SUSGame(){
    board.resize(size, vector<char>(size,' '));
}

void SUSGame::displayBoard(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout << board[i][j];
            if(j!=size-1) cout << " | ";
        }
        cout << endl;
        if(i!=size-1) cout << string(size*4-3,'-') << endl;
    }
}

bool SUSGame::makeMove(int row,int col,char player){
    if(row<0 || row>=size || col<0 || col>=size || board[row][col]!=' ')
        return false;
    board[row][col]=player;
    return true;
}

int SUSGame::countSUS(char player){
    int cnt=0;

    for(int i=0;i<size;i++)
        for(int j=0;j<=size-3;j++)
            if(board[i][j]=='S' && board[i][j+1]=='U' && board[i][j+2]=='S')
                cnt++;

    for(int j=0;j<size;j++)
        for(int i=0;i<=size-3;i++)
            if(board[i][j]=='S' && board[i+1][j]=='U' && board[i+2][j]=='S')
                cnt++;
    return cnt;
}

char SUSGame::checkWinner(){
    int Xcount=countSUS('X');
    int Ocount=countSUS('O');
    if(Xcount>Ocount) return 'X';
    if(Ocount>Xcount) return 'O';
    return 'D'; // Draw
}
