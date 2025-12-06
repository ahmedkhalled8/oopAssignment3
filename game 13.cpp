#include <iostream>
#include "Memory_TTT.h"
using namespace std;

Memory_TTT::Memory_TTT() {
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
            hidden[i][j] = '-';
}

void Memory_TTT::printBoard() {
    for(int i=1;i<4;i++){
        for(int j=1;j<4;j++){
            if (hidden[i][j] == '-') cout << "- ";
            else cout << "? ";
        }
        cout << endl;
    }
}

bool Memory_TTT::updateBoard(int r, int c, char p) {
    if (r<1 || r>3 || c<1 || c>3) return false;
    if (hidden[r][c] != '-') return false;

    hidden[r][c] = p;
    return true;
}

bool Memory_TTT::checkWin(char p) {
    for(int i=1;i<4;i++){
        if(hidden[i][1]==p && hidden[i][2]==p && hidden[i][3]==p) return true;
        if(hidden[1][i]==p && hidden[2][i]==p && hidden[3][i]==p) return true;
    }

    if(hidden[1][1]==p && hidden[2][2]==p && hidden[3][3]==p) return true;
    if(hidden[1][3]==p && hidden[2][2]==p && hidden[3][1]==p) return true;

    return false;
}
