#include <iostream>
#include <vector>
#include <algorithm>
#include "numericalclass.h"
using namespace std;

NumericalBoard::NumericalBoard() : Board(3, 3) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = 0;
        }
    }
    used_numbers.clear();
    n_moves = 0;
    cout << "\nNumerical Board Created Successfully!\n";
}

bool NumericalBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "\nInvalid position! Use 0-2 only.\n";
        return false;
    }

    if (board[x][y] != 0) {
        cout << "\nCell (" << x << "," << y << ") already occupied!\n";
        return false;
    }

    if (number < 1 || number > 9) {
        cout << "\nInvalid number! Use 1-9 only.\n";
        return false;
    }

    for (int used : used_numbers) {
        if (used == number) {
            cout << "\nNumber " << number << " already used!\n";
            return false;
        }
    }

    board[x][y] = number;
    used_numbers.push_back(number);
    n_moves++;
    cout << "\nMove accepted: " << number << " at (" << x << "," << y << ")\n";
    return true;
}

bool NumericalBoard::is_win(Player<int>* player) {
    const int target_sum = 15;

    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
            int sum = board[i][0] + board[i][1] + board[i][2];
            if (sum == target_sum) {
                cout << "\n*** WINNER! Row " << i << " sums to 15 ***\n";
                return true;
            }
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) {
            int sum = board[0][j] + board[1][j] + board[2][j];
            if (sum == target_sum) {
                cout << "\n*** WINNER! Column " << j << " sums to 15 ***\n";
                return true;
            }
        }
    }

    if (board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) {
        int sum = board[0][0] + board[1][1] + board[2][2];
        if (sum == target_sum) {
            cout << "\n*** WINNER! Main diagonal sums to 15 ***\n";
            return true;
        }
    }

    if (board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) {
        int sum = board[0][2] + board[1][1] + board[2][0];
        if (sum == target_sum) {
            cout << "\n*** WINNER! Anti-diagonal sums to 15 ***\n";
            return true;
        }
    }

    return false;
}

bool NumericalBoard::is_draw(Player<int>* player) {
    if (n_moves >= 9 && !is_win(player)) {
        cout << "\n*** DRAW! Board is full ***\n";
        return true;
    }
    return false;
}

bool NumericalBoard::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

vector<int> NumericalBoard::get_used_numbers() const {
    return used_numbers;
}

NumericalUI::NumericalUI() : UI<int>("\n===== Welcome to Numerical Tic-Tac-Toe =====\n", 3) {}

Player<int>* NumericalUI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}

vector<int> get_available_numbers(const vector<int>& used_numbers, char symbol) {
    vector<int> available;

    vector<int> allowed_numbers;

    if (symbol == '1') {
        for (int i = 1; i <= 9; i += 2) {
            allowed_numbers.push_back(i);
        }
    }
    else if (symbol == '2') {
        for (int i = 2; i <= 8; i += 2) {
            allowed_numbers.push_back(i);
        }
    }

    for (int num : allowed_numbers) {
        if (find(used_numbers.begin(), used_numbers.end(), num) == used_numbers.end()) {
            available.push_back(num);
        }
    }

    return available;
}

Move<int>* NumericalUI::get_move(Player<int>* player) {
    int x, y, number;

    if (player->get_type() == PlayerType::HUMAN) {
        auto board_ptr = dynamic_cast<NumericalBoard*>(player->get_board_ptr());
        vector<int> used_nums = board_ptr->get_used_numbers();
        vector<int> available_nums = get_available_numbers(used_nums, (char)player->get_symbol());

        while (true) {
            cout << "\n----------------------------------------\n";
            cout << player->get_name() << "'s turn";
            cout << " [Player " << (char)player->get_symbol() << " - ";

            if (player->get_symbol() == '1') {
                cout << "ODD numbers]\n";
            }
            else {
                cout << "EVEN numbers]\n";
            }

            cout << "----------------------------------------\n";

            cout << "\nAvailable numbers for you: ";
            for (int num : available_nums) {
                cout << num << " ";
            }
            cout << endl;

            cout << "Enter your move (number[from above], row[0-2] and column[0-2]): ";

            if (!(cin >> number >> x >> y)) {
                cout << "\n!! Invalid input! Please enter numbers only.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            bool number_available = false;
            for (int avail_num : available_nums) {
                if (avail_num == number) {
                    number_available = true;
                    break;
                }
            }

            if (!number_available) {
                cout << "\n!! Number " << number << " is not available for you!\n";
                cout << "Please choose from available numbers only.\n";
                continue;
            }

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "\n!! Positions must be between 0 and 2!\n";
                continue;
            }

            cout << endl << player->get_name() << " plays: " << number << " at (" << x << "," << y << ")\n";
            break;
        }

    }
    else {
        x = rand() % 3;
        y = rand() % 3;

        auto board_ptr = dynamic_cast<NumericalBoard*>(player->get_board_ptr());
        vector<int> used_nums = board_ptr->get_used_numbers();
        vector<int> available_nums = get_available_numbers(used_nums, (char)player->get_symbol());

        if (!available_nums.empty()) {
            number = available_nums[rand() % available_nums.size()];
        }
        else {
            number = (player->get_symbol() == '1') ? 1 : 2;
        }

        cout << "Computer plays: " << number << " at (" << x << "," << y << ")\n";
    }

    return new Move<int>(x, y, number);
}