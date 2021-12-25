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
    for(int i = 0; i < vec.size(); ++i){

    }
}