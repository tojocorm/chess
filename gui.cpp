#include "gui.h"

// prints the board from the perspective of turn
void print_board(const int turn){
    // invert turn -- everything for the current turn should be printed last
    int this_turn = !turn;
    cout << "Game Board, Move " << move << ":" << endl << endl;
    this_turn == White ? cout << "White" : cout << "Black";

    cout << " has taken pieces: ";
    for(auto it = takenPieces[this_turn].begin(); it != takenPieces[this_turn].end(); ++it){
        pieceType type = it.first;
        int num = it.second;
        for(int i = 0; i < num; ++i){
            cout << get_type(type) << ", ";
        }
    }

    if(turn == White){
        for(int i = board.size() - 1; i >= 0; --i){
            for(int j = board[i].size() - 1; j >= 0; --j){
                print_space(board[i][j]);
            }
            cout << endl;
        }
    }
    else{
        for(int i = 0; i < board.size(); ++i){
            for(int j = 0; j < board[i].size(); ++j){
                print_space(board[i][j]);
            }
            cout << endl;
        }
    }
    turn == White ? cout << "White" : cout << "Black";

    cout << " has taken pieces: ";
    for(auto it = takenPieces[this_turn].begin(); it != takenPieces[this_turn].end(); ++it){
        pieceType type = it.first;
        int num = it.second;
        for(int i = 0; i < num; ++i){
            cout << get_type(type) << ", ";
        }
    }
}

void print_space(pieceType type){
    std::string symbol = get_board_symbol(type);
    cout << symbol << " ";
}