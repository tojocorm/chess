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
   }
}

int get_points(std::vector< pieceType > vec){
    std::vector<int> vals{1, 3, 3, 5, 9, 0};
    int sum = 0;
    for(int i = 0; i < vec.size(); ++i){

    }
}