#ifndef ULTIMATE_TTT_H
#define ULTIMATE_TTT_H

/**
 * @class UltimateTTT
 * @brief Implements the Ultimate Tic-Tac-Toe board logic.
 *
 * Contains 9 mini 3×3 boards and a larger 3×3 board representing the winners
 * of each mini-board.
 */
class UltimateTTT {
public:
    char boards[9][3][3]; ///< 9 mini boards, each 3×3
    char big[9];          ///< Large board tracking winners of each mini board

    /**
     * @brief Constructor initializes all boards to '-'.
     */
    UltimateTTT();

    /**
     * @brief Prints all mini and big boards in formatted layout.
     */
    void print();

    /**
     * @brief Attempts to play a move on the given mini board.
     * @param board Mini-board index (0–8)
     * @param row Row within mini-board (0–2)
     * @param col Column within mini-board (0–2)
     * @param p Player symbol ('X' or 'O')
     * @return True if move is valid and placed successfully
     */
    bool playMove(int board, int row, int col, char p);

    /**
     * @brief Checks if a mini-board has a winner.
     * @param board Mini-board index
     * @return 'X', 'O', or '-' for no winner
     */
    char checkMini(int board);

    /**
     * @brief Marks the large board with a winner.
     * @param board Mini-board index
     * @param p Winner ('X' or 'O')
     */
    void markBig(int board, char p);

    /**
     * @brief Checks if the large 3×3 board has a winner.
     * @return 'X', 'O', or '-' for no winner
     */
    char checkBig();
};

#endif
