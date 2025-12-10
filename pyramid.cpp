#include "pyramid.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

 pyramid::pyramid() {
    for(int r=0;r<3;r++) for(int c=0;c<5;c++) board[r][c]='-';
    srand(static_cast<unsigned int>(time(0)));
}

void pyramid::printBoard() {
    cout << "    " << board[0][2] << "\n";
    cout << "  " << board[1][1] << " " << board[1][2] << " " << board[1][3] << "\n";
    cout << board[2][0] << " " << board[2][1] << " " << board[2][2] << " " << board[2][3] << " " << board[2][4] << "\n";
}

bool pyramid::validCell(int userRow,int userCol) const {
    if(userRow<1||userRow>3) return false;
    if(userRow==1) return userCol==1;
    if(userRow==2) return userCol>=1 && userCol<=3;
    return userCol>=1 && userCol<=5;
}

bool pyramid::place(int userRow,int userCol,char p) {
    if(!validCell(userRow,userCol)) return false;
    int ri = userRow-1;
    int ci = (userRow==1?2:(userRow==2?userCol: userCol-1));
    if(board[ri][ci] != '-') return false;
    board[ri][ci] = p;
    return true;
}

bool pyramid::checkWin(char p) const {
    if(board[1][1]==p && board[1][2]==p && board[1][3]==p) return true;
    if(board[2][0]==p && board[2][1]==p && board[2][2]==p) return true;
    if(board[2][1]==p && board[2][2]==p && board[2][3]==p) return true;
    if(board[2][2]==p && board[2][3]==p && board[2][4]==p) return true;
    if(board[0][2]==p && board[1][2]==p && board[2][2]==p) return true;
    if(board[0][2]==p && board[1][1]==p && board[2][0]==p) return true;
    if(board[0][2]==p && board[1][3]==p && board[2][4]==p) return true;
    return false;
}

bool pyramid::aiMove(char aiSymbol) {
    char opp = (aiSymbol=='X'?'O':'X');
    for(int r=1;r<=3;r++){
        int maxc = (r==1?1:(r==2?3:5));
        for(int c=1;c<=maxc;c++){
            if(!validCell(r,c)) continue;
            int ri=r-1, ci=(r==1?2:(r==2?c:c-1));
            if(board[ri][ci] != '-') continue;
            board[ri][ci]=aiSymbol;
            if(checkWin(aiSymbol)) return true;
            board[ri][ci]='-';
        }
    }
    for(int r=1;r<=3;r++){
        int maxc = (r==1?1:(r==2?3:5));
        for(int c=1;c<=maxc;c++){
            int ri=r-1, ci=(r==1?2:(r==2?c:c-1));
            if(board[ri][ci] != '-') continue;
            board[ri][ci]=opp;
            if(checkWin(opp)){ board[ri][ci]=aiSymbol; return true; }
            board[ri][ci]='-';
        }
    }
    int bestR= -1, bestC = -1, bestScore=-1000;
    for(int r=1;r<=3;r++){
        int maxc = (r==1?1:(r==2?3:5));
        for(int c=1;c<=maxc;c++){
            int ri=r-1, ci=(r==1?2:(r==2?c:c-1));
            if(board[ri][ci] != '-') continue;
            int score=0;
            board[ri][ci]=aiSymbol;
            for(int rr=0;rr<3;rr++) for(int cc=0;cc<5;cc++){
                if(board[rr][cc]==aiSymbol){
                    int cnt=0, emptyc=0;
                    if(rr==1 && cc>=1 && cc<=3){ if(board[1][1]==aiSymbol) cnt++; if(board[1][2]=='-') emptyc++; }
                }
            }
            board[ri][ci]='-';
            if(score>bestScore){ bestScore=score; bestR=r; bestC=c; }
        }
    }
    if(bestR!=-1) return place(bestR,bestC,aiSymbol);
    for(int r=1;r<=3;r++){
        int maxc = (r==1?1:(r==2?3:5));
        for(int c=1;c<=maxc;c++){
            if(place(r,c,aiSymbol)) return true;
        }
    }
    return false;
}

void pyramid::runGame() {
    string name1;
    cout << "Enter name for Player 1 (X): ";
    getline(cin>>ws, name1);
    cout << "Choose Player 2 type:\n1. Human\n2. Computer (AI)\nEnter choice: ";
    int choice; cin >> choice;
    string name2; bool p2isAI=false;
    if(choice==1){ cout<<"Enter name for Player 2 (O): "; getline(cin>>ws, name2); } else { name2="Computer AI"; p2isAI=true; }
    char player='X';
    while(true){
        printBoard();
        cout << "\nPlayer " << player << " turn.\n";
        if(player=='X'){
            int r,c;
            cout << "Enter row (1..3): ";
            if(!(cin>>r)){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Bad input\n"; continue; }
            int maxc = (r==1?1:(r==2?3:5));
            cout << "Enter column (1.." << maxc << "): ";
            if(!(cin>>c)){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Bad input\n"; continue; }
            if(!place(r,c,player)){ cout<<"Invalid move\n"; continue; }
            if(checkWin(player)){ printBoard(); cout<<"\nPlayer "<<player<<" WINS!\n"; break; }
            player='O';
        } else {
            if(p2isAI){
                if(!aiMove('O')){ cout<<"AI cannot move\n"; break; }
                if(checkWin('O')){ printBoard(); cout<<"\nPlayer O (Computer AI) WINS!\n"; break; }
                player='X';
            } else {
                int r,c;
                cout << "Enter row (1..3): ";
                if(!(cin>>r)){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Bad input\n"; continue; }
                int maxc = (r==1?1:(r==2?3:5));
                cout << "Enter column (1.." << maxc << "): ";
                if(!(cin>>c)){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Bad input\n"; continue; }
                if(!place(r,c,player)){ cout<<"Invalid move\n"; continue; }
                if(checkWin(player)){ printBoard(); cout<<"\nPlayer "<<player<<" WINS!\n"; break; }
                player='X';
            }
        }
    }
}

void launchPyramid()  { 
    cout << "\nStarting Pyramid Tic-Tac-Toe...\n";
    pyramid game;
    game.runGame();
    cin.ignore(1000, '\n');
}
