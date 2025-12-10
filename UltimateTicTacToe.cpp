#include "UltimateTicTacToe.h"
#include <iostream>
using namespace std;

UltimateTTT::UltimateTTT() {
    for(int b=0;b<9;b++){
        big[b]='-';
        for(int r=0;r<3;r++)
            for(int c=0;c<3;c++)
                boards[b][r][c]='-';
    }
}


void UltimateTTT::print() {
    cout<<endl;
    cout << "\nBoards:\n";
    cout << "1 2 3\n4 5 6\n7 8 9\n\n";
    for(int blockRow=0;blockRow<3;blockRow++){
        for(int r=0;r<3;r++){
            for(int blockCol=0;blockCol<3;blockCol++){
                int b=blockRow*3+blockCol;
                if(big[b]=='X'){
                    if(r==0) cout<<"\\   / ";
                    if(r==1) cout<<"  X   ";
                    if(r==2) cout<<"/   \\ ";
                }
                else if(big[b]=='O'){
                    if(r==0) cout<<"/---\\ ";
                    if(r==1) cout<<"| O | ";
                    if(r==2) cout<<"\\---/ ";
                }
                else{
                    for(int c=0;c<3;c++)
                        cout<<boards[b][r][c]<<" ";
                }
                cout<<"   ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

bool UltimateTTT::playMove(int b,int r,int c,char p){
    if(big[b]!='-') return false;
    if(boards[b][r][c]!='-') return false;
    boards[b][r][c]=p;
    return true;
}

char UltimateTTT::checkMini(int b){
    char (*bd)[3]=boards[b];
    for(int i=0;i<3;i++){
        if(bd[i][0]!='-'&&bd[i][0]==bd[i][1]&&bd[i][1]==bd[i][2]) return bd[i][0];
        if(bd[0][i]!='-'&&bd[0][i]==bd[1][i]&&bd[1][i]==bd[2][i]) return bd[0][i];
    }
    if(bd[0][0]!='-'&&bd[0][0]==bd[1][1]&&bd[1][1]==bd[2][2]) return bd[0][0];
    if(bd[0][2]!='-'&&bd[0][2]==bd[1][1]&&bd[1][1]==bd[2][0]) return bd[0][2];
    return '-';
}

void UltimateTTT::markBig(int b,char p){
    big[b]=p;
}

char UltimateTTT::checkBig(){
    for(int i=0;i<3;i++){
        if(big[i*3]!='-'&&big[i*3]==big[i*3+1]&&big[i*3+1]==big[i*3+2]) return big[i*3];
        if(big[i]!='-'&&big[i]==big[i+3]&&big[i+3]==big[i+6]) return big[i];
    }
    if(big[0]!='-'&&big[0]==big[4]&&big[4]==big[8]) return big[0];
    if(big[2]!='-'&&big[2]==big[4]&&big[4]==big[6]) return big[2];
    return '-';
}



void launchUltimate() { 
     UltimateTTT game;
    char player = 'X';

    cout << "\nStarting Ultimate Tic Tac Toe...\n";

    while (true) {
        game.print();

        int b, r, c;

        cout << "Player " << player << " choose board (1-9): ";
        if (!(cin >> b) || b < 1 || b > 9) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid board.\n";
            continue;
        }
        b--;

        cout << "Row (1-3): ";
        if (!(cin >> r) || r < 1 || r > 3) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid row.\n";
            continue;
        }

        cout << "Column (1-3): ";
        if (!(cin >> c) || c < 1 || c > 3) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid column.\n";
            continue;
        }

        if (!game.playMove(b, r-1, c-1, player)) {
            cout << "Invalid move.\n";
            continue;
        }

        char miniWinner = game.checkMini(b);
        if (miniWinner != '-') {
            game.markBig(b, miniWinner);
        }

        char bigWinner = game.checkBig();
        if (bigWinner != '-') {
            game.print();
            cout << "\nPLAYER " << bigWinner << " WINS THE ULTIMATE GAME!\n";
            break;
        }

        player = (player == 'X' ? 'O' : 'X');
    }

    cin.ignore(1000, '\n');
}