/**
 * @file INFINITY_CLASSES.h
 * @brief Declares the Infinity Tic-Tac-Toe board, player, and UI classes.
 *
 * Infinity mode allows unlimited moves. Every move is recorded in a
 * queue-based history, and three-in-a-row still determines win/lose.
 */

#ifndef INFINITY_H
#define INFINITY_H

#include "BoardGame_Classes.h"
#include <queue>
#include <string>
#include <vector>

/**
 * @class Infinity_Board
 * @brief A non-bounded Tic-Tac-Toe variant with infinite moves tracked in history.
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';   ///< Empty cell character.
    std::queue<std::pair<int,int>> history; ///< Stores coordinates of all moves.
    int total_moves = 0;        ///< Counter for number of moves made.

public:
    /** @brief Initializes the Infinity board. */
    Infinity_Board();

    /** @brief Applies a move, stores it into history queue. */
    bool update_board(Move<char>* move) override;

    /** @brief True if the player has 3-in-a-row. */
    bool is_win(Player<char>* player) override;

    /** @brief True if the player loses (enemy forms 3-in-a-row). */
    bool is_lose(Player<char>* player) override;

    /** @brief A draw occurs only if rules define no possible wins. */
    bool is_draw(Player<char>* player) override;

    /** @brief Returns true if win/lose/draw has occurred. */
    bool game_is_over(Player<char>* player) override;

    /** @brief Checks if symbol `s` has 3-in-a-row. */
    bool has_three_in_a_row(char s) const;
};

/**
 * @class Infinity_Player
 * @brief Player class for Infinity mode, storing a fixed symbol.
 */
class Infinity_Player : public Player<char> {
private:
    char fixed_symbol; ///< Symbol used for game logic.

public:
    /** @brief Constructs a player for Infinity mode. */
    Infinity_Player(std::string name, char symbol, PlayerType type, char fixed);

    /** @brief Returns fixed symbol. */
    char get_fixed_symbol() const;

    /** @brief Sets the fixed symbol. */
    void set_fixed_symbol(char c);
};

/**
 * @class Infinity_UI
 * @brief UI handler for Infinity Tic-Tac-Toe (input/output).
 */
class Infinity_UI : public UI<char> {
public:
    /** @brief Prints intro message. */
    Infinity_UI();

    /** @brief Creates a human or AI Infinity player. */
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /** @brief Gets a move from the current player. */
    Move<char>* get_move(Player<char>* player) override;

    /** @brief Prints the game board. */
    void print_board(Board<char>* board);
};
void launchInfinity();
#endif
