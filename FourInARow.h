#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

/**
 * @file FourInARow.h
 * @brief Defines the FourInARow class implementing a Connect Four board.
 *
 * This class provides the logic for a standard 6x7 Connect Four game.
 * Players drop pieces into columns, and gravity determines the final row.
 * A player wins by connecting 4 identical symbols horizontally,
 * vertically, or diagonally.
 */
class FourInARow : public Board<char> {
public:
    /**
     * @brief Constructs a 6x7 Connect Four board initialized with spaces.
     */
    FourInARow();

    /**
     * @brief Attempts to place a player's symbol into the requested column.
     * @param move The Move containing column and symbol.
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player.
     * @return true if the player has connected four.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Connect Four does not use lose states.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if the board is full and no winner exists.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Returns true if the game is finished (win or draw).
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Prints the current board layout.
     */
    void display_board();

private:
    /**
     * @brief Checks for 4 in a row starting from a cell in a direction.
     * @param row Starting row
     * @param col Starting col
     * @param dr Row direction
     * @param dc Col direction
     * @param symbol Player symbol
     * @return true if 4 in a row found
     */
    bool check_four(int row, int col, int dr, int dc, char symbol);

    /**
     * @brief Returns the lowest empty row in a given column.
     */
    int get_lowest_empty_row(int col);
};
void launchConnect4();
#endif
