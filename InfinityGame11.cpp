#include "InfinityGame11.h" // Assuming this is the correct header file name
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

using namespace std;


Infinity_Board::Infinity_Board() : Board<char>(3,3) {
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
            board[i][j] = blank_symbol;
    total_moves = 0;
    while(!history.empty()) history.pop();
}


bool Infinity_Board::update_board(Move<char>* move) {
    if(!move) return false;
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if(x<0 || x>=rows || y<0 || y>=columns) return false;
    if(board[x][y] != blank_symbol) return false;

    board[x][y] = sym;
    history.push({x,y});
    total_moves++;

    if(history.size() > 6) {
        auto old = history.front();
        history.pop();
        int ox = old.first;
        int oy = old.second;
        board[ox][oy] = blank_symbol;
    }

    return true;
}


bool Infinity_Board::has_three_in_a_row(char s) const {
    for(int i=0;i<3;i++)
        if(board[i][0]==s && board[i][1]==s && board[i][2]==s) return true;
    for(int j=0;j<3;j++)
        if(board[0][j]==s && board[1][j]==s && board[2][j]==s) return true;
    if(board[0][0]==s && board[1][1]==s && board[2][2]==s) return true;
    if(board[0][2]==s && board[1][1]==s && board[2][0]==s) return true;
    return false;
}

bool Infinity_Board::is_win(Player<char>* player) {
    if(!player) return false;
    return has_three_in_a_row(player->get_symbol());
}

bool Infinity_Board::is_lose(Player<char>* player) {
    if(!player) return false;
    char s = player->get_symbol();
    char opponent = (s == 'X' ? 'O' : (s == 'O' ? 'X' : 0));

    return opponent ? has_three_in_a_row(opponent) : false;
}

bool Infinity_Board::is_draw(Player<char>*) {
    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player);
}


Infinity_Player::Infinity_Player(string name, char symbol, PlayerType type, char fixed)
    : Player<char>(name,symbol,type), fixed_symbol(fixed) {}

char Infinity_Player::get_fixed_symbol() const { return fixed_symbol; }
void Infinity_Player::set_fixed_symbol(char c) { fixed_symbol = c; }


Infinity_UI::Infinity_UI() : UI<char>("Starting Infinity Tic-Tac-Toe!",3) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Player<char>* Infinity_UI::create_player(string& name, char, PlayerType type) {
    static char first_choice = 0;
    char chosen = 0;

    if(first_choice==0){
        int choice = 0;
        while(true){
            cout << "Choose your symbol:\n1. X\n2. O\nEnter choice: ";
            if(cin>>choice && (choice==1||choice==2)){
                chosen = (choice==1?'X':'O');
                first_choice = chosen;
                break;
            }
            cout << "Invalid choice.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    } else {
        chosen = (first_choice=='X'?'O':'X');
        cout << name << " will automatically get symbol: " << chosen << "\n";
    }

    return new Infinity_Player(name,chosen,type,chosen);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x=0,y=0;
    if(!player) return nullptr;
    char c = player->get_symbol();

    const auto& board_matrix = player->get_board_ptr()->get_board_matrix();
    const char blank_symbol = '.'; // Assuming '.' is the blank symbol

    if(player->get_type()==PlayerType::HUMAN){
        while(true){
            cout << player->get_name() << " (" << c << ") - Enter x y (0-2): ";

            if((cin>>x>>y)) {

                if (x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cout << "Invalid input: Coordinates must be between 0 and 2.\n";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue; // Skip to next iteration
                }

                if (board_matrix[x][y] != blank_symbol) {
                    cout << "Invalid input: Spot (" << x << "," << y << ") is already occupied.\n";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue; // Skip to next iteration
                }

                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                break;
            }

            cout << "Invalid input or out of bounds.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    } else {
        auto m = player->get_board_ptr()->get_board_matrix();
        vector<pair<int,int>> empty;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(m[i][j]=='.') empty.push_back({i,j});

        if(!empty.empty()){
            auto p = empty[rand()%empty.size()];
            x=p.first;
            y=p.second;
        } else {
            x=rand()%3; y=rand()%3;
        }

        cout << "Computer plays " << c << " at (" << x << "," << y << ")\n";
    }

    return new Move<char>(x,y,c);
}

void Infinity_UI::print_board(Board<char>* b){
    cout << "\n   0   1   2\n  -----------\n";
    for(int i=0;i<3;i++){
        cout << i << " | ";
        for(int j=0;j<3;j++){
            cout << b->get_board_matrix()[i][j] << " | ";
        }
        cout << "\n  -----------\n";
    }
}

void launchInfinity() { 
     cout << "\nStarting Infinity Tic-Tac-Toe...\n";

    Infinity_UI* ui = new Infinity_UI();
    Infinity_Board* board = new Infinity_Board();

    Player<char>** players = ui->setup_players();
    GameManager<char> manager(board, players, ui);
    manager.run();

    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}