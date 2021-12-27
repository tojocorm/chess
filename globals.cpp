#include "globals.h"

std::string get_type(pieceType type){
    switch(type) {
        case Pawn :
            return "Pawn";
        case Bishop :
            return "Bishop";
        case Knight :
            return "Knight";
        case Rook :
            return "Rook";
        case King :
            return "King";
        case Queen :
            return "Queen";
        case Blank :
            return "Blank";
   }
}
// return the points of the vector
int get_points(std::vector< pieceType > vec){
    std::vector<int> vals;
    vals.push_back(1);
    vals.push_back(3);
    vals.push_back(3);
    vals.push_back(5);
    vals.push_back(9);
    vals.push_back(0);

    int sum = 0;
    for(size_t i = 0; i < vec.size(); ++i){
        sum += vals[vec[i]];
    }
    return sum;
}

std::string get_board_symbol(pieceType type){
    switch(type) {
        case Pawn :
            return "P";
        case Bishop :
            return "B";
        case Knight :
            return "K";
        case Rook :
            return "R";
        case King :
            return "X";
        case Queen :
            return "Q";
        case Blank :
            return "o";
   }
}