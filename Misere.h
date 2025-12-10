

#ifndef MISERE_H
#define MISERE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>


class MisereBoard : public Board<char> {
public:
   
    MisereBoard();

   
    bool update_board(Move<char>* move) override;


    bool is_win(Player<char>* player) override;

 
    bool is_lose(Player<char>* player) override;

  
    bool is_draw(Player<char>* player) override;

    
    bool game_is_over(Player<char>* player) override;

    
    bool has_three_in_row(char s) const;

private:
    
    char opposite_symbol(char s) const;
};


class MisereUI : public UI<char> {
public:
    MisereUI();


    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

 
    Move<char>* get_move(Player<char>* player) override;

private:
    Move<char>* get_human_move(Player<char>* player);
    Move<char>* get_computer_move(Player<char>* player);
    Move<char>* random_empty_move(Player<char>* player);

    bool three_in_row_in_matrix(const std::vector<std::vector<char>>& mat, char s) const;
    bool read_int(int& out);
};
void launchMisere();
#endif 
