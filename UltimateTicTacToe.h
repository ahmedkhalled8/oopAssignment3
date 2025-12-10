#ifndef ULTIMATE_TTT_H
#define ULTIMATE_TTT_H


class UltimateTTT {
public:
    char boards[9][3][3]; ///< 9 mini boards, each 3×3
    char big[9];          ///< Large board tracking winners of each mini board


    UltimateTTT();

   
    void print();

    bool playMove(int board, int row, int col, char p);

   
    char checkMini(int board);

    
    void markBig(int board, char p);

  
    char checkBig();
};
void launchUltimate();

#endif
