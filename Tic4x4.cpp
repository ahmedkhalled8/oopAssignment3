#include "Tic4x4.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;

Tic4x4::Tic4x4() {
    char init[4][4] = {
        {'O','X','O','X'},
        {' ',' ',' ',' '},
        {' ',' ',' ',' '},
        {'X','O','X','O'}
    };
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) board[i][j]=init[i][j];
    turn='X';
    srand(static_cast<unsigned int>(time(0)));
}

void Tic4x4::printBoard() {
    cout << "\n  0 1 2 3\n";
    for(int i=0;i<4;i++){
        cout << i << " ";
        for(int j=0;j<4;j++){
            cout << board[i][j];
            if(j<3) cout << "|";
        }
        cout << "\n";
    }
}

Tic4x4::Move Tic4x4::readMove() {
    Move m;
    cout << "Enter from (r c): ";
    while(!(cin>>m.r1>>m.c1)){ cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout<<"Bad input\n"; cout<<"Enter from (r c): "; }
    cout << "Enter to (r c): ";
    while(!(cin>>m.r2>>m.c2)){ cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout<<"Bad input\n"; cout<<"Enter to (r c): "; }
    return m;
}

bool Tic4x4::validMove(const Move& m, char player) const {
    if(m.r1<0||m.r1>3||m.c1<0||m.c1>3) return false;
    if(m.r2<0||m.r2>3||m.c2<0||m.c2>3) return false;
    if(board[m.r1][m.c1] != player) return false;
    if(board[m.r2][m.c2] != ' ') return false;
    int dr = abs(m.r2 - m.r1), dc = abs(m.c2 - m.c1);
    if(dr + dc != 1) return false;
    return true;
}

void Tic4x4::applyMove(const Move& m) {
    board[m.r2][m.c2] = board[m.r1][m.c1];
    board[m.r1][m.c1] = ' ';
}

bool Tic4x4::checkWin(char s) const {
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            if(board[i][j]==s && board[i][j+1]==s && board[i][j+2]==s) return true;
            if(board[j][i]==s && board[j+1][i]==s && board[j+2][i]==s) return true;
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            if(board[i][j]==s && board[i+1][j+1]==s && board[i+2][j+2]==s) return true;
        }
        for(int j=2;j<4;j++){
            if(board[i][j]==s && board[i+1][j-1]==s && board[i+2][j-2]==s) return true;
        }
    }
    return false;
}

vector<Tic4x4::Move> Tic4x4::genMoves(char player) const {
    vector<Move> out;
    for(int r=0;r<4;r++) for(int c=0;c<4;c++){
        if(board[r][c] != player) continue;
        const int dr[4]={1,-1,0,0}, dc[4]={0,0,1,-1};
        for(int d=0;d<4;d++){
            Move m{r,c,r+dr[d],c+dc[d]};
            if(m.r2<0||m.r2>3||m.c2<0||m.c2>3) continue;
            if(board[m.r2][m.c2]==' ') out.push_back(m);
        }
    }
    return out;
}

Tic4x4::Move Tic4x4::aiChooseMove(char aiSymbol) {
    char opp = (aiSymbol=='X' ? 'O' : 'X');
    auto myMoves = genMoves(aiSymbol);
    for(auto mv: myMoves){
        char b0 = board[mv.r1][mv.c1], b1 = board[mv.r2][mv.c2];
        Tic4x4 tmp = *this;
        tmp.applyMove(mv);
        if(tmp.checkWin(aiSymbol)) return mv;
    }
    auto oppMoves = genMoves(opp);
    for(auto mvOpp: oppMoves){
        char b0 = board[mvOpp.r1][mvOpp.c1], b1 = board[mvOpp.r2][mvOpp.c2];
        Tic4x4 tmp = *this;
        tmp.applyMove(mvOpp);
        if(tmp.checkWin(opp)){
            for(auto myMv: myMoves){
                Tic4x4 tmp2 = *this;
                tmp2.applyMove(myMv);
                bool blocks = true;
                auto nextOpp = tmp2.genMoves(opp);
                for(auto nm: nextOpp){
                    Tic4x4 tmp3 = tmp2;
                    tmp3.applyMove(nm);
                    if(tmp3.checkWin(opp)) { blocks = false; break; }
                }
                if(blocks) return myMv;
            }
        }
    }
    int bestScore = -1000;
    Move best = myMoves.empty() ? Move{-1,-1,-1,-1} : myMoves[0];
    for(auto mv: myMoves){
        int score = 0;
        Tic4x4 tmp = *this;
        tmp.applyMove(mv);
        auto myNext = tmp.genMoves(aiSymbol);
        score += (int)myNext.size();
        for(int r=0;r<4;r++) for(int c=0;c<4;c++){
            if(tmp.board[r][c]==aiSymbol){
                for(int len=0;len<4;len++){
                    int rr=r, cc=c;
                }
            }
        }
        if(score>bestScore){ bestScore=score; best=mv; }
    }
    if(best.r1==-1) return myMoves.empty() ? Move{-1,-1,-1,-1} : myMoves[0];
    return best;
}

void Tic4x4::runGame() {
    string name1;
    cout << "Enter name for Player 1 (X): ";
    getline(cin>>ws, name1);
    cout << "Choose Player 2 type:\n1. Human\n2. Computer (AI)\nEnter choice: ";
    int choice; cin >> choice;
    string name2; bool p2isAI=false;
    if(choice==1){ cout<<"Enter name for Player 2 (O): "; getline(cin>>ws, name2); } else { name2="Computer AI"; p2isAI=true; }
    printBoard();
    while(true){
        if(turn=='X'){
            cout << name1 << " (" << turn << ") turn.\n";
            Move m = readMove();
            if(!validMove(m,'X')){ cout<<"Invalid move\n"; continue; }
            applyMove(m);
            printBoard();
            if(checkWin('X')){ cout << name1 << " WINS!\n"; break; }
            turn='O';
        } else {
            cout << name2 << " (" << turn << ") turn.\n";
            Move m;
            if(p2isAI){
                m = aiChooseMove('O');
                if(m.r1==-1){ cout<<"No moves for AI\n"; break; }
                cout << "Computer moved from " << m.r1 << " " << m.c1 << " to " << m.r2 << " " << m.c2 << "\n";
            } else {
                m = readMove();
            }
            if(!validMove(m,'O')){ cout<<"Invalid move\n"; continue; }
            applyMove(m);
            printBoard();
            if(checkWin('O')){ cout << name2 << " WINS!\n"; break; }
            turn='X';
        }
    }
}


void launchMovingTTT(){ 
    cout << "\nStarting 4x4 Moving Tic-Tac-Toe...\n";
    Tic4x4 g; g.runGame(); 
}
