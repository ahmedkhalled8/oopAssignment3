#pragma once
#ifndef NUMERICAL_H
#define NUMERICAL_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class NumericalBoard
 * @brief Implements Numerical Tic-Tac-Toe (Magic Square variant).
 *
 * Players place numbers 1–9, attempting to form a line summing to 15.
 */
class NumericalBoard : public Board<int> {
private:
    vector<int> used_numbers; ///< Numbers already placed on the board

public:
    NumericalBoard();

    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override { return false; }
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;

    /**
     * @brief Returns all used numbers.
     */
    vector<int> get_used_numbers() const;
};

/**
 * @class NumericalUI
 * @brief Handles input/output for Numerical Tic-Tac-Toe.
 */
class NumericalUI : public UI<int> {
public:
    NumericalUI();

    /**
     * @brief Creates a player for the game.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /**
     * @brief Gets move input from a player or CPU.
     */
    Move<int>* get_move(Player<int>* player) override;
};
void launchNumerical();
#endif
