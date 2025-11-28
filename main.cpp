#include <iostream>
#include "game3h.h"
#include "game10h.h"
using namespace std;

void playerMove(BoardGame &game, char player, int size);

int main() {
    int choice;
    cout << "Choose the game:\n1. Game 3 (5x5 Tic Tac Toe)\n2. Game 10 (Obstacles Tic Tac Toe)\nChoice: ";
    cin >> choice;

    BoardGame *game = nullptr;
    int size = 5;

    if(choice == 1) game = new game3h();
    else if(choice == 2) { game = new game10h(); size = 6; }
    else { cout << "Invalid choice!\n"; return 0; }

    char winner = ' ';
    char currentPlayer = 'X';

    while(winner == ' ') {
        cout << "\nCurrent Board:\n";
        game->displayBoard();

        playerMove(*game, currentPlayer, size);

        if(choice == 2 && currentPlayer == 'O') {
            ((game10h*)game)->addObstacles();
            cout << "Two new obstacles added!\n";
        }

        winner = game->checkWinner();
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    cout << "\nFinal Board:\n";
    game->displayBoard();
    if(winner == 'D') cout << "Draw!\n";
    else cout << "The winner is: " << winner << "!\n";

    delete game;
    return 0;
}

void playerMove(BoardGame &game, char player, int size) {
    int row, col;
    while(true) {
        cout << "Player " << player << ", enter row and column (0-" << size-1 << "): ";
        cin >> row >> col;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid input, try again.\n";
            continue;
        }
        if(game.makeMove(row, col, player)) break;
        else cout << "Invalid move, try again.\n";
    }
}
