#include "globals.h"

std::string get_type(piece piece){
    switch(piece.type) {
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
    return "";
}
// return the points of the vector
int get_points(std::vector< piece > vec){
    std::vector<int> vals;
    vals.push_back(1);
    vals.push_back(3);
    vals.push_back(3);
    vals.push_back(5);
    vals.push_back(9);
    vals.push_back(0);

    int sum = 0;
    for(size_t i = 0; i < vec.size(); ++i){
        sum += vals[vec[i].type];
    }
    return sum;
}

char get_board_symbol(piece piece){
    // not sure how to do this but I weant these unicodes
    // https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
    int color = piece.color;
    if(color == White){
        switch(piece.type) {
            case Pawn :
                return 'P';
            case Bishop :
                return 'B';
            case Knight :
                return 'K';
            case Rook :
                return 'R';
            case King :
                return 'X';
            case Queen :
                return 'Q';
            case Blank :
                return 'o';
        }
    }
    switch(piece.type) {
        case Pawn :
            return 'p';
        case Bishop :
            return 'b';
        case Knight :
            return 'k';
        case Rook :
            return 'r';
        case King :
            return 'x';
        case Queen :
            return 'q';
        case Blank :
            return 'o';
    }
    return '\0';
}

bool valid_move(std::string play, bool check){
    return false;
}

void make_move(std::string play){
    return;
}
// 0 is neither check nor mate, 1 is check, 2 is mate
int check_checkmate(int turn){
    return 0;
}
