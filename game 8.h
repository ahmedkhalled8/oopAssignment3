/**
* @file Pyramid_TTT.h
 * @brief Declares the Pyramid Tic-Tac-Toe game.
 *
 * The game is played on a pyramid-shaped 1-3-5 board.
 */

#ifndef PYRAMID_TTT_H
#define PYRAMID_TTT_H

#include <string>

/**
 * @class Pyramid_TTT
 * @brief Manages gameplay and rules for the Pyramid tic-tac-toe board.
 */
class Pyramid_TTT {
private:
    char board[3][5]; ///< The pyramid-shaped game board.

public:
    /** @brief Initializes the board. */
    Pyramid_TTT();

    /** @brief Prints the board. */
    void printBoard();

    /** @brief Runs the game loop. */
    void runGame();

private:
    /**
     * @brief Attempts to place a mark.
     * @param userRow Row index.
     * @param userCol Column index.
     * @param p Player symbol.
     */
    bool place(int userRow, int userCol, char p);

    /**
     * @brief Validates a board cell.
     */
    bool validCell(int userRow, int userCol) const;

    /**
     * @brief Checks whether the given player has won.
     */
    bool checkWin(char p) const;

    /**
     * @brief Performs an AI move.
     */
    bool aiMove(char aiSymbol);
};

#endif
