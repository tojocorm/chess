#include "globals.h"

// prints the board from the perspective of turn
void print_board(const int turn){
    cout << "Board, Move " << move << ":" << endl << endl;
    turn == White ? cout << "White " : cout << "Black ";

    cout << "has taken pieces: ";
    for(auto it = takenPieces[turn].begin(); it != takenPieces[turn].end(); ++it){
        pieceType type = it.first;
        int num = it.second;

        cout << 
    }
}

