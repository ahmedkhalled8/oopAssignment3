#include <iostream>
#include "boardgameclass.h"
#include "game 11.h"
#include "game 7.h"
#include "game 5.h"
#include "numericalclass.h"
#include "SUSClass.h"

using namespace std;

// Simple placeholder UI classes for Game7 and Game5
class Game7UI {
public:
    Player<char>** setup_players() {
        Player<char>** players = new Player<char>*[2];
        string n1, n2;
        cout << "Enter Player 1 (X) name: "; cin >> n1;
        cout << "Enter Player 2 (O) name: "; cin >> n2;
        players[0] = new Player<char>(n1, 'X', PlayerType::HUMAN);
        players[1] = new Player<char>(n2, 'O', PlayerType::HUMAN);
        return players;
    }

    void display_board_matrix(const vector<vector<char>>& matrix) const {}
    Move<char>* get_move(Player<char>* p) { return nullptr; }
};

class Game5UI {
public:
    Player<char>** setup_players() {
        Player<char>** players = new Player<char>*[2];
        string n1, n2;
        cout << "Enter Player 1 (X) name: "; cin >> n1;
        cout << "Enter Player 2 (O) name: "; cin >> n2;
        players[0] = new Player<char>(n1, 'X', PlayerType::HUMAN);
        players[1] = new Player<char>(n2, 'O', PlayerType::HUMAN);
        return players;
    }

    void display_board_matrix(const vector<vector<char>>& matrix) const {}
    Move<char>* get_move(Player<char>* p) { return nullptr; }
};

class SUSUI {
public:
    Player<char>** setup_players() {
        Player<char>** players = new Player<char>*[2];
        string n1, n2;
        cout << "Enter Player 1 (X) name: "; cin >> n1;
        cout << "Enter Player 2 (O) name: "; cin >> n2;
        players[0] = new Player<char>(n1, 'X', PlayerType::HUMAN);
        players[1] = new Player<char>(n2, 'O', PlayerType::HUMAN);
        return players;
    }

    Move<char>* get_move(Player<char>* p) { return nullptr; }
    void display_board_matrix(const vector<vector<char>>& matrix) const {}
};

int main() {
    int choice;

    while (true) {
        cout << "\n============== GAME MENU ==============\n";
        cout << "1. Play Game 11\n";
        cout << "2. Play Game 7\n";
        cout << "3. Play Game 5\n";
        cout << "4. Play SUS Game\n";
        cout << "5. Play Numerical Tic-Tac-Toe\n";
        cout << "6. Exit\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            InfinityBoard* board = new InfinityBoard();
            Game11UI* ui = new Game11UI();
            auto players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            for (int i = 0; i < 2; i++) delete players[i];
            delete[] players;
            delete board;
            delete ui;
            break;
        }
        case 2: {
            FourByFourBoard* board = new FourByFourBoard();
            Game7UI* ui = new Game7UI();
            auto players = ui->setup_players();
            // Note: you may need a custom game loop for Game7
            delete[] players;
            delete board;
            delete ui;
            break;
        }

        case 3: {
            MisereBoard* board = new MisereBoard();
            Game5UI* ui = new Game5UI();
            auto players = ui->setup_players();
            // Note: you may need a custom game loop for Game5
            delete[] players;
            delete board;
            delete ui;
            break;
        }

        case 4: {
            SUSBoard* board = new SUSBoard();
            SUSUI* ui = new SUSUI();
            auto players = ui->setup_players();
            // Note: you may need a custom game loop for SUS
            delete[] players;
            delete board;
            delete ui;
            break;
        }

        case 5: {
            NumericalBoard* board = new NumericalBoard();
            NumericalUI* ui = new NumericalUI();
            auto players = ui->setup_players();
            GameManager<int> game(board, players, ui);
            game.run();

            for (int i = 0; i < 2; i++) delete players[i];
            delete[] players;
            delete board;
            delete ui;
            break;
        }

        case 6:
            cout << "Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}