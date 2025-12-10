#include <iostream>
#include "memoryTicTacToe.h"
using namespace std;

memoryTicTacToe::memoryTicTacToe() {
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
            hidden[i][j] = '-';
}

void memoryTicTacToe::printBoard() {
    for(int i=1;i<4;i++){
        for(int j=1;j<4;j++){
            if (hidden[i][j] == '-') cout << "- ";
            else cout << "? ";
        }
        cout << endl;
    }
}

bool memoryTicTacToe::updateBoard(int r, int c, char p) {
    if (r<1 || r>3 || c<1 || c>3) return false;
    if (hidden[r][c] != '-') return false;

    hidden[r][c] = p;
    return true;
}

bool memoryTicTacToe::checkWin(char p) {
    for(int i=1;i<4;i++){
        if(hidden[i][1]==p && hidden[i][2]==p && hidden[i][3]==p) return true;
        if(hidden[1][i]==p && hidden[2][i]==p && hidden[3][i]==p) return true;
    }

    if(hidden[1][1]==p && hidden[2][2]==p && hidden[3][3]==p) return true;
    if(hidden[1][3]==p && hidden[2][2]==p && hidden[3][1]==p) return true;

    return false;
}

void launchMemory()   { 
    cout << "\nStarting Memory Tic-Tac-Toe...\n";

    memoryTicTacToe game;
    char player = 'X';
    int r, c;

    while (true) {
        game.printBoard();
        cout << "\nPlayer " << player << " turn.\n";

        cout << "Enter row (1-3): ";
        cin >> r;
        cout << "Enter column (1-3): ";
        cin >> c;

        if (!game.updateBoard(r, c, player)) {
            cout << "Invalid move, try again!\n";
            continue;
        }

        if (game.checkWin(player)) {
            cout << "\nPlayer " << player << " WINS!!\n";
            break;
        }

        player = (player == 'X' ? 'O' : 'X');
    }

    cin.ignore(1000, '\n');
 }
