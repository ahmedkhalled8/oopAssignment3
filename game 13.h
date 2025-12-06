#ifndef MEMORY_TTT_H
#define MEMORY_TTT_H

/**
 * @class Memory_TTT
 * @brief Implements a hidden Tic-Tac-Toe memory game.
 *
 * The board shows '?' for occupied cells and '-' for empty cells.
 */
class Memory_TTT {
private:
    char hidden[4][4]; ///< Internal hidden board (1–3 used)

public:
    /**
     * @brief Constructor initializes all hidden cells to '-'.
     */
    Memory_TTT();

    /**
     * @brief Prints the masked board to the screen.
     */
    void printBoard();

    /**
     * @brief Updates a board position.
     * @param r Row (1–3)
     * @param c Column (1–3)
     * @param player Player symbol
     * @return True if valid move
     */
    bool updateBoard(int r, int c, char player);

    /**
     * @brief Checks if the player has a winning line.
     * @param player Symbol to check
     * @return True if the player wins
     */
    bool checkWin(char player);
};

#endif
